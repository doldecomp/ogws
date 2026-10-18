#include <Pack/RPSports/RPBowScene/bowling.h>

extern nw4r::math::VEC2 lbl_803CABF0[2][4];

/**
 * @brief Destructor
 */
RPBowPowerThrowsPinLayout::~RPBowPowerThrowsPinLayout() {}

/**
 * @brief Initializes the Power Throws pin layout
 *
 * @param pAcc Layout resource accessor
 */
void RPBowPowerThrowsPinLayout::Init(RPSysLytResAccessor* pAcc) {
    mpLayout = RPSysLayout::create(NULL, pAcc, "pin_01.brlyt");
    mpRootPane = mpLayout->findPane("RootPane");

    char buf[256];

    for (int i = 0; i < 10; i++) {
        StagePane* pCurrentStage = &mStages[i];
        pCurrentStage->line = NULL;
        pCurrentStage->lineBG = NULL;

        if (i != 0) {
            sprintf(buf, "N_lineBG%02d_00", i + 4);
            pCurrentStage->lineBG = mpLayout->findPane(buf);

            sprintf(buf, "N_line%02d_00", i + 4);
            pCurrentStage->line = mpLayout->findPane(buf);
        }

        sprintf(buf, "pin_01_stage_%02d.brlan", i);
        pCurrentStage->stageAnm = mpLayout->createAnmObj(NULL, pAcc, buf);
    }

    for (int i = 0; i < 91; i++) {
        sprintf(buf, "P_pin_%02d", i);
        mpPins[i] = mpLayout->findPane(buf);
    }

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and animation objects
 */
void RPBowPowerThrowsPinLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
}

/**
 * @brief Updates the pin layout logic for the Power Throws mode
 *
 * @param pContext Bowling scene context
 */
void RPBowPowerThrowsPinLayout::Update(SceneContext* pContext) {
    if (mAnimationState == 0 || mAnimationState == 3) {
        if (mUnk4) {
            mpLayout->startDynAnmIn(0);
            mAnimationState = 1;
            mpLayout->unbindAllAnmObj();

            mpLayout->bindAnmObj(mStages[pContext->field_0xC38].stageAnm);

            RPSysLytAnmObj* pTempAnm = mStages[pContext->field_0xC38].stageAnm;
            s16 startFrame = pTempAnm->getStartFrame();
            pTempAnm->setFrame((float)startFrame);
            pTempAnm->setFlags(0);
            pTempAnm->setEnabled(1);
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!mUnk4) {
            mpLayout->startDynAnmOut(0);
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

    for (int i = 0; i < 10; i++) {
        if (mStages[i].lineBG != NULL) {
            mStages[i].lineBG->SetVisible(i < pContext->field_0xC38);
        }
        if (mStages[i].line != NULL) {
            mStages[i].line->SetVisible(i < pContext->field_0xC38);
        }
    }

    for (int i = 0; i < 91; i++) {
        if (pContext->pinStatus.pinBits[i / 30] & (1 << (i % 30))) {
            mpPins[i]->SetVisible(true);
        } else {
            mpPins[i]->SetVisible(false);
        }
    }

    int tvIdx = (EGG::Screen::GetTVMode() != EGG::Screen::TV_MODE_STD);
    int typeIdx = pContext->mUnkC1C;

    f32* pFloats = (f32*)lbl_803CABF0[tvIdx];
    volatile f32 dummyX = pFloats[typeIdx * 2];
    volatile f32 dummyY = pFloats[typeIdx * 2 + 1];

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowPowerThrowsPinLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowPowerThrowsPinLayout::IsFinished() const {
    return mAnimationState == 0;
}
