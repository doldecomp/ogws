#include <Pack/RPGraphics.h>
#include <Pack/RPSystem.h>

/**
* @brief Constructor
*/
// TODO(ThePlayerRolo): Could there be a constructor of RPGrpScreen that sets the canvas mode only?
RPSysCommonObject::RPSysCommonObject() {
    RPGrpRenderer* renderer = RPGrpRenderer::GetCurrent();

    RPGrpScreen* screen = new RPGrpScreen();
    screen->SetCanvasMode(EGG::Frustum::CANVAS_CC);
    renderer->CreateView2D(RPGrpRenderer::VIEW_29, screen);

    RPGrpRenderer::GetCurrent()->get_88()->_1 = 15;

    RPGrpScreen* screen2 = new RPGrpScreen();
    screen2->SetCanvasMode(EGG::Frustum::CANVAS_CC);
    renderer->CreateView2D(RPGrpRenderer::VIEW_31, screen2);

    RPGrpRenderer::GetCurrent()->AppendDrawObject(this);
}

/**
* @brief Initializes common objects' state
*/
void RPSysCommonObject::init() {
    RPSysTutorialWinMgr::instance()->init();
    RPSysSystemWinMgr::instance()->init();
    RPSysCursorDrawMgr::instance()->init();
    RPSysHomeMenuMgr::instance()->init();
    RPSysPauseMgr::instance()->init();
}

/**
* @brief Updates common objects' state before the scene gets to update
*/
void RPSysCommonObject::preUpdate() {
    if (RPSysSceneMgr::instance()->isNormalState() && !RPSysHomeMenuMgr::instance()->isOpen()) {
        RPSysCursorDrawMgr::instance()->preUpdate();
        if (RPSysSystemWinMgr::instance()->getUnk8C() == 0) {
            RPSysPauseMgr::instance()->update();
        }
    }
    RPSysHomeMenuMgr::instance()->update();
}

/**
* @brief Updates common objects' state after the scene gets to update
*/
void RPSysCommonObject::postUpdate() {
    if (RPSysSceneMgr::instance()->isNormalState() && !RPSysHomeMenuMgr::instance()->isOpen()) {
        RPSysCursorDrawMgr::instance()->postUpdate();

        if (RPSysPauseMgr::instance()->isPause()) {
            RPSysEffectMgr::instance()->update(1);
            return;
        }

        RPSysTutorialWinMgr::instance()->calc();
        RPSysSystemWinMgr::instance()->update();
        RPSysEffectMgr::instance()->update(0);
        RPSysSceneMgr::instance()->calcSceneFader();
    }
}

/**
* @brief Renders common objects' state
*/
void RPSysCommonObject::UserDraw() {
    RPGrpRenderer::E_VIEW currentViewID = RPGrpRenderer::GetCurrentViewID();
    RPGrpRenderer::E_RENDERPASS currentRenderPass = RPGrpRenderer::GetCurrentRenderPass();

    if (currentViewID == RPGrpRenderer::VIEW_29) {
        if (currentRenderPass == RPGrpRenderer::RENDERPASS_SYSDRAW) {
            RPSysSceneMgr::instance()->drawSceneFader();
        } else if (currentRenderPass == RPGrpRenderer::RENDERPASS_DRAW2D) {
            RPSysTutorialWinMgr::instance()->draw();
            RPSysPauseMgr::instance()->draw();
            RPSysSystemWinMgr::instance()->draw();
        }
    } else if (currentViewID == RPGrpRenderer::VIEW_31 && currentRenderPass == RPGrpRenderer::RENDERPASS_DRAW2D) {
        RPSysHomeMenuMgr::instance()->draw();
    }
}
