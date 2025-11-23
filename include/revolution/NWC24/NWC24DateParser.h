#ifndef RVL_SDK_NWC24_DATE_PARSER_H
#define RVL_SDK_NWC24_DATE_PARSER_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day);

#ifdef __cplusplus
}
#endif
#endif
