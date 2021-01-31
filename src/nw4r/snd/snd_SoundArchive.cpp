#include <string.h>
#include "snd_SoundArchive.h"
#include "snd_SoundArchiveFile.h"

namespace nw4r
{
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
		
		UNKWORD SoundArchive::OpenExtStreamImpl(void * arg1, int arg2, const char * pExternalFileName, u32 arg4, u32 arg5) const
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
				
				if (absoluteLength >= sizeof absoluteFileName) return 0;
				
				strncpy(absoluteFileName, mExternalFileRoot, rootLength + 1);
				strncat(absoluteFileName, pExternalFileName, relativeLength + 1);
				
				pName = absoluteFileName;
			}
			
			return OpenExtStream(arg1, arg2, pName, arg4, arg5);
		}
		
		UNKWORD SoundArchive::detail_OpenFileStream(u32 index, void * r30, int r31) const
		{
			GroupInfo groupInfo; // at 0x38
			GroupItemInfo groupItemInfo; // at 0x20
			FileInfo fileInfo; // at 0x10
			FilePos filePos; // at 0x8
			
			if (!detail_ReadFileInfo(index, &fileInfo)) return 0;
			
			if (fileInfo.mExternalFileName) return OpenExtStreamImpl(r30, r31, fileInfo.mExternalFileName, 0, 0);
			
			if (!detail_ReadFilePos(index, 0, &filePos)) return 0;
			
			if (!detail_ReadGroupInfo(filePos.mGroupIndex, &groupInfo)) return 0;
			
			if (!detail_ReadGroupItemInfo(filePos.mGroupIndex, filePos.mGroupItemIndex, &groupItemInfo)) return 0;
			
			u32 r26 = groupInfo.INT_0x8 + groupItemInfo.INT_0x4;
			u32 r25 = groupItemInfo.INT_0x8;
			
			if (groupInfo.mExternalFileName) return OpenExtStreamImpl(r30, r31, groupInfo.mExternalFileName, r26, r25);
			
			return OpenStream(r30, r31, r26, r25);
		}
		
		UNKWORD SoundArchive::detail_OpenGroupStream(u32 index, void * r26, int r27) const
		{
			GroupInfo groupInfo; // at 0x8
			
			if (!detail_ReadGroupInfo(index, &groupInfo)) return 0;
			
			if (groupInfo.mExternalFileName) return OpenExtStreamImpl(r26, r27, groupInfo.mExternalFileName, groupInfo.INT_0x8, groupInfo.INT_0xC);
			
			return OpenStream(r26, r27, groupInfo.INT_0x8, groupInfo.INT_0xC);
		}
		
		UNKWORD SoundArchive::detail_OpenGroupWaveDataStream(u32 index, void * r26, int r27) const
		{
			GroupInfo groupInfo; // at 0x8
			
			if (!detail_ReadGroupInfo(index, &groupInfo)) return 0;
			
			if (groupInfo.mExternalFileName) return OpenExtStreamImpl(r26, r27, groupInfo.mExternalFileName, groupInfo.INT_0x10, groupInfo.INT_0x14);
			
			return OpenStream(r26, r27, groupInfo.INT_0x10, groupInfo.INT_0x14);
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