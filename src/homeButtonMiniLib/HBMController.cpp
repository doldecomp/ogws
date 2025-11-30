#include <homeButtonMiniLib.h>

#include <revolution/MTX.h>
#include <revolution/OS.h>
#include <revolution/PAD.h>
#include <revolution/WPAD.h>


namespace homebutton {

bool Controller::sBatteryFlag[WPAD_MAX_CONTROLLERS];
OSAlarm Controller::sAlarm[WPAD_MAX_CONTROLLERS];
OSAlarm Controller::sAlarmSoundOff[WPAD_MAX_CONTROLLERS];
Controller* Controller::sThis[WPAD_MAX_CONTROLLERS];

void Controller::wpadConnectCallback(s32 chan, s32 result) {
    switch (result) {
    case WPAD_ERR_OK: {
        if (!sThis[chan]->mCallbackFlag) {
            sThis[chan]->mOldExtensionCallback =
                WPADSetExtensionCallback(chan, &wpadExtensionCallback);

            sThis[chan]->mCallbackFlag = true;
        }

        WPADControlSpeaker(chan, WPAD_SPEAKER_OFF, NULL);
        break;
    }

    case WPAD_ERR_NO_CONTROLLER: {
        WPADSetExtensionCallback(chan, sThis[chan]->mOldExtensionCallback);
        sThis[chan]->mOldExtensionCallback = NULL;

        sThis[chan]->mCallbackFlag = false;
        sThis[chan]->mCheckSoundTimeFlag = false;
        sThis[chan]->mCheckSoundIntervalFlag = false;
        break;
    }
    }

    if (sThis[chan]->mOldConnectCallback != NULL) {
        sThis[chan]->mOldConnectCallback(chan, result);
    }
}

void Controller::wpadExtensionCallback(s32 chan, s32 result) {
    switch (result) {
    case WPAD_DEV_UNKNOWN: {
        sThis[chan]->soundOff(1000);
        break;
    }
    }

    if (sThis[chan]->mOldExtensionCallback != NULL) {
        sThis[chan]->mOldExtensionCallback(chan, result);
    }
}

void Controller::soundOnCallback(OSAlarm* alm, OSContext* /* ctx */) {
    int chan = reinterpret_cast<int>(OSGetAlarmUserData(alm));
    sThis[chan]->soundOn();
}

Controller::Controller(int chan, RemoteSpk* spk) {
    mHBController.unk20 = 0;
    mHBController.chan = chan;
    mHBController.rumble = false;
    mHBController.spVol = 1.0f;

    remotespk = spk;
    mOldConnectCallback = NULL;
    mOldExtensionCallback = NULL;
    mCallbackFlag = false;
    mSoundOffFlag = false;
    mRumbleFlag = true;

    if (chan < WPAD_MAX_CONTROLLERS) {
        sBatteryFlag[chan] = false;
        OSCreateAlarm(&sAlarm[chan]);
        OSCreateAlarm(&sAlarmSoundOff[chan]);
        sThis[chan] = this;
    }
}

Controller::~Controller() {
    OSCancelAlarm(&sAlarm[mHBController.chan]);
    OSCancelAlarm(&sAlarmSoundOff[mHBController.chan]);

    sThis[mHBController.chan] = NULL;
}

void Controller::initCallback() {
    s32 type;

    mOldConnectCallback =
        WPADSetConnectCallback(mHBController.chan, &wpadConnectCallback);

    mRumbleFlag = true;

    switch (WPADProbe(mHBController.chan, &type)) {
    case WPAD_ERR_OK: {
        mOldExtensionCallback = WPADSetExtensionCallback(
            mHBController.chan, &wpadExtensionCallback);

        mCallbackFlag = true;
        break;
    }

    case WPAD_ERR_NO_CONTROLLER: {
        mCallbackFlag = false;
        break;
    }
    }
}

void Controller::clearCallback() {
    WPADSetConnectCallback(mHBController.chan, mOldConnectCallback);
    mOldConnectCallback = NULL;

    WPADSetExtensionCallback(mHBController.chan, mOldExtensionCallback);
    mOldExtensionCallback = NULL;
}

void Controller::setKpad(const HBMKPadData* con, bool updatePos) {
    if (!con->kpad) {
        return;
    }

    if (updatePos) {
        if (con->kpad->dev_type == WPAD_DEV_CLASSIC &&
            con->use_devtype == WPAD_DEV_CLASSIC) {
            mHBController.x = con->pos.x;
            mHBController.y = con->pos.y;
        } else {
            mHBController.x = con->kpad->pos.x;
            mHBController.y = con->kpad->pos.y;
        }
    }

    mHBController.trig = con->kpad->trig;
    mHBController.hold = con->kpad->hold;
    mHBController.release = con->kpad->release;

    if (con->kpad->dev_type == WPAD_DEV_CLASSIC &&
        con->use_devtype == WPAD_DEV_CLASSIC) {
        u32 h = con->kpad->ex_status.cl.hold;
        u32 t = con->kpad->ex_status.cl.trig;
        u32 r = con->kpad->ex_status.cl.release;

        // clang-format off
		if (h & WPAD_BUTTON_CL_A)     mHBController.hold    |= WPAD_BUTTON_A;
		if (t & WPAD_BUTTON_CL_A)     mHBController.trig    |= WPAD_BUTTON_A;
		if (r & WPAD_BUTTON_CL_A)     mHBController.release |= WPAD_BUTTON_A;

		if (h & WPAD_BUTTON_CL_PLUS)  mHBController.hold    |= WPAD_BUTTON_PLUS;
		if (t & WPAD_BUTTON_CL_PLUS)  mHBController.trig    |= WPAD_BUTTON_PLUS;
		if (r & WPAD_BUTTON_CL_PLUS)  mHBController.release |= WPAD_BUTTON_PLUS;

		if (h & WPAD_BUTTON_CL_MINUS) mHBController.hold    |= WPAD_BUTTON_MINUS;
		if (t & WPAD_BUTTON_CL_MINUS) mHBController.trig    |= WPAD_BUTTON_MINUS;
		if (r & WPAD_BUTTON_CL_MINUS) mHBController.release |= WPAD_BUTTON_MINUS;

		if (h & WPAD_BUTTON_CL_HOME)  mHBController.hold    |= WPAD_BUTTON_HOME;
		if (t & WPAD_BUTTON_CL_HOME)  mHBController.trig    |= WPAD_BUTTON_HOME;
		if (r & WPAD_BUTTON_CL_HOME)  mHBController.release |= WPAD_BUTTON_HOME;
        // clang-format on
    }
}

void Controller::clrKpadButton() {
    mHBController.trig = 0;
    mHBController.hold = 0;
    mHBController.release = 0;
}

void Controller::setInValidPos() {
    mHBController.x = -10000.0f;
    mHBController.y = -10000.0f;
}

int Controller::getChan() const {
    return mHBController.chan;
}

void Controller::connect() {
    getRemoteSpk()->Connect(getChan());
}

void Controller::disconnect() {}

void Controller::setSpeakerVol(f32 vol) {
    mHBController.spVol = vol;
}

f32 Controller::getSpeakerVol() const {
    return mHBController.spVol;
}

void Controller::playSound(nw4r::snd::SoundArchivePlayer* /* player */,
                           int id) {
    if (mSoundOffFlag) {
        return;
    }

    getRemoteSpk()->Play(getChan(), id, getSpeakerVol() * 10.0f);

    if (WPADIsSpeakerEnabled(getChan())) {
        if (!mCheckSoundTimeFlag) {
            mPlaySoundTime = OSGetTime();
        }

        mCheckSoundTimeFlag = true;
        mCheckSoundIntervalFlag = false;
    }
}

bool Controller::isPlayingSound() const {
    return getRemoteSpk()->isPlaying(getChan());
}

bool Controller::isPlayingSoundId(int id) const {
    if (!isPlayingSound()) {
        return false;
    }

    if (!getRemoteSpk()->isPlayingId(getChan(), id)) {
        return false;
    }

    return true;
}

void Controller::initSound() {
    mCheckSoundTimeFlag = false;
    mCheckSoundIntervalFlag = false;
}

void Controller::soundOff(int msec) {
    int chan = getChan();

    if (!WPADIsSpeakerEnabled(chan)) {
        return;
    }

    WPADControlSpeaker(chan, WPAD_SPEAKER_MUTE, NULL);

    OSSetAlarmUserData(&sAlarmSoundOff[chan], reinterpret_cast<void*>(chan));
    OSCancelAlarm(&sAlarmSoundOff[chan]);
    OSSetAlarm(&sAlarmSoundOff[chan], OS_MSEC_TO_TICKS(msec), &soundOnCallback);

    mSoundOffFlag = true;
}

void Controller::soundOn() {
    int chan = getChan();

    if (WPADIsSpeakerEnabled(chan)) {
        WPADControlSpeaker(chan, WPAD_SPEAKER_UNMUTE, NULL);
    }

    mSoundOffFlag = false;
}

bool Controller::isPlayReady() const {
    return getRemoteSpk()->isPlayReady(getChan());
}

HBController* Controller::getController() {
    return &mHBController;
}

void Controller::startMotor() {
    if (getChan() < WPAD_MAX_CONTROLLERS && !isPlayingSound() && mRumbleFlag) {
        setRumble();
        WPADControlMotor(getChan(), WPAD_MOTOR_RUMBLE);
    }
}

void Controller::stopMotor() {
    if (getChan() < WPAD_MAX_CONTROLLERS && isRumbling()) {
        clrRumble();
        WPADControlMotor(getChan(), WPAD_MOTOR_STOP);
    }
}

s32 Controller::getInfoAsync(WPADInfo* info) {
    if (getChan() >= WPAD_MAX_CONTROLLERS) {
        return WPAD_ERR_COMMUNICATION_ERROR;
    }

    if (isPlayingSound() || isRumbling()) {
        return WPAD_ERR_COMMUNICATION_ERROR;
    }

    return WPADGetInfoAsync(getChan(), info, &ControllerCallback);
}

void Controller::ControllerCallback(s32 chan, s32 result) {
    if (result == WPAD_ERR_OK && chan < WPAD_MAX_CONTROLLERS) {
        sBatteryFlag[chan] = true;
    }
}

bool Controller::getBatteryFlag() const {
    if (getChan() >= WPAD_MAX_CONTROLLERS) {
        return false;
    }

    return sBatteryFlag[getChan()];
}

void Controller::clrBatteryFlag() {
    if (getChan() >= WPAD_MAX_CONTROLLERS) {
        return;
    }

    sBatteryFlag[getChan()] = false;
}

} // namespace homebutton
