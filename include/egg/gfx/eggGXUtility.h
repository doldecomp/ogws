#ifndef EGG_GFX_GX_UTILITY_H
#define EGG_GFX_GX_UTILITY_H
#include "types_egg.h"
#include "types_nw4r.h"
#include <GX/GXTexture.h>
#include <math/mtx.h>

namespace EGG
{
    class GXUtility
    {
    public:
        // Unofficial symbol
        static u8 getTexCoordGenVal(int);

        static void setScaleOffsetPerspective(f32 *, f32, f32, f32, f32);
        static void getTexObj(GXTexObj *, const ResTIMG&);

        // Unofficial symbols
        static void getTexObj(GXTexObj *, const nw4r::g3d::ResTex&, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
        static void func_800a1b6c(u16, Mtx, UNKTYPE *);
        static void func_800a1b88(UNKTYPE *);

    private:
        // Unofficial symbol
        static u8 sTexCoordGenVals[8];
    };
}

#endif