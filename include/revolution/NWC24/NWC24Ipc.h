#ifndef RVL_SDK_NWC24_IPC_H
#define RVL_SDK_NWC24_IPC_H
#include <revolution/IPC.h>
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iOpenResourceManager(const char* user, const char* name,
                                   s32* fdOut, IPCOpenMode mode);
NWC24Err NWC24iCloseResourceManager(const char* user, s32 fd);

NWC24Err NWC24iIoctlResourceManager(const char* user, s32 fd, s32 type,
                                    void* in, s32 inSize, void* out,
                                    s32 outSize);
NWC24Err NWC24iIoctlResourceManagerAsync(const char* user, s32 fd, s32 type,
                                         void* in, s32 inSize, void* out,
                                         s32 outSize, void* callbackArg);

BOOL NWC24iIsAsyncRequestPending(void);

/**
 * @brief Macros to supply name of caller
 */

// clang-format off
#define NWC24_OPEN_DEVICE(name, fdOut, mode) \
    NWC24iOpenResourceManager(__FUNCTION__, name, fdOut, mode)

#define NWC24_CLOSE_DEVICE(fd) \
    NWC24iCloseResourceManager(__FUNCTION__, fd)

#define NWC24_IOCTL_DEVICE(fd, type, in, inSize, out, outSize) \
    NWC24iIoctlResourceManager(__FUNCTION__, fd, type, in, inSize, out, outSize)

#define NWC24_IOCTL_DEVICE_ASYNC(fd, type, in, inSize, out, outSize, callbackArg) \
    NWC24iIoctlResourceManagerAsync(__FUNCTION__, fd, type, in, inSize, out, outSize, callbackArg)
// clang-format on

#ifdef __cplusplus
}
#endif
#endif
