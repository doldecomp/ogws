#ifndef REVOSDK_MEM_EXPHEAP_H
#define REVOSDK_MEM_EXPHEAP_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct MEMExpHeap
{
    u32 mMagic; // "EXPH"
    // . . .
};

#ifdef __cplusplus
}
#endif
#endif