#ifdef __DECOMP_NON_MATCHING
#pragma ipa file
#include <string.h>
#include <new>
#include "ut_algorithm.h"
#include "snd_DvdSoundArchive.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		DvdSoundArchive::DvdSoundArchive() : mOpenFlag(false) {}
		
		DvdSoundArchive::~DvdSoundArchive()
		{
			Close();
		}
		
		bool DvdSoundArchive::Open(s32 entrynum)
		{
			if (!DVDFastOpen(entrynum, &mFileInfo)) return false;
			
			mOpenFlag = true;
			
			static const u32 headerAlignSize = RoundUp<u32>(sizeof(SoundArchiveFile::Header), 0x20);
			u8 unalignedHeader[0x68]; // at 0x8
			void * alignedHeader = RoundUp<u8 *>(unalignedHeader, 0x20);
			u32 bytesRead = DVDReadPrio(&mFileInfo, alignedHeader, headerAlignSize, 0, 2);
			
			if (bytesRead != headerAlignSize) return false;
			
			mFileReader.Init(alignedHeader);
			SoundArchive::Setup(&mFileReader);
			
			return true;
		}
		
		bool DvdSoundArchive::Open(const char * pPath)
		{
			s32 entrynum = DVDConvertPathToEntrynum(pPath);
			
			if (entrynum < 0) return false;
			
			if (!Open(entrynum)) return false;
			
			char externalFileRoot[0x100];
			
			for (int i = strlen(pPath) - 1; i >= 0; i--)
			{
				if (pPath[i] == '/' || pPath[i] == '\\')
				{
					strncpy(externalFileRoot, pPath + i, i);
					externalFileRoot[i] = '\0';
					SoundArchive::SetExternalFileRoot(externalFileRoot);
					break;
				}
			}
			
			return true;
		}
		
		void DvdSoundArchive::Close()
		{
			DVDClose(&mFileInfo);
			mOpenFlag = false;
			SoundArchive::Shutdown();
		}
		
		DvdSoundArchive::DvdFileStream::DvdFileStream(const DVDFileInfo * pFileInfo, u32 startOffset, u32 size)
			: DvdLockedFileStream(pFileInfo, false), mStartOffset(startOffset), mSize(size)
		{
			if (!mSize) mSize = mPosition.mFileSize;
			
			ut::DvdFileStream::Seek(mStartOffset, 0);
		}
		
		FileStream * DvdSoundArchive::OpenStream(void * pBuffer, int bufferSize, u32 startOffset, u32 streamSize) const
		{
			if (mOpenFlag) return NULL;
			
			if (bufferSize < sizeof(DvdFileStream)) return NULL;
			
			return new (pBuffer) DvdFileStream(&mFileInfo, startOffset, streamSize);
		}
		
		DvdSoundArchive::DvdFileStream::DvdFileStream(s32 entrynum, u32 startOffset, u32 size)
			: DvdLockedFileStream(entrynum), mStartOffset(startOffset), mSize(size)
		{
			if (!mSize) mSize = mPosition.mFileSize;
			
			ut::DvdFileStream::Seek(mStartOffset, 0);
		}
		
		FileStream * DvdSoundArchive::OpenExtStream(void * pBuffer, int bufferSize, const char * pPath, u32 startOffset, u32 streamSize) const
		{
			if (mOpenFlag) return NULL;
			
			if (bufferSize < sizeof(DvdFileStream)) return NULL;
			
			u32 entrynum = DVDConvertPathToEntrynum(pPath);
			
			if (entrynum < 0) return NULL;
			
			return new (pBuffer) DvdFileStream(entrynum, startOffset, streamSize);
		}
		
		int DvdSoundArchive::detail_GetRequiredStreamBufferSize() const
		{
			return sizeof(DvdFileStream);
		}
		
		bool DvdSoundArchive::LoadHeader(void * pBuffer, u32 bufferSize)
		{
			u32 infoChunkSize = mFileReader.GetInfoChunkSize();
			s32 infoChunkOffset = mFileReader.GetInfoChunkOffset();
			
			if (bufferSize < infoChunkSize) return false;
			
			u32 bytesRead = DVDReadPrio(&mFileInfo, pBuffer, infoChunkSize, infoChunkOffset, 2);
			
			if (bytesRead != infoChunkSize) return false;
			
			mFileReader.SetInfoChunk(pBuffer, infoChunkSize);
			
			return true;
		}
		
		bool DvdSoundArchive::LoadLabelStringData(void * pBuffer, u32 bufferSize)
		{
			u32 labelStringChunkSize = mFileReader.GetLabelStringChunkSize();
			s32 labelStringChunkOffset = mFileReader.GetLabelStringChunkOffset();
			
			if (bufferSize < labelStringChunkSize) return false;
			
			u32 bytesRead = DVDReadPrio(&mFileInfo, pBuffer, labelStringChunkSize, labelStringChunkOffset, 2);
			
			if (bytesRead != labelStringChunkSize) return false;
			
			mFileReader.SetStringChunk(pBuffer, labelStringChunkSize);
			
			return true;
		}
		
		int DvdSoundArchive::DvdFileStream::Read(void * pBuffer, u32 count)
		{
			u32 endOffset = mStartOffset + mSize;
			
			if (mPosition.mFileOffset + count > endOffset) count = RoundUp<u32>(endOffset - mPosition.mFileOffset, 0x20);
			
			return DvdLockedFileStream::Read(pBuffer, count);
		}
		
		void DvdSoundArchive::DvdFileStream::Seek(s32 offset, u32 origin)
		{
			switch (origin)
			{
				case 0:
					offset += mStartOffset;
					break;
				case 1:
					offset += mPosition.mFileOffset;
					break;
				case 2:
					offset = mStartOffset + mSize - offset;
					break;
				default:
					return;
			}
			
			if (offset < mStartOffset)
			{
				offset = mStartOffset;
			}
			else if (offset > mStartOffset + mSize)
			{
				offset = mStartOffset + mSize;
			}
			
			ut::DvdFileStream::Seek(offset, 0);
		}
		
		u32 DvdSoundArchive::DvdFileStream::GetSize() const
		{
			return mSize;
		}
		
		u32 DvdSoundArchive::DvdFileStream::Tell() const
		{
			return mPosition.mFileOffset - mStartOffset;
		}
		
		const void * DvdSoundArchive::detail_GetWaveDataFileAddress(u32) const
		{
			return NULL;
		}
		
		const void * DvdSoundArchive::detail_GetFileAddress(u32) const
		{
			return NULL;
		}
	}
}

#else
#error This file has yet to be decompiled accurately. Use "snd_DvdSoundArchive.s" instead.
#endif