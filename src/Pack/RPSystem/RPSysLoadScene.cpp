#include <Pack/RPSystem.h>

#include <revolution/OS.h>

#include <cstring>

/**
 * @brief Displays the game's build date timestamp
 *
 * @param color Text color
 */
void RPSysScene::drawTimeStamp(nw4r::ut::Color color) {
    enum {
        YEAR_SZ = sizeof("yyyy") - 1,
        MONTH_SZ = sizeof("mm") - 1,
        DAY_SZ = sizeof("dd") - 1,
        TIME_SZ = sizeof("hh:mm") - 1,
    };

    RP_GET_INSTANCE(RPSysTextWriter)->Begin();
    {
        RP_GET_INSTANCE(RPSysTextWriter)->SetDrawFlag(0);
        RP_GET_INSTANCE(RPSysTextWriter)->SetScale(0.65f, 0.65f);
        RP_GET_INSTANCE(RPSysTextWriter)->SetTextColor(color);

        const char* pTimeStamp =
            RP_GET_INSTANCE(RPSysSystem)->getTimeStampString();

        char year[8];
        std::strncpy(   //
            year,       //
            pTimeStamp, //
            YEAR_SZ);

        char month[8];
        std::strncpy(                           //
            month,                              //
            pTimeStamp + YEAR_SZ + sizeof('/'), //
            MONTH_SZ);

        char day[8];
        std::strncpy(                                                    //
            day,                                                         //
            pTimeStamp + YEAR_SZ + sizeof('/') + MONTH_SZ + sizeof('/'), //
            DAY_SZ);

        char time[8];
        std::strncpy( //
            time,     //
            pTimeStamp + YEAR_SZ + sizeof('/') + MONTH_SZ + sizeof('/') +
                DAY_SZ + sizeof(" \r\n") - 1,
            TIME_SZ);

        year[YEAR_SZ] = 0;
        month[MONTH_SZ] = 0;
        day[DAY_SZ] = 0;
        time[TIME_SZ] = 0;

        RP_GET_INSTANCE(RPSysTextWriter)
            ->PrintfZeroCenter(-0.95f, -0.90f, "%s %s %s %s", //
                               month, day, year, time);
    }
    RP_GET_INSTANCE(RPSysTextWriter)->End();
}

void RPSysScene::loadUpdate() {}

void RPSysScene::setTaskAsync() {
    mFlags.setBit(EFlag_1);
    mFlags.setBit(EFlag_2);
}

bool RPSysScene::isTaskAsyncFinish() const {
    return mFlags.onBit(EFlag_1) && !mFlags.onBit(EFlag_2);
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
    // Need to use loadMessage()
    if (mFlags.onBit(EFlag_LoadMessage)) {
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
    // Need to use load()
    if (mFlags.offBit(EFlag_LoadMessage)) {
        return;
    }
}
