#ifndef REVOSDK_MEM_ALLOCATOR_H
#define REVOSDK_MEM_ALLOCATOR_H
#include <types.h>
#include "mem_expHeap.h"
#include "mem_frameHeap.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef UNKTYPE (*MEMAllocatorHeapAllocFunc)(UNKTYPE);
typedef UNKTYPE (*MEMAllocatorHeapFreeFunc)(UNKTYPE);

struct MEMAllocatorFuncs
{
    MEMAllocatorHeapAllocFunc mHeapAllocFunc; // at 0x0
    MEMAllocatorHeapFreeFunc mHeapFreeFunc; // at 0x4
};

struct MEMAllocator
{
    struct MEMAllocatorFuncs * mAllocFuncs; // at 0x0
    union
    {
        struct MEMExpHeap *mExpHeap; // at 0x4
        struct MEMFrmHeap *mFrmHeap; // at 0x4
    };
    UNKWORD WORD_0x8;
    UNKWORD WORD_0xC;
};

UNKTYPE MEMAllocFromAllocator(struct MEMAllocator *, UNKWORD);
UNKTYPE MEMFreeToAllocator(struct MEMAllocator *, UNKTYPE *);

#ifdef __cplusplus
}
#endif
#endif