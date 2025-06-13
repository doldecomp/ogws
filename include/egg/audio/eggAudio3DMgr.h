#ifndef EGG_AUDIO_3D_MGR_H
#define EGG_AUDIO_3D_MGR_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/snd.h>

namespace EGG {

template <int N> class TAudioSound3DMgr {
public:
    struct TAudioSound3DMgrArg {
        s32 maxPrioReduction;  // at 0x0
        f32 interiorSize;      // at 0x4
        f32 maxVolumeDistance; // at 0x8
        f32 unitDistance;      // at 0xC
    };

public:
    TAudioSound3DMgr() : mListenerCount(N), mCameraCount(1) {
        mSoundArchive3D = NULL;
    }

    void initialize3D(TAudioSound3DMgrArg* arg) {
#line 63
        EGG_ASSERT(arg);

        for (int i = 0; i < N; i++) {
            mSound3DManagers[i].SetMaxPriorityReduction(arg->maxPrioReduction);

            mSound3DListeners[i].SetInteriorSize(arg->interiorSize);
            mSound3DListeners[i].SetMaxVolumeDistance(arg->maxVolumeDistance);
            mSound3DListeners[i].SetUnitDistance(arg->unitDistance);

            mSound3DManagers[i].AddListener(&mSound3DListeners[i]);
        }
    }

    void setUseArchive3D(nw4r::snd::SoundArchive* archive,
                         nw4r::snd::SoundHeap* heap) {

        mSoundArchive3D = archive;

        if (mSoundArchive3D == NULL) {
            return;
        }

#line 92
        EGG_ASSERT(heap);

        for (int i = 0; i < N; i++) {
            u32 heapSize = mSound3DManagers[i].GetRequiredMemSize(archive);
            void* pHeapBuffer = heap->Alloc(heapSize, NULL, NULL);
            mSound3DManagers[i].Setup(archive, pHeapBuffer, heapSize);
        }
    }

    void clearArchive3D() {
        mSoundArchive3D = NULL;
    }

    nw4r::snd::Sound3DManager& getSound3DManager(s32 cam_num) {
        return mSound3DManagers[cam_num];
    }

    void setListenerMatrix(s32 cam_num, const nw4r::math::MTX34& rMtx) {
#line 107
        EGG_ASSERT(cam_num<mCameraCount);

        mSound3DListeners[cam_num].SetMatrix(rMtx);
    }

    void setCameraCount(s32 cam_count) {
#line 116
        EGG_ASSERT(0<cam_count);
        EGG_ASSERT(4>=cam_count);

        mCameraCount = cam_count;
    }

private:
    nw4r::snd::Sound3DManager mSound3DManagers[N];
    nw4r::snd::Sound3DListener mSound3DListeners[N];
    nw4r::snd::SoundArchive* mSoundArchive3D;

    s32 mListenerCount;
    s32 mCameraCount;
};

} // namespace EGG

#endif
