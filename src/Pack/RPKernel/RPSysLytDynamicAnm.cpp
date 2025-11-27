#include <Pack/RPKernel.h>

#include <egg/math.h>

#include <nw4r/lyt.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

const f32* RPSysLytDynamicAnm::lbl_804BF588 = NULL;
const f32 RPSysLytDynamicAnm::lbl_804C1750[] = {12625.324f, 1.7388418E-19f};

/**
 * @brief Constructor
 *
 * @param pParent Parent pane
 * @param direction Animation direction
 * @param frameNum Number of frames to animate
 */
RPSysLytDynamicAnm::RPSysLytDynamicAnm(nw4r::lyt::Pane* pParent,
                                       EDirection direction, s16 frameNum) {
    mpParent = pParent;
    mAlpha = mpParent->GetAlpha();

    const nw4r::math::VEC3& rParentPos = mpParent->GetTranslate();
    mStartPos.set(rParentPos.x, rParentPos.y, rParentPos.z);
    mNowPos.set(mStartPos.x, mStartPos.y, mStartPos.z);

    mEndFrame = frameNum;
    mStartFrame = 0;
    mDirection = direction;

    // Need to recalculate target position
    // TODO(kiwi) Surely this is an inline, but I can't get it to work
    EGG::Vector3f delta(0.0f, 0.0f, 0.0f);
    f32 width = static_cast<f32>(RPGrpScreen::GetSizeXMax());
    f32 height = static_cast<f32>(RPGrpScreen::GetSizeYMax());

    switch (direction) {
    case EDirection_Up: {
        delta.set(0.0f, height, 0.0f);
        break;
    }

    case EDirection_Down: {
        delta.set(0.0f, -height, 0.0f);
        break;
    }

    case EDirection_Left: {
        delta.set(-width, 0.0f, 0.0f);
        break;
    }

    case EDirection_Right: {
        delta.set(width, 0.0f, 0.0f);
        break;
    }

    default: {
        break;
    }
    }

    mNowPos = mStartPos + delta;
    reset();

    lbl_804BF588 = lbl_804C1750;
}

/**
 * @brief Resets the dynamic animation
 */
void RPSysLytDynamicAnm::reset() {
    mState = EState_FinishOut;
    mNextState = EState_None;
    mFrame = 0;
    mStartFrame = 0;

    mpParent->SetAlpha(0);
    mpParent->SetTranslate(mNowPos);
}

/**
 * @brief Flips the horizontal direction of the animation
 * @note If the animation has a vertical direction, this function will never
 * reverse it.
 *
 * @param reverse Whether to reverse the horizontal direction
 */
void RPSysLytDynamicAnm::reverseAnmHDirection(bool reverse) {
    EDirection reverseDir = mDirection;

    if (reverse) {
        switch (reverseDir) {
        case EDirection_Left: {
            reverseDir = EDirection_Right;
            break;
        }

        case EDirection_Right: {
            reverseDir = EDirection_Left;
            break;
        }

        // This function only flips horizontally
        default: {
            break;
        }
        }
    }

    // Need to recalculate target position
    EGG::Vector3f delta(0.0f, 0.0f, 0.0f);
    f32 width = static_cast<f32>(RPGrpScreen::GetSizeXMax());
    f32 height = static_cast<f32>(RPGrpScreen::GetSizeYMax());

    switch (reverseDir) {
    case EDirection_Up: {
        delta.set(0.0f, height, 0.0f);
        break;
    }

    case EDirection_Down: {
        delta.set(0.0f, -height, 0.0f);
        break;
    }

    case EDirection_Left: {
        delta.set(-width, 0.0f, 0.0f);
        break;
    }

    case EDirection_Right: {
        delta.set(width, 0.0f, 0.0f);
        break;
    }

    default: {
        break;
    }
    }

    mNowPos = mStartPos + delta;
}

/**
 * @brief Starts playing the animation inwards
 * @details The pane will move opposite the animation direction until it
 * is back at its original position.
 *
 * @param frame Starting frame (-1 to play from the ending frame)
 */
void RPSysLytDynamicAnm::startAnmIn(s16 frame) {
    mNextState = EState_StartIn;

    if (frame >= 0) {
        mStartFrame = frame;
    } else {
        mStartFrame = mEndFrame;
    }
}

/**
 * @brief Starts playing the animation outwards
 * @details The pane will move in the animation direction until it is no
 * longer visible.
 *
 * @param frame Starting frame (-1 to play from the ending frame)
 */
void RPSysLytDynamicAnm::startAnmOut(s16 frame) {
    mNextState = EState_StartOut;

    if (frame >= 0) {
        mStartFrame = frame;
    } else {
        mStartFrame = mEndFrame;
    }
}

/**
 * @brief Updates the dynamic animation
 */
void RPSysLytDynamicAnm::calc() {
    s16 next = mNextState;

    if (next != EState_None) {
        mState = next;
        mNextState = EState_None;

        switch (next) {
        case EState_StartIn:
        case EState_StartOut: {
            mFrame = mStartFrame;
            break;
        }

        default: {
            mFrame = 0;
            break;
        }
        }

        mStartFrame = 0;
    }

    switch (mState) {
    case EState_StartIn: {
        mFrame++;

        if (mFrame < mEndFrame) {
            f32 target, amount;

            amount = static_cast<f32>(mFrame) / static_cast<f32>(mEndFrame);
            if (amount <= 0.0f) {
                target = 0.0f;
            } else if (amount >= 1.0f) {
                target = 1.0f;
            } else {
                f32 rad = NW4R_MATH_PI * (amount - 0.5f);
                target = nw4r::math::SinRad(rad) * 0.5f + 0.5f;
            }

            mpParent->SetTranslate(mNowPos * (1.0f - target) +
                                   mStartPos * target);
            mpParent->SetAlpha(mAlpha * amount);

        } else {
            mNextState = EState_FinishIn;
            mpParent->SetTranslate(mStartPos);
            mpParent->SetAlpha(mAlpha);
        }
        break;
    }

    case EState_StartOut: {
        mFrame++;

        if (mFrame < mEndFrame) {
            f32 amount, target;

            amount = static_cast<f32>(mFrame) / static_cast<f32>(mEndFrame);
            if (amount <= 0.0f) {
                target = 0.0f;
            } else if (amount >= 1.0f) {
                target = 1.0f;
            } else {
                f32 rad = NW4R_MATH_PI * (amount - 0.5f);
                target = nw4r::math::SinRad(rad) * 0.5f + 0.5f;
            }

            mpParent->SetTranslate(mNowPos * target +
                                   mStartPos * (1.0f - target));
            mpParent->SetAlpha(mAlpha * (1.0f - amount));

        } else {
            mNextState = EState_FinishOut;
            mpParent->SetTranslate(mNowPos);
            mpParent->SetAlpha(0);
        }
        break;
    }

    case EState_FinishOut:
    case EState_FinishIn:
    default: {
        break;
    }
    }
}
