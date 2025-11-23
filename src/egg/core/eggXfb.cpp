// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

void Xfb::init(u16 width, u16 height, Heap* pHeap) {
    mWidth = width;
    mHeight = height;

    u32 bufferSize = calcBufferSize(width, height);

    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    mBuffer = new (pHeap, 32) u8[bufferSize];
#line 40
    EGG_ASSERT(mBuffer);

    mNext = NULL;
    mPrev = NULL;
}

DECOMP_FORCEACTIVE(eggXfb_cpp,
                  "rm != NULL");

Xfb::Xfb(Heap* pHeap) {
    Video* video = BaseSystem::getVideo();
#line 75
    EGG_ASSERT(video != NULL);

    GXRenderModeObj* rm = video->getRenderModeObj();
#line 77
    EGG_ASSERT(rm != NULL);

    init(rm->fbWidth, rm->xfbHeight, pHeap);
}

u32 Xfb::calcBufferSize(u16 width, u16 height) {
    width = ROUND_UP(width, 16);
    return width * height * sizeof(u16);
}

} // namespace EGG
