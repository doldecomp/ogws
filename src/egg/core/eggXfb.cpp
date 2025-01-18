#pragma ipa file

#include "eggXfb.h"
#include "eggSystem.h"
#include "eggVideo.h"
#include "eggHeap.h"
#include "eggAssert.h"

#include "ut_algorithm.h"

using namespace nw4r;

namespace EGG
{
    void Xfb::init(u16 width, u16 height, Heap *heap)
    {
        mWidth = width;
        mHeight = height;

        const u32 bufferSize = calcBufferSize(width, height);
        
        if (!heap)
            heap = Heap::getCurrentHeap();

        mBuffer = new (heap, 32) u8[bufferSize];
        #line 40
        EGG_ASSERT(mBuffer);

        mNext = NULL;
        mPrev = NULL;
    }

    void UNUSED_ASSERTS_EGGXFB()
    {
        EGG_ASSERT_MSG(false, "rm != NULL");
    }

    Xfb::Xfb(Heap *heap)
    {
        Video *video = BaseSystem::getVideo();
        #line 75
        EGG_ASSERT(video != NULL);

        GXRenderModeObj *rm = video->mRenderMode;
        #line 77
        EGG_ASSERT(rm != NULL);

        init(rm->fbWidth, rm->xfbHeight, heap);
    }

    u32 Xfb::calcBufferSize(u16 width, u16 height)
    {
        const u16 new_w = ut::RoundUp(width, 16);
        return (new_w * height * 2);
    }
}