#ifndef RVL_SDK_NWC24_CONFIG_H
#define RVL_SDK_NWC24_CONFIG_H
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 NWC24GetAppId(void);

u16 NWC24GetGroupId(void);

NWC24Err NWC24iConfigOpen(void);

NWC24Err NWC24iConfigFlush(void);

#ifdef __cplusplus
}
#endif
#endif
