#ifndef EGG_CORE_ALLOCATOR_H
#define EGG_CORE_ALLOCATOR_H
#include "types_egg.h"
#include <revolution/MEM/mem_allocator.h>

namespace EGG
{
    struct Allocator : MEMAllocator
    {
        Allocator(Heap *, s32);
        virtual ~Allocator();
        virtual void * alloc(u32);
        virtual void free(void *);
    };
}

#endif