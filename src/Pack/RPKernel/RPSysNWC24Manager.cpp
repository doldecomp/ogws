#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

#include <revolution/NWC24.h>

#include <cwchar>

/**
 * @brief Whether the last NWC24 operation was successful
 */
BOOL RPSysNWC24Manager::sSuccess = true;

/**
 * @brief Suspends the WiiConnect24 scheduler so the library can be opened
 */
void RPSysNWC24Manager::initialize() {
    s32 err = NWC24SuspendScheduler();
    if (err >= NWC24_OK) {
        return;
    }

    switch (err) {
    case NWC24_ERR_FATAL: {
        sSuccess = false;
        break;
    }

    case NWC24_ERR_INTERNAL_IPC:
    case NWC24_ERR_MUTEX:
    case NWC24_ERR_INPROGRESS: {
        break;
    }

    default: {
        break;
    }
    }
}

/**
 * @brief Constructor
 *
 * @param pHeap Heap to use for allocations
 */
RPSysNWC24Manager::RPSysNWC24Manager(EGG::Heap* pHeap) {
    mpNwc24Work = new (pHeap, 32) u8[sizeof(NWC24Work)];
    mpMsgWork = new (pHeap) wchar_t[MSG_BUFFER_SIZE];
}

/**
 * @brief Destructor
 */
RPSysNWC24Manager::~RPSysNWC24Manager() {}

/**
 * @brief Attempts to commit a message to the Wii Message Board
 *
 * @param pWork Library work buffer
 * @param pAltName Mail letter alt name
 * @param pMsg Mail letter message (can be a format string)
 * @param date Mail letter send date
 * @param pAvatar Mii avatar to include
 * @param argc Number of message format arguments
 * @param argv Message format arguments
 * @return Success
 */
bool RPSysNWC24Manager::commitMail(const wchar_t* pAltName, const wchar_t* pMsg,
                                   RPTime16 date, const RPSysAvatar* pAvatar,
                                   int argc, va_list argv) {
    if (!sSuccess) {
        return false;
    }

    if (RP_GET_INSTANCE(RPSysSceneMgr)->isShutDownReserved()) {
        return false;
    }

    RP_GET_INSTANCE(RPSysTagProcessor)
        ->PreProcessEx(pMsg, mpMsgWork, MSG_BUFFER_SIZE, NULL, argc, argv);

    if (!openLib()) {
        closeLib();
        return false;
    }

    NWC24MsgObj msg;
    if (NWC24InitMsgObj(&msg, NWC24_MSGTYPE_RVL_MENU) != NWC24_OK) {
        closeLib();
        return false;
    }

    u64 uid;
    if (NWC24GetMyUserId(&uid) != NWC24_OK) {
        closeLib();
        return false;
    }

    if (NWC24SetMsgAltName(&msg, pAltName, std::wcslen(pAltName) + 1) !=
        NWC24_OK) {

        closeLib();
        return false;
    }

    if (NWC24SetMsgToId(&msg, uid) != NWC24_OK) {
        closeLib();
        return false;
    }

    if (NWC24SetMsgText(&msg,                                     //
                        reinterpret_cast<const char*>(mpMsgWork), //
                        std::wcslen(mpMsgWork) * sizeof(wchar_t), //
                        NWC24_UTF_16BE, NWC24_ENC_BASE64) != NWC24_OK) {
        closeLib();
        return false;
    }

    u32 year = 0;
    u32 month = 0;
    u32 day = 0;
    RP_GET_INSTANCE(RPSysSystem)->getCalendarTime(&date, year, month, day);

    if (NWC24SetMsgMBNoReply(&msg, TRUE) != NWC24_OK) {
        closeLib();
        return false;
    }

    switch (NWC24SetMsgMBRegDate(&msg, year, month, day)) {
    // This will always happen starting in 2035!
    case NWC24_ERR_INVALID_VALUE: {
        closeLib();
        return false;
    }

    case NWC24_OK: {
        break;
    }

    default: {
        closeLib();
        return false;
    }
    }

    bool attach = false;
    u16 index = 0;

    if (pAvatar != NULL) {
        RPSysKokeshiLocation location = pAvatar->GetGenInfo().GetLocation();

        // RFL only supports attaching official DB Miis
        if (location.GetDataSource() == RFLDataSource_Official) {
            attach = true;
            index = location.GetIndex();
        }
    }

    s32 commitErr = NWC24_OK;

    if (attach) {
        switch (RFLCommitNWC24Msg(&msg, index)) {
        case RFLErrcode_NotAvailable:
        case RFLErrcode_Broken: {
            closeLib();
            return false;
        }

        case RFLErrcode_NWC24Fail: {
            commitErr = RFLGetLastReason();
            break;
        }

        case RFLErrcode_Success: {
            break;
        }

        default: {
            break;
        }
        }
    } else {
        commitErr = NWC24CommitMsg(&msg);
    }

    switch (commitErr) {
    case NWC24_ERR_FULL: {
        closeLib();
        return false;
    }

    case NWC24_ERR_NAND_CORRUPT:
    case NWC24_ERR_FILE_OTHER:
    case NWC24_ERR_FILE_NOEXISTS:
    case NWC24_ERR_FILE_WRITE:
    case NWC24_ERR_FILE_READ:
    case NWC24_ERR_FILE_CLOSE:
    case NWC24_ERR_FILE_OPEN: {
        NWC24CloseLib();
        sSuccess = false;
        return false;
    }

    default: {
        closeLib();
        return false;
    }

    case NWC24_OK: {
        closeLib();
        return true;
    }
    }
}

/**
 * @brief Attempts to open the WiiConnect24 library for use
 *
 * @return Success
 */
bool RPSysNWC24Manager::openLib() {
    NWC24Work* pNwc24Work = reinterpret_cast<NWC24Work*>(mpNwc24Work);

    switch (NWC24OpenLib(pNwc24Work)) {
    case NWC24_ERR_LIB_OPENED:
    case NWC24_OK: {
        return true;
    }

    case NWC24_ERR_INPROGRESS:
    case NWC24_ERR_BUSY:
    case NWC24_ERR_MUTEX: {
        return false;
    }

    case NWC24_ERR_NAND_CORRUPT:
    case NWC24_ERR_FILE_OTHER:
    case NWC24_ERR_FILE_NOEXISTS:
    case NWC24_ERR_FILE_WRITE:
    case NWC24_ERR_FILE_READ:
    case NWC24_ERR_FILE_CLOSE:
    case NWC24_ERR_FILE_OPEN:
    case NWC24_ERR_BROKEN:
    case NWC24_ERR_FATAL: {
        sSuccess = false;
        return false;
    }

    default: {
        return false;
    }
    }
}

/**
 * @brief Closes the WiiConnect24 library
 */
void RPSysNWC24Manager::closeLib() {
    switch (NWC24CloseLib()) {
    case NWC24_ERR_FILE_OTHER:
    case NWC24_ERR_FILE_NOEXISTS:
    case NWC24_ERR_FILE_WRITE:
    case NWC24_ERR_FILE_READ:
    case NWC24_ERR_FILE_CLOSE:
    case NWC24_ERR_FILE_OPEN: {
        sSuccess = false;
        break;
    }

    case NWC24_ERR_LIB_NOT_OPENED:
    case NWC24_OK:
    default: {
        break;
    }
    }
}
