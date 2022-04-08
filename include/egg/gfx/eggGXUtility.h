#ifndef EGG_GFX_GX_UTILITY_H
#define EGG_GFX_GX_UTILITY_H
#include "types_egg.h"
#include "eggIDrawGX.h"
#include "types_nw4r.h"
#include <GX/GXTexture.h>
#include <math/mtx.h>

namespace EGG
{
    class GXUtility : public IDrawGX
    {
    public:
        typedef UNKTYPE (* ProjectionCallback)(UNKWORD, bool);

        enum DrawSetting
        {
            ENABLE_COLOR_UPDATE = 0x1,
            ENABLE_ALPHA_UPDATE = 0x2,
            ENABLE_DITHER = 0x4,
        };

    public:
        static u8 getTexCoordGenVal(int);
        static void setScaleOffsetPerspective(f32 *, f32, f32, f32, f32);
        static void getTexObj(GXTexObj *, const ResTIMG&);
        static void getTexObj(GXTexObj *, const nw4r::g3d::ResTex&, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
        static void set(u16, Matrix34f&, eggScreen&);
        static void setScreenProjection(bool);

        static void setDrawSetting(u32 setting) { sDrawSettings = setting; }

    private:
        static const u8 sTexCoordGenVals[];
        static ProjectionCallback sProjectionCallback;
        static UNKWORD sProjectionCallbackArg;
        static u16 lbl_804BEC7C;
        static u32 sDrawSettings;
        static Matrix34f sCameraMtx;
    };
}

#endif