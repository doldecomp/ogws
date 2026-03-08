#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

RP_SINGLETON_IMPL_EX(RPSysPlayerMgr);

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

const RPSysPlayer& RPSysPlayerMgr::getPlayer(s32 idx) const {
    return mpPlayers[idx];
}

u8 RPSysPlayerMgr::getChannel(s32 idx) const {
    return mpPlayers[idx].getChannel();
}

u32 RPSysPlayerMgr::getSpeakerFlag(s32 player) const {
    // TODO(kiwi) Uses something from RPSysCoreControllerMgr...
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

void RPSysPlayerMgr::saveAllData() {
    for (int i = 0; i < mPlayerNum; i++) {
        RPSysPlayerArg arg;
        arg.pSportsPlayerData = mpSportsPlayerData;
        arg.ppCtrlSportsPlayerData = mppCtrlSportsPlayerData;
        arg.pPartyPlayerData = mpPartyPlayerData;
        arg.ppCtrlPartyPlayerData = mppCtrlPartyPlayerData;

        mpPlayers[i].saveData(arg);
    }
}

bool RPSysPlayerMgr::isABPress(s32 player) const {
    return mFlags & 1 << static_cast<u8>(player);
}

void RPSysPlayerMgr::setABPress(s32 player) {
    mFlags |= 1 << static_cast<u8>(player);
}

void RPSysPlayerMgr::reset() {
    mPlayerNum = 0;
    mRemoteNum = 0;

    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        mpPlayers[i].reset();
    }
}

void RPSysPlayerMgr::setPlayerNum(s32 num) {
    mPlayerNum = num;
}

void RPSysPlayerMgr::setRemoteNum(s32 num) {
    mRemoteNum = num < mPlayerNum ? num : mPlayerNum;

    s32 chan = 0;
    for (int i = 0; i < mPlayerNum; i++) {
        mpPlayers[i].setChannel(chan);

        if (++chan > num - 1) {
            chan = 0;
        }
    }
}

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

void RPSysPlayerMgr::saveOldData() {
    s32 rel2Abs[RP_MAX_PLAYERS] = {
        0,     // 1 player
        0 + 1, // 2 players
#if defined(PACK_SPORTS)
        0 + 1 + 2,     // 3 players
        0 + 1 + 2 + 3, // 4 players
#endif
    };

    bool valid[RP_MAX_PLAYERS];
    for (int i = 0; i < RP_MAX_PLAYERS; i++) {
        valid[i] = true;
    }

    ;
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysPlayerMgr::RPSysPlayerMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {}

/**
 * @brief Destructor
 */
RPSysPlayerMgr::~RPSysPlayerMgr() {}
