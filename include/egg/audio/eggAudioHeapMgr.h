#ifndef EGG_AUDIO_HEAP_MGR_H
#define EGG_AUDIO_HEAP_MGR_H
#include <egg/types_egg.h>

#include <nw4r/snd.h>

#include <revolution/OS.h>

namespace EGG {

// Forward declarations
class Allocator;
class Heap;

class SoundHeapMgr {
public:
    SoundHeapMgr() {
        // @bug Forgot to initialize GetLevel message queue???
        OSInitMessageQueue(&mLoadStateMesgQueue, mLoadStateMesgBuffer,
                           ARRAY_SIZE(mLoadStateMesgBuffer));

        OSInitMessageQueue(&mSaveStateMesgQueue, mSaveStateMesgBuffer,
                           ARRAY_SIZE(mSaveStateMesgBuffer));

        OSInitMessageQueue(&mResponseMesgQueue, mResponseMesgBuffer,
                           ARRAY_SIZE(mResponseMesgBuffer));
    }

    ~SoundHeapMgr() {
        destroySoundHeap();
    }

    virtual bool loadState(s32 id) {
        s32 level = mHeap.GetCurrentLevel();

        if (id > 0 && level >= id) {
            mHeap.LoadState(id);
            return true;
        }

        return false;
    } // at 0x8

    virtual s32 getCurrentLevel() {
        return mHeap.GetCurrentLevel();
    } // at 0xC

    virtual void stateProc() {
        OSMessage mesg;

        if (OSReceiveMessage(&mLoadStateMesgQueue, &mesg, 0)) {
            s32 id = reinterpret_cast<s32>(mesg);
            OSMessage result = reinterpret_cast<OSMessage>(loadState(id));
            OSSendMessage(&mResponseMesgQueue, result, 0);
        }

        if (OSReceiveMessage(&mSaveStateMesgQueue, &mesg, 0)) {
            OSMessage result = reinterpret_cast<OSMessage>(saveState());
            OSSendMessage(&mResponseMesgQueue, result, 0);
        }

        if (OSReceiveMessage(&mGetLevelMesgQueue, &mesg, 0)) {
            OSMessage result = reinterpret_cast<OSMessage>(getCurrentLevel());
            OSSendMessage(&mResponseMesgQueue, result, 0);
        }
    } // at 0x10

    s32 saveState() {
        return mHeap.SaveState();
    }

    nw4r::snd::SoundHeap& getSoundHeap() {
        return mHeap;
    }

    void createSoundHeap(Heap* pHeap, u32 size);
    void createSoundHeap(Allocator* pAllocator, u32 size);
    void destroySoundHeap();

private:
    nw4r::snd::SoundHeap mHeap; // at 0x4

    OSMessageQueue mGetLevelMesgQueue; // at 0x30
    OSMessage mGetLevelMesgBuffer[4];  // at 0x50

    OSMessageQueue mLoadStateMesgQueue; // at 0x60
    OSMessage mLoadStateMesgBuffer[4];  // at 0x80

    OSMessageQueue mSaveStateMesgQueue; // at 0x90
    OSMessage mSaveStateMesgBuffer[4];  // at 0xB0

    OSMessageQueue mResponseMesgQueue; // at 0xC0
    OSMessage mResponseMesgBuffer[4];  // at 0xE0
};

} // namespace EGG

#endif
