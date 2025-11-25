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
RPSysAppMiiManager::RPSysAppMiiManager(u16 num, EGG::Heap* pHeap)
    : mNumMii(num), mppStoreData(NULL), mppCharData(NULL) {

    // Only Wii Sports uses character data (no checksum)
    if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
        RPSysSceneCreator::EPackID_SportsPack) {

        mppCharData = new (pHeap) RFLCharData*[num];
    } else {
        mppStoreData = new (pHeap) RFLStoreData*[num];
    }
}
