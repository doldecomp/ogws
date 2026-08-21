#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

namespace EGG {

ScnRootEx::ScnRootEx(nw4r::g3d::ScnRoot* pScnRoot)
    : mpScnRoot(pScnRoot),
      mpLightManager(NULL),
      mpFogManager(NULL),
      mpShadowTextureManager(NULL),
      mSceneSettings(cSceneSetting_Default),
      mFlags(0),
      mDrawSettings(cDrawSetting_Default),
      mpScreen(NULL) {

#line 64
    EGG_ASSERT(pScnRoot);

    u8 id = mpScnRoot->GetCurrentCameraID();
    pScnRoot->GetCamera(id).GetCameraMtx(&mCameraMtx);

    mpShadowTextureManager = new ShadowTextureManager();
#line 68
    EGG_ASSERT(mpShadowTextureManager);

    mpScreen = new Screen();
#line 71
    EGG_ASSERT(mpScreen);

    unk4C = 0;
}

void ScnRootEx::configure() {}

void ScnRootEx::setLightManager(LightManager* pLightManager) {
    mpLightManager = pLightManager;
}

void ScnRootEx::setFogManager(FogManager* pFogManager) {
    mpFogManager = pFogManager;
}

ScnRootEx::~ScnRootEx() {
    delete mpShadowTextureManager;
    mpShadowTextureManager = NULL;

    delete mpScreen;
    mpScreen = NULL;
}

void ScnRootEx::UpdateFrame() {
    if (mSceneSettings & cSceneSetting_UpdateFrame) {
        mpScnRoot->UpdateFrame();
    }
}

void ScnRootEx::CalcMaterial() {
    if (mSceneSettings & cSceneSetting_CalcMaterial) {
        mpScnRoot->CalcMaterial();
    }
}

void ScnRootEx::CalcVtx() {
    if (mSceneSettings & cSceneSetting_CalcVtx) {
        mpScnRoot->CalcVtx();
    }
}

void ScnRootEx::CalcWorld() {
    calc_before_CalcWorld();

    if (mSceneSettings & cSceneSetting_CalcWorld) {
        mpScnRoot->CalcWorld();
        mFlags |= cFlag_DoneCalcWorld;
    }

    calc_after_CalcWorld();
}

void ScnRootEx::SetCurrentCamera(int idx, const nw4r::math::MTX34& rCameraMtx,
                                 const Screen& rScreen) {
    mFlags &= ~cFlag_DoneDraw;

    mpScnRoot->GetCamera(idx).SetCameraMtxDirectly(rCameraMtx);
    SetCurrentCamera(idx, rScreen);
}

void ScnRootEx::CalcView() {
    draw_before_CalcView();

    bool calcViewReady = (mSceneSettings & cSceneSetting_CalcView) &&
                         (mFlags & cFlag_DoneCalcWorld);

    if (calcViewReady && !(mSceneSettings & cSceneSetting_12)) {
        mpScnRoot->CalcView();
    }
}

void ScnRootEx::GatherDrawScnObj() {
    if (mSceneSettings & cSceneSetting_GatherDrawScnObj) {
        mpScnRoot->GatherDrawScnObj();
    }
}

void ScnRootEx::ZSort() {
    if (mSceneSettings & cSceneSetting_ZSort) {
        mpScnRoot->ZSort();
    }
}

void ScnRootEx::DrawOpa() {
    if (mSceneSettings & cSceneSetting_DrawOpa) {
        setDrawSettingGX(true);
        mpScnRoot->DrawOpa();
    }

    draw_after_DrawOpa();
}

void ScnRootEx::DrawXlu() {
    if (mSceneSettings & cSceneSetting_DrawXlu) {
        setDrawSettingGX(false);
        mpScnRoot->DrawXlu();
    }

    draw_after_DrawOpaXlu();
}

void ScnRootEx::calc_before_CalcWorld() {
    if (mpLightManager != NULL) {
        mpLightManager->Calc(mpScnRoot);
    }

    if (mpFogManager != NULL) {
        mpFogManager->Calc();
        mpFogManager->CopyToG3D(mpScnRoot);
    }

    nw4r::math::MTX34Identity(&mCameraMtx);
}

void ScnRootEx::calc_after_CalcWorld() {
    if (mSceneSettings & cSceneSetting_ShadowTexture) {
        mpShadowTextureManager->Calc();
    }
}

void ScnRootEx::SetCurrentCamera(u8 idx, const Screen& rScreen) {
    mpScreen->CopyFromAnother(rScreen);
    mpScnRoot->SetCurrentCamera(idx);

    nw4r::g3d::Camera current = mpScnRoot->GetCurrentCamera();
    current.GetCameraMtx(&mCameraMtx);

    mpScreen->CopyToG3D(current);
    DrawGX::SetCameraMtx(mCameraMtx);
}

void ScnRootEx::draw_before_CalcView() {
    StateGX::resetGXCache();
    beginDrawView(mpScnRoot->GetCurrentCameraID(), mCameraMtx, getScreen());

    if (mpLightManager != NULL) {
        mpLightManager->CalcView(mCameraMtx, mpScnRoot->GetCurrentCameraID(),
                                 mpScnRoot);
    }

    if (mpFogManager != NULL) {
        mpFogManager->LoadScreenClip(getScreen());
    }

    if (mpLightManager != NULL &&
        (mSceneSettings & cSceneSetting_LightTexture)) {

        const Screen::DataEfb& rEfb = mpScreen->GetDataEfb();

        LightTextureManager* pLightTextureManager =
            mpLightManager->GetLightTextureManager();

        pLightTextureManager->drawAndCaptureTexture(
            mpLightManager, rEfb, rEfb.vp.x, rEfb.vp.y, rEfb.vp.width,
            rEfb.vp.height);
    }

    if (mSceneSettings & cSceneSetting_ShadowTexture) {
        mpShadowTextureManager->Draw(mpScreen);
    }
}

void ScnRootEx::draw_after_DrawOpa() {}

void ScnRootEx::draw_after_DrawOpaXlu() {}

void ScnRootEx::finishDraw() {
    if (mpLightManager != NULL) {
        mpLightManager->DoneDraw();
    }

    if (mpFogManager != NULL) {
        mpFogManager->DoneDraw();
    }

    mFlags |= cFlag_DoneDraw;
    mFlags &= ~cFlag_DoneCalcWorld;
}

DECOMP_FORCEACTIVE(eggScnRootEx_cpp,
                  "Can't call this func if not isEnableDoubleBuffer().");

void ScnRootEx::changeScnRoot(nw4r::g3d::ScnRoot* pScnRoot) {
#line 613
    EGG_ASSERT(pScnRoot != NULL);
    mpScnRoot = pScnRoot;
}

void ScnRootEx::setDrawSettingGX(bool opa) const {
    u32 drawFlags = 0;

    if (opa) {
        if (mDrawSettings & cDrawSetting_ColorUpdateOpa) {
            drawFlags |= cFlag_ColorUpdate;
        }
        if (mDrawSettings & cDrawSetting_AlphaUpdateOpa) {
            drawFlags |= cFlag_AlphaUpdate;
        }
        if (mDrawSettings & cDrawSetting_DitherOpa) {
            drawFlags |= cFlag_Dither;
        }

    } else {
        if (mDrawSettings & cDrawSetting_ColorUpdateXlu) {
            drawFlags |= cFlag_ColorUpdate;
        }
        if (mDrawSettings & cDrawSetting_AlphaUpdateXlu) {
            drawFlags |= cFlag_AlphaUpdate;
        }
        if (mDrawSettings & cDrawSetting_DitherXlu) {
            drawFlags |= cFlag_Dither;
        }
    }

    setDrawFlag(drawFlags);
    IDrawGX::setDrawSettingGX(opa);
}

} // namespace EGG
