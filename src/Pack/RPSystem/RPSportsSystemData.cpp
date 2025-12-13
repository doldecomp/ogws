#include <Pack/RPSystem.h>

/**
 * @brief Constructor
 */
RPSportsSystemData::RPSportsSystemData() {
    reset();
}

/**
 * @brief Resets the data to a default save state
 */
void RPSportsSystemData::reset() {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        mOldIndex[i] = -1;

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            mOldAddress[i][j] = 0;
        }
    }

    mPhysicalCount = 0;
    mPhysicalEndLastDate = 0;

    unk4A = 0;
    unk4C = 0;

    mFlags.makeAllZero();
    unk54.makeAllZero();
}

/**
 * @brief Gets the old data for the specified player count and player index
 *
 * @param[out] pIndex Official database index
 * @param[out] pAddr Remote Bluetooth address
 * @param playerNum Player count
 * @param playerNo Player index
 */
void RPSportsSystemData::getOldData(s8* pIndex, u8* pAddr, s32 playerNum,
                                    s32 playerNo) const {
    u32 rel2Abs[WPAD_MAX_CONTROLLERS] = {
        0,             // 1 player
        0 + 1,         // 2 players
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
    };

    u32 absIdx = rel2Abs[--playerNum] + playerNo;

    *pIndex = mOldIndex[absIdx];

    for (int i = 0; i < WPAD_ADDR_LEN; i++) {
        pAddr[i] = mOldAddress[absIdx][i];
    }
}

/**
 * @brief Sets the old data for the specified player count and player index
 *
 * @param[out] pIndex Official database index
 * @param[out] pAddr Remote Bluetooth address
 * @param playerNum Player count
 * @param playerNo Player index
 */
void RPSportsSystemData::setOldData(s8 index, const u8* pAddr, s32 playerNum,
                                    s32 playerNo) {
    u32 rel2Abs[WPAD_MAX_CONTROLLERS] = {
        0,             // 1 player
        0 + 1,         // 2 players
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
    };

    u32 absIdx = rel2Abs[--playerNum] + playerNo;

    mOldIndex[absIdx] = index;

    for (int i = 0; i < WPAD_ADDR_LEN; i++) {
        mOldAddress[absIdx][i] = pAddr[i];
    }
}

/**
 * @brief Sets the total number of fitness tests completed
 *
 * @param count Number of fitness tests completed
 */
void RPSportsSystemData::setPhysicalEndCount(u8 count) {
    mPhysicalCount = count;
}

/**
 * @brief Gets the total number of fitness tests completed
 */
u8 RPSportsSystemData::getPhysicalEndCount() const {
    return mPhysicalCount;
}

/**
 * @brief Sets the last date on which a fitness test was completed
 *
 * @param date Last completion date
 */
void RPSportsSystemData::setPhysicalEndLastDate(RPTime16 date) {
    mPhysicalEndLastDate = date;
}

/**
 * @brief Gets the last date on which a fitness test was completed
 */
RPTime16 RPSportsSystemData::getPhysicalEndLastDate() const {
    return mPhysicalEndLastDate;
}

/**
 * @brief Sets whether the specified training game's unlock cutscene has
 * played
 *
 * @param idx Training game index
 * @param open Whether the unlock cutscene has played
 */
void RPSportsSystemData::setGameOpenDemo(u8 idx, bool open) {
    return mFlags.changeBit(idx, open);
}

/**
 * @brief Tests whether the specified training game's unlock cutscene has
 * played
 *
 * @param idx Training game index
 */
bool RPSportsSystemData::isGameOpenDemo(u8 idx) const {
    return mFlags.onBit(idx);
}

/**
 * @brief Sets whether the specified training game is available
 *
 * @param idx Training game index
 * @param open Whether the game is available
 */
void RPSportsSystemData::setGameOpen(u8 idx, bool open) {
    // First set of EGame bits is for demo
    return mFlags.changeBit(EGame_Max + idx, open);
}

/**
 * @brief Tests whether the specified training game is available
 *
 * @param idx Training game index
 */
bool RPSportsSystemData::isGameOpen(u8 idx) const {
    // First set of EGame bits is for demo
    return mFlags.onBit(EGame_Max + idx);
}

/**
 * @brief Deserializes this object from the specified stream
 *
 * @param rStrm Memory stream
 */
void RPSportsSystemData::read(EGG::RamStream& rStrm) {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        mOldIndex[i] = rStrm.read_s8();

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            mOldAddress[i][j] = rStrm.read_u8();
        }
    }

    mPhysicalCount = rStrm.read_u8();
    mPhysicalEndLastDate = rStrm.read_u16();
    unk4A = rStrm.read_u16();
    unk4C = rStrm.read_u8();
    mFlags = rStrm.read_u32();
    unk54 = rStrm.read_u32();
}

/**
 * @brief Serializes this object to the specified stream
 *
 * @param rStrm Memory stream
 */
void RPSportsSystemData::write(EGG::RamStream& rStrm) {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        rStrm.write_s8(mOldIndex[i]);

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            rStrm.write_u8(mOldAddress[i][j]);
        }
    }

    rStrm.write_u8(mPhysicalCount);
    rStrm.write_u16(mPhysicalEndLastDate);
    rStrm.write_u16(unk4A);
    rStrm.write_u8(unk4C);
    rStrm.write_u32(mFlags);
    rStrm.write_u32(unk54);
}
