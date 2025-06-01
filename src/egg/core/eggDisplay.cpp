// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace EGG {

Display::Display(u8 frameRate)
    : mFrameRate(frameRate),
      mRetraceCount(0),
      mFrameCount(0),
      mClearColor(nw4r::ut::Color::GRAY),
      mClearZ(GX_CLEAR_Z_MAX),
      mPrevFrameTick(0) {

    mEfbFlags.setBit(BIT_EFB_COPY_CLEAR);
}

void Display::syncVRetrace(u8 frameRate) {
    // Retraces waited so far for the next frame
    u32 waitForFrame = VIGetRetraceCount() - mRetraceCount;

    do {
        // Show the next XFB when the frame is ready
        if (waitForFrame >= frameRate - 1) {
            if (mXfbFlags.onBit(BIT_XFB_CHANGE_BLACK)) {
                BaseSystem::getVideo()->changeBlack();
                mXfbFlags.resetBit(BIT_XFB_CHANGE_BLACK);
            }

            BaseSystem::getXfbManager()->setNextFrameBuffer();
        }

        VIWaitForRetrace();
    } while (++waitForFrame < frameRate);

    calcFrequency();

    mRetraceCount = VIGetRetraceCount();
    mFrameCount++;
}

u32 Display::getTickPerFrame() {
    return Video::getTickPerVRetrace();
}

void Display::beginFrame() {
    syncVRetrace(mFrameRate);
}

void Display::beginRender() {}

void Display::endRender() {
    copyEFBtoXFB();
}

void Display::endFrame() {
    GXDrawDone();
}

void Display::copyEFBtoXFB() {
    if (mEfbFlags.onBit(BIT_EFB_COPY_CLEAR)) {
        GXSetCopyClear(mClearColor, mClearZ);
    }

    const GXRenderModeObj* pObj = BaseSystem::getVideo()->getRenderModeObj();
#line 150
    EGG_ASSERT(pObj != NULL);

    GXSetCopyFilter(pObj->aa, pObj->sample_pattern, !pObj->aa, pObj->vfilter);

    bool clearEfb = mEfbFlags.onBit(BIT_EFB_COPY_CLEAR);
    BaseSystem::getXfbManager()->copyEFB(clearEfb);
}

void Display::calcFrequency() {
    s32 nowFrameTick = OSGetTick();
    mFrameCostTick = nowFrameTick - mPrevFrameTick;

    mFrequency = 1000000.0f / OS_TICKS_TO_USEC(mFrameCostTick);
    mPrevFrameTick = nowFrameTick;
}

} // namespace EGG
