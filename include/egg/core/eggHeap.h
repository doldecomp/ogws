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
        virtual ~Heap();

        virtual EHeapKind getHeapKind() const = 0;
        virtual UNKTYPE initAllocator() = 0;
        virtual UNKTYPE alloc(u32, s32) = 0;
        virtual UNKTYPE free(void *) = 0;
        virtual UNKTYPE destroy() = 0;
        virtual UNKTYPE resizeForMBlock(void *, u32) = 0;
        virtual UNKTYPE getAllocatableSize(s32) = 0;
        virtual UNKTYPE adjust() = 0;

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