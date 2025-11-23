// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>

#include <nw4r/snd.h>

namespace EGG {

AudioSystem* AudioSystem::sInstanse = NULL;

AudioSystem::AudioSystem()
    : mShutDownStatus(SHUTDOWN_STATUS_NONE), FLOAT_0x0(1.0f) {

    mResetStatus = RESET_STATUS_NONE;
    sInstanse = this;
}

AudioSystem::~AudioSystem() {}

void AudioSystem::calc() {
    f32 masterVol = nw4r::snd::SoundSystem::GetMasterVolume();

    if (mShutDownStatus == SHUTDOWN_STATUS_QUEUED && masterVol == 0.0f) {
        nw4r::snd::SoundSystem::ShutdownSoundSystem();
        nw4r::snd::SoundSystem::PrepareReset();
        nw4r::snd::SoundSystem::WaitForResetReady();

        mShutDownStatus = SHUTDOWN_STATUS_FINISH;
    }

    if (mShutDownStatus != SHUTDOWN_STATUS_FINISH &&
        mResetStatus == RESET_STATUS_QUEUED && masterVol == 0.0f) {

        mResetStatus = RESET_STATUS_FINISH;
    }
}

} // namespace EGG
