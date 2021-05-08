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

    void * Allocator::alloc(u32 size)
    {
        return MEMAllocFromAllocator(this, size);
    }

    void Allocator::free(void *pBlock)
    {
        MEMFreeToAllocator(this, pBlock);
    }
}