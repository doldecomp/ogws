#ifndef EGG_CORE_FRAMEHEAP_H
#define EGG_CORE_FRAMEHEAP_H
#include "types_egg.h"
#include "eggHeap.h"
#include "eggDisposer.h"

namespace EGG
{
    struct FrmHeap : Heap
    {
        virtual ~FrmHeap(); // at 0x8
        virtual EHeapKind getHeapKind() const; // at 0xC
        virtual void initAllocator(Allocator *, s32); // at 0x10
        virtual void * alloc(u32, s32); // at 0x14
        virtual void free(void *); // at 0x18
        virtual void destroy(); // at 0x1C
        virtual UNKWORD resizeForMBlock(void *, u32); // at 0x20
        virtual UNKWORD getAllocatableSize(s32); // at 0x24
        virtual UNKWORD adjust(); // at 0x28

        FrmHeap * create(void *, u32, u16);
        FrmHeap * create(u32, Heap *, u16);
    };
}

#endif