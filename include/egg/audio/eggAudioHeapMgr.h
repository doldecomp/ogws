#ifndef EGG_AUDIO_HEAP_MGR_H
#define EGG_AUDIO_HEAP_MGR_H
#include "types_egg.h"
#include "snd_SoundHeap.h"

namespace EGG
{
    class SoundHeapMgr
    {
    public:
        // TO-DO: Implement these weak funcs
        virtual UNKWORD loadState(s32); // at 0x8
        virtual UNKWORD getCurrentLevel(); // at 0xC
        virtual void saveState(); // at 0x10

        nw4r::snd::SoundHeap * getSoundHeap() { return &mHeap; }

        void createSoundHeap(Heap *, u32);
        void createSoundHeap(Allocator *, u32);
        void destroySoundHeap();

    private:
        nw4r::snd::SoundHeap mHeap; // at 0x4
    };
}

#endif