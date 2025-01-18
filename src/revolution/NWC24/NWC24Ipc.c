#include <revolution/NWC24.h>

static BOOL NWC24iIsRequestPending = FALSE;

static s32 CallbackAsyncIpc(s32 result, void* arg);

NWC24Err NWC24iOpenResourceManager(const char* user, const char* name,
                                   s32* fdOut, IPCOpenMode mode) {
#pragma unused(user)

    NWC24Err result;

    if (fdOut == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = IOS_Open(name, mode);
    *fdOut = result;

    if (result < 0) {
        if (result == IPC_RESULT_NOEXISTS_INTERNAL) {
            return NWC24_ERR_INPROGRESS;
        }

        if (result == IPC_RESULT_BUSY_INTERNAL) {
            return NWC24_ERR_BUSY;
        }

        return NWC24_ERR_INTERNAL_IPC;
    }

    return NWC24_OK;
}

NWC24Err NWC24iCloseResourceManager(const char* user, s32 fd) {
#pragma unused(user)

    return IOS_Close(fd) < 0 ? NWC24_ERR_INTERNAL_IPC : NWC24_OK;
}

NWC24Err NWC24iIoctlResourceManager(const char* user, s32 fd, s32 type,
                                    void* in, s32 inSize, void* out,
                                    s32 outSize) {
#pragma unused(user)

    return IOS_Ioctl(fd, type, in, inSize, out, outSize) < 0
               ? NWC24_ERR_INTERNAL_IPC
               : NWC24_OK;
}

NWC24Err NWC24iIoctlResourceManagerAsync(const char* user, s32 fd, s32 type,
                                         void* in, s32 inSize, void* out,
                                         s32 outSize, void* callbackArg) {
#pragma unused(user)

    if (IOS_IoctlAsync(fd, type, in, inSize, out, outSize, CallbackAsyncIpc,
                       callbackArg) < 0) {
        return NWC24_ERR_INTERNAL_IPC;
    }

    NWC24iIsRequestPending = TRUE;
    return NWC24_OK;
}

BOOL NWC24iIsAsyncRequestPending(void) {
    return NWC24iIsRequestPending;
}

static s32 CallbackAsyncIpc(s32 result, void* arg) {
    if (arg != NULL) {
        *(s32*)arg = result;
    }

    NWC24iIsRequestPending = FALSE;
    return IPC_RESULT_OK;
}
