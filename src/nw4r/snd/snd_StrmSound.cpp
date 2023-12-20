#include "snd_StrmSound.h"
#include "snd_StrmSoundHandle.h"
#include "snd_SoundInstanceManager.h"
#include "ut_algorithm.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            StrmSound::StrmSound(SoundInstanceManager<StrmSound> *pManager)
                : mPlayer(), mManager(pManager), mTempSpecialHandle(NULL)
            {

            }

            bool StrmSound::Prepare(StrmBufferPool *pPool, StrmPlayer::StartOffsetType offset,
                s32 r6, int r7, ut::FileStream *pStream)
            {
                if (pPool == NULL) return false;

                InitParam();
                
                if (!mPlayer.Setup(pPool)) return false;
                if (!mPlayer.Prepare(pStream, r7, offset, r6))
                {
                    mPlayer.Shutdown();
                    return false;
                }

                return true;
            }

            UNKTYPE StrmSound::Shutdown()
            {
                BasicSound::Shutdown();
                mManager->Free(this);
            }

            StrmSound::~StrmSound()
            {

            }

            void StrmSound::SetPlayerPriority(int priority)
            {
                BasicSound::SetPlayerPriority(priority);
                mManager->UpdatePriority(this, CalcCurrentPlayerPriority());
            }

            bool StrmSound::IsAttachedTempSpecialHandle()
            {
                return (mTempSpecialHandle != NULL);
            }

            UNKTYPE StrmSound::DetachTempSpecialHandle()
            {
                mTempSpecialHandle->DetachSound();
            }

            BasicPlayer * StrmSound::GetBasicPlayer()
            {
                return &mPlayer;
            }

            const BasicPlayer * StrmSound::GetBasicPlayer() const
            {
                return &mPlayer;
            }

            bool StrmSound::IsPrepared() const
            {
                return mPlayer.IsPrepared();
            }

            const ut::detail::RuntimeTypeInfo * StrmSound::GetRuntimeTypeInfo() const
            {
                return &typeInfo;
            }

            ut::detail::RuntimeTypeInfo StrmSound::typeInfo(&BasicSound::typeInfo);
        }
    }
}