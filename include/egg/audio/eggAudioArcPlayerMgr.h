#ifndef EGG_AUDIO_ARC_PLAYER_MGR_H
#define EGG_AUDIO_ARC_PLAYER_MGR_H
#include <egg/types_egg.h>

#include <nw4r/snd.h>

#include <revolution/CNT.h>
#include <revolution/OS.h>

namespace EGG {

class ArcPlayer {
public:
    enum SARC_STORAGE {
        SARC_STORAGE_NONE,
        SARC_STORAGE_DVD,
        SARC_STORAGE_NAND,
        SARC_STORAGE_CNT,
        SARC_STORAGE_MEM
    };

public:
    explicit ArcPlayer(nw4r::snd::SoundHeap* pHeap);
    virtual ~ArcPlayer(); // at 0x8

    virtual nw4r::snd::SoundArchivePlayer*
    openArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                SARC_STORAGE storage,
                CNTHandle* pHandle); // at 0xC

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
    virtual nw4r::snd::SoundArchivePlayer*
    setupMemoryArchive(const void* pBinary, nw4r::snd::SoundHeap* pHeap,
                       s32 /* arg2 */) {
        return setupMemoryArchive(pBinary, pHeap);
    } // at 0x20

    virtual void closeArchive(); // at 0x24

    virtual bool loadGroup(unsigned int id, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x28
    virtual bool loadGroup(int id, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x2C
    virtual bool loadGroup(const char* pName, nw4r::snd::SoundHeap* pHeap,
                           u32 blockSize); // at 0x30

    virtual void calc(); // at 0x34

    virtual bool startSound(nw4r::snd::SoundHandle* pHandle, u32 id) {
        return mPlayer->StartSound(pHandle, id);
    } // at 0x38
    virtual bool startSound(nw4r::snd::SoundHandle* pHandle, unsigned int id) {
        return mPlayer->StartSound(pHandle, id);
    } // at 0x3C
    virtual bool startSound(nw4r::snd::SoundHandle* pHandle,
                            const char* pName) {

        u32 id = nw4r::snd::SoundArchive::INVALID_ID;
        if (mArchive != NULL) {
            id = changeNameToId(pName);
        }

        return mPlayer->StartSound(pHandle, id);
    } // at 0x40

    virtual bool prepareSound(nw4r::snd::SoundHandle* pHandle, u32 id) {
        return mPlayer->PrepareSound(pHandle, id);
    } // at 0x44
    virtual bool prepareSound(nw4r::snd::SoundHandle* pHandle,
                              unsigned int id) {
        return mPlayer->PrepareSound(pHandle, id);
    } // at 0x48
    virtual bool prepareSound(nw4r::snd::SoundHandle* pHandle,
                              const char* pName) {
        u32 id = nw4r::snd::SoundArchive::INVALID_ID;
        if (mArchive != NULL) {
            id = changeNameToId(pName);
        }

        return mPlayer->PrepareSound(pHandle, id);
    } // at 0x4C

    virtual bool holdSound(nw4r::snd::SoundHandle* pHandle, u32 id) {
        return mPlayer->HoldSound(pHandle, id);
    } // at 0x50
    virtual bool holdSound(nw4r::snd::SoundHandle* pHandle, unsigned int id) {
        return mPlayer->HoldSound(pHandle, id);
    } // at 0x54
    virtual bool holdSound(nw4r::snd::SoundHandle* pHandle, const char* pName) {
        u32 id = nw4r::snd::SoundArchive::INVALID_ID;
        if (mArchive != NULL) {
            id = changeNameToId(pName);
        }

        return mPlayer->HoldSound(pHandle, id);
    } // at 0x58

    bool setSteamBlocks(u32 numBlocks);
    void stopAllSound();

    u32 changeNameToId(const char* pName) {
        return mArchive->ConvertLabelStringToSoundId(pName);
    }
    const char* changeIdToName(u32 id) {
        return mArchive->GetSoundLabelString(id);
    }

    const char* getSoundWithOffsetDirect(const char* pName, u32 offset) {
        u32 id = changeNameToId(pName);
        return changeIdToName(id + offset);
    }

    nw4r::snd::SoundArchive& getSoundArchive() {
        return *mArchive;
    }
    nw4r::snd::SoundArchivePlayer& getPlayer() {
        return *mPlayer;
    }

protected:
    bool mIsOpeningArchive; // at 0x4
    bool mIsLoadingGroup;   // at 0x5

    nw4r::snd::SoundArchive* mArchive;                 // at 0x8
    nw4r::snd::DvdSoundArchive mDvdSoundArchive;       // at 0xC
    nw4r::snd::NandSoundArchive mNandSoundArchive;     // at 0x198
    nw4r::snd::MemorySoundArchive mMemorySoundArchive; // at 0x374

    nw4r::snd::SoundArchivePlayer mSoundArchivePlayer; // at 0x4C4
    nw4r::snd::SoundArchivePlayer* mPlayer;            // at 0x5A4

    nw4r::snd::SoundHeap* mSoundHeap; // at 0x5A8
    SARC_STORAGE mStorage;            // at 0x5AC
    u32 mStreamBlocks;                // at 0x5B0
};

}; // namespace EGG

#endif
