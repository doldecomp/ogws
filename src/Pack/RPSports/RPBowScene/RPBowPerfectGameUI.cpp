#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Initializes the perfect game UI
 *
 * @param pAccessor Layout resource accessor
 * @param pMessage Message handler
 */
void RPBowPerfectGameUI::Init(RPSysLytResAccessor* pAccessor, RPSysMessage* pMessage) {
    mpLayout = RPSysLayout::create(0, pAccessor, "bwgText_05.brlyt");
    mpAnmIn = mpLayout->createAnmObj(0, pAccessor, "bwgText_05_in_00.brlan");
    mpAnmOut = mpLayout->createAnmObj(0, pAccessor, "bwgText_05_out_00.brlan");

    for (int i = 0; i < 5; i++) {
        char buf[256];
        std::sprintf(buf, "T_perfect_%02d", i);
        RPSysLytTextBox* pTextBox = mpLayout->findTextBox(buf);
        pTextBox->setMessage(pMessage, 0x6784, 0, 0);
    }

    mpHubukiEffect = new RPSysEffect("Bow_perfect_hubuki", mDrawGroup, 0);

    mpRootPane = mpLayout->findPane("N_perfect_00");
}

/**
 * @brief Resets the UI state
 */
void RPBowPerfectGameUI::Reset() {
    mState = 0;
}

/**
 * @brief Updates the UI state and animations
 */
void RPBowPerfectGameUI::Calc() {
    bool flag = false;

    if (mState == 0) {
        if (mIsVisible) {
            mpLayout->unbindAllAnmObj();
            mpLayout->bindAnmObj(mpAnmIn);

            RPSysLytAnmObj* pIn = mpAnmIn;
            s16 len = pIn->getStartFrame();
            pIn->setFrame(len);
            pIn->setFlags(0);
            pIn->setEnabled(1);

            mState = 2;
            flag = true;
        }
    }

    if (mState == 1) {
        if (!mIsVisible) {
            mpLayout->unbindAllAnmObj();
            mpLayout->bindAnmObj(mpAnmOut);

            RPSysLytAnmObj* pOut = mpAnmOut;
            s16 len = pOut->getStartFrame();
            pOut->setFrame(len);
            pOut->setFlags(0);
            pOut->setEnabled(1);

            mpHubukiEffect->fade();
            mState = 3;
        }
    }

    if (mState == 2) {
        if (mpAnmIn->isFinished()) {
            mState = 1;
        }
    }

    if (mState == 3) {
        if (mpAnmOut->isFinished()) {
            mState = 0;
        }
    }

    mpLayout->calc();

    nw4r::math::MTX34 mtx = mpRootPane->GetGlobalMtx();

    if (flag) {
        RPSysEffect kiraEffect("Bow_perfect_kira", mDrawGroup, 0);
        kiraEffect.create();

        nw4r::math::VEC3 pos(mtx[0][3], mtx[1][3], mtx[2][3]);
        kiraEffect.setPos(pos);
        kiraEffect.update();

        mpHubukiEffect->forceKill();
        mpHubukiEffect->create();
    }

    nw4r::math::VEC3 pos2(mtx[0][3], mtx[1][3], mtx[2][3]);
    mpHubukiEffect->setPos(pos2);
    mpHubukiEffect->update();
}

/**
 * @brief Draws the UI layout
 */
void RPBowPerfectGameUI::Draw() {
    mpLayout->draw();
}
