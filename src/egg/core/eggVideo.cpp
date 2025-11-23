// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>

#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/SC.h>
#include <revolution/VI.h>

namespace EGG {
namespace {

const GXRenderModeObj gRMO_Ntsc_640x456IntDf_4x3 = {
    VI_TVMODE_NTSC_INT, // tvInfo
    640,                // fbWidth
    456,                // efbHeight
    456,                // xfbHeight
    25,                 // viXOrigin
    12,                 // viYOrigin
    670,                // viWidth
    456,                // viHeight
    VI_XFBMODE_DF,      // xfbMode
    GX_FALSE,           // field_rendering
    GX_FALSE,           // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Ntsc_640x456Prog_4x3 = {
    VI_TVMODE_NTSC_PROG, // tvInfo
    640,                 // fbWidth
    456,                 // efbHeight
    456,                 // xfbHeight
    25,                  // viXOrigin
    12,                  // viYOrigin
    670,                 // viWidth
    456,                 // viHeight
    VI_XFBMODE_SF,       // xfbMode
    GX_FALSE,            // field_rendering
    GX_FALSE,            // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {0, 0, 21, 22, 21, 0, 0} // vfilter
};

const GXRenderModeObj gRMO_Pal50_640x456IntDf_4x3 = {
    VI_TVMODE_PAL_INT, // tvInfo
    640,               // fbWidth
    456,               // efbHeight
    542,               // xfbHeight
    27,                // viXOrigin
    16,                // viYOrigin
    666,               // viWidth
    542,               // viHeight
    VI_XFBMODE_DF,     // xfbMode
    GX_FALSE,          // field_rendering
    GX_FALSE,          // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Pal60_640x456IntDf_4x3 = {
    VI_TVMODE_EURGB60_INT, // tvInfo
    640,                   // fbWidth
    456,                   // efbHeight
    456,                   // xfbHeight
    25,                    // viXOrigin
    12,                    // viYOrigin
    670,                   // viWidth
    456,                   // viHeight
    VI_XFBMODE_DF,         // xfbMode
    GX_FALSE,              // field_rendering
    GX_FALSE,              // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Pal60_640x456Prog_4x3 = {
    VI_TVMODE_EURGB60_PROG, // tvInfo
    640,                    // fbWidth
    456,                    // efbHeight
    456,                    // xfbHeight
    25,                     // viXOrigin
    12,                     // viYOrigin
    670,                    // viWidth
    456,                    // viHeight
    VI_XFBMODE_SF,          // xfbMode
    GX_FALSE,               // field_rendering
    GX_FALSE,               // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {0, 0, 21, 22, 21, 0, 0} // vfilter
};

const GXRenderModeObj gRMO_Ntsc_640x456IntDf_16x9 = {
    VI_TVMODE_NTSC_INT, // tvInfo
    640,                // fbWidth
    456,                // efbHeight
    456,                // xfbHeight
    17,                 // viXOrigin
    12,                 // viYOrigin
    686,                // viWidth
    456,                // viHeight
    VI_XFBMODE_DF,      // xfbMode
    GX_FALSE,           // field_rendering
    GX_FALSE,           // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Ntsc_640x456Prog_16x9 = {
    VI_TVMODE_NTSC_PROG, // tvInfo
    640,                 // fbWidth
    456,                 // efbHeight
    456,                 // xfbHeight
    17,                  // viXOrigin
    12,                  // viYOrigin
    686,                 // viWidth
    456,                 // viHeight
    VI_XFBMODE_SF,       // xfbMode
    GX_FALSE,            // field_rendering
    GX_FALSE,            // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {0, 0, 21, 22, 21, 0, 0} // vfilter
};

const GXRenderModeObj gRMO_Pal50_640x456IntDf_16x9 = {
    VI_TVMODE_PAL_INT, // tvInfo
    640,               // fbWidth
    456,               // efbHeight
    542,               // xfbHeight
    19,                // viXOrigin
    16,                // viYOrigin
    682,               // viWidth
    542,               // viHeight
    VI_XFBMODE_DF,     // xfbMode
    GX_FALSE,          // field_rendering
    GX_FALSE,          // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Pal60_640x456IntDf_16x9 = {
    VI_TVMODE_EURGB60_INT, // tvInfo
    640,                   // fbWidth
    456,                   // efbHeight
    456,                   // xfbHeight
    17,                    // viXOrigin
    12,                    // viYOrigin
    686,                   // viWidth
    456,                   // viHeight
    VI_XFBMODE_DF,         // xfbMode
    GX_FALSE,              // field_rendering
    GX_FALSE,              // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {7, 7, 12, 12, 12, 7, 7} // vfilter
};

const GXRenderModeObj gRMO_Pal60_640x456Prog_16x9 = {
    VI_TVMODE_EURGB60_PROG, // tvInfo
    640,                    // fbWidth
    456,                    // efbHeight
    456,                    // xfbHeight
    17,                     // viXOrigin
    12,                     // viYOrigin
    686,                    // viWidth
    456,                    // viHeight
    VI_XFBMODE_SF,          // xfbMode
    GX_FALSE,               // field_rendering
    GX_FALSE,               // aa
    {
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
        {6, 6},
    },                       // sample_pattern
    {0, 0, 21, 22, 21, 0, 0} // vfilter
};

} // namespace

void Video::initialize(GXRenderModeObj* pRenderMode) {
    VIInit();
    configure(pRenderMode);
}

GXRenderModeObj* Video::configure(GXRenderModeObj* pRenderMode) {
    GXRenderModeObj* pOldRenderMode = mRenderMode;

    if (pRenderMode == NULL) {
        pRenderMode = const_cast<GXRenderModeObj*>(getStandardRenderModeObj());
    }

    if (mRenderMode != pRenderMode) {
        mRenderMode = pRenderMode;

        VISetBlack(TRUE);
        VIConfigure(pRenderMode);
        VIFlush();

        mConfiguredTime = OSGetTick();
        mFlags.setBit(BIT_VIDEO_SHOW);

        u16 fbWidth = pRenderMode->fbWidth;
        u16 efbHeight = pRenderMode->efbHeight;

        f32 scaleY = GXGetYScaleFactor(efbHeight, pRenderMode->xfbHeight);
        u32 numXfbLines = GXGetNumXfbLines(efbHeight, scaleY);

        GXSetDispCopySrc(0, 0, fbWidth, efbHeight);
        GXSetDispCopyDst(fbWidth, numXfbLines);
        GXSetDispCopyYScale(scaleY);

        VIWaitForRetrace();
        VIWaitForRetrace();
    }

    return pOldRenderMode;
}

DECOMP_FORCELITERAL(eggVideo_cpp,
                    4503599627370496.0);

u32 Video::getTickPerVRetrace(u32 tvFormat) {
    f32 retraceRate;

    switch (tvFormat) {
    case VI_TVFORMAT_NTSC:
    case VI_TVFORMAT_EURGB60:
    default: {
        retraceRate = 59.94f;
        break;
    }

    case VI_TVFORMAT_PAL:
    case VI_TVFORMAT_MPAL: {
        retraceRate = 50.0f;
        break;
    }
    }

    return OS_SEC_TO_TICKS(1) / retraceRate;
}

u32 Video::getTickPerVRetrace() {
    return getTickPerVRetrace(VIGetTvFormat());
}

const GXRenderModeObj* Video::getStandardRenderModeObj() {
    bool progressive = SCGetProgressiveMode() == SC_PROGRESSIVE;
    bool pal60 = SCGetEuRgb60Mode() == SC_EURGB_60_HZ;
    bool stdAspect = SCGetAspectRatio() == SC_ASPECT_STD;
    bool componentCable = VIGetDTVStatus() == VI_VISEL_COMPONENT;

    bool ntsc = false;
    switch (VIGetTvFormat()) {
    case VI_TVFORMAT_NTSC: {
        ntsc = true;
        break;
    }

    case VI_TVFORMAT_PAL:
    case VI_TVFORMAT_EURGB60: {
        ntsc = false;
        break;
    }

    default: {
        ntsc = true;
        break;
    }
    }

    if (componentCable && progressive) {
        if (ntsc) {
            if (stdAspect ? true : false) {
                return &gRMO_Ntsc_640x456Prog_4x3;
            } else {
                return &gRMO_Ntsc_640x456Prog_16x9;
            }
        } else {
            if (stdAspect ? true : false) {
                return &gRMO_Pal60_640x456Prog_4x3;
            } else {
                return &gRMO_Pal60_640x456Prog_16x9;
            }
        }
    }

    if (ntsc) {
        if (stdAspect ? true : false) {
            return &gRMO_Ntsc_640x456IntDf_4x3;
        } else {
            return &gRMO_Ntsc_640x456IntDf_16x9;
        }
    }

    if (pal60) {
        if (stdAspect ? true : false) {
            return &gRMO_Pal60_640x456IntDf_4x3;
        } else {
            return &gRMO_Pal60_640x456IntDf_16x9;
        }
    }

    return stdAspect ? &gRMO_Pal50_640x456IntDf_4x3
                     : &gRMO_Pal50_640x456IntDf_16x9;
}

DECOMP_FORCEACTIVE(eggVideo_cpp_1,
                  "eggVideo.cpp",
                  "RenderMode is null");

} // namespace EGG
