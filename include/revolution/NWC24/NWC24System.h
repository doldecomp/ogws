#ifndef RVL_SDK_NWC24_SYSTEM_H
#define RVL_SDK_NWC24_SYSTEM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 NWC24EnableLedNotification(BOOL enable);
s32 NWC24iPrepareShutdown(void);
s32 NWC24iRequestShutdown(u32 event, s32* resultOut);
BOOL NWC24Shutdown(u32 pass, u32 event);

#ifdef __cplusplus
}
#endif
#endif
