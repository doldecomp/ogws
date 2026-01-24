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
    RPSndAudioActorBase* pIt = static_cast<RPSndAudioActorBase*>(
        nw4r::ut::List_GetFirst(&RPSndAudioActorBase::sActorList));

    for (; pIt != NULL;
         pIt = static_cast<RPSndAudioActorBase*>(
             nw4r::ut::List_GetNext(&RPSndAudioActorBase::sActorList, pIt))) {

        pIt->stopAllSound(frames);
    }
}
