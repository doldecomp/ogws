#include <Pack/RPAudio.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <revolution/VI.h>

RP_SINGLETON_IMPL_EX(RPSysSceneMgr);

/**
 * @brief Constructor
 *
 * @param pHeap Heap to use for allocations
 */
RPSysSceneMgr::RPSysSceneMgr(EGG::Heap* pHeap)
    : mpParentHeap(pHeap), mState(EState_Normal) {

    mpSceneFader = new EGG::ColorFader(             //
        0.0f, 0.0f,                                 //
        RP_GET_INSTANCE(RPSysSystem)->getFBWidth(), //
        RP_GET_INSTANCE(RPSysSystem)->getFBHeight() //
    );
}

/**
 * @brief Gets the currently active scene as the Pack Project type
 */
RPSysScene* RPSysSceneMgr::getCurrentSceneRP() const {
    return static_cast<RPSysScene*>(getCurrentScene());
}

/**
 * @brief Performs a soft reset
 *
 * @param fromHBM Whether the request came from HBM
 * @return Success
 */
bool RPSysSceneMgr::softReset(bool fromHBM) {
    if (mState == EState_Normal) {
        mState = EState_SoftReset;

        // HBM does its own fadeout
        if (fromHBM) {
            resetFadeFrame();
            resetFadeColor();
            setSceneStatus(EGG::Fader::STATUS_PREPARE_IN);
        }

        return true;
    }

    return false;
}

/**
 * @brief Returns to the IPL
 *
 * @param fromHBM Whether the request came from HBM
 * @return Success
 */
bool RPSysSceneMgr::returnToMenu(bool fromHBM) {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSaveDataMgr)->setSaveDisable(true);
        mState = EState_ReturnToMenu;

        // HBM does its own fadeout
        if (fromHBM) {
            VISetBlack(TRUE);
        }

        return true;
    }

    return false;
}

/**
 * @brief Powers off the console
 *
 * @param fromHBM Whether the request came from HBM
 * @return Success
 */
bool RPSysSceneMgr::shutdownSystem(bool fromHBM) {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSaveDataMgr)->setSaveDisable(true);
        mState = EState_Shutdown;

        // HBM does its own fadeout
        if (fromHBM) {
            VISetBlack(TRUE);
        }

        return true;
    }

    return false;
}

/**
 * @brief Tests whether this manager is operating normally
 */
bool RPSysSceneMgr::isNormalState() const {
    return mState == EState_Normal;
}

/**
 * @brief Tests whether this manager is currently shutting down the system
 */
bool RPSysSceneMgr::isShutDownReserved() const {
    return mState == EState_Shutdown;
}

/**
 * @brief Tests whether this manager is currently returning to the IPL
 */
bool RPSysSceneMgr::getReturnToMenu() const {
    return mState == EState_ReturnToMenu;
}

/**
 * @brief Disables the guard state and returns to normal operation
 */
void RPSysSceneMgr::resetGuard() {
    if (mState == EState_Guard) {
        mState = EState_Normal;
    }
}

/**
 * @brief Tests whether this manager is currently exiting the program
 */
bool RPSysSceneMgr::isApplicationEndReserved() {
    return getReturnToMenu() || isShutDownReserved();
}

/**
 * @brief Tests whether a DVD error should exit the program
 */
bool RPSysSceneMgr::isDvdErrorApplicationEnd() {
    return mState != EState_Normal;
}

/**
 * @brief Requests a scene change after fading out
 * @details A scene id of -1 will select the current scene.
 *
 * @param id New scene ID
 * @param reconfigure Whether to fully reconfigure the scene
 * @return Success
 */
bool RPSysSceneMgr::changeNextSceneAfterFade(s32 id, bool reconfigure) {
    //! Scene change method
    enum EMethod {
        Default,
        ChangeSiblingSceneAfterFadeOut,
        CreateChildSceneAfterFadeOut,
        ReInitCurrentSceneAfterFadeOut,
        DestroyToSelectSceneIDAfterFadeOut,
        ChangeSceneAfterFadeOut,
        ChangeScene,      // no fadeout
        CreateChildScene, // no fadeout
    };

    EMethod method = Default;

    if (getCurrentSceneRP() != NULL) {
        int current = getCurrentSceneRP()->getSceneID();

        // Parent scene's exit type takes priority over the new create type
        RPSysSceneCreator::EExitType exitType =
            RP_GET_INSTANCE(RPSysSceneCreator)->getExitType(current);

        // Current scene requests that new scenes are children
        if (exitType == RPSysSceneCreator::EExitType_Child) {
            method = CreateChildScene;

            goto _do_change;
        }

        // Current scene is being reloaded
        if (current == id) {
            // Usual behavior is re-init, which skips the Configure phase.
            // The reconfigure parameter forces a full destroy -> create.
            if (reconfigure ||
                exitType == RPSysSceneCreator::EExitType_Sibling) {
                method = ChangeSiblingSceneAfterFadeOut;
            } else {
                method = ReInitCurrentSceneAfterFadeOut;
            }

            goto _do_change;
        }

        // Orphan scenes can be freely destroyed
        if (findParentScene(id) != NULL) {
            method = DestroyToSelectSceneIDAfterFadeOut;

            goto _do_change;
        }

        // New scene's create type takes the lowest priority
        switch (RP_GET_INSTANCE(RPSysSceneCreator)->getCreateType(id)) {
        case RPSysSceneCreator::ECreateType_Standard: {
            method = ChangeSceneAfterFadeOut;
            break;
        }

        case RPSysSceneCreator::ECreateType_Sibling: {
            method = ChangeSiblingSceneAfterFadeOut;
            break;
        }

        case RPSysSceneCreator::ECreateType_Child: {
            method = CreateChildSceneAfterFadeOut;
            break;
        }
        }

    } else {
        // No scene exists yet, nothing else needs to be done
        method = ChangeScene;
    }

_do_change:
    switch (method) {
    case Default:
    case ChangeSiblingSceneAfterFadeOut: {
        return changeSiblingSceneAfterFadeOut(id);
    }

    case CreateChildSceneAfterFadeOut: {
        return createChildSceneAfterFadeOut(id, getCurrentSceneRP());
    }

    case CreateChildScene: {
        createChildScene(id, getCurrentSceneRP());
        return true;
    }

    case ReInitCurrentSceneAfterFadeOut: {
        return reinitCurrentSceneAfterFadeOut();
    }

    case DestroyToSelectSceneIDAfterFadeOut: {
        return destroyToSelectSceneIDAfterFadeOut(id);
    }

    case ChangeSceneAfterFadeOut: {
        return changeSceneAfterFadeOut(id);
    }

    case ChangeScene: {
        changeScene(id);
        return true;
    }

    default: {
        return false;
    }
    }
}

/**
 * @brief Resets the duration of all faders
 */
void RPSysSceneMgr::resetFadeFrame() {
    mpSceneFader->setFrame(DEFAULT_FADE_FRAME);
    mCurrentFader->setFrame(DEFAULT_FADE_FRAME);
}

/**
 * @brief Gets the duration of the scene fader
 */
u16 RPSysSceneMgr::getFadeFrame() {
    return mpSceneFader->getFrame();
}

/**
 * @brief Sets the duration of all faders
 *
 * @param frame Fade duration, in frames
 */
void RPSysSceneMgr::setFadeFrame(u16 frame) {
    mpSceneFader->setFrame(frame);
    mCurrentFader->setFrame(frame);
}

/**
 * @brief Resets the color of all faders
 * @details The default fader color is white.
 */
void RPSysSceneMgr::resetFadeColor() {
    mpSceneFader->setColor(DEFAULT_FADE_COLOR);
    mCurrentFader->setColor(DEFAULT_FADE_COLOR);
}

/**
 * @brief Gets the color of the manager fader
 */
nw4r::ut::Color RPSysSceneMgr::getFadeColor() {
    return mCurrentFader->getColor();
}

/**
 * @brief Sets the color of all faders
 *
 * @param color Fade color
 */
void RPSysSceneMgr::setFadeColor(nw4r::ut::Color color) {
    mpSceneFader->setColor(color);
    mCurrentFader->setColor(color);
}

/**
 * @brief Sets the color of the scene fader
 *
 * @param color Fade color
 */
void RPSysSceneMgr::setSceneFadeColor(nw4r::ut::Color color) {
    mpSceneFader->setColor(color);
}

/**
 * @brief Gets the status of the scene fader
 */
EGG::Fader::EStatus RPSysSceneMgr::getSceneStatus() {
    return mpSceneFader->getStatus();
}

/**
 * @brief Sets the status of the scene fader
 *
 * @param status Fade status
 */
void RPSysSceneMgr::setSceneStatus(EGG::Fader::EStatus status) {
    mpSceneFader->setStatus(status);
}

/**
 * @brief Begins fading in the manager fader
 *
 * @return Success
 */
bool RPSysSceneMgr::startMgrFadeIn() {
    return fadeIn();
}

/**
 * @brief Begins fading in the scene fader
 *
 * @return Success
 */
bool RPSysSceneMgr::startSceneFadeIn() {
    return mpSceneFader->fadeIn();
}

/**
 * @brief Begins fading out the scene fader
 *
 * @return Success
 */
bool RPSysSceneMgr::startSceneFadeOut() {
    return mpSceneFader->fadeOut();
}

/**
 * @brief Tests whether the scene is fully visible
 */
bool RPSysSceneMgr::isDisplay() {
    return mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT &&
           mpSceneFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT;
}

/**
 * @brief Tests whether the scene is visibly obscured
 */
bool RPSysSceneMgr::isBlank() {
    return mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_IN ||
           mpSceneFader->getStatus() == EGG::Fader::STATUS_PREPARE_IN;
}

/**
 * @brief Tests whether the scene is fading out
 */
bool RPSysSceneMgr::isFadeOut() {
    return mCurrentFader->getStatus() == EGG::Fader::STATUS_FADE_OUT ||
           mpSceneFader->getStatus() == EGG::Fader::STATUS_FADE_OUT;
}

/**
 * @brief Tests whether all asynchronous tasks have finished
 */
bool RPSysSceneMgr::isTaskFinished() {
    if (RP_GET_INSTANCE(RPSysSaveDataMgr)->isNandAccessFinish() &&
        !RP_GET_INSTANCE(RPSysSystem)->getNandThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getDvdThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getWc24Thread()->isTaskExist()) {

        return true;
    }

    return false;
}

/**
 * @brief Tests whether a scene change would be allowed
 */
bool RPSysSceneMgr::isSceneChangeEnable() {
    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT &&
        RP_GET_INSTANCE(RPSysSaveDataMgr)->isNandAccessFinish() &&
        !RP_GET_INSTANCE(RPSysSystem)->getNandThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getDvdThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getWc24Thread()->isTaskExist()) {

        return true;
    }

    return false;
}

/**
 * @brief Updates the state of the scene fader
 *
 * @return Whether the fade has finished
 */
bool RPSysSceneMgr::calcSceneFader() {
    return mpSceneFader->calc();
}

/**
 * @brief Displays the state of the scene fader
 */
void RPSysSceneMgr::drawSceneFader() {
    mpSceneFader->draw();
}

/**
 * @brief Displays the state of the manager fader
 */
void RPSysSceneMgr::drawMgrFader() {
    mCurrentFader->draw();
}

/**
 * @brief Updates the state of the current scene
 */
void RPSysSceneMgr::calcCurrentScene() {
    updateState();
    EGG::SceneManager::calcCurrentScene();
}

/**
 * @brief Updates the state of this manager
 */
void RPSysSceneMgr::updateState() {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSystem)->setCallBack();
        return;
    }

    if (isSceneChangeEnable()) {
        bool success = false;

        if (mState == EState_SoftReset) {
            success = RP_GET_INSTANCE(RPSysSceneCreator)->changeSoftReset();

        } else if (mState == EState_ReturnToMenu || mState == EState_Shutdown) {
            // Dummy scene change to allow RPSysSceneCreator::destroy() to exit
            success = changeSceneAfterFadeOut(
                RPSysSceneCreator::ESceneID_RPSysBootScene);
        }

        if (success) {
            resetFadeFrame();

            if (mState == EState_SoftReset) {
                if (getCurrentSceneID() !=
                    RPSysSceneCreator::ESceneID_RPSysBootScene) {

                    resetFadeColor();
                }

                RP_GET_INSTANCE(RPSndAudioMgr)->resetSystem(DEFAULT_FADE_FRAME);
                mState = EState_Guard;

            } else if (mState == EState_ReturnToMenu ||
                       mState == EState_Shutdown) {

                setFadeColor(DEFAULT_FADE_COLOR);

                RP_GET_INSTANCE(RPSndAudioMgr)
                    ->shutdownSystem(DEFAULT_FADE_FRAME);
            }
        }
    }
}

/**
 * @brief Destructor
 */
RPSysSceneMgr::~RPSysSceneMgr() {}
