#ifndef RP_SPORTS_GOL_RESOURCE_MANAGER_H
#define RP_SPORTS_GOL_RESOURCE_MANAGER_H

#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_gol
//! @{

/**
 * @brief Resource manager for Golf
 */
class RPGolResourceManager {
public:
    RP_SINGLETON_DECL(RPGolResourceManager);

    static void getGameArchive(const char* pName);

    static void* getFile(const char* pName, int offset);

    static bool checkFile(const char* pName, int offset);

    /**
     * @brief Creates 3D models from a provided archive.
     *
     * @param pName Archive file name
     * @param offset Offset of model within archive
     */

    static void createModel(const char* pName, int offset);

private:
    EGG::Archive** mppArchives; // at 0x4
    void* unk8;
    void* unkC;
    void* unk10;
    void* unk14;
};

//! @}

#endif
