#ifndef EGG_AUDIO_EXP_MGR_H
#define EGG_AUDIO_EXP_MGR_H
#include <egg/types_egg.h>

#include <egg/audio/eggAudio3DMgr.h>
#include <egg/audio/eggAudioFxMgr.h>
#include <egg/audio/eggAudioMgr.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

#include <revolution/CNT.h>
#include <revolution/WPAD.h>

namespace EGG {

/******************************************************************************
 *
 * SimpleAudioMgrWithSound3D
 *
 ******************************************************************************/
#if !defined(NONMATCHING)
class SimpleAudioMgrWithSound3D
    : public SimpleAudioMgr,
      public TAudioSound3DMgr<WPAD_MAX_CONTROLLERS> {
private:
    // Dummy class to instantiate necessary weak functions
    virtual ~SimpleAudioMgrWithSound3D();
};
#endif

/******************************************************************************
 *
 * SimpleAudioMgrWithFx
 *
 ******************************************************************************/
#if !defined(NONMATCHING)
class SimpleAudioMgrWithFx : public SimpleAudioMgr, public AudioFxMgr {
private:
    // Dummy class to instantiate necessary weak functions
    virtual ~SimpleAudioMgrWithFx();
};
#endif

/******************************************************************************
 *
 * ExpAudioMgr
 *
 ******************************************************************************/
class ExpAudioMgr : public SimpleAudioMgr,
                    public TAudioSound3DMgr<WPAD_MAX_CONTROLLERS>,
                    public AudioFxMgr {
public:
    struct ExpAudioMgrArg : SimpleAudioMgrArg,
                            TAudioSound3DMgrArg,
                            AudioFxMgrArg {

        // TODO(kiwi) How is this calculated?
        static const u32 DEFAULT_FX_HEAP_SIZE = 0x25800;

        ExpAudioMgrArg();
    };

public:
    ExpAudioMgr();
    virtual ~ExpAudioMgr(); // at 0x8

    virtual void initialize(Arg* pArg); // at 0x8

    virtual nw4r::snd::SoundArchivePlayer*
    setupMemoryArchive(const void* pPath,
                       nw4r::snd::SoundHeap* pHeap); // at 0x1C

    virtual void closeArchive(); // at 0x24

    virtual nw4r::snd::SoundArchivePlayer*
    openArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                SARC_STORAGE storage, CNTHandle* pHandle); // at 0xC

    virtual nw4r::snd::SoundArchivePlayer*
    setupMemoryArchive(const void* pBinary, nw4r::snd::SoundHeap* pHeap,
                       s32 /* arg2 */) {
        return setupMemoryArchive(pBinary, pHeap);
    } // at 0x20

    virtual bool loadState(s32 id) {
#line 171
        // "When the archive is open, it cannot be returned to level 1 state."
        EGG_ASSERT_MSG(id > 1 || mPlayer->IsAvailable() != true,
            "アーカイブオープン時はレベル1のステートには戻せません。");

        return SoundHeapMgr::loadState(id);
    } // at 0x8
};

} // namespace EGG

#endif
