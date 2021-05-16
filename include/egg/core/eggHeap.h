#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H
#include "types_egg.h"
#include "eggDisposer.h"
#include "ut_list.h"
#include <RevoSDK/MEM/mem_heapCommon.h>
#include <RevoSDK/OS/OSMutex.h>

#define MB_AS_B 1024.0f * 1024.0f // 1048576.0f

namespace EGG
{
    struct Heap : Disposer
    {
        enum EHeapKind
        {
            HEAP_EXPANDED = 1,
            HEAP_FRAME = 2
        };

        Heap(MEMiHeapHead *);
        virtual ~Heap(); // at 0x8
        virtual EHeapKind getHeapKind() const = 0; // at 0xC
        virtual void initAllocator(Allocator *, s32) = 0; // at 0x10
        virtual void * alloc(u32, s32) = 0; // at 0x14
        virtual void free(void *) = 0; // at 0x18
        virtual void destroy() = 0; // at 0x1C
        virtual UNKWORD resizeForMBlock(void *, u32) = 0; // at 0x20
        virtual UNKWORD getAllocatableSize(s32) = 0; // at 0x24
        virtual UNKWORD adjust() = 0; // at 0x28

        static void initialize();
        static void * alloc(u32, int, Heap *);
        Heap * findParentHeap();
        static Heap * findContainHeap(const void *);
        static void free(void *, Heap *);
        void dispose();
        Heap * becomeCurrentHeap();

        UNKWORD WORD_0x8;
        UNKWORD WORD_0xC;
        MEMiHeapHead * mHeapHandle; // at 0x10
        UNKWORD WORD_0x14;
        Heap * mParentHeap; // at 0x18
        UNKWORD WORD_0x1C;
        nw4r::ut::Node mNode; // at 0x20
        nw4r::ut::List mChildren; // at 0x28

        // TO-DO: Figure out the rest of the static members in the assembly
        static nw4r::ut::List sHeapList;
        static OSMutex sRootMutex;
        static Heap *sCurrentHeap;
        static bool sIsHeapListInitialized;
    };
}

void * operator new(size_t);
void * operator new(size_t, EGG::Heap *, int);
void * operator new[](size_t);
void * operator new[](size_t, int);
void * operator new[](size_t, EGG::Heap *, int);
void operator delete(void *);
void operator delete[](void *);

#endif