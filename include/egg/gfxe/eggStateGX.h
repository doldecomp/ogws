#ifndef EGG_GFXE_STATE_GX_H
#define EGG_GFXE_STATE_GX_H
#include <nw4r/g3d.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>

namespace EGG {

class StateGX {
public:
    class AutoColorUpdate {
    public:
        AutoColorUpdate(bool enable) : mOldState(s_cacheGX.colorUpdate) {
            GXSetColorUpdate_(enable);
        }
        ~AutoColorUpdate() {
            GXSetColorUpdate_(mOldState);
        }

    private:
        bool mOldState; // at 0x0
    };

    class AutoAlphaUpdate {
    public:
        AutoAlphaUpdate(bool enable) : mOldState(s_cacheGX.alphaUpdate) {
            GXSetAlphaUpdate_(enable);
        }
        ~AutoAlphaUpdate() {
            GXSetAlphaUpdate_(mOldState);
        }

    private:
        bool mOldState; // at 0x0
    };

    class AutoDither {
    public:
        AutoDither(bool enable) : mOldState(s_cacheGX.dither) {
            GXSetDither_(enable);
        }
        ~AutoDither() {
            GXSetDither_(mOldState);
        }

    private:
        bool mOldState; // at 0x0
    };

public:
    static void initialize();

    static void frameInit();
    static void initGXCache();

    static void resetGX();
    static void resetVtx();
    static void resetColorChannel();
    static void resetIndirect();
    static void resetTexture();
    static void resetTexGen();
    static void resetTev();
    static void resetPE();
    static void resetGXCache();

    static void GXSetProjection_(Mtx44 mtx, GXProjectionType type);
    static void GXSetProjectionv_(const f32 pProj[GX_VIEWPORT_SZ]);

    static void GXSetViewport_(f32 left, f32 top, f32 width, f32 height,
                               f32 near, f32 far);

    static void GXSetScissor_(u32 s0, u32 s1, u32 s2, u32 s3);
    static void GXSetScissorBoxOffset_(int b0, int b1);

    static void GXSetColorUpdate_(bool enable);
    static void GXSetAlphaUpdate_(bool enable);
    static void GXSetDither_(bool enable);

    static void setPixelFormatGX(GXPixelFmt pixFormat, GXZFmt16 zFmt16);

    static GXPixelFmt getDefaultPixelFormat() {
        return s_pixFormat;
    }
    static GXZFmt16 getDefaultZFmt16() {
        return s_zFmt16;
    }

    static const GXColor& getEfbClearColor() {
        return s_clearEfb;
    }
    static void setEfbClearColor(const GXColor& rColor) {
        s_clearEfb = rColor;
    }

    static u16 getEfbWidth() {
        return s_widthFb;
    }
    static void setEfbWidth(u16 width) {
        s_widthFb = width;
    }

    static u16 getEfbHeight() {
        return s_heightEfb;
    }
    static void setEfbHeight(u16 height) {
        s_heightEfb = height;
    }

private:
    struct GXCache {
        u32 flags;        // at 0x0
        int scissorX;     // at 0x4
        int scissorY;     // at 0x8
        bool colorUpdate; // at 0xC
        bool alphaUpdate; // at 0xD
        bool dither;      // at 0xE
    };

    enum {
        cCacheFlag_ProjectionV = 1 << 0,
        cCacheFlag_Viewport = 1 << 1,
        cCacheFlag_Scissor = 1 << 2,
        cCacheFlag_ScissorBox = 1 << 3,
        cCacheFlag_Dither = 1 << 4,
        cCacheFlag_ColorUpdate = 1 << 5,
        cCacheFlag_AlphaUpdate = 1 << 6,
    };

    enum {
        cFlag_EnableTMem = 1 << 4,
        cFlag_EnableCache = 1 << 5,
    };

private:
    static GXCache s_cacheGX;

    static u16 s_widthFb;
    static u16 s_heightEfb;

    static GXPixelFmt s_pixFormat;
    static GXZFmt16 s_zFmt16;

    static GXPixelFmt s_pixFormatCurrent;
    static GXZFmt16 s_zFmt16Current;

    static GXColor s_clearEfb;

    static u16 s_flag;

    static f32 s_modifyRatio;

    static nw4r::g3d::tmem::TMemLayout s_tmem_layout;
};

} // namespace EGG

#endif
