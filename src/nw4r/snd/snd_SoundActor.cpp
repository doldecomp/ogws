#include "snd_SoundActor.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			UNKWORD SoundActor::detail_SetupSound(SoundHandle * r4,
				u32 r5,
				detail::BasicSound::AmbientArgInfo *,
				detail::ExternalSoundPlayer *,
				bool r8,
				const StartInfo * r9)
			{
				return mStartable.detail_SetupSound(r4, r5, NULL, mPlayers, r8, r9);
			}
		}
	}
}