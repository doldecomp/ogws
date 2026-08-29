#include <Pack/RPAudio.h>
#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <revolution/GX.h>

RPSysScene::UnkStruct RPSysScene::sUnkStruct;

/**
 * @brief Tests whether the scene is fully visible
 */
bool RPSysScene::isSceneDisplay() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->isDisplay();
}

/**
 * @brief Tests whether the scene is visibly obscured
 */
bool RPSysScene::isSceneBlank() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->isBlank();
}

/**
 * @brief Tests whether a scene change would be allowed
 */
bool RPSysScene::isSceneChangeEnable() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->isSceneChangeEnable();
}

/**
 * @brief Tests whether NAND access would be safe
 */
bool RPSysScene::isNandAccessEnable() const {
    return !RP_GET_INSTANCE(RPSysSceneMgr)->isFadeOut() &&
           RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished();
}

/**
 * @brief Sets the duration of all faders
 *
 * @param frame Fade duration, in frames
 */
void RPSysScene::setFadeFrame(u16 frame) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setFadeFrame(frame);
}

/**
 * @brief Gets the color of the manager fader
 */
nw4r::ut::Color RPSysScene::getFadeColor() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->getFadeColor();
}

/**
 * @brief Sets the color of all faders
 *
 * @param color Fade color
 */
void RPSysScene::setFadeColor(nw4r::ut::Color color) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setFadeColor(color);
}

/**
 * @brief Sets the color of the scene fader
 *
 * @param color Fade color
 */
void RPSysScene::setSceneFadeColor(nw4r::ut::Color color) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setSceneFadeColor(color);
}

/**
 * @brief Begins fading in the scene fader
 *
 * @return Success
 */
bool RPSysScene::startFadeIn() {
    return RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeIn();
}

/**
 * @brief Begins fading out the scene fader
 *
 * @return Success
 */
bool RPSysScene::startFadeOut() {
    return RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeOut();
}

/**
 * @brief Toggles screen dimming
 * @note If "Screen Saver Mode" is disabled, dimming is always OFF.
 *
 * @param enable Whether to dim the screen
 */
void RPSysScene::setDimming(bool enable) {
    RP_GET_INSTANCE(RPSysSystem)->setDimming(enable);
}

/**
 * @brief Constructor
 */
RPSysScene::RPSysScene()
    : mpRenderer(NULL),
      mpCommonObject(NULL),
      mpEffectCreator(NULL),
      mpSceneHeap(NULL),
      mCreatorSceneID(-1) {}

/**
 * @brief Prepares this scene to be entered
 */
void RPSysScene::incomingScene() {
    RPSysCoreController::initScene();

    RP_GET_INSTANCE(RPSysTextWriter)->Reset();

    if (!mFlags.onBit(EFlag_IsChild)) {
        initTaskAsync();
    }

    mpRenderer->BecomeCurrent();
    mpCommonObject->init();

    RP_GET_INSTANCE(RPSysSceneMgr)->resetFadeColor();
    RP_GET_INSTANCE(RPSysSceneMgr)->resetFadeFrame();
    RP_GET_INSTANCE(RPSysSceneMgr)
        ->setSceneStatus(EGG::Fader::STATUS_PREPARE_OUT);

    RP_GET_INSTANCE(RPSysSceneMgr)->resetGuard();
    setDimming(true);

    RP_GET_INSTANCE(RPSysEffectMgr)
        ->setCreator(mpEffectCreator, RPSysEffectMgr::EEffectScene_Scene);

    Reset();

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->startMgrFadeIn();
    }
}

/**
 * @brief Enters the scene
 */
void RPSysScene::enter() {
    init();
    Configure();

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->drawMgrFader();

        load();
        loadMessage();
    }

    incomingScene();
}

/**
 * @brief Prepares this scene to be exited
 */
void RPSysScene::outgoingScene() {
    RPSysCoreController::stopMotorAll();

    RP_GET_INSTANCE(RPSysEffectMgr)->stopAllEffect();
    RP_GET_INSTANCE(RPSysEffectMgr)->resetCreator(mpEffectCreator);
}

/**
 * @brief Re-initializes the scene
 */
void RPSysScene::reinit() {
    outgoingScene();
    incomingScene();
}

/**
 * @brief Prepares for destruction of (and transition from) a child scene
 */
void RPSysScene::incoming_childDestroy() {
    incomingScene();
}

/**
 * @brief Updates the scene state
 */
void RPSysScene::calc() {
    if (!RP_GET_INSTANCE(RPSysDvdStatus)->isErrorOccured()) {
        mpCommonObject->preUpdate();

        loadUpdate();

        if (RP_GET_INSTANCE(RPSysSceneMgr)->isNormalState() &&
            !RP_GET_INSTANCE(RPSysHomeMenuMgr)->isOpen() &&
            !RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {

            mpRenderer->PreCalculate();
            Calculate();
            mpRenderer->PostCalculate();
        } else {
            mpRenderer->CalculateInPause();
        }

        RP_GET_INSTANCE(RP_DEBUG_STUB_0)->Calculate();
        RP_GET_INSTANCE(RPSysHostIOSocketManager)->Update();

        mpCommonObject->postUpdate();
    }

    updateDvdEndMessage();
    updateNandEndMessage();
}

/**
 * @brief Renders the scene state
 */
void RPSysScene::draw() {
    RP_GET_INSTANCE(RPSysKokeshiManager)->UpdateCtrlMgr();

    RPGrpRenderer::Begin();
    {
        mpRenderer->Rendering();

        RPGrpRenderer::StartDebugDraw();
        RP_GET_INSTANCE(RP_DEBUG_STUB_0)->DebugDraw();
    }
    RPGrpRenderer::End();
}

/**
 * @brief Prepares for creation of (and transition to) a child scene
 */
void RPSysScene::outgoing_childCreate() {
    outgoingScene();
}

/**
 * @brief Finalizes this scene after being exited
 */
void RPSysScene::exitScenePost() {
    GXDrawDone();
    mpRenderer->Destruct();

    if (mpSceneHeap != NULL) {
        RP_GET_INSTANCE(RPSysSystem)->destroyHeap(mpSceneHeap);
    }
}

/**
 * @brief Exits the scene
 */
void RPSysScene::exit() {
    outgoingScene();
    Exit();
    exitScenePost();
}

/**
 * @brief Initializes this scene's members
 */
void RPSysScene::init() {
    EGG::Allocator* pAllocator = new EGG::Allocator(getHeap());
    mpRenderer = RPGrpRenderer::Construct(pAllocator, getSceneID());

    mpRenderer->BecomeCurrent();
    RPGrpRenderer::GetCurrent()->AppendDrawObject(*this);

    mpCommonObject = new RPSysCommonObject();

    mpEffectCreator =
        new RPSysEffectCreator(RPSysEffectMgr::EEffectScene_Scene);

    RP_GET_INSTANCE(RPSysKokeshiManager)->Reset();

    RPSysSceneCreator::EAudioType audioType =
        RP_GET_INSTANCE(RPSysSceneCreator)->getAudioType(getSceneID());

    if (audioType == RPSysSceneCreator::EAudioType_Common) {
        RP_GET_INSTANCE(RPSndAudioMgr)->configureTitle();
    }

    RPSysSceneCreator::EExitType exitType =
        RP_GET_INSTANCE(RPSysSceneCreator)->getExitType(getSceneID());

    if (exitType == RPSysSceneCreator::EExitType_Standard) {
        RP_GET_INSTANCE(RPSysPlayerMgr)->loadAllData();

    } else if (exitType == RPSysSceneCreator::EExitType_Sibling ||
               exitType == RPSysSceneCreator::EExitType_2) {

        RP_GET_INSTANCE(RPSysPlayerMgr)->reset();
    }
}

/**
 * @brief Sets this scene's parent/creator ID
 *
 * @param id ID of this scene's parent/creator
 */
void RPSysScene::setCreatorSceneID(s32 id) {
    mCreatorSceneID = id;
}

/**
 * @brief Gets this scene's parent/creator ID
 */
s32 RPSysScene::getCreatorSceneID() const {
    return mCreatorSceneID;
}

/**
 * @brief Marks this scene as a child of the previous scene
 */
void RPSysScene::setChildScene() {
    mFlags.setBit(EFlag_IsChild);
}
