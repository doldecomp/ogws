#ifndef EGG_AUDIO_ARCPLAYER_MGR_H
#define EGG_AUDIO_ARCPLAYER_MGR_H
#include "types_egg.h"
#include "types_nw4r.h"
#include "snd_SoundHeap.h"
#include "snd_DvdSoundArchive.h"
#include "snd_NandSoundArchive.h"
#include "snd_MemorySoundArchive.h"
#include "snd_SoundArchivePlayer.h"
#include <revolution/CNT/cnt.h>

namespace EGG
{
    class ArcPlayer
    {
    public:
        enum SARC_STORAGE
        {
            STORAGE_NONE,
            STORAGE_DVD,
            STORAGE_NAND,
            STORAGE_CNT,
            STORAGE_MEM
        };

        ArcPlayer(nw4r::snd::SoundHeap *);
        virtual ~ArcPlayer(); // at 0x8
        bool setSteamBlocks(u32);
        void stopAllSound();

        u32 changeNameToId(const char *name) { return mOpenSndArchive->ConvertLabelStringToSoundId(name); }
        nw4r::snd::SoundArchivePlayer * getPlayer() { return mActiveSndArchivePlayer; }

        virtual UNKTYPE * openArchive(const char *, nw4r::snd::SoundHeap *, SARC_STORAGE, CNTHandle *); // at 0xC
        virtual UNKTYPE * openDvdArchive(const char *, nw4r::snd::SoundHeap *); // at 0x10
        virtual UNKTYPE * openNandArchive(const char *, nw4r::snd::SoundHeap *); // at 0x14
        virtual UNKTYPE * openCntArchive(const char *, CNTHandle *, nw4r::snd::SoundHeap *); // at 0x18
        virtual UNKTYPE * setupMemoryArchive(const void *, nw4r::snd::SoundHeap *); // at 0x1C

        virtual UNKTYPE * setupMemoryArchive(const void *p, nw4r::snd::SoundHeap *heap, s32) // at 0x20
        { 
            return setupMemoryArchive(p, heap);
        }

        virtual UNKTYPE closeArchive(); // at 0x24
        virtual bool loadGroup(unsigned int, nw4r::snd::SoundHeap *, u32); // at 0x28
        virtual bool loadGroup(int, nw4r::snd::SoundHeap *, u32); // at 0x2C
        virtual bool loadGroup(const char *, nw4r::snd::SoundHeap *, u32); // at 0x30   
        virtual void calc(); // at 0x34

        virtual bool startSound(nw4r::snd::SoundHandle *handle, u32 id) // at 0x38
        {
            return mActiveSndArchivePlayer->StartSound(handle, id);
        }

        virtual bool startSound(nw4r::snd::SoundHandle *handle, unsigned int id) // at 0x3C
        {
            return ArcPlayer::startSound(handle, (u32)id);
        }

        virtual bool startSound(nw4r::snd::SoundHandle *handle, const char *name)  // at 0x40
        {
            u32 id = -1;
            if (mOpenSndArchive) id = changeNameToId(name);

            return ArcPlayer::startSound(handle, id);
        }

        virtual bool prepareSound(nw4r::snd::SoundHandle *handle, u32 id) // at 0x44
        {
            return mActiveSndArchivePlayer->PrepareSound(handle, id);
        }

        virtual bool prepareSound(nw4r::snd::SoundHandle *handle, unsigned int id) // at 0x48
        {
            return ArcPlayer::prepareSound(handle, (u32)id);
        }

        virtual bool prepareSound(nw4r::snd::SoundHandle *handle, const char *name) // at 0x4C
        {
            u32 id = -1;
            if (mOpenSndArchive) id = changeNameToId(name);

            return ArcPlayer::prepareSound(handle, id);
        }

        virtual bool holdSound(nw4r::snd::SoundHandle *handle, u32 id) // at 0x50
        {
            return mActiveSndArchivePlayer->HoldSound(handle, id);
        }

        virtual bool holdSound(nw4r::snd::SoundHandle *handle, unsigned int id) // at 0x54
        {
            return ArcPlayer::holdSound(handle, (u32)id);
        }

        virtual bool holdSound(nw4r::snd::SoundHandle *handle, const char *name) // at 0x58
        {
            u32 id = -1;
            if (mOpenSndArchive) id = changeNameToId(name);

            return ArcPlayer::holdSound(handle, id);
        }

    private:
        bool mIsOpeningArchive; // at 0x4
        bool mIsLoadingGroup; // at 0x5
        nw4r::snd::SoundArchive *mOpenSndArchive; // at 0x8
        nw4r::snd::DvdSoundArchive mDvdSndArchive; // at 0xC
        nw4r::snd::NandSoundArchive mNandSndArchive; // at 0x198
        nw4r::snd::MemorySoundArchive mMemorySndArchive; // at 0x374
        nw4r::snd::SoundArchivePlayer mSndArchivePlayer; // at 0x4C4
        nw4r::snd::SoundArchivePlayer *mActiveSndArchivePlayer; // at 0x5A4
        nw4r::snd::SoundHeap *mSoundHeap; // at 0x5A8
        SARC_STORAGE mStorage; // at 0x5AC
        u32 mSteamBlocks; // at 0x5B0
    };
};

#endif