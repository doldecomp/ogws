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
			struct MemoryFileStream;		
				
			const void * mMemory; // at 0x108
			detail::SoundArchiveFileReader mFileReader; // at 0x10c
			
			MemorySoundArchive();
			virtual ~MemorySoundArchive(); // at 0x8
			
			bool Setup(const void *);
			void Shutdown();
			
			virtual const void * detail_GetFileAddress(u32) const;
			virtual const void * detail_GetWaveDataFileAddress(u32) const;
			virtual int detail_GetRequiredStreamBufferSize() const;
			virtual ut::FileStream * OpenStream(void *, int, u32, u32) const; // at 0x18
			virtual ut::FileStream * OpenExtStream(void *, int, const char *, u32, u32) const; // at 0x1c
		};

		struct MemorySoundArchive::MemoryFileStream : ut::FileStream
		{
			const void * mMemory; // at 0x14
			int mSize; // at 0x18
			int mOffset; // at 0x1c
			
			MemoryFileStream(const void *, u32); //inlined

			virtual ~MemoryFileStream();
			virtual void Close();
			virtual int Read(void *, u32); // at 0x14
			virtual void Seek(s32, u32); // at 0x44
			virtual u32 GetSize() const; // at 0x40
			virtual u32 Tell() const; // at 0x58
			virtual bool CanWrite() const; // at 0x30
			virtual bool CanRead() const; // at 0x2c
			virtual bool CanAsync() const; // at 0x28
			virtual bool CanCancel() const; // at 0x54
			virtual bool CanSeek() const; // at 0x50
		};
	}
}

#endif