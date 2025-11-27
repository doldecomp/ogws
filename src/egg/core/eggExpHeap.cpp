// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>

#include <nw4r/ut.h>

#include <revolution/MEM.h>

namespace EGG {

ExpHeap::ExpHeap(MEMiHeapHead* pHeapHandle) : Heap(pHeapHandle) {}

ExpHeap::~ExpHeap() {
    dispose();
    MEMDestroyExpHeap(mHeapHandle);
}

ExpHeap* ExpHeap::create(void* pHeapStart, u32 size, u16 opt) {
    ExpHeap* pHeap = NULL;

    void* pHeapBuffer = pHeapStart;
    void* pHeapEnd = ROUND_DOWN_PTR(addOffset(pHeapStart, size), 4);

    pHeapStart = ROUND_UP_PTR(pHeapStart, 4);

    if (pHeapStart > pHeapEnd ||
        nw4r::ut::GetOffsetFromPtr(pHeapStart, pHeapEnd) <
            sizeof(ExpHeap) + 4) {

        return NULL;
    }

    MEMiHeapHead* pHeapHandle = MEMCreateExpHeapEx(
        addOffset(pHeapStart, sizeof(ExpHeap)),
        nw4r::ut::GetOffsetFromPtr(pHeapStart, pHeapEnd) - sizeof(ExpHeap),
        opt);

    if (pHeapHandle != NULL) {
        Heap* pContainHeap = findContainHeap(pHeapStart);

        pHeap = new (pHeapStart) ExpHeap(pHeapHandle);
        pHeap->registerHeapBuffer(pHeapBuffer);
        pHeap->mParentHeap = pContainHeap;
    }

    return pHeap;
}

ExpHeap* ExpHeap::create(u32 size, Heap* pParentHeap, u16 opt) {
    ExpHeap* pHeap = NULL;

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

void ExpHeap::destroy() {
    Heap* pParentHeap = findParentHeap();

    this->~ExpHeap();
    if (pParentHeap != NULL) {
        pParentHeap->free(this);
    }
}

void* ExpHeap::alloc(u32 size, s32 align) {
    return MEMAllocFromExpHeapEx(mHeapHandle, size, align);
}

void ExpHeap::free(void* pBlock) {
    MEMFreeToExpHeap(mHeapHandle, pBlock);
}

u32 ExpHeap::resizeForMBlock(void* pBlock, u32 size) {
    return MEMResizeForMBlockExpHeap(mHeapHandle, pBlock, size);
}

u32 ExpHeap::getAllocatableSize(s32 align) {
    return MEMGetAllocatableSizeForExpHeapEx(mHeapHandle, align);
}

u32 ExpHeap::adjust() {
    u32 adjustSize = MEMAdjustExpHeap(mHeapHandle) + sizeof(ExpHeap);

    if (adjustSize > sizeof(ExpHeap) && mParentHeap != NULL) {
        mParentHeap->resizeForMBlock(mHeapBuffer, adjustSize);
        return adjustSize;
    }

    return 0;
}

void ExpHeap::initAllocator(Allocator* pAllocator, s32 align) {
    MEMInitAllocatorForExpHeap(pAllocator, mHeapHandle, align);
}

} // namespace EGG
