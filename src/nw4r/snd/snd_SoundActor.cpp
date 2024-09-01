#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

SoundStartable::StartResult
SoundActor::detail_SetupSound(SoundHandle* pHandle, u32 id,
                              detail::BasicSound::AmbientArgInfo* pArgInfo,
                              detail::ExternalSoundPlayer* pPlayer, bool hold,
                              const StartInfo* pStartInfo) {

    return mStartable.detail_SetupSound(
        pHandle, id, NULL, detail_GetActorSoundPlayer(0), hold, pStartInfo);
}

} // namespace detail
} // namespace snd
} // namespace nw4r
