#pragma ipa file
#include "eggXfb.h"
#include "eggSystem.h"
#include "eggVideo.h"
#include "eggHeap.h"
#include "eggAssert.h"
#include "ut_algorithm.h"

namespace EGG
{
    using namespace nw4r;

    void Xfb::init(u16 width, u16 height, Heap *heap)
    {
        mWidth = width;
        mHeight = height;

        UNKWORD bufSize = calcBufferSize(width, height);
        if (!heap) heap = Heap::sCurrentHeap;

        mBuffer = new (heap, 32) char[bufSize];
        #line 40
        EGG_ASSERT(mBuffer);

        XFB_0xC = NULL;
        XFB_0x8 = NULL;
    }

    // Force string pool ordering by creating an instance of "rm != NULL"
    void UNUSED()
    {
        GXRenderModeObj *rm;
        EGG_ASSERT(rm != NULL);
    }

    Xfb::Xfb(Heap *heap)
    {
        Video *video = BaseSystem::getVideo();
        #line 75
        EGG_ASSERT(video != NULL);
        GXRenderModeObj *rm = video->mRenderMode;
        EGG_ASSERT(rm != NULL);

        init(rm->mFbWidth, rm->mFbHeight, heap);
    }

    UNKWORD Xfb::calcBufferSize(u16 width, u16 height)
    {
        u16 round = ut::RoundUp(width, 16);
        return (round * height * 2);
    }
}