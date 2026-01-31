#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

namespace {

/**
 * @brief Tests whether two given RFL create IDs are equivalent
 *
 * @param rLhs Left-hand side ID
 * @param rRhs Right-hand side ID
 */
bool IsSameCreateID(const RFLCreateID& rLhs, const RFLCreateID& rRhs) {
    for (u32 i = 0; i < RFL_CREATEID_LEN; i++) {
        if (rLhs.data[i] != rRhs.data[i]) {
            return false;
        }
    }

    return true;
}

} // namespace

/**
 * @brief Constructor
 */
RPSysPlayer::RPSysPlayer() : mpSportsPlayerData(NULL), mpPartyPlayerData(NULL) {
#if defined(PACK_SPORTS)
    mpSportsPlayerData = new RPSportsPlayerData();
#elif defined(PACK_PARTY)
    mpPartyPlayerData = new RPPartyPlayerData();
#endif
}

/**
 * @brief Resets the data to a default state
 */
void RPSysPlayer::reset() {
    mChannel = WPAD_CHAN0;
    mDataSource = -1;
    mIndex = -1;
    mPlayerDataIndex = -1;

    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = 0;
    }

#if defined(PACK_SPORTS)
    mpSportsPlayerData->reset();
#elif defined(PACK_PARTY)
    mpPartyPlayerData->reset();
#endif
}

/**
 * @brief Sets the Mii avatar associated with this player
 *
 * @param dataSrc Mii data source
 * @param index Mii database index
 * @param createID Mii create ID
 */
void RPSysPlayer::setAvatar(s8 dataSrc, u16 index, RFLCreateID createID) {
    mDataSource = dataSrc;
    mIndex = index;
    mCreateID = createID;
}

/**
 * @brief Loads this player's data
 *
 * @param rArg Parameter set
 */
void RPSysPlayer::loadData(const RPSysPlayerArg& rArg) {
    mPlayerDataIndex = mIndex;

    if (mDataSource == RFLDataSource_Official && mIndex < RFL_DB_CHAR_MAX) {
        RPSysSaveDataMgr* pSaveDataMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

        if (mpSportsPlayerData != NULL) {
            *mpSportsPlayerData =
                pSaveDataMgr->getSportsPlayerData(mPlayerDataIndex);
        }

        if (mpPartyPlayerData != NULL) {
            *mpPartyPlayerData =
                pSaveDataMgr->getPartyPlayerData(mPlayerDataIndex);
        }

    } else if (mDataSource == RFLDataSource_Default &&
               mIndex < RFL_DEFAULT_CHAR_MAX) {

        if (mpSportsPlayerData != NULL && rArg.pSportsPlayerData != NULL) {
            *mpSportsPlayerData = rArg.pSportsPlayerData[mPlayerDataIndex];
        }

        if (mpPartyPlayerData != NULL && rArg.pPartyPlayerData != NULL) {
            *mpPartyPlayerData = rArg.pPartyPlayerData[mPlayerDataIndex];
        }

    } else if (mDataSource >= RFLDataSource_Controller1 &&
               mDataSource <= RFLDataSource_Controller4 &&
               mIndex < RFL_CTRL_CHAR_MAX) {

        u32 ctrlIndex = mDataSource - RFLDataSource_Controller1;

        if (mpSportsPlayerData != NULL && rArg.ppTempSportsPlayerData != NULL) {
            *mpSportsPlayerData =
                rArg.ppTempSportsPlayerData[ctrlIndex][mPlayerDataIndex];
        }

        if (mpPartyPlayerData != NULL && rArg.ppTempPartyPlayerData != NULL) {
            *mpPartyPlayerData =
                rArg.ppTempPartyPlayerData[ctrlIndex][mPlayerDataIndex];
        }
    }

    RFLCreateID expected;
    mpSportsPlayerData->getCreateID(&expected);

    if (!IsSameCreateID(mCreateID, expected)) {
        mpSportsPlayerData->reset();
        mpSportsPlayerData->setCreateID(&mCreateID);
    }
}

/**
 * @brief Saves this player's data
 *
 * @param rArg Parameter set
 */
void RPSysPlayer::saveData(const RPSysPlayerArg& rArg) {
    if (mPlayerDataIndex < 0) {
        return;
    }

    if (mDataSource == RFLDataSource_Official &&
        mPlayerDataIndex < RFL_DB_CHAR_MAX) {

        RPSysSaveDataMgr* pSaveDataMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

        if (mpSportsPlayerData != NULL) {
            pSaveDataMgr->setSportsPlayerData(*mpSportsPlayerData,
                                              mPlayerDataIndex);
        }

        if (mpPartyPlayerData != NULL) {
            pSaveDataMgr->setPartyPlayerData(*mpPartyPlayerData,
                                             mPlayerDataIndex);
        }

    } else if (mDataSource == RFLDataSource_Default &&
               mPlayerDataIndex < RFL_DEFAULT_CHAR_MAX) {

        if (mpSportsPlayerData != NULL && rArg.pSportsPlayerData != NULL) {
            rArg.pSportsPlayerData[mPlayerDataIndex] = *mpSportsPlayerData;
        }

        if (mpPartyPlayerData != NULL && rArg.pPartyPlayerData != NULL) {
            rArg.pPartyPlayerData[mPlayerDataIndex] = *mpPartyPlayerData;
        }

    } else if (mDataSource >= RFLDataSource_Controller1 &&
               mDataSource <= RFLDataSource_Controller4 &&
               mPlayerDataIndex < RFL_CTRL_CHAR_MAX) {

        u32 ctrlIndex = mDataSource - RFLDataSource_Controller1;

        if (mpSportsPlayerData != NULL && rArg.ppTempSportsPlayerData != NULL) {
            rArg.ppTempSportsPlayerData[ctrlIndex][mPlayerDataIndex] =
                *mpSportsPlayerData;
        }

        if (mpPartyPlayerData != NULL && rArg.ppTempPartyPlayerData != NULL) {
            rArg.ppTempPartyPlayerData[ctrlIndex][mPlayerDataIndex] =
                *mpPartyPlayerData;
        }
    }
}
