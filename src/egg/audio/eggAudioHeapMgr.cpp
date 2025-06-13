// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

namespace EGG {

void SoundHeapMgr::createSoundHeap(Heap* pHeap, u32 size) {
    Allocator allocator(pHeap);
    createSoundHeap(&allocator, size);
}

void SoundHeapMgr::createSoundHeap(Allocator* pAllocator, u32 size) {
    if (mHeap.IsValid()) {
        return;
    }

    void* pBuffer = pAllocator->alloc(size);
    mHeap.Create(pBuffer, size);

#line 59
    EGG_ASSERT(mHeap.IsValid());
}

void SoundHeapMgr::destroySoundHeap() {
    mHeap.Destroy();
}

} // namespace EGG
