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
				u8 BYTE_0x4;
				u8 BYTE_0x5;
			};
			
			struct SoundArchivePlayerInfo
			{
				u32 SIZE_0x0;
				char UNK_0x4[0x4];
				u32 SIZE_0x8;
				char UNK_0xC[0x8];
				u32 SIZE_0x14;
			};
			
			bool detail_ReadSound3DParam(u32, Sound3DParam *) const;
			
			bool ReadSoundArchivePlayerInfo(SoundArchivePlayerInfo *) const;
		};
	}
}

#endif