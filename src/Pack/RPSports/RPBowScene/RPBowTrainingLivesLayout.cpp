#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Destructor
 */
RPBowTrainingLivesLayout::~RPBowTrainingLivesLayout() {}

/**
 * @brief Initializes the training lives layout
 *
 * @param pAcc Layout resource accessor
 */
void RPBowTrainingLivesLayout::Init(RPSysLytResAccessor* pAcc) {
    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgCount_00.brlyt");
    mpRootPane = mpLayout->findPane("RootPane");

    char buf[64];
    TrainingLifePane* pPane = mAnmPanes;
    for (int i = 0; i < 5; i++, pPane++) {
        pPane->bigBallObj = mpLayout->createAnmObj(NULL, pAcc, "bwgCount_00_bigBall_00.brlan");
        pPane->smallBallObj = mpLayout->createAnmObj(NULL, pAcc, "bwgCount_00_smallBall_00.brlan");

        sprintf(buf, "N_ball_%02d", i);
        pPane->pane = mpLayout->findPane(buf);

        for (int j = 0; j < 5; j++) {
            sprintf(buf, "bwgCount_00_ballColor_%02d.brlan", j);
            pPane->colors[j] = mpLayout->createAnmObj(NULL, pAcc, buf);
        }
    }

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and animation objects
 */
void RPBowTrainingLivesLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;

    mAnmPanes[0].activeIdx2 = -1;
    mAnmPanes[0].activeIdx1 = -1;
    mAnmPanes[1].activeIdx2 = -1;
    mAnmPanes[1].activeIdx1 = -1;
    mAnmPanes[2].activeIdx2 = -1;
    mAnmPanes[2].activeIdx1 = -1;
    mAnmPanes[3].activeIdx2 = -1;
    mAnmPanes[3].activeIdx1 = -1;
    mAnmPanes[4].activeIdx2 = -1;
    mAnmPanes[4].activeIdx1 = -1;
}

// Global lookup array referenced for scaling
extern nw4r::math::VEC2 lbl_803CADA8[2][2];

/**
 * @brief Updates the training lives logic and pane states
 *
 * @param pContext Bowling scene context
 */
void RPBowTrainingLivesLayout::Update(SceneContext* pContext) {
    int playerIdx = -pContext->mUnkC34;

    if (mAnimationState == 0 || mAnimationState == 3) {
        if (mUnk4) {
            mpLayout->startDynAnmIn((short)playerIdx);
            mAnimationState = 1;
            mpLayout->unbindAllAnmObj();

            mAnmPanes[0].activeIdx2 = -1;
            mAnmPanes[0].activeIdx1 = -1;
            mAnmPanes[1].activeIdx2 = -1;
            mAnmPanes[1].activeIdx1 = -1;
            mAnmPanes[2].activeIdx2 = -1;
            mAnmPanes[2].activeIdx1 = -1;
            mAnmPanes[3].activeIdx2 = -1;
            mAnmPanes[3].activeIdx1 = -1;
            mAnmPanes[4].activeIdx2 = -1;
            mAnmPanes[4].activeIdx1 = -1;
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

    TrainingLifePane* pPaneBase = mAnmPanes;
    TrainingLifePane* pPane = pPaneBase;

    for (int i = 0; i < 5; i++, pPane++) {
        s32 anmVal1 = 1;
        if (i == pContext->field_0xC40) {
            anmVal1 = 0;
        }

        if (pPane->activeIdx1 != anmVal1) {
            if (pPane->activeIdx1 >= 0) {
                RPSysLayout::unbindAnmObjToPane(
                    ((RPSysLytAnmObj**)pPane)[pPane->activeIdx1],
                    pPane->pane, true);
            }

            RPSysLayout::bindAnmObjToPane(((RPSysLytAnmObj**)pPane)[anmVal1], pPane->pane, true);

            s16 len = ((RPSysLytAnmObj**)pPane)[anmVal1]->getStartFrame();
            ((RPSysLytAnmObj**)pPane)[anmVal1]->setFrame(len);
            ((RPSysLytAnmObj**)pPane)[anmVal1]->setFlags(0);
            ((RPSysLytAnmObj**)pPane)[anmVal1]->setEnabled(1);

            pPane->activeIdx1 = anmVal1;
        }
    }

    for (int j = 0; j < 5; j++, pPaneBase++) {
        s32 anmVal2;
        if (j < pContext->field_0xC40) {
            anmVal2 = 0;
        } else {
            anmVal2 = (pContext->unkC60 % 4) + 1;
        }

        if (pPaneBase->activeIdx2 != anmVal2) {
            if (pPaneBase->activeIdx2 >= 0) {
                RPSysLayout::unbindAnmObjToPane(
                    pPaneBase->colors[pPaneBase->activeIdx2],
                    pPaneBase->pane,
                    true
                );
            }

            RPSysLayout::bindAnmObjToPane(pPaneBase->colors[anmVal2], pPaneBase->pane, true);

            s16 len2 = pPaneBase->colors[anmVal2]->getStartFrame();
            pPaneBase->colors[anmVal2]->setFrame(len2);
            pPaneBase->colors[anmVal2]->setFlags(0);
            pPaneBase->colors[anmVal2]->setEnabled(1);

            pPaneBase->activeIdx2 = anmVal2;
        }
    }

    int tvIdx = (EGG::Screen::GetTVMode() != EGG::Screen::TV_MODE_STD);
    int typeIdx = pContext->mUnkC1C;

    f32* pFloats = (f32*)lbl_803CADA8[tvIdx];
    volatile f32 dummyX = pFloats[typeIdx * 2];
    volatile f32 dummyY = pFloats[typeIdx * 2 + 1];

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowTrainingLivesLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowTrainingLivesLayout::IsFinished() const {
    return mAnimationState == 0;
}
