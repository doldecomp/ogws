#include <Pack/RPSystem.h>

/**
 * @brief Constructor
 */
RPPartyPlayerData::RPPartyPlayerData() {
    reset();
}

/**
 * @brief Resets the data to a default save state
 */
void RPPartyPlayerData::reset() {
    mPlayerFlags.makeAllZero();

    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = 0;
    }

    mDebutTime = 0;

    for (int i = 0; i < EGame_Max; i++) {
        for (int j = 0; j < MY_RECORDS_LENGTH; j++) {
            mMyRecords[i][j] = 0;
        }

        mMedals[i] = EMedal_None;
    }

    mMedalDemoFlags.makeAllZero();
}

/**
 * @brief Tests whether this player has been registered with the player list
 */
bool RPPartyPlayerData::isRegistered() const {
    return mPlayerFlags.onBit(EFlag_Registered);
}

/**
 * @brief Sets whether this player has been registered with the player list
 *
 * @param registered Registration status
 */
void RPPartyPlayerData::setRegistered(bool registered) {
    mPlayerFlags.changeBit(EFlag_Registered, registered);
}

/**
 * @brief Gets this player's Mii create ID
 *
 * @param[out] pCreateID Mii create ID
 */
void RPPartyPlayerData::getCreateID(RFLCreateID* pCreateID) const {
    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        pCreateID->data[i] = mCreateID.data[i];
    }
}

/**
 * @brief Set this player's Mii create ID
 *
 * @param pCreateID Mii create ID
 */
void RPPartyPlayerData::setCreateID(const RFLCreateID* pCreateID) {
    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = pCreateID->data[i];
    }
}

/**
 * @brief Gets the time this player was registered with the player list
 */
RPTime32 RPPartyPlayerData::getDebutTime() const {
    return mDebutTime;
}

/**
 * @brief Sets the time this player was registered with the player list
 *
 * @param time Debut time
 */
void RPPartyPlayerData::setDebutTime(RPTime32 time) {
    mDebutTime = time;
}
