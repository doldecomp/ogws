#include <RPGraphics.h>
#include <RPKernel.h>

static bool renderState;

void RPGrpRenderer::Begin() {
    f32 modify;

    sRendering = FALSE;
    sRenderPass = RENDERPASS_BEGIN;
    spCurrentScreen = &RPGrpScreen::GetRootScreen();
    EGG::GfxEngine::beginDraw();
    modify = RP_GET_INSTANCE(RPSysSystem)->getModifyRatio();
    EGG::StateGX::setModifyRatio(modify);
}

void RPGrpRenderer::StartDebugDraw() {
    EGG::Matrix34f mtx;

    RPGrpScreen clone(RPGrpScreen::GetRootScreen());
    clone.SetNearZ(0.0f);
    clone.SetFarZ(1.0f);
    clone.SetProjectionType(EGG::Frustum::PROJ_ORTHO);
    clone.SetProjectionGX();

    nw4r::math::MTX34Identity(&mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXLoadNrmMtxImm(mtx, GX_PNMTX0);
}

void RPGrpRenderer::End() {
    sRenderPass = RENDERPASS_END;
}

RPGrpViewRender3D* RPGrpRenderer::CreateView3D(u8 viewNo, RPGrpCamera* camera,
                                               RPGrpScreen* screen) {
    RPGrpViewRender3D* render = new RPGrpViewRender3D(viewNo);

    render->Configure();
    render->AttachCamera(camera);
    render->AttachScreen(screen);

    return render;
}

void RPGrpRenderer::AppendDrawObject(IRPGrpDrawObject* pObject) {
    if (pObject) {
        mpDrawObj = pObject;
    } else {
        mpDrawObj = pObject;
        mpDrawList = pObject;
    }
}
