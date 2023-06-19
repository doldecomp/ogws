#pragma ipa file
#include "eggAudioHeapMgr.h"
#include "eggAllocator.h"
#include "eggAssert.h"

namespace EGG
{
    void SoundHeapMgr::createSoundHeap(Heap *heap, u32 r5)
    {
        Allocator a = Allocator(heap, 32);
        createSoundHeap(&a, r5);
    }

    void SoundHeapMgr::createSoundHeap(Allocator *a, u32 r5)
    {
        if (!mHeap.IsValid())
        {
            void *heapBuf = a->alloc(r5);
            mHeap.Create(heapBuf, r5);

            #line 59
            EGG_ASSERT(mHeap.IsValid());
        }
    }

    void SoundHeapMgr::destroySoundHeap()
    {
        mHeap.Destroy();
    }
}