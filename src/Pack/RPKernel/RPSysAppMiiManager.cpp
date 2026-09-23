#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 *
 * @param num Mii buffer capacity
 * @param pHeap Heap to use for allocations
 */
RPSysAppMiiManager::RPSysAppMiiManager(u16 num, EGG::Heap* pHeap) : mNumData(num) {
    //! Private variables require out-of-declaration setting
    //! because ProjectLocal is accessed here as well.
    RPSysProjectLocal *local = RP_GET_INSTANCE(RPSysProjectLocal);
    mppStoreData = NULL;
    mppCharData = NULL;

    // Only Wii Sports uses character data (no checksum)
    if (local->getPack() ==
        RPSysSceneCreator::EPackID_SportsPack) {

        mppCharData = new (pHeap) RFLCharData*[num];
    } else {
        mppStoreData = new (pHeap) RFLStoreData*[num];
    }
}

/**
 * @brief Destructor
 */
 //! Should be defined here: wrong order otherwise
RPSysAppMiiManager::~RPSysAppMiiManager() {}
