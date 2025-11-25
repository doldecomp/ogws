#ifndef RP_SYSTEM_FONT_MANAGER_H
#define RP_SYSTEM_FONT_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <nw4r/ut.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Font manager
 */
class RPSysFontManager {
    RP_SINGLETON_DECL(RPSysFontManager);

public:
    /**
     * @brief Pack Project resource fonts
     */
    enum ResFontType {
        //! New Rodin (Demibold, 32pt, I4 tex format)
        ResFontType_nRodDb_32_I4,
        //! New Rodin (Demibold, 32pt, IA4 tex format)
        ResFontType_nRodDb_32_IA4,
        //! New Rodin (Demibold, 62pt, IA4 tex format)
        ResFontType_nRodDb_62_IA4,
        //! New Rodin (Demibold, 200pt, IA4 tex format)
        ResFontType_nRodDb_200_IA4,

        //! New Rodin (Extrabold, 32pt, I4 tex format)
        ResFontType_nRodEb_32_I4,
        //! New Rodin (Extrabold, 70pt, IA4 tex format)
        ResFontType_nRodEb_70_IA4,

        ResFontType_HealthTime,

        ResFontType_Max
    };

public:
    /**
     * @brief Sets up the ROM font
     */
    void LoadRomFont();
    /**
     * @brief Sets up all resource fonts required by this pack
     */
    void LoadResFonts();

    /**
     * @brief Gets resource font data by name
     */
    void* GetResFontData(const char* name) const;

    /**
     * @brief Accesses the ROM font
     */
    nw4r::ut::RomFont* GetRomFont() const {
        return mpRomFont;
    }

    /**
     * @brief Accesses the specified resource font
     *
     * @param idx Font index
     */
    nw4r::ut::ResFont* GetResFont(int idx) const {
        return mpResFonts[idx];
    }

private:
    //! Resource font filenames
    static const char* sResFontNames[ResFontType_Max];
    //! Table which marks the resource fonts needed by this pack
    static BOOL sIsNeedResFont[ResFontType_Max];

    //! ROM font provided by the system
    nw4r::ut::RomFont* mpRomFont; // at 0x4
    //! Resource fonts provided by the disc
    nw4r::ut::ResFont* mpResFonts[ResFontType_Max]; // at 0x8

    //! Serialized versions of resource fonts (for layout access)
    void* mpResFontData[ResFontType_Max]; // at 0x24
};

//! @}

#endif
