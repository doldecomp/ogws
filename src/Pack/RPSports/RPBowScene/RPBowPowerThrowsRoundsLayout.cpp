#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Initializes the Power Throws rounds layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowPowerThrowsRoundsLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;
    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgCount_01.brlyt");
    mpRootPane = mpLayout->findPane("RootPane");

    char buf[64];
    PowerThrowsRoundPane* pPane = mAnmPanes;
    for (int i = 0; i < 10; i++, pPane++) {
        sprintf(buf, "N_ball_%02d", i);
        pPane->pane1 = mpLayout->findPane(buf);

        sprintf(buf, "P_check_%02d", i);
        pPane->pane2 = mpLayout->findPane(buf);

        RPSysLytAnmObj** ppAnm = pPane->anmObjs;
        for (int j = 0; j < 4; j++, ppAnm++) {
            sprintf(buf, "bwgCount_01_ballColor_%02d.brlan", j);
            *ppAnm = mpLayout->createAnmObj(NULL, pAcc, buf);
        }
    }

    mAnimationState = 0;
    mpTextBoxes[0][0] = mpLayout->findTextBox("T_text_00");
    mpTextBoxes[0][1] = mpLayout->findTextBox("T_text_01");
    mpTextBoxes[1][0] = mpLayout->findTextBox("T_textS_00");
    mpTextBoxes[1][1] = mpLayout->findTextBox("T_textS_01");
}

/**
 * @brief Resets the layout components and state tracking variables
 */
void RPBowPowerThrowsRoundsLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;

    PowerThrowsRoundPane* pPane = mAnmPanes;
    for (int i = 0; i < 10; i++, pPane++) {
        pPane->activeIdx = -1;
    }
}

/**
 * @brief Updates the scoring text boxes and active animations for current frame
 *
 * @param pContext Bowling scene context
 */
void RPBowPowerThrowsRoundsLayout::Update(SceneContext* pContext) {
    int playerIdx = -pContext->mUnkC34;

    if (mAnimationState == 0 || mAnimationState == 3) {
        if (unk04) {
            mpLayout->startDynAnmIn(playerIdx);
            mAnimationState = 1;
            mpLayout->unbindAllAnmObj();
            mAnmPanes[0].activeIdx = -1;
            mAnmPanes[1].activeIdx = -1;
            mAnmPanes[2].activeIdx = -1;
            mAnmPanes[3].activeIdx = -1;
            mAnmPanes[4].activeIdx = -1;
            mAnmPanes[5].activeIdx = -1;
            mAnmPanes[6].activeIdx = -1;
            mAnmPanes[7].activeIdx = -1;
            mAnmPanes[8].activeIdx = -1;
            mAnmPanes[9].activeIdx = -1;
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!unk04) {
            mpLayout->startDynAnmOut(playerIdx);
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

    PowerThrowsRoundPane* pPane = mAnmPanes;
    for (int i = 0; i < 10; i++, pPane++) {
        s32 anmVal = pContext->unkC60 % 4;

        if (pPane->activeIdx != anmVal) {
            if (pPane->activeIdx >= 0) {
                RPSysLayout::unbindAnmObjToPane(
                    pPane->anmObjs[pPane->activeIdx],
                    pPane->pane1,
                    true
                );
            }

            RPSysLayout::bindAnmObjToPane(pPane->anmObjs[anmVal], pPane->pane1, true);

            RPSysLytAnmObj* pAnm = pPane->anmObjs[anmVal];
            pAnm->setFrame(pAnm->getStartFrame());
            pAnm->setFlags(0);
            pAnm->setEnabled(1);

            pPane->activeIdx = anmVal;
        }
    }

    for (int j = 0; j < 10; j++) {
        PowerThrowsRoundPane* pPaneRev = &mAnmPanes[9 - j];
        if (j < pContext->field_0xC40) {
            pPaneRev->pane1->SetVisible(false);
        } else {
            pPaneRev->pane1->SetVisible(true);
        }
    }

    for (int j = 0; j < 10; j++) {
        PowerThrowsRoundPane* pPaneRev = &mAnmPanes[9 - j];
        if (j < pContext->field_0xC40 && pContext->unkC45[j] != 0) {
            pPaneRev->pane2->SetVisible(true);
        } else {
            pPaneRev->pane2->SetVisible(false);
        }
    }

    s32 score = pContext->unkC50;
    u32 msgIdx = !RPSysStringUtility::IsSingular(score);

    wchar_t buffer[32];
    RPSysStringUtility::GetStringHalfSizeNumber(score, buffer, 32, false);

    mpTextBoxes[msgIdx][0]->setMessage(mpMessage, 0x6720, msgIdx, 1, buffer);
    mpTextBoxes[msgIdx][1]->setMessage(mpMessage, 0x6720, msgIdx, 1, buffer);

    u32 otherIdx = 1 - msgIdx;
    mpTextBoxes[msgIdx][0]->SetVisible(true);
    mpTextBoxes[msgIdx][1]->SetVisible(true);
    mpTextBoxes[otherIdx][0]->SetVisible(false);
    mpTextBoxes[otherIdx][1]->SetVisible(false);

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowPowerThrowsRoundsLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowPowerThrowsRoundsLayout::IsFinished() const {
    return mAnimationState == 0;
}
