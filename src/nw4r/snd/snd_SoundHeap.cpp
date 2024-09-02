#include "snd_SoundHeap.h"
#include "snd_FrameHeap.h"
#include "snd_SoundThread.h"
#include "snd_DisposeCallbackManager.h"
#include <OSMutex.h>
#include <nw4r/ut.h>

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
            ut::detail::AutoLock<OSMutex> lock(mMutex);

            return mFrameHeap.Alloc(blockSize, &DisposeCallbackFunc, NULL);
        }

        void * SoundHeap::Alloc(u32 blockSize, FrameHeap::AllocCallback callback, void *p)
        {
            ut::detail::AutoLock<OSMutex> lock(mMutex);

            return mFrameHeap.Alloc(blockSize, callback, p);
        }

        void SoundHeap::Clear()
        {
            ut::detail::AutoLock<OSMutex> lockHeap(mMutex);
            SoundThread::AutoLock lockThread;

            mFrameHeap.Clear();
        }

        int SoundHeap::SaveState()
        {
            ut::detail::AutoLock<OSMutex> lock(mMutex);

            return mFrameHeap.SaveState();
        }

        void SoundHeap::LoadState(int state)
        {
            ut::detail::AutoLock<OSMutex> lockHeap(mMutex);
            SoundThread::AutoLock lockThread;

            mFrameHeap.LoadState(state);
        }

        void SoundHeap::DisposeCallbackFunc(void *p1, u32 i, void *p2)
        {
            DisposeCallbackManager::GetInstance().Dispose(p1, i, p2);
            DisposeCallbackManager::GetInstance().DisposeWave(p1, i, p2);
        }
    }
}