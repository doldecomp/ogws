#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>
#include <revolution/OS.h>

namespace nw4r {
namespace snd {
namespace detail {

SoundThread::SoundThread() : mStackEnd(NULL), mCreateFlag(false) {
    OSInitMessageQueue(&mMsgQueue, mMsgBuffer, MSG_QUEUE_CAPACITY);
    OSInitThreadQueue(&mThreadQueue);
    OSInitMutex(&mMutex);
}

SoundThread& SoundThread::GetInstance() {
    static SoundThread instance;
    return instance;
}

bool SoundThread::Create(s32 priority, void* pStack, u32 stackSize) {
    if (mCreateFlag) {
        return true;
    }

    mCreateFlag = true;
    mStackEnd = pStack;

    BOOL success = OSCreateThread(&mThread, SoundThreadFunc, &GetInstance(),
                                  static_cast<u8*>(pStack) + stackSize,
                                  stackSize, priority, 0);

    if (success) {
        OSResumeThread(&mThread);
    }

    return success;
}

void SoundThread::Shutdown() {
    if (!mCreateFlag) {
        return;
    }

    OSJamMessage(&GetInstance().mMsgQueue,
                 reinterpret_cast<OSMessage>(MSG_SHUTDOWN), OS_MSG_BLOCKING);

    OSJoinThread(&mThread, NULL);
    mCreateFlag = false;
}

void SoundThread::AxCallbackFunc() {
    GetInstance().AxCallbackProc();
}

void SoundThread::AxCallbackProc() {
    OSSendMessage(&mMsgQueue, reinterpret_cast<OSMessage>(MSG_AX_CALLBACK), 0);

    NW4R_UT_LIST_SAFE_FOREACH (mPlayerCallbackList,
                          { it->OnUpdateVoiceSoundThread(); })

    VoiceManager::GetInstance().NotifyVoiceUpdate();
}

void* SoundThread::SoundThreadFunc(void* pArg) {
    SoundThread* p = static_cast<SoundThread*>(pArg);

    AxManager::GetInstance().RegisterCallback(&p->mAxCallbackNode,
                                              AxCallbackFunc);

    p->SoundThreadProc();

    AxManager::GetInstance().UnregisterCallback(&p->mAxCallbackNode);

    return NULL;
}

void SoundThread::RegisterPlayerCallback(PlayerCallback* pCallback) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    mPlayerCallbackList.PushBack(pCallback);
}

void SoundThread::UnregisterPlayerCallback(PlayerCallback* pCallback) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    mPlayerCallbackList.Erase(pCallback);
}

void SoundThread::SoundThreadProc() {
    OSMessage msg;

    while (true) {
        OSReceiveMessage(&mMsgQueue, &msg, OS_MSG_BLOCKING);

        if (reinterpret_cast<u32>(msg) == MSG_AX_CALLBACK) {
            ut::detail::AutoLock<OSMutex> lock(mMutex);

            NW4R_UT_LIST_SAFE_FOREACH(mSoundFrameCallbackList,
                it->OnBeginSoundFrame();
            )

            u32 start = OSGetTick();
            {
                AxVoiceManager::GetInstance().FreeAllReservedAxVoice();
                AxManager::GetInstance().Update();

                if (!AxManager::GetInstance().IsDiskError()) {
                    NW4R_UT_LIST_SAFE_FOREACH(mPlayerCallbackList,
                        it->OnUpdateFrameSoundThread();
                    )

                    ChannelManager::GetInstance().UpdateAllChannel();
                }

                (void)Util::CalcRandom();
                VoiceManager::GetInstance().UpdateAllVoices();
            }
            mProcessTick = OSGetTick() - start;

            NW4R_UT_LIST_SAFE_FOREACH(mSoundFrameCallbackList,
                it->OnEndSoundFrame();
            )

        } else if (reinterpret_cast<u32>(msg) == MSG_SHUTDOWN) {
            NW4R_UT_LIST_SAFE_FOREACH(mPlayerCallbackList,
                it->OnShutdownSoundThread();
            )

            break;
        }
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
