#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

RP_SINGLETON_IMPL_EX(RPSysPlayerMgr);

/**
 * @brief Resets the old data to a default state
 */
void RPSysPlayerMgr::resetOldData() {
    for (int i = 0; i < OLD_DATA_LEN; i++) {
        mpOldData[i].dataSource = -1;
        mpOldData[i].index = -1;

        for (int j = 0; j < RFL_CREATEID_LEN; j++) {
            mpOldData[i].createID.data[j] = 0;
        }

        mpOldData[i].address.reset();
    }
}

/**
 * @brief Gets the player at the specified index
 *
 * @param idx Player index
 */
const RPSysPlayer& RPSysPlayerMgr::getPlayer(s32 idx) const {
    return mpPlayers[idx];
}

/**
 * @brief Gets the remote channel associated with the specified player
 *
 * @param idx Player index
 */
u8 RPSysPlayerMgr::getChannel(s32 idx) const {
    return mpPlayers[idx].getChannel();
}

/**
 * @brief Gets the speaker flag required to play sounds through the
 * specified player's remote
 *
 * @param player Player index
 */
u32 RPSysPlayerMgr::getSpeakerFlag(s32 player) const {
    // TODO(kiwi) Uses something from RPSysCoreController
    s32 chan = getChannel(player);

    if (chan == WPAD_CHAN0) {
        return 1 << WPAD_CHAN0;
    }

    if (chan == WPAD_CHAN1) {
        return 1 << WPAD_CHAN1;
    }

    if (chan == WPAD_CHAN2) {
        return 1 << WPAD_CHAN2;
    }

    if (chan == WPAD_CHAN3) {
        return 1 << WPAD_CHAN3;
    }

    return 1 << WPAD_CHAN0 | //
           1 << WPAD_CHAN1 | //
           1 << WPAD_CHAN2 | //
           1 << WPAD_CHAN3;
}

/**
 * @brief Writes the save data for all players
 */
void RPSysPlayerMgr::saveAllData() {
    for (int i = 0; i < mPlayerNum; i++) {
        RPSysPlayerArg arg;
        arg.pDefaultSportsPlayerData = mpDefaultSportsPlayerData;
        arg.ppCtrlSportsPlayerData = mppCtrlSportsPlayerData;
        arg.pDefaultPartyPlayerData = mpDefaultPartyPlayerData;
        arg.ppCtrlPartyPlayerData = mppCtrlPartyPlayerData;

        mpPlayers[i].saveData(arg);
    }
}

/**
 * @brief Tests whether the specified player has completed the A+B check
 *
 * @param player Player index
 */
bool RPSysPlayerMgr::isABPress(s32 player) const {
    return mFlags & 1 << static_cast<u8>(player);
}

/**
 * @brief Sets that the specified player has completed the A+B check
 *
 * @param player Player index
 */
void RPSysPlayerMgr::setABPress(s32 player) {
    mFlags |= 1 << static_cast<u8>(player);
}

/**
 * @brief Resets the manager state
 */
void RPSysPlayerMgr::reset() {
    mPlayerNum = 0;
    mRemoteNum = 0;

    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        mpPlayers[i].reset();
    }
}

/**
 * @brief Sets the number of players
 *
 * @param num Player count
 */
void RPSysPlayerMgr::setPlayerNum(s32 num) {
    mPlayerNum = num;
}

/**
 * @brief Sets the number of controllers
 *
 * @param num Controller count
 */
void RPSysPlayerMgr::setRemoteNum(s32 num) {
    mRemoteNum = num < mPlayerNum ? num : mPlayerNum;

    s32 chan = WPAD_CHAN0;
    for (int i = 0; i < mPlayerNum; i++) {
        mpPlayers[i].setChannel(chan);

        if (++chan > num - 1) {
            chan = WPAD_CHAN0;
        }
    }
}

/**
 * @brief Tests whether the old data configuration for the current player
 * count is usable
 */
bool RPSysPlayerMgr::isValidOldData() {
    // Can't use old data when people are sharing remotes
    if (mPlayerNum == mRemoteNum) {
        s32 rel2Abs[RP_MAX_PLAYERS] = {
            0,     // 1 player
            0 + 1, // 2 players
#if defined(PACK_SPORTS)
            0 + 1 + 2,     // 3 players
            0 + 1 + 2 + 3, // 4 players
#endif
        };

        s32 relIdx = mPlayerNum;
        s32 absIdx = rel2Abs[--relIdx];

        for (int i = absIdx; i < absIdx + mPlayerNum; i++) {
            if (mpOldData[i].dataSource != RFLDataSource_Official) {
                continue;
            }

            s16 expected = RPSysKokeshiManager::GetOfficialDBIndexFromCreateID(
                &mpOldData[i].createID);

            // Mii database has changed since last play
            if (mpOldData[i].index != expected) {
                return false;
            }
        }

        s32 player = 0;
        s32 found = 0;

        for (int i = absIdx; i < absIdx + mPlayerNum; i++, player++) {
            for (int j = absIdx; j < absIdx + mPlayerNum; j++) {
                if (!mpOldData[j].address.isValid()) {
                    continue;
                }

                RPSysCoreController* pController =
                    RPSysCoreControllerMgr::getNthController(player);

                if (pController->getAddress() == mpOldData[j].address) {
                    found++;
                    mpOldData[i] = RPSysPlayerOldData(mpOldData[j]);
                    break;
                }
            }
        }

        return found == mPlayerNum;
    }

    return false;
}

/**
 * @brief Gets the old data configuration for the current player count
 *
 * @param[out] pDataSrc Mii data source
 * @param[out] pIndex Mii database index
 * @param idx Player index
 */
void RPSysPlayerMgr::getOldData(s8* pDataSrc, u16* pIndex, s32 idx) {
    s32 rel2Abs[RP_MAX_PLAYERS] = {
        0,     // 1 player
        0 + 1, // 2 players
#if defined(PACK_SPORTS)
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
#endif
    };

    s32 relIdx = mPlayerNum;
    s32 absIdx = rel2Abs[--relIdx];

    *pDataSrc = mpOldData[idx + absIdx].dataSource;
    *pIndex = mpOldData[idx + absIdx].index;
}

/**
 * @brief Tests whether the old data configuration for the specified player
 * describes a Mii from a controller database
 *
 * @param idx Player index
 */
bool RPSysPlayerMgr::isCtrlOldData(s32 idx) {
    s32 rel2Abs[RP_MAX_PLAYERS] = {
        0,     // 1 player
        0 + 1, // 2 players
#if defined(PACK_SPORTS)
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
#endif
    };

    s32 relIdx = mPlayerNum;
    s32 absIdx = rel2Abs[--relIdx];

    if (mpOldData[idx + absIdx].dataSource >= RFLDataSource_Controller1 &&
        mpOldData[idx + absIdx].dataSource <= RFLDataSource_Controller4 &&
        mpOldData[idx + absIdx].index < RFL_CTRL_CHAR_MAX) {

        return true;
    }

    return false;
}

/**
 * @brief Updates the old data configuration for the current player count
 */
void RPSysPlayerMgr::calcOldData() {
    // Can't use old data when people are sharing remotes
    if (mPlayerNum == mRemoteNum) {
        s32 rel2Abs[RP_MAX_PLAYERS] = {
            0,     // 1 player
            0 + 1, // 2 players
#if defined(PACK_SPORTS)
            0 + 1 + 2,     // 3 players
            0 + 1 + 2 + 3, // 4 players
#endif
        };

        s32 relIdx = mPlayerNum;
        s32 absIdx = rel2Abs[--relIdx];

        for (int i = 0; i < mPlayerNum; i++) {
            mpOldData[i + absIdx].dataSource = mpPlayers[i].getDataSource();
            mpOldData[i + absIdx].index = mpPlayers[i].getIndex();
            mpOldData[i + absIdx].createID = mpPlayers[i].getCreateID();

            RPSysCoreController* pController =
                RPSysCoreControllerMgr::getNthController(i);

            mpOldData[i + absIdx].address = pController->getAddress();
        }
    }
}

/**
 * @brief Loads the old data configuration from the save file
 */
void RPSysPlayerMgr::loadOldData() {
    s32 rel2Abs[RP_MAX_PLAYERS] = {
        0,     // 1 player
        0 + 1, // 2 players
#if defined(PACK_SPORTS)
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
#endif
    };

    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        s32 firstIdx = rel2Abs[i];

        // Already in use
        if (mpOldData[firstIdx].dataSource != -1 ||
            mpOldData[firstIdx].index != 0xFFFF) {
            continue;
        }

        for (int j = 0; j < i + 1; j++) {
            s32 currIdx = j + firstIdx;

#if defined(PACK_SPORTS)
            RPSportsSystemData systemData =
                RP_GET_INSTANCE(RPSysSaveDataMgr)->getSportsSystemData();
#elif defined(PACK_PARTY)
            RPPartySystemData systemData =
                RP_GET_INSTANCE(RPSysSaveDataMgr)->getPartySystemData();
#endif

            s8 index;
            u8 addr[WPAD_ADDR_LEN];
            systemData.getOldData(&index, addr, i + 1, j);

            if (index >= 0) {
                mpOldData[currIdx].dataSource = RFLDataSource_Official;
                mpOldData[currIdx].index = index;

#if defined(PACK_SPORTS)
                RP_GET_INSTANCE(RPSysSaveDataMgr)
                    ->getSportsPlayerData(index)
                    .getCreateID(&mpOldData[currIdx].createID);
#elif defined(PACK_PARTY)
                RP_GET_INSTANCE(RPSysSaveDataMgr)
                    ->getPartyPlayerData(index)
                    .getCreateID(&mpOldData[currIdx].createID);
#endif

                mpOldData[currIdx].address.set(addr);
            }
        }
    }
}

/**
 * @brief Writes the old data configuration to the save file
 */
void RPSysPlayerMgr::saveOldData() {
    s32 rel2Abs[RP_MAX_PLAYERS] = {
        0,     // 1 player
        0 + 1, // 2 players
#if defined(PACK_SPORTS)
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
#endif
    };

    bool valid[RP_MAX_PLAYERS] = {
        true, // 1 player
        true, // 2 players
#if defined(PACK_SPORTS)
        true, // 3 players
        true, // 4 players
#endif
    };

    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        s32 firstIdx = rel2Abs[i];

        if (mpOldData[firstIdx].dataSource != RFLDataSource_Official ||
            mpOldData[firstIdx].index >= RFL_DB_CHAR_MAX ||
            !mpOldData[firstIdx].address.isValid()) {

            valid[firstIdx] = false;
        }
    }

    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        s32 firstIdx = rel2Abs[i];

        for (int j = 0; i < i + 1; j++) {
            s32 currIdx = j + firstIdx;

            u8 addr[WPAD_ADDR_LEN];
            for (int k = 0; k < WPAD_ADDR_LEN; k++) {
                addr[k] = mpOldData[currIdx].address[k];
            }

#if defined(PACK_SPORTS)
            RPSportsSystemData systemData =
                RP_GET_INSTANCE(RPSysSaveDataMgr)->getSportsSystemData();
#elif defined(PACK_PARTY)
            RPPartySystemData systemData =
                RP_GET_INSTANCE(RPSysSaveDataMgr)->getPartySystemData();
#endif

            systemData.setOldData(mpOldData[currIdx].index, addr, i, j);

#if defined(PACK_SPORTS)
            RP_GET_INSTANCE(RPSysSaveDataMgr)->setSportsSystemData(systemData);
#elif defined(PACK_PARTY)
            RP_GET_INSTANCE(RPSysSaveDataMgr)->setPartySystemData(systemData);
#endif
        }
    }
}

/**
 * @brief Loads the save data for the specified player
 *
 * @param idx Player index
 */
void RPSysPlayerMgr::loadData(s32 idx) {
    RPSysPlayerArg arg;
    arg.pDefaultSportsPlayerData = mpDefaultSportsPlayerData;
    arg.ppCtrlSportsPlayerData = mppCtrlSportsPlayerData;
    arg.pDefaultPartyPlayerData = mpDefaultPartyPlayerData;
    arg.ppCtrlPartyPlayerData = mppCtrlPartyPlayerData;

    mpPlayers[idx].loadData(arg);
}

/**
 * @brief Loads the save data for all players
 */
void RPSysPlayerMgr::loadAllData() {
    RPSysPlayerArg arg;
    arg.pDefaultSportsPlayerData = mpDefaultSportsPlayerData;
    arg.ppCtrlSportsPlayerData = mppCtrlSportsPlayerData;
    arg.pDefaultPartyPlayerData = mpDefaultPartyPlayerData;
    arg.ppCtrlPartyPlayerData = mppCtrlPartyPlayerData;

    for (int i = 0; i < mPlayerNum; i++) {
        mpPlayers[i].loadData(arg);
    }
}

/**
 * @brief Sets the Mii avatar associated with the specified player
 *
 * @param dataSrc Mii data source
 * @param index Mii database index
 * @param rCreateID Mii create ID
 * @param idx Player index
 */
void RPSysPlayerMgr::setAvatar(s8 dataSrc, u16 index,
                               const RFLCreateID& rCreateID, s32 idx) {

    mpPlayers[idx].setAvatar(dataSrc, index, rCreateID);
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysPlayerMgr::RPSysPlayerMgr(EGG::Heap* pHeap)
    : mpParentHeap(pHeap),
      mPlayerNum(0),
      mRemoteNum(0),
      mFlags(0),
      mpPlayers(new RPSysPlayer[RP_MAX_PLAYERS]),
      mpOldData(new RPSysPlayerOldData[OLD_DATA_LEN]),
      mpDefaultSportsPlayerData(NULL),
      mppCtrlSportsPlayerData(NULL),
      mpDefaultPartyPlayerData(NULL),
      mppCtrlPartyPlayerData(NULL) {

#if defined(PACK_SPORTS)
    mpDefaultSportsPlayerData = new RPSportsPlayerData[RFL_DEFAULT_CHAR_MAX];
    mppCtrlSportsPlayerData = new RPSportsPlayerData*[RP_MAX_CONTROLLERS];

    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        mppCtrlSportsPlayerData[i] = new RPSportsPlayerData[OLD_DATA_LEN];
    }
#elif defined(PACK_PARTY)
    mpDefaultPartyPlayerData = new RPPartyPlayerData[RFL_DEFAULT_CHAR_MAX];
    mppCtrlPartyPlayerData = new RPPartyPlayerData*[RP_MAX_CONTROLLERS];

    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        mppCtrlPartyPlayerData[i] = new RPSportsPlayerData[OLD_DATA_LEN];
    }
#endif

    resetOldData();
}

/**
 * @brief Destructor
 */
RPSysPlayerMgr::~RPSysPlayerMgr() {}
