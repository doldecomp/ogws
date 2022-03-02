#ifndef EGG_GFX_STATE_GX_H
#define EGG_GFX_STATE_GX_H
#include "types_egg.h"
#include "g3d_tmem.h"
#include <RevoSDK/GX/GX.h>
#include <RevoSDK/GX/GXPixel.h>
#include <RevoSDK/math/mtx44.h>

namespace EGG
{
    class StateGX
    {
    public:
        static void func_80083E18();
        static void func_80083E5C();
        static void func_80083EBC();
        static void func_80083EC0();
        static void func_80083EF8();
        static void func_80084034();
        static void func_80084110();
        static void func_80084188();
        static void func_8008422C();
        static void func_800842E0();
        static void func_80084490();
        static void func_80084548();

        static void GXSetProjection(Mtx, int);
        static void GXSetProjectionv(const f32 *);
        static void GXSetViewport(f32, f32, f32, f32, f32, f32);

        static void GXSetColorUpdate(bool);
        static void GXSetAlphaUpdate(bool);
        static void GXSetDither(bool);

    public:
        static GXColor sDefaultTexColor;

    private:
        static u16 sStateFlags1; // 804BD480
        static nw4r::g3d::tmem::TMemLayout sTMemLayout; // 804BD488

        static u32 sStateFlags2; // 80409720
        static u8 sTexObjImage[4 * 4] __attribute__ ((aligned (32))); // 80409740

        static const GXColor cAmbColorWhite;
    };
}

#endif