#include <Pack/RPSystem.h>
#include <Pack/RPKernel.h>
#include <egg/core.h>
#include <egg/gfxe.h>
#include <revolution/SC.h>
#include <revolution/VI.h>
#include <revolution/OS.h>

void RPSysSystem::setupTVMode() {
    int i;

    VIInit();
    for (i = 0; i < 60; i++) {
        if (SCCheckStatus() == SC_STATUS_OK) {
            break;
        }
        VIWaitForRetrace();
    }
    if (SCGetAspectRatio() == SC_ASPECT_WIDE) {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_WIDE);
    }
    else {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_STD);
    }
}

RPSysSceneCreator::ESceneID RPSysSystem::getBootScene() {
    // this function is hardcoded (symbol name is official, weirdly enough)
    return RPSysSceneCreator::ESceneID_RPSportsTitleScene;
}

void RPSysSystem::startLoadCount() {
    mLoadCount = 0; // wrong register, should be r3 but this compiles to r4
}

const char* RPSysSystem::getTimeStampString() {
    return mpTimeStampString;
}

void RPSysSystem::setupLocalSettings() {
    u8 sysLanguage = SCGetLanguage();

    if (sysLanguage == SC_LANG_EN) {
        RP_GET_INSTANCE(RPSysProjectLocal)->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)->setLanguage(RPSysProjectLocal::EArea_USA);
    }
    else if (sysLanguage == SC_LANG_FR) {
        RP_GET_INSTANCE(RPSysProjectLocal)->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)->setLanguage(RPSysProjectLocal::EArea_France);
    }
    else if (sysLanguage == SC_LANG_SP) {
        RP_GET_INSTANCE(RPSysProjectLocal)->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)->setLanguage(RPSysProjectLocal::EArea_Spain);
    }
    //! Requires ifdef for non Americas versions
    else {
        RP_GET_INSTANCE(RPSysProjectLocal)->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)->setLanguage(RPSysProjectLocal::EArea_USA);
    }
}

/**
 * @brief Controls whether the game restarts or returns to the Wii Menu upon a
 * soft reset.
 */

void RPSysSystem::softResetCallBack() {
    if (RP_GET_INSTANCE(RPSysDvdStatus)->isErrorOccured()) {
        RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(FALSE);
    } else {
        VIEnableDimming(FALSE);
        if (RP_GET_INSTANCE(RPSysSceneMgr)->isNormalState() &&
            !RP_GET_INSTANCE(RPSysHomeMenuMgr)->startBlackOut()) {
            RP_GET_INSTANCE(RPSysSceneMgr)->softReset(FALSE);
        }
    }
}

void RPSysSystem::shutdownSystemCallBack() {
    RP_GET_INSTANCE(RPSysSceneMgr)->shutdownSystem(FALSE);
}
