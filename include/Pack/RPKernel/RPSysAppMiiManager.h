#ifndef RP_KERNEL_APP_MII_MANAGER_H
#define RP_KERNEL_APP_MII_MANAGER_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Application Mii data manager
 */
class RPSysAppMiiManager {
protected:
    //! Mii buffer capacity
    u16 mNumData; // at 0x0
    //! Store data (.RSD) buffer
    RFLStoreData** mppStoreData; // at 0x4

public:
    /**
     * @brief Constructor
     *
     * @param num Mii buffer capacity
     * @param pHeap Heap to use for allocations
     */
    RPSysAppMiiManager(u16 num, EGG::Heap* pHeap);

    /**
     * @brief Destructor
     */
    virtual ~RPSysAppMiiManager() {} // at 0x8

    /**
     * @brief Gets the capacity of the Mii buffer
     */
    u16 GetNumData() const {
        return mNumData;
    }

    /**
     * @brief Accesses the specified Mii character data (.RCD)
     *
     * @param index Database index
     */
    const RFLCharData* GetCharData(u16 index) const {
        return mppCharData[index];
    }

    /**
     * @brief Accesses the specified Mii store data (.RSD)
     *
     * @param index Database index
     */
    const RFLStoreData* GetStoreData(u16 index) const {
        return mppStoreData[index];
    }

protected:
    //! Character data (.RCD) buffer
    RFLCharData** mppCharData; // at 0xC
};

//! @}

#endif
