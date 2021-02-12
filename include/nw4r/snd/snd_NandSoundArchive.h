#ifndef NW4R_SND_NAND_SOUND_ARCHIVE_H
#define NW4R_SND_NAND_SOUND_ARCHIVE_H
#include <nand.h>
#include "ut_NandFileStream.h"
#include "snd_SoundArchive.h"
#include "snd_SoundArchiveFile.h"

namespace nw4r
{
	namespace snd
	{
		struct NandSoundArchive : SoundArchive
		{
			//sizeof(DvdFileStream) = 0x174
			struct NandFileStream : ut::NandFileStream
			{
				int mStartOffset; // at 0x16c
				int mSize; // at 0x170
				
				NandFileStream(const NANDFileInfo *, u32, u32); //inlined
				NandFileStream(const char *, u32, u32); //inlined
				
				int Read(void *, u32); // at 0x14
				
				void Seek(s32, u32); // at 0x44
				u32 GetSize() const; // at 0x40
				u32 Tell() const; // at 0x58
			};
			
			detail::SoundArchiveFileReader mFileReader; // at 0x108
			NANDFileInfo mFileInfo; // at 0x14c
			bool mOpenFlag; // at 0x1d8
			
			NandSoundArchive();
			~NandSoundArchive(); // at 0x8
			
			bool Open(const char *);
			
			void Close();
			
			ut::FileStream * OpenStream(void *, int, u32, u32) const; // at 0x18
			ut::FileStream * OpenExtStream(void *, int, const char *, u32, u32) const; // at 0x1c
			
			int detail_GetRequiredStreamBufferSize() const; // at 0x14
			
			bool LoadFileHeader();
			
			bool LoadHeader(void *, u32);
			bool LoadLabelStringData(void *, u32);
			
			const void * detail_GetWaveDataFileAddress(u32) const;
			const void * detail_GetFileAddress(u32) const;
		};
	}
}

#endif