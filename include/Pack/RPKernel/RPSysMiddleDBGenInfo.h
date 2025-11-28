#ifndef RP_KERNEL_MIDDLE_DB_GEN_INFO_H
#define RP_KERNEL_MIDDLE_DB_GEN_INFO_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysAppMiiManager;

/**
 * @brief Middle database generation parameters
 */
class RPSysMiddleDBGenInfo {
private:
    //! Middle database type
    RFLMiddleDBType mType; // at 0x0
    //! Database capacity
    u16 mSize; // at 0x4

    //! Random database gender mask
    RFLSex mGenderMask; // at 0x8
    //! Random database age mask
    RFLAge mAgeMask; // at 0xC
    //! Random database race mask
    RFLRace mRaceMask; // at 0x10

    //! Application Mii manager (only for RFLMiddleDBType_UserSet)
    RPSysAppMiiManager* mpMiiManager; // at 0x14

public:
    /**
     * @brief Constructor
     */
    RPSysMiddleDBGenInfo();

    /**
     * @brief Destructor
     */
    virtual ~RPSysMiddleDBGenInfo(); // at 0x8

    /**
     * @brief Gets the type of the middle database
     */
    RFLMiddleDBType GetType() const {
        return mType;
    }

    /**
     * @brief Sets the type of the middle database
     *
     * @param type Middle database type
     */
    void SetType(RFLMiddleDBType type) {
        mType = type;
    }

    /**
     * @brief Gets the size of the middle database
     */
    u16 GetSize() const {
        return mSize;
    }

    /**
     * @brief Sets the size of the middle database
     *
     * @param size New size
     */
    void SetSize(u16 size) {
        mSize = size;
    }

    /**
     * @brief Gets the gender mask for random/hidden generation
     */
    RFLSex GetGenderMask() const {
        return mGenderMask;
    }

    /**
     * @brief Sets the gender mask for random/hidden generation
     *
     * @param sex New gender mask
     */
    void SetGenderMask(RFLSex sex) {
        mGenderMask = sex;
    }

    /**
     * @brief Gets the age mask for random/hidden generation
     */
    RFLAge GetAgeMask() const {
        return mAgeMask;
    }

    /**
     * @brief Sets the age mask for random/hidden generation
     *
     * @param age New age mask
     */
    void SetAgeMask(RFLAge age) {
        mAgeMask = age;
    }

    /**
     * @brief Gets the race mask for random/hidden generation
     */
    RFLRace GetRaceMask() const {
        return mRaceMask;
    }

    /**
     * @brief Sets the race mask for random/hidden generation
     *
     * @param race New race mask
     */
    void SetRaceMask(RFLRace race) {
        mRaceMask = race;
    }

    /**
     * @brief Gets the application Mii manager
     * @details The Mii manager is the data source for RFLMiddleDBType_UserSet.
     */
    RPSysAppMiiManager* GetMiiManager() const {
        return mpMiiManager;
    }

    /**
     * @brief Sets the application Mii manager
     * @details The Mii manager is the data source for RFLMiddleDBType_UserSet.
     */
    void SetMiiManager(RPSysAppMiiManager* pMiiManager) {
        mpMiiManager = pMiiManager;
    }
};

//! @}

#endif
