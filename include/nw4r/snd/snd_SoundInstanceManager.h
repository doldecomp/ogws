#ifndef NW4R_SND_SOUND_INSTANCE_MANAGER_H
#define NW4R_SND_SOUND_INSTANCE_MANAGER_H
#include <nw4r/snd/snd_InstancePool.h>
#include <nw4r/types_nw4r.h>
#include <nw4r/ut.h>
#include <revolution/OS.h>

namespace nw4r {
namespace snd {
namespace detail {

template <typename T> class SoundInstanceManager {
public:
    SoundInstanceManager() {
        OSInitMutex(&mMutex);
    }

    void Create(void* pBuffer, u32 size) {
        ut::detail::AutoLock<OSMutex> lock(mMutex);
        mPool.Create(pBuffer, size);
    }

    void Destroy(void* pBuffer, u32 size) {
        ut::detail::AutoLock<OSMutex> lock(mMutex);
        mPool.Destroy(pBuffer, size);
    }

    T* Alloc(int priority) {
        priority = ut::Clamp(priority, 0, BasicSound::PRIORITY_MAX);

        ut::detail::AutoLock<OSMutex> lock(mMutex);
        T* pSound = NULL;

        while (pSound == NULL) {
            void* pBuffer = mPool.Alloc();

            if (pBuffer != NULL) {
                pSound = new (pBuffer) T(this);
            } else {
                T* pLowest = GetLowestPrioritySound();

                if (pLowest == NULL) {
                    return NULL;
                }

                if (priority < pLowest->CalcCurrentPlayerPriority()) {
                    return NULL;
                }

                OSUnlockMutex(&mMutex);
                pLowest->Stop();
                OSLockMutex(&mMutex);
            }
        }

        InsertPriorityList(pSound, priority);
        return pSound;
    }

    void Free(T* pSound) {
        ut::detail::AutoLock<OSMutex> lock(mMutex);

        if (mPriorityList.IsEmpty()) {
            return;
        }

        RemovePriorityList(pSound);
        pSound->~T();
        mPool.Free(pSound);
    }

    u32 GetActiveCount() const {
        return mPriorityList.GetSize();
    }

    u32 GetFreeCount() const {
        return mPool.Count();
    }

    T* GetLowestPrioritySound() {
        if (mPriorityList.IsEmpty()) {
            return NULL;
        }

        return &mPriorityList.GetFront();
    }

    void InsertPriorityList(T* pSound, int priority) {
        BasicSoundPrioList::Iterator it = mPriorityList.GetBeginIter();

        for (; it != mPriorityList.GetEndIter(); ++it) {
            if (priority < it->CalcCurrentPlayerPriority()) {
                break;
            }
        }

        mPriorityList.Insert(it, pSound);
    }

    void RemovePriorityList(T* pSound) {
        mPriorityList.Erase(pSound);
    }

    void SortPriorityList() {
        if (mPriorityList.GetSize() < 2) {
            return;
        }

        ut::detail::AutoLock<OSMutex> lock(mMutex);
        BasicSoundPrioList listsByPrio[BasicSound::PRIORITY_MAX + 1];

        while (!mPriorityList.IsEmpty()) {
            BasicSound& rSound = mPriorityList.GetFront();
            mPriorityList.PopFront();
            listsByPrio[rSound.CalcCurrentPlayerPriority()].PushBack(&rSound);
        }

        for (int i = 0; i < BasicSound::PRIORITY_MAX + 1; i++) {
            while (!listsByPrio[i].IsEmpty()) {
                BasicSound& rSound = listsByPrio[i].GetFront();
                listsByPrio[i].PopFront();
                mPriorityList.PushBack(&rSound);
            }
        }
    }

    void UpdatePriority(T* pSound, int priority) {
        ut::detail::AutoLock<OSMutex> lock(mMutex);

        RemovePriorityList(pSound);
        InsertPriorityList(pSound, priority);
    }

private:
    MemoryPool<T> mPool;              // at 0x0
    BasicSoundPrioList mPriorityList; // at 0x4
    OSMutex mMutex;                   // at 0x10
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
