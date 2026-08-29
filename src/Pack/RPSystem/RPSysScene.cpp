#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

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
 * @brief Sets the current frame of both faders
 *
 * @param frame Frame count
 */
void RPSysScene::setFadeFrame(u16 frame) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setFadeFrame(frame);
}

/**
 * @brief Gets the color of the manager fader
 */
nw4r::ut::Color RPSysScene::getFadeColor() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->getMgrFadeColor();
}

/**
 * @brief Sets the color of both faders
 *
 * @param color Fade color
 */
void RPSysScene::setFadeColor(nw4r::ut::Color color) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setSceneFadeColor(color);
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
 */
void RPSysScene::startFadeIn() {
    RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeIn();
}

/**
 * @brief Begins fading out the scene fader
 */
void RPSysScene::startFadeOut() {
    RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeOut();
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
 * @brief Enters the scene
 */
void RPSysScene::enter() {
    ;
}

void RPSysScene::outgoingScene() {
    RPSysCoreController::stopMotorAll();

    RP_GET_INSTANCE(RPSysEffectMgr)->stopAllEffect();
    RP_GET_INSTANCE(RPSysEffectMgr)->resetCreator(mpEffectCreator);
}

/**
 * @brief Re-initializes the scene
 */
void RPSysScene::reinit() {
    ;
}

/**
 * @brief Prepares for destruction of (and transition from) a child scene
 */
void RPSysScene::incoming_childDestroy() {
    ;
}

/**
 * @brief Updates the scene state
 */
void RPSysScene::calc() {
    ;
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

void RPSysScene::init() {
    ;
}

void RPSysScene::setCreatorSceneID(s32 id) {
    mCreatorSceneID = id;
}

s32 RPSysScene::getCreatorSceneID() const {
    return mCreatorSceneID;
}
