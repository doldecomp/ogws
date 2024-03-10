#include <revolution/AI.h>
#include <revolution/BASE.h>
#include <revolution/DSP.h>
#include <revolution/EXI.h>
#include <revolution/OS.h>
#include <string.h>

static OSInterruptHandler* InterruptHandlerTable;
s64 __OSLastInterruptTime;
s16 __OSLastInterrupt;
u32 __OSLastInterruptSrr0;

static u32 InterruptPrioTable[] = {
    0x00000100, 0x00000040, 0xF8000000, 0x00000200, 0x00000080, 0x00000010,
    0x00003000, 0x00000020, 0x03FF8C00, 0x04000000, 0x00004000, 0xFFFFFFFF};

static void ExternalInterruptHandler(u8 type, OSContext* ctx);

asm BOOL OSDisableInterrupts(void) {
    // clang-format off
    nofralloc

    entry __RAS_OSDisableInterrupts_begin

    mfmsr r3
    // Clear external interrupts bit
    rlwinm r4, r3, 0, 17, 15
    mtmsr r4

    entry __RAS_OSDisableInterrupts_end

    // Return old interrupt status
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
}

asm BOOL OSEnableInterrupts(void) {
    // clang-format off
    nofralloc

    mfmsr r3
    // Set external interrupts bit
    ori r4, r3, MSR_EE
    mtmsr r4

    // Return old interrupt status
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
}

asm BOOL OSRestoreInterrupts(register BOOL status){
    // clang-format off
    nofralloc

    cmpwi status, 0
    mfmsr r4
    beq disable

    // Set external interrupts bit
    ori r5, r4, MSR_EE
    b set_msr

disable:
    // Clear external interrupts bit
    rlwinm r5, r4, 0, 17, 15

set_msr:
    mtmsr r5
    // Return old interrupt status
    rlwinm r3, r4, 17, 31, 31
    blr
    // clang-format on
}

OSInterruptHandler
    __OSSetInterruptHandler(OSInterruptType type, OSInterruptHandler handler) {
    OSInterruptHandler old = InterruptHandlerTable[type];
    InterruptHandlerTable[type] = handler;
    return old;
}

OSInterruptHandler __OSGetInterruptHandler(OSInterruptType type) {
    return InterruptHandlerTable[type];
}

void __OSInterruptInit(void) {
    InterruptHandlerTable =
        (OSInterruptHandler*)OSPhysicalToCached(OS_PHYS_INTR_HANDLER_TABLE);
    memset(InterruptHandlerTable, 0, sizeof(OSInterruptHandler) * OS_INTR_MAX);

    *(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK) = 0;
    *(u32*)OSPhysicalToCached(OS_PHYS_CURRENT_INTR_MASK) = 0;

    PI_HW_REGS[PI_INTMR] =
        PI_INTMR_EXI | PI_INTMR_AI | PI_INTMR_DSP | PI_INTMR_MEM;
    OS_UNK_CD000034 = 0x40000000;

    __OSMaskInterrupts(
        OS_INTR_MASK(OS_INTR_MEM_0) | OS_INTR_MASK(OS_INTR_MEM_1) |
        OS_INTR_MASK(OS_INTR_MEM_2) | OS_INTR_MASK(OS_INTR_MEM_3) |
        OS_INTR_MASK(OS_INTR_MEM_ADDRESS) | OS_INTR_MASK(OS_INTR_DSP_AI) |
        OS_INTR_MASK(OS_INTR_DSP_ARAM) | OS_INTR_MASK(OS_INTR_DSP_DSP) |
        OS_INTR_MASK(OS_INTR_AI_AI) | OS_INTR_MASK(OS_INTR_EXI_0_EXI) |
        OS_INTR_MASK(OS_INTR_EXI_0_TC) | OS_INTR_MASK(OS_INTR_EXI_0_EXT) |
        OS_INTR_MASK(OS_INTR_EXI_1_EXI) | OS_INTR_MASK(OS_INTR_EXI_1_TC) |
        OS_INTR_MASK(OS_INTR_EXI_1_EXT) | OS_INTR_MASK(OS_INTR_EXI_2_EXI) |
        OS_INTR_MASK(OS_INTR_EXI_2_TC) | OS_INTR_MASK(OS_INTR_PI_CP) |
        OS_INTR_MASK(OS_INTR_PI_PE_TOKEN) | OS_INTR_MASK(OS_INTR_PI_PE_FINISH) |
        OS_INTR_MASK(OS_INTR_PI_SI) | OS_INTR_MASK(OS_INTR_PI_DI) |
        OS_INTR_MASK(OS_INTR_PI_RSW) | OS_INTR_MASK(OS_INTR_PI_ERROR) |
        OS_INTR_MASK(OS_INTR_PI_VI) | OS_INTR_MASK(OS_INTR_PI_DEBUG) |
        OS_INTR_MASK(OS_INTR_PI_HSP) | OS_INTR_MASK(OS_INTR_PI_ACR));

    __OSSetExceptionHandler(OS_ERR_EXT_INTERRUPT, ExternalInterruptHandler);
}

static u32 SetInterruptMask(u32 type, u32 mask) {
    u32 miMask;
    u32 dspMask;
    u32 aiMask;
    u32 exi0Mask, exi1Mask, exi2Mask;
    u32 piMask;

    switch (__cntlzw(type)) {
    /**
     * MEM interrupts
     */
    case OS_INTR_MEM_0:
    case OS_INTR_MEM_1:
    case OS_INTR_MEM_2:
    case OS_INTR_MEM_3:
    case OS_INTR_MEM_ADDRESS:
        miMask = 0;

        if (!(mask & OS_INTR_MASK(OS_INTR_MEM_0))) {
            miMask |= MI_INTMR_MEM0;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_MEM_1))) {
            miMask |= MI_INTMR_MEM1;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_MEM_2))) {
            miMask |= MI_INTMR_MEM2;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_MEM_3))) {
            miMask |= MI_INTMR_MEM3;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_MEM_ADDRESS))) {
            miMask |= MI_INTMR_ADDR;
        }

        MI_HW_REGS[MI_INTMR] = miMask;
        return type &
               ~(OS_INTR_MASK(OS_INTR_MEM_0) | OS_INTR_MASK(OS_INTR_MEM_1) |
                 OS_INTR_MASK(OS_INTR_MEM_2) | OS_INTR_MASK(OS_INTR_MEM_3) |
                 OS_INTR_MASK(OS_INTR_MEM_ADDRESS));
    /**
     * DSP interrupts
     */
    case OS_INTR_DSP_AI:
    case OS_INTR_DSP_ARAM:
    case OS_INTR_DSP_DSP:
        dspMask = DSP_HW_REGS[DSP_CSR];
        dspMask &= ~(DSP_CSR_AIDINT | DSP_CSR_AIDINTMSK | DSP_CSR_ARINT |
                     DSP_CSR_ARINTMSK | DSP_CSR_DSPINT | DSP_CSR_DSPINTMSK);

        if (!(mask & OS_INTR_MASK(OS_INTR_DSP_AI))) {
            dspMask |= DSP_CSR_AIDINTMSK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_DSP_ARAM))) {
            dspMask |= DSP_CSR_ARINTMSK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_DSP_DSP))) {
            dspMask |= DSP_CSR_DSPINTMSK;
        }

        DSP_HW_REGS[DSP_CSR] = dspMask;
        return type &
               ~(OS_INTR_MASK(OS_INTR_DSP_AI) | OS_INTR_MASK(OS_INTR_DSP_ARAM) |
                 OS_INTR_MASK(OS_INTR_DSP_DSP));
    /**
     * AI interrupts
     */
    case OS_INTR_AI_AI:
        aiMask = AI_HW_REGS[AI_AICR];
        aiMask &= ~(AI_AICR_AIINTMSK | AI_AICR_AIINT | AI_AICR_SCRESET);

        if (!(mask & OS_INTR_MASK(OS_INTR_AI_AI))) {
            aiMask |= AI_AICR_AIINTMSK;
        }

        AI_HW_REGS[AI_AICR] = aiMask;
        return type & ~OS_INTR_MASK(OS_INTR_AI_AI);
    /**
     * EXI interrupts (Channel 0)
     */
    case OS_INTR_EXI_0_EXI:
    case OS_INTR_EXI_0_TC:
    case OS_INTR_EXI_0_EXT:
        exi0Mask = EXI_CHAN_PARAMS[EXI_CHAN_0].cpr;
        exi0Mask &= ~(EXI_CPR_EXIINTMASK | EXI_CPR_EXIINT | EXI_CPR_TCINTMASK |
                      EXI_CPR_TCINT | EXI_CPR_EXTINTMASK | EXI_CPR_EXTINT |
                      EXI_CPR_ROMDIS);

        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_0_EXI))) {
            exi0Mask |= EXI_CPR_EXIINTMASK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_0_TC))) {
            exi0Mask |= EXI_CPR_TCINTMASK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_0_EXT))) {
            exi0Mask |= EXI_CPR_EXTINTMASK;
        }

        EXI_CHAN_PARAMS[EXI_CHAN_0].cpr = exi0Mask;
        return type & ~(OS_INTR_MASK(OS_INTR_EXI_0_EXI) |
                        OS_INTR_MASK(OS_INTR_EXI_0_TC) |
                        OS_INTR_MASK(OS_INTR_EXI_0_EXT));
    /**
     * EXI interrupts (Channel 1)
     */
    case OS_INTR_EXI_1_EXI:
    case OS_INTR_EXI_1_TC:
    case OS_INTR_EXI_1_EXT:
        exi1Mask = EXI_CHAN_PARAMS[EXI_CHAN_1].cpr;
        exi1Mask &= ~(EXI_CPR_EXIINTMASK | EXI_CPR_EXIINT | EXI_CPR_TCINTMASK |
                      EXI_CPR_TCINT | EXI_CPR_EXTINTMASK | EXI_CPR_EXTINT);

        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_1_EXI))) {
            exi1Mask |= EXI_CPR_EXIINTMASK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_1_TC))) {
            exi1Mask |= EXI_CPR_TCINTMASK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_1_EXT))) {
            exi1Mask |= EXI_CPR_EXTINTMASK;
        }

        EXI_CHAN_PARAMS[EXI_CHAN_1].cpr = exi1Mask;
        return type & ~(OS_INTR_MASK(OS_INTR_EXI_1_EXI) |
                        OS_INTR_MASK(OS_INTR_EXI_1_TC) |
                        OS_INTR_MASK(OS_INTR_EXI_1_EXT));
    /**
     * EXI interrupts (Channel 2)
     */
    case OS_INTR_EXI_2_EXI:
    case OS_INTR_EXI_2_TC:
        exi2Mask = EXI_CHAN_PARAMS[EXI_CHAN_2].cpr;
        exi2Mask &= ~(EXI_CPR_EXIINTMASK | EXI_CPR_EXIINT | EXI_CPR_TCINTMASK |
                      EXI_CPR_TCINT);

        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_2_EXI))) {
            exi2Mask |= EXI_CPR_EXIINTMASK;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_EXI_2_TC))) {
            exi2Mask |= EXI_CPR_TCINTMASK;
        }

        EXI_CHAN_PARAMS[EXI_CHAN_2].cpr = exi2Mask;
        return type & ~(OS_INTR_MASK(OS_INTR_EXI_2_EXI) |
                        OS_INTR_MASK(OS_INTR_EXI_2_TC));
    /**
     * PI interrupts
     */
    case OS_INTR_PI_CP:
    case OS_INTR_PI_PE_TOKEN:
    case OS_INTR_PI_PE_FINISH:
    case OS_INTR_PI_SI:
    case OS_INTR_PI_DI:
    case OS_INTR_PI_RSW:
    case OS_INTR_PI_ERROR:
    case OS_INTR_PI_VI:
    case OS_INTR_PI_DEBUG:
    case OS_INTR_PI_HSP:
    case OS_INTR_PI_ACR:
        piMask = PI_INTMR_EXI | PI_INTMR_AI | PI_INTMR_DSP | PI_INTMR_MEM;

        if (!(mask & OS_INTR_MASK(OS_INTR_PI_CP))) {
            piMask |= PI_INTMR_CP;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_SI))) {
            piMask |= PI_INTMR_SI;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_DI))) {
            piMask |= PI_INTMR_DI;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_RSW))) {
            piMask |= PI_INTMR_RSW;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_ERROR))) {
            piMask |= PI_INTMR_ERROR;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_VI))) {
            piMask |= PI_INTMR_VI;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_DEBUG))) {
            piMask |= PI_INTMR_DEBUG;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_PE_TOKEN))) {
            piMask |= PI_INTMR_PE_TOKEN;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_PE_FINISH))) {
            piMask |= PI_INTMR_PE_FINISH;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_HSP))) {
            piMask |= PI_INTMR_HSP;
        }
        if (!(mask & OS_INTR_MASK(OS_INTR_PI_ACR))) {
            piMask |= PI_INTMR_ACR;
        }

        PI_HW_REGS[PI_INTMR] = piMask;
        return type &
               ~(OS_INTR_MASK(OS_INTR_PI_CP) |
                 OS_INTR_MASK(OS_INTR_PI_PE_TOKEN) |
                 OS_INTR_MASK(OS_INTR_PI_PE_FINISH) |
                 OS_INTR_MASK(OS_INTR_PI_SI) | OS_INTR_MASK(OS_INTR_PI_DI) |
                 OS_INTR_MASK(OS_INTR_PI_RSW) | OS_INTR_MASK(OS_INTR_PI_ERROR) |
                 OS_INTR_MASK(OS_INTR_PI_VI) | OS_INTR_MASK(OS_INTR_PI_DEBUG) |
                 OS_INTR_MASK(OS_INTR_PI_HSP) | OS_INTR_MASK(OS_INTR_PI_ACR));
    default:
        return type;
    }
}

u32 __OSMaskInterrupts(u32 userMask) {
    BOOL enabled = OSDisableInterrupts();
    u32 prevMask = *(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK);
    u32 currMask = *(u32*)OSPhysicalToCached(OS_PHYS_CURRENT_INTR_MASK);

    u32 workMask = userMask & ~(prevMask | currMask);
    userMask = prevMask | userMask;
    *(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK) = userMask;

    while (workMask != 0) {
        workMask = SetInterruptMask(workMask, userMask | currMask);
    }

    OSRestoreInterrupts(enabled);
    return prevMask;
}

u32 __OSUnmaskInterrupts(u32 userMask) {
    BOOL enabled = OSDisableInterrupts();
    u32 prevMask = *(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK);
    u32 currMask = *(u32*)OSPhysicalToCached(OS_PHYS_CURRENT_INTR_MASK);

    u32 workMask = userMask & (prevMask | currMask);
    userMask = prevMask & ~userMask;
    *(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK) = userMask;

    while (workMask != 0) {
        workMask = SetInterruptMask(workMask, userMask | currMask);
    }

    OSRestoreInterrupts(enabled);
    return prevMask;
}

void __OSDispatchInterrupt(u8 intr, OSContext* ctx) {
    u32 intsr;
    u32 mask, newMask;
    u32 miCause;
    u32 dspCause;
    u32 exi0Cause, exi1Cause, exi2Cause;
    u32 piMask;

    intsr = PI_HW_REGS[PI_INTSR];
    intsr &= ~PI_INTSR_RSWST;

    piMask = PI_HW_REGS[PI_INTMR];
    if (intsr == 0 || !(intsr & piMask)) {
        OSLoadContext(ctx);
    }

    mask = 0;
    newMask = 0;

    /**
     * MEM interrupts
     */
    if (intsr & PI_INTMR_MEM) {
        miCause = MI_HW_REGS[MI_INTSR];
        if (miCause & MI_INTSR_MEM0) {
            mask |= OS_INTR_MASK(OS_INTR_MEM_0);
        }
        if (miCause & MI_INTSR_MEM1) {
            mask |= OS_INTR_MASK(OS_INTR_MEM_1);
        }
        if (miCause & MI_INTSR_MEM2) {
            mask |= OS_INTR_MASK(OS_INTR_MEM_2);
        }
        if (miCause & MI_INTSR_MEM3) {
            mask |= OS_INTR_MASK(OS_INTR_MEM_3);
        }
        if (miCause & MI_INTSR_ADDR) {
            mask |= OS_INTR_MASK(OS_INTR_MEM_ADDRESS);
        }
    }

    /**
     * DSP interrupts
     */
    if (intsr & PI_INTSR_DSP) {
        dspCause = DSP_HW_REGS[DSP_CSR];
        if (dspCause & DSP_CSR_AIDINT) {
            mask |= OS_INTR_MASK(OS_INTR_DSP_AI);
        }
        if (dspCause & DSP_CSR_ARINT) {
            mask |= OS_INTR_MASK(OS_INTR_DSP_ARAM);
        }
        if (dspCause & DSP_CSR_DSPINT) {
            mask |= OS_INTR_MASK(OS_INTR_DSP_DSP);
        }
    }

    /**
     * AI interrupts
     */
    if ((intsr & PI_INTSR_AI) && (AI_HW_REGS[AI_AICR] & AI_AICR_AIINT)) {
        mask |= OS_INTR_MASK(OS_INTR_AI_AI);
    }

    /**
     * EXI interrupts
     */
    if (intsr & PI_INTSR_EXI) {
        exi0Cause = EXI_CHAN_PARAMS[EXI_CHAN_0].cpr;
        if (exi0Cause & EXI_CPR_EXIINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_0_EXI);
        }
        if (exi0Cause & EXI_CPR_TCINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_0_TC);
        }
        if (exi0Cause & EXI_CPR_EXTINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_0_EXT);
        }

        exi1Cause = EXI_CHAN_PARAMS[EXI_CHAN_1].cpr;
        if (exi1Cause & EXI_CPR_EXIINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_1_EXI);
        }
        if (exi1Cause & EXI_CPR_TCINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_1_TC);
        }
        if (exi1Cause & EXI_CPR_EXTINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_1_EXT);
        }

        exi2Cause = EXI_CHAN_PARAMS[EXI_CHAN_2].cpr;
        if (exi2Cause & EXI_CPR_EXIINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_2_EXI);
        }
        if (exi2Cause & EXI_CPR_TCINT) {
            mask |= OS_INTR_MASK(OS_INTR_EXI_2_TC);
        }
    }

    /**
     * PI interrupts
     */
    if (intsr & PI_INTSR_HSP) {
        mask |= OS_INTR_MASK(OS_INTR_PI_HSP);
    }
    if (intsr & PI_INTSR_DEBUG) {
        mask |= OS_INTR_MASK(OS_INTR_PI_DEBUG);
    }
    if (intsr & PI_INTSR_PE_FINISH) {
        mask |= OS_INTR_MASK(OS_INTR_PI_PE_FINISH);
    }
    if (intsr & PI_INTSR_PE_TOKEN) {
        mask |= OS_INTR_MASK(OS_INTR_PI_PE_TOKEN);
    }
    if (intsr & PI_INTSR_VI) {
        mask |= OS_INTR_MASK(OS_INTR_PI_VI);
    }
    if (intsr & PI_INTSR_SI) {
        mask |= OS_INTR_MASK(OS_INTR_PI_SI);
    }
    if (intsr & PI_INTSR_DI) {
        mask |= OS_INTR_MASK(OS_INTR_PI_DI);
    }
    if (intsr & PI_INTSR_RSW) {
        mask |= OS_INTR_MASK(OS_INTR_PI_RSW);
    }
    if (intsr & PI_INTSR_CP) {
        mask |= OS_INTR_MASK(OS_INTR_PI_CP);
    }
    if (intsr & PI_INTSR_ERROR) {
        mask |= OS_INTR_MASK(OS_INTR_PI_ERROR);
    }
    if (intsr & PI_INTSR_ACR) {
        mask |= OS_INTR_MASK(OS_INTR_PI_ACR);
    }

    newMask = mask & ~(*(u32*)OSPhysicalToCached(OS_PHYS_PREV_INTR_MASK) |
                       *(u32*)OSPhysicalToCached(OS_PHYS_CURRENT_INTR_MASK));

    if (newMask != 0) {
        s16 type;
        u32* pPrio;
        OSInterruptHandler handler;

        for (pPrio = InterruptPrioTable; TRUE; pPrio++) {
            if (newMask & *pPrio) {
                type = __cntlzw(newMask & *pPrio);
                break;
            }
        }

        handler = __OSGetInterruptHandler(type);
        if (handler != NULL) {
            if (type > OS_INTR_MEM_ADDRESS) {
                __OSLastInterrupt = type;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = ctx->srr0;
            }

            OSDisableScheduler();
            handler(type, ctx);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(ctx);
        }
    }

    OSLoadContext(ctx);
}

static asm void ExternalInterruptHandler(register u8 type,
                                         register OSContext* ctx) {
    // clang-format off
    nofralloc

    stw r0, ctx->gprs[0]
    stw r1, ctx->gprs[1]
    stw r2, ctx->gprs[2]
    stmw r6, ctx->gprs[6]

    mfspr r0, GQR1
    stw r0, ctx->gqrs[1]
    mfspr r0, GQR2
    stw r0, ctx->gqrs[2]
    mfspr r0, GQR3
    stw r0, ctx->gqrs[3]
    mfspr r0, GQR4
    stw r0, ctx->gqrs[4]
    mfspr r0, GQR5
    stw r0, ctx->gqrs[5]
    mfspr r0, GQR6
    stw r0, ctx->gqrs[6]
    mfspr r0, GQR7
    stw r0, ctx->gqrs[7]

    stwu r1, -8(r1)
    b __OSDispatchInterrupt
    // clang-format on
}
