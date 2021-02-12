#ifndef NW4R_SND_MEMORY_SOUND_ARCHIVE_H
#define NW4R_SND_MEMORY_SOUND_ARCHIVE_H
#include "ut_FileStream.h"
#include "snd_SoundArchive.h"
#include "snd_SoundArchiveFile.h"

namespace nw4r
{
	namespace snd
	{
		struct MemorySoundArchive : SoundArchive
		{
			struct MemoryFileStream : ut::FileStream
			{
				const void * mMemory; // at 0x14
				int mSize; // at 0x18
				int mOffset; // at 0x1c
				
				MemoryFileStream(const void *, u32); //inlined
				
				void Close();
				
				int Read(void *, u32); // at 0x14
				
				void Seek(s32, u32); // at 0x44
				
				u32 GetSize() const; // at 0x40
				u32 Tell() const; // at 0x58
				
				bool CanWrite() const; // at 0x30
				
				bool CanRead() const; // at 0x2c
				bool CanAsync() const; // at 0x28
				bool CanCancel() const; // at 0x54
				bool CanSeek() const; // at 0x50
			};
			
			const void * mMemory; // at 0x108
			detail::SoundArchiveFileReader mFileReader; // at 0x10c
			
			MemorySoundArchive();
			~MemorySoundArchive(); // at 0x8
			
			bool Setup(const void *);
			void Shutdown();
			
			const void * detail_GetFileAddress(u32) const;
			const void * detail_GetWaveDataFileAddress(u32) const;
			
			ut::FileStream * OpenStream(void *, int, u32, u32) const; // at 0x18
			ut::FileStream * OpenExtStream(void *, int, const char *, u32, u32) const; // at 0x1c
			
			int detail_GetRequiredStreamBufferSize() const;
		};
	}
}

#endif