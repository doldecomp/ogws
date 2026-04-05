#ifndef RVL_SDK_NWC24_INTERNAL_UTILS_H
#define RVL_SDK_NWC24_INTERNAL_UTILS_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Length of a string literal
#define NWC24i_KSTRLEN(x) ((int)(sizeof(x)))

void NWC24iConvIdToStr(u64 addr, char* pBuffer);

#ifdef __cplusplus
}
#endif
#endif
