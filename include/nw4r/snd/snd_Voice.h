#ifndef NW4R_SND_VOICE_H
#define NW4R_SND_VOICE_H
#include <nw4r/snd/snd_AxVoice.h>
#include <nw4r/snd/snd_Common.h>
#include <nw4r/snd/snd_DisposeCallback.h>
#include <nw4r/snd/snd_WaveFile.h>
#include <nw4r/types_nw4r.h>
#include <nw4r/ut.h>
#include <revolution/WPAD.h>

namespace nw4r {
namespace snd {
namespace detail {

class Voice : public DisposeCallback {
public:
    enum VoiceCallbackStatus {
        CALLBACK_STATUS_FINISH_WAVE,
        CALLBACK_STATUS_CANCEL,
        CALLBACK_STATUS_DROP_VOICE,
        CALLBACK_STATUS_DROP_DSP,
    };

    typedef void (*VoiceCallback)(Voice* voice, VoiceCallbackStatus status,
                                  void* arg);

    enum VoiceSyncFlag {
        SYNC_AX_SRC_INITIAL = (1 << 0),
        SYNC_AX_VOICE = (1 << 1),
        SYNC_AX_SRC = (1 << 2),
        SYNC_AX_VE = (1 << 3),
        SYNC_AX_MIX = (1 << 4),
        SYNC_AX_LPF = (1 << 5),
        SYNC_AX_REMOTE = (1 << 7),
        SYNC_AX_BIQUAD = (1 << 8),
    };

public:
    Voice();
    virtual ~Voice(); // at 0x8

    virtual void InvalidateData(const void* start, const void* end) {} // at 0xC
    virtual void InvalidateWaveData(const void* start,
                                    const void* end); // at 0x10

    int GetPriority() const { return mPriority; }
    int GetAxVoiceCount() const { return mChannelCount * mVoiceOutCount; }

    bool IsActive() const { return mAxVoice[0][0] != NULL; }
    bool IsPlayFinished() const {
        return IsActive() && mAxVoice[0][0]->IsPlayFinished();
    }

    void InitParam(int chans, int voices, VoiceCallback callback, void* arg);
    void StopFinished();
    void Calc();
    void Update();
    bool Acquire(int chans, int voices, int prio, VoiceCallback callback,
                 void* arg);

    void Start();
    void Setup(const WaveData&, u32);
    void SetPriority(int);
    void Stop();
    void Free();
    void SetPanMode(PanMode);
    void SetPanCurve(PanCurve);
    void SetVolume(f32);
    void SetVeVolume(f32, f32);
    void SetPitch(f32);
    void SetPan(f32);
    void SetSurroundPan(f32);
    void SetLpfFreq(f32);
    void SetRemoteFilter(int);
    void SetOutputLine(int);
    void SetMainOutVolume(f32);
    void SetMainSend(f32);
    void SetFxSend(AuxBus bus, f32 send);
    void SetRemoteOutVolume(int remote, f32 vol);
    void SetRemoteSend(int remote, f32 send);
    void SetRemoteFxSend(int remote, f32 send);
    void Pause(bool flag);

    void CalcAxSrc(bool initial);
    void CalcAxVe();
    bool CalcAxMix();
    void CalcAxLpf();
    void CalcAxRemoteFilter();

    void SyncAxVoice();

    void RunAllAxVoice();
    void StopAllAxVoice();

    static void AxVoiceCallbackFunc(AxVoice* voice,
                                    AxVoice::AxVoiceCallbackStatus status,
                                    void* arg);

private:
    static const int CHANNELS_MIN = 1;
    static const int CHANNELS_MAX = 2;

    static const int VOICES_OUT_MIN = 1;
    static const int VOICES_OUT_MAX = 4;

    static const int PRIORITY_MIN = 0;
    static const int PRIORITY_MAX = 255;

    AxVoice* mAxVoice[CHANNELS_MAX][VOICES_OUT_MAX]; // at 0xC
    SoundParam mVoiceOutParam[VOICES_OUT_MAX];       // at 0x2C
    int mChannelCount;                               // at 0x9C
    int mVoiceOutCount;                              // at 0xA0
    VoiceCallback mCallback;                         // at 0xA4
    void* mCallbackArg;                              // at 0xA8
    bool mIsActive;                                  // at 0xAC
    bool mIsStarting;                                // at 0xAD
    bool mIsStarted;                                 // at 0xAE
    bool mIsPause;                                   // at 0xAF
    bool mIsPausing;                                 // at 0xB0
    u8 mSyncFlag;                                    // at 0xB1
    u8 mRemoteFilter;                                // at 0xB2
    u8 mBiquadType;                                  // at 0xB3
    int mPriority;                                   // at 0xB4
    f32 mPan;                                        // at 0xB8
    f32 mSurroundPan;                                // at 0xBC
    f32 mLpfFreq;                                    // at 0xC0
    int mOutputLineFlag;                             // at 0xC4
    f32 mMainOutVolume;                              // at 0xC8
    f32 mMainSend;                                   // at 0xCC
    f32 mFxSend[AUX_BUS_NUM];                        // at 0xD0
    f32 mRemoteOutVolume[WPAD_MAX_CONTROLLERS];      // at 0xDC
    f32 mRemoteSend[WPAD_MAX_CONTROLLERS];           // at 0xEC
    f32 mRemoteFxSend[WPAD_MAX_CONTROLLERS];         // at 0xFC
    f32 mPitch;                                      // at 0x10C
    f32 mVolume;                                     // at 0x110
    f32 mVeInitVolume;                               // at 0x114
    f32 mVeTargetVolume;                             // at 0x118
    PanMode mPanMode;                                // at 0x11C
    PanCurve mPanCurve;                              // at 0x120

public:
    NW4R_UT_LIST_NODE_DECL(); // at 0x124
};

NW4R_UT_LIST_TYPEDEF_DECL(Voice);

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
