#include <Pack/RPSystem.h>

#include <revolution/GX.h>
#include <revolution/VI.h>

namespace {

/**
 * @brief Render mode configuration for NTSC (interlaced)
 */
GXRenderModeObj localNtsc640x456IntDf = {
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

/**
 * @brief Render mode configuration for NTSC (progressive)
 */
GXRenderModeObj localNtsc640x456Prog = {
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

/**
 * @brief Render mode configuration for PAL50 (interlaced)
 */
GXRenderModeObj localPal50_640x456IntDf = {
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

/**
 * @brief Render mode configuration for NTSC video
 */
GXRenderModeObj localPal60_640x456IntDf = {
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

/**
 * @brief Render mode configuration for PAL (progressive)
 */
GXRenderModeObj localPal60_640x456Prog = {
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

} // namespace

/**
 * @brief Render mode configurations
 */
GXRenderModeObj* const RPSysRenderMode::spRenderModeTable[EFormat_Max] = {
    &localNtsc640x456IntDf,   // EFormat_Ntsc
    &localNtsc640x456Prog,    // EFormat_NtscProg
    &localPal50_640x456IntDf, // EFormat_Pal50
    &localPal60_640x456IntDf, // EFormat_Pal60
    &localPal60_640x456Prog,  // EFormat_PalProg
};

/**
 * @brief Adjusts a render mode to account for widescreen/50Hz formats
 *
 * @param pOriginX Pointer to render mode viXOrigin
 * @param pWidth Pointer to render mode viWidth
 * @param format Render mode format
 * @param wide Whether the display is widescreen
 */
void RPSysRenderMode::adjust(u16* pOriginX, u16* pWidth, EFormat format,
                             bool wide) {
    if (wide) {
        if (format == EFormat_Pal50) {
            *pWidth = 682;
        } else {
            *pWidth = 686;
        }
    } else if (format == EFormat_Pal50) {
        *pWidth = 666;
    } else {
        *pWidth = 670;
    }

    switch (format) {
    case EFormat_Ntsc:
    case EFormat_NtscProg: {
        *pOriginX = (720 - *pWidth) / 2;
        break;
    }

    case EFormat_Pal50: {
        *pOriginX = (720 - *pWidth) / 2;
        break;
    }

    case EFormat_Pal60:
    case EFormat_PalProg: {
        *pOriginX = (720 - *pWidth) / 2;
        break;
    }

    default: {
        break;
    }
    }
}
