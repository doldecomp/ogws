// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>

#include <nw4r/ut.h>

#include <revolution/MEM.h>

namespace EGG {

FrmHeap::FrmHeap(MEMiHeapHead* pHeapHandle) : Heap(pHeapHandle) {}

FrmHeap::~FrmHeap() {
    dispose();
    MEMDestroyFrmHeap(mHeapHandle);
}

FrmHeap* FrmHeap::create(void* pHeapStart, u32 size, u16 opt) {
    FrmHeap* pHeap = NULL;

    void* pHeapBuffer = pHeapStart;
    void* pHeapEnd = ROUND_DOWN_PTR(addOffset(pHeapStart, size), 4);

    pHeapStart = ROUND_UP_PTR(pHeapStart, 4);

    if (pHeapStart > pHeapEnd ||
        PTR_DISTANCE(pHeapStart, pHeapEnd) < sizeof(FrmHeap) + 4) {

        return NULL;
    }

    MEMiHeapHead* pHeapHandle = MEMCreateFrmHeapEx(
        addOffset(pHeapStart, sizeof(FrmHeap)),
        PTR_DISTANCE(pHeapStart, pHeapEnd) - sizeof(FrmHeap), opt);

    if (pHeapHandle != NULL) {
        Heap* pContainHeap = findContainHeap(pHeapStart);

        pHeap = new (pHeapStart) FrmHeap(pHeapHandle);
        pHeap->registerHeapBuffer(pHeapBuffer);
        pHeap->mParentHeap = pContainHeap;
    }

    return pHeap;
}

FrmHeap* FrmHeap::create(u32 size, Heap* pParentHeap, u16 opt) {
    FrmHeap* pHeap = NULL;

    if (pParentHeap == NULL) {
        pParentHeap = getCurrentHeap();
    }

    if (size == 0xFFFFFFFF) {
        size = pParentHeap->getAllocatableSize();
    }

    void* pHeapStart = pParentHeap->alloc(size);
    if (pHeapStart != NULL) {

        pHeap = create(pHeapStart, size, opt);
        if (pHeap != NULL) {
            pHeap->mParentHeap = pParentHeap;
        } else {
            pParentHeap->free(pHeapStart);
        }
    }

    return pHeap;
}

void FrmHeap::destroy() {
    Heap* pParentHeap = findParentHeap();

    this->~FrmHeap();
    if (pParentHeap != NULL) {
        pParentHeap->free(this);
    }
}

void* FrmHeap::alloc(u32 size, s32 align) {
    return MEMAllocFromFrmHeapEx(mHeapHandle, size, align);
}

void FrmHeap::free(void* pBlock) {
#pragma unused(pBlock)
}

u32 FrmHeap::resizeForMBlock(void* pBlock, u32 size) {
    return MEMResizeForMBlockFrmHeap(mHeapHandle, pBlock, size);
}

u32 FrmHeap::getAllocatableSize(s32 align) {
    return MEMGetAllocatableSizeForFrmHeapEx(mHeapHandle, align);
}

u32 FrmHeap::adjust() {
    u32 adjustSize = MEMAdjustFrmHeap(mHeapHandle) + sizeof(FrmHeap);

    if (adjustSize > sizeof(FrmHeap) && mParentHeap != NULL) {
        mParentHeap->resizeForMBlock(mHeapBuffer, adjustSize);
        return adjustSize;
    }

    return 0;
}

void FrmHeap::initAllocator(Allocator* pAllocator, s32 r5) {
    MEMInitAllocatorForFrmHeap((MEMAllocator*)pAllocator, mHeapHandle, r5);
}

} // namespace EGG
