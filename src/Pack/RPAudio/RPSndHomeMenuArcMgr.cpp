#include <Pack/RPAudio.h>

/**
 * @brief Constructor
 */
RPSndHomeMenuArcMgr::RPSndHomeMenuArcMgr()
    : EGG::ArcPlayer(&getSoundHeap()), mIsInitialized(false) {}

/**
 * @brief Destructor
 */
RPSndHomeMenuArcMgr::~RPSndHomeMenuArcMgr() {}

/**
 * @brief Mounts the provided sound archive
 *
 * @param pBinary Binary sound archive
 * @return Success
 */
bool RPSndHomeMenuArcMgr::setupArchive(const void* pBinary) {
    bool success = setupMemoryArchive(pBinary, &getSoundHeap()) != NULL;

    mIsInitialized = true;
    return success;
}

/**
 * @brief Updates the state of the sound player
 */
void RPSndHomeMenuArcMgr::calc() {
    if (!mIsInitialized) {
        return;
    }

    EGG::ArcPlayer::calc();
}
