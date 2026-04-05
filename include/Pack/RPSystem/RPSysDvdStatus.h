#ifndef RP_SYSTEM_DVD_STATUS_H
#define RP_SYSTEM_DVD_STATUS_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysProjectLocal.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Disc drive status
 */
class RPSysDvdStatus {
    RP_SINGLETON_DECL_EX(RPSysDvdStatus);

public:
    /**
     * @brief Updates the status of the disc drive
     * @return Whether the disc drive status is OK
     */
    bool update();

    /**
     * @brief Displays the disc drive error message
     */
    void draw();

private:
    /**
     * @brief Disc drive error type
     */
    enum EErrorStatus {
        EErrorStatus_Success = -2,
        EErrorStatus_Busy,          //!< Drive is busy
        EErrorStatus_NoOrWrongDisk, //!< Disk is ejected or is the wrong game
        EErrorStatus_DiskError,     //!< Cannot read from the disk
        EErrorStatus_Fatal          //!< Fatal error
    };

    //! Number of error messages per language
    static const int ERROR_MESSAGE_KIND_NUM =
        (EErrorStatus_DiskError - EErrorStatus_NoOrWrongDisk) + 1;

    //! Number of strings per error message
    static const int ERROR_MESSAGE_STRING_NUM = 2;

    //! Size of the error message buffer
    static const int MESSAGE_BUFFER_SIZE = 256;

private:
    /**
     * @brief Tests whether a disc drive error has occurred
     * @typo
     */
    bool isErrorOccured() const;

private:
    //! Game disc name
    static const char* GAME_DISK_NAME;

    //! English error message language
    static const char* LANGUAGE_ENG[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! French error message language
    static const char* LANGUAGE_FRA[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! German error message language
    static const char* LANGUAGE_GER[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! Italian error message language
    static const char* LANGUAGE_ITA[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! Spanish error message language
    static const char* LANGUAGE_SPA[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! Japanese error message language
    static const char* LANGUAGE_JPN[ERROR_MESSAGE_STRING_NUM]
                                   [ERROR_MESSAGE_KIND_NUM];

    //! DVD error status
    EErrorStatus mErrorStatus; // at 0x8
    //! Error message text
    char* mpErrorMessage; // at 0xC
    //! Fader for the background
    EGG::ColorFader* mpErrorFader; // at 0x10
};

//! @}

#endif
