#include <revolution/AX.h>
#include <revolution/OS.h>

// Compression parameters.
// Later versions of AX have these as static vars
#define THRESHOLD 32768
#define RELEASE_FRAMES 10

// Space is allocated for two commands lists
#define LIST_MAX 2

#define LIST_WRITE_16(x)                                                       \
    do {                                                                       \
        __AXWriteToCommandList((x));                                           \
    } while (0)

#define LIST_WRITE_32(x)                                                       \
    do {                                                                       \
        __AXWriteToCommandList((x) >> 16);                                     \
        __AXWriteToCommandList((x));                                           \
    } while (0)

/**
 * Command list opcodes (from Dolphin Emulator)
 */
typedef enum {
    COMMAND_SETUP,
    COMMAND_ADD_TO_LR,
    COMMAND_SUB_TO_LR,
    COMMAND_ADD_SUB_TO_LR,
    COMMAND_PROCESS,
    COMMAND_MIX_AUXA,
    COMMAND_MIX_AUXB,
    COMMAND_MIX_AUXC,
    COMMAND_UPL_AUXA_MIX_LRSC,
    COMMAND_UPL_AUXB_MIX_LRSC,
    COMMAND_COMPRESSOR,
    COMMAND_OUTPUT,
    COMMAND_OUTPUT_DPL2,
    COMMAND_WM_OUTPUT,
    COMMAND_END
};

static u32 __AXCommandListPosition;

static u16* __AXClWrite;
u32 __AXClMode;

static u32 __AXCommandListCycles;
static u8 __AXCommandList[AX_CL_SIZE * LIST_MAX];

static BOOL __AXCompressor;

static volatile u16 __AXMasterVolume;
static u16 __AXAuxAVolume;
static u16 __AXAuxBVolume;
static u16 __AXAuxCVolume;

u32 __AXGetCommandListCycles(void) {
    return __AXCommandListCycles;
}

void* __AXGetCommandListAddress(void) {
    void* list = __AXCommandList + __AXCommandListPosition * AX_CL_SIZE;

    __AXCommandListPosition++;
    __AXCommandListPosition %= LIST_MAX;
    __AXClWrite =
        (u16*)(__AXCommandList + __AXCommandListPosition * AX_CL_SIZE);

    return list;
}

void __AXWriteToCommandList(u16 cmd) {
    *__AXClWrite = cmd;
    __AXClWrite++;
}

void __AXNextFrame(void* surround, void* lr, void* rmt) {
    void* imm;
    void* backup;

    __AXCommandListCycles = 7811;
    backup = __AXClWrite;
    imm = __AXGetStudio();

    LIST_WRITE_16(COMMAND_SETUP);
    LIST_WRITE_32((uintptr_t)imm);
    __AXCommandListCycles += 4126;

    switch (__AXClMode) {
    case AX_OUTPUT_STEREO:
        LIST_WRITE_16(COMMAND_ADD_TO_LR);
        LIST_WRITE_32((uintptr_t)surround);
        __AXCommandListCycles += 733;
        break;
    case AX_OUTPUT_SURROUND:
        LIST_WRITE_16(COMMAND_SUB_TO_LR);
        LIST_WRITE_32((uintptr_t)surround);
        __AXCommandListCycles += 829;
        break;
    case AX_OUTPUT_DPL2:
        LIST_WRITE_16(COMMAND_ADD_SUB_TO_LR);
        LIST_WRITE_32((uintptr_t)surround);
        __AXCommandListCycles += 925;
        break;
    }

    imm = __AXGetPBs();
    LIST_WRITE_16(COMMAND_PROCESS);
    LIST_WRITE_32((uintptr_t)imm);

    if (__AXClMode == AX_OUTPUT_DPL2) {
        __AXGetAuxAInput(&imm);
        if (imm != NULL) {
            LIST_WRITE_16(COMMAND_UPL_AUXA_MIX_LRSC);
            LIST_WRITE_16(__AXAuxAVolume);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAInputDpl2(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAOutput(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAOutputDpl2R(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAOutputDpl2Ls(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAOutputDpl2Rs(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXCommandListCycles += 3036;
        }

        __AXGetAuxBInput(&imm);
        if (imm != NULL) {
            LIST_WRITE_16(COMMAND_UPL_AUXB_MIX_LRSC);
            LIST_WRITE_16(__AXAuxBVolume);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBInputDpl2(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBOutput(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBOutputDpl2R(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBOutputDpl2Ls(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBOutputDpl2Rs(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXCommandListCycles += 3036;
        }
    } else {
        __AXGetAuxAInput(&imm);
        if (imm != NULL) {
            LIST_WRITE_16(COMMAND_MIX_AUXA);
            LIST_WRITE_16(__AXAuxAVolume);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxAOutput(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXCommandListCycles += 2235;
        }

        __AXGetAuxBInput(&imm);
        if (imm != NULL) {
            LIST_WRITE_16(COMMAND_MIX_AUXB);
            LIST_WRITE_16(__AXAuxBVolume);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxBOutput(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXCommandListCycles += 2235;
        }

        __AXGetAuxCInput(&imm);
        if (imm != NULL) {
            LIST_WRITE_16(COMMAND_MIX_AUXC);
            LIST_WRITE_16(__AXAuxCVolume);
            LIST_WRITE_32((uintptr_t)imm);

            __AXGetAuxCOutput(&imm);
            LIST_WRITE_32((uintptr_t)imm);

            __AXCommandListCycles += 2235;
        }
    }

    if (__AXCompressor) {
        LIST_WRITE_16(COMMAND_COMPRESSOR);
        LIST_WRITE_16(THRESHOLD);
        LIST_WRITE_16(RELEASE_FRAMES);
        LIST_WRITE_32((uintptr_t)__AXCompressorTable);
        __AXCommandListCycles += 1850;
    }

    LIST_WRITE_16(COMMAND_WM_OUTPUT);
    LIST_WRITE_32(((u32*)rmt)[0]);
    LIST_WRITE_32(((u32*)rmt)[1]);
    LIST_WRITE_32(((u32*)rmt)[2]);
    LIST_WRITE_32(((u32*)rmt)[3]);
    __AXCommandListCycles += 409;

    if (__AXClMode == AX_OUTPUT_DPL2) {
        LIST_WRITE_16(COMMAND_OUTPUT_DPL2);
        LIST_WRITE_16(__AXMasterVolume);
        LIST_WRITE_32((uintptr_t)surround);
        LIST_WRITE_32((uintptr_t)lr);
        __AXCommandListCycles += 1195;
    } else {
        LIST_WRITE_16(COMMAND_OUTPUT);
        LIST_WRITE_16(__AXMasterVolume);
        LIST_WRITE_32((uintptr_t)surround);
        LIST_WRITE_32((uintptr_t)lr);
        __AXCommandListCycles += 1172;
    }

    LIST_WRITE_16(COMMAND_END);
    __AXCommandListCycles += 30;

    DCFlushRange(backup, AX_CL_SIZE);
}

void __AXClInit(void) {
    __AXClMode = AX_OUTPUT_STEREO;
    __AXCommandListPosition = 0;
    __AXClWrite = (u16*)__AXCommandList;
    __AXCompressor = TRUE;

    __AXAuxCVolume = __AXAuxBVolume = __AXAuxAVolume = __AXMasterVolume =
        AX_MAX_VOLUME;
}

void AXSetMode(u32 mode) {
    __AXClMode = mode;
}

u32 AXGetMode(void) {
    return __AXClMode;
}

u16 AXGetAuxAReturnVolume(void) {
    return __AXAuxAVolume;
}

u16 AXGetAuxBReturnVolume(void) {
    return __AXAuxBVolume;
}

u16 AXGetAuxCReturnVolume(void) {
    return __AXAuxCVolume;
}

void AXSetMasterVolume(u16 volume) {
    if (volume > AX_MAX_VOLUME) {
        volume = AX_MAX_VOLUME;
    }

    __AXMasterVolume = volume;
}

void AXSetAuxAReturnVolume(u16 volume) {
    __AXAuxAVolume = volume;
}

void AXSetAuxBReturnVolume(u16 volume) {
    __AXAuxBVolume = volume;
}

void AXSetAuxCReturnVolume(u16 volume) {
    __AXAuxCVolume = volume;
}
