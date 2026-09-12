#ifndef RP_SPORTS_GOL_RESOURCE_MANAGER_H
#define RP_SPORTS_GOL_RESOURCE_MANAGER_H

#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_gol
//! @{

/**
 * @brief Resource manager for Golf
 */
class RPGolResourceManager {

    RP_SINGLETON_DECL(RPGolResourceManager);

public:
    enum EArchive {
        EArchive_GameCommon,
        EArchive_GameLocal,
        EArchive_GameStage,
        EArchive_StaticCommon,
        EArchive_StaticLocal,
        EArchive_Max,
    };

    static void getGameArchive(const char* pName);

    static void* hasFile(const char* pName, EArchive archive);

    static bool checkFile(const char* pName, EArchive archive);

    /**
     * @brief Creates 3D models from a provided archive.
     *
     * @param pName Name of 3D model
     * @param archive Archive type
     */

    static RPGrpHandle createModel(const char* pName, EArchive archive);

private:
    EGG::Archive** mppArchives; // at 0x4
    void* unk8;
    void* unkC;
    void* unk10;
    void* unk14;
};

//! @}

#endif
