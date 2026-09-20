#include <Pack/RPSports/RPBowScene/bowling.h>

extern const nw4r::math::VEC2 lbl_803CAE40[2][16];
extern const f32 lbl_804BFA08[2];

/**
 * @brief Destructor
 */
RPBowAimGuideLayout::~RPBowAimGuideLayout() {}

/**
 * @brief Initializes the aim guide layout
 *
 * @param pHeap Memory heap
 * @param pMsg System message configuration
 */
void RPBowAimGuideLayout::Init(EGG::Heap* pHeap, RPSysMessage* pMsg) {
    mpMessage = pMsg;
    mpLayout = RPSysLayout::create((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00.brlyt");
    mpRootPane = mpLayout->findPane("RootPane");

    mpBlinkAnm = mpLayout->createAnmObj((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00_blink_00.brlan");
    mpPlusButton00 = mpLayout->findPane("N_plusButton_00");

    mpPlusText00 = mpLayout->findTextBox("T_plusText_00");
    mpPlusText01 = mpLayout->findTextBox("T_plusText_01");
    mpAText00 = mpLayout->findTextBox("T_aText_00");
    mpAText01 = mpLayout->findTextBox("T_aText_01");

    mpAText00->setMessage(mpMessage, 0x65B9, 0, 0);
    mpAText01->setMessage(mpMessage, 0x65B9, 0, 0);

    mpChangeAnm[0] = mpLayout->createAnmObj((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00_change_00.brlan");
    mpChangeAnm[1] = mpLayout->createAnmObj((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00_change_00.brlan");

    mpChangePanes[0] = mpLayout->findPane("N_aButton_00");
    mpChangePanes[1] = mpLayout->findPane("N_plusText_00");

    for (int i = 0; i < 2; i++) {
        mpOnAnm[i] = mpLayout->createAnmObj((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00_on_00.brlan");
        mpOffAnm[i] = mpLayout->createAnmObj((EGG::Heap*)NULL, (RPSysLytResAccessor*)pHeap, "bwgMoveExp_00_off_00.brlan");
    }

    mpOnOffPanes[0] = mpLayout->findPane("N_plusButton_01");
    mpOnOffPanes[1] = mpLayout->findPane("N_plusText_01");

    RPSysLytTextBox* pPlusText02 = mpLayout->findTextBox("T_plusText_02");
    pPlusText02->setMessage(pMsg, 0x65ba, 0, 0);

    RPSysLytTextBox* pPlusText03 = mpLayout->findTextBox("T_plusText_03");
    pPlusText03->setMessage(pMsg, 0x65ba, 0, 0);

    mState = 0;
}

/**
 * @brief Resets the layout and unbinds objects
 */
void RPBowAimGuideLayout::Reset() {
    mpLayout->reset();
    mpLayout->unbindAllAnmObj();
    mState = 0;
    mUnk44 = 0;
    mUnk3C = 0;
    mUnk40 = 0;
}

/**
 * @brief Calculates transformations and pane statuses based on current context
 *
 * @param pContext Bowling scene context
 */
void RPBowAimGuideLayout::Calc(SceneContext* pContext) {
    if (pContext->mUnkC54 != 0) {
        mUnk38 = 0;
    } else {
        mUnk38 = 1;
    }

    s32 animSpeed = -pContext->mUnkC34;

    if (mState == 0 || mState == 3) {
        if (mUnk4 != 0) {
            mpLayout->unbindAllAnmObj();
            RPSysLayout::bindAnmObjToPane(mpBlinkAnm, mpPlusButton00, true);

            mpBlinkAnm->setFrame(mpBlinkAnm->getStartFrame());
            mpBlinkAnm->setFlags(0);
            mpBlinkAnm->setEnabled(1);

            mUnk70 = 1;

            for (int i = 0; i < 2; i++) {
                RPSysLayout::bindAnmObjToPane(mpOnAnm[i], mpOnOffPanes[i], true);
                mpOnAnm[i]->play((s16)(mpOnAnm[i]->getFrameMax() - 1.0f));
            }

            mpLayout->startDynAnmIn(animSpeed);
            mState = 1;
            mUnk38 = 0;
            mUnk44 = 99999;
            mUnk3C = -1;
            mUnk40 = 0;
        }
    }

    if (mState == 1 || mState == 2) {
        if (mUnk4 == 0) {
            mpLayout->startDynAnmOut(0);
            mState = 3;
        }
    }

    if (mState == 1) {
        if (mpLayout->isFinishedDynAnmIn()) {
            mState = 2;
        }
    }

    if (mState == 3) {
        if (mpLayout->isFinishedDynAnmOut()) {
            mState = 0;
        }
    }

    if (mUnk40 != mUnk38) {
        for (int i = 0; i < 2; i++) {
            RPSysLayout::unbindAnmObjToPane(mpChangeAnm[i], mpChangePanes[i], true);
            RPSysLayout::bindAnmObjToPane(mpChangeAnm[i], mpChangePanes[i], true);

            RPSysLytAnmObj* pTempAnm = mpChangeAnm[i];
            pTempAnm->setFrame(pTempAnm->getStartFrame());
            pTempAnm->setFlags(0);
            pTempAnm->setEnabled(1);
        }
        mUnk40 = mUnk38;
    }

    if (mUnk38 != mUnk3C) {
        mUnk44++;
        if (mUnk44 >= 4) {
            mpPlusText00->setMessage(mpMessage, 0x65B8, 0, 0);
            mpPlusText01->setMessage(mpMessage, 0x65B8, mUnk38, 0);
            mUnk44 = 0;
            mUnk3C = mUnk38;
        }
    }

    u32 cond = (pContext->mUnkC5D == 0) ? 1 : 0;
    if (mUnk70 != cond) {
        RPSysLayout::unbindAnmObjToPane(mpOnAnm[0], mpOnOffPanes[0], true);
        RPSysLayout::unbindAnmObjToPane(mpOnAnm[1], mpOnOffPanes[1], true);
        RPSysLayout::unbindAnmObjToPane(mpOffAnm[0], mpOnOffPanes[0], true);
        RPSysLayout::unbindAnmObjToPane(mpOffAnm[1], mpOnOffPanes[1], true);

        for (int i = 0; i < 2; i++) {
            RPSysLytAnmObj* pAnm = mpOnAnm[i];
            RPSysLayout::bindAnmObjToPane(pAnm, mpOnOffPanes[i], true);

            pAnm->setFrame(pAnm->getStartFrame());
            pAnm->setFlags(0);
            pAnm->setEnabled(1);
        }

        mUnk70 = cond;
    }

    bool isTvMode = EGG::Screen::GetTVMode();
    nw4r::math::VEC2 pos(
        lbl_803CAE40[isTvMode][pContext->mUnkC1C].x,
        lbl_804BFA08[isTvMode] * (pContext->mUnk4 - 1) + lbl_803CAE40[isTvMode][pContext->mUnkC1C].y
    );

    mpRootPane->SetTranslate(nw4r::math::VEC3(pos.x, pos.y, 0.0f));

    mpLayout->calc();
}

/**
 * @brief Draws the layout
 */
void RPBowAimGuideLayout::Draw() {
    mpLayout->draw();
}

/**
 * @brief Tests whether the layout animation has finished
 *
 * @return True if state is 0, false otherwise
 */
bool RPBowAimGuideLayout::IsFinished() const {
    return mState == 0;
}
