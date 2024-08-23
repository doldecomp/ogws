#pragma ipa file
#pragma use_lmw_stmw on
#include "eggAudioArcPlayerMgr.h"
#include "eggAssert.h"
#include "eggCntFile.h"
#include "snd_SoundPlayer.h"
#include <revolution/OS/OSCache.h>

namespace EGG
{
    using namespace nw4r;

    ArcPlayer::ArcPlayer(snd::SoundHeap *heap)
        : mIsOpeningArchive(false), mIsLoadingGroup(false), mOpenSndArchive(NULL)
    {
        mActiveSndArchivePlayer = &mSndArchivePlayer;
        mSoundHeap = heap;
        mStorage = STORAGE_NONE;
        mSteamBlocks = 1;
    }
    
    ArcPlayer::~ArcPlayer() 
    {

    }
    
    bool ArcPlayer::setSteamBlocks(u32 n) 
    {
        if (!mOpenSndArchive)
        {
            mSteamBlocks = n;
            return true;
        }

        return false;
    }
    
    UNKTYPE * ArcPlayer::openArchive(const char *name, snd::SoundHeap *heap,
        SARC_STORAGE storage, CNTHandle *handle) 
    {
        UNKTYPE *ret = NULL;

        switch(storage)
        {
            case STORAGE_DVD:
                ret = openDvdArchive(name, heap);
                break;

            case STORAGE_NAND:
                ret = openNandArchive(name, heap);
                break;

            case STORAGE_CNT:
                ret = openCntArchive(name, handle, heap);
                break;

            default:
                #line 91
                EGG_ASSERT_MSG(false, "Unlknown Storage :%d\n", storage);
        }

        return ret;
    }
    
    UNKTYPE * ArcPlayer::openDvdArchive(const char *name, snd::SoundHeap *heap) 
    {
        u32 headerBufSize;

        if (!heap) heap = mSoundHeap;
        #line 118
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mOpenSndArchive)
        {
            EGG_PRINT("Sound Archive is already opened\n");
            return mActiveSndArchivePlayer;
        }
        
        snd::DvdSoundArchive *dvdSndArchive = &mDvdSndArchive;
        mOpenSndArchive = dvdSndArchive;
        
        if (dvdSndArchive->Open(name))
        {
            mIsOpeningArchive = true;

            headerBufSize = dvdSndArchive->GetHeaderSize();
            void *headerBuf = heap->Alloc(headerBufSize, NULL, NULL);
            if (!dvdSndArchive->LoadHeader(headerBuf, headerBufSize))
            {
                mIsOpeningArchive = false;
                return NULL;
            }

            u32 setupBufSize = mActiveSndArchivePlayer->GetRequiredMemSize(dvdSndArchive);
            void *setupBuf = heap->Alloc(setupBufSize, NULL, NULL);
            #line 161
            EGG_ASSERT_MSG(setupBuf, "cannot alloc setup memory %d\n", setupBufSize);

            u32 strmBufSize = mSteamBlocks * mActiveSndArchivePlayer->GetRequiredStrmBufferSize(dvdSndArchive);
            void *strmBuf = heap->Alloc(strmBufSize, NULL, NULL);
            #line 165
            EGG_ASSERT_MSG(strmBuf, "cannot alloc setup strm memory %d\n", strmBufSize);

            if (!mActiveSndArchivePlayer->Setup(dvdSndArchive, setupBuf, setupBufSize, strmBuf, strmBufSize))
            {
                mIsOpeningArchive = false;
                return NULL;
            }

            headerBufSize = dvdSndArchive->GetLabelStringDataSize();
            void *stringDataBuf = heap->Alloc(headerBufSize, NULL, NULL);
            if (!dvdSndArchive->LoadLabelStringData(stringDataBuf, headerBufSize))
            {
                EGG_PRINT("openArchive : Cannot Use String Data : %s\n", name);
            }

            mStorage = STORAGE_DVD;
            mIsOpeningArchive = false;
            return mActiveSndArchivePlayer;
        }

        return NULL;
    }
    
    UNKTYPE * ArcPlayer::openNandArchive(const char *name, snd::SoundHeap *heap) 
    {
        u32 headerBufSize;

        if (!heap) heap = mSoundHeap;
        #line 199
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mOpenSndArchive)
        {
            EGG_PRINT("Sound Archive is already opened\n");
            return mActiveSndArchivePlayer;
        }
        
        snd::NandSoundArchive *nandSndArchive = &mNandSndArchive;
        mOpenSndArchive = nandSndArchive;
        
        if (nandSndArchive->Open(name))
        {
            mIsOpeningArchive = true;

            headerBufSize = nandSndArchive->GetHeaderSize();
            void *headerBuf = heap->Alloc(headerBufSize, NULL, NULL);
            if (!nandSndArchive->LoadHeader(headerBuf, headerBufSize))
            {
                mIsOpeningArchive = false;
                return NULL;
            }

            u32 setupBufSize = mActiveSndArchivePlayer->GetRequiredMemSize(nandSndArchive);
            void *setupBuf = heap->Alloc(setupBufSize, NULL, NULL);
            #line 242
            EGG_ASSERT_MSG(setupBuf, "cannot alloc setup memory %d\n", setupBufSize);

            u32 strmBufSize = mSteamBlocks * mActiveSndArchivePlayer->GetRequiredStrmBufferSize(nandSndArchive);
            void *strmBuf = heap->Alloc(strmBufSize, NULL, NULL);
            #line 246
            EGG_ASSERT_MSG(strmBuf, "cannot alloc setup strm memory %d\n", strmBufSize);

            if (!mActiveSndArchivePlayer->Setup(nandSndArchive, setupBuf, setupBufSize, strmBuf, strmBufSize))
            {
                mIsOpeningArchive = false;
                return NULL;
            }

            headerBufSize = nandSndArchive->GetLabelStringDataSize();
            void *stringDataBuf = heap->Alloc(headerBufSize, NULL, NULL);
            if (!nandSndArchive->LoadLabelStringData(stringDataBuf, headerBufSize))
            {
                EGG_PRINT("openArchive : Cannot Use String Data : %s\n", name);
            }

            mStorage = STORAGE_NAND;
            mIsOpeningArchive = false;
            return mActiveSndArchivePlayer;
        }

        return NULL;
    }
    
    UNKTYPE * ArcPlayer::openCntArchive(const char *name, CNTHandle *handle, snd::SoundHeap *heap) 
    {
        if (!heap) heap = mSoundHeap;
        #line 282
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");
    
        if (mOpenSndArchive)
        {
            EGG_PRINT("Sound Archive is already opened\n");
            return mActiveSndArchivePlayer;
        }

        CntFile f;
        f.initiate();
        f.open(name, handle);

        UNKWORD fileSize = f.getFileSize();
        void *buf = heap->Alloc(fileSize, NULL, NULL);
        f.readData(buf, fileSize, 0);
        DCFlushRange(buf, fileSize);
        f.close();

        snd::MemorySoundArchive *memSndArchive = &mMemorySndArchive;
        mOpenSndArchive = memSndArchive;

        if (memSndArchive->Setup(buf))
        {
            mIsOpeningArchive = true;
            
            u32 neededForMem = mActiveSndArchivePlayer->GetRequiredMemSize(memSndArchive);
            void *memBuf = heap->Alloc(neededForMem, NULL, NULL);
            #line 327
            EGG_ASSERT_MSG(memBuf, "cannot alloc setup memory %d\n", neededForMem);

            u32 neededForStrm = mSteamBlocks * mActiveSndArchivePlayer->GetRequiredStrmBufferSize(memSndArchive);
            void *strmBuf = heap->Alloc(neededForStrm, NULL, NULL);
            #line 331
            EGG_ASSERT_MSG(strmBuf, "cannot alloc setup strm memory %d\n", neededForStrm);

            if (!mActiveSndArchivePlayer->Setup(memSndArchive, memBuf, neededForMem, strmBuf, neededForStrm))
            {
               mIsOpeningArchive = false;
                return NULL;
            }

            mStorage = STORAGE_CNT;
            mIsOpeningArchive = false;
            return mActiveSndArchivePlayer;
        }

        return NULL;
    }

    UNKTYPE * ArcPlayer::setupMemoryArchive(const void *work, snd::SoundHeap *heap) 
    {
        if (!heap) heap = mSoundHeap;
        #line 361
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mOpenSndArchive)
        {
            EGG_PRINT("Sound Archive is already opened\n");
            return mActiveSndArchivePlayer;
        }

        snd::MemorySoundArchive *memSndArchive = &mMemorySndArchive;
        mOpenSndArchive = memSndArchive;

        if (memSndArchive->Setup(work))
        {
            mIsOpeningArchive = true;
            
            u32 neededForMem = mActiveSndArchivePlayer->GetRequiredMemSize(memSndArchive);
            void *memBuf = heap->Alloc(neededForMem, NULL, NULL);
            #line 392
            EGG_ASSERT_MSG(memBuf, "cannot alloc setup memory %d\n", neededForMem);

            u32 neededForStrm = mSteamBlocks * mActiveSndArchivePlayer->GetRequiredStrmBufferSize(memSndArchive);
            void *strmBuf = heap->Alloc(neededForStrm, NULL, NULL);
            #line 396
            EGG_ASSERT_MSG(strmBuf, "cannot alloc setup strm memory %d\n", neededForStrm);

            if (!mActiveSndArchivePlayer->Setup(memSndArchive, memBuf, neededForMem, strmBuf, neededForStrm))
            {
                mIsOpeningArchive = false;
                return NULL;
            }

            mStorage = STORAGE_MEM;
            mIsOpeningArchive = false;
            return mActiveSndArchivePlayer;
        }

        return NULL;
    }
    
    UNKTYPE ArcPlayer::closeArchive() 
    {
        if (!mOpenSndArchive) return;

        switch(mStorage)
        {
            case STORAGE_DVD:
                mDvdSndArchive.Close();
                break;

            case STORAGE_NAND:
                mNandSndArchive.Close();
                break;

            case STORAGE_CNT:
            case STORAGE_MEM:
                mMemorySndArchive.Shutdown();
                break;
        }

        mActiveSndArchivePlayer->Shutdown();

        mStorage = STORAGE_NONE;
        mOpenSndArchive = NULL;
    }
    
    bool ArcPlayer::loadGroup(unsigned int id, snd::SoundHeap *heap, u32 loadBlockSize) 
    {
        if (mStorage == STORAGE_NAND || mStorage == STORAGE_CNT) return true;
        
        if (!heap) heap = mSoundHeap;
        #line 458
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mIsOpeningArchive)
        {
            EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
            return false;
        }
        else
        {
            if (!mActiveSndArchivePlayer->IsAvailable())
            {
                EGG_PRINT("archive is not opened!!!\n");
                return false;
            }

            mIsLoadingGroup = true;
            UNKWORD result = mActiveSndArchivePlayer->LoadGroup((u32)id, heap, loadBlockSize);
            mIsLoadingGroup = false;
            return (result != 0);
        }
    }
    
    bool ArcPlayer::loadGroup(int id, snd::SoundHeap * heap, u32 loadBlockSize) 
    {
        if (mStorage == STORAGE_NAND || mStorage == STORAGE_CNT) return true;
        
        if (!heap) heap = mSoundHeap;
        #line 483
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mIsOpeningArchive)
        {
            EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
            return false;
        }
        else
        {
            if (!mActiveSndArchivePlayer->IsAvailable())
            {
                EGG_PRINT("archive is not opened!!!\n");
                return false;
            }

            mIsLoadingGroup = true;
            UNKWORD result = mActiveSndArchivePlayer->LoadGroup((u32)id, heap, loadBlockSize);
            mIsLoadingGroup = false;
            return (result != 0);
        }
    }
    
    bool ArcPlayer::loadGroup(const char *name, snd::SoundHeap *heap, u32 loadBlockSize) 
    {
        if (mStorage == STORAGE_NAND || mStorage == STORAGE_CNT) return true;
        
        if (!heap) heap = mSoundHeap;
        #line 508
        EGG_ASSERT_MSG(heap, "Set Sound Heap\n");

        if (mIsOpeningArchive)
        {
            EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
            return false;
        }
        else
        {
            if (!mActiveSndArchivePlayer->IsAvailable())
            {
                EGG_PRINT("archive is not opened!!!\n");
                return false;
            }

            mIsLoadingGroup = true;
            bool b = (mActiveSndArchivePlayer->LoadGroup(name, heap, loadBlockSize) != 0);
            mIsLoadingGroup = false;
            return b;
        }
    }
    
    void ArcPlayer::calc() 
    {
        if (!mIsOpeningArchive) mActiveSndArchivePlayer->Update();
    }

    void ArcPlayer::stopAllSound() 
    {
        for (int i = 0; i < mActiveSndArchivePlayer->WORD_0x30; i++)
        {
            mActiveSndArchivePlayer->GetSoundPlayer(i)->StopAllSound(0);
        }
    }
}

UNKTYPE UNUSED_ASSERTS()
{
    EGG_PRINT("playernum<getPlayer().GetSoundPlayerCount()");
}