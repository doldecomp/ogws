#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Destructor
 */
RPBowScoreLayout::~RPBowScoreLayout() {}

/**
 * @brief Initializes the player icons for the score layout
 */
void RPBowScoreLayout::InitIcons() {
    for (int i = 0; i < 4; i++) {
        RPSysKokeshiGenInfo info;
        GXColor color = {0, 0, 0, 0};

        info.SetGenType(RPSysKokeshiManager::GenType_Player);
        info.SetPlayerNo(i);
        info.SetIconWidth(48);
        info.SetIconHeight(48);
        info.SetIconBGType((RFLIconBGType)1);
        info.SetIconBGColor(color);
        info.SetIconMipMap(true);

        mpIcons[i] = new RPSysKokeshiIcon(&info);
    }
    unkBC0 = 50.0f;
    unkBC4 = -50.0f;
}

/**
 * @brief Initializes the main scoring layout elements
 *
 * @param pAcc Layout resource accessor
 * @param unk Unknown configuration parameter
 */
void RPBowScoreLayout::Init(RPSysLytResAccessor* pAcc, u32 unk) {
    unkB7C = unk;
    mpLayout = RPSysLayout::create(NULL, pAcc, "score_00.brlyt");

    char buf[64];
    for (int i = 0; i < 10; i++) {
        sprintf(buf, "P_frameBG%02d_00", i + 1);
        mpFrameBGP[i] = mpLayout->findPane(buf);

        sprintf(buf, "T_frame%02d_00", i + 1);
        mpFrameT[i] = mpLayout->findTextBox(buf);
    }

    mpFrameBGP[10] = mpLayout->findPane("P_frameBG10_01");
    mpFrameT[10] = mpLayout->findTextBox("T_frame10_01");

    for (int i = 0; i < 4; i++) {
        sprintf(buf, "P_playerBG_%02d", i);
        mpPlayerBGP[i] = mpLayout->findPicture(buf);
    }

    mpScoreRootP = mpLayout->findPane("N_scoreRoot_00");
    mScoreRoot.x = mpScoreRootP->GetTranslate().x;
    mScoreRoot.y = mpScoreRootP->GetTranslate().y;
    mScoreRoot.z = mpScoreRootP->GetTranslate().z;
    mpRootPane = mpLayout->findPane("RootPane");

    for (int p = 0; p < 4; p++) {
        for (int f = 0; f < 11; f++) {
            if (f < 9) {
                mFrames[p][f].layout = RPSysLayout::create(NULL, pAcc, "score_01.brlyt");
            } else {
                mFrames[p][f].layout = RPSysLayout::create(NULL, pAcc, "score_02.brlyt");
            }

            mFrames[p][f].scoreBG = mFrames[p][f].layout->findPane("P_scoreBG_00");
            mFrames[p][f].rootPane = mFrames[p][f].layout->findPane("RootPane");
            mFrames[p][f].alpha = mFrames[p][f].scoreBG->GetAlpha();

            mFrames[p][f].rootX = mpFrameBGP[f]->GetTranslate().x;
            mFrames[p][f].rootY = mpPlayerBGP[p]->GetTranslate().y;

            for (int t = 0; t < 3; t++) {
                sprintf(buf, "T_throw%d_00", t + 1);
                mFrames[p][f].throwT[t] = mFrames[p][f].layout->findTextBox(buf);

                sprintf(buf, "P_strike%d_00", t + 1);
                mFrames[p][f].strikeP[t] = mFrames[p][f].layout->findPane(buf);

                sprintf(buf, "P_spare%d_00", t + 1);
                mFrames[p][f].spareP[t] = mFrames[p][f].layout->findPane(buf);
            }

            mFrames[p][f].totalT = mFrames[p][f].layout->findTextBox("T_total_00");
        }
    }

    for (int p = 0; p < 4; p++) {
        sprintf(buf, "N_playerIcon_%02d", p);
        mpPlayerIconP[p] = mpLayout->findPane(buf);
        mpIcons[p]->LoadResource(NULL);
    }

    unkBCC = 0;
}

/**
 * @brief Resets the layout components and state tracking variables
 */
void RPBowScoreLayout::Reset() {
    mpLayout->reset();

    for (int p = 0; p < 4; p++) {
        for (int f = 0; f < 10; f++) {
            mFrames[p][f].layout->reset();
        }
    }

    unkBA4 = 0;
    unkBA0 = 0;
    unkBA8 = 0;
    unkBCC = 0;
}
