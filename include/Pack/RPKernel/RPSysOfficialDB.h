#ifndef RP_KERNEL_OFFICIAL_DB_H
#define RP_KERNEL_OFFICIAL_DB_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysKokeshiManager.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief NAND Mii database accessor
 */
class RPSysOfficialDB {
private:
    //! Mii states by database index
    RPSysKokeshiManager::OfficialDBState mStates[RFL_DB_CHAR_MAX]; // at 0x0

public:
    /**
     * @brief Constructor
     */
    RPSysOfficialDB();

    /**
     * @brief Destructor
     */
    virtual ~RPSysOfficialDB(); // at 0x8

    /**
     * @brief Finds the index holding the Mii with the specified create ID
     *
     * @param pCreateID Mii create ID
     * @return Database index, or -1 if not found
     */
    s16 GetIndexFromCreateID(const RFLCreateID* pCreateID);

    /**
     * @brief Resets the database to the latest states
     */
    void Reset();

    /**
     * @brief Gets the number of valid Miis in the database
     */
    u16 GetValidNum();

    /**
     * @brief Gets the state of the specified database index
     *
     * @param index Database index
     */
    RPSysKokeshiManager::OfficialDBState GetState(u16 index) {
        return mStates[index];
    }

    /**
     * @brief Sets the state of the specified database index
     *
     * @param index Database index
     * @param state New state
     */
    void SetState(u16 index, RPSysKokeshiManager::OfficialDBState state) {
        mStates[index] = state;
    }
};

//! @}

#endif
