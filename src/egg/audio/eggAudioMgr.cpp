// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

#include <revolution/AI.h>
#include <revolution/AX.h>

namespace EGG {

/******************************************************************************
 *
 * SimpleAudioMgrArg
 *
 ******************************************************************************/
SimpleAudioMgr::SimpleAudioMgrArg::SimpleAudioMgrArg() {
    streamBlocks = 1;
    soundHeapSize = DEFAULT_SOUND_HEAP_SIZE;
}

/******************************************************************************
 *
 * SimpleAudioMgr
 *
 ******************************************************************************/
SimpleAudioMgr::SimpleAudioMgr() : ArcPlayer(&getSoundHeap()) {
    mIsInitialized = false;
}

SimpleAudioMgr::~SimpleAudioMgr() {}

void SimpleAudioMgr::initialize(Arg* arg_) {
#line 92
    EGG_ASSERT(arg_);

    SimpleAudioMgrArg* pArg = static_cast<SimpleAudioMgrArg*>(arg_);

    AIInit(NULL);
    AXInit();

    if (pArg->soundHeapSize > 0 && pArg->pHeap != NULL) {
        Allocator allocator(pArg->pHeap);
        createSoundHeap(&allocator, pArg->soundHeapSize);
    }

    if (pArg->soundThreadStackSize == 0 && pArg->dvdThreadStackSize == 0) {
        nw4r::snd::SoundSystem::InitSoundSystem(pArg->soundThreadPrio,
                                                pArg->dvdThreadPrio);

    } else {
        if (pArg->soundThreadStackSize == 0) {
            pArg->soundThreadStackSize =
                nw4r::snd::SoundSystem::DEFAULT_SOUND_THREAD_STACK_SIZE;
        }

        if (pArg->dvdThreadStackSize == 0) {
            pArg->dvdThreadStackSize =
                nw4r::snd::SoundSystem::DEFAULT_DVD_THREAD_STACK_SIZE;
        }

        nw4r::snd::SoundSystem::SoundSystemParam param;
        param.soundThreadPriority = pArg->soundThreadPrio;
        param.soundThreadStackSize = pArg->soundThreadStackSize;
        param.dvdThreadPriority = pArg->dvdThreadPrio;
        param.dvdThreadStackSize = pArg->dvdThreadStackSize;

        u32 workSize = nw4r::snd::SoundSystem::GetRequiredMemSize(param);
        void* pWorkBuffer = getSoundHeap().Alloc(workSize, NULL, NULL);
        nw4r::snd::SoundSystem::InitSoundSystem(param, pWorkBuffer, workSize);
    }

    setSteamBlocks(pArg->streamBlocks);
    mIsInitialized = true;
}

void SimpleAudioMgr::calc() {
    AudioSystem::calc();

    if (getResetStatus() == AudioSystem::RESET_STATUS_FINISH) {
        stopAllSound();
    }

    ArcPlayer::calc();
}

nw4r::snd::SoundArchivePlayer*
SimpleAudioMgr::openDvdArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap) {
    return ArcPlayer::openDvdArchive(pPath, pHeap);
}

nw4r::snd::SoundArchivePlayer*
SimpleAudioMgr::openNandArchive(const char* pPath,
                                nw4r::snd::SoundHeap* pHeap) {

    return ArcPlayer::openNandArchive(pPath, pHeap);
}

nw4r::snd::SoundArchivePlayer*
SimpleAudioMgr::openCntArchive(const char* pPath, CNTHandle* pHandle,
                               nw4r::snd::SoundHeap* pHeap) {

    return ArcPlayer::openCntArchive(pPath, pHandle, pHeap);
}

nw4r::snd::SoundArchivePlayer*
SimpleAudioMgr::setupMemoryArchive(const void* pPath,
                                   nw4r::snd::SoundHeap* pHeap) {
    return ArcPlayer::setupMemoryArchive(pPath, pHeap);
}

void SimpleAudioMgr::closeArchive() {
    ArcPlayer::closeArchive();
}

bool SimpleAudioMgr::loadGroup(unsigned int id, nw4r::snd::SoundHeap* pHeap,
                               u32 blockSize) {

    return ArcPlayer::loadGroup(id, pHeap, blockSize);
}

bool SimpleAudioMgr::loadGroup(int id, nw4r::snd::SoundHeap* pHeap,
                               u32 blockSize) {

    return ArcPlayer::loadGroup(id, pHeap, blockSize);
}

bool SimpleAudioMgr::loadGroup(const char* pName, nw4r::snd::SoundHeap* pHeap,
                               u32 blockSize) {

    return ArcPlayer::loadGroup(pName, pHeap, blockSize);
}

} // namespace EGG
