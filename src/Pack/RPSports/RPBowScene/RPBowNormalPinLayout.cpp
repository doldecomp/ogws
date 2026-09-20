#include <Pack/RPSports/RPBowScene/bowling.h>

extern nw4r::math::VEC2 lbl_803CAB88[2][2];

/**
 * @brief Destructor
 */
RPBowNormalPinLayout::~RPBowNormalPinLayout() {}

/**
 * @brief Initializes the normal pin layout
 *
 * @param pAcc Layout resource accessor
 */
void RPBowNormalPinLayout::Init(RPSysLytResAccessor* pAcc) {
    mpLayout = RPSysLayout::create(NULL, pAcc, "pin_00.brlyt");
    mpRootPane = mpLayout->findPane("RootPane");

    char buf[64];

    for (int i = 0; i < 10; i++) {
        sprintf(buf, "N_pin%02d_00", i + 1);
        mpPinPanes[i] = mpLayout->findPane(buf);
    }

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and animation state
 */
void RPBowNormalPinLayout::Reset() {
    mpLayout->reset();
    mAnimationState = 0;
}

/**
 * @brief Updates the pin layout logic and animations for the current frame
 *
 * @param pContext Bowling scene context
 */
void RPBowNormalPinLayout::Update(SceneContext* pContext) {
    int typeIdx = pContext->mUnkC1C;

    if (pContext->mUnkC44 != 0) {
        typeIdx = 0;
    }

    bool revAnm = false;
    if (typeIdx != 0) {
        if (pContext->mUnk34 != 0) {
            revAnm = true;
        }
    }

    int playerIdx = -pContext->mUnkC34;
    mpLayout->reverseAnmHDirection(revAnm);

    if (mAnimationState == 0 || mAnimationState == 3) {
        if (mUnk4) {
            mpLayout->startDynAnmIn((short)playerIdx);
            mAnimationState = 1;
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!mUnk4) {
            mpLayout->startDynAnmOut((short)playerIdx);
            mAnimationState = 3;
        }
    }

    if (mAnimationState == 1) {
        if (mpLayout->isFinishedDynAnmIn()) {
            mAnimationState = 2;
        }
    }

    if (mAnimationState == 3) {
        if (mpLayout->isFinishedDynAnmOut()) {
            mAnimationState = 0;
        }
    }

    u32* pPinBits = pContext->pinStatus.pinBits;
    for (int i = 0; i < 10; i++) {
        if (pPinBits[i / 30] & (1 << (i % 30))) {
            mpPinPanes[i]->SetVisible(true);
        } else {
            mpPinPanes[i]->SetVisible(false);
        }
    }

    int tvIdx = (EGG::Screen::GetTVMode() != EGG::Screen::TV_MODE_STD);
    f32* pFloats = (f32*)lbl_803CAB88[tvIdx];

    f32 x = pFloats[typeIdx * 2];
    f32 y = pFloats[typeIdx * 2 + 1];

    nw4r::math::VEC2 pos(x, y);
    nw4r::math::VEC3 trans(pos.x, pos.y, 0.0f);

    mpRootPane->SetTranslate(trans);
    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowNormalPinLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowNormalPinLayout::IsFinished() const {
    return mAnimationState == 0;
}
