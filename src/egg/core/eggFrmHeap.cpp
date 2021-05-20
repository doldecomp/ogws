#pragma use_lmw_stmw on
#include "eggFrmHeap.h"
#include "ut_algorithm.h"
#include <RevoSDK/MEM/mem_frameHeap.h>
#include <RevoSDK/MEM/mem_allocator.h>
#include <new>

namespace EGG
{
    using namespace nw4r;

    FrmHeap::FrmHeap(MEMiHeapHead *handle) : Heap(handle)
    {

    }

    FrmHeap::~FrmHeap()
    {
        dispose();
        MEMDestroyFrmHeap(mHeapHandle);
    }

    #ifdef __DECOMP_NON_MATCHING
    FrmHeap * FrmHeap::create(void *memBlock, u32 size, u16 r5)
    {
        void *heapEnd = ut::RoundDown((void *)((u32)memBlock + size), 4);
        void *heapStart = ut::RoundUp(memBlock, 4);
        FrmHeap *newHeap = NULL;

        // 1. Heap size must be positive (end > start)
        // 2. Heap size must be bigger than heap object size + 4 (Smallest reasonable heap size?)
        u32 heapSize = ut::GetOffsetFromPtr(heapStart, heapEnd);
        if (heapEnd < heapStart || heapSize < sizeof(FrmHeap) + 4)
        {
            return NULL;
        }

        // Beginning of mem block is reserved for FrmHeap object
        // As a result, max heap size is (Mem block size - sizeof(FrmHeap))
        MEMiHeapHead *handle = MEMCreateFrmHeapEx((void *)ut::AddOffsetToPtr<u32>(heapStart, sizeof(FrmHeap)),
            heapSize - sizeof(FrmHeap), r5);

        if (handle)
        {
            Heap * containHeap = findContainHeap(heapStart);
            if (containHeap)
            {
                (void)new (heapStart) FrmHeap(handle);
            }

            FrmHeap *temp = (FrmHeap *)heapStart;
            temp->mMemBlock = memBlock;
            temp->mParentHeap = containHeap;
            newHeap = temp;
        }

        return newHeap;
    }
    #else
    #error This file has not yet been decompiled accurately. Use "eggFrmHeap.s" instead.
    #endif

    FrmHeap * FrmHeap::create(u32 size, Heap *pHeap, u16 r5)
    {
        FrmHeap *newHeap = NULL;

        if (!pHeap) pHeap = sCurrentHeap;
        if (size == -1) size = pHeap->getAllocatableSize(4);

        void *memBlock = pHeap->alloc(size, 4);
        if (memBlock)
        {
            newHeap = create(memBlock, size, r5);
            if (newHeap)
            {
                newHeap->mParentHeap = pHeap;
            }
            else
            {
                pHeap->free(memBlock);
            }
        }

        return newHeap;
    }

    void FrmHeap::destroy()
    {
        Heap *pParent = findParentHeap();
        this->~FrmHeap();

        if (pParent) pParent->free(this);
    }

    void * FrmHeap::alloc(u32 size, s32 align)
    {
        return MEMAllocFromFrmHeapEx(mHeapHandle, size, align);
    }

    void FrmHeap::free(void *p)
    {

    }

    u32 FrmHeap::resizeForMBlock(void *memBlock, u32 size)
    {
        return MEMResizeForMBlockFrmHeap(mHeapHandle, memBlock, size);
    }

    u32 FrmHeap::getAllocatableSize(s32 align)
    {
        return MEMGetAllocatableSizeForFrmHeapEx(mHeapHandle, align);
    }

    u32 FrmHeap::adjust()
    {
        u32 newSize = MEMAdjustFrmHeap(mHeapHandle) + sizeof(FrmHeap);

        if (newSize > sizeof(FrmHeap) && mParentHeap)
        {
            mParentHeap->resizeForMBlock(mMemBlock, newSize);
            return newSize;
        }
        else
        {
            return 0;
        }
    }

    void FrmHeap::initAllocator(Allocator *pAllocator, s32 r5)
    {
        MEMInitAllocatorForFrmHeap((MEMAllocator *)pAllocator, mHeapHandle, r5);
    }

    Heap::EHeapKind FrmHeap::getHeapKind() const
    {
        return HEAP_FRAME;
    }
}