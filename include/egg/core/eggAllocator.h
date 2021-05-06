#ifndef EGG_CORE_ALLOCATOR_H
#define EGG_CORE_ALLOCATOR_H
#include "types_egg.h"
#include <RevoSDK/MEM/mem_allocator.h>

namespace EGG
{
    struct Allocator : MEMAllocator
    {
        Allocator(Heap *, s32);
        virtual ~Allocator();
        virtual UNKTYPE * alloc(u32);
        virtual UNKTYPE free(void *);
    };
}

#endif