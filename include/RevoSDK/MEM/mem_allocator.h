#ifndef REVOSDK_MEM_ALLOCATOR_H
#define REVOSDK_MEM_ALLOCATOR_H
#include <types.h>
#include "mem_heapCommon.h"
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
    struct MEMiHeapHead *mHeapHandle; // at 0x4
    UNKWORD WORD_0x8;
    UNKWORD WORD_0xC;
};

void * MEMAllocFromAllocator(struct MEMAllocator *, UNKWORD);
UNKTYPE MEMFreeToAllocator(struct MEMAllocator *, UNKTYPE *);

void MEMInitAllocatorForFrmHeap(struct MEMAllocator *, struct MEMiHeapHead *, s32);

#ifdef __cplusplus
}
#endif
#endif