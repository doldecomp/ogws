#include <revolution/AI.h>
#include <revolution/DSP.h>
#include <revolution/OS.h>

const char* __AIVersion =
    "<< RVL_SDK - AI \trelease build: Nov 30 2006 03:26:11 (0x4199_60831) >>";

static AIDMACallback __AID_Callback;

static void* __CallbackStack;
static void* __OldStack;

static s64 bound_32KHz;
static s64 bound_48KHz;

static s64 min_wait;
static s64 max_wait;
static s64 buffer;

static BOOL __AID_Active;
static BOOL __AI_init_flag;

static void __AICallbackStackSwitch(AIDMACallback callback);
static void __AI_SRC_INIT(void);

AIDMACallback AIRegisterDMACallback(AIDMACallback callback) {
    BOOL enabled;
    AIDMACallback old;

    old = __AID_Callback;
    enabled = OSDisableInterrupts();

    __AID_Callback = callback;

    OSRestoreInterrupts(enabled);
    return old;
}

void AIInitDMA(void* buffer, u32 length) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    DSP_HW_REGS[DSP_AI_DMA_START_H] =
        (DSP_HW_REGS[DSP_AI_DMA_START_H] & ~0x1FFF) |
        (((uintptr_t)buffer) >> 16 & 0xFFFF);

    DSP_HW_REGS[DSP_AI_DMA_START_L] =
        (DSP_HW_REGS[DSP_AI_DMA_START_L] & ~0xFFE0) |
        (((uintptr_t)buffer) & 0xFFFF);

    DSP_HW_REGS[DSP_AI_DMA_CSR] =
        (DSP_HW_REGS[DSP_AI_DMA_CSR] & ~0x7FFF) | ((length / 32) & 0xFFFF);

    OSRestoreInterrupts(enabled);
}

void AIStartDMA(void) {
    DSP_HW_REGS[DSP_AI_DMA_CSR] |= DSP_AI_DMA_CSR_PLAY;
}

u32 AIGetDMABytesLeft(void) {
    return (DSP_HW_REGS[DSP_AI_DMA_BYTES_LEFT] & 0x7FFF) * 32;
}

void AISetDSPSampleRate(u32 rate) {
    BOOL enabled;

    if (rate != AIGetDSPSampleRate()) {
        AI_HW_REGS[AI_AICR] &= ~AI_AICR_SAMPLERATE;

        if (rate == AI_DSP_32KHZ) {
            enabled = OSDisableInterrupts();

            __AI_SRC_INIT();
            AI_HW_REGS[AI_AICR] |= AI_AICR_SAMPLERATE;

            OSRestoreInterrupts(enabled);
        }
    }
}

u32 AIGetDSPSampleRate(void) {
    return ((AI_HW_REGS[AI_AICR] & AI_AICR_SAMPLERATE) >> 6) ^ 1;
}

void AIInit(void* stack) {
    if (__AI_init_flag != TRUE) {
        OSRegisterVersion(__AIVersion);

        bound_32KHz = OS_NSEC_TO_TICKS(31524);
        bound_48KHz = OS_NSEC_TO_TICKS(42024);
        min_wait = OS_NSEC_TO_TICKS(42000);
        max_wait = OS_NSEC_TO_TICKS(63000);
        buffer = OS_NSEC_TO_TICKS(3000);

        AI_HW_REGS[AI_AICR] &=
            ~(AI_AICR_PSTAT | AI_AICR_AIINTMSK | AI_AICR_AIINTVLD);

        AI_HW_REGS[AI_AIVR] = 0;
        AI_HW_REGS[AI_AIIT] = 0;

        AI_HW_REGS[AI_AICR] =
            (AI_HW_REGS[AI_AICR] & ~AI_AICR_SCRESET) | AI_AICR_SCRESET;

        AISetDSPSampleRate(AI_DSP_32KHZ);

        __AID_Callback = NULL;
        __CallbackStack = stack;

        __OSSetInterruptHandler(OS_INTR_DSP_AI, __AIDHandler);
        __OSUnmaskInterrupts(OS_INTR_MASK(OS_INTR_DSP_AI));

        __AI_init_flag = TRUE;
    }
}

void __AIDHandler(s16 intr, OSContext* ctx) {
#pragma unused(intr)

    OSContext tempCtx;

    DSP_HW_REGS[DSP_CSR] =
        (DSP_HW_REGS[DSP_CSR] & ~(DSP_CSR_ARINT | DSP_CSR_DSPINT)) |
        DSP_CSR_AIDINT;

    OSClearContext(&tempCtx);
    OSSetCurrentContext(&tempCtx);

    if (__AID_Callback != NULL && !__AID_Active) {
        __AID_Active = TRUE;

        if (__CallbackStack != NULL) {
            __AICallbackStackSwitch(__AID_Callback);
        } else {
            __AID_Callback();
        }

        __AID_Active = FALSE;
    }

    OSClearContext(&tempCtx);
    OSSetCurrentContext(ctx);
}

static asm void __AICallbackStackSwitch(register AIDMACallback callback) {
    // clang-format off

    mr r31, callback

    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    stw r1, 0(r5)

    lis r5, __CallbackStack@ha
    addi r5, r5, __CallbackStack@l
    lwz r1, 0(r5)
        
    subi r1, r1, 0x8
    mtlr r31
    blrl
    
    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    lwz r1, 0(r5)

    frfree
    blr

    // clang-format on
}

static void __AI_SRC_INIT(void) {
    s64 start = 0;
    s64 end = 0;
    BOOL exit = FALSE;
    s64 diff = 0;
    s64 wait = 0;
    u32 samples = 0;

    while (!exit) {
        AI_HW_REGS[AI_AICR] =
            (AI_HW_REGS[AI_AICR] & ~AI_AICR_SCRESET) | AI_AICR_SCRESET;

        AI_HW_REGS[AI_AICR] &= ~AI_AICR_AFR;

        AI_HW_REGS[AI_AICR] =
            (AI_HW_REGS[AI_AICR] & ~AI_AICR_PSTAT) | AI_AICR_PSTAT;

        // Waiting for one sample?
        samples = AI_HW_REGS[AI_AISCNT] & ~0x80000000;
        while (samples == (AI_HW_REGS[AI_AISCNT] & ~0x80000000)) {
            ;
        }

        start = OSGetTime();

        AI_HW_REGS[AI_AICR] =
            (AI_HW_REGS[AI_AICR] & ~AI_AICR_AFR) | AI_AICR_AFR;

        AI_HW_REGS[AI_AICR] =
            (AI_HW_REGS[AI_AICR] & ~AI_AICR_PSTAT) | AI_AICR_PSTAT;

        // Waiting for one sample?
        samples = AI_HW_REGS[AI_AISCNT] & ~0x80000000;
        while (samples == (AI_HW_REGS[AI_AISCNT] & ~0x80000000)) {
            ;
        }

        end = OSGetTime();
        diff = end - start;

        AI_HW_REGS[AI_AICR] &= ~AI_AICR_AFR;
        AI_HW_REGS[AI_AICR] &= ~AI_AICR_PSTAT;

        if (diff < bound_32KHz - buffer) {
            wait = min_wait;
            exit = TRUE;
        } else if (diff >= bound_32KHz + buffer &&
                   diff < bound_48KHz - buffer) {
            wait = max_wait;
            exit = TRUE;
        } else {
            exit = FALSE;
        }
    }

    while (end + wait > OSGetTime()) {
        ;
    }
}
