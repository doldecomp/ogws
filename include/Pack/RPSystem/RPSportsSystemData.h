#ifndef RP_SYSTEM_SPORTS_SYSTEM_DATA_H
#define RP_SYSTEM_SPORTS_SYSTEM_DATA_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Sports Pack save file system data
 */
class RPSportsSystemData {
public:
    /**
     * @brief Training game ID
     */
    enum EGame {
        EGame_Box_Mituchi,  //!< Throwing Punches
        EGame_Box_Tamayoke, //!< Dodging
        EGame_Box_Sandbag,  //!< Working the Bag

        EGame_Gol_Target,  //!< Target Practice
        EGame_Gol_Nearpin, //!< Hitting the Green
        EGame_Gol_Onepat,  //!< Putting

        EGame_Bow_Gatetoshi,  //!< Spin Control
        EGame_Bow_Nagitaoshi, //!< Power Throws
        EGame_Bow_Spareget,   //!< Picking Up Spares

        EGame_Bsb_Renzoku,  //!< Batting Practice
        EGame_Bsb_Uchiwake, //!< Swing Control
        EGame_Bsb_Homerun,  //!< Hitting Home Runs

        EGame_Tns_Kabeuchi,  //!< Target Practice
        EGame_Tns_Nerauchii, //!< Timing Your Swing
        EGame_Tns_Renzoku,   //!< Returning Balls

        EGame_Max,
    };

public:
    /**
     * @brief Constructor
     */
    RPSportsSystemData();

    /**
     * @brief Resets the data to a default save state
     */
    void reset();

    /**
     * @brief Gets the old data for the specified player count and player index
     *
     * @param[out] pIndex Official database index
     * @param[out] pAddr Remote Bluetooth address
     * @param playerNum Player count
     * @param playerNo Player index
     */
    void getOldData(s8* pIndex, u8* pAddr, s32 playerNum, s32 playerNo) const;
    /**
     * @brief Sets the old data for the specified player count and player index
     *
     * @param[out] pIndex Official database index
     * @param[out] pAddr Remote Bluetooth address
     * @param playerNum Player count
     * @param playerNo Player index
     */
    void setOldData(s8 index, const u8* pAddr, s32 playerNum, s32 playerNo);

    /**
     * @brief Sets the total number of fitness tests completed
     *
     * @param count Number of fitness tests completed
     */
    void setPhysicalEndCount(u8 count);
    /**
     * @brief Gets the total number of fitness tests completed
     */
    u8 getPhysicalEndCount() const;

    /**
     * @brief Sets the last date on which a fitness test was completed
     *
     * @param date Last completion date
     */
    void setPhysicalEndLastDate(RPTime16 date);
    /**
     * @brief Gets the last date on which a fitness test was completed
     */
    RPTime16 getPhysicalEndLastDate() const;

    /**
     * @brief Sets whether the specified training game's unlock cutscene has
     * played
     *
     * @param idx Training game index
     * @param open Whether the unlock cutscene has played
     */
    void setGameOpenDemo(u8 idx, bool open);
    /**
     * @brief Tests whether the specified training game's unlock cutscene has
     * played
     *
     * @param idx Training game index
     */
    bool isGameOpenDemo(u8 idx) const;

    /**
     * @brief Sets whether the specified training game is available
     *
     * @param idx Training game index
     * @param open Whether the game is available
     */
    void setGameOpen(u8 idx, bool open);
    /**
     * @brief Tests whether the specified training game is available
     *
     * @param idx Training game index
     */
    bool isGameOpen(u8 idx) const;

    /**
     * @brief Deserializes this object from the specified stream
     *
     * @param rStrm Memory stream
     */
    void read(EGG::RamStream& rStrm);
    /**
     * @brief Serializes this object to the specified stream
     *
     * @param rStrm Memory stream
     */
    void write(EGG::RamStream& rStrm);

private:
    //! Old data exists for each player count
    static const int OLD_DATA_LEN = 1 + 2 + 3 + 4;

private:
    /**
     * @name Previous Mii data
     */
    /**@{*/
    //! Official database index
    s8 mOldIndex[OLD_DATA_LEN]; // at 0x0
    //! Remote Blutetooth address
    u8 mOldAddress[OLD_DATA_LEN][WPAD_ADDR_LEN]; // at 0xA
    /**@}*/

    //! Total number of fitness tests completed
    u8 mPhysicalCount; // at 0x46
    //! Last fitness test completed
    RPTime16 mPhysicalEndLastDate; // at 0x48

    u16 unk4A;
    u8 unk4C;

    //! Game/demo bitflags
    EGG::TBitFlag<u32> mFlags; // at 0x50
    EGG::TBitFlag<u32> unk54;
};

//! @}

#endif
