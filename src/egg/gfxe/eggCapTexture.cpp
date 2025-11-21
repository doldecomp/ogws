#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

const u8 CapTexture::SAMPLE_PATTERN_OFF[12][2] = {
    // Raw copy
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
};

const u8 CapTexture::VFILTER_BLUR[GX_VFILTER_SZ] = {
    // Blends color with neighboring pixels
    21, 0, 0, 22, 0, 21, 0,
};

const u8 CapTexture::VFILTER_OFF[GX_VFILTER_SZ] = {
    // Only use the current pixel's color
    0, 0, 1, 63, 0, 0, 0,
};

void CapTexture::configure() {
    CpuTexture::configure();
    mLoadMap = GX_TEXMAP0;

    // @typo
    static const GXColor DEFUALT_CLEAR_COLOR = {0, 0, 0, 0};
    setClearColor(DEFUALT_CLEAR_COLOR);
    setClearZ(GX_CLEAR_Z_MAX);

    setVFilterOff();
    enablePixModeSync();
}

void CapTexture::load(GXTexMapID map) {
#line 45
    EGG_ASSERT(getBuffer());

    mLoadMap = map;
    CpuTexture::load(map);
}

void CapTexture::capture(u16 x, u16 y, bool mipmap, int format) {
#line 60
    EGG_ASSERT(getBuffer());
    EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");

    if (format == -1) {
        format = static_cast<int>(getFormat());
    }

    u16 w = mipmap ? getWidth() * 2 : getWidth();
    u16 h = mipmap ? getHeight() * 2 : getHeight();

#line 68
    EGG_ASSERT(w > 0 && h > 0);

    GXSetTexCopySrc(x, y, w + (w & 1), h + (h & 1));

    GXSetTexCopyDst(getWidth(), getHeight(), static_cast<GXTexFmt>(format),
                    mipmap);

    GXSetCopyFilter(GX_FALSE, SAMPLE_PATTERN_OFF, checkVFilterEnable(),
                    checkVFilterEnable() ? mVerticalFilter : VFILTER_OFF);

    if (checkColorUpdate() || checkAlphaUpdate() || checkZBufferUpdate()) {
        StateGX::ScopedColorUpdate color(checkColorUpdate());
        StateGX::ScopedAlphaUpdate alpha(checkAlphaUpdate());

        GXSetZMode(GX_TRUE, GX_ALWAYS, checkZBufferUpdate());
        GXSetCopyClear(mClearColor, mClearZ);

        GXCopyTex(getBuffer(), GX_TRUE);
    } else {
        GXCopyTex(getBuffer(), GX_FALSE);
    }

    GXSetCopyFilter(GX_FALSE, SAMPLE_PATTERN_OFF, GX_FALSE, VFILTER_OFF);

    if (checkPixModeSync()) {
        GXPixModeSync();
    }
}

} // namespace EGG
