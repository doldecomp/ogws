#ifndef EGG_GFX_STATE_GX_H
#define EGG_GFX_STATE_GX_H
#include "types_egg.h"
#include "g3d_tmem.h"
#include <revolution/GX.h>
#include <revolution/MTX.h>

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

        struct ScopedColor
        {
            ScopedColor(bool x)
            {
                old = sCache.colorUpdate;
                GXSetColorUpdate_(x);
            }

            ~ScopedColor()
            {
                GXSetColorUpdate_(old);
            }

            bool old;
        };

        struct ScopedAlpha
        {
            ScopedAlpha(bool x)
            {
                old = sCache.alphaUpdate;
                GXSetAlphaUpdate_(x);
            }

            ~ScopedAlpha()
            {
                GXSetAlphaUpdate_(old);
            }

            bool old;
        };

        struct ScopedDither
        {
            ScopedDither(bool x)
            {
                old = sCache.dither;
                GXSetDither_(x);
            }

            ~ScopedDither()
            {
                GXSetDither_(old);
            }

            bool old;
        };

    public:
        static GXPixelFmt getDefaultPixelFormat() { return s_pixFormat; }
        static UNKWORD getDefaultPixelFormatArg2() { return sDefaultPixelFormatArg2; }
        static GXColor& getDefaultTexColor() { return sDefaultTexColor; }
        static void setDefaultTexColor(GXColor c) { sDefaultTexColor = c; }
        static u16 getEfbWidth() { return s_widthFb; } 
        static void setEfbWidth(u16 w) { s_widthFb = w; }
        static u16 getEfbHeight() { return s_heightEfb; } 
        static void setEfbHeight(u16 h) { s_heightEfb = h; }

        static void initialize();
        static void frameInit();
        static void doResetStateCache();
        static void resetGX();
        static void resetVtx();
        static void resetColorChannel();
        static void resetIndirect();
        static void resetTexture();
        static void resetTexGen();
        static void resetTev();
        static void resetPE();
        static void resetStateCache();
        static void GXSetProjection_(Mtx44, int);
        static void GXSetProjectionv_(const f32 *);
        static void GXSetViewport_(f32, f32, f32, f32, f32, f32);
        static void GXSetScissor_(u32, u32, u32, u32);
        static void GXSetScissorBoxOffset_(int, int);
        static void GXSetColorUpdate_(bool);
        static void GXSetAlphaUpdate_(bool);
        static void GXSetDither_(bool);
        static void GXSetPixelFmt_(GXPixelFmt, UNKWORD);

    private:
        static CachedState sCache;
        static u8 sDefaultTexObjImage[4 * 4] __attribute__ ((aligned (32)));

        static const f32 lbl_80378C68[2][3];
        static const f32 lbl_80378C80[];

        static u16 s_widthFb;
        static u16 s_heightEfb;
        static GXPixelFmt s_pixFormat;
        static UNKWORD sDefaultPixelFormatArg2;
        static GXPixelFmt s_pixFormatCurrent;
        static UNKWORD sCurrentPixelFormatArg2;
        static GXColor sDefaultTexColor;

        static u16 sStateFlags;
        static f32 sModifyRatio;
        static nw4r::g3d::tmem::TMemLayout sTMemLayout;

        static const GXColor cDefaultGXColor;
    };
}

#endif
