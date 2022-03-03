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
        enum StateFlags
        {
            USE_TMEM = 0x10,
            VALID_CACHE = 0x20
        };

        enum CacheFlags
        {
            PROJECTIONV_CACHED = 0x1,
            VIEWPORT_CACHED = 0x2,
            SCISSOR_CACHED = 0x4,
            SCISSOR_BOX_CACHED = 0x8,
            DITHER_CACHED = 0x10,
            COLOR_UPDATE_CACHED = 0x20,
            ALPHA_UPDATE_CACHED = 0x40,
        };

        struct CachedState
        {
            u32 flags; // at 0x0
            int scissorOfsX; // at 0x4
            int scissorOfsY; // at 0x8
            bool colorUpdate; // at 0xC
            bool alphaUpdate; // at 0xD
            bool dither; // at 0xE
        };

    public:
        static GXPixelFmt getDefaultPixelFormat() { return sDefaultPixelFormat; }
        static const GXColor& getDefaultTexColor() { return sDefaultTexColor; }

        static void invalidateTexAllGX();
        static void resetGXCache();
        static void resetCache();
        static void resetGX();
        static void resetGXAttr();
        static void resetGXChans();
        static void resetGXTexMtx();
        static void resetGXTexObjs();
        static void resetGXTexCoords();
        static void resetGXTevs();
        static void resetGXFog();
        static void setupCache();
        static void GXSetProjection(Mtx44, int);
        static void GXSetProjectionv(const f32 *);
        static void GXSetViewport(f32, f32, f32, f32, f32, f32);
        static void GXSetScissor(u32, u32, u32, u32);
        static void GXSetScissorBoxOffset(int, int);
        static void GXSetColorUpdate(bool);
        static void GXSetAlphaUpdate(bool);
        static void GXSetDither(bool);
        static void GXSetPixelFmt(GXPixelFmt, UNKWORD);

    private:
        static CachedState sCache;
        static u8 sDefaultTexObjImage[4 * 4] __attribute__ ((aligned (32)));

        static const f32 lbl_80378C68[];
        static const f32 lbl_80378C80[];

        static u16 sScreenWidth;
        static u16 sScreenHeight;
        static GXPixelFmt sDefaultPixelFormat;
        static UNKWORD sDefaultPixelFormatArg2;
        static GXPixelFmt sCurrentPixelFormat;
        static UNKWORD sCurrentPixelFormatArg2;
        static GXColor sDefaultTexColor;

        static u16 sStateFlags;
        static f32 sModifyRatio;
        static nw4r::g3d::tmem::TMemLayout sTMemLayout;

        static const GXColor cDefaultGXColor;
    };
}

#endif