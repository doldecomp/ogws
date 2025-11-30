#ifndef HOME_BUTTON_MINI_LIB_REMOTE_SPK_H
#define HOME_BUTTON_MINI_LIB_REMOTE_SPK_H
#include <homebuttonMiniLib/HBMTypes.h>

#include <revolution/ARC.h>
#include <revolution/OS.h>
#include <revolution/WENC.h>
#include <revolution/WPAD.h>

namespace homebutton {

class RemoteSpk {
private:
    struct ChanInfo {
        OSAlarm alarm;     // at 0x0
        WENCInfo wencinfo; // at 0x30
        const s16* in_pcm; // at 0x50
        int length;        // at 0x54
        int seId;          // at 0x58
        bool first;        // at 0x5C
        s8 vol;            // at 0x5D
        s8 cannotSendCnt;  // at 0x5E
        u16 pad;           // at 0x60
        bool playReady;    // at 0x62
    };

private:
    static RemoteSpk* spInstance;

    ChanInfo info[WPAD_MAX_CONTROLLERS]; // at 0x0
    OSAlarm speakerAlarm;                // at 0x1A0
    ARCHandle handle;                    // at 0x1D0
    bool available;                      // at 0x1EC

public:
    static void SetInstance(RemoteSpk* pThis);
    static RemoteSpk* GetInstance();

    RemoteSpk(void* pSpkSeBuf);
    virtual ~RemoteSpk(); // at 0x8

    bool isPlayReady(s32 chan) const;
    bool isPlaying(s32 chan) const;
    bool isPlayingId(s32 chan, int seId) const;

    void GetPCMFromSeID(int id, s16*& rpPcm, int& rLength);
    void ClearPcm();
    void Start();
    void Stop();
    void Connect(s32 chan);
    void Play(s32 chan, int seID, s8 vol);

private:
    static void UpdateSpeaker(OSAlarm* pAlarm, OSContext* pContext);

    static void SpeakerOnCallback(s32 chan, s32 result);
    static void DelaySpeakerOnCallback(OSAlarm* pAlarm, OSContext* pContext);

    static void SpeakerPlayCallback(s32 chan, s32 result);
    static void DelaySpeakerPlayCallback(OSAlarm* pAlarm, OSContext* pContext);
};

} // namespace homebutton

#endif
