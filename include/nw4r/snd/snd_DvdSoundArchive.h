#ifndef NW4R_SND_DVD_SOUND_ARCHIVE_H
#define NW4R_SND_DVD_SOUND_ARCHIVE_H
#include <dvd.h>
#include "ut_DvdLockedFileStream.h"
#include "snd_SoundArchive.h"
#include "snd_SoundArchiveFile.h"

namespace nw4r
{
	namespace snd
	{
		struct DvdSoundArchive : SoundArchive
		{
			//sizeof(DvdFileStream) = 0x78
			struct DvdFileStream : ut::DvdLockedFileStream
			{
				int mStartOffset; // at 0x70
				int mSize; // at 0x74
				
				DvdFileStream(const DVDFileInfo *, u32, u32); //inlined
				DvdFileStream(s32, u32, u32); //inlined
				
				int Read(void *, u32); // at 0x14
				
				void Seek(s32, u32); // at 0x44
				u32 GetSize() const; // at 0x40
				u32 Tell() const; // at 0x58
			};
			
			detail::SoundArchiveFileReader mFileReader; // at 0x108
			DVDFileInfo mFileInfo; // at 0x14c
			bool mOpenFlag; // at 0x188
			
			DvdSoundArchive();
			~DvdSoundArchive(); // at 0x8
			
			bool Open(s32); //inlined
			bool Open(const char *);
			
			void Close();
			
			ut::FileStream * OpenStream(void *, int, u32, u32) const; // at 0x18
			ut::FileStream * OpenExtStream(void *, int, const char *, u32, u32) const; // at 0x1c
			
			int detail_GetRequiredStreamBufferSize() const; // at 0x14
			
			bool LoadHeader(void *, u32);
			bool LoadLabelStringData(void *, u32);
			
			const void * detail_GetWaveDataFileAddress(u32) const;
			const void * detail_GetFileAddress(u32) const;
		};
	}
}

#endif