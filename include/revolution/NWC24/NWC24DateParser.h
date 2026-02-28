#ifndef RVL_SDK_NWC24_DATE_PARSER_H
#define RVL_SDK_NWC24_DATE_PARSER_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/NWC24Utils.h>
#include <revolution/OS.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day);
NWC24Err NWC24iEpochSecondsToDate(NWC24Date* date, s64 timestamp);
NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime* time,
                                    const NWC24Date* date);

#ifdef __cplusplus
}
#endif
#endif
