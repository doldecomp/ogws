#include <nw4r/g3d.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace {

NW4R_LIB_VERSION(G3D, "Jun  8 2007", "11:16:25", "0x4199_60831");

} // namespace

namespace nw4r {
namespace g3d {

void G3dInit(bool enableLockedCache) {
    OSRegisterVersion(NW4R_G3D_Version_);

    if (enableLockedCache) {
        ut::LC::Enable();
    } else {
        ut::LC::Disable();
    }

    InitFastCast();

    GXRenderModeObj* pMode;
    switch (VIGetTvFormat()) {
    case VI_TVFORMAT_NTSC: {
        pMode = &GXNtsc480IntDf;
        break;
    }

    case VI_TVFORMAT_PAL: {
        pMode = &GXPal528IntDf;
        break;
    }

    case VI_TVFORMAT_EURGB60: {
        pMode = &GXEurgb60Hz480IntDf;
        break;
    }

    case VI_TVFORMAT_MPAL: {
        pMode = &GXMpal480IntDf;
        break;
    }

    default: {
        pMode = &GXNtsc480IntDf;
        break;
    }
    }

    G3DState::SetRenderModeObj(*pMode);
}

void G3dReset() {
    G3DState::Invalidate();
}

} // namespace g3d
} // namespace nw4r
