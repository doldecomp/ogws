#ifndef RP_SYSTEM_PLAYER_MGR_H
#define RP_SYSTEM_PLAYER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPPartySystemData.h>
#include <Pack/RPSystem/RPSportsSystemData.h>
#include <Pack/RPSystem/RPSysPlayer.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

struct RPSysPlayerOldData {
    //! Mii data source
    s8 dataSource; // at 0x0
    //! Mii database index
    u16 index; // at 0x2
    //! Mii create ID
    RFLCreateID createID; // at 0x4
    //! Controller address
    RPSysCoreAddress address; // at 0xC
};

/**
 * @brief Player manager
 */
class RPSysPlayerMgr {
    RP_SINGLETON_DECL_EX(RPSysPlayerMgr);

public:
    //! Number of old data entries
#if defined(PACK_SPORTS)
    static const int OLD_DATA_LEN = RPSportsSystemData::OLD_DATA_LEN;
#elif defined(PACK_PARTY)
    static const int OLD_DATA_LEN = RPPartySystemData::OLD_DATA_LEN;
#endif

public:
    void resetOldData();

    const RPSysPlayer& getPlayer(s32 idx) const;

    u8 getChannel(s32 idx) const;

    u32 getSpeakerFlag(s32 player) const;

    void saveAllData();

    bool isABPress(s32 player) const;
    void setABPress(s32 player);

    void reset();

    void setPlayerNum(s32 num);
    void setRemoteNum(s32 num);

    bool isValidOldData();
    void getOldData(s8* pDataSrc, u16* pIndex, s32 idx);
    bool isCtrlOldData(s32 idx);
    void calcOldData();

    void loadOldData();
    void saveOldData();

    s32 getPlayerNum() const {
        return mPlayerNum;
    }

private:
    s32 mPlayerNum; // at 0x8
    s32 mRemoteNum; // at 0xC

    u32 mFlags;                    // at 0x10
    RPSysPlayer* mpPlayers;        // at 0x14
    RPSysPlayerOldData* mpOldData; // at 0x18

    RPSportsPlayerData* mpSportsPlayerData;       // at 0x1C
    RPSportsPlayerData** mppCtrlSportsPlayerData; // at 0x20
    RPPartyPlayerData* mpPartyPlayerData;         // at 0x24
    RPPartyPlayerData** mppCtrlPartyPlayerData;   // at 0x28
};

//! @}

#endif
