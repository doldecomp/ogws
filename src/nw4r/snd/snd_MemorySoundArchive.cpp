#ifdef __DECOMP_NON_MATCHING
#include <string.h>
#include <new>
#include "ut_algorithm.h"
#include "snd_MemorySoundArchive.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		MemorySoundArchive::MemorySoundArchive() : mMemory(NULL) {}
		
		MemorySoundArchive::~MemorySoundArchive() {}
		
		bool MemorySoundArchive::Setup(const void * pMemory)
		{
			mFileReader.Init(pMemory);
			
			SoundArchive::Setup(&mFileReader);
			
			const void * pInfoChunk = AddOffsetToPtr<u32>(pMemory, mFileReader.GetInfoChunkOffset());
			
			mFileReader.SetInfoChunk(pInfoChunk, mFileReader.GetInfoChunkSize());
			
			const void * pStringChunk = AddOffsetToPtr<u32>(pMemory, mFileReader.GetLabelStringChunkOffset());
			
			mFileReader.SetStringChunk(pStringChunk, mFileReader.GetLabelStringChunkSize());
			
			mMemory = pMemory;
			
			return true;
		}
		
		void MemorySoundArchive::Shutdown()
		{
			mMemory = NULL;
			SoundArchive::Shutdown();
		}
		
		const void * MemorySoundArchive::detail_GetFileAddress(u32 fileIndex) const
		{
			SoundArchive::GroupInfo groupInfo; // at 0x28
			SoundArchive::GroupItemInfo groupItemInfo; // at 0x10
			SoundArchive::FilePos filePos; // at 0x8
			
			if (!detail_ReadFilePos(fileIndex, 0, &filePos)) return NULL;
			
			if (!detail_ReadGroupInfo(filePos.mGroupIndex, &groupInfo)) return NULL;
			
			if (!detail_ReadGroupItemInfo(filePos.mGroupIndex, filePos.mGroupItemIndex, &groupItemInfo)) return NULL;
			
			if (groupInfo.mExternalFileName) return NULL;
			
			return AddOffsetToPtr<u32>(mMemory, groupInfo.INT_0x8 + groupItemInfo.INT_0x4);
		}
		
		const void * MemorySoundArchive::detail_GetWaveDataFileAddress(u32 fileIndex) const
		{
			SoundArchive::GroupInfo groupInfo; // at 0x28
			SoundArchive::GroupItemInfo groupItemInfo; // at 0x10
			SoundArchive::FilePos filePos; // at 0x8
			
			if (!detail_ReadFilePos(fileIndex, 0, &filePos)) return NULL;
			
			if (!detail_ReadGroupInfo(filePos.mGroupIndex, &groupInfo)) return NULL;
			
			if (!detail_ReadGroupItemInfo(filePos.mGroupIndex, filePos.mGroupItemIndex, &groupItemInfo)) return NULL;
			
			if (groupInfo.mExternalFileName) return NULL;
			
			return AddOffsetToPtr<u32>(mMemory, groupInfo.INT_0x10 + groupItemInfo.INT_0xC);
		}
		
		MemorySoundArchive::MemoryFileStream::MemoryFileStream(const void * pMemory, u32 size)
			: mMemory(pMemory), mSize(size), mOffset(0)
		{}
		
		FileStream * MemorySoundArchive::OpenStream(void * pBuffer, int bufferSize, u32 startOffset, u32 streamSize) const
		{
			if (!mMemory) return NULL;
			
			if (bufferSize < sizeof(MemoryFileStream)) return NULL;
			
			return new (pBuffer) MemoryFileStream(AddOffsetToPtr<u32>(mMemory, startOffset), streamSize);
		}
		
		FileStream * MemorySoundArchive::OpenExtStream(void *, int, const char *, u32, u32) const
		{
			return NULL;
		}
		
		int MemorySoundArchive::detail_GetRequiredStreamBufferSize() const
		{
			return sizeof(MemoryFileStream);
		}
		
		void MemorySoundArchive::MemoryFileStream::Close()
		{
			mMemory = NULL;
			mSize = 0;
			mOffset = 0;
		}
		
		int MemorySoundArchive::MemoryFileStream::Read(void * pBuffer, u32 count)
		{
			u32 bytesRead = Min<u32>(count, mSize - mOffset);
			
			memcpy(pBuffer, AddOffsetToPtr<u32>(mMemory, mOffset), bytesRead);
			
			return bytesRead;
		}
		
		void MemorySoundArchive::MemoryFileStream::Seek(s32 offset, u32 origin)
		{
			switch (origin)
			{
				case 0:
					mOffset = offset;
					break;
				case 1:
					mOffset += offset;
					break;
				case 2:
					mOffset = mSize - offset;
					break;
				default:
					return;
			}
		}
		
		u32 MemorySoundArchive::MemoryFileStream::GetSize() const
		{
			return mSize;
		}
		
		u32 MemorySoundArchive::MemoryFileStream::Tell() const
		{
			return mOffset;
		}
		
		bool MemorySoundArchive::MemoryFileStream::CanWrite() const
		{
			return true;
		}
		
		bool MemorySoundArchive::MemoryFileStream::CanRead() const
		{
			return true;
		}
		
		bool MemorySoundArchive::MemoryFileStream::CanAsync() const
		{
			return false;
		}
		
		bool MemorySoundArchive::MemoryFileStream::CanCancel() const
		{
			return true;
		}
		
		bool MemorySoundArchive::MemoryFileStream::CanSeek() const
		{
			return true;
		}
	}
}

#else
#error This file has yet to be decompiled accurately. Use "snd_MemorySoundArchive.s" instead.
#endif