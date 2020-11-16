#ifndef NW4R_SND_REMOTE_SPEAKER_MANAGER_H
#define NW4R_SND_REMOTE_SPEAKER_MANAGER_H
#include "snd_RemoteSpeaker.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct RemoteSpeakerManager
			{
				static RemoteSpeakerManager * GetInstance();
				
				RemoteSpeaker * GetRemoteSpeaker(int);
			};
		}
	}
}

#endif