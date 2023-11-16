#ifndef RVL_SDK_NWC24_TIME_H
#define RVL_SDK_NWC24_TIME_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 NWC24iGetUniversalTime(s64* timeOut);
s32 NWC24iGetTimeDifference(s64* diffOut);
s32 NWC24iSetRtcCounter(u32 rtc, u32 misc);
s32 NWC24iSynchronizeRtcCounter(BOOL misc);

#ifdef __cplusplus
}
#endif
#endif
