#ifndef EGG_GFXE_SCN_ROOT_EX_H
#define EGG_GFXE_SCN_ROOT_EX_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggIDrawGX.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#define CALC_BEFORE_DECL(x) virtual void calc_before_##x()
#define CALC_AFTER_DECL(x) virtual void calc_after_##x()

#define DRAW_BEFORE_DECL(x) virtual void draw_before_##x()
#define DRAW_AFTER_DECL(x) virtual void draw_after_##x()

namespace EGG {

class ScnRootEx : public IDrawGX {
protected:
    nw4r::g3d::ScnRoot* mpScnRoot;                // at 0x0
    LightManager* mpLightManager;                 // at 0x4
    FogManager* mpFogManager;                     // at 0x8
    ShadowTextureManager* mpShadowTextureManager; // at 0xC
    u16 mSceneSettings;                           // at 0x10
    u16 mFlags;                                   // at 0x12
    u16 mDrawSettings;                            // at 0x14
    nw4r::math::MTX34 mCameraMtx;                 // at 0x18
    Screen* mpScreen;                             // at 0x48
    u32 unk4C;

public:
    ScnRootEx(nw4r::g3d::ScnRoot* pScnRoot);
    virtual ~ScnRootEx(); // at 0x8

    virtual void configure();                                 // at 0xC
    virtual void finishDraw();                                // at 0x10
    virtual void changeScnRoot(nw4r::g3d::ScnRoot* pScnRoot); // at 0x14

    CALC_BEFORE_DECL(CalcWorld); // at 0x18
    CALC_AFTER_DECL(CalcWorld);  // at 0x1C

    virtual void SetCurrentCamera(u8 idx, const Screen& rScreen); // at 0x20

    DRAW_BEFORE_DECL(CalcView);  // at 0x24
    DRAW_AFTER_DECL(DrawOpa);    // at 0x28
    DRAW_AFTER_DECL(DrawOpaXlu); // at 0x2C

    void setLightManager(LightManager* pLightManager);
    void setFogManager(FogManager* pFogManager);

    void UpdateFrame();

    void CalcMaterial();
    void CalcVtx();
    void CalcWorld();

    void SetCurrentCamera(int idx, const nw4r::math::MTX34& rCameraMtx,
                          const Screen& rScreen);

    void CalcView();

    void GatherDrawScnObj();
    void ZSort();

    void DrawOpa();
    void DrawXlu();

    void setDrawSettingGX(bool opa) const;

    LightManager* getLightManager() const {
        return mpLightManager;
    }
    FogManager* getFogManager() const {
        return mpFogManager;
    }
    ShadowTextureManager* getShadowTextureManager() const {
        return mpShadowTextureManager;
    }

    Screen& getScreen() const {
#line 171
        EGG_ASSERT(mpScreen);
        return *mpScreen;
    }

protected:
    enum SceneSetting {
        cSceneSetting_LightTexture = 1 << 0,
        cSceneSetting_ShadowTexture = 1 << 1,
        cSceneSetting_UpdateFrame = 1 << 2,
        cSceneSetting_CalcWorld = 1 << 3,
        cSceneSetting_CalcMaterial = 1 << 4,
        cSceneSetting_CalcVtx = 1 << 5,
        cSceneSetting_CalcView = 1 << 6,
        cSceneSetting_GatherDrawScnObj = 1 << 7,
        cSceneSetting_ZSort = 1 << 8,
        cSceneSetting_DrawOpa = 1 << 9,
        cSceneSetting_DrawXlu = 1 << 10,
        cSceneSetting_12 = 1 << 12,

        cSceneSetting_Default =
            cSceneSetting_LightTexture | cSceneSetting_ShadowTexture | //
            cSceneSetting_UpdateFrame |                                //
            cSceneSetting_CalcWorld | cSceneSetting_CalcMaterial |
            cSceneSetting_CalcVtx | cSceneSetting_CalcView | //
            cSceneSetting_GatherDrawScnObj |                 //
            cSceneSetting_ZSort |                            //
            cSceneSetting_DrawOpa | cSceneSetting_DrawXlu
    };

    enum DrawSetting {
        cDrawSetting_ColorUpdateOpa = 1 << 0,
        cDrawSetting_AlphaUpdateOpa = 1 << 1,
        cDrawSetting_DitherOpa = 1 << 2,

        cDrawSetting_ColorUpdateXlu = 1 << 3,
        cDrawSetting_AlphaUpdateXlu = 1 << 4,
        cDrawSetting_DitherXlu = 1 << 5,

        cDrawSetting_Default =
            cDrawSetting_ColorUpdateOpa | cDrawSetting_AlphaUpdateOpa |
            cDrawSetting_DitherOpa | //
            cDrawSetting_ColorUpdateXlu | cDrawSetting_AlphaUpdateXlu |
            cDrawSetting_DitherXlu
    };

    enum {
        cFlag_DoneDraw = 1 << 0,
        cFlag_DoneCalcWorld = 1 << 1,
    };
};

} // namespace EGG

#endif
