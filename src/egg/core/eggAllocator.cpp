#include <egg/core.h>

namespace EGG {

Allocator::Allocator(Heap* pHeap, s32 align) {
    pHeap->initAllocator(this, align);
}

Allocator::~Allocator() {}

void* Allocator::alloc(u32 size) {
    return MEMAllocFromAllocator(this, size);
}

void Allocator::free(void* pBlock) {
    MEMFreeToAllocator(this, pBlock);
}

} // namespace EGG
