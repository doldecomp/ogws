#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

SoundStartable::StartResult SoundStartable::detail_StartSound(
    SoundHandle* pHandle, u32 id, detail::BasicSound::AmbientArgInfo* pArgInfo,
    detail::ExternalSoundPlayer* pPlayer, const StartInfo* pStartInfo) {

    StartResult result =
        detail_SetupSound(pHandle, id, pArgInfo, pPlayer, false, pStartInfo);

    if (result != START_SUCCESS) {
        return result;
    }

    pHandle->StartPrepared();
    return START_SUCCESS;
}

SoundStartable::StartResult SoundStartable::detail_HoldSound(
    SoundHandle* pHandle, u32 id, detail::BasicSound::AmbientArgInfo* pArgInfo,
    detail::ExternalSoundPlayer* pPlayer, const StartInfo* pStartInfo) {

    if (pHandle->IsAttachedSound() && id == pHandle->GetId()) {
        pHandle->detail_GetAttachedSound()->SetAutoStopCounter(1);
        return START_SUCCESS;
    }

    StartResult result =
        detail_SetupSound(pHandle, id, pArgInfo, pPlayer, true, pStartInfo);

    if (result != START_SUCCESS) {
        return result;
    }

    pHandle->StartPrepared();
    pHandle->detail_GetAttachedSound()->SetAutoStopCounter(1);
    return START_SUCCESS;
}

SoundStartable::StartResult
SoundStartable::detail_PrepareSound(SoundHandle* handle, u32 targetID,
                                    detail::BasicSound::AmbientArgInfo* argInfo,
                                    detail::ExternalSoundPlayer* player,
                                    const StartInfo* startInfo) {
    return detail_SetupSound(handle, targetID, argInfo, player, false,
                             startInfo);
}

} // namespace snd
} // namespace nw4r
