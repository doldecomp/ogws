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
    /**
     * @brief Resets the old data to a default state
     */
    void resetOldData();

    /**
     * @brief Gets the player at the specified index
     *
     * @param idx Player index
     */
    const RPSysPlayer& getPlayer(s32 idx) const;

    /**
     * @brief Gets the remote channel associated with the specified player
     *
     * @param idx Player index
     */
    u8 getChannel(s32 idx) const;

    /**
     * @brief Gets the speaker flag required to play sounds through the
     * specified player's remote
     *
     * @param player Player index
     */
    u32 getSpeakerFlag(s32 player) const;

    /**
     * @brief Writes the save data for all players
     */
    void saveAllData();

    /**
     * @brief Tests whether the specified player has completed the A+B check
     *
     * @param player Player index
     */
    bool isABPress(s32 player) const;

    /**
     * @brief Sets that the specified player has completed the A+B check
     *
     * @param player Player index
     */
    void setABPress(s32 player);

    /**
     * @brief Resets the manager state
     */
    void reset();

    /**
     * @brief Gets the configured number of players
     */
    s32 getPlayerNum() const {
        return mPlayerNum;
    }

    /**
     * @brief Sets the number of players
     *
     * @param num Player count
     */
    void setPlayerNum(s32 num);

    /**
     * @brief Sets the number of controllers
     *
     * @param num Controller count
     */
    void setRemoteNum(s32 num);

    /**
     * @brief Tests whether the old data configuration for the current player
     * count is usable
     */
    bool isValidOldData();

    /**
     * @brief Gets the old data configuration for the specified player
     *
     * @param[out] pDataSrc Mii data source
     * @param[out] pIndex Mii database index
     * @param idx Player index
     */
    void getOldData(s8* pDataSrc, u16* pIndex, s32 idx);

    /**
     * @brief Tests whether the old data configuration for the specified player
     * describes a Mii from a controller database
     *
     * @param idx Player index
     */
    bool isCtrlOldData(s32 idx);

    /**
     * @brief Updates the old data configuration for the current player count
     */
    void calcOldData();

    /**
     * @brief Loads the old data configuration from the save file
     */
    void loadOldData();

    /**
     * @brief Writes the old data configuration to the save file
     */
    void saveOldData();

    /**
     * @brief Loads the save data for the specified player
     *
     * @param idx Player index
     */
    void loadData(s32 idx);

    /**
     * @brief Loads the save data for all players
     */
    void loadAllData();

    /**
     * @brief Sets the Mii avatar associated with the specified player
     *
     * @param dataSrc Mii data source
     * @param index Mii database index
     * @param rCreateID Mii create ID
     * @param idx Player index
     */
    void setAvatar(s8 dataSrc, u16 index, const RFLCreateID& rCreateID,
                   s32 idx);

private:
    //! Number of active players
    s32 mPlayerNum; // at 0x8
    //! Number of connected controllers
    s32 mRemoteNum; // at 0xC

    //! State flags
    u32 mFlags; // at 0x10

    //! Player objects
    RPSysPlayer* mpPlayers; // at 0x14
    //! Previous player configurations
    RPSysPlayerOldData* mpOldData; // at 0x18

    //! Sports Pack player save data for default database Miis
    RPSportsPlayerData* mpDefaultSportsPlayerData; // at 0x1C
    //! Sports Pack player save data for controller database Miis
    RPSportsPlayerData** mppCtrlSportsPlayerData; // at 0x20

    //! Party Pack player save data for default database Miis
    RPPartyPlayerData* mpDefaultPartyPlayerData; // at 0x24
    //! Party Pack player save data for controller database Miis
    RPPartyPlayerData** mppCtrlPartyPlayerData; // at 0x28
};

//! @}

#endif
