#include <Pack/RPAudio.h>

#include <nw4r/ut.h>

/******************************************************************************
 *
 * RPSndAudioActorBase
 *
 ******************************************************************************/

/**
 * @brief List of all active actors
 */
nw4r::ut::List RPSndAudioActorBase::sActorList;

/******************************************************************************
 *
 * RPSndObjMgr
 *
 ******************************************************************************/

/**
 * @brief Fades out all active sounds in the specified number of frames
 *
 * @param frames Fade out time
 */
void RPSndObjMgr::stopAllActorSound(int frames) {
    RP_NW4R_LIST_FOREACH (RPSndAudioActorBase, it,
                          RPSndAudioActorBase::sActorList) {
        it->stopAllSound(frames);
    }
}
