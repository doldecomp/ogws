#ifndef EGG_CORE_DISPOSER_H
#define EGG_CORE_DISPOSER_H
#include "types_egg.h"

namespace EGG
{
    struct Disposer
    {
        Disposer();
        virtual ~Disposer();

        Heap *mHeap; // at 0x0
    };
}

#endif