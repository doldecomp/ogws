// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/MEM.h>
#include <revolution/OS.h>

namespace EGG {

Heap* Heap::sCurrentHeap = NULL;

nw4r::ut::List Heap::sHeapList;
BOOL Heap::sIsHeapListInitialized = false;
OSMutex Heap::sRootMutex;

Heap* Heap::sAllocatableHeap = NULL;

void Heap::initialize() {
    NW4R_UT_LIST_INIT(sHeapList, Heap);
    OSInitMutex(&sRootMutex);
    sIsHeapListInitialized = TRUE;
}

Heap::Heap(MEMiHeapHead* pHeapHandle)
    : mHeapHandle(pHeapHandle), mHeapBuffer(NULL), mParentHeap(NULL) {

    NW4R_UT_LIST_INIT(mDisposerList, Disposer);

#line 63
    EGG_ASSERT_MSG(sIsHeapListInitialized, "Please call Heap::initialize()");

    OSLockMutex(&sRootMutex);
    nw4r::ut::List_Append(&sHeapList, this);
    OSUnlockMutex(&sRootMutex);
}

Heap::~Heap() {
    OSLockMutex(&sRootMutex);
    nw4r::ut::List_Remove(&sHeapList, this);
    OSUnlockMutex(&sRootMutex);
}

void* Heap::alloc(u32 size, int align, Heap* pHeap) {
    void* pBlock = NULL;

    if (sAllocatableHeap != NULL) {
        if (sCurrentHeap != NULL && pHeap == NULL) {
            pHeap = sCurrentHeap;
        }

        if (pHeap != sAllocatableHeap) {
#line 97
            EGG_ASSERT_MSG(false, "cannot allocate from heap %x : %x\n", pHeap,
                           sAllocatableHeap);

            return NULL;
        }
    }

    if (pHeap != NULL) {
        return pHeap->alloc(size, align);
    }

    if (sCurrentHeap != NULL) {
        pBlock = sCurrentHeap->alloc(size, align);

        if (pBlock == NULL) {
            // clang-format off
            EGG_PRINT("heap (%p):(%.1fMBytes) size(%d:%.1fMBytes)\n",
                      sCurrentHeap,
                      sCurrentHeap->getTotalSize() / (1024.0f * 1024.0f),
                      size,
                      size  / (1024.0f * 1024.0f));
            // clang-format on
        }

        return pBlock;
    }

#line 129
    EGG_ASSERT_MSG(false, "cannot allocate %d from heap %x\n", size, pHeap);
    return NULL;
}

Heap* Heap::findHeap(MEMiHeapHead* pHeapHandle) {
    Heap* pContainHeap = NULL;
    OSLockMutex(&sRootMutex);

    if (sIsHeapListInitialized) {
        NW4R_UT_LIST_FOREACH(Heap, it, sHeapList, {
            if (it->mHeapHandle == pHeapHandle) {
                pContainHeap = it;
                break;
            }
        });
    }

    OSUnlockMutex(&sRootMutex);
    return pContainHeap;
}

Heap* Heap::findParentHeap() {
#line 173
    EGG_ASSERT(mHeapHandle != NULL);

    return mParentHeap;
}

Heap* Heap::findContainHeap(const void* pBlock) {
    Heap* pContainHeap = NULL;
    MEMiHeapHead* pHeapHandle = MEMFindContainHeap(pBlock);

    if (pHeapHandle != NULL) {
        pContainHeap = findHeap(pHeapHandle);
    }

    return pContainHeap;
}

void Heap::free(void* pBlock, Heap* pHeap) {
    if (pHeap == NULL) {
        MEMiHeapHead* pHeapHandle = MEMFindContainHeap(pBlock);
        if (pHeapHandle == NULL) {
            return;
        }

        pHeap = findHeap(pHeapHandle);
        if (pHeap == NULL) {
            return;
        }
    }

    pHeap->free(pBlock);
}

void Heap::dispose() {
    Disposer* pDisposer = NULL;

    while ((pDisposer = static_cast<Disposer*>(
                nw4r::ut::List_GetFirst(&mDisposerList))) != NULL) {

        pDisposer->~Disposer();
    }
}

Heap* Heap::becomeCurrentHeap() {
#line 328
    EGG_ASSERT(this != NULL);

    OSLockMutex(&sRootMutex);

    Heap* pOldHeap = sCurrentHeap;
    sCurrentHeap = this;

    OSUnlockMutex(&sRootMutex);
    return pOldHeap;
}

} // namespace EGG

void* operator new(size_t size) {
    return EGG::Heap::alloc(size, 4, NULL);
}

void* operator new(size_t size, EGG::Heap* pHeap, int align) {
    return EGG::Heap::alloc(size, align, pHeap);
}

void* operator new[](size_t size) {
    return EGG::Heap::alloc(size, 4, NULL);
}

void* operator new[](size_t size, int align) {
    return EGG::Heap::alloc(size, align, NULL);
}

void* operator new[](size_t size, EGG::Heap* pHeap, int align) {
    return EGG::Heap::alloc(size, align, pHeap);
}

void operator delete(void* pBlock) {
    EGG::Heap::free(pBlock, NULL);
}

void operator delete[](void* pBlock) {
    EGG::Heap::free(pBlock, NULL);
}
