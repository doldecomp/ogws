#include "eggAllocator.h"
#include "eggHeap.h"

namespace EGG
{
    Allocator::Allocator(Heap *pHeap, s32 r5)
    {
        pHeap->initAllocator(this, r5);
    }

    Allocator::~Allocator()
    {

    }

    UNKTYPE * Allocator::alloc(u32 size)
    {
        MEMAllocFromAllocator(this, size);
    }

    UNKTYPE Allocator::free(void *pBlock)
    {
        MEMFreeToAllocator(this, pBlock);
    }
}