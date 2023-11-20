#ifndef RVL_SDK_NWC24_SYSTEM_H
#define RVL_SDK_NWC24_SYSTEM_H
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24EnableLedNotification(BOOL enable);
NWC24Err NWC24iPrepareShutdown(void);
NWC24Err NWC24iRequestShutdown(u32 event, NWC24Err* resultOut);
BOOL NWC24Shutdown(BOOL final, u32 event);

#ifdef __cplusplus
}
#endif
#endif
