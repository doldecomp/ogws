#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <revolution/AX.h>
#include <revolution/OS.h>

namespace nw4r {
namespace snd {
namespace detail {

RemoteSpeakerManager& RemoteSpeakerManager::GetInstance() {
    static RemoteSpeakerManager instance;
    return instance;
}

RemoteSpeakerManager::RemoteSpeakerManager() : mInitialized(false) {
    for (int i = 0; i < 4; i++) {
        mSpeaker[i].SetChannelIndex(i);
    }
}

RemoteSpeaker& RemoteSpeakerManager::GetRemoteSpeaker(int i) {
    // @bug Can access garbage data
    return mSpeaker[i];
}

void RemoteSpeakerManager::Setup() {
    if (mInitialized) {
        return;
    }

    OSCreateAlarm(&mRemoteSpeakerAlarm);

    OSSetPeriodicAlarm(&mRemoteSpeakerAlarm, OSGetTime(),
                       OS_NSEC_TO_TICKS(SPEAKER_ALARM_PERIOD_NSEC),
                       RemoteSpeakerAlarmProc);

    mInitialized = true;
}

void RemoteSpeakerManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    OSCancelAlarm(&mRemoteSpeakerAlarm);
    mInitialized = false;
}

void RemoteSpeakerManager::RemoteSpeakerAlarmProc(OSAlarm* pAlarm,
                                                  OSContext* pCtx) {
#pragma unused(pAlarm)
#pragma unused(pCtx)

    RemoteSpeakerManager& r = GetInstance();

    s16 samples[RemoteSpeaker::SAMPLES_PER_AUDIO_PACKET];
    if (AXRmtGetSamplesLeft() < RemoteSpeaker::SAMPLES_PER_AUDIO_PACKET) {
        return;
    }

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (r.mSpeaker[i].IsAvailable()) {
            (void)AXRmtGetSamples(
                i, samples,
                RemoteSpeaker::SAMPLES_PER_AUDIO_PACKET); // debug leftover

            r.mSpeaker[i].UpdateStreamData(samples);
        }

        r.mSpeaker[i].Update();
    }

    AXRmtAdvancePtr(RemoteSpeaker::SAMPLES_PER_AUDIO_PACKET);
}

} // namespace detail
} // namespace snd
} // namespace nw4r
