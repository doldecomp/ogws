#ifndef RP_SYSTEM_SAVE_DATA_MGR_H
#define RP_SYSTEM_SAVE_DATA_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPPartyPlayerData.h>
#include <Pack/RPSystem/RPPartySystemData.h>
#include <Pack/RPSystem/RPSportsPlayerData.h>
#include <Pack/RPSystem/RPSportsSystemData.h>

#include <egg/core.h>

#include <revolution/OS.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysSaveData;

/**
 * @brief Save data manager
 */
class RPSysSaveDataMgr : public IRPSysHostIOSocket {
    RP_SINGLETON_DECL_EX(RPSysSaveDataMgr);

public:
    /**
     * @brief Banner file type
     */
    enum EBannerType {
        EBannerType_Real, //!< Banner file in the home directory
        EBannerType_Temp, //!< Banner file in the temporary directory

        EBannerType_Max
    };

public:
    /**
     * @name Access save data
     */
    /**@{*/
    /**
     * @brief Gets the Sports Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPSportsPlayerData getSportsPlayerData(s32 idx) const;
    /**
     * @brief Sets the Sports Pack player data at the specified player list
     * index
     *
     * @param rPlayerData Player data
     * @param idx Player list index
     */
    void setSportsPlayerData(const RPSportsPlayerData& rPlayerData, s32 idx);

    /**
     * @brief Gets the Sports Pack system data
     */
    RPSportsSystemData getSportsSystemData() const;
    /**
     * @brief Sets the Sports Pack system data
     *
     * @param rSystemData System data
     */
    void setSportsSystemData(const RPSportsSystemData& rSystemData);

    /**
     * @brief Gets the Party Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPPartyPlayerData getPartyPlayerData(s32 idx) const;
    /**
     * @brief Sets the Party Pack player data at the specified player list
     * index
     *
     * @param rPlayerData Player data
     * @param idx Player list index
     */
    void setPartyPlayerData(const RPPartyPlayerData& rPlayerData, s32 idx);

    /**
     * @brief Gets the Party Pack system data
     */
    RPPartySystemData getPartySystemData() const;
    /**
     * @brief Sets the Party Pack system data
     *
     * @param rSystemData System data
     */
    void setPartySystemData(const RPPartySystemData& rSystemData);
    /**@}*/

    /**
     * @name Prepare save data
     */
    /**@{*/
    /**
     * @brief Checks which save data files exist on the NAND
     *
     * @return Success
     */
    bool existPackFileSync();
    /**
     * @brief Checks which save data files exist on the NAND (asynchronous)
     *
     * @return Success
     */
    bool existPackFileAsync();
    /**
     * @brief Tests whether the NAND has enough free space to store both the
     * banner and save files (asynchronous)
     *
     * @return Success
     */
    bool existNandMemoryAsync();

    /**
     * @brief Attempts to create both the banner and save files on the NAND
     *
     * @return Success
     */
    bool createPackFileSync();
    /**
     * @brief Attempts to create both the banner and save files on the NAND
     * (asynchonous)
     *
     * @return Success
     */
    bool createPackFileAsync();
    /**
     * @brief Attempts to delete both the banner and save files from the NAND
     *
     * @return Success
     */
    bool deletePackFileSync();
    /**
     * @brief Attempts to save both the banner and save files to the NAND
     *
     * @return Success
     */
    bool savePackFileSync();

    /**
     * @brief Attempts to load the save file from the NAND (asynchronous)
     *
     * @return Success
     */
    bool loadAsync();
    /**
     * @brief Attempts to save both the banner and save files to the NAND
     * (asynchronous)
     *
     * @return Success
     */
    bool saveAsync();

    /**
     * @brief Loads the save file from the NAND
     */
    void loadSync();
    /**
     * @brief Saves both the banner and save files to the NAND
     */
    void saveSync();

    /**
     * @name State checking
     */
    /**@{*/
    /**
     * @brief Tests whether async operations have completed
     */
    bool isAsyncFinish() const;
    /**
     * @brief Tests whether NAND operations have completed
     */
    bool isNandAccessFinish() const;

    /**
     * @brief Tests whether both the banner and save files exist on the NAND
     */
    bool isPackFileExist() const;
    /**
     * @brief Tests whether the NAND has enough free space to store both the
     * banner and save files
     */
    bool isNandMemoryExist() const;

    /**
     * @brief Tests whether the save file is broken (bad magic, checksum, etc.)
     */
    bool isSaveFileBroken() const;
    /**
     * @brief Tests whether any unrecoverable error has occurred
     * @typo
     */
    bool isErrorOccured() const;
    /**@}*/

    /**
     * @brief Toggles the ability to save both the banner and save files to the
     * NAND
     *
     * @param disable Whether to disable saving
     */
    void setSaveDisable(bool disable);

    /**
     * @name NAND
     */
    /**@{*/
    /**
     * @brief Gets the result of the last NAND memory check
     */
    u32 getNandCheckAnswer() const;
    /**
     * @brief Gets the result of the last NAND operation
     */
    s32 getErrorCode() const;

    /**
     * @brief Gets the number of free NAND blocks needed to store both the
     * banner and save files
     */
    u32 getUserBlockSize() const;
    /**
     * @brief Gets the number of free NAND inodes needed to store both the
     * banner and save files
     */
    u32 getSaveFileNum() const;

    /**
     * @brief Marks the current async NAND operations as completed
     */
    void finishNandAccess();
    /**@}*/

    /**
     * @brief Updates the save manager state
     *
     * @param display Whether the scene is fully displayed
     */
    void update(bool display);

    /**
     * @brief Initializes the banner file binary
     */
    void initBanner();

private:
    /**
     * @brief Bitflag indices
     */
    enum {
        EFlag_NandMemoryExist, //!< Enough NAND memory exists for all files
        EFlag_BannerFileExist, //!< The banner file exists on the NAND
        EFlag_SaveFileExist,   //!< The save file exists on the NAND
        EFlag_3,
        EFlag_DisableSave, //!< Saving is disabled
        EFlag_5,
        EFlag_6,
        EFlag_7,
        EFlag_NandAccess,  //!< NAND operation is happening on another thread
        EFlag_AsyncSave,   //!< Save file is being written on another thread
        EFlag_ErrorWindow, //!< System window error was displayed
        EFlag_11,
        EFlag_NandError, //!< Unrecoverable NAND error
        EFlag_13,
        EFlag_14,
    };

    /**
     * @brief banner.tpl file indices
     */
    enum ETplIndex {
        ETplIndex_BannerTexture, //!< Banner texture
        ETplIndex_IconTexture,   //!< Icon texture
    };

    //! VF work memory size
    static const u32 VF_WORK_SIZE = OS_MEM_KB_TO_B(16);

    //! NAND save file banner size
    static const u32 SAVE_BANNER_SIZE = NAND_BANNER_SIZE(1);

    //! Number of files written when saving
#if defined(PACK_SPORTS)
    static const u32 SAVE_FILE_NUM = 2; // RPSports.dat, banner.bin
#elif defined(PACK_PARTY)
    static const u32 SAVE_FILE_NUM = 2; // RPParty.dat, banner.bin
#endif

    //! Number of icon texture frames in the save banner
    static const u32 BANNER_ICON_FRAME_NUM = 1;

private:
    /**
     * @brief Prompts the user to continue without saving
     */
    void checkContinueReject();

    /**
     * @brief Checks if the NAND has enough free space to store both the banner
     * and save files
     */
    void existNandMemorySync() DECOMP_DONT_INLINE;

    /**
     * @brief Checks whether the banner file exists on the NAND
     */
    void existBannerFile();
    /**
     * @brief Creates the banner file on the NAND
     * @details For safety purposes, the banner file is first created in the
     * temporary directory, before being moved out.
     */
    void createBannerFile();
    /**
     * @brief Deletes the banner file from the NAND
     * @details This function only deletes the banner file in the home directory
     */
    void deleteBannerFile();
    /**
     * @brief Saves the banner file to the NAND
     *
     * @param type Which type of banner file to save
     */
    void saveBannerFile(EBannerType type);

    /**
     * @brief Checks whether the save file exists on the NAND
     */
    void existSaveFile();
    /**
     * @brief Deletes the save file from the NAND
     */
    void deleteSaveFile();

    /**
     * @name Thread functions
     */
    /**@{*/
    /**
     * @brief Checks which save data files exist on the NAND
     *
     * @param pArg Thread function argument
     */
    static void existPackFileFunc(void* pArg);
    /**
     * @brief Checks if the NAND has enough free space to store both the banner
     * and save files
     *
     * @param pArg Thread function argument
     */
    static void existNandMemoryFunc(void* pArg);

    /**
     * @brief Creates both the banner and save files on the NAND
     *
     * @param pArg Thread function argument
     */
    static void createPackFileFunc(void* pArg);

    /**
     * @brief Loads the save file from the NAND
     *
     * @param pArg Thread function argument
     */
    static void loadDataFunc(void* pArg);
    /**
     * @brief Saves both the banner and save files to the NAND
     *
     * @param pArg Thread function argument
     */
    static void saveDataFunc(void* pArg);
    /**@}*/

private:
    //! Banner file names
    static const char* BANNER_FILE_NAMES[EBannerType_Max];
    //! Save file name
    static const char* SAVE_FILE_NAME;

    //! Status flags
    EGG::TBitFlag<u32> mFlags; // at 0x8

    //! Last NAND operation result
    s32 mNandErrorCode; // at 0xC
    u32 unk10;
    //! NANDCheck result
    u32 mNandCheckAnswer; // at 0x14

    //! Save file (`RPSports.dat`) size
    u32 mSaveFileSize; // at 0x18
    //! Save banner (`banner.bin`) size
    u32 mBannerFileSize; // at 0x1C
    //! Size of both the save file and banner together
    u32 mClusterFileSize; // at 0x20

    //! Banner file binary
    NANDBanner* mpBannerFile; // at 0x24
    //! Save file binary
    u8* mpSaveFile; // at 0x28

    //! Game save data
    RPSysSaveData* mpSaveData; // at 0x2C
};

//! @}

#endif
