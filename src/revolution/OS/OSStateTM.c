#include <revolution/IPC.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

typedef enum {
    STM_IOCTL_REG_STM_EVENT = 0x1000,
    STM_IOCTL_HOT_RESET = 0x2001,
    STM_IOCTL_SHUTDOWN_TO_SBY = 0x2003,
    STM_IOCTL_UNREG_STM_EVENT = 0x3002,
    STM_IOCTL_SET_VI_DIM = 0x5001,
    STM_IOCTL_SET_IDLE_LED_MODE = 0x6002,
} OSStateTMIoctl;

static u8 StmEhInBuf[32] ALIGN(32);
static u8 StmEhOutBuf[32] ALIGN(32);

static u8 StmImInBuf[32] ALIGN(32);
static u8 StmImOutBuf[32] ALIGN(32);

static u8 StmVdInBuf[32] ALIGN(32);
static u8 StmVdOutBuf[32] ALIGN(32);

static OSStateCallback ResetCallback;
static OSStateCallback PowerCallback;

static BOOL StmVdInUse;

static BOOL StmEhRegistered;
static BOOL StmEhDesc;

static BOOL StmImDesc;

static BOOL StmReady;
static BOOL ResetDown;

static s32 AccessVIDimRegs(void);
static s32 __OSVIDimReplyHandler(s32 result, void* arg);
static void __OSRegisterStateEvent(void);
static void __OSDefaultResetCallback(void);
static void __OSDefaultPowerCallback(void);
static s32 __OSStateEventHandler(s32 result, void* arg);
static void LockUp(void);

OSStateCallback OSSetResetCallback(OSStateCallback callback) {
    BOOL enabled;
    OSStateCallback old;

    enabled = OSDisableInterrupts();

    old = ResetCallback;
    ResetCallback = callback;

    if (!StmEhRegistered) {
        __OSRegisterStateEvent();
    }

    OSRestoreInterrupts(enabled);
    return old;
}

OSStateCallback OSSetPowerCallback(OSStateCallback callback) {
    BOOL enabled;
    OSStateCallback old;

    enabled = OSDisableInterrupts();

    old = PowerCallback;
    PowerCallback = callback;

    if (!StmEhRegistered) {
        __OSRegisterStateEvent();
    }

    OSRestoreInterrupts(enabled);
    return old;
}

BOOL __OSInitSTM(void) {
    BOOL success;

    PowerCallback = __OSDefaultPowerCallback;
    ResetCallback = __OSDefaultResetCallback;
    ResetDown = FALSE;

    if (StmReady) {
        return TRUE;
    }

    StmVdInUse = FALSE;
    StmImDesc = IOS_Open("/dev/stm/immediate", IPC_OPEN_NONE);
    if (StmImDesc < 0) {
        StmReady = FALSE;
        success = FALSE;
        goto exit;
    }

    StmEhDesc = IOS_Open("/dev/stm/eventhook", IPC_OPEN_NONE);
    if (StmEhDesc < 0) {
        StmReady = FALSE;
        success = FALSE;
        goto exit;
    }

    __OSRegisterStateEvent();
    StmReady = TRUE;
    success = TRUE;

exit:
    return success;
}

void __OSShutdownToSBY(void) {
#define in_args ((u32*)StmImInBuf)

    VI_HW_REGS[VI_DCR] = 0;

    // clang-format off
#line 276
    OS_ASSERT(StmReady, "Error: The firmware doesn't support shutdown feature.\n");
    // clang-format on

    in_args[0] = 0;
    IOS_Ioctl(StmImDesc, STM_IOCTL_SHUTDOWN_TO_SBY, StmImInBuf,
              sizeof(StmImInBuf), StmImOutBuf, sizeof(StmImOutBuf));
    LockUp();

#undef in_args
}

void __OSHotReset(void) {
    VI_HW_REGS[VI_DCR] = 0;

    // clang-format off
#line 340
    OS_ASSERT(StmReady, "Error: The firmware doesn't support reboot feature.\n");
    // clang-format on

    IOS_Ioctl(StmImDesc, STM_IOCTL_HOT_RESET, StmImInBuf, sizeof(StmImInBuf),
              StmImOutBuf, sizeof(StmImOutBuf));
    LockUp();
}

BOOL __OSGetResetButtonStateRaw(void) {
    return (!(PI_HW_REGS[PI_INTSR] & PI_INTSR_RSWST)) ? TRUE : FALSE;
}

s32 __OSSetVIForceDimming(u32 arg0, u32 arg1, u32 arg2) {
#define in_args ((u32*)StmVdInBuf)

    BOOL enabled;

    if (!StmReady) {
        return -10;
    }

    enabled = OSDisableInterrupts();

    if (StmVdInUse) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    StmVdInUse = TRUE;
    OSRestoreInterrupts(enabled);

    // Screen brightness
    in_args[0] = arg1 << 3 | arg2 | arg0 << 7;

    in_args[1] = 0;
    in_args[2] = 0;
    in_args[3] = 0;
    in_args[4] = 0;

    in_args[5] = 0xFFFFFFFF;
    in_args[6] = 0xFFFF0000;

    in_args[7] = 0;

    return AccessVIDimRegs();

#undef in_args
}

s32 __OSSetIdleLEDMode(u32 mode) {
#define in_args ((u32*)StmImInBuf)

    if (!StmReady) {
        return -6;
    }

    in_args[0] = mode;

    return IOS_Ioctl(StmImDesc, STM_IOCTL_SET_IDLE_LED_MODE, StmImInBuf,
                     sizeof(StmImInBuf), StmImOutBuf, sizeof(StmImOutBuf));

#undef in_args
}

s32 __OSUnRegisterStateEvent(void) {
    IPCResult result;

    if (!StmEhRegistered) {
        return 0;
    }

    if (!StmReady) {
        return -6;
    }

    result = IOS_Ioctl(StmImDesc, STM_IOCTL_UNREG_STM_EVENT, StmImInBuf,
                       sizeof(StmImInBuf), StmImOutBuf, sizeof(StmImOutBuf));
    if (result == IPC_RESULT_OK) {
        StmEhRegistered = FALSE;
    }

    return result;
}

static s32 AccessVIDimRegs(void) {
    IPCResult result = IOS_IoctlAsync(
        StmImDesc, STM_IOCTL_SET_VI_DIM, StmVdInBuf, sizeof(StmVdInBuf),
        StmVdOutBuf, sizeof(StmVdOutBuf), __OSVIDimReplyHandler, NULL);
    return result != IPC_RESULT_OK ? result : 1;
}

static s32 __OSVIDimReplyHandler(s32 result, void* arg) {
#pragma unused(result)
#pragma unused(arg)

    StmVdInUse = FALSE;
    return IPC_RESULT_OK;
}

static void __OSRegisterStateEvent(void) {
    BOOL enabled = OSDisableInterrupts();

    if (IOS_IoctlAsync(StmEhDesc, STM_IOCTL_REG_STM_EVENT, StmEhInBuf,
                       sizeof(StmEhInBuf), StmEhOutBuf, sizeof(StmEhOutBuf),
                       __OSStateEventHandler, NULL) == IPC_RESULT_OK) {
        StmEhRegistered = TRUE;
    } else {
        StmEhRegistered = FALSE;
    }

    OSRestoreInterrupts(enabled);
}

static void __OSDefaultResetCallback(void) {}

static void __OSDefaultPowerCallback(void) {}

static s32 __OSStateEventHandler(s32 result, void* arg) {
#pragma unused(result)
#pragma unused(arg)

#define out_args ((u32*)StmEhOutBuf)

    BOOL enabled;
    OSStateCallback callback;

    // clang-format off
#line 748
    OS_ASSERT(result == IPC_RESULT_OK, "Error on STM state event handler\n");
    // clang-format on

    StmEhRegistered = FALSE;

    if (out_args[0] == 0x20000) {
        if (__OSGetResetButtonStateRaw()) {
            enabled = OSDisableInterrupts();

            callback = ResetCallback;
            ResetDown = TRUE;
            ResetCallback = __OSDefaultResetCallback;
            callback();

            OSRestoreInterrupts(enabled);
        }
        __OSRegisterStateEvent();
    }

    if (out_args[0] == 0x800) {
        enabled = OSDisableInterrupts();

        callback = PowerCallback;
        PowerCallback = __OSDefaultPowerCallback;
        callback();

        OSRestoreInterrupts(enabled);
    }

    return IPC_RESULT_OK;

#undef out_args
}

static void LockUp(void) {
    OSDisableInterrupts();
    ICFlashInvalidate();

    while (TRUE) {
        ;
    }
}
