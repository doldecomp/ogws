// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace EGG {

bool XfbManager::attach(Xfb* pXfb) {
    bool success = false;

    if (pXfb != NULL) {
        if (mQueueFront == NULL) {
            mQueueFront = pXfb;
            mQueueEnd = pXfb;
            pXfb->mPrev = pXfb;
            pXfb->mNext = pXfb;
        } else {
            mQueueFront->mNext->mPrev = pXfb;
            pXfb->mNext = mQueueFront->mNext;

            mQueueFront->mNext = pXfb;
            pXfb->mPrev = mQueueFront;

            mQueueEnd = mQueueFront->mPrev;
        }

        success = true;
    }

    return success;
}

void XfbManager::copyEFB(bool clearEfb) {
    if (clearEfb) {
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
        GXSetAlphaUpdate(GX_TRUE);
        GXSetColorUpdate(GX_TRUE);
    }

    GXCopyDisp(mQueueEnd->getBuffer(), clearEfb);
    GXFlush();

    mShowXfb = mQueueEnd;
    mQueueEnd = mQueueEnd->mPrev;
}

void XfbManager::setNextFrameBuffer() {
    BOOL enabled = OSDisableInterrupts();

    if (mShowXfb != NULL) {
        VISetNextFrameBuffer(mShowXfb->getBuffer());
        VIFlush();

        mCopiedXfb = mShowXfb;
        mShowXfb = NULL;
    }

    OSRestoreInterrupts(enabled);
}

void XfbManager::postVRetrace() {
    if (mCopiedXfb == NULL) {
        return;
    }

    if (mCopiedXfb->getBuffer() == VIGetCurrentFrameBuffer()) {
        mQueueFront = mCopiedXfb;
        mCopiedXfb = NULL;
    }
}

} // namespace EGG
