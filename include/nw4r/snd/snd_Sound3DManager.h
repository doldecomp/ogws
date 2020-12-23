#ifndef NW4R_SND_SOUND_3D_MANAGER_H
#define NW4R_SND_SOUND_3D_MANAGER_H
#include "snd_BasicSound.h"
#include "snd_SoundArchive.h"
#include "snd_SoundActor.h"
#include "math_types.h"

namespace nw4r
{
	namespace snd
	{
		struct Sound3DManager :
			detail::BasicSound::AmbientParamUpdateCallback,
			detail::BasicSound::AmbientArgAllocaterCallback
		{
			struct Sound3DActorParam
			{
				UNKWORD WORD_0x0;
				
				SoundArchive::Sound3DParam mSound3DParam; // at 0x4
				
				math::_VEC3 mPosition; // at 0xc
				
				Sound3DActorParam();
			};
		};
	}
}

#endif