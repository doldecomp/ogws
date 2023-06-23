#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H

#include "types_egg.h"
#include "eggDisposer.h"
#include "eggBitFlag.h"

#include "ut_list.h"

#include <MEM/mem_heapCommon.h>
#include <OS/OSMutex.h>

namespace EGG
{
    class Heap : Disposer
    {
    public:
        enum EHeapKind
        {
            HEAP_EXPANDED = 1,
            HEAP_FRAME = 2
        };

    public:
        static void * addOffset(void *p, u32 ofs) { return (char *)p + ofs;}
        static Heap* getCurrentHeap() { return sCurrentHeap; }

        static void initialize();
        static Heap * findHeap(MEMiHeapHead *);
        static Heap * findContainHeap(const void *);
        static void * alloc(u32, int, Heap *);
        static void free(void *, Heap *);

        Heap(MEMiHeapHead *);
        virtual ~Heap(); // at 0x8
        virtual EHeapKind getHeapKind() const = 0; // at 0xC
        virtual void initAllocator(Allocator *, s32) = 0; // at 0x10
        virtual void * alloc(u32, s32) = 0; // at 0x14
        virtual void free(void *) = 0; // at 0x18
        virtual void destroy() = 0; // at 0x1C
        virtual u32 resizeForMBlock(void *, u32) = 0; // at 0x20
        virtual u32 getAllocatableSize(s32) = 0; // at 0x24
        virtual u32 adjust() = 0; // at 0x28

        u8 * getStartAddress() { return (u8 *)this; }
        u8 * getEndAddress() { return mHeapHandle->end; }
        int getTotalSize() { return getEndAddress() - getStartAddress(); }

        bool tstDisableAllocation() { return mFlags.onBit(0); }
        void disableAllocation() { mFlags.setBit(0); }
        void enableAllocation() { mFlags.resetBit(0); }

        void appendDisposer(Disposer* disposer)
        {
            nw4r::ut::List_Append(&mChildren, disposer);
        }
        void removeDisposer(Disposer* disposer)
        {
            nw4r::ut::List_Remove(&mChildren, disposer);
        }

        Heap * findParentHeap();
        void dispose();
        Heap * becomeCurrentHeap();

    protected:
        MEMiHeapHead * mHeapHandle; // at 0x10
        void * mMemBlock; // at 0x14
        Heap * mParentHeap; // at 0x18
        TBitFlag<u16> mFlags; // at 0x1C
        nw4r::ut::Node mNode; // at 0x20
        nw4r::ut::List mChildren; // at 0x28

        static nw4r::ut::List sHeapList;
        static OSMutex sRootMutex;
        static Heap *sCurrentHeap;
        static BOOL sIsHeapListInitialized;
        static Heap *sAllocatableHeap;
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