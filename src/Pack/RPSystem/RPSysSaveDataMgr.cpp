#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/common_message.h>
#include <Pack/sports_message.h>

#include <egg/core.h>

#include <revolution/NAND.h>
#include <revolution/TPL.h>
#include <revolution/VF.h>

/**
 * @brief Pack-specific message file name
 */
#if defined(PACK_SPORTS)
#define PACK_MSG_FILE_NAME "sports_message.bmg"
#elif defined(PACK_PARTY)
#define PACK_MSG_FILE_NAME "party_message.bmg"
#endif

/**
 * @brief Banner icon TPL file name
 */
#define BANNER_ICON_FILE_NAME "banner.tpl"

/**
 * @brief Banner file names
 */
const char* RPSysSaveDataMgr::BANNER_FILE_NAMES[EBannerType_Max] = {
    "banner.bin",     // EBannerType_Real
    "/tmp/banner.bin" // EBannerType_Temp
};

/**
 * @brief Save file name
 */
#if defined(PACK_SPORTS)
static const char* SAVE_FILE_NAME = "RPSports.dat";
#elif defined(PACK_PARTY)
static const char* SAVE_FILE_NAME = "RPParty.dat";
#endif

RP_SINGLETON_IMPL_EX(RPSysSaveDataMgr);

/**
 * @brief Gets the Sports Pack player data at the specified player list
 * index
 *
 * @param idx Player list index
 */
RPSportsPlayerData RPSysSaveDataMgr::getSportsPlayerData(s32 idx) const {
    return *mpSaveData->getSportsPlayerData(idx);
}

/**
 * @brief Sets the Sports Pack player data at the specified player list
 * index
 *
 * @param rPlayerData Player data
 * @param idx Player list index
 */
void RPSysSaveDataMgr::setSportsPlayerData(
    const RPSportsPlayerData& rPlayerData, s32 idx) {

    RPSportsPlayerData clone(rPlayerData);
    mpSaveData->setSportsPlayerData(&clone, idx);
}

/**
 * @brief Gets the Sports Pack system data
 */
RPSportsSystemData RPSysSaveDataMgr::getSportsSystemData() const {
    return *mpSaveData->getSportsSystemData();
}

/**
 * @brief Sets the Sports Pack system data
 *
 * @param rSystemData System data
 */
void RPSysSaveDataMgr::setSportsSystemData(
    const RPSportsSystemData& rSystemData) {

    RPSportsSystemData clone(rSystemData);
    mpSaveData->setSportsSystemData(&clone);
}

/**
 * @brief Gets the Party Pack player data at the specified player list
 * index
 *
 * @param idx Player list index
 */
RPPartyPlayerData RPSysSaveDataMgr::getPartyPlayerData(s32 idx) const {
    return *mpSaveData->getPartyPlayerData(idx);
}

/**
 * @brief Sets the Party Pack player data at the specified player list
 * index
 *
 * @param rPlayerData Player data
 * @param idx Player list index
 */
void RPSysSaveDataMgr::setPartyPlayerData(const RPPartyPlayerData& rPlayerData,
                                          s32 idx) {

    RPPartyPlayerData clone(rPlayerData);
    mpSaveData->setPartyPlayerData(&clone, idx);
}

/**
 * @brief Gets the Party Pack system data
 */
RPPartySystemData RPSysSaveDataMgr::getPartySystemData() const {
    return *mpSaveData->getPartySystemData();
}

/**
 * @brief Sets the Party Pack system data
 *
 * @param rSystemData System data
 */
void RPSysSaveDataMgr::setPartySystemData(
    const RPPartySystemData& rSystemData) {

    RPPartySystemData clone(rSystemData);
    mpSaveData->setPartySystemData(&clone);
}

/**
 * @brief Checks which save data files exist on the NAND
 *
 * @return Success
 */
bool RPSysSaveDataMgr::existPackFileSync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        existSaveFile();
        existBannerFile();

        return true;
    }

    return false;
}

/**
 * @brief Checks which save data files exist on the NAND (asynchronous)
 *
 * @return Success
 */
bool RPSysSaveDataMgr::existPackFileAsync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.setBit(EFlag_NandAccess);
        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        RP_GET_INSTANCE(RPSysSystem)
            ->getNandThread()
            ->request(existPackFileFunc, NULL,
                      RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage());

        return true;
    }

    return false;
}

/**
 * @brief Tests whether the NAND has enough free space to store both the
 * banner and save files (asynchronous)
 *
 * @return Success
 */
bool RPSysSaveDataMgr::existNandMemoryAsync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.setBit(EFlag_NandAccess);
        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        RP_GET_INSTANCE(RPSysSystem)
            ->getNandThread()
            ->request(existNandMemoryFunc, NULL,
                      RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage());

        return true;
    }

    return false;
}

/**
 * @brief Attempts to create both the banner and save files on the NAND
 *
 * @return Success
 */
bool RPSysSaveDataMgr::createPackFileSync() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        mFlags.resetBit(EFlag_SaveFileExist);

        mNandErrorCode =
            NANDCreate(SAVE_FILE_NAME,
                       NAND_PERM_RUSR | NAND_PERM_WUSR | NAND_PERM_RGRP, 0);

        if (mNandErrorCode == NAND_RESULT_OK ||
            mNandErrorCode == NAND_RESULT_EXISTS) {

            mFlags.setBit(EFlag_SaveFileExist);
        } else {
            mFlags.setBit(EFlag_NandError);
        }
    }

    saveSync();
    return true;
}

/**
 * @brief Attempts to create both the banner and save files on the NAND
 * (asynchonous)
 *
 * @return Success
 */
bool RPSysSaveDataMgr::createPackFileAsync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.setBit(EFlag_NandAccess);
        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        RP_GET_INSTANCE(RPSysSystem)
            ->getNandThread()
            ->request(createPackFileFunc, NULL,
                      RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage());

        return true;
    }

    return false;
}

/**
 * @brief Attempts to delete both the banner and save files from the NAND
 *
 * @return Success
 */
bool RPSysSaveDataMgr::deletePackFileSync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        deleteBannerFile();
        deleteSaveFile();

        return true;
    }

    return false;
}

/**
 * @brief Attempts to save both the banner and save files to the NAND
 *
 * @return Success
 */
bool RPSysSaveDataMgr::savePackFileSync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        saveSync();
        saveBannerFile(EBannerType_Real);

        return true;
    }

    return false;
}

/**
 * @brief Attempts to load the save file from the NAND (asynchronous)
 *
 * @return Success
 */
bool RPSysSaveDataMgr::loadAsync() {
    bool enable = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        mFlags.setBit(EFlag_NandAccess);
        mFlags.resetBit(EFlag_NandError);
        mFlags.resetBit(EFlag_13);

        enable = true;
    } else {
        enable = false;
    }

    if (enable) {
        RP_GET_INSTANCE(RPSysSystem)
            ->getNandThread()
            ->request(loadDataFunc, NULL,
                      RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage());

        return true;
    }

    return false;
}

/**
 * @brief Attempts to save both the banner and save files to the NAND
 * (asynchronous)
 *
 * @return Success
 */
bool RPSysSaveDataMgr::saveAsync() {
    if (mFlags.offBit(EFlag_AsyncSave)) {
        bool enable = false;

        if (RP_GET_INSTANCE(RPSysSceneMgr)
                ->getCurrentSceneRP()
                ->isNandAccessEnable()) {

            mFlags.setBit(EFlag_NandAccess);
            mFlags.resetBit(EFlag_NandError);
            mFlags.resetBit(EFlag_13);

            enable = true;
        } else {
            enable = false;
        }

        bool request = false;

        if (enable) {
            RP_GET_INSTANCE(RPSysSystem)
                ->getNandThread()
                ->request(saveDataFunc, NULL,
                          RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage());

            request = true;
        } else {
            request = false;
        }

        if (request) {
            mFlags.setBit(EFlag_AsyncSave);
            mFlags.resetBit(EFlag_ErrorWindow);
        }

        return mFlags.onBit(EFlag_AsyncSave);
    }

    return false;
}

/**
 * @brief Tests whether async operations have completed
 */
bool RPSysSaveDataMgr::isAsyncFinish() const {
    return mFlags.offBit(EFlag_NandAccess) && mFlags.offBit(EFlag_AsyncSave);
}

/**
 * @brief Tests whether NAND operations have completed
 */
bool RPSysSaveDataMgr::isNandAccessFinish() const {
    return mFlags.offBit(EFlag_NandAccess);
}

/**
 * @brief Tests whether both the banner and save files exist on the NAND
 */
bool RPSysSaveDataMgr::isPackFileExist() const {
    return mFlags.onBit(EFlag_BannerFileExist) &&
           mFlags.onBit(EFlag_SaveFileExist);
}

/**
 * @brief Tests whether the NAND has enough free space to store both the
 * banner and save files
 */
bool RPSysSaveDataMgr::isNandMemoryExist() const {
    return mFlags.onBit(EFlag_NandMemoryExist);
}

/**
 * @brief Tests whether the save file is broken (bad magic, checksum, etc.)
 */
bool RPSysSaveDataMgr::isSaveFileBroken() const {
    return mpSaveData->isErrorOccured();
}

/**
 * @brief Tests whether any unrecoverable error has occurred
 * @typo
 */
bool RPSysSaveDataMgr::isErrorOccured() const {
    return !mFlags.onBit(EFlag_DisableSave) &&
           (mFlags.onBit(EFlag_NandError) || mFlags.onBit(EFlag_13));
}

/**
 * @brief Toggles the ability to save both the banner and save files to the
 * NAND
 *
 * @param disable Whether to disable saving
 */
void RPSysSaveDataMgr::setSaveDisable(bool disable) {
    mFlags.changeBit(EFlag_DisableSave, disable);
}

/**
 * @brief Gets the result of the last NAND memory check
 */
u32 RPSysSaveDataMgr::getNandCheckAnswer() const {
    return mNandCheckAnswer;
}

/**
 * @brief Gets the result of the last NAND operation
 */
s32 RPSysSaveDataMgr::getErrorCode() const {
    return mNandErrorCode;
}

/**
 * @brief Gets the number of free NAND blocks needed to store both the
 * banner and save files
 */
u32 RPSysSaveDataMgr::getUserBlockSize() const {
    return (mClusterFileSize / NAND_BLOCK_SIZE) +
           (mClusterFileSize % NAND_BLOCK_SIZE != 0);
}

/**
 * @brief Gets the number of free NAND inodes needed to store both the
 * banner and save files
 */
u32 RPSysSaveDataMgr::getSaveFileNum() const {
    return SAVE_FILE_NUM;
}

/**
 * @brief Marks the current async NAND operations as completed
 */
void RPSysSaveDataMgr::finishNandAccess() {
    mFlags.resetBit(EFlag_NandAccess);
}

/**
 * @brief Updates the save manager state
 *
 * @param display Whether the scene is fully displayed
 */
void RPSysSaveDataMgr::update(bool display) {
    if (mFlags.offBit(EFlag_AsyncSave)) {
        return;
    }
    if (mFlags.onBit(EFlag_NandAccess)) {
        return;
    }

    if (isErrorOccured()) {
        if (mNandErrorCode == NAND_RESULT_BUSY) {
            RPSysSystemWinMgr* pWinMgr = RP_GET_INSTANCE(RPSysSystemWinMgr);

            if (mFlags.offBit(EFlag_ErrorWindow)) {
                // "Unable to save."
                pWinMgr->setSystemWindow(RPSysSystemWinMgr::E_WINDOW_TYPE_ERROR,
                                         MSG_GROUP(CMN_MSG_171_000), NULL, 0);

                pWinMgr->setCursors();
                mFlags.setBit(EFlag_ErrorWindow);

            } else if (pWinMgr->getResult() ==
                       RPSysSystemWinMgr::RESULT_CONTINUE) {

                mFlags.resetBit(EFlag_AsyncSave);
                mFlags.resetBit(EFlag_ErrorWindow);
            }

        } else if (display) {
            checkContinueReject();
        }

    } else {
        mFlags.resetBit(EFlag_AsyncSave);
        mFlags.resetBit(EFlag_ErrorWindow);
    }
}

/**
 * @brief Initializes the banner file binary
 */
void RPSysSaveDataMgr::initBanner() {
    EGG::Heap* pHeap =
        RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP()->getHeap();

    void* pMessageRes =
        RPSysResourceManager::GetMessageResource(PACK_MSG_FILE_NAME);

    RPSysMessage* pMessage = new (pHeap) RPSysMessage(pMessageRes, pHeap);

    const wchar_t* pSaveTitleMsg =
        pMessage->GetMsg(MSG_TUPLE(SP_MSG_29940_000));
    const wchar_t* pSaveSubTitleMsg =
        pMessage->GetMsg(MSG_TUPLE(SP_MSG_29941_000));

    NANDInitBanner(mpBannerFile, 0, pSaveTitleMsg, pSaveSubTitleMsg);

    u8* pTplBuffer =
        static_cast<u8*>(EGG::Heap::alloc(mBannerFileSize, 32, pHeap));

    void* pTplFile = EGG::DvdRipper::loadToMainRAM(
        BANNER_ICON_FILE_NAME, pTplBuffer, pHeap,
        EGG::DvdRipper::ALLOC_DIR_HEAD, 0, NULL, NULL);

    TPLPalette* pPalette = static_cast<TPLPalette*>(pTplFile);
    TPLBind(pPalette);

    TPLDescriptor* pBannerTexture = TPLGet(pPalette, ETplIndex_BannerTexture);

    memcpy(mpBannerFile->bannerTexture, pBannerTexture->textureHeader->data,
           sizeof(mpBannerFile->bannerTexture));

    for (int i = 0; i < BANNER_ICON_FRAME_NUM; i++) {
        TPLDescriptor* pIconTexture =
            TPLGet(pPalette, ETplIndex_IconTexture + i);

        if (pIconTexture != NULL) {
            memcpy(mpBannerFile->iconTexture[i],
                   pIconTexture->textureHeader->data, NAND_BANNER_ICON_SIZE);

            NAND_BANNER_SET_ICON_SPEED(mpBannerFile, i, 2);
        }
    }

    // Frame with a speed of zero marks the end of the animation
    NAND_BANNER_SET_ICON_SPEED(mpBannerFile, BANNER_ICON_FRAME_NUM + 1, 0);
}

/**
 * @brief Prompts the user to continue without saving
 */
void RPSysSaveDataMgr::checkContinueReject() {
    RPSysSystemWinMgr* pWinMgr = RP_GET_INSTANCE(RPSysSystemWinMgr);

    if (mFlags.offBit(EFlag_ErrorWindow)) {
        // "The game could not be saved. Continue without saving?"
        pWinMgr->setSystemWindow(RPSysSystemWinMgr::E_WINDOW_TYPE_ERROR,
                                 MSG_GROUP(CMN_MSG_052_000), NULL, 0);

        pWinMgr->setDefaultCursor(RPSysSystemWinMgr::E_BUTTON_YES);
        pWinMgr->setCursors();

        mFlags.setBit(EFlag_ErrorWindow);

    } else if (pWinMgr->getResult() == RPSysSystemWinMgr::RESULT_YES) {
        mFlags.setBit(EFlag_DisableSave);

        mFlags.resetBit(EFlag_AsyncSave);
        mFlags.resetBit(EFlag_ErrorWindow);

    } else if (pWinMgr->getResult() == RPSysSystemWinMgr::RESULT_NO) {
        RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(false);

        mFlags.resetBit(EFlag_AsyncSave);
        mFlags.resetBit(EFlag_ErrorWindow);
    }
}

/**
 * @brief Checks if the NAND has enough free space to store both the banner
 * and save files
 */
void RPSysSaveDataMgr::existNandMemorySync() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        mFlags.resetBit(EFlag_NandMemoryExist);

        // TODO(kiwi) Why is the block calculation different?
        mNandErrorCode =
            NANDCheck(getUserBlockSize(), getSaveFileNum(), &mNandCheckAnswer);

        if (mNandErrorCode == NAND_RESULT_OK) {
            if (mNandCheckAnswer == 0) {
                mFlags.setBit(EFlag_NandMemoryExist);
            }
        } else {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Checks whether the banner file exists on the NAND
 */
void RPSysSaveDataMgr::existBannerFile() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        mFlags.resetBit(EFlag_SaveFileExist);

        u8 type;
        mNandErrorCode = NANDGetType(SAVE_FILE_NAME, &type);

        if (mNandErrorCode == NAND_RESULT_OK) {
            mFlags.setBit(EFlag_SaveFileExist);
        } else if (mNandErrorCode != NAND_RESULT_NOEXISTS) {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Creates the banner file on the NAND
 * @details For safety purposes, the banner file is first created in the
 * temporary directory, before being moved out.
 */
void RPSysSaveDataMgr::createBannerFile() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        mFlags.resetBit(EFlag_BannerFileExist);

        mNandErrorCode =
            NANDCreate(BANNER_FILE_NAMES[EBannerType_Temp],
                       NAND_PERM_RUSR | NAND_PERM_WUSR | NAND_PERM_RGRP, 0);

        if (mNandErrorCode != NAND_RESULT_OK &&
            mNandErrorCode != NAND_RESULT_EXISTS) {

            mFlags.setBit(EFlag_NandError);
            return;
        }

        saveBannerFile(EBannerType_Temp);

        if (mFlags.onBit(EFlag_NandError)) {
            return;
        }
        if (mFlags.onBit(EFlag_13)) {
            return;
        }

        char homeDir[NAND_MAX_PATH];
        mNandErrorCode = NANDGetHomeDir(homeDir);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDMove(BANNER_FILE_NAMES[EBannerType_Temp], homeDir);

        if (mNandErrorCode == NAND_RESULT_OK ||
            mNandErrorCode == NAND_RESULT_EXISTS) {

            mFlags.setBit(EFlag_BannerFileExist);
        } else {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Deletes the banner file from the NAND
 * @details This function only deletes the banner file in the home directory
 */
void RPSysSaveDataMgr::deleteBannerFile() {
    mNandErrorCode = NANDDelete(BANNER_FILE_NAMES[EBannerType_Real]);

    if (mNandErrorCode == NAND_RESULT_OK ||
        mNandErrorCode == NAND_RESULT_NOEXISTS) {

        mFlags.resetBit(EFlag_BannerFileExist);
    } else {
        mFlags.setBit(EFlag_NandError);
    }
}

/**
 * @brief Saves both the banner and save files to the NAND
 */
void RPSysSaveDataMgr::saveSync() {
    if (mFlags.offBit(EFlag_DisableSave) && mFlags.offBit(EFlag_NandError) &&
        mFlags.offBit(EFlag_13)) {

        {
            EGG::RamStream strm(mpSaveFile, mSaveFileSize);
            mpSaveData->write(strm, mpSaveFile);
        }

        NANDFileInfo info;
        mNandErrorCode = NANDOpen(SAVE_FILE_NAME, &info, NAND_ACCESS_WRITE);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDWrite(&info, mpSaveFile, mSaveFileSize);

        if (mNandErrorCode != mSaveFileSize) {
            NANDClose(&info);
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Loads the save file from the NAND
 */
void RPSysSaveDataMgr::loadSync() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        NANDFileInfo info;
        mNandErrorCode = NANDOpen(SAVE_FILE_NAME, &info, NAND_ACCESS_READ);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDRead(&info, mpSaveFile, mSaveFileSize);

        if (mNandErrorCode != mSaveFileSize) {
            NANDClose(&info);
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
            // No early return?
        }

        {
            EGG::RamStream strm(mpSaveFile, mSaveFileSize);
            mpSaveData->read(strm, mpSaveFile);
        }
    }
}

/**
 * @brief Saves the banner file to the NAND
 *
 * @param type Which type of banner file to save
 */
void RPSysSaveDataMgr::saveBannerFile(EBannerType type) {
    if (mFlags.offBit(EFlag_DisableSave) && mFlags.offBit(EFlag_NandError) &&
        mFlags.offBit(EFlag_13)) {

        NANDFileInfo info;
        mNandErrorCode =
            NANDOpen(BANNER_FILE_NAMES[type], &info, NAND_ACCESS_WRITE);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDWrite(&info, mpBannerFile, mBannerFileSize);

        if (mNandErrorCode != mBannerFileSize) {
            NANDClose(&info);
            mFlags.setBit(EFlag_NandError);
            return;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Checks whether the save file exists on the NAND
 */
void RPSysSaveDataMgr::existSaveFile() {
    if (mFlags.offBit(EFlag_NandError) && mFlags.offBit(EFlag_13)) {
        mFlags.resetBit(EFlag_BannerFileExist);

        u8 type;
        mNandErrorCode =
            NANDGetType(BANNER_FILE_NAMES[EBannerType_Real], &type);

        if (mNandErrorCode == NAND_RESULT_OK) {
            mFlags.setBit(EFlag_BannerFileExist);
        } else if (mNandErrorCode != NAND_RESULT_NOEXISTS) {
            mFlags.setBit(EFlag_NandError);
        }
    }
}

/**
 * @brief Deletes the save file from the NAND
 */
void RPSysSaveDataMgr::deleteSaveFile() {
    mNandErrorCode = NANDDelete(SAVE_FILE_NAME);

    if (mNandErrorCode == NAND_RESULT_OK ||
        mNandErrorCode == NAND_RESULT_NOEXISTS) {

        mFlags.resetBit(EFlag_SaveFileExist);
    } else {
        mFlags.setBit(EFlag_NandError);
    }
}

/**
 * @brief Checks which save data files exist on the NAND
 *
 * @param pArg Thread function argument
 */
void RPSysSaveDataMgr::existPackFileFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->existSaveFile();
    RP_GET_INSTANCE(RPSysSaveDataMgr)->existBannerFile();
}

/**
 * @brief Checks if the NAND has enough free space to store both the banner
 * and save files
 *
 * @param pArg Thread function argument
 */
void RPSysSaveDataMgr::existNandMemoryFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->existNandMemorySync();
}

/**
 * @brief Creates both the banner and save files on the NAND
 *
 * @param pArg Thread function argument
 */
void RPSysSaveDataMgr::createPackFileFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->createPackFileSync();
    RP_GET_INSTANCE(RPSysSaveDataMgr)->createBannerFile();
}

/**
 * @brief Loads the save file from the NAND
 *
 * @param pArg Thread function argument
 */
void RPSysSaveDataMgr::loadDataFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->loadSync();
}

/**
 * @brief Saves both the banner and save files to the NAND
 *
 * @param pArg Thread function argument
 */
void RPSysSaveDataMgr::saveDataFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->saveSync();
    RP_GET_INSTANCE(RPSysSaveDataMgr)->saveBannerFile(EBannerType_Real);
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysSaveDataMgr::RPSysSaveDataMgr(EGG::Heap* pHeap)
    : IRPSysHostIOSocket("Save File"), mpParentHeap(pHeap) {

    if (VFIsAvailable() == VF_OK) {
        void* pWorkBuffer = EGG::Heap::alloc(VF_WORK_SIZE, 4, pHeap);
        VFInitEx(pWorkBuffer, VF_WORK_SIZE);
    }

    mFlags.makeAllZero();
    mNandErrorCode = NAND_RESULT_OK;
    unk10 = 0;
    mNandCheckAnswer = 0;

    mpSaveData = new (pHeap) RPSysSaveData();

    mSaveFileSize = RPSysSaveData::getSaveFileSize();
    mBannerFileSize = SAVE_BANNER_SIZE;

    mClusterFileSize = ((mSaveFileSize / NAND_CLUSTER_SIZE) +
                        (mSaveFileSize % NAND_CLUSTER_SIZE != 0) +
                        (mBannerFileSize / NAND_CLUSTER_SIZE) +
                        (mBannerFileSize % NAND_CLUSTER_SIZE != 0)) //
                       * NAND_CLUSTER_SIZE;

    mpBannerFile = static_cast<NANDBanner*>(
        EGG::Heap::alloc(sizeof(NANDBanner), 32, pHeap));

    mpSaveFile = static_cast<u8*>(EGG::Heap::alloc(mSaveFileSize, 32, pHeap));
}

/**
 * @brief Destructor
 */
RPSysSaveDataMgr::~RPSysSaveDataMgr() {}
