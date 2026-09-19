#include <Pack/RPSystem.h>

#if defined(VERSION_RSPE01_00)
/**
 * @brief Resets the data to a default save state
 */
void RPPartySystemData::reset() {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        mOldIndex[i] = -1;

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            mOldAddress[i][j] = 0;
        }
    }

    mRegistTodayCount = 0;
    mRegistLastDate = 0;
    mGameFlags.makeAllZero();
    mMsgFlags.makeAllZero();
}
#endif

/**
 * @brief Tests whether the specified minigame is available
 *
 * @param idx Minigame index
 */
bool RPPartySystemData::isGameOpen(s32 idx) const {
    return mGameFlags.onBit(idx);
}

/**
 * @brief Deserializes this object from the specified stream
 *
 * @param rStrm Memory stream
 */
void RPPartySystemData::read(EGG::RamStream& rStrm) {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        mOldIndex[i] = rStrm.read_s8();

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            mOldAddress[i][j] = rStrm.read_u8();
        }
    }

    mRegistTodayCount = rStrm.read_u8();
    mRegistLastDate = rStrm.read_u16();
    mGameFlags = rStrm.read_u32();
    mMsgFlags = rStrm.read_u32();
}

/**
 * @brief Serializes this object to the specified stream
 *
 * @param rStrm Memory stream
 */
void RPPartySystemData::write(EGG::RamStream& rStrm) {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        rStrm.write_s8(mOldIndex[i]);

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            rStrm.write_u8(mOldAddress[i][j]);
        }
    }

    rStrm.write_u8(mRegistTodayCount);
    rStrm.write_u16(mRegistLastDate);
    rStrm.write_u32(mGameFlags);
    rStrm.write_u32(mMsgFlags);
}
