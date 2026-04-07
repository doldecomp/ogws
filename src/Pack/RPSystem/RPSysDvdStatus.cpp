#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem.h>

#include <revolution/DVD.h>
#include <revolution/VI.h>

#include <cstring>

RP_SINGLETON_IMPL_EX(RPSysDvdStatus);

/**
 * @brief Game disc name
 */
#if defined(PACK_SPORTS)
const char* RPSysDvdStatus::GAME_DISK_NAME = "Wii Sports";
#elif defined(PACK_PARTY)
const char* RPSysDvdStatus::GAME_DISK_NAME = "Wii Play";
#endif

/**
 * @brief English error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_ENG[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "Please insert the ",

    "\nGame Disc.",

    "The Game Disc could not be read.\n"
    "Please read the Wii Operations\n"
    "Manual for more information.",

    "",
};
// clang-format on

/**
 * @brief French error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_FRA[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "Veuillez ins\xE9""rer le disque de\n",

    ".",

    "La lecture du disque a \xE9""chou\xE9.\n"
    "Veuillez vous r\xE9""f\xE9rer\n"
    "au mode d'emploi Wii\n"
    "pour de plus amples informations.",

    "",
};
// clang-format on

/**
 * @brief German error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_GER[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "Bitte schiebe die\n",

    "-Disc ein.",

    "Diese Disc kann nicht gelesen werden.\n"
    "Bitte lies die Wii-Bedienungsanleitung,\n"
    "um weitere Informationen zu erhalten.",

    "",
};
// clang-format on

/**
 * @brief Italian error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_ITA[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "Inserisci il disco di ",

    ".",

    "Impossibile leggere il disco di gioco.\n"
    "Per maggiori informazioni consulta\n"
    "il manuale di istruzioni della console Wii.",

    "",
};
// clang-format on

/**
 * @brief Spanish error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_SPA[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "Inserta el disco de ",

    ".",

    "No se puede leer el disco.\n"
    "Consulta el manual de\n"
    "instrucciones de la consola Wii\n"
    "para obtener m\xE1s informaci\xF3n.",

    "",
};
// clang-format on

/**
 * @brief Japanese error message language
 */
// clang-format off
const char* RPSysDvdStatus::LANGUAGE_JPN[ERROR_MESSAGE_STRING_NUM]
                                        [ERROR_MESSAGE_KIND_NUM] = {
    "",

    " のディスクを\nセットしてください。",

    "ディスクを読めませんでした。\n"
    "詳しくは、本体の取扱説明書を\n"
    "お読みください。",

    "",
};
// clang-format on

/**
 * @brief Tests whether a disc drive error has occurred
 * @typo
 */
bool RPSysDvdStatus::isErrorOccured() const {
    return mErrorStatus > EErrorStatus_Busy;
}

/**
 * @brief Updates the status of the disc drive
 * @return Whether the disc drive status is OK
 */
bool RPSysDvdStatus::update() {
    s32 status = DVDGetDriveStatus();

    if (status == DVD_STATE_FATAL) {
        mErrorStatus = EErrorStatus_Fatal;
    } else if (status == DVD_STATE_DISK_ERROR) {
        mErrorStatus = EErrorStatus_DiskError;
    } else if (status == DVD_STATE_NO_DISK) {
        mErrorStatus = EErrorStatus_NoOrWrongDisk;
    } else if (status == DVD_STATE_WRONG_DISK_ID) {
        mErrorStatus = EErrorStatus_NoOrWrongDisk;
    } else if (status == DVD_STATE_BUSY) {
        mErrorStatus = EErrorStatus_Busy;
    } else {
        mErrorStatus = EErrorStatus_Success;
    }

    if (isErrorOccured()) {
        RPSysCoreController::stopMotorAll();
        RP_GET_INSTANCE(RPSysHomeMenuMgr)->update();

        if (RP_GET_INSTANCE(RPSysSceneMgr)->isDvdErrorApplicationEnd()) {
            RP_GET_INSTANCE(RPSysSystem)->systemShutDown();
        }

        return false;
    }

    return true;
}

/**
 * @brief Displays the disc drive error message
 */
void RPSysDvdStatus::draw() {
    if (!isErrorOccured()) {
        return;
    }

    VISetBlack(FALSE);
    mpErrorFader->draw();

    if (mErrorStatus < ERROR_MESSAGE_KIND_NUM) {
        RP_GET_INSTANCE(RPSysTextWriter)->SetupGX();

        // Always pass the Z test (draw over everything)
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);

        RP_GET_INSTANCE(RPSysTextWriter)
            ->SetDrawFlag(RPSysTextWriter::DRAWFLAG_ALIGN_H_CENTER |
                          RPSysTextWriter::DRAWFLAG_ALIGN_V_CENTER);

        RP_GET_INSTANCE(RPSysTextWriter)->SetScale(1.0f, 1.0f);
        RP_GET_INSTANCE(RPSysTextWriter)->SetTextColor(nw4r::ut::Color::WHITE);
        RP_GET_INSTANCE(RPSysTextWriter)->SetCursor(320.0f, 228.0f);

        const char** pLanguage = NULL;

        switch (RP_GET_INSTANCE(RPSysProjectLocal)->getLocale()) {
        case RPSysProjectLocal::EArea_England: {
            pLanguage = LANGUAGE_ENG[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_France: {
            pLanguage = LANGUAGE_FRA[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_Germany: {
            pLanguage = LANGUAGE_GER[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_Italy: {
            pLanguage = LANGUAGE_ITA[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_Spain: {
            pLanguage = LANGUAGE_SPA[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_Netherlands: {
            pLanguage = LANGUAGE_ENG[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_Japan: {
            pLanguage = LANGUAGE_JPN[mErrorStatus];
            break;
        }

        case RPSysProjectLocal::EArea_USA: {
            pLanguage = LANGUAGE_ENG[mErrorStatus];
            break;
        }

        default: {
            break;
        }
        }

        std::strcpy(mpErrorMessage, pLanguage[0]);

        // @bug Same comparison twice
        if (mErrorStatus == EErrorStatus_NoOrWrongDisk ||
            mErrorStatus == EErrorStatus_NoOrWrongDisk) {

            std::strcat(mpErrorMessage, GAME_DISK_NAME);
            std::strcat(mpErrorMessage, pLanguage[1]);
        }

        RP_GET_INSTANCE(RPSysTextWriter)
            ->Print(mpErrorMessage, std::strlen(mpErrorMessage));
    }
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysDvdStatus::RPSysDvdStatus(EGG::Heap* pHeap)
    : mpParentHeap(pHeap), mErrorStatus(EErrorStatus_Success) {

    mpErrorMessage = new (pHeap) char[MESSAGE_BUFFER_SIZE];

    mpErrorFader = new (pHeap) EGG::ColorFader(0.0f, 0.0f, 640.0f, 456.0f);
    mpErrorFader->setStatus(EGG::ColorFader::STATUS_PREPARE_IN);
}

/**
 * @brief Destructor
 */
RPSysDvdStatus::~RPSysDvdStatus() {}
