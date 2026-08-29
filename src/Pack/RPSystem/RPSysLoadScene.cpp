#include <Pack/RPAudio.h>
#include <Pack/RPSystem.h>

#include <revolution/OS.h>

#include <cstring>

#if defined(PACK_SPORTS)
#define RP_COMMON_SOUND_PATH "Sound/RPSportsCommon/rp_Common_Sports.brsar"
#elif defined(PACK_PARTY)
#define RP_COMMON_SOUND_PATH "Sound/RPPartyCommon/rp_Common_Party.brsar"
#endif

/**
 * @brief Displays the game's build date timestamp
 *
 * @param color Text color
 */
void RPSysScene::drawTimeStamp(nw4r::ut::Color color) {
    enum {
        YEARSIZE = sizeof("yyyy") - 1,
        MONTHSIZE = sizeof("mm") - 1,
        DAYSIZE = sizeof("dd") - 1,
        TIMESIZE = sizeof("hh:mm") - 1,
        BUFSIZE = 8
    };

    RP_GET_INSTANCE(RPSysTextWriter)->Begin();
    {
        RP_GET_INSTANCE(RPSysTextWriter)->SetDrawFlag(0);
        RP_GET_INSTANCE(RPSysTextWriter)->SetScale(0.65f, 0.65f);
        RP_GET_INSTANCE(RPSysTextWriter)->SetTextColor(color);

        const char* pTimeStamp =
            RP_GET_INSTANCE(RPSysSystem)->getTimeStampString();

        char year[BUFSIZE];
        std::strncpy(   //
            year,       //
            pTimeStamp, //
            YEARSIZE);

        char month[BUFSIZE];
        std::strncpy(                            //
            month,                               //
            pTimeStamp + YEARSIZE + sizeof('/'), //
            MONTHSIZE);

        char day[BUFSIZE];
        std::strncpy(                                                      //
            day,                                                           //
            pTimeStamp + YEARSIZE + sizeof('/') + MONTHSIZE + sizeof('/'), //
            DAYSIZE);

        char time[BUFSIZE];
        std::strncpy( //
            time,     //
            pTimeStamp + YEARSIZE + sizeof('/') + MONTHSIZE + sizeof('/') +
                DAYSIZE + sizeof(" \r\n") - 1,
            TIMESIZE);

        year[YEARSIZE] = 0;
        month[MONTHSIZE] = 0;
        day[DAYSIZE] = 0;
        time[TIMESIZE] = 0;

        RP_GET_INSTANCE(RPSysTextWriter)
            ->PrintfZeroCenter(-0.95f, -0.90f, "%s %s %s %s", //
                               month, day, year, time);
    }
    RP_GET_INSTANCE(RPSysTextWriter)->End();
}

void RPSysScene::loadUpdate() {}

/**
 * @brief Marks that this scene requires an asynchronous task
 */
void RPSysScene::setTaskAsync() {
    mFlags.setBit(EFlag_TaskAsyncSet);
    mFlags.setBit(EFlag_TaskAsyncRunning);
}

/**
 * @brief Tests whether this scene's asynchronous task has finished
 */
bool RPSysScene::isTaskAsyncFinish() const {
    return mFlags.onBit(EFlag_TaskAsyncSet) &&
           mFlags.offBit(EFlag_TaskAsyncRunning);
}

/**
 * @brief Enables the "Now Loading" message display
 */
void RPSysScene::enableLoadMessage() {
    mFlags.setBit(EFlag_LoadMessage);
}

/**
 * @brief Loads this scene's resources asynchronously
 */
void RPSysScene::load() {
    if (mFlags.onBit(EFlag_LoadMessage)) {
        // Need to use loadMessage()
        return;
    }

    BOOL success = FALSE;
    OSMessage msg;

    RP_GET_INSTANCE(RPSysSystem)
        ->getDvdThread()
        ->request(loadResourceFunc, //
                  this,             //
                  RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage());

    do {
        do {
            RP_GET_INSTANCE(RPSysSystem)->loadFrameWork(true);

            EGG::TaskThread* pDvdThread =
                RP_GET_INSTANCE(RPSysSystem)->getDvdThread();

            msg = pDvdThread->waitQueueMessage( //
                pDvdThread->getEndMessageQueue(), &success);

        } while (!success);
    } while (msg != RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage());
}

/**
 * @brief Loads this scene's resources asynchronously, displaying a "Now
 * Loading" message if the feature is enabled
 */
void RPSysScene::loadMessage() {
    if (mFlags.offBit(EFlag_LoadMessage)) {
        // Need to use load()
        return;
    }

    bool finished = false;

    RP_GET_INSTANCE(RPSysSceneMgr)
        ->setSceneStatus(EGG::Fader::STATUS_PREPARE_IN);

    RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeIn();

    RP_GET_INSTANCE(RPSysSystem)
        ->getDvdThread()
        ->request(loadResourceFunc, //
                  this,             //
                  RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage());

    while (true) {
        BOOL success = FALSE;

        RP_GET_INSTANCE(RPSysSystem)->loadFrameWork(false);

        if (RP_GET_INSTANCE(RPSysSceneMgr)->calcSceneFader()) {
            break;
        }

        if (!finished) {
            EGG::TaskThread* pDvdThread =
                RP_GET_INSTANCE(RPSysSystem)->getDvdThread();

            OSMessage msg = pDvdThread->waitQueueMessage( //
                pDvdThread->getEndMessageQueue(), &success);

            if (success &&
                msg == RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage()) {

                finished = true;
            }

        } else if (RP_GET_INSTANCE(RPSysSceneMgr)->getSceneStatus() ==
                   EGG::Fader::STATUS_PREPARE_OUT) {

            RP_GET_INSTANCE(RPSysSceneMgr)->startSceneFadeOut();
        }
    }
}

/**
 * @brief Creates the asynchronous task thread if requested by the scene
 */
void RPSysScene::initTaskAsync() {
    if (mFlags.onBit(EFlag_TaskAsyncSet) &&
        mFlags.onBit(EFlag_TaskAsyncRunning)) {

        RP_GET_INSTANCE(RPSysSystem)
            ->getDvdThread()
            ->request(taskAsyncFunc, //
                      this,          //
                      RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage());
    }
}

/**
 * @brief Polls the status of the DVD task thread
 */
void RPSysScene::updateDvdEndMessage() {
    if (mFlags.onBit(EFlag_TaskAsyncSet) &&
        mFlags.onBit(EFlag_TaskAsyncRunning)) {

        BOOL success = FALSE;

        EGG::TaskThread* pDvdThread =
            RP_GET_INSTANCE(RPSysSystem)->getDvdThread();

        OSMessage msg = pDvdThread->waitQueueMessage(
            pDvdThread->getEndMessageQueue(), &success);

        if (success &&
            msg == RP_GET_INSTANCE(RPSysSystem)->getDvdEndMessage()) {

            mFlags.resetBit(EFlag_TaskAsyncRunning);
        }
    }
}

/**
 * @brief Polls the status of the NAND task thread
 */
void RPSysScene::updateNandEndMessage() {
    if (!RP_GET_INSTANCE(RPSysSaveDataMgr)->isNandAccessFinish()) {
        BOOL success = FALSE;

        EGG::TaskThread* pNandThread =
            RP_GET_INSTANCE(RPSysSystem)->getNandThread();

        OSMessage msg = pNandThread->waitQueueMessage(
            pNandThread->getEndMessageQueue(), &success);

        if (success &&
            msg == RP_GET_INSTANCE(RPSysSystem)->getNandEndMessage()) {

            RP_GET_INSTANCE(RPSysSaveDataMgr)->finishNandAccess();
        }
    }

    if (!RP_GET_INSTANCE(RPSysHomeMenuMgr)->isOpen() &&
        !RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {

        RP_GET_INSTANCE(RPSysSaveDataMgr)->update(isSceneDisplay());
    }
}

/**
 * @brief Thread function for the LoadResource phase
 *
 * @param pArg Thread function argument
 */
void RPSysScene::loadResourceFunc(void* pArg) {
    RPSysScene* p = static_cast<RPSysScene*>(pArg);

    if (RP_GET_INSTANCE(RPSysSceneCreator)->getAudioType(p->getSceneID()) ==
        RPSysSceneCreator::EAudioType_Common) {

        RP_GET_INSTANCE(RPSndAudioMgr)
            ->openArchive(RP_COMMON_SOUND_PATH, NULL,
                          EGG::ArcPlayer::SARC_STORAGE_DVD, NULL);

        if (p->getSceneID() == RPSysSceneCreator::ESceneID_RPSysBootScene) {
            RP_GET_INSTANCE(RPSndAudioMgr)->loadGroup("GROUP_LOGO");
        } else {
            RP_GET_INSTANCE(RPSndAudioMgr)->loadGroup("GROUP_COMMON_01");
        }
    }

    p->LoadResource();
}

/**
 * @brief Thread function for the scene's task
 *
 * @param pArg Thread function argument
 */
void RPSysScene::taskAsyncFunc(void* pArg) {
    RPSysScene* p = static_cast<RPSysScene*>(pArg);

    p->taskAsync();
}
