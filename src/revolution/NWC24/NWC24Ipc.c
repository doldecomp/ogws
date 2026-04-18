#include <revolution/NWC24.h>
#include <revolution/NWC24/NWC24Internal.h>

static BOOL NWC24iIsRequestPending = FALSE;

// Forward declarations
static s32 CallbackAsyncIpc(s32 result, void* pArg);

NWC24Err NWC24iOpenResourceManager(const char* pUser, const char* pName,
                                   s32* pFd, IPCOpenMode mode) {
#pragma unused(pUser)

    s32 result;

    if (pFd == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = IOS_Open(pName, mode);
    *pFd = result;

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

NWC24Err NWC24iCloseResourceManager(const char* pUser, s32 fd) {
#pragma unused(pUser)

    return IOS_Close(fd) < 0 ? NWC24_ERR_INTERNAL_IPC : NWC24_OK;
}

NWC24Err NWC24iIoctlResourceManager(const char* pUser, s32 fd, s32 type,
                                    void* pIn, s32 inSize, void* pOut,
                                    s32 outSize) {
#pragma unused(pUser)

    return IOS_Ioctl(fd, type, pIn, inSize, pOut, outSize) < 0
               ? NWC24_ERR_INTERNAL_IPC
               : NWC24_OK;
}

NWC24Err NWC24iIoctlResourceManagerAsync(const char* pUser, s32 fd, s32 type,
                                         void* pIn, s32 inSize, void* pOut,
                                         s32 outSize, void* pCallbackArg) {
#pragma unused(pUser)

    if (IOS_IoctlAsync(fd, type, pIn, inSize, pOut, outSize, CallbackAsyncIpc,
                       pCallbackArg) < 0) {

        return NWC24_ERR_INTERNAL_IPC;
    }

    NWC24iIsRequestPending = TRUE;
    return NWC24_OK;
}

BOOL NWC24iIsAsyncRequestPending(void) {
    return NWC24iIsRequestPending;
}

static s32 CallbackAsyncIpc(s32 result, void* pArg) {
    if (pArg != NULL) {
        *(s32*)pArg = result;
    }

    NWC24iIsRequestPending = FALSE;
    return IPC_RESULT_OK;
}
