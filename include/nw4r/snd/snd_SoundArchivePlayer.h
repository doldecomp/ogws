#ifndef NW4R_SND_SOUND_ARCHIVE_PLAYER_H
#define NW4R_SND_SOUND_ARCHIVE_PLAYER_H
#include "snd_SoundStartable.h"
#include "snd_DisposeCallback.h"
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundArchivePlayer : detail::DisposeCallback, SoundStartable
		{
			SoundArchive * GetSoundArchive() const;
			
			UNKWORD detail_SetupSound(SoundHandle *,
				u32,
				detail::BasicSound::AmbientArgInfo *,
				detail::ExternalSoundPlayer *,
				bool,
				const StartInfo *);
		};
	}
}

#endif