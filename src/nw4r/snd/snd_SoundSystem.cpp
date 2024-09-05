#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <revolution/AX.h>
#include <revolution/OS.h>
#include <revolution/SC.h>

namespace {

const char* NW4R_SND_Version_ =
    "<< NW4R    - SND \tfinal   build: Jun  8 2007 11:17:15 (0x4199_60831) >>";

static bool sInitialized = false;

} // namespace

namespace nw4r {
namespace snd {

detail::TaskThread SoundSystem::sTaskThread;

void SoundSystem::InitSoundSystem(s32 soundThreadPriority,
                                  s32 dvdThreadPriority) {
    const int defaultWorkSize = DEFAULT_SOUND_THREAD_STACK_SIZE +
                                DEFAULT_DVD_THREAD_STACK_SIZE +
                                detail::AxVoiceManager::WORK_SIZE_MAX +
                                detail::VoiceManager::WORK_SIZE_MAX +
                                detail::ChannelManager::WORK_SIZE_MAX;

    static u8 defaultSoundSystemWork[defaultWorkSize] ALIGN(32);

    OSRegisterVersion(NW4R_SND_Version_);

    SoundSystemParam param;
    param.soundThreadPriority = soundThreadPriority;
    param.dvdThreadPriority = dvdThreadPriority;

    InitSoundSystem(param, defaultSoundSystemWork,
                    sizeof(defaultSoundSystemWork));
}

u32 SoundSystem::GetRequiredMemSize(const SoundSystemParam& rParam) {
    return rParam.soundThreadStackSize + rParam.dvdThreadStackSize +
           detail::AxVoiceManager::GetInstance().GetRequiredMemSize() +
           detail::VoiceManager::GetInstance().GetRequiredMemSize() +
           detail::ChannelManager::GetInstance().GetRequiredMemSize();
}

void SoundSystem::InitSoundSystem(const SoundSystemParam& rParam, void* pWork,
                                  u32 workSize) {
    if (sInitialized) {
        return;
    }

    sInitialized = true;

    detail::AxManager::GetInstance().Init();

    SCInit();
    while (SCCheckStatus() == SC_STATUS_BUSY) {
        ;
    }

    switch (SCGetSoundMode()) {
    case SC_SND_MONO:
        detail::AxManager::GetInstance().SetOutputMode(OUTPUT_MODE_MONO);
        break;

    case SC_SND_STEREO:
        detail::AxManager::GetInstance().SetOutputMode(OUTPUT_MODE_STEREO);
        break;

    case SC_SND_SURROUND:
        detail::AxManager::GetInstance().SetOutputMode(OUTPUT_MODE_DPL2);
        break;

    default:
        detail::AxManager::GetInstance().SetOutputMode(OUTPUT_MODE_STEREO);
        break;
    }

    detail::RemoteSpeakerManager::GetInstance().Setup();

    u8* pPtr = static_cast<u8*>(pWork);

    void* pDvdThreadStack = pPtr;
    pPtr += rParam.dvdThreadStackSize;

    void* pSoundThreadStack = pPtr;
    pPtr += rParam.soundThreadStackSize;

    void* pAxVoiceWork = pPtr;
    pPtr += detail::AxVoiceManager::GetInstance().GetRequiredMemSize();

    detail::AxVoiceManager::GetInstance().Setup(
        pAxVoiceWork,
        detail::AxVoiceManager::GetInstance().GetRequiredMemSize());

    void* pVoiceWork = pPtr;
    pPtr += detail::VoiceManager::GetInstance().GetRequiredMemSize();

    detail::VoiceManager::GetInstance().Setup(
        pVoiceWork, detail::VoiceManager::GetInstance().GetRequiredMemSize());

    void* pChannelWork = pPtr;
    pPtr += detail::ChannelManager::GetInstance().GetRequiredMemSize();

    detail::ChannelManager::GetInstance().Setup(
        pChannelWork,
        detail::ChannelManager::GetInstance().GetRequiredMemSize());

    sTaskThread.Create(rParam.dvdThreadPriority, pDvdThreadStack,
                       rParam.dvdThreadStackSize);

    detail::SoundThread::GetInstance().Create(rParam.soundThreadPriority,
                                              pSoundThreadStack,
                                              rParam.soundThreadStackSize);
}

void SoundSystem::ShutdownSoundSystem() {
    if (!sInitialized) {
        return;
    }

    detail::SoundThread::GetInstance().Shutdown();
    detail::TaskManager::GetInstance().CancelAllTask();
    sTaskThread.Destroy();

    detail::RemoteSpeakerManager::GetInstance().Shutdown();
    detail::ChannelManager::GetInstance().Shutdown();
    detail::VoiceManager::GetInstance().Shutdown();
    detail::AxVoiceManager::GetInstance().Shutdown();
    detail::AxManager::GetInstance().Shutdown();

    sInitialized = false;
}

void SoundSystem::WaitForResetReady() {
    if (!sInitialized) {
        return;
    }

    u32 start = OSGetTick();

    while (!detail::AxManager::GetInstance().IsResetReady()) {
        if (OS_TICKS_TO_SEC(OSGetTick() - start) > 0) {
            break;
        }
    }
}

} // namespace snd
} // namespace nw4r
