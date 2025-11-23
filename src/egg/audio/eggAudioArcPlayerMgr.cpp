// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

#include <revolution/OS.h>

namespace EGG {

ArcPlayer::ArcPlayer(nw4r::snd::SoundHeap* pHeap)
    : mIsOpeningArchive(false),
      mIsLoadingGroup(false),
      mArchive(NULL),
      mPlayer(&mSoundArchivePlayer),
      mSoundHeap(pHeap),
      mStorage(SARC_STORAGE_NONE),
      mStreamBlocks(1) {}

ArcPlayer::~ArcPlayer() {}

bool ArcPlayer::setSteamBlocks(u32 numBlocks) {
    if (mArchive == NULL) {
        mStreamBlocks = numBlocks;
        return true;
    }

    return false;
}

nw4r::snd::SoundArchivePlayer*
ArcPlayer::openArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                       SARC_STORAGE storage, CNTHandle* pHandle) {

    nw4r::snd::SoundArchivePlayer* pArchive = NULL;

    switch (storage) {
    case SARC_STORAGE_DVD: {
        pArchive = openDvdArchive(pPath, pHeap);
        break;
    }

    case SARC_STORAGE_NAND: {
        pArchive = openNandArchive(pPath, pHeap);
        break;
    }

    case SARC_STORAGE_CNT: {
        pArchive = openCntArchive(pPath, pHandle, pHeap);
        break;
    }

    default: {
#line 91
        EGG_ASSERT_MSG(false, "Unlknown Storage :%d\n", storage);
    }
    }

    return pArchive;
}

nw4r::snd::SoundArchivePlayer*
ArcPlayer::openDvdArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap) {
    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 118
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mArchive != NULL) {
        EGG_PRINT("Sound Archive is already opened\n");
        return mPlayer;
    }

    nw4r::snd::DvdSoundArchive* pDvdArchive = &mDvdSoundArchive;
    mArchive = pDvdArchive;

    if (pDvdArchive->Open(pPath)) {
        mIsOpeningArchive = true;

        u32 headerSize = pDvdArchive->GetHeaderSize();
        void* pHeaderBuffer = pHeap->Alloc(headerSize, NULL, NULL);

        if (!pDvdArchive->LoadHeader(pHeaderBuffer, headerSize)) {
            mIsOpeningArchive = false;
            return NULL;
        }

        u32 setupSize = mPlayer->GetRequiredMemSize(pDvdArchive);
        void* pSetupBuffer = pHeap->Alloc(setupSize, NULL, NULL);
#line 161
        EGG_ASSERT_MSG(pSetupBuffer != NULL, "cannot alloc setup memory %d\n", setupSize);

        u32 strmSize =
            mStreamBlocks * mPlayer->GetRequiredStrmBufferSize(pDvdArchive);
        void* pStrmBuffer = pHeap->Alloc(strmSize, NULL, NULL);
#line 165
        EGG_ASSERT_MSG(pStrmBuffer != NULL, "cannot alloc setup strm memory %d\n", strmSize);

        if (!mPlayer->Setup(pDvdArchive, pSetupBuffer, setupSize, pStrmBuffer,
                            strmSize)) {

            mIsOpeningArchive = false;
            return NULL;
        }

        u32 stringSize = pDvdArchive->GetLabelStringDataSize();
        void* pStringBuffer = pHeap->Alloc(stringSize, NULL, NULL);

        if (!pDvdArchive->LoadLabelStringData(pStringBuffer, stringSize)) {
            EGG_PRINT("openArchive : Cannot Use String Data : %s\n", pPath);
        }

        mStorage = SARC_STORAGE_DVD;
        mIsOpeningArchive = false;
        return mPlayer;
    }

    return NULL;
}

nw4r::snd::SoundArchivePlayer*
ArcPlayer::openNandArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap) {
    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 199
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mArchive != NULL) {
        EGG_PRINT("Sound Archive is already opened\n");
        return mPlayer;
    }

    nw4r::snd::NandSoundArchive* pNandArchive = &mNandSoundArchive;
    mArchive = pNandArchive;

    if (pNandArchive->Open(pPath)) {
        mIsOpeningArchive = true;

        u32 headerSize = pNandArchive->GetHeaderSize();
        void* pHeaderBuffer = pHeap->Alloc(headerSize, NULL, NULL);

        if (!pNandArchive->LoadHeader(pHeaderBuffer, headerSize)) {
            mIsOpeningArchive = false;
            return NULL;
        }

        u32 setupSize = mPlayer->GetRequiredMemSize(pNandArchive);
        void* pSetupBuffer = pHeap->Alloc(setupSize, NULL, NULL);
#line 242
        EGG_ASSERT_MSG(pSetupBuffer != NULL, "cannot alloc setup memory %d\n", setupSize);

        u32 strmSize =
            mStreamBlocks * mPlayer->GetRequiredStrmBufferSize(pNandArchive);
        void* pStrmBuffer = pHeap->Alloc(strmSize, NULL, NULL);
#line 246
        EGG_ASSERT_MSG(pStrmBuffer != NULL, "cannot alloc setup strm memory %d\n", strmSize);

        if (!mPlayer->Setup(pNandArchive, pSetupBuffer, setupSize, pStrmBuffer,
                            strmSize)) {

            mIsOpeningArchive = false;
            return NULL;
        }

        u32 stringSize = pNandArchive->GetLabelStringDataSize();
        void* pStringBuffer = pHeap->Alloc(stringSize, NULL, NULL);

        if (!pNandArchive->LoadLabelStringData(pStringBuffer, stringSize)) {
            EGG_PRINT("openArchive : Cannot Use String Data : %s\n", pPath);
        }

        mStorage = SARC_STORAGE_NAND;
        mIsOpeningArchive = false;
        return mPlayer;
    }

    return NULL;
}

nw4r::snd::SoundArchivePlayer*
ArcPlayer::openCntArchive(const char* pPath, CNTHandle* pHandle,
                          nw4r::snd::SoundHeap* pHeap) {

    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 282
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mArchive != NULL) {
        EGG_PRINT("Sound Archive is already opened\n");
        return mPlayer;
    }

    CntFile f;
    f.initiate();
    f.open(pPath, pHandle);

    u32 fileSize = f.getFileSize();
    void* pBuffer = pHeap->Alloc(fileSize, NULL, NULL);

    f.readData(pBuffer, fileSize, 0);
    DCFlushRange(pBuffer, fileSize);
    f.close();

    nw4r::snd::MemorySoundArchive* pMemoryArchive = &mMemorySoundArchive;
    mArchive = pMemoryArchive;

    if (pMemoryArchive->Setup(pBuffer)) {
        mIsOpeningArchive = true;

        u32 mramSize = mPlayer->GetRequiredMemSize(pMemoryArchive);
        void* pMramBuffer = pHeap->Alloc(mramSize, NULL, NULL);
#line 327
        EGG_ASSERT_MSG(pMramBuffer != NULL, "cannot alloc setup memory %d\n", mramSize);

        u32 strmSize =
            mStreamBlocks * mPlayer->GetRequiredStrmBufferSize(pMemoryArchive);
        void* pStrmBuffer = pHeap->Alloc(strmSize, NULL, NULL);
#line 331
        EGG_ASSERT_MSG(pStrmBuffer != NULL, "cannot alloc setup strm memory %d\n", strmSize);

        if (!mPlayer->Setup(pMemoryArchive, pMramBuffer, mramSize, pStrmBuffer,
                            strmSize)) {

            mIsOpeningArchive = false;
            return NULL;
        }

        mStorage = SARC_STORAGE_CNT;
        mIsOpeningArchive = false;
        return mPlayer;
    }

    return NULL;
}

nw4r::snd::SoundArchivePlayer*
ArcPlayer::setupMemoryArchive(const void* pBinary,
                              nw4r::snd::SoundHeap* pHeap) {

    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 361
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mArchive != NULL) {
        EGG_PRINT("Sound Archive is already opened\n");
        return mPlayer;
    }

    nw4r::snd::MemorySoundArchive* pMemoryArchive = &mMemorySoundArchive;
    mArchive = pMemoryArchive;

    if (pMemoryArchive->Setup(pBinary)) {
        mIsOpeningArchive = true;

        u32 mramSize = mPlayer->GetRequiredMemSize(pMemoryArchive);
        void* pMramBuffer = pHeap->Alloc(mramSize, NULL, NULL);
#line 392
        EGG_ASSERT_MSG(pMramBuffer != NULL, "cannot alloc setup memory %d\n", mramSize);

        u32 strmSize =
            mStreamBlocks * mPlayer->GetRequiredStrmBufferSize(pMemoryArchive);
        void* pStrmBuffer = pHeap->Alloc(strmSize, NULL, NULL);
#line 396
        EGG_ASSERT_MSG(pStrmBuffer != NULL, "cannot alloc setup strm memory %d\n", strmSize);

        if (!mPlayer->Setup(pMemoryArchive, pMramBuffer, mramSize, pStrmBuffer,
                            strmSize)) {

            mIsOpeningArchive = false;
            return NULL;
        }

        mStorage = SARC_STORAGE_MEM;
        mIsOpeningArchive = false;
        return mPlayer;
    }

    return NULL;
}

void ArcPlayer::closeArchive() {
    if (mArchive == NULL) {
        return;
    }

    switch (mStorage) {
    case SARC_STORAGE_DVD: {
        mDvdSoundArchive.Close();
        break;
    }

    case SARC_STORAGE_NAND: {
        mNandSoundArchive.Close();
        break;
    }

    case SARC_STORAGE_CNT:
    case SARC_STORAGE_MEM: {
        mMemorySoundArchive.Shutdown();
        break;
    }

    default: {
        break;
    }
    }

    mPlayer->Shutdown();
    mStorage = SARC_STORAGE_NONE;
    mArchive = NULL;
}

bool ArcPlayer::loadGroup(unsigned int id, nw4r::snd::SoundHeap* pHeap,
                          u32 blockSize) {

    if (mStorage == SARC_STORAGE_NAND || mStorage == SARC_STORAGE_CNT) {
        return true;
    }

    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 458
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mIsOpeningArchive) {
        EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
        return false;
    }

    if (!mPlayer->IsAvailable()) {
        EGG_PRINT("archive is not opened!!!\n");
        return false;
    }

    mIsLoadingGroup = true;
    bool success = mPlayer->LoadGroup(id, pHeap, blockSize) != false;
    mIsLoadingGroup = false;

    return success;
}

bool ArcPlayer::loadGroup(int id, nw4r::snd::SoundHeap* pHeap, u32 blockSize) {
    if (mStorage == SARC_STORAGE_NAND || mStorage == SARC_STORAGE_CNT) {
        return true;
    }

    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 483
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mIsOpeningArchive) {
        EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
        return false;
    }

    if (!mPlayer->IsAvailable()) {
        EGG_PRINT("archive is not opened!!!\n");
        return false;
    }

    mIsLoadingGroup = true;
    bool success = mPlayer->LoadGroup(id, pHeap, blockSize) != false;
    mIsLoadingGroup = false;

    return success;
}

bool ArcPlayer::loadGroup(const char* pName, nw4r::snd::SoundHeap* pHeap,
                          u32 blockSize) {

    if (mStorage == SARC_STORAGE_NAND || mStorage == SARC_STORAGE_CNT) {
        return true;
    }

    if (pHeap == NULL) {
        pHeap = mSoundHeap;
    }

#line 508
    EGG_ASSERT_MSG(pHeap != NULL, "Set Sound Heap\n");

    if (mIsOpeningArchive) {
        EGG_PRINT("Now Setteing (oprn archive not finished)!!!\n");
        return false;
    }

    if (!mPlayer->IsAvailable()) {
        EGG_PRINT("archive is not opened!!!\n");
        return false;
    }

    mIsLoadingGroup = true;
    bool success = mPlayer->LoadGroup(pName, pHeap, blockSize) != false;
    mIsLoadingGroup = false;

    return success;
}

void ArcPlayer::calc() {
    if (mIsOpeningArchive) {
        return;
    }

    mPlayer->Update();
}

void ArcPlayer::stopAllSound() {
    for (int i = 0; i < mPlayer->GetSoundPlayerCount(); i++) {
        mPlayer->GetSoundPlayer(i).StopAllSound(0);
    }
}

DECOMP_FORCEACTIVE(eggAudioArcPlayerMgr_cpp,
                   "playernum<getPlayer().GetSoundPlayerCount()");

} // namespace EGG
