#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

//! Shadow offset from the normal cursor effect
#define SHADOW_OFFSET 3.0f

/**
 * @brief Position way outside of the screen boundaries
 */
const EGG::Vector2f RPSysCursorDrawMgr::OUT_OF_SCREEN_POS(0.0f, 12800.0f);

RP_SINGLETON_IMPL_EX(RPSysCursorDrawMgr);

/**
 * @brief Pushes the current controller parameter set to the stack
 */
void RPSysCursorDrawMgr::stackControllerSetting() {
    RPSysCoreController::pushDpdCtrlStackAll(true);
    RPSysCoreController::pushKPADParamStackAll();
}

/**
 * @brief Pops the top controller parameter set from the stack
 */
void RPSysCursorDrawMgr::popControllerSetting() {
    RPSysCoreController::popDpdCtrlStackAll();
    RPSysCoreController::popKPADParamStackAll();
}

/**
 * @brief Pushes a new DPD cursor configuration to the stack
 */
void RPSysCursorDrawMgr::startDpdCheck() {
    mActiveCursorIndex = -1;
    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorIndex[i] = -1;
    }

    if (checkActiveCursorEnable()) {
        for (int i = (FLAG_STACK_SIZE - 1) - 1; i >= 0; i--) {
            mCursorFlagStack[i + 1] = mCursorFlagStack[i];
        }
    }

    // Clear all other flags
    mCursorFlagStack[0] = 1 << EFlag_ActiveCursorEnable;

    // Cursors draw in port priority
    for (int i = EPlayer_P4; i >= EPlayer_P1; i--) {
        mpEffCursorShadow[i]->create();
        mpEffCursorBlur[i]->create();
        mpEffCursorNormal[i]->create();

        drawCursor(i, false, false);
    }

    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorPos[i] = OUT_OF_SCREEN_POS;
        mCursorHideTime[i] = mCursorHideTimeMax;
        updateCursor(i, i);
    }

    stackControllerSetting();
}

/**
 * @brief Pops the top DPD cursor configuration from the stack
 */
void RPSysCursorDrawMgr::finishDpdCheck() {
    // May need to create cursors from previous configuration
    if (mCursorFlagStack[1].onBit(EFlag_ActiveCursorEnable)) {
        for (int i = 0; i < FLAG_STACK_SIZE - 1; i++) {
            mCursorFlagStack[i] = mCursorFlagStack[i + 1];
        }

        mCursorFlagStack[FLAG_STACK_SIZE - 1].makeAllZero();

        if (mCursorFlagStack[0] & //
            (1 << EFlag_ActiveCursorValid | 1 << EFlag_9 | 1 << EFlag_10 |
             1 << EFlag_11)) {

            createActiveCursor();

        } else if (checkPlayerCursorEnable()) {
            for (int i = 0; i < EPlayer_Max; i++) {
                if (getPlayerCursorValid(static_cast<EPlayer>(i))) {
                    createPlayerCursor(static_cast<EPlayer>(i));
                }
            }
        }

    } else {
        mCursorFlagStack[0].makeAllZero();

        for (int i = 0; i < EPlayer_Max; i++) {
            mpEffCursorShadow[i]->forceKill();
            mpEffCursorBlur[i]->forceKill();
            mpEffCursorNormal[i]->forceKill();
        }
    }

    popControllerSetting();
}

/**
 * @brief Creates the active (main player) cursor
 */
void RPSysCursorDrawMgr::createActiveCursor() {
    if (checkActiveCursorEnable()) {
        mActiveCursorIndex =
            RPSysCoreController::getActiveController()->getPlayerNo();

        for (int i = 0; i < EPlayer_Max; i++) {
            mCursorIndex[i] = -1;
        }

        mCursorFlagStack[0].makeAllZero();
        mCursorFlagStack[0].setBit(EFlag_ActiveCursorEnable);
        mCursorFlagStack[0].setBit(EFlag_ActiveCursorValid);

        for (int i = 0; i < EPlayer_Max; i++) {
            mCursorPos[i] = OUT_OF_SCREEN_POS;

            drawCursor(i, true, mActiveCursorIndex == i);
            updateCursor(i, i);
        }
    }
}

/**
 * @brief Fades away the active (main player) cursor
 */
void RPSysCursorDrawMgr::fadeActiveCursor() {
    if (checkActiveCursorEnable()) {
        // Clear all other flags
        mCursorFlagStack[0] = 1 << EFlag_ActiveCursorEnable;

        for (int i = 0; i < EPlayer_Max; i++) {
            drawCursor(i, false, false);
        }
    }
}

/**
 * @brief Gets the screen position of the active (main player) cursor
 */
const EGG::Vector2f& RPSysCursorDrawMgr::getActiveCursorPos() const {
    if (checkActiveCursorEnable() && getActiveCursorValid() &&
        mActiveCursorIndex >= 0) {

        return mCursorPos[mActiveCursorIndex];
    }

    return OUT_OF_SCREEN_POS;
}

/**
 * @brief Gets the DPD cursor type of the active (main player) cursor
 */
RPSysCursorDrawMgr::ECursorType
RPSysCursorDrawMgr::getActiveCursorType() const {
    if (checkActiveCursorEnable() && getActiveCursorValid() &&
        mActiveCursorIndex >= 0) {

        return mCursorType[mActiveCursorIndex];
    }

    return ECursorType_Invalid;
}

/**
 * @brief Gets the player index of the active (main player) cursor
 *
 * @return Player slot index, or -1 if no such cursor exists
 */
s32 RPSysCursorDrawMgr::getActiveCursorPlayer() const {
    if (checkActiveCursorEnable() && getActiveCursorValid()) {
        return RPSysCoreController::getActiveController()->getPlayerNo();
    }

    return -1;
}

/**
 * @brief Creates the cursor for the specified player
 *
 * @param player Player slot index
 */
void RPSysCursorDrawMgr::createPlayerCursor(EPlayer player) {
    if (checkActiveCursorEnable()) {
        mActiveCursorIndex = -1;
        mCursorIndex[player] = -1;

        RPSysPlayerMgr* pPlayerMgr = RP_GET_INSTANCE(RPSysPlayerMgr);

        if (player < pPlayerMgr->getPlayerNum()) {
            mCursorIndex[player] = pPlayerMgr->getChannel(player);
            mCursorFlagStack[0].setBit(EFlag_Player1CursorValid + player);

            for (int i = 0; i < EPlayer_Max; i++) {
                mCursorPos[i] = OUT_OF_SCREEN_POS;
                drawCursor(i, getPlayerCursorValid(player), true);
                updateCursor(i, i);
            }
        }
    }
}

/**
 * @brief Moves the specified player cursor outside the screen
 *
 * @param player Player slot index
 */
void RPSysCursorDrawMgr::setPlayerCursorOutOfScreen(EPlayer player) {
    if (checkActiveCursorEnable()) {
        mCursorFlagStack[0].resetBit(EFlag_Player1CursorValid + player);
        mCursorPos[player] = OUT_OF_SCREEN_POS;

        drawCursor(player, false, false);
    }
}

/**
 * @brief Gets the position of the specified player cursor
 *
 * @param player Player slot index
 */
const EGG::Vector2f&
RPSysCursorDrawMgr::getPlayerCursorPos(EPlayer player) const {
    if (checkActiveCursorEnable() && getPlayerCursorValid(player) &&
        mCursorIndex[player] >= 0) {

        return mCursorPos[mCursorIndex[player]];
    }

    return OUT_OF_SCREEN_POS;
}

/**
 * @brief Gets the controller channel used by the specified player cursor
 *
 * @param player Player slot index
 * @return Controller channel, or -1 if no such cursor exists
 */
s32 RPSysCursorDrawMgr::getPlayerCursorChannel(EPlayer player) const {
    if (checkActiveCursorEnable() && getPlayerCursorValid(player)) {
        return RP_GET_INSTANCE(RPSysPlayerMgr)->getChannel(player);
    }

    return -1;
}

/**
 * @brief Forces a player cursor to the specified screen position
 *
 * @param rPos New cursor position
 * @param player Player slot index
 * @param clearHorizon Whether to reset the cursor horizon to zero
 */
void RPSysCursorDrawMgr::setPlayerCursorPos(const EGG::Vector2f& rPos,
                                            EPlayer player, bool clearHorizon) {
    if (checkActiveCursorEnable() && getPlayerCursorValid(player) &&
        mCursorIndex[player] >= 0) {

        mCursorPos[mCursorIndex[player]] = rPos;

        if (clearHorizon) {
            mCursorHorizon[mCursorIndex[player]] = 0.0f;
        }
    }
}

/**
 * @brief Clears this manager's state
 */
void RPSysCursorDrawMgr::init() {
    for (int i = 0; i < FLAG_STACK_SIZE; i++) {
        mCursorFlagStack[i].makeAllZero();
    }

    mActiveCursorIndex = -1;
    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorIndex[i] = -1;
    }

    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorHideTime[i] = mCursorHideTimeMax;
    }

    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorPos[i] = OUT_OF_SCREEN_POS;

        mpEffCursorShadow[i]->forceKill();
        mpEffCursorBlur[i]->forceKill();
        mpEffCursorNormal[i]->forceKill();
    }
}

/**
 * @brief Performs pre-update logic for the active (main player) cursor
 */
void RPSysCursorDrawMgr::preUpdateActive() {
    // Hide active DPD cursor when buttons are pressed
    if (getActiveCursorValid() && mActiveCursorIndex >= 0) {
        if (RP_GET_CORE_CTRL(mActiveCursorIndex)
                ->getCoreStatus()
                ->down(RPSysCoreController::CURSOR_BUTTONS)) {

            mCursorHideTime[mActiveCursorIndex] = 0;
        }
    }
}

/**
 * @brief Performs pre-update logic for player cursors
 */
void RPSysCursorDrawMgr::preUpdatePlayer() {
    // Hide player DPD cursor(s) when buttons are pressed
    if (checkPlayerCursorEnable()) {
        s32 playerNum = RP_GET_INSTANCE(RPSysPlayerMgr)->getPlayerNum();

        for (int i = 0; i < playerNum; i++) {
            if (mCursorIndex[i] < 0 ||
                !getPlayerCursorValid(static_cast<EPlayer>(i))) {

                continue;
            }

            if (RP_GET_CORE_CTRL(mCursorIndex[i])
                    ->getCoreStatus()
                    ->down(RPSysCoreController::CURSOR_BUTTONS)) {

                mCursorHideTime[mCursorIndex[i]] = 0;
            }
        }
    }
}

/**
 * @brief Performs logic that must occur before the scene is updated
 */
void RPSysCursorDrawMgr::preUpdate() {
    if (!checkActiveCursorEnable()) {
        return;
    }

    s32 remoteNum = RP_GET_INSTANCE(RPSysPlayerMgr)->getRemoteNum();

    if (remoteNum == 0) {
        remoteNum = RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
                            RPSysSceneCreator::EPackID_SportsPack
                        ? RP_SPORTS_MAX_PLAYERS
                        : RP_PARTY_MAX_PLAYERS;
    }

    // Hide active cursor if the device is not supported
    if (getActiveCursorValid()) {
        if (RPSysCoreController::getActiveController()->isCoreBaseDevice()) {
            mActiveCursorIndex =
                RPSysCoreController::getActiveController()->getPlayerNo();

        } else if (mActiveCursorIndex >= 0) {
            mCursorPos[mActiveCursorIndex] = OUT_OF_SCREEN_POS;
        }
    }

    // Hide player cursors if the device is not supported
    if (checkPlayerCursorEnable()) {
        s32 playerNum = RP_GET_INSTANCE(RPSysPlayerMgr)->getPlayerNum();

        for (int i = 0; i < playerNum; i++) {
            mCursorIndex[i] = RP_GET_INSTANCE(RPSysPlayerMgr)->getChannel(i);

            if (RP_GET_CORE_CTRL(mCursorIndex[i])->isCoreBaseDevice()) {
                continue;
            }

            mCursorPos[mCursorIndex[i]] = OUT_OF_SCREEN_POS;
        }
    }

    RPGrpView* pCursorView = RPGrpRenderer::GetCurrent() //
                                 ->GetView(RPSysCommonObject::EView_2D_Cursor);

    if (pCursorView != NULL) {
        RPGrpScreen* pScreen = pCursorView->GetScreen();

        if (pScreen != NULL) {
            preUpdateActive();
            preUpdatePlayer();

            // Poll latest cursor state
            for (int i = 0; i < remoteNum; i++) {
                // Hidden cursor(s) wait to wake-up
                if (mCursorHideTime[i] < mCursorHideTimeMax) {
                    mCursorType[i] = ECursorType_Invalid;
                    mCursorPos[i] = OUT_OF_SCREEN_POS;

                    mCursorHideTime[i] +=
                        RP_GET_INSTANCE(RPSysSystem)->getFrameRate();
                }
                // Process valid cursor
                else {
                    EGG::CoreStatus status =
                        *RP_GET_CORE_CTRL(i)->getCoreStatus();

                    mCursorType[i] =
                        static_cast<ECursorType>(status.getDPDValidFlag());

                    if (mCursorType[i] > 0 &&
                        RP_GET_CORE_CTRL(i)->isCoreBaseDevice()) {

                        EGG::Vector2f pos = status.getDpdPos();
                        pos.x = EGG::Mathf::clamp2(pos.x, -1.0f, 1.0f);
                        pos.y = EGG::Mathf::clamp2(pos.y, -1.0f, 1.0f);

                        pScreen->ConvertFromNormalCC(
                            pos.x, -pos.y, &mCursorPos[i].x, &mCursorPos[i].y);

                        EGG::Vector2f hori = status.getHorizon();
                        mCursorHorizon[i] = EGG::Mathf::atan2(hori.y, hori.x);
                    } else {
                        mCursorPos[i] = OUT_OF_SCREEN_POS;
                    }
                }
            }
        }
    }
}

/**
 * @brief Performs logic that must occur after the scene is updated
 */
void RPSysCursorDrawMgr::postUpdate() {
    if (checkActiveCursorEnable()) {
        postUpdateActive();
        postUpdatePlayer();
    }
}

/**
 * @brief Performs post-update logic for the active (main player) cursor
 */
void RPSysCursorDrawMgr::postUpdateActive() {
    if (mCursorFlagStack[0] & 1 << EFlag_ActiveCursorValid) {
        s32 playerNum = RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
                                RPSysSceneCreator::EPackID_PartyPack
                            ? RP_PARTY_MAX_PLAYERS
                            : RP_MAX_PLAYERS;

        if (mCursorFlagStack[0] & 1 << EFlag_ActiveCursorValid) {
            for (int i = 0; i < playerNum; i++) {
                updateCursor(i, i);
            }
        }
    }
}

/**
 * @brief Performs post-update logic for player cursors
 */
void RPSysCursorDrawMgr::postUpdatePlayer() {
    if (!checkPlayerCursorEnable()) {
        return;
    }

    s32 playerNum = RP_GET_INSTANCE(RPSysPlayerMgr)->getPlayerNum();

    // @bug Undefined behavior
#if defined(BUG_FIX)
    bool update[EPlayer_Max] = {};
#else
    bool update[EPlayer_Max];
#endif

    for (int i = 0; i < playerNum; i++) {
        update[i] = true;
    }

    for (int i = 0; i < playerNum; i++) {
        if (mCursorIndex[i] < 0) {
            continue;
        }

        if (!update[mCursorIndex[i]]) {
            continue;
        }

        if (!getPlayerCursorValid(static_cast<EPlayer>(i))) {
            continue;
        }

        update[mCursorIndex[i]] = false;
        updateCursor(i, mCursorIndex[i]);
    }

    for (int i = 0; i < playerNum; i++) {
        if (mCursorIndex[i] < 0) {
            continue;
        }

        if (!update[mCursorIndex[i]]) {
            continue;
        }

        update[mCursorIndex[i]] = false;
        updateCursor(i, mCursorIndex[i]);
    }
}

/**
 * @brief Configures the effect draw settings of the specified cursor
 *
 * @param cursor Cursor index
 * @param visible Whether the cursor should be visible
 * @param enabled Whether the cursor should be enabled (not faded)
 */
void RPSysCursorDrawMgr::drawCursor(s32 cursor, bool visible, bool enabled) {
    if (visible) {
        if (enabled) {
            mpEffCursorNormal[cursor]->setColor(255, 255, 255, 255);
            mpEffCursorNormal[cursor]->setDisableDraw(false);
            mpEffCursorBlur[cursor]->setDisableDraw(false);
            mpEffCursorShadow[cursor]->setDisableDraw(false);
        } else {
            mpEffCursorNormal[cursor]->setColor(255, 255, 255, mDisabledAlpha);
            mpEffCursorNormal[cursor]->setDisableDraw(false);

            mpEffCursorBlur[cursor]->setDisableDraw(true);
            mpEffCursorShadow[cursor]->setDisableDraw(true);
        }
    } else {
        mpEffCursorNormal[cursor]->setDisableDraw(true);
        mpEffCursorBlur[cursor]->setDisableDraw(true);
        mpEffCursorShadow[cursor]->setDisableDraw(true);
    }
}

/**
 * @brief Updates the specified cursor to match the latest DPD data
 *
 * @param cursor Cursor index
 * @param player Player index
 */
void RPSysCursorDrawMgr::updateCursor(s32 cursor, s32 player) {
    EGG::Vector3f cursorPos(  //
        mCursorPos[player].x, //
        mCursorPos[player].y, //
        0.0f                  //
    );

    EGG::Vector3f shadowPos(         //
        cursorPos.x + SHADOW_OFFSET, //
        cursorPos.y - SHADOW_OFFSET, //
        0.0f                         //
    );

    EGG::Vector3f cursorRot(   //
        0.0f,                  //
        0.0f,                  //
        mCursorHorizon[player] //
    );

    mpEffCursorNormal[cursor]->setPos(cursorPos);
    mpEffCursorNormal[cursor]->setParticleRotate(cursorRot);
    mpEffCursorNormal[cursor]->update();

    mpEffCursorBlur[cursor]->setPos(cursorPos);
    mpEffCursorBlur[cursor]->setParticleRotate(cursorRot);
    mpEffCursorBlur[cursor]->update();

    mpEffCursorShadow[cursor]->setPos(shadowPos);
    mpEffCursorShadow[cursor]->setParticleRotate(cursorRot);
    mpEffCursorShadow[cursor]->update();
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysCursorDrawMgr::RPSysCursorDrawMgr(EGG::Heap* pHeap)
    : IRPSysHostIOSocket("Cursor Manager"), mpParentHeap(pHeap) {

    for (int i = 0; i < FLAG_STACK_SIZE; i++) {
        mCursorFlagStack[i].makeAllZero();
    }

    mActiveCursorIndex = -1;
    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorIndex[i] = -1;
    }

    mCursorHideTimeMax = HIDE_TIME_MAX;
    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorHideTime[i] = mCursorHideTimeMax;
    }

    mDisabledAlpha = DISABLED_ALPHA;

    const char* pNormalNames[EPlayer_Max][2] = {
        // clang-format off
        "def_cursor_normal_1p",
        "def_cursor_normal_1p_n",

        "def_cursor_normal_2p",
        "def_cursor_normal_2p_n",

        "def_cursor_normal_3p",
        "def_cursor_normal_3p_n",

        "def_cursor_normal_4p",
        "def_cursor_normal_4p_n",
        // clang-format on
    };

    const char* pBlurNames[EPlayer_Max] = {
        "def_cursor_normal_1p_blur",
        "def_cursor_normal_2p_blur",
        "def_cursor_normal_3p_blur",
        "def_cursor_normal_4p_blur",
    };

    // Wii Sports uses the _n ("neon"?) version
    int cursorType = 0;
    if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
        RPSysSceneCreator::EPackID_SportsPack) {

        cursorType = 1;
    }

    for (int i = 0; i < EPlayer_Max; i++) {
        mCursorType[i] = ECursorType_Invalid;
        mCursorPos[i] = OUT_OF_SCREEN_POS;

        mpEffCursorNormal[i] = new (pHeap) RPSysEffect( //
            pNormalNames[i][cursorType],                //
            RPSysEffectMgr::EDrawGroup_Cursor,          //
            RPSysEffectMgr::EDrawScene_Cursor);

        mpEffCursorBlur[i] = new (pHeap) RPSysEffect( //
            pBlurNames[i],                            //
            RPSysEffectMgr::EDrawGroup_Cursor,        //
            RPSysEffectMgr::EDrawScene_Cursor);

        mpEffCursorShadow[i] = new (pHeap) RPSysEffect( //
            "def_cursor_normal_sd",                     //
            RPSysEffectMgr::EDrawGroup_Cursor,          //
            RPSysEffectMgr::EDrawScene_Cursor);
    }
}

/**
 * @brief Destructor
 */
RPSysCursorDrawMgr::~RPSysCursorDrawMgr() {}
