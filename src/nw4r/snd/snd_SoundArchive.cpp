#include <string.h>
#include "snd_SoundArchive.h"
#include "snd_SoundArchiveFile.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		SoundArchive::SoundArchive() : mFileReader(NULL)
		{
			mExternalFileRoot[0] = '/';
			mExternalFileRoot[1] = '\0';
		}
		
		SoundArchive::~SoundArchive() {}
		
		bool SoundArchive::IsAvailable() const
		{
			return mFileReader;
		}
		
		void SoundArchive::Setup(SoundArchiveFileReader * pFileReader)
		{
			mFileReader = pFileReader;
		}
		
		void SoundArchive::Shutdown()
		{
			mFileReader = NULL;
			mExternalFileRoot[0] = '/';
			mExternalFileRoot[1] = '\0';
		}
		
		u32 SoundArchive::GetPlayerCount() const
		{
			return mFileReader->GetPlayerCount();
		}
		
		u32 SoundArchive::GetGroupCount() const
		{
			return mFileReader->GetGroupCount();
		}
		
		const char * SoundArchive::GetSoundLabelString(u32 index) const
		{
			return mFileReader->GetSoundLabelString(index);
		}
		
		u32 SoundArchive::ConvertLabelStringToSoundId(const char * pLabelString) const
		{
			return mFileReader->ConvertLabelStringToId(mFileReader->mSoundStringTree, pLabelString);
		}
		
		u32 SoundArchive::ConvertLabelStringToPlayerId(const char * pLabelString) const
		{
			return mFileReader->ConvertLabelStringToId(mFileReader->mPlayerStringTree, pLabelString);
		}
		
		u32 SoundArchive::ConvertLabelStringToGroupId(const char * pLabelString) const
		{
			return mFileReader->ConvertLabelStringToId(mFileReader->mGroupStringTree, pLabelString);
		}
		
		UNKWORD SoundArchive::GetSoundUserParam(u32 index) const
		{
			return mFileReader->GetSoundUserParam(index);
		}
		
		UNKWORD SoundArchive::GetSoundType(u32 index) const
		{
			return mFileReader->GetSoundType(index);
		}
		
		bool SoundArchive::ReadSoundInfo(u32 index, SoundInfo * pSoundInfo) const
		{
			return mFileReader->ReadSoundInfo(index, pSoundInfo);
		}
		
		bool SoundArchive::detail_ReadSeqSoundInfo(u32 index, SeqSoundInfo * pSeqSoundInfo) const
		{
			return mFileReader->ReadSeqSoundInfo(index, pSeqSoundInfo);
		}
		
		bool SoundArchive::detail_ReadStrmSoundInfo(u32 index, StrmSoundInfo * pStrmSoundInfo) const
		{
			return mFileReader->ReadStrmSoundInfo(index, pStrmSoundInfo);
		}
		
		bool SoundArchive::detail_ReadWaveSoundInfo(u32 index, WaveSoundInfo * pWaveSoundInfo) const
		{
			return mFileReader->ReadWaveSoundInfo(index, pWaveSoundInfo);
		}
		
		bool SoundArchive::ReadPlayerInfo(u32 index, PlayerInfo * pPlayerInfo) const
		{
			return mFileReader->ReadPlayerInfo(index, pPlayerInfo);
		}
		
		bool SoundArchive::ReadSoundArchivePlayerInfo(SoundArchivePlayerInfo * pSoundArchivePlayerInfo) const
		{
			return mFileReader->ReadSoundArchivePlayerInfo(pSoundArchivePlayerInfo);
		}
		
		bool SoundArchive::detail_ReadSound3DParam(u32 index, Sound3DParam * pSound3DParam) const
		{
			return mFileReader->ReadSound3DParam(index, pSound3DParam);
		}
		
		bool SoundArchive::detail_ReadBankInfo(u32 index, BankInfo * pBankInfo) const
		{
			return mFileReader->ReadBankInfo(index, pBankInfo);
		}
		
		bool SoundArchive::detail_ReadGroupInfo(u32 index, GroupInfo * pGroupInfo) const
		{
			return mFileReader->ReadGroupInfo(index, pGroupInfo);
		}
		
		bool SoundArchive::detail_ReadGroupItemInfo(u32 groupIndex, u32 itemIndex, GroupItemInfo * pGroupItemInfo) const
		{
			return mFileReader->ReadGroupItemInfo(groupIndex, itemIndex, pGroupItemInfo);
		}
		
		bool SoundArchive::detail_ReadFileInfo(u32 index, FileInfo * pFileInfo) const
		{
			return mFileReader->ReadFileInfo(index, pFileInfo);
		}
		
		bool SoundArchive::detail_ReadFilePos(u32 fileIndex, u32 posIndex, FilePos * pFilePos) const
		{
			return mFileReader->ReadFilePos(fileIndex, posIndex, pFilePos);
		}
		
		FileStream * SoundArchive::OpenExtStreamImpl(void * pBuffer, int bufferSize, const char * pExternalFileName, u32 startOffset, u32 streamSize) const
		{
			char absoluteFileName[0x100];
			const char * pName;
			
			if (pExternalFileName[0] == '/')
			{
				pName = pExternalFileName;
			}
			else
			{
				u32 relativeLength = strlen(pExternalFileName);
				u32 rootLength = strlen(mExternalFileRoot);
				u32 absoluteLength = relativeLength + rootLength;
				
				if (absoluteLength >= sizeof absoluteFileName) return NULL;
				
				strncpy(absoluteFileName, mExternalFileRoot, rootLength + 1);
				strncat(absoluteFileName, pExternalFileName, relativeLength + 1);
				
				pName = absoluteFileName;
			}
			
			return OpenExtStream(pBuffer, bufferSize, pName, startOffset, streamSize);
		}
		
		FileStream * SoundArchive::detail_OpenFileStream(u32 index, void * pBuffer, int bufferSize) const
		{
			GroupInfo groupInfo; // at 0x38
			GroupItemInfo groupItemInfo; // at 0x20
			FileInfo fileInfo; // at 0x10
			FilePos filePos; // at 0x8
			
			if (!detail_ReadFileInfo(index, &fileInfo)) return NULL;
			
			if (fileInfo.mExternalFileName) return OpenExtStreamImpl(pBuffer, bufferSize, fileInfo.mExternalFileName, 0, 0);
			
			if (!detail_ReadFilePos(index, 0, &filePos)) return NULL;
			
			if (!detail_ReadGroupInfo(filePos.groupId, &groupInfo)) return NULL;
			
			if (!detail_ReadGroupItemInfo(filePos.groupId, filePos.index, &groupItemInfo)) return NULL;
			
			u32 startOffset = groupInfo.offset + groupItemInfo.offset;
			u32 streamSize = groupItemInfo.size;
			
			if (groupInfo.extFilePath) return OpenExtStreamImpl(pBuffer, bufferSize, groupInfo.extFilePath, startOffset, streamSize);
			
			return OpenStream(pBuffer, bufferSize, startOffset, streamSize);
		}
		
		FileStream * SoundArchive::detail_OpenGroupStream(u32 index, void * pBuffer, int bufferSize) const
		{
			GroupInfo groupInfo; // at 0x8
			
			if (!detail_ReadGroupInfo(index, &groupInfo)) return NULL;
			
			if (groupInfo.extFilePath) return OpenExtStreamImpl(pBuffer, bufferSize, groupInfo.extFilePath, groupInfo.offset, groupInfo.size);
			
			return OpenStream(pBuffer, bufferSize, groupInfo.offset, groupInfo.size);
		}
		
		FileStream * SoundArchive::detail_OpenGroupWaveDataStream(u32 index, void * pBuffer, int bufferSize) const
		{
			GroupInfo groupInfo; // at 0x8
			
			if (!detail_ReadGroupInfo(index, &groupInfo)) return NULL;
			
			if (groupInfo.extFilePath) return OpenExtStreamImpl(pBuffer, bufferSize, groupInfo.extFilePath, groupInfo.waveDataOffset, groupInfo.waveDataSize);
			
			return OpenStream(pBuffer, bufferSize, groupInfo.waveDataOffset, groupInfo.waveDataSize);
		}
		
		UNKTYPE SoundArchive::SetExternalFileRoot(const char * pExternalFileRoot)
		{
			u32 argumentLength = strlen(pExternalFileRoot);
			u32 memberLength = argumentLength;
			
			if (pExternalFileRoot[argumentLength - 1] != '/')
			{
				mExternalFileRoot[argumentLength] = '/';
				memberLength = argumentLength + 1;
			}
			
			mExternalFileRoot[memberLength] = '\0';
			
			strncpy(mExternalFileRoot, pExternalFileRoot, argumentLength);
		}
	}
}