#ifndef RVL_SDK_NWC24_DATE_PARSER_H
#define RVL_SDK_NWC24_DATE_PARSER_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/NWC24Utils.h>
#include <revolution/OS.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iDateToMinutes(s32* pMinutes, const NWC24Date* pDate);
s32 NWC24iGetDayOfWeek(u16 year, u8 month, u8 day);
NWC24Err NWC24iEpochSecondsToDate(NWC24Date* pDate, s64 timestamp);
NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime* pOSTime,
                                    const NWC24Date* pDate);
NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day);

#ifdef __cplusplus
}
#endif
#endif
