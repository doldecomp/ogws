#include "eggAudioSystem.h"
#include "snd_AxManager.h"
#include "snd_SoundSystem.h"

namespace EGG
{
    using namespace nw4r;

    AudioSystem::AudioSystem() : WORD_0x8(0), FLOAT_0x0(1.0f)
    {
        WORD_0x4 = 0;
        sInstance = this;
    }

    AudioSystem::~AudioSystem()
    {

    }

    void AudioSystem::calc()
    {
        f32 currentVolume = snd::SoundSystem::GetMasterVolume();

        if ((WORD_0x8 == 1) && (currentVolume == 0.0f))
        {
            snd::SoundSystem::ShutdownSoundSystem();
            snd::SoundSystem::PrepareReset();
            snd::SoundSystem::WaitForResetReady();
            WORD_0x8 = 2;
        }

        if ((WORD_0x8 != 2) && (WORD_0x4 == 1) && (currentVolume == 0.0f))
        {
            WORD_0x4 = 2;
        }
    }

    AudioSystem *AudioSystem::sInstance;
}