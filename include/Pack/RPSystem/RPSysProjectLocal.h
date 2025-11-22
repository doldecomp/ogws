#ifndef RP_SYSTEM_PROJECT_LOCAL_H
#define RP_SYSTEM_PROJECT_LOCAL_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysSceneCreator.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Runtime project localization
 */
class RPSysProjectLocal {
    RP_SINGLETON_DECL_EX(RPSysProjectLocal);

public:
    /**
     * @brief Game region
     */
    enum ERegion {
        ERegion_NTSC_J, //!< Japan
        ERegion_NTSC_U, //!< Americas/Asia
        ERegion_PAL,    //!< Europe/Oceania
        ERegion_KOR     //!< Korea
    };

    /**
     * @brief World area
     */
    enum EArea {
        EArea_England,
        EArea_France,
        EArea_Germany,
        EArea_Italy,
        EArea_Spain,
        EArea_Netherlands,
        EArea_Japan,
        EArea_USA
    };

    /**
     * @brief Storage device
     */
    enum EStorage {
        EStorage_Memory, //!< Sound archives are loaded from RAM
        EStorage_NAND,   //!< Sound archives are loaded from the NAND (WiiWare)
        EStorage_DVD     //!< Sound archives are loaded from the DVD
    };

public:
    /**
     * @brief Appends locale directory to the given path
     *
     * @param pPath Path to append to
     * @param pSuffix Optional suffix to append after the locale
     */
    void appendLocalDirectory(char* pPath, const char* pSuffix = "");

    /**
     * @brief Sets the current dialect
     *
     * @param dialect Dialect area
     */
    void setDialect(EArea dialect);

    /**
     * @brief Sets the current language
     *
     * @param lang Language area
     */
    void setLanguage(EArea lang);

    /**
     * @brief Gets the current game region
     */
    ERegion getRegion() const {
        return mRegion;
    }

    /**
     * @brief Gets the current Pack Project game ID
     */
    RPSysSceneCreator::EPackID getPack() const {
        return mPack;
    }

    /**
     * @brief Gets the current language dialect
     */
    EArea getDialect() const {
        return mDialect;
    }

    /**
     * @brief Gets the current game language
     */
    EArea getLanguage() const {
        return mLanguage;
    }

    /**
     * @brief Tests whether the game is expected to run at 50Hz
     */
    bool isPal50() const {
        return mIsPal50;
    }

    /**
     * @brief Gets the storage device where sound data is located
     */
    EStorage getSoundStorage() const {
        return mSoundStorage;
    }

private:
    //! Game region
    ERegion mRegion; // at 0x8
    //! Pack Project title
    RPSysSceneCreator::EPackID mPack; // at 0xC
    //! Language dialect
    EArea mDialect; // at 0x10
    //! Game language
    EArea mLanguage; // at 0x14
    //! Whether the display is 50Hz
    BOOL mIsPal50; // at 0x18
    //! Sound archive storage device
    EStorage mSoundStorage; // at 0x1C
};

//! @}

#endif
