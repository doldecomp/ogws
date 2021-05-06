#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H
#include "types_egg.h"
#include <RevoSDK/MEM/mem_heapCommon.h>
#include "ut_list.h"

namespace EGG
{
    using namespace nw4r;

    struct Heap
    {
        enum EHeapKind
        {
            HEAP_EXPANDED = 1,
            HEAP_FRAME = 2
        };

        Heap(MEMiHeapHead *);
        virtual ~Heap(); // at 0x8

        virtual EHeapKind getHeapKind() const = 0; // at 0xC
        virtual UNKTYPE initAllocator(Allocator *, s32) = 0; // at 0x10
        virtual UNKTYPE alloc(u32, s32) = 0; // at 0x14
        virtual UNKTYPE free(void *) = 0; // at 0x18
        virtual UNKTYPE destroy() = 0; // at 0x1C
        virtual UNKTYPE resizeForMBlock(void *, u32) = 0; // at 0x20
        virtual UNKTYPE getAllocatableSize(s32) = 0; // at 0x24
        virtual UNKTYPE adjust() = 0; // at 0x28

        static UNKTYPE initialize();
        static UNKTYPE alloc(u32, int, Heap *);
        Heap * findParentHeap();
        static Heap * findContainHeap(const void *);
        static UNKTYPE free(void *, Heap *);
        UNKTYPE dispose();
        UNKTYPE becomeCurrentHeap();

        UNKWORD WORD_0x4;
        UNKWORD WORD_0x8;
        UNKWORD WORD_0xC;
        MEMiHeapHead * mHeapHandle; // at 0x10
        UNKWORD WORD_0x14;
        Heap * mParentHeap; // at 0x18
        UNKWORD WORD_0x1C;
        UNKWORD WORD_0x20;
        UNKWORD WORD_0x24;
        ut::List mChildren; // at 0x28
        // . . .
    };
}

void * operator new(size_t);
void * operator new (size_t, EGG::Heap *, int);
void * operator new[](size_t);
void * operator new[](size_t, int);
void * operator new[](size_t, EGG::Heap *, int);
void operator delete(void *);
void operator delete[](void *);

#endif