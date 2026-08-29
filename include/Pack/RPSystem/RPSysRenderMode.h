#ifndef RP_SYSTEM_RENDER_MODE_H
#define RP_SYSTEM_RENDER_MODE_H
#include <Pack/types_pack.h>

#include <revolution/GX.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Render mode utilities
 */
class RPSysRenderMode {
public:
    /**
     * @brief Render mode formats
     */
    enum EFormat {
        EFormat_Ntsc,     //!< NTSC
        EFormat_NtscProg, //!< NTSC, Progressive Mode

        EFormat_Pal50,   //!< PAL, 50Hz ("EuRgb50")
        EFormat_Pal60,   //!< PAL, 60Hz ("EuRgb60")
        EFormat_PalProg, //!< PAL, Progressive Mode

        EFormat_Max
    };

public:
    /**
     * @brief Gets the render mode for the specified format
     *
     * @param format Render mode format
     */
    static GXRenderModeObj* getRenderMode(EFormat format) {
        return spRenderModeTable[format];
    }

    /**
     * @brief Adjusts a render mode to account for widescreen/50Hz formats
     *
     * @param pOriginX Pointer to render mode viXOrigin
     * @param pWidth Pointer to render mode viWidth
     * @param format Render mode format
     * @param wide Whether the display is widescreen
     */
    static void adjust(u16* pOriginX, u16* pWidth, EFormat format, bool wide);

private:
    //! Render mode configurations
    static GXRenderModeObj* const spRenderModeTable[EFormat_Max];
};

//! @}

#endif
