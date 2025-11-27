#include <Pack/RPKernel.h>

/**
 * @brief Initializes the animation state
 *
 * @param frameNum Number of frames to animate
 */
void RPSysFrameCtrl::init(s16 frameNum) {
    mPlayMode = EPlayMode_OneTime;
    mFlags = 0;
    mIsEnabled = false;

    mStartFrame = 0;
    mEndFrame = frameNum;
    mLoopFrame = 0;
    mUpdateRate = 1.0f;
    mFrame = 0.0f;
}

/**
 * @brief Updates the animation state
 */
void RPSysFrameCtrl::update() {
    mFlags = 0;

    if (mIsEnabled == true) {
        mFrame += mUpdateRate;
    }

    switch (mPlayMode) {
    case EPlayMode_OneTime: {
        // OneTime finishes once it leaves the (start, end] range
        if (mFrame < mStartFrame) {
            mFrame = mStartFrame;
            mFlags |= EFlag_Finished;
            mIsEnabled = false;
        } else if (mFrame >= mEndFrame) {
            mFrame = mEndFrame;
            mFlags |= EFlag_Finished;
            mIsEnabled = false;
        }
        break;
    }

    case EPlayMode_Loop: {
        s16 remain = mEndFrame - mStartFrame + 1;

        while (mFrame < mStartFrame) {
            s16 frame = 0;
            if (mLoopFrame > 0) {
                frame = remain - mLoopFrame - 1;
            }

            mFlags |= EFlag_Looped;
            mFrame += remain - frame;
        }

        while (mFrame > mEndFrame) {
            mFlags |= EFlag_Looped;
            mFrame -= remain - mLoopFrame;
        }
        break;
    }

    case EPlayMode_Reset: {
        // Reset jumps back once it leaves the (start, end] range
        if (mFrame < mStartFrame) {
            mFrame = mStartFrame;
            mFlags |= EFlag_Finished;
            mIsEnabled = false;
        } else if (mFrame >= mEndFrame) {
            mFrame = mStartFrame;
            mFlags |= EFlag_Finished;
            mIsEnabled = false;
        }
        break;
    }
    }
}
