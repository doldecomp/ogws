#include <homeButtonMiniLib.h>

namespace homebutton {

void FrameController::init(int anm_type, f32 max_frame, f32 min_frame,
                           f32 delta) {
    mAnmType = anm_type;
    mMaxFrame = max_frame;
    mMinFrame = min_frame;

    mFrameDelta = delta;
    mState = eState_Stopped;
    mAltFlag = false;

    initFrame();
}

void FrameController::initFrame() {
    mCurFrame = mAnmType == eAnmType_Backward ? mMaxFrame : mMinFrame;
}

void FrameController::calc() {
    if (mState != eState_Playing) {
        return;
    }

    switch (mAnmType) {
    case eAnmType_Forward: {
        if ((mCurFrame += mFrameDelta) >= getLastFrame()) {
            mCurFrame = getLastFrame();
            stop();
        }

        break;
    }

    case eAnmType_Backward: {
        if ((mCurFrame -= mFrameDelta) <= mMinFrame) {
            mCurFrame = mMinFrame;
            stop();
        }

        break;
    }

    case eAnmType_Wrap: {
        if ((mCurFrame += mFrameDelta) >= mMaxFrame)
            mCurFrame -= mMaxFrame - mMinFrame;

        break;
    }

    case eAnmType_Oscillate: {
        if (!mAltFlag) {
            if ((mCurFrame += mFrameDelta) >= getLastFrame()) {
                mCurFrame = getLastFrame();
                mAltFlag = true;
            }
        } else {
            if ((mCurFrame -= mFrameDelta) <= mMinFrame) {
                mCurFrame = mMinFrame;
                mAltFlag = false;
            }
        }

        break;
    }
    }
}

} // namespace homebutton
