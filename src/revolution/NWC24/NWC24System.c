#include <revolution/NWC24.h>
#include <revolution/OS.h>
#include <revolution/SC.h>

#define SHUTDOWN_RETRY_MAX 5

typedef enum {
    NWC24_IOCTL_SHUTDOWN = 40,
} NWC24Ioctl;

static s32 nwc24ShtFd = -1;
static s32 nwc24ShtRetryRest = 0;

static OSShutdownFunctionInfo ShutdownFuncInfo;

NWC24Err NWC24EnableLedNotification(BOOL enable) {
    SCIdleModeInfo idleMode;
    u32 status;
    u32 led = 0;

    if (enable) {
        do {
            status = SCCheckStatus();

            if (status == SC_STATUS_FATAL) {
                return NWC24_ERR_FATAL;
            }
        } while (status == SC_STATUS_BUSY);

        SCGetIdleMode(&idleMode);
        led = idleMode.slotLight;
    }

    __OSSetIdleLEDMode(led);
    return NWC24_OK;
}

NWC24Err NWC24iPrepareShutdown(void) {
    NWC24Err result = NWC24_OK;

    NWC24iRegister();

    ShutdownFuncInfo.func = NWC24Shutdown;
    ShutdownFuncInfo.prio = 110;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);

    if (nwc24ShtFd < 0) {
        result = NWC24_OPEN_DEVICE("/dev/net/kd/request", &nwc24ShtFd,
                                   IPC_OPEN_READ);
    }

    nwc24ShtRetryRest = SHUTDOWN_RETRY_MAX;
    NWC24EnableLedNotification(TRUE);

    return result;
}

NWC24Err NWC24iRequestShutdown(u32 event, NWC24Err* resultOut) {
    static u8 shtBuffer[32] ALIGN(32);
    static u8 shtResult[32] ALIGN(32);

    *(u32*)shtBuffer = event;
    return NWC24_IOCTL_DEVICE_ASYNC(nwc24ShtFd, NWC24_IOCTL_SHUTDOWN, shtBuffer,
                                    sizeof(shtBuffer), shtResult,
                                    sizeof(shtResult), resultOut);
}

BOOL NWC24Shutdown(BOOL final, u32 event) {
    static BOOL shuttingdown = FALSE;
    static NWC24Err result = NWC24_OK;

    if (final) {
        return TRUE;
    }

    if (shuttingdown) {
        if (NWC24iIsAsyncRequestPending()) {
            return FALSE;
        }

        if (result >= 0) {
            return TRUE;
        }

        if (nwc24ShtRetryRest > 0) {
            shuttingdown = FALSE;
            nwc24ShtRetryRest--;
        } else {
            return TRUE;
        }
    } else if (NWC24iRequestShutdown(event, &result) >= 0) {
        shuttingdown = TRUE;
    }

    return FALSE;
}
