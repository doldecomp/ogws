#include <Pack/RPSports/RPBowScene/bowling.h>
#include <Pack/RPSystem/RPSysResourceManager.h>

// --------------------

/**
 * @brief Initializes the guidance layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowGuidanceLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgText_00.brlyt");

    mpAnm1 = mpLayout->createAnmObj(NULL, pAcc, "bwgText_00_in_00.brlan");
    mpAnm2 = mpLayout->createAnmObj(NULL, pAcc, "bwgText_00_out_00.brlan");

    mpPane1 = mpLayout->findPane("P_tutorial_01");
    mpTextBox1 = mpLayout->findTextBox("T_exp_00");

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowGuidanceLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
    mFlag28 = 1;
}

// void fn_80352ED8()

/**
 * @brief Draws the layout
 */
void RPBowGuidanceLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowGuidanceLayout::IsFinished() const {
    return mAnimationState == 0;
}

// --------------------

/**
 * @brief Initializes the event text layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowEventTextLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgText_01.brlyt");

    mpTextBoxes[0][0] = mpLayout->findTextBox("T_text_00");
    mpTextBoxes[0][1] = mpLayout->findTextBox("T_text_01");
    mpTextBoxes[1][0] = mpLayout->findTextBox("T_textS_00");
    mpTextBoxes[1][1] = mpLayout->findTextBox("T_textS_01");

    mpAnm1 = mpLayout->createAnmObj(NULL, pAcc, "bwgText_01_in_00.brlan");
    mpAnm2 = mpLayout->createAnmObj(NULL, pAcc, "bwgText_01_in_00.brlan");

    mpPane1 = mpLayout->findPane("N_text_00");
    mpPane2 = mpLayout->findPane("N_textS_00");

    mpTextBox5 = mpLayout->findTextBox("T_double_00");
    mpTextBox6 = mpLayout->findTextBox("T_double_01");

    mpAnm3 = mpLayout->createAnmObj(NULL, pAcc, "bwgText_01_in_00.brlan");

    mpPane3 = mpLayout->findPane("N_double_00");
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowEventTextLayout::Reset() {
    mpLayout->reset();
    mAnimationState = 0;
    mpLayout->unbindAllAnmObj();
    mField48 = 0;
}

/**
 * @brief Updates the event text animation each frame
 *
 * @param pContext Bowling scene context
 */
void RPBowEventTextLayout::Update(SceneContext* pContext) {
    if (mAnimationState == 0 || mAnimationState == 3) {
        if (unk04) {
            mpLayout->unbindAllAnmObj();
            mpLayout->bindAnmObjToPane(mpAnm1, mpPane1, true);
            mpLayout->bindAnmObjToPane(mpAnm2, mpPane2, true);

            RPSysLytAnmObj* pTempAnm1 = mpAnm1;
            bool isC55 = pContext->mUnkC55;

            pTempAnm1->setFrame(pTempAnm1->getStartFrame());
            pTempAnm1->setFlags(0);
            pTempAnm1->setEnabled(1);

            RPSysLytAnmObj* pTempAnm2 = mpAnm2;
            pTempAnm2->setFrame(pTempAnm2->getStartFrame());
            pTempAnm2->setFlags(0);
            pTempAnm2->setEnabled(1);

            if (isC55) {
                mpLayout->bindAnmObjToPane(mpAnm3, mpPane3, true);

                RPSysLytAnmObj* pTempAnm3 = mpAnm3;
                pTempAnm3->setFrame(pTempAnm3->getStartFrame());
                pTempAnm3->setFlags(0);
                pTempAnm3->setEnabled(1);

                mpPane3->SetVisible(true);
            } else {
                mpPane3->SetVisible(false);
            }

            mAnimationState = 1;
            mField48 = 0;
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!unk04) {
            mAnimationState = 0;
        }
    }

    if (mAnimationState == 1) {
        if (mpAnm1->isFinished() && mpAnm2->isFinished()) {
            mAnimationState = 2;
        }
    }

    s32 fieldC3C = pContext->field_0xC3C;
    bool bActive;

    if (fieldC3C == -1) {
        bActive = true;
        mpTextBoxes[1][0]->setMessage(mpMessage, 0x659C, 0, 0);
        mpTextBoxes[1][1]->setMessage(mpMessage, 0x659C, 0, 0);
    } else {
        bActive = true;
        s32 pluralOffset = !RPSysStringUtility::IsSingular(fieldC3C) + 2;

        wchar_t buffer[32];
        RPSysStringUtility::GetStringHalfSizeNumber(fieldC3C, buffer, 32, false);

        mpTextBoxes[1][0]->setMessage(mpMessage, 0x659A, pluralOffset, 1, buffer);
        mpTextBoxes[1][1]->setMessage(mpMessage, 0x659A, pluralOffset, 1, buffer);
    }

    mpTextBoxes[bActive][0]->SetVisible(true);
    mpTextBoxes[bActive][1]->SetVisible(true);
    mpTextBoxes[!bActive][0]->SetVisible(false);
    mpTextBoxes[!bActive][1]->SetVisible(false);

    mField48++;
    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowEventTextLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowEventTextLayout::IsFinished() const {
    return mAnimationState == 0;
}

// --------------------

/**
 * @brief Initializes the training stage layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowTrainingStageLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgText_02.brlyt");
    mAnimationState = 0;

    mpTextBox1 = mpLayout->findTextBox("T_stage_00");
    mpTextBox2 = mpLayout->findTextBox("T_stage_01");
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowTrainingStageLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
}

/**
 * @brief Updates the training stage animation each frame
 *
 * @param pContext Bowling scene context
 */
void RPBowTrainingStageLayout::Update(SceneContext* pContext) {
    if (mAnimationState == 0 || mAnimationState == 3) {
        if (unk04) {
            mpLayout->startDynAnmIn(0);
            mAnimationState = 1;
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!unk04) {
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

    wchar_t buffer[32];
    RPSysStringUtility::GetStringHalfSizeNumber(pContext->field_0xC38 + 1, buffer, 32, false);

    mpTextBox1->setMessage(mpMessage, 0x65F4, 0, 1, buffer);
    mpTextBox2->setMessage(mpMessage, 0x65F4, 0, 1, buffer);

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowTrainingStageLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowTrainingStageLayout::IsFinished() const {
    return mAnimationState == 0;
}

// --------------------

/**
 * @brief Initializes the Power Throws stage layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowPowerThrowsStageLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgText_03.brlyt");
    mAnimationState = 0;

    mpTextBox1 = mpLayout->findTextBox("T_stage_00");
    mpTextBox2 = mpLayout->findTextBox("T_stage_01");
    mpTextBox3 = mpLayout->findTextBox("T_pin_00");
    mpTextBox4 = mpLayout->findTextBox("T_pin_01");
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowPowerThrowsStageLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
}

/**
 * @brief Updates the Power Throws stage animation each frame
 *
 * @param pContext Bowling scene context
 */
void RPBowPowerThrowsStageLayout::Update(SceneContext* pContext) {
    if (mAnimationState == 0 || mAnimationState == 3) {
        if (unk04) {
            mpLayout->startDynAnmIn(0);
            mAnimationState = 1;
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!unk04) {
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

    wchar_t buffer1[32];
    RPSysStringUtility::GetStringHalfSizeNumber(pContext->field_0xC38 + 1, buffer1, 32, false);
    mpTextBox1->setMessage(mpMessage, 0x65F6, 0, 1, buffer1);
    mpTextBox2->setMessage(mpMessage, 0x65F6, 0, 1, buffer1);

    s32 max = pContext->field_0xC38 + 4;
    s32 sum = 0;
    for (s32 i = 0; i <= max; i++) {
        sum += i;
    }

    wchar_t buffer2[32];
    RPSysStringUtility::GetStringHalfSizeNumber(sum, buffer2, 32, false);
    mpTextBox3->setMessage(mpMessage, 0x65F5, 0, 1, buffer2);
    mpTextBox4->setMessage(mpMessage, 0x65F5, 0, 1, buffer2);

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowPowerThrowsStageLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 * 
 * @return True if animation state is 0, false otherwise
 */
bool RPBowPowerThrowsStageLayout::IsFinished() const {
    return mAnimationState == 0;
}

// -----------------

/**
 * @brief Initializes the Game Over layout
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowGameOverLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgText_04.brlyt");
    mpUnkAnim = mpLayout->createAnmObj(NULL, pAcc, "bwgText_04_inOut_00.brlan");

    RPSysLytTextBox* pTb1 = mpLayout->findTextBox("T_game_00");
    RPSysLytTextBox* pTb2 = mpLayout->findTextBox("T_game_01");

    pTb1->setMessage(pMsg, 0x65C2, 0, 0);
    pTb2->setMessage(pMsg, 0x65C2, 0, 0);

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowGameOverLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
}

/**
 * @brief Updates the Game Over layout animation each frame
 */
void RPBowGameOverLayout::Update() {
    if (mAnimationState == 0) {
        if (unk04) {
            mpLayout->unbindAllAnmObj();
            mpLayout->bindAnmObj(mpUnkAnim);

            RPSysLytAnmObj* pTempObj = mpUnkAnim;
            pTempObj->setFrame(pTempObj->getStartFrame());
            pTempObj->setFlags(0);
            pTempObj->setEnabled(1);

            mAnimationState = 1;
        }
    }

    if (mAnimationState == 1) {
        if (mpUnkAnim->isFinished()) {
            mpLayout->unbindAllAnmObj();
            mAnimationState = 0;
        }
    }

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowGameOverLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowGameOverLayout::IsFinished() const {
    return mAnimationState == 0;
}

// ------------------------

/**
 * @brief Initializes the strike text layout
 *
 * @param pAccessor Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowStrikeLayout::Init(RPSysLytResAccessor* pAccessor, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAccessor, "bwgStrike_00.brlyt");

    mpStrikeAnim = mpLayout->createAnmObj(NULL, pAccessor, "bwgStrike_00_inOut_00.brlan");

    mpTextBox1 = mpLayout->findTextBox("T_strike_00");
    mpTextBox2 = mpLayout->findTextBox("T_strike_01");

    mAnimationState = 0;
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowStrikeLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
}

/**
 * @brief Updates the strike layout animation each frame
 *
 * @param pContext Bowling scene context
 */
void RPBowStrikeLayout::Update(SceneContext* pContext) {
    if (pContext->field_0xC58 >= 2) {
        if (mAnimationState == 0) {
            if (unk04) {
                mpLayout->unbindAllAnmObj();
                mpLayout->bindAnmObj(mpStrikeAnim);

                RPSysLytAnmObj* pTempObj = mpStrikeAnim;
                pTempObj->setFrame(pTempObj->getStartFrame());
                pTempObj->setFlags(0);
                pTempObj->setEnabled(1);

                mAnimationState = 1;
            }
        }

        if (mAnimationState == 1) {
            if (mpStrikeAnim->isFinished()) {
                mpLayout->unbindAllAnmObj();
                mAnimationState = 0;
            }
        }

        s32 msgArg = pContext->field_0xC58 - 2;

        mpTextBox1->setMessage(mpMessage, 0x659B, msgArg, 0);
        mpTextBox2->setMessage(mpMessage, 0x659B, msgArg, 0);

        mpLayout->calc();
    }
}

/**
 * @brief Draws the layout
 */
void RPBowStrikeLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowStrikeLayout::IsFinished() const {
    return mAnimationState == 0;
}

// ------------------

// Sub-class instantiated in the manager
struct UnkTutorialHelper {
    u8 data[0x24];
};

extern "C" {
    bool fn_801CFCD4(UnkTutorialHelper*);
    bool fn_801CFCC4(UnkTutorialHelper*);
    void fn_801CFFE8(UnkTutorialHelper*);
    void fn_801CFCE8(UnkTutorialHelper*);
    void fn_801CFD64(UnkTutorialHelper*, nw4r::lyt::Pane*, f32, f32);
    void fn_801CFEA8(UnkTutorialHelper*);
    void fn_801D0044(UnkTutorialHelper*, void*, int);
    void fn_801CFE90(UnkTutorialHelper*);
}

/**
 * @brief Initializes the bowling tutorial layout and its components
 * @details Creates the layout showing the "Swing your arm while holding down B,
 * and release it to roll the ball." message and accompanying button animation.
 *
 * @param pAcc Layout resource accessor
 * @param pMsg System message configuration
 */
void RPBowTutorialLayout::Init(RPSysLytResAccessor* pAcc, RPSysMessage* pMsg) {
    mpMessage = pMsg;

    mpLayout = RPSysLayout::create(NULL, pAcc, "bwgTutorial_00.brlyt");
    mpObj1 = mpLayout->createAnmObj(NULL, pAcc, "bwgTutorial_00_in_00.brlan");
    mpObj2 = mpLayout->createAnmObj(NULL, pAcc, "bwgTutorial_00_out_00.brlan");
    mpObj3 = mpLayout->createAnmObj(NULL, pAcc, "bwgTutorial_00_loop_00.brlan");
    mpPane1 = mpLayout->findPane("N_AButton_00");
    mpPane2 = mpLayout->findPane("N_tutorial_01");

    RPSysLytTextBox* pTb = mpLayout->findTextBox("T_tutorial_00");
    pTb->setMessage(pMsg, 0x6592, 0, 0);

    mAnimationState = 0;
    mpTutorialHelper = new UnkTutorialHelper();

    void* pField30 = *(void**)((u8*)RP_GET_INSTANCE(RPSysResourceManager) + 0x30);
    fn_801D0044((UnkTutorialHelper*)mpTutorialHelper, pField30, 0);
}

/**
 * @brief Resets the tutorial layout to its initial state
 */
void RPBowTutorialLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mAnimationState = 0;
    fn_801CFFE8((UnkTutorialHelper*)mpTutorialHelper);
}

/**
 * @brief Updates the tutorial animation each frame
 */
void RPBowTutorialLayout::Update() {
    if (mAnimationState == 0 || mAnimationState == 3) {
        if (unk04) {
            mpLayout->reset();
            mpLayout->unbindAllAnmObj();
            mpLayout->bindAnmObj(mpObj1);

            RPSysLytAnmObj* pIn1 = mpObj1;
            s16 len1 = pIn1->getStartFrame();
            pIn1->setFrame(len1);
            pIn1->setFlags(0);
            pIn1->setEnabled(1);

            mAnimationState = 1;

            mpLayout->bindAnmObjToPane(mpObj3, mpPane2, true);

            RPSysLytAnmObj* pIn3 = mpObj3;
            s16 len3 = pIn3->getStartFrame();
            pIn3->setFrame(len3);
            pIn3->setFlags(0);
            pIn3->setEnabled(1);

            fn_801CFFE8((UnkTutorialHelper*)mpTutorialHelper);
            fn_801CFD64((UnkTutorialHelper*)mpTutorialHelper, mpPane1, 0.0f, 0.0f);
        }
    }

    if (mAnimationState == 1 || mAnimationState == 2) {
        if (!unk04) {
            if (fn_801CFCD4((UnkTutorialHelper*)mpTutorialHelper)) {
                mpLayout->unbindAllAnmObj();
                mpLayout->bindAnmObj(mpObj2);

                RPSysLytAnmObj* pIn2 = mpObj2;
                s16 len2 = pIn2->getStartFrame();
                pIn2->setFrame(len2);
                pIn2->setFlags(0);
                pIn2->setEnabled(1);

                mAnimationState = 3;
                fn_801CFCE8((UnkTutorialHelper*)mpTutorialHelper);
            }
        }
    }

    if (mAnimationState == 1) {
        if (mpObj1->isFinished()) {
            mAnimationState = 2;
        }
    }

    if (mAnimationState == 3) {
        if (mpObj2->isFinished()) {
            if (fn_801CFCC4((UnkTutorialHelper*)mpTutorialHelper)) {
                mAnimationState = 0;
            }
        }
    }

    // Controls the speed of the tutorial animation.
    if (mAnimationState == 2) {
        mpObj3->setRate(1.0f);
    } else {
        mpObj3->setRate(0.0f);
    }

    mpLayout->calc();
    fn_801CFEA8((UnkTutorialHelper*)mpTutorialHelper);
}

/**
 * @brief Draws the layout
 */
void RPBowTutorialLayout::Draw() {
    mpLayout->draw();
    fn_801CFE90((UnkTutorialHelper*)mpTutorialHelper);
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if animation state is 0, false otherwise
 */
bool RPBowTutorialLayout::IsFinished() const {
    return mAnimationState == 0;
}
