#include "snd_SoundStartable.h"
#include "snd_SoundHandle.h"

namespace nw4r
{
    namespace snd
    {
        UNKWORD SoundStartable::detail_StartSound(SoundHandle *handle,
            u32 targetID,
            detail::BasicSound::AmbientArgInfo *argInfo,
            detail::ExternalSoundPlayer *player,
            const StartInfo *startInfo)
        {
            UNKWORD ret = detail_SetupSound(handle, targetID, argInfo, player, false, startInfo);
            if (ret != 0) return ret;

            handle->StartPrepared();
            
            return 0;
        }

        UNKWORD SoundStartable::detail_HoldSound(SoundHandle *handle,
            u32 targetID,
            detail::BasicSound::AmbientArgInfo *argInfo,
            detail::ExternalSoundPlayer *player,
            const StartInfo *startInfo)
        {
            if (handle->IsAttachedSound())
            {
                if (targetID == handle->GetId())
                {
                    handle->detail_GetAttachedSound()->SetAutoStopCounter(1);
                    return 0;
                }
            }

            UNKWORD ret = detail_SetupSound(handle, targetID, argInfo, player, true, startInfo);
            if (ret != 0) return ret;

            handle->StartPrepared();
            handle->detail_GetAttachedSound()->SetAutoStopCounter(1);

            return 0;
        }

        UNKWORD SoundStartable::detail_PrepareSound(SoundHandle *handle,
            u32 targetID,
            detail::BasicSound::AmbientArgInfo *argInfo,
            detail::ExternalSoundPlayer *player,
            const StartInfo *startInfo)
        {
            return detail_SetupSound(handle, targetID, argInfo, player, false, startInfo);
        }
    }
}