#include <Pack/RPGraphics.h>

/**
 * @brief Constructor
 *
 * @param no View ID
 */
RPGrpViewRender3D::RPGrpViewRender3D(u8 no)
    : RPGrpView(no), mpCamera(NULL), unk24(0) {

    mProjType = EProjType_Persp;
}

/**
 * @brief Updates this view's state
 */
void RPGrpViewRender3D::Calc() {
    RPGrpView::Calc();

    if (!IsSysCalc()) {
        return;
    }

    if (GetCamera() == NULL) {
        return;
    }

    GetCamera()->SaveCameraMatrix();
}

/**
 * @brief Prepares this view for a new frame
 */
void RPGrpViewRender3D::PrepareDraw() {
    RPGrpView::PrepareDraw();

    if (!IsSysCalc()) {
        return;
    }

    ClearBuffer();

    if (!IsSysDraw()) {
        return;
    }

    RPGrpModelScene* pModelScene =
        RPGrpModelManager::GetCurrent()->GetModelScene(mDrawScene);

    RPGrpScreen clone(*GetEnableScreen());

    clone.SetProjectionType(mProjType == EProjType_Persp
                                ? EGG::Screen::PROJ_PERSP
                                : EGG::Screen::PROJ_ORTHO);

    pModelScene->DrawPrepare(GetEnableCamera(), &clone);
}

/**
 * @brief Renders the contents of this view
 */
void RPGrpViewRender3D::Draw() {
    if (!IsSysCalc()) {
        return;
    }

    if (!IsSysDraw()) {
        return;
    }

    RPGrpModelScene* pModelScene =
        RPGrpModelManager::GetCurrent()->GetModelScene(mDrawScene);

    pModelScene->Draw();
}

/**
 * @brief Prepares this view for a new render pass
 */
void RPGrpViewRender3D::PrepareDrawGX() {
    if (IsSysDraw()) {
        RPGrpModelScene* pModelScene =
            RPGrpModelManager::GetCurrent()->GetModelScene(mDrawScene);

        pModelScene->PreConditionForRenderingGX();
    } else {
        SetProjectionGX();
    }
}

/**
 * @brief Attaches a new camera to this view
 *
 * @param pCamera New camera
 * @return Previously attached camera
 */
RPGrpCamera* RPGrpViewRender3D::AttachCamera(RPGrpCamera* pCamera) {
    RPGrpCamera* pOldCamera = mpCamera;
    mpCamera = pCamera;
    return pOldCamera;
}
