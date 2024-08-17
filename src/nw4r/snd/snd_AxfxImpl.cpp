#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

AxfxImpl* AxfxImpl::mCurrentFx = NULL;
u32 AxfxImpl::mAllocatedSize = 0;

bool AxfxImpl::CreateHeap(void* buffer, u32 size) {
    mHeap = MEMCreateFrmHeap(buffer, size);
    return mHeap != NULL;
}

void AxfxImpl::DestroyHeap() {
    if (mHeap != NULL) {
        MEMDestroyFrmHeap(mHeap);
    }
}

void AxfxImpl::HookAlloc(AXFXAllocHook* allocHook, AXFXFreeHook* freeHook) {
    AXFXGetHooks(allocHook, freeHook);
    AXFXSetHooks(Alloc, Free);
    mCurrentFx = this;
}

void AxfxImpl::RestoreAlloc(AXFXAllocHook allocHook, AXFXFreeHook freeHook) {
    AXFXSetHooks(allocHook, freeHook);
    mCurrentFx = NULL;
}

void* AxfxImpl::Alloc(u32 size) {
    void* block = MEMAllocFromFrmHeap(mCurrentFx->mHeap, size);

    mCurrentFx->mAllocCount++;
    mAllocatedSize += ut::RoundUp(size, 4);

    return block;
}

void AxfxImpl::Free(void* block) {
    if (mCurrentFx->mAllocCount != 0) {
        mCurrentFx->mAllocCount--;
    }

    if (mCurrentFx->mAllocCount == 0) {
        MEMFreeToFrmHeap(mCurrentFx->mHeap, MEM_FRM_HEAP_FREE_ALL);
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
