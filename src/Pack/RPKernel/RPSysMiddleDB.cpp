#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <RVLFaceLib/RVLFaceLibInternal.h>

/**
 * @brief Constructor
 *
 * @param pGenInfo Middle DB generation parameters
 */
RPSysMiddleDB::RPSysMiddleDB(const RPSysMiddleDBGenInfo* pGenInfo)
    : mSize(pGenInfo->GetSize()), mStoredNum(0), mCurrentIndex(0) {

    u32 middleBufSize = RFLGetMiddleDBBufferSize(pGenInfo->GetSize());

    switch (pGenInfo->GetType()) {
    case RFLMiddleDBType_HiddenRandom:
    case RFLMiddleDBType_HiddenNewer:
    case RFLMiddleDBType_HiddenOlder: {
        u8* pHiddenBuf = new u8[middleBufSize];
        mpMiddleDB = new RFLMiddleDB();

        RFLInitMiddleDB(mpMiddleDB, pGenInfo->GetType(), pHiddenBuf,
                        pGenInfo->GetSize());

        RFLSetMiddleDBHiddenMask(mpMiddleDB, pGenInfo->GetGenderMask());

        switch (RFLUpdateMiddleDBAsync(mpMiddleDB)) {
        case RFLErrcode_DBNodata: {
            mStoredNum = 0;
            break;
        }

        case RFLErrcode_Busy: {
            break;
        }

        default: {
            mStoredNum = 0;
            break;
        }
        }

        switch (RFLWaitAsync()) {
        case RFLErrcode_Success:
        case RFLErrcode_DBNodata: {
            mStoredNum = RFLGetMiddleDBStoredSize(mpMiddleDB);
            break;
        }

        case RFLErrcode_NANDCommandfail:
        case RFLErrcode_Fatal:
        case RFLErrcode_Broken: {
            mStoredNum = 0;
            break;
        }

        default: {
            mStoredNum = 0;
            break;
        }
        }

        break;
    }

    case RFLMiddleDBType_UserSet: {
        RPSysAppMiiManager* pMiiManager = pGenInfo->GetMiiManager();

        u8* pUserSetBuf = new u8[middleBufSize];
        mpMiddleDB = new RFLMiddleDB();

        RFLInitMiddleDB(mpMiddleDB, pGenInfo->GetType(), pUserSetBuf,
                        pGenInfo->GetSize());

        u16 userSetSize = pGenInfo->GetSize();
        if (userSetSize >= pMiiManager->GetNumData()) {
            userSetSize = pMiiManager->GetNumData();
        }

        for (u16 i = 0; i < userSetSize; i++) {
            // Only Wii Sports uses character data (no checksum)
            if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
                RPSysSceneCreator::EPackID_SportsPack) {

                RFLiAddMiddleDBUserData(mpMiddleDB,
                                        pMiiManager->GetCharData(i));
            } else {
                RFLAddMiddleDBStoreData(mpMiddleDB,
                                        pMiiManager->GetStoreData(i));
            }
        }

        mStoredNum = RFLGetMiddleDBStoredSize(mpMiddleDB);
        break;
    }

    default: {
        mpMiddleDB = NULL;
        break;
    }
    }

    u32 randomBufSize = RFLGetMiddleDBBufferSize(mSize);
    u8* pRandomBuf = new u8[randomBufSize];
    mpRandomDB = new RFLMiddleDB();

    u16 randomSize = pGenInfo->GetSize();
    if (randomSize > RFL_DB_CHAR_MAX) {
        randomSize = RFL_DB_CHAR_MAX;
    }

    RFLInitMiddleDB(mpRandomDB, RFLMiddleDBType_Random, pRandomBuf, randomSize);

    RFLSetMiddleDBRandomMask(mpRandomDB, pGenInfo->GetGenderMask(),
                             pGenInfo->GetAgeMask(), pGenInfo->GetRaceMask());

    RFLUpdateMiddleDBAsync(mpRandomDB);
}

/**
 * @brief Destructor
 */
RPSysMiddleDB::~RPSysMiddleDB() {}

/**
 * @brief Increments the current database index
 * @details The current index wraps around when it becomes invalid
 */
void RPSysMiddleDB::IncrementCurrentIndex() {
    mCurrentIndex++;

    if (mSize <= mCurrentIndex) {
        mCurrentIndex = 0;
    }
}

/**
 * @brief Gets the RFL parameters necessary to access the specified Mii
 * @details If the index is invalid for the middle database, the parameters
 * returned will instead fetch a Mii from the random database.
 *
 * @param index Database index
 * @param ppMiddleDB Middle DB to use with RFL
 * @param pIndex Database index to use with RFL
 */
void RPSysMiddleDB::GetRFLMiddleDB(u16 index, RFLMiddleDB** ppMiddleDB,
                                   u16* pIndex) {
    if (mStoredNum > index) {
        *ppMiddleDB = mpMiddleDB;
        *pIndex = index;
    } else {
        *ppMiddleDB = mpRandomDB;
        *pIndex = (index - mStoredNum) % RFLGetMiddleDBStoredSize(mpRandomDB);
    }
}
