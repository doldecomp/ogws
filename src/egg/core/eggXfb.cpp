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
        #line 48
        EGG_ASSERT(mBuffer);

        XFB_0xC = NULL;
        XFB_0x8 = NULL;
    }

    // The strings  aren't ordered correctly
    // "rm != NULL" must come before "video != NULL" in the pool.
    #ifdef __DECOMP_NON_MATCHING
    Xfb::Xfb(Heap *heap)
    {
        Video *video = BaseSystem::getVideo();
        #line 75
        EGG_ASSERT(video != NULL);
        GXRenderModeObj *rm = video->mRenderMode;
        EGG_ASSERT(rm != NULL);

        init(rm->mFbWidth, rm->mEfbHeight, heap);
    }
    #else
    #error This file has yet to be decompiled accurately. Use "eggXfb.s" instead.
    #endif

    UNKWORD Xfb::calcBufferSize(u16 width, u16 height)
    {
        return (ut::RoundUp(width, 16) * height * 2);
    }
}