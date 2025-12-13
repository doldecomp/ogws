#ifndef RP_SYSTEM_SAVE_DATA_H
#define RP_SYSTEM_SAVE_DATA_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPPartyPlayerData;
class RPPartySystemData;
class RPSportsPlayerData;
class RPSportsSystemData;

/**
 * @brief Pack Project save data
 */
class RPSysSaveData {
public:
    //! Length of the player list
    static const int PLAYER_LIST_SIZE = 100;

public:
    /**
     * @brief Constructor
     */
    RPSysSaveData();

    /**
     * @brief Resets the save data state
     */
    void reset();

    /**
     * @brief Tests whether an error occurred while reading the save file
     * @typo
     */
    bool isErrorOccured() const;

    /**
     * @brief Gets the Sports Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPSportsPlayerData* getSportsPlayerData(u32 idx) const;
    /**
     * @brief Sets the Sports Pack player data at the specified player list
     * index
     *
     * @param pPlayerData Player data
     * @param idx Player list index
     */
    void setSportsPlayerData(const RPSportsPlayerData* pPlayerData, u32 idx);

    /**
     * @brief Gets the Sports Pack system data
     */
    RPSportsSystemData* getSportsSystemData() const;
    /**
     * @brief Sets the Sports Pack system data
     *
     * @param pSystemData System data
     */
    void setSportsSystemData(const RPSportsSystemData* pSystemData);

    /**
     * @brief Gets the Party Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPPartyPlayerData* getPartyPlayerData(u32 idx) const;
    /**
     * @brief Sets the Party Pack player data at the specified player list
     * index
     *
     * @param pPlayerData Player data
     * @param idx Player list index
     */
    void setPartyPlayerData(const RPPartyPlayerData* pPlayerData, u32 idx);

    /**
     * @brief Gets the Party Pack system data
     */
    RPPartySystemData* getPartySystemData() const;
    /**
     * @brief Sets the Party Pack system data
     *
     * @param pSystemData System data
     */
    void setPartySystemData(const RPPartySystemData* pSystemData);

    /**
     * @brief Deserializes this object from the specified stream
     *
     * @param rStrm Memory stream
     * @param pRawSave Raw save data
     */
    void read(EGG::RamStream& rStrm, const void* pRawSave);
    /**
     * @brief Serializes this object to the specified stream
     *
     * @param rStrm Memory stream
     * @param pRawSave Raw save data
     */
    void write(EGG::RamStream& rStrm, const void* pRawSave) const;

    /**
     * @brief Gets the size of the current pack's save file, in bytes
     */
    static u32 getSaveFileSize();

private:
    enum {
        EFlag_BadPack,    //!< The save file is not for this pack
        EFlag_BadVersion, //!< The save file is not for this version
        EFlag_BadCrc,     //!< The save file checksum is invalid
    };

    //! Name of the Pack Project game this save file is intended for
#if defined(PACK_SPORTS)
    static const u32 SIGNATURE_PACK = FOURCC('R', 'P', 'S', 'P');
#elif defined(PACK_PARTY)
    static const u32 SIGNATURE_PACK = FOURCC('R', 'P', 'P', 'T');
#endif

    //! Version of this save file
    static const u32 SIGNATURE_VERSION = FOURCC('0', '0', '0', '0');

private:
    /**
     * @brief Calculates a checksum of the specified data
     *
     * @param pData Data buffer
     * @param size Buffer size
     * @return 32-bit checksum
     */
    static u32 calcCrc(const void* pData, u32 size);

private:
    //! Data error flags
    EGG::TBitFlag<u32> mFlags; // at 0x0

    //! Sports Pack system data
    RPSportsSystemData* mpSportsSystemData; // at 0x4
    //! Sports Pack player save data list
    RPSportsPlayerData* mpSportsPlayerList; // at 0x8

    //! Party Pack system save data
    RPPartySystemData* mpPartySystemData; // at 0xC
    //! Party Pack player save data list
    RPPartyPlayerData* mpPartyPlayerList; // at 0x10

    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
};

//! @}

#endif
