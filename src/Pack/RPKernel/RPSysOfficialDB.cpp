#include <Pack/RPKernel.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 */
RPSysOfficialDB::RPSysOfficialDB() {
    for (u16 i = 0; i < ARRAY_SIZE(mStates); i++) {
        mStates[i] = RPSysKokeshiManager::OfficialDBState_Unused;
    }
}

/**
 * @brief Destructor
 */
RPSysOfficialDB::~RPSysOfficialDB() {}

/**
 * @brief Finds the index holding the Mii with the specified create ID
 *
 * @param pCreateID Mii create ID
 * @return Database index, or -1 if not found
 */
s16 RPSysOfficialDB::GetIndexFromCreateID(const RFLCreateID* pCreateID) {
    u16 index = 0;
    if (RFLSearchOfficialData(pCreateID, &index)) {
        return index;
    }

    return -1;
}

/**
 * @brief Resets the database to the latest states
 */
void RPSysOfficialDB::Reset() {
    for (u16 i = 0; i < ARRAY_SIZE(mStates); i++) {
        if (RFLIsAvailableOfficialData(i)) {
            mStates[i] = RPSysKokeshiManager::OfficialDBState_Valid;
        } else {
            mStates[i] = RPSysKokeshiManager::OfficialDBState_Unused;
        }
    }
}

/**
 * @brief Gets the number of valid Miis in the database
 */
u16 RPSysOfficialDB::GetValidNum() {
    u16 num = 0;

    for (u16 i = 0; i < ARRAY_SIZE(mStates); i++) {
        if (mStates[i] == RPSysKokeshiManager::OfficialDBState_Valid) {
            num++;
        }
    }

    return num;
}
