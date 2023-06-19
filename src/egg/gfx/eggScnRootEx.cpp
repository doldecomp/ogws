#include "eggScnRootEx.h"
#include "eggAssert.h"
#include "eggLightManager.h"
#include "eggLightTextureManager.h"
#include "eggFogManager.h"
#include "eggShadowTextureManager.h"
#include "eggScreen.h"
#include "eggStateGX.h"
#include "eggGXUtility.h"
#include "eggDrawGX.h"
#include "g3d_scnroot.h"

namespace EGG
{
    using namespace nw4r;

    ScnRootEx::ScnRootEx(g3d::ScnRoot *pScnRoot) :
        mBase(pScnRoot),
        mpLightManager(NULL),
        mpFogManager(NULL),
        mpShadowTextureManager(NULL),
        mSceneSettings(SCENE_SETTING_ALL),
        SHORT_0x12(0),
        mDrawSettings(DRAW_SETTING_ALL),
        mpScreen(NULL)
    {
        #line 64
        EGG_ASSERT(pScnRoot);
        u8 id = mBase->GetCurrentCameraID();
        pScnRoot->GetCamera(id).GetCameraMtx(&mCamMtx);

        mpShadowTextureManager = new ShadowTextureManager();
        #line 68
        EGG_ASSERT(mpShadowTextureManager);

        mpScreen = new Screen();
        #line 71
        EGG_ASSERT(mpScreen);

        WORD_0x4C = 0;
    }

    void ScnRootEx::configure()
    {
    }

    void ScnRootEx::setLightManager(LightManager *lightMgr)
    {
        mpLightManager = lightMgr;
    }

    void ScnRootEx::setFogManager(FogManager *fogMgr)
    {
        mpFogManager = fogMgr;
    }

    ScnRootEx::~ScnRootEx()
    {
        delete mpShadowTextureManager;
        mpShadowTextureManager = NULL;

        delete mpScreen;
        mpScreen = NULL;
    }

    void ScnRootEx::UpdateFrame()
    {
        if (mSceneSettings & SCENE_UPDATE_FRAME)
            mBase->UpdateFrame();
    }

    void ScnRootEx::CalcMaterial()
    {
        if (mSceneSettings & SCENE_CALC_MATERIAL)
            mBase->CalcMaterial();
    }

    void ScnRootEx::CalcVtx()
    {
        if (mSceneSettings & SCENE_CALC_VTX)
            mBase->CalcVtx();
    }

    void ScnRootEx::CalcWorld()
    {
        calc_before_CalcWorld();

        if (mSceneSettings & SCENE_CALC_WORLD)
        {
            mBase->CalcWorld();
            SHORT_0x12 |= 0x2;
        }

        calc_after_CalcWorld();
    }

    void ScnRootEx::SetCurrentCamera(int id, const math::MTX34& mtx, const Screen& screen)
    {
        SHORT_0x12 &= ~0x1;

        mBase->GetCamera(id).SetCameraMtxDirectly(mtx);
        SetCurrentCamera(id, screen);
    }

    void ScnRootEx::CalcView()
    {
        draw_before_CalcView();

        bool b = (mSceneSettings & 0x40) && (SHORT_0x12 & 0x2);

        if (b && (mSceneSettings & 0x1000) == 0)
            mBase->CalcView();
    }

    void ScnRootEx::GatherDrawScnObj()
    {
        if (mSceneSettings & SCENE_GATHER_DRAW_SCN_OBJ)
            mBase->GatherDrawScnObj();
    }

    void ScnRootEx::ZSort()
    {
        if (mSceneSettings & SCENE_Z_SORT)
            mBase->ZSort();
    }

    void ScnRootEx::DrawOpa()
    {
        if (mSceneSettings & SCENE_DRAW_OPA)
        {
            setDrawSettingGX(true);
            mBase->DrawOpa();
        }

        draw_after_DrawOpa();
    }

    void ScnRootEx::DrawXlu()
    {
        if (mSceneSettings & SCENE_DRAW_XLU)
        {
            setDrawSettingGX(false);
            mBase->DrawXlu();
        }

        draw_after_DrawOpaXlu();
    }

    void ScnRootEx::calc_before_CalcWorld()
    {
        if (mpLightManager != NULL)
        {
            mpLightManager->Calc(mBase);
        }

        if (mpFogManager != NULL)
        {
            mpFogManager->Calc();
            mpFogManager->CopyToG3D(mBase);
        }

        math::MTX34Identity(&mCamMtx);
    }

    void ScnRootEx::calc_after_CalcWorld()
    {
        if (mSceneSettings & 0x2)
            mpShadowTextureManager->Calc();
    }

    void ScnRootEx::SetCurrentCamera(u8 id, const Screen& screen)
    {
        mpScreen->CopyFromAnother(screen);
        mBase->SetCurrentCamera(id);

        g3d::Camera current = mBase->GetCurrentCamera();
        current.GetCameraMtx(&mCamMtx);
        mpScreen->CopyToG3D(current);

        DrawGX::s_cameraMtx = mCamMtx;
    }

    void ScnRootEx::draw_before_CalcView()
    {
        StateGX::resetStateCache();
        GXUtility::set(mBase->GetCurrentCameraID(), mCamMtx, getScreen());

        if (mpLightManager != NULL)
        {
            mpLightManager->CalcView(mCamMtx,
                mBase->GetCurrentCameraID(), mBase);
        }

        if (mpFogManager != NULL)
        {
            mpFogManager->UseScreenZ(getScreen());
        }

        if (mpLightManager != NULL &&
            mSceneSettings & SCENE_SETTING_0x1)
        {
            const Screen::DataEfb& efb = mpScreen->GetDataEfb();
            LightTextureManager *mgr = mpLightManager->GetLightTextureManager();

            mgr->draw(mpLightManager, efb,
                efb.vp.x1, efb.vp.y1, efb.vp.x2, efb.vp.y2);
        }

        if (mSceneSettings & SCENE_SETTING_0x2)
        {
            mpShadowTextureManager->Draw(mpScreen);
        }
    }

    void ScnRootEx::draw_after_DrawOpa()
    {
    }

    void ScnRootEx::draw_after_DrawOpaXlu()
    {
    }

    void ScnRootEx::finishDraw()
    {
        if (mpLightManager != NULL)
            mpLightManager->DoneDraw();

        if (mpFogManager != NULL)
            mpFogManager->DoneDraw();

        SHORT_0x12 |= 0x1;
        SHORT_0x12 &= ~0x2;
    }

    namespace
    {
        void UNUSED_ASSERTS_SCNROOTEX()
        {
            EGG_ASSERT_MSG(false,
                "Can't call this func if not isEnableDoubleBuffer().");
        }
    }

    void ScnRootEx::changeScnRoot(g3d::ScnRoot *pScnRoot)
    {
        #line 613
        EGG_ASSERT(pScnRoot != NULL);
        mBase = pScnRoot;
    }

    void ScnRootEx::setDrawSettingGX(bool opa) const
    {
        u32 setting = 0;

        if (opa)
        {
            if (mDrawSettings & DRAW_COLOR_UPDATE_OPA)
                setting |= GXUtility::ENABLE_COLOR_UPDATE;
            if (mDrawSettings & DRAW_ALPHA_UPDATE_OPA)
                setting |= GXUtility::ENABLE_ALPHA_UPDATE;
            if (mDrawSettings & DRAW_DITHER_OPA)
                setting |= GXUtility::ENABLE_DITHER;
        }
        else
        {
            if (mDrawSettings & DRAW_COLOR_UPDATE_XLU)
                setting |= GXUtility::ENABLE_COLOR_UPDATE;
            if (mDrawSettings & DRAW_ALPHA_UPDATE_XLU)
                setting |= GXUtility::ENABLE_ALPHA_UPDATE;
            if (mDrawSettings & DRAW_DITHER_XLU)
                setting |= GXUtility::ENABLE_DITHER;
        }

        GXUtility::setDrawSetting(setting);
        GXUtility::setScreenProjection(opa);
    }
}