#include <revolution/NWC24.h>
#include <revolution/SC.h>
#include <string.h>

#define CHECK_CALLING_STATUS() CheckCallingStatus(__FUNCTION__)

#define IOCTL_IN ((CommonBuffer*)nwc24TimeCommonBuffer)
#define IOCTL_OUT ((CommonResult*)nwc24TimeCommonResult)

typedef enum {
    NWC24_IOCTL_SET_RTC_COUNTER = 23,
    NWC24_IOCTL_GET_TIME_DIFFERENCE = 24,
} NWC24Ioctl;

typedef struct CommonBuffer {
    u32 rtc;   // at 0x0
    u32 flags; // at 0x4
} CommonBuffer;

#pragma pack(push, 1)
typedef struct CommonResult {
    s32 result; // at 0x0
    s64 diff;   // at 0x4
} CommonResult;
#pragma pack(pop)

static BOOL nwc24TimeInitialized = FALSE;
static u32 nwc24TimeRtc = 0;
static s64 nwc24TimeDifference = 0;

static u8 nwc24TimeCommonResult[32] ALIGN(32);
static u8 nwc24TimeCommonBuffer[32] ALIGN(32);
static OSMutex nwc24TimeCommandMutex ALIGN(32);

static NWC24Err GetRTC(u32* rtc);
static NWC24Err CheckCallingStatus(const char* user);
static void InitMutex(void);
static void LockRight(void);
static void UnlockRight(void);

// Unused from NWC24iStrTime, but pooled in
static u8 buf[128];
DECOMP_FORCEACTIVE(NWC24Time_c, buf);

NWC24Err NWC24iGetUniversalTime(s64* timeOut) {
    static s64 whenCached = 0;

    NWC24Err result;
    s64 sysTime;

    if (timeOut == NULL) {
        nwc24TimeDifference = 0;
        return NWC24_ERR_INVALID_VALUE;
    }

    if (whenCached == 0 ||
        whenCached + OS_SEC_TO_TICKS(1) <= __OSGetSystemTime() ||
        nwc24TimeRtc == 0) {

        result = NWC24iGetTimeDifference(&nwc24TimeDifference);
        if (result < 0) {
            return result;
        }

        result = GetRTC(&nwc24TimeRtc);
        if (result != NWC24_OK) {
            return result;
        }

        whenCached = __OSGetSystemTime();
    }

    *timeOut = nwc24TimeDifference + nwc24TimeRtc;
    return NWC24_OK;
}

NWC24Err NWC24iGetTimeDifference(s64* diffOut) {
    s32 fd;
    NWC24Err result;
    NWC24Err close;

    result = CHECK_CALLING_STATUS();
    if (result < 0) {
        return result;
    }

    LockRight();
    {
        result = NWC24_OPEN_DEVICE("/dev/net/kd/time", &fd, IPC_OPEN_NONE);

        if (result >= 0) {
            result = NWC24_IOCTL_DEVICE(fd, NWC24_IOCTL_GET_TIME_DIFFERENCE,
                                        NULL, 0, &nwc24TimeCommonResult,
                                        sizeof(nwc24TimeCommonResult));

            if (result >= 0) {
                result = IOCTL_OUT->result;

                // Cast is necessary
                if (result == 0 && diffOut != (void*)NULL) {
                    *diffOut = IOCTL_OUT->diff;
                }
            }

            close = NWC24_CLOSE_DEVICE(fd);
            if (result >= 0) {
                result = close;
            }
        }
    }
    UnlockRight();

    return result;
}

NWC24Err NWC24iSetRtcCounter(u32 rtc, u32 flags) {
    s32 fd;
    NWC24Err result;
    NWC24Err close;

    result = CHECK_CALLING_STATUS();
    if (result < 0) {
        return result;
    }

    LockRight();
    {
        result = NWC24_OPEN_DEVICE("/dev/net/kd/time", &fd, IPC_OPEN_NONE);

        if (result >= 0) {
            IOCTL_IN->rtc = rtc;
            IOCTL_IN->flags = flags;

            result = NWC24_IOCTL_DEVICE(
                fd, NWC24_IOCTL_SET_RTC_COUNTER, &nwc24TimeCommonBuffer,
                sizeof(nwc24TimeCommonBuffer), &nwc24TimeCommonResult,
                sizeof(nwc24TimeCommonResult));

            if (result >= 0) {
                result = IOCTL_OUT->result;
            }

            close = NWC24_CLOSE_DEVICE(fd);
            if (result >= 0) {
                result = close;
            }
        }
    }
    UnlockRight();

    return result;
}

NWC24Err NWC24iSynchronizeRtcCounter(BOOL forceSave) {
    u32 rtc;
    NWC24Err result;

    result = GetRTC(&rtc);
    if (result != NWC24_OK) {
        return result;
    }

    return NWC24iSetRtcCounter(rtc, forceSave ? 1 : 0);
}

static NWC24Err GetRTC(u32* rtc) {
    u32 status;

    do {
        status = SCCheckStatus();

        if (status == SC_STATUS_FATAL) {
            return NWC24_ERR_FATAL;
        }
    } while (status != SC_STATUS_OK);

    *rtc = OS_TICKS_TO_SEC(OSGetTime()) - SCGetCounterBias();
    return NWC24_OK;
}

static NWC24Err CheckCallingStatus(const char* user) {
#pragma unused(user)

    if (OSGetCurrentThread() == NULL) {
        return NWC24_ERR_FATAL;
    }

    return NWC24_OK;
}

static void InitMutex(void) {
    BOOL enabled = OSDisableInterrupts();

    if (!nwc24TimeInitialized) {
        OSInitMutex(&nwc24TimeCommandMutex);

        memset(&nwc24TimeCommonBuffer, 0, sizeof(nwc24TimeCommonBuffer));
        memset(&nwc24TimeCommonResult, 0, sizeof(nwc24TimeCommonResult));

        nwc24TimeInitialized = TRUE;
    }

    OSRestoreInterrupts(enabled);
}

static void LockRight(void) {
    if (!nwc24TimeInitialized) {
        InitMutex();
    }

    OSLockMutex(&nwc24TimeCommandMutex);
}

static void UnlockRight(void) {
    OSUnlockMutex(&nwc24TimeCommandMutex);
}
