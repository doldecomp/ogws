#ifndef RVL_SDK_MEM_ALLOCATOR_H
#define RVL_SDK_MEM_ALLOCATOR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct MEMAllocator MEMAllocator;
typedef struct MEMiHeapHead MEMiHeapHead;

typedef void* (*MEMAllocatorAllocFunc)(MEMAllocator* allocator, u32 size);
typedef void (*MEMAllocatorFreeFunc)(MEMAllocator* allocator, void* block);

typedef struct MEMAllocatorFuncs {
    MEMAllocatorAllocFunc allocFunc; // at 0x0
    MEMAllocatorFreeFunc freeFunc;   // at 0x4
} MEMAllocatorFuncs;

typedef struct MEMAllocator {
    const MEMAllocatorFuncs* funcs; // at 0x0
    MEMiHeapHead* heap;             // at 0x4
    u32 heapParam1;                 // at 0x8
    u32 heapParam2;                 // at 0xC
} MEMAllocator;

void* MEMAllocFromAllocator(MEMAllocator* allocator, u32 size);
void MEMFreeToAllocator(MEMAllocator* allocator, void* block);

void MEMInitAllocatorForExpHeap(MEMAllocator* allocator, MEMiHeapHead* heap,
                                s32 align);
void MEMInitAllocatorForFrmHeap(MEMAllocator* allocator, MEMiHeapHead* heap,
                                s32 align);

#ifdef __cplusplus
}
#endif
#endif
