#include "eggCapTexture.h"
#include "eggStateGX.h"

#include <revolution/GX.h>

namespace EGG
{
    // https://decomp.me/scratch/SrABn
    // - Copy filter argument copies incorrectly
    void CapTexture::configure()
    {
        static const GXColor scDefaultClearColor = {0, 0, 0, 0};

        CpuTexture::configure();

        mLoadMap = GX_TEXMAP0;
        mClearZ = 0x00FFFFFF;
        setClearColor(scDefaultClearColor);
        // setCopyFilterArg1(sCopyFilterArg1_1);
        setFlag(0x80);
    }

    void CapTexture::load(GXTexMapID map) const
    {
        #line 45
        EGG_ASSERT(getBuffer());

        mLoadMap = map;
        CpuTexture::load(map);
    }

    // https://decomp.me/scratch/awE6M
    // - Issue with ternary for GXSetCopyFilter
    void CapTexture::capture(u16 x, u16 y, bool upscale, int format)
    {
        u16 w, h;

        #line 60
        EGG_ASSERT(getBuffer());
        EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");

        if (format == -1)
            format = static_cast<int>(getFormat());

        u32 lw;
        if (upscale)
            lw = getWidth() * 2;
        else
            lw = getWidth();
        w = static_cast<u16>(lw);

        u32 lh;
        if (upscale)
            lh = getHeight() * 2;
        else
            lh = getHeight();
        h = static_cast<u16>(lh);

        #line 68
        EGG_ASSERT(w > 0 && h > 0);

        GXSetTexCopySrc(x, y, w + (w & 1), h + (h & 1));
        GXSetTexCopyDst(getWidth(), getHeight(), static_cast<GXTexFmt>(format), upscale);

        GXSetCopyFilter(0, const_cast<u8(*)[2]>(scCopyFilterArg0), mFlags & 0x40,
            mFlags & 0x40 ? mCopyFilterArg1 : sCopyFilterArg1_1);

        if ((mFlags & 0x8) || (mFlags & 0x10) || (mFlags & 0x20))
        {
            StateGX::ScopedColor color(mFlags & 0x8);
            StateGX::ScopedAlpha alpha(mFlags & 0x10);

            GXSetZMode(1, GX_ALWAYS, (mFlags & 0x20) != 0);
            GXSetCopyClear(mClearColor, mClearZ);
            GXCopyTex(getBuffer(), 1);
        }
        else
        {
            GXCopyTex(getBuffer(), 0);
        }

        GXSetCopyFilter(0, const_cast<u8(*)[2]>(scCopyFilterArg0),
            0, sCopyFilterArg1_1);

        if (mFlags & 0x80)
            GXPixModeSync();
    }
}
