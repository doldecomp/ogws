#pragma ipa file
#include <revolution/OS/OSTime.h>
#include "ut_lock.h"
#include "snd_SoundThread.h"
#include "snd_VoiceManager.h"
#include "snd_AxVoiceManager.h"
#include "snd_ChannelManager.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            SoundThread::SoundThread() : mStackEnd(NULL), mIsCreated(false)
            {
                OSInitMessageQueue(&mMesgQueue, &mMesgBuffer, 4);
                OSInitThreadQueue(&mThreadQueue);
                OSInitMutex(&mMutex);
            }

            SoundThread * SoundThread::GetInstance()
            {
                static SoundThread instance;
                return &instance;
            }

            bool SoundThread::Create(s32 r4, void *stack, u32 stackSize)
            {
                if (mIsCreated) return true;

                mIsCreated = true;
                mStackEnd = stack;
                BOOL success = OSCreateThread(&mThread, SoundThreadFunc, GetInstance(),
                    (u8 *)stack + stackSize, stackSize, r4, 0);

                if (success) OSResumeThread(&mThread);

                return success;
            }

            void SoundThread::Shutdown()
            {
                if (!mIsCreated) return;

                OSJamMessage(&GetInstance()->mMesgQueue, (OSMessage)2, 1);
                OSJoinThread(&mThread, 0);
                mIsCreated = false;
            }

            void SoundThread::AxCallbackFunc()
            {
                GetInstance()->AxCallbackProc();
            }

            void SoundThread::AxCallbackProc()
            {
                OSSendMessage(&mMesgQueue, (OSMessage)1, 0);

                ut::LinkList<PlayerCallback, 0>::Iterator it = mPlayerCbList.GetBeginIter();
                while (it != mPlayerCbList.GetEndIter())
                {
                    it++->OnUpdateVoiceSoundThread();
                }

                VoiceManager::GetInstance().NotifyVoiceUpdate();
            }

            void* SoundThread::SoundThreadFunc(void *data)
            {
                SoundThread *thisx = (SoundThread *)data;

                AxManager::GetInstance().RegisterCallback(&thisx->mAxNode, AxCallbackFunc);
                thisx->SoundThreadProc();
                AxManager::GetInstance().UnregisterCallback(&thisx->mAxNode);

                return NULL;
            }

            void SoundThread::RegisterPlayerCallback(PlayerCallback *cb)
            {
                ut::detail::AutoLock<OSMutex> lock(mMutex);
                mPlayerCbList.PushBack(cb);
            }

            void SoundThread::UnregisterPlayerCallback(PlayerCallback *cb)
            {
                ut::detail::AutoLock<OSMutex> lock(mMutex);
                mPlayerCbList.Erase(cb);
            }

           void SoundThread::SoundThreadProc()
            {
                OSMessage msg;

                while(true)
                {
                    OSReceiveMessage(&mMesgQueue, &msg, 1);

                    if ((u32)msg == 1)
                    {
                        ut::detail::AutoLock<OSMutex> lock(mMutex);

                        ut::LinkList<SoundThreadCallback, 0>::Iterator threadCb = mThreadCbList.GetBeginIter();
                        while (threadCb != mThreadCbList.GetEndIter())
                        {
                            threadCb++->VF_0xC();
                        }

                        s32 start = OSGetTick();

                        AxVoiceManager::GetInstance().FreeAllReservedAxVoice();
                        AxManager::GetInstance().Update();

                        if (AxManager::GetInstance().IsDiskError() == 0)
                        {
                            ut::LinkList<PlayerCallback, 0>::Iterator playerCb = mPlayerCbList.GetBeginIter();
                            while (playerCb != mPlayerCbList.GetEndIter())
                            {
                                playerCb++->OnUpdateFrameSoundThread();
                            }

                            ChannelManager::GetInstance()->UpdateAllChannel();
                        }

                        Util::CalcRandom();
                        VoiceManager::GetInstance().UpdateAllVoices();

                        s32 end = OSGetTick();
                        mLastUpdateTime = end - start;

                        threadCb = mThreadCbList.GetBeginIter();
                        while (threadCb != mThreadCbList.GetEndIter())
                        {
                            threadCb++->VF_0x10();
                        }
                    }
                    else if ((u32)msg == 2)
                    {
                        ut::LinkList<PlayerCallback, 0>::Iterator playerCb = mPlayerCbList.GetBeginIter();
                        while (playerCb != mPlayerCbList.GetEndIter())
                        {
                            playerCb++->OnShutdownSoundThread();
                        }

                        break;
                    }
                }
            }
        }
    }
}