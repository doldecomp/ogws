#include <revolution/NWC24.h>
#include <revolution/OS.h>
#include <string.h>

#define CHECK_CALLING_STATUS(block) CheckCallingStatus(__FUNCTION__, block)

#define IOCTL_IN ((CommonBuffer*)nwc24ScdCommonBuffer)
#define IOCTL_OUT ((CommonResult*)nwc24ScdCommonResult)

typedef enum {
    NWC24_IOCTL_SUSPEND_SCHEDULER = 1,
    NWC24_IOCTL_TRY_SUSPEND_SCHEDULER = 2,
    NWC24_IOCTL_RESUME_SCHEDULER = 3,
    NWC24_IOCTL_GENERATE_USER_ID = 15,
} NWC24Ioctl;

typedef struct CommonBuffer {
    u32 WORD_0x0;
} CommonBuffer;

#pragma pack(push, 1)
typedef struct CommonResult {
    s32 result; // at 0x0
    union {
        u64 userid;
        s32 exResult;
    }; // at 0x4
    u32 WORD_0x8;
} CommonResult;
#pragma pack(pop)

static u32 nwc24ScdInitialized = 0;
static s32 nwc24ScdSuspendCnt = 0;
static s32 nwc24ScdOpenCnt = 0;

static OSMutex nwc24ScdCommandMutex;
static OSMutex nwc24ScdCounterMutex;

static u8 nwc24ScdCommonBuffer[32] ALIGN(32);
static u8 nwc24ScdCommonResult[32] ALIGN(32);

static u8 nwc24ScdStatBuf[256] ALIGN(32);

// clang-format off
// nwc24ScdStatBuf unused
DECOMP_FORCEACTIVE(NWC24Schedule_c,
                   nwc24ScdCounterMutex,
                   nwc24ScdCommandMutex,
                   nwc24ScdCommonBuffer,
                   nwc24ScdCommonResult,
                   nwc24ScdStatBuf);
// clang-format on

// Pool order
DECOMP_FORCEACTIVE(NWC24Schedule_c, "/dev/net/kd/request");

static NWC24Err ExecSuspendScheduler(void) DECOMP_DONT_INLINE;
static NWC24Err ExecTrySuspendScheduler(u32 arg0);
static NWC24Err ExecResumeScheduler(void) DECOMP_DONT_INLINE;
static NWC24Err ExecNoParamCommand(const char* user, s32 type,
                                   NWC24Err* exResultOut);

static void InitScdMutex(void);

static void LockRight(void);
static BOOL TryLockRight(void);
static void UnlockRight(void);

static void LockCounters(void);
static BOOL TryLockCounters(void);
static void UnlockCounters(void);

static NWC24Err CheckCallingStatus(const char* user, BOOL block);

s32 NWC24SuspendScheduler(void) {
    s32 count;

    LockCounters();
    {
        count = ExecSuspendScheduler();
        if (count >= 0) {
            nwc24ScdSuspendCnt++;
            count -= nwc24ScdOpenCnt;
        }
    }
    UnlockCounters();

    return count;
}

s32 NWC24ResumeScheduler(void) {
    s32 count;

    LockCounters();
    {
        if (nwc24ScdOpenCnt > 0 && nwc24ScdSuspendCnt == 0) {
            count = 0;
        } else {
            count = ExecResumeScheduler();

            if (nwc24ScdSuspendCnt > 0) {
                nwc24ScdSuspendCnt--;
                count -= nwc24ScdOpenCnt;
            }
        }
    }
    UnlockCounters();

    return count;
}

NWC24Err NWC24iRequestGenerateUserId(u64* idOut, u32* arg1) {
    s32 fd;
    NWC24Err result;
    NWC24Err close;

    result = CHECK_CALLING_STATUS(TRUE);
    if (result < 0) {
        return result;
    }

    LockRight();
    {
        result = NWC24_OPEN_DEVICE("/dev/net/kd/request", &fd, IPC_OPEN_NONE);

        if (result >= 0) {
            result = NWC24_IOCTL_DEVICE(fd, NWC24_IOCTL_GENERATE_USER_ID, NULL,
                                        0, nwc24ScdCommonResult,
                                        sizeof(nwc24ScdCommonResult));

            if (result >= 0) {
                result = IOCTL_OUT->result;

                if (result == NWC24_OK || result == NWC24_ERR_ID_GENERATED ||
                    result == NWC24_ERR_ID_REGISTERED) {

                    if (idOut != (void*)NULL) {
                        *idOut = IOCTL_OUT->userid;
                    }

                    if (arg1 != (void*)NULL) {
                        *arg1 = IOCTL_OUT->WORD_0x8;
                    }
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

NWC24Err NWC24iTrySuspendForOpenLib(void) {
    NWC24Err result;

    if (!TryLockCounters()) {
        return NWC24_ERR_MUTEX;
    }

    result = ExecTrySuspendScheduler(0);
    if (result >= 0) {
        nwc24ScdOpenCnt++;
        result = NWC24_OK;
    }

    UnlockCounters();
    return result;
}

NWC24Err NWC24iResumeForCloseLib(void) {
    NWC24Err result;

    LockCounters();
    {
        result = ExecResumeScheduler();
        if (result >= 0) {
            nwc24ScdOpenCnt--;
            result = NWC24_OK;
        }
    }
    UnlockCounters();

    return result;
}

static NWC24Err ExecSuspendScheduler(void) {
    return ExecNoParamCommand(NULL, NWC24_IOCTL_SUSPEND_SCHEDULER, NULL);
}

static NWC24Err ExecTrySuspendScheduler(u32 arg0) {
    s32 fd;
    NWC24Err result;
    NWC24Err close;

    result = CHECK_CALLING_STATUS(TRUE);
    if (result < 0) {
        return result;
    }

    if (!TryLockRight()) {
        return NWC24_ERR_MUTEX;
    }

    result = NWC24_OPEN_DEVICE("/dev/net/kd/request", &fd, IPC_OPEN_NONE);

    if (result >= 0) {
        IOCTL_IN->WORD_0x0 = arg0;

        result = NWC24_IOCTL_DEVICE(
            fd, NWC24_IOCTL_TRY_SUSPEND_SCHEDULER, nwc24ScdCommonBuffer,
            sizeof(nwc24ScdCommonBuffer), nwc24ScdCommonResult,
            sizeof(nwc24ScdCommonResult));

        if (result >= 0) {
            result = IOCTL_OUT->result;
        }

        close = NWC24_CLOSE_DEVICE(fd);
        if (close < 0) {
            result = close;
        }
    }

    UnlockRight();
    return result;
}

static NWC24Err ExecResumeScheduler(void) {
    return ExecNoParamCommand(NULL, NWC24_IOCTL_RESUME_SCHEDULER, NULL);
}

static NWC24Err ExecNoParamCommand(const char* user, s32 type,
                                   NWC24Err* exResultOut) {
    s32 fd;
    NWC24Err result;
    NWC24Err close;

    if (OSGetCurrentThread() == NULL) {
        return NWC24_ERR_FATAL;
    }

    LockRight();
    {
        result = NWC24iOpenResourceManager(user, "/dev/net/kd/request", &fd,
                                           IPC_OPEN_NONE);

        if (result >= 0) {
            result = NWC24iIoctlResourceManager(user, fd, type, NULL, 0,
                                                nwc24ScdCommonResult,
                                                sizeof(nwc24ScdCommonResult));

            if (result >= 0) {
                result = IOCTL_OUT->result;

                if (result == NWC24_ERR_FAILED ||
                    result == NWC24_ERR_CONFIG_NETWORK) {

                    if (exResultOut != (void*)NULL) {
                        *exResultOut = IOCTL_OUT->exResult;
                    }
                }
            }

            close = NWC24iCloseResourceManager(user, fd);
            if (close < 0) {
                result = close;
            }
        }
    }
    UnlockRight();

    return result;
}

static void InitScdMutex(void) {
    BOOL enabled = OSDisableInterrupts();

    if (!(nwc24ScdInitialized & 1)) {
        OSInitMutex(&nwc24ScdCommandMutex);
        OSInitMutex(&nwc24ScdCounterMutex);

        memset(nwc24ScdCommonBuffer, 0, sizeof(nwc24ScdCommonBuffer));
        memset(nwc24ScdCommonResult, 0, sizeof(nwc24ScdCommonResult));

        nwc24ScdInitialized |= 1;
    }

    OSRestoreInterrupts(enabled);
}

static void LockRight(void) {
    if (!(nwc24ScdInitialized & 1)) {
        InitScdMutex();
    }

    OSLockMutex(&nwc24ScdCommandMutex);
}

static BOOL TryLockRight(void) {
    if (!(nwc24ScdInitialized & 1)) {
        InitScdMutex();
    }

    return OSTryLockMutex(&nwc24ScdCommandMutex);
}

static void UnlockRight(void) {
    OSUnlockMutex(&nwc24ScdCommandMutex);
}

static void LockCounters(void) {
    if (!(nwc24ScdInitialized & 1)) {
        InitScdMutex();
    }

    OSLockMutex(&nwc24ScdCounterMutex);
}

static BOOL TryLockCounters(void) {
    if (!(nwc24ScdInitialized & 1)) {
        InitScdMutex();
    }

    return OSTryLockMutex(&nwc24ScdCounterMutex);
}

static void UnlockCounters(void) {
    OSUnlockMutex(&nwc24ScdCounterMutex);
}

static NWC24Err CheckCallingStatus(const char* user, BOOL block) {
#pragma unused(user)
#pragma unused(block)

    if (OSGetCurrentThread() == NULL) {
        return NWC24_ERR_FATAL;
    }

    if (NWC24IsMsgLibOpened() || NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_OPENED;
    }

    return NWC24_OK;
}
