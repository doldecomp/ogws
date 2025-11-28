#ifndef RP_KERNEL_MIDDLE_DB_H
#define RP_KERNEL_MIDDLE_DB_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysMiddleDBGenInfo;

/**
 * @brief In-memory Mii database
 */
class RPSysMiddleDB {
private:
    //! Middle/hidden database
    RFLMiddleDB* mpMiddleDB; // at 0x0
    //! Random database for bad queries
    RFLMiddleDB* mpRandomDB; // at 0x4

    //! Database capacity
    u16 mSize; // at 0x8
    //! Number of Miis stored in the middle database
    u16 mStoredNum; // at 0xA
    //! Current database index (only for RFLMiddleDBType_UserSet)
    u16 mCurrentIndex; // at 0xC

public:
    /**
     * @brief Constructor
     *
     * @param pGenInfo Middle DB generation parameters
     */
    RPSysMiddleDB(const RPSysMiddleDBGenInfo* pGenInfo);

    /**
     * @brief Destructor
     */
    virtual ~RPSysMiddleDB(); // at 0x8

    /**
     * @brief Increments the current database index
     * @details The current index wraps around when it becomes invalid
     */
    void IncrementCurrentIndex();

    /**
     * @brief Gets the RFL parameters necessary to access the specified Mii
     * @details If the index is invalid for the middle database, the parameters
     * returned will instead fetch a Mii from the random database.
     *
     * @param index Database index
     * @param ppMiddleDB Middle DB to use with RFL
     * @param pIndex Database index to use with RFL
     */
    void GetRFLMiddleDB(u16 index, RFLMiddleDB** ppMiddleDB, u16* pIndex);

    /**
     * @brief Gets the number of Miis stored in the middle database
     */
    u16 GetStoredNum() const {
        return mStoredNum;
    }

    /**
     * @brief Gets the current database index
     */
    u16 GetCurrentIndex() const {
        return mCurrentIndex;
    }
};

//! @}

#endif
