#ifndef RVL_SDK_NWC24_UTILS_H
#define RVL_SDK_NWC24_UTILS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24Data {
    const void* ptr; // at 0x0
    u32 size;        // at 0x4
} NWC24Data;

typedef struct NWC24Date {
    u16 year; // at 0x0
    u8 month; // at 0x2
    u8 day;   // at 0x3
    u8 hour;  // at 0x4
    u8 sec;   // at 0x5
    u8 min;   // at 0x6
    u8 BYTE_0x7;
} NWC24Date;

typedef struct NWC24Calendar {
    /* 0x00 */ u32 sec;
    /* 0x04 */ u32 min;
    /* 0x08 */ u32 hour;
    /* 0x0C */ u32 day;
    /* 0x10 */ u32 month;
    /* 0x14 */ u32 year;
    /* 0x18 */ u32 UNK_0x18;
    /* 0x1C */ u32 UNK_0x1C;
    /* 0x20 */ u32 UNK_0x20;
} NWC24Calendar;

void NWC24Data_Init(NWC24Data* data);
void NWC24Data_SetDataP(NWC24Data* data, const void* ptr, u32 size);
void NWC24Date_Init(NWC24Date* date);
void NWC24iConvIdToStr(u64 addr, char* out);

#ifdef __cplusplus
}
#endif
#endif
