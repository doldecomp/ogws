#ifndef NW4R_SND_SOUND_ARCHIVE_H
#define NW4R_SND_SOUND_ARCHIVE_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundArchive
		{
			struct Sound3DParam
			{
				UNKWORD WORD_0x0;
				char BYTE_0x4;
				char BYTE_0x5;
			};
			
			bool detail_ReadSound3DParam(u32, Sound3DParam *) const;
		};
	}
}

#endif