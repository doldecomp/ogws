#ifndef RP_SYSTEM_PARTY_SYSTEM_DATA_H
#define RP_SYSTEM_PARTY_SYSTEM_DATA_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Party Pack save file system data
 */
class RPPartySystemData {
public:
    /**
     * @brief Minigame ID
     */
    enum EGame {
        EGame_Duc, //!< Shooting Range
        EGame_Wly, //!< Find Mii
        EGame_Pnp, //!< Table Tennis
        EGame_Bom, //!< Pose Mii
        EGame_Hky, //!< Laser Hockey
        EGame_Bil, //!< Billiards
        EGame_Fsh, //!< Fishing
        EGame_Cow, //!< Charge!
        EGame_Tnk, //!< Tanks!

        EGame_Max,
    };

    /**
     * @brief Message ID
     */
    enum EMsg {
        EMsg_Welcome,    //!< Play for the first time
        EMsg_StageTwo,   //!< Unlock stage two
        EMsg_StageThree, //!< Unlock stage three
        EMsg_StageFour,  //!< Unlock stage four
        EMsg_StageFive,  //!< Unlock stage five
        EMsg_StageSix,   //!< Unlock stage six
        EMsg_StageSeven, //!< Unlock stage seven
        EMsg_StageEight, //!< Unlock stage eight
        EMsg_StageFinal, //!< Unlock the final stage
        EMsg_Master,     //!< Completed all stages

        EMsg_Max
    };

public:
    /**
     * @brief Constructor
     */
    RPPartySystemData();

    /**
     * @brief Tests whether the specified minigame is available
     *
     * @param idx Minigame index
     */
    bool isGameOpen(s32 idx) const;

private:
    //! Old data exists for each player count
    static const int OLD_DATA_LEN = 1 + 2;

private:
    /**
     * @name Previous Mii data
     */
    /**@{*/
    //! Official database index
    s8 mOldIndex[OLD_DATA_LEN]; // at 0x0
    //! Remote Blutetooth address
    u8 mOldAddress[OLD_DATA_LEN][WPAD_ADDR_LEN]; // at 0x3
    /**@}*/

    //! Number of new players registered today
    u8 mRegistTodayCount; // at 0x15
    //! Last fitness test completed
    RPTime16 mRegistLastDate; // at 0x16

    //! Game unlock flags
    EGG::TBitFlag<u32> mGameFlags; // at 0x18
    //! Message seen flags
    EGG::TBitFlag<u32> mMsgFlags; // at 0x1C
};

//! @}

#endif
