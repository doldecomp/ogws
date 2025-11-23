// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

namespace EGG {

/******************************************************************************
 *
 * SimpleAudioMgrWithSound3D
 *
 ******************************************************************************/
#if !defined(NONMATCHING)
SimpleAudioMgrWithSound3D::~SimpleAudioMgrWithSound3D() {}
#endif

/******************************************************************************
 *
 * SimpleAudioMgrWithFx
 *
 ******************************************************************************/
#if !defined(NONMATCHING)
SimpleAudioMgrWithFx::~SimpleAudioMgrWithFx() {}
#endif

/******************************************************************************
 *
 * ExpAudioMgr
 *
 ******************************************************************************/
ExpAudioMgr::ExpAudioMgr() {}

ExpAudioMgr::~ExpAudioMgr() {}

ExpAudioMgr::ExpAudioMgrArg::ExpAudioMgrArg() {
    maxPrioReduction = 32;
    interiorSize = 1.0f;
    maxVolumeDistance = 1.0f;
    unitDistance = 1.0f;

    heapSize[nw4r::snd::AUX_A] = DEFAULT_FX_HEAP_SIZE;
    heapSize[nw4r::snd::AUX_B] = DEFAULT_FX_HEAP_SIZE;
    heapSize[nw4r::snd::AUX_C] = DEFAULT_FX_HEAP_SIZE;
}

void ExpAudioMgr::initialize(Arg* pArg) {
    SimpleAudioMgr::initialize(pArg);

    if (!mIsInitialized) {
        return;
    }

    initialize3D(static_cast<ExpAudioMgrArg*>(pArg));

    AudioSound3DActor::setCommonPlayer(mPlayer);
    AudioSound3DActor::setCommonManager(&getSound3DManager(0));

    if (mHeap.IsValid()) {
        bool ret = initializeFx(&mHeap, static_cast<ExpAudioMgrArg*>(pArg));
#line 189
        EGG_ASSERT(ret);

        mHeap.SaveState();
    }
}

nw4r::snd::SoundArchivePlayer*
ExpAudioMgr::openArchive(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                         SARC_STORAGE storage, CNTHandle* pHandle) {

    nw4r::snd::SoundArchivePlayer* pPlayer =
        ArcPlayer::openArchive(pPath, pHeap, storage, pHandle);

    if (pPlayer != NULL) {
        setUseArchive3D(mArchive, &mHeap);
    }

    return pPlayer;
}

nw4r::snd::SoundArchivePlayer*
ExpAudioMgr::setupMemoryArchive(const void* pPath,
                                nw4r::snd::SoundHeap* pHeap) {

    nw4r::snd::SoundArchivePlayer* pPlayer =
        SimpleAudioMgr::setupMemoryArchive(pPath, pHeap);

    if (pPlayer != NULL) {
        setUseArchive3D(mArchive, &mHeap);
    }

    return pPlayer;
}

void ExpAudioMgr::closeArchive() {
    SimpleAudioMgr::closeArchive();
    clearArchive3D();
}

} // namespace EGG
