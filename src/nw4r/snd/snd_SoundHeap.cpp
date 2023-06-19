#include "snd_SoundHeap.h"
#include "snd_FrameHeap.h"
#include "snd_SoundThread.h"
#include "snd_DisposeCallbackManager.h"
#include <OSMutex.h>

namespace nw4r
{
    namespace snd
    {
        using namespace detail;

        SoundHeap::SoundHeap()
        {
            OSInitMutex(&mMutex);
        }

        SoundHeap::~SoundHeap()
        {
            mFrameHeap.Destroy();
        }

        bool SoundHeap::Create(void *pos, u32 size)
        {
            return mFrameHeap.Create(pos, size);
        }

        void SoundHeap::Destroy()
        {
            mFrameHeap.Destroy();
        }

        void * SoundHeap::Alloc(u32 blockSize)
        {
            OSMutex *mutex = &mMutex;

            OSLockMutex(mutex);
            void* result = mFrameHeap.Alloc(blockSize, &DisposeCallbackFunc, NULL);
            OSUnlockMutex(mutex);
            return result;
        }

        void * SoundHeap::Alloc(u32 blockSize, FrameHeap::AllocCallback callback, void *p)
        {
            OSMutex *mutex = &mMutex;

            OSLockMutex(mutex);
            void* result = mFrameHeap.Alloc(blockSize, callback, p);
            OSUnlockMutex(mutex);
            return result;
        }

        void SoundHeap::Clear()
        {
            OSMutex* mutex = &mMutex;

            OSLockMutex(mutex);
            SoundThread::GetInstance()->Lock();
            mFrameHeap.Clear();
            SoundThread::GetInstance()->Unlock();
            OSUnlockMutex(mutex);
        }

        int SoundHeap::SaveState()
        {
            OSMutex* mutex = &mMutex;

            OSLockMutex(mutex);
            int result = mFrameHeap.SaveState();
            OSUnlockMutex(mutex);
            return result;
        }

        void SoundHeap::LoadState(int state)
        {
            OSMutex* mutex = &mMutex;

            OSLockMutex(mutex);
            SoundThread::GetInstance()->Lock();
            mFrameHeap.LoadState(state);
            SoundThread::GetInstance()->Unlock();
            OSUnlockMutex(mutex);
        }

        void SoundHeap::DisposeCallbackFunc(void *p1, u32 i, void *p2)
        {
            DisposeCallbackManager::GetInstance()->Dispose(p1, i, p2);
            DisposeCallbackManager::GetInstance()->DisposeWave(p1, i, p2);
        }
    }
}