#ifndef EGG_GFX_SCN_ROOT_EX_H
#define EGG_GFX_SCN_ROOT_EX_H
#include "types_egg.h"
#include "types_nw4r.h"
#include "eggMatrix.h"
#include "eggAssert.h"

namespace EGG
{
    class ScnRootEx
    {
    public:
        enum SceneSetting
        {
            SCENE_SETTING_0x1 = (1 << 0),
            SCENE_SETTING_0x2 = (1 << 1),
            SCENE_UPDATE_FRAME = (1 << 2),
            SCENE_CALC_WORLD = (1 << 3),
            SCENE_CALC_MATERIAL = (1 << 4),
            SCENE_CALC_VTX = (1 << 5),
            SCENE_SETTING_0x40 = (1 << 6),
            SCENE_GATHER_DRAW_SCN_OBJ = (1 << 7),
            SCENE_Z_SORT = (1 << 8),
            SCENE_DRAW_OPA = (1 << 9),
            SCENE_DRAW_XLU = (1 << 10),

            SCENE_SETTING_MAX = (1 << 11),
            SCENE_SETTING_ALL = SCENE_SETTING_MAX - 1
        };

        enum DrawSetting
        {
            DRAW_COLOR_UPDATE_OPA = (1 << 0),
            DRAW_ALPHA_UPDATE_OPA = (1 << 1),
            DRAW_DITHER_OPA = (1 << 2),
            DRAW_COLOR_UPDATE_XLU = (1 << 3),
            DRAW_ALPHA_UPDATE_XLU = (1 << 4),
            DRAW_DITHER_XLU = (1 << 5),

            DRAW_SETTING_MAX = (1 << 6),
            DRAW_SETTING_ALL = DRAW_SETTING_MAX - 1
        };

    protected:
        nw4r::g3d::ScnRoot *mBase; // at 0x0
        LightManager *mpLightManager; // at 0x4
        FogManager *mpFogManager; // at 0x8
        ShadowTextureManager *mpShadowTextureManager; // at 0xC
        u16 mSceneSettings; // at 0x10
        u16 SHORT_0x12;
        u16 mDrawSettings; // at 0x14
        Matrix34f mCamMtx; // 0x18
        eggScreen *mpScreen; // at 0x48
        UNKWORD WORD_0x4C;

    public:
        ScnRootEx(nw4r::g3d::ScnRoot *);
        virtual ~ScnRootEx(); // at 0x8
        virtual void configure(); // at 0xC
        virtual void finishDraw(); // at 0x10
        virtual void changeScnRoot(nw4r::g3d::ScnRoot *); // at 0x14
        virtual void calc_before_CalcWorld(); // at 0x18
        virtual void calc_after_CalcWorld(); // at 0x1C
        virtual void setCurrentCamera(u8, const eggScreen&); // at 0x20
        virtual void draw_before_CalcView(); // at 0x24
        virtual void draw_after_DrawOpa(); // at 0x28
        virtual void draw_after_DrawOpaXlu(); // at 0x2C

        void setLightManager(LightManager *);
        void setFogManager(FogManager *);

        void UpdateFrame();
        void CalcMaterial();
        void CalcVtx();
        void CalcWorld();
        void SetCurrentCamera(int, const Matrix34f&, const eggScreen&);
        void CalcView();
        void GatherDrawScnObj();
        void ZSort();
        void DrawOpa();
        void DrawXlu();

        void setDrawSettingGX(bool) const;

        eggScreen& getScreen() const
        {
            #line 171
            EGG_ASSERT(mpScreen);
            return *mpScreen;
        }
    };
}

#endif