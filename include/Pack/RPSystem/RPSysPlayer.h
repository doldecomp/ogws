#ifndef RP_SYSTEM_PLAYER_H
#define RP_SYSTEM_PLAYER_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPPartyPlayerData.h>
#include <Pack/RPSystem/RPSportsPlayerData.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Player function parameter set
 */
struct RPSysPlayerArg {
    //! Sports Pack player data for official database Miis
    RPSportsPlayerData* pSportsPlayerData; // at 0x0
    //! Sports Pack player data for temporary storage (guest/controller miis)
    RPSportsPlayerData** ppTempSportsPlayerData; // at 0x4

    //! Party Pack player data for official database Miis
    RPPartyPlayerData* pPartyPlayerData; // at 0x8
    //! Party Pack player data for temporary storage (guest/controller miis)
    RPPartyPlayerData** ppTempPartyPlayerData; // at 0xC
};

/**
 * @brief Player object
 */
class RPSysPlayer {
public:
    /**
     * @brief Constructor
     */
    RPSysPlayer();

    /**
     * @brief Destructor
     */
    ~RPSysPlayer() {
        // @bug Memory leak
#if defined(BUG_FIX)
        delete mpSportsPlayerData;
        mpSportsPlayerData = NULL;

        delete mpPartyPlayerData;
        mpPartyPlayerData = NULL;
#endif
    }

    /**
     * @brief Resets the data to a default state
     */
    void reset();

    /**
     * @brief Sets the Mii avatar associated with this player
     *
     * @param dataSrc Mii data source
     * @param index Mii database index
     * @param createID Mii create ID
     */
    void setAvatar(s8 dataSrc, u16 index, RFLCreateID createID);

    /**
     * @brief Loads this player's data
     *
     * @param rArg Parameter set
     */
    void loadData(const RPSysPlayerArg& rArg);

    /**
     * @brief Saves this player's data
     *
     * @param rArg Parameter set
     */
    void saveData(const RPSysPlayerArg& rArg);

    /**
     * @brief Gets the RFL data source where this player avatar can be found
     * @details If the data source was never configured, this value will be -1.
     */
    s8 getDataSource() const {
        return mDataSource;
    }

    /**
     * @brief Gets the database index where this player avatar can be found
     */
    u16 getIndex() const {
        return mIndex;
    }

private:
    //! Controller channel
    u8 mChannel; // at 0x0

    //! Mii data source
    s8 mDataSource; // at 0x1
    //! Mii database index
    u16 mIndex; // at 0x2
    //! Mii create ID
    RFLCreateID mCreateID; // at 0x4

    //! Player data list index
    s32 mPlayerDataIndex; // at 0xC

    //! Sports Pack player data
    RPSportsPlayerData* mpSportsPlayerData; // at 0x10
    //! Party Pack player datya
    RPPartyPlayerData* mpPartyPlayerData; // at 0x14
};

//! @}

#endif
