#ifndef RP_SPORTS_APP_MII_MANAGER_H
#define RP_SPORTS_APP_MII_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>

#include <egg/core.h>

//! @addtogroup rp_sports
//! @{

/**
 * @brief Sports Pack Mii data manager
 */
class RPSportsAppMiiManager : public RPSysAppMiiManager {
public:
    /**
     * @brief Constructor
     *
     * @param pHeap Heap to use for allocations
     */
    RPSportsAppMiiManager(EGG::Heap* pHeap);

    /**
     * @brief Loads the Mii data resources
     */
    virtual void LoadResource(); // at 0xC

private:
    // . . .
};

//! @}

#endif
