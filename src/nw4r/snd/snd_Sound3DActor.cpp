#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

Sound3DActor::Sound3DActor(SoundArchivePlayer& rPlayer,
                           Sound3DManager& rManager)
    : detail::SoundActor(rPlayer),
      m3DManager(rManager),
      mSoundArchivePlayer(rPlayer) {}

Sound3DActor::~Sound3DActor() {
    ForEachSound(ClearUpdateCallback, false);
}

SoundStartable::StartResult
Sound3DActor::detail_SetupSound(SoundHandle* pHandle, u32 id,
                                detail::BasicSound::AmbientArgInfo* pArgInfo,
                                detail::ExternalSoundPlayer* pPlayer, bool hold,
                                const SoundStartable::StartInfo* pStartInfo) {
#pragma unused(pArgInfo)
#pragma unused(pPlayer)

    Sound3DManager::Sound3DActorParam actorParam;
    actorParam.position = mPosition;
    actorParam.userParam = mUserParam;

    SoundArchive::Sound3DParam param;
    if (mSoundArchivePlayer.GetSoundArchive()->detail_ReadSound3DParam(
            id, &param)) {
        actorParam.soundParam = param;
    }

    detail::BasicSound::AmbientArgInfo argInfo = {
        &m3DManager,                              // paramUpdateCallback
        this,                                     // argUpdateCallback
        &m3DManager,                              // argAllocaterCallback
        &actorParam,                              // arg
        sizeof(Sound3DManager::Sound3DActorParam) // argSize
    };

    StartResult result = mSoundArchivePlayer.detail_SetupSound(
        pHandle, id, &argInfo, detail_GetActorSoundPlayer(0), hold, pStartInfo);

    if (pHandle->IsAttachedSound()) {
        pHandle->detail_GetAttachedSound()->SetPanCurve(
            detail::PAN_CURVE_SINCOS);
    }

    return result;
}

void Sound3DActor::SetPosition(const math::VEC3& rPosition) {
    mPosition = rPosition;
}

void Sound3DActor::detail_Update(void* pArg, const detail::BasicSound* pSound) {
    Sound3DManager::Sound3DActorParam* pParam =
        static_cast<Sound3DManager::Sound3DActorParam*>(pArg);

    pParam->position = mPosition;
    pParam->userParam = mUserParam;
}

void Sound3DActor::ClearUpdateCallback(SoundHandle& rHandle) {
    if (rHandle.IsAttachedSound()) {
        rHandle.detail_GetAttachedSound()->ClearAmbientArgUpdateCallback();
    }
}

} // namespace snd
} // namespace nw4r
