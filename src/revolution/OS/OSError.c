#include <revolution/BASE.h>
#include <revolution/DSP.h>
#include <revolution/OS.h>
#include <stdio.h>

OSErrorHandler __OSErrorTable[OS_ERR_MAX];
u32 __OSFpscrEnableBits =
    (FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE);

void OSReport(const char* msg, ...) {
    va_list list;
    va_start(list, msg);
    vprintf(msg, list);
    va_end(list);
}

void OSPanic(const char* file, int line, const char* msg, ...) {
    u32 depth;
    u32* sp;
    va_list list;

    OSDisableInterrupts();

    va_start(list, msg);
    vprintf(msg, list);
    va_end(list);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (depth = 0, sp = (u32*)OSGetStackPointer();
         sp != NULL && sp != (u32*)0xFFFFFFFF && depth++ < 16; sp = (u32*)*sp) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", sp, sp[0], sp[1]);
    }

    PPCHalt();
}

OSErrorHandler OSSetErrorHandler(u16 error, OSErrorHandler handler) {
    OSErrorHandler oldHandler;
    BOOL enabled = OSDisableInterrupts();

    oldHandler = __OSErrorTable[error];
    __OSErrorTable[error] = handler;

    if (error == OS_ERR_FP_EXCEPTION) {
        OSThread* thread;
        u32 msr;
        u32 fpscr;

        msr = PPCMfmsr();
        PPCMtmsr(msr | MSR_FP);
        fpscr = PPCMffpscr();

        if (handler != NULL) {
            int i;
            for (thread = OS_THREAD_QUEUE.head; thread != NULL;
                 thread = thread->nextActive) {
                thread->context.srr1 |= 0x900;

                if (!(thread->context.state & 0x1)) {
                    thread->context.state |= 0x1;

                    for (i = 0; i < 32; i++) {
                        *(u64*)&thread->context.fprs[i] = 0xFFFFFFFFFFFFFFFF;
                        *(u64*)&thread->context.psfs[i] = 0xFFFFFFFFFFFFFFFF;
                    }

                    thread->context.fpscr = FPSCR_NI;
                }
                thread->context.fpscr |=
                    __OSFpscrEnableBits &
                    (FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE);
                thread->context.fpscr &=
                    (FPSCR_FEX | FPSCR_VX | FPSCR_FR | FPSCR_FPRF |
                     FPSCR_UNK20 | FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE |
                     FPSCR_XE | FPSCR_NI | FPSCR_RN);
            }

            fpscr |= __OSFpscrEnableBits &
                     (FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE);
            msr |= (MSR_FE0 | MSR_FE1);
        } else {
            for (thread = OS_THREAD_QUEUE.head; thread != NULL;
                 thread = thread->nextActive) {
                thread->context.srr1 &= ~0x900;
                thread->context.fpscr &=
                    ~(FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE);
                thread->context.fpscr &=
                    (FPSCR_FEX | FPSCR_VX | FPSCR_FR | FPSCR_FPRF |
                     FPSCR_UNK20 | FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE |
                     FPSCR_XE | FPSCR_NI | FPSCR_RN);
            }

            fpscr &= ~(FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE);
            msr &= ~(MSR_FE0 | MSR_FE1);
        }

        PPCMtfpscr(fpscr & (FPSCR_FEX | FPSCR_VX | FPSCR_FR | FPSCR_FPRF |
                            FPSCR_UNK20 | FPSCR_VE | FPSCR_OE | FPSCR_UE |
                            FPSCR_ZE | FPSCR_XE | FPSCR_NI | FPSCR_RN));
        PPCMtmsr(msr);
    }

    OSRestoreInterrupts(enabled);
    return oldHandler;
}

void __OSUnhandledException(u8 error, OSContext* ctx, u32 dsisr, u32 dar) {
    s64 tb = OSGetTime();

    if (!(ctx->srr1 & 0x2)) {
        OSReport("Non-recoverable Exception %d", error);
    } else {
        if (error == OS_ERR_PROGRAM && ctx->srr1 & 0x100000 &&
            __OSErrorTable[OS_ERR_FP_EXCEPTION] != NULL) {
            u32 msr;
            u32 fpscr;

            error = OS_ERR_FP_EXCEPTION;

            msr = PPCMfmsr();
            PPCMtmsr(msr | MSR_FP);

            if (OS_CURRENT_FPU_CONTEXT != NULL) {
                OSSaveFPUContext(OS_CURRENT_FPU_CONTEXT);
            }

            fpscr = PPCMffpscr();
            PPCMtfpscr(fpscr & (FPSCR_FEX | FPSCR_VX | FPSCR_FR | FPSCR_FPRF |
                                FPSCR_UNK20 | FPSCR_VE | FPSCR_OE | FPSCR_UE |
                                FPSCR_ZE | FPSCR_XE | FPSCR_NI | FPSCR_RN));
            PPCMtmsr(msr);

            if (OS_CURRENT_FPU_CONTEXT == ctx) {
                OSDisableScheduler();
                __OSErrorTable[error](error, ctx, dsisr, dar);
                ctx->srr1 &= ~0x2000;
                OS_CURRENT_FPU_CONTEXT = NULL;
                ctx->fpscr &= (FPSCR_FEX | FPSCR_VX | FPSCR_FR | FPSCR_FPRF |
                               FPSCR_UNK20 | FPSCR_VE | FPSCR_OE | FPSCR_UE |
                               FPSCR_ZE | FPSCR_XE | FPSCR_NI | FPSCR_RN);
                OSEnableScheduler();
                __OSReschedule();
            } else {
                ctx->srr1 &= ~0x2000;
                OS_CURRENT_FPU_CONTEXT = NULL;
            }

            OSLoadContext(ctx);
        }

        if (__OSErrorTable[error] != NULL) {
            OSDisableScheduler();
            __OSErrorTable[error](error, ctx, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(ctx);
        }

        if (error == OS_ERR_DECREMENTER) {
            OSLoadContext(ctx);
        }

        OSReport("Unhandled Exception %d", error);
    }

    OSReport("\n");
    OSDumpContext(ctx);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", tb);
    switch (error) {
    case OS_ERR_DSI:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "invalid address 0x%x (read from DAR)\n",
                 ctx->srr0, dar);
        break;
    case OS_ERR_ISI:
        OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                 "(read from SRR0)\n",
                 ctx->srr0);
        break;
    case OS_ERR_ALIGNMENT:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "unaligned address 0x%x (read from DAR)\n",
                 ctx->srr0, dar);
        break;
    case OS_ERR_PROGRAM:
        OSReport("\nProgram exception : Possible illegal instruction/operation "
                 "at or around 0x%x (read from SRR0)\n",
                 ctx->srr0, dar);
        break;
    case OS_ERR_PROTECTION:
        OSReport("\n");
        OSReport("AI DMA Address =   0x%04x%04x\n",
                 DSP_HW_REGS[DSP_AI_DMA_START_H],
                 DSP_HW_REGS[DSP_AI_DMA_START_L]);
        OSReport("ARAM DMA Address = 0x%04x%04x\n",
                 DSP_HW_REGS[DSP_AR_DMA_MMADDR_H],
                 DSP_HW_REGS[DSP_AR_DMA_MMADDR_L]);
        OSReport("DI DMA Address =   0x%08x\n", OS_DI_DMA_ADDR);
        break;
    }

    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n",
             __OSLastInterrupt, __OSLastInterruptSrr0, __OSLastInterruptTime);
    PPCHalt();
}
