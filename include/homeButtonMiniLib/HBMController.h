#ifndef HOME_BUTTON_MINI_LIB_CONTROLLER_H
#define HOME_BUTTON_MINI_LIB_CONTROLLER_H
#include <homeButtonMiniLib/HBMTypes.h>

#include <nw4r/snd.h>

#include <revolution/MTX.h>
#include <revolution/OS.h>
#include <revolution/WPAD.h>

struct HBController {
    int chan;    // at 0x0
    f32 spVol;   // at 0x4
    f32 x;       // at 0x8
    f32 y;       // at 0xC
    u32 trig;    // at 0x10
    u32 hold;    // at 0x14
    u32 release; // at 0x18
    bool rumble; // at 0x1C
    u32 unk20;
};

namespace homebutton {

// Forward declarations
class RemoteSpk;

class Controller {
public:
    Controller(int chan, RemoteSpk* spk);
    ~Controller();

    HBController* getController();

    int getChan() const;
    f32 getSpeakerVol() const;
    void setSpeakerVol(f32 vol);

    bool isRumbling() {
        return mHBController.rumble;
    }
    void setRumble() {
        mHBController.rumble = true;
    }
    void clrRumble() {
        mHBController.rumble = false;
    }

    RemoteSpk* getRemoteSpk() const {
        return remotespk;
    }

    bool getBatteryFlag() const;

    void setEnableRumble(bool flag) {
        mRumbleFlag = flag;
    }

    s32 getInfoAsync(WPADInfo* info);
    bool isPlayReady() const;
    bool isPlayingSound() const;
    bool isPlayingSoundId(int id) const;

    void setKpad(const HBMKPadData* con, bool updatePos);
    void setInValidPos();
    void clrBatteryFlag();
    void clrKpadButton();

    void connect();
    void disconnect();

    void initSound();
    void updateSound();
    void playSound(nw4r::snd::SoundArchivePlayer* player, int id);

    void soundOn();
    void soundOff(int msec);

    void startMotor();
    void stopMotor();

    void initCallback();
    void clearCallback();

private:
    static void wpadConnectCallback(s32 chan, s32 result);
    static void wpadExtensionCallback(s32 chan, s32 result);
    static void soundOnCallback(OSAlarm* alm, OSContext* context);
    static void ControllerCallback(s32 chan, s32 result);

private:
    static bool sBatteryFlag[WPAD_MAX_CONTROLLERS];
    static OSAlarm sAlarm[WPAD_MAX_CONTROLLERS];
    static OSAlarm sAlarmSoundOff[WPAD_MAX_CONTROLLERS];
    static Controller* sThis[WPAD_MAX_CONTROLLERS];

    HBController mHBController;                  // at 0x00
    RemoteSpk* remotespk;                        // at 0x20
    WPADConnectCallback mOldConnectCallback;     // at 0x24
    WPADExtensionCallback mOldExtensionCallback; // at 0x28
    s64 mPlaySoundTime;                          // at 0x30
    s64 mStopSoundTime;                          // at 0x38
    bool mCallbackFlag;                          // at 0x40
    bool mSoundOffFlag;                          // at 0x41
    bool mCheckSoundTimeFlag;                    // at 0x42
    bool mCheckSoundIntervalFlag;                // at 0x43
    bool mRumbleFlag;                            // at 0x44
};

} // namespace homebutton

#endif
