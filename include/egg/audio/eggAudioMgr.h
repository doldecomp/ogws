#ifndef EGG_AUDIO_AUDIO_MGR_H
#define EGG_AUDIO_AUDIO_MGR_H
#include <egg/types_egg.h>

#include <egg/audio/eggAudioArcPlayerMgr.h>
#include <egg/audio/eggAudioHeapMgr.h>
#include <egg/audio/eggAudioSystem.h>

namespace EGG {

// Forward declarations
class Heap;

/******************************************************************************
 *
 * IAudioMgr
 *
 ******************************************************************************/
class IAudioMgr {
public:
    /**************************************************************************
     * Arg
     **************************************************************************/
    struct Arg {
        Heap* pHeap; // at 0x0
        UNKWORD WORD_0x4;
        s32 soundThreadPrio;      // at 0x8
        s32 dvdThreadPrio;        // at 0xC
        u32 soundThreadStackSize; // at 0x10
        u32 dvdThreadStackSize;   // at 0x14

        Arg() {
            pHeap = NULL;

            // clang-format off
            soundThreadPrio = nw4r::snd::SoundSystem::DEFAULT_SOUND_THREAD_PRIORITY;
            dvdThreadPrio = nw4r::snd::SoundSystem::DEFAULT_DVD_THREAD_PRIORITY;
            // clang-format on

            WORD_0x4 = 0;

            soundThreadStackSize = 0;
            dvdThreadStackSize = 0;
        }
    };

public:
    virtual void initialize(Arg* pArg) {} // at 0x8
    virtual void calc() = 0;              // at 0xC

protected:
    bool mIsInitialized; // at 0x4
};

/******************************************************************************
 *
 * SimpleAudioMgr
 *
 ******************************************************************************/
class SimpleAudioMgr : public IAudioMgr,
                       public SoundHeapMgr,
                       public ArcPlayer,
                       public AudioSystem {
public:
    /**************************************************************************
     * SimpleAudioMgrArg
     **************************************************************************/
    struct SimpleAudioMgrArg : IAudioMgr::Arg {
        // TODO: How is this calculated?
        static const u32 DEFAULT_SOUND_HEAP_SIZE = 0x8CA000;

        u32 streamBlocks;  // at 0x18
        u32 soundHeapSize; // at 0x1C

        SimpleAudioMgrArg();
    };

public:
    SimpleAudioMgr();
    virtual ~SimpleAudioMgr(); // at 0x8

    virtual void initialize(Arg* pArg); // at 0x8
    virtual void calc();                // at 0xC

    virtual nw4r::snd::SoundArchivePlayer*
    openDvdArchive(const char* pPath,
                   nw4r::snd::SoundHeap* pHeap); // at 0x10

    virtual nw4r::snd::SoundArchivePlayer*
    openNandArchive(const char* pPath,
                    nw4r::snd::SoundHeap* pHeap); // at 0x14

    virtual nw4r::snd::SoundArchivePlayer*
    openCntArchive(const char* pPath, CNTHandle* pHandle,
                   nw4r::snd::SoundHeap* pHeap); // at 0x18

    virtual nw4r::snd::SoundArchivePlayer*
    setupMemoryArchive(const void* pPath,
                       nw4r::snd::SoundHeap* pHeap); // at 0x1C

    virtual void closeArchive(); // at 0x24

    virtual bool loadGroup(unsigned int id, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x28
    virtual bool loadGroup(int id, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x2C
    virtual bool loadGroup(const char* pName, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x30
};

} // namespace EGG

#endif
