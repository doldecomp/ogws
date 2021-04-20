#ifndef REVOSDK_MEM_ALLOCATOR_H
#define REVOSDK_MEM_ALLOCATOR_H
#include <types.h>
#include "mem_expHeap.h"
#ifdef __cplusplus
extern "C" {
#endif

struct MEMAllocator
{
    void *PTR_0x0;
    MEMExpHeap *mExpHeap;
    // . . .
};

#ifdef __cplusplus
}
#endif
#endif