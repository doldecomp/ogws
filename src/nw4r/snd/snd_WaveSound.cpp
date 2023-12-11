#include "snd_WaveSound.h"
#include "snd_WaveSoundHandle.h"
#include "snd_WsdPlayer.h"
#include "snd_SoundInstanceManager.h"
#include "ut_algorithm.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            WaveSound::WaveSound(SoundInstanceManager<WaveSound> *pManager)
                : mPlayer(), mManager(pManager), mTempSpecialHandle(NULL), mIsPrepared(false)
            {

            }

            bool WaveSound::Prepare(const void *waveSoundBase, long r5, WsdPlayer::StartOffsetType offset,
                s32 r7, int r8, const WsdPlayer::WsdCallback *pCallback, u32 r10)
            {
                InitParam();
                
                if (!mPlayer.Prepare(waveSoundBase, r5, offset, r7, r8, pCallback, r10)) return false;

                mIsPrepared = true;
                return true;
            }

            UNKTYPE WaveSound::Shutdown()
            {
                BasicSound::Shutdown();
                mManager->Free(this);
            }

            WaveSound::~WaveSound()
            {

            }

            void WaveSound::SetChannelPriority(int priority)
            {
                mPlayer.SetChannelPriority(priority);
            }

            void WaveSound::SetReleasePriorityFix(bool b)
            {
                mPlayer.SetReleasePriorityFix(b);
            }

            void WaveSound::SetPlayerPriority(int priority)
            {
                BasicSound::SetPlayerPriority(priority);
                
                int prio = mPlayerPriority + mParam.INT_0x18;
                mManager->UpdatePriority(this, (prio = ut::Clamp(prio, 0, 127)));
            }

            bool WaveSound::IsAttachedTempSpecialHandle()
            {
                return (mTempSpecialHandle != NULL);
            }

            UNKTYPE WaveSound::DetachTempSpecialHandle()
            {
                mTempSpecialHandle->DetachSound();
            }

            BasicPlayer * WaveSound::GetBasicPlayer()
            {
                return &mPlayer;
            }

            const BasicPlayer * WaveSound::GetBasicPlayer() const
            {
                return &mPlayer;
            }

            bool WaveSound::IsPrepared() const
            {
                return mIsPrepared;
            }

            const ut::detail::RuntimeTypeInfo * WaveSound::GetRuntimeTypeInfo() const
            {
                return &typeInfo;
            }

            ut::detail::RuntimeTypeInfo WaveSound::typeInfo(&BasicSound::typeInfo);
        }
    }
}