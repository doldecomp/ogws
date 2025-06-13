#ifndef EGG_CORE_ALLOCATOR_H
#define EGG_CORE_ALLOCATOR_H
#include <egg/types_egg.h>

#include <revolution/MEM.h>

namespace EGG {

// Forward declarations
class Heap;

class Allocator : public MEMAllocator {
public:
    Allocator(Heap* pHeap, s32 align = 32);
    virtual ~Allocator();

    virtual void* alloc(u32 size);
    virtual void free(void* pBlock);
};

} // namespace EGG

#endif
