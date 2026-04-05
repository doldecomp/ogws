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
     * @brief Loads the ROM font provided by the system
     */
    void LoadRomFont();

    /**
     * @brief Loads all resource fonts required by this pack
     */
    void LoadResFonts();

    /**
     * @brief Gets the index of the specified resource font
     *
     * @param pName Font name
     */
    u8 GetResFontIndex(const char* pName) const;

    /**
     * @brief Gets the data of the specified resource font
     *
     * @param pName Font name
     */
    void* GetResFontData(const char* pName) const;

    /**
     * @brief Accesses the ROM font provided by the system
     */
    nw4r::ut::RomFont* GetRomFont() const {
        return mpRomFont;
    }

    /**
     * @brief Accesses the specified resource font
     *
     * @param idx Font index
     */
    nw4r::ut::ResFont* GetResFont(u8 idx) const {
        return mpResFonts[idx];
    }

private:
    /**
     * @brief Loads the specified resource font from the provided archive
     *
     * @param idx Font index
     * @param pArchive Font archive
     */
    void LoadResFont(u8 idx, EGG::Archive* pArchive);

private:
    //! Font resource filenames
    static const char* RES_FONT_NAMES[ResFontType_Max];
    //! Whether each font resource is required by this pack
    static const BOOL sIsNeedResFont[ResFontType_Max];

    //! ROM font provided by the system
    nw4r::ut::RomFont* mpRomFont; // at 0x4
    //! Resource fonts
    nw4r::ut::ResFont* mpResFonts[ResFontType_Max]; // at 0x8

    //! Serialized versions of resource fonts
    void* mpResFontData[ResFontType_Max]; // at 0x24
};

//! @}

#endif
