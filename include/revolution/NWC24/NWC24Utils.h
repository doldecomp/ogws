#ifndef RVL_SDK_NWC24_UTILS_H
#define RVL_SDK_NWC24_UTILS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24Data {
    void* data;  // at 0x0
    size_t size; // at 0x4
} NWC24Data;

#ifdef __cplusplus
}
#endif
#endif
