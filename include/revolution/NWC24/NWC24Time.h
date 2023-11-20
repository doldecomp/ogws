#ifndef RVL_SDK_NWC24_TIME_H
#define RVL_SDK_NWC24_TIME_H
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iGetUniversalTime(s64* timeOut);
NWC24Err NWC24iGetTimeDifference(s64* diffOut);
NWC24Err NWC24iSetRtcCounter(u32 rtc, u32 misc);
NWC24Err NWC24iSynchronizeRtcCounter(BOOL misc);

#ifdef __cplusplus
}
#endif
#endif
