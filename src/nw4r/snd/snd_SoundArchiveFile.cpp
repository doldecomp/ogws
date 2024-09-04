#include <string.h>
#include "snd_SoundArchiveFile.h"
#include "ut_algorithm.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			using namespace SoundArchiveFile;
			using namespace Util;
			
			SoundArchiveFileReader::SoundArchiveFileReader() :
				mInfoChunk(NULL),
				mStringChunk(NULL),
				mStringTable(NULL),
				mSoundStringTree(NULL),
				mPlayerStringTree(NULL),
				mGroupStringTree(NULL),
				PTR_0x40(NULL)
			{}
			
			bool SoundArchiveFileReader::IsValidFileHeader(const void * ptr)
			{
				const BinaryFileHeader * pFileHeader = static_cast<const BinaryFileHeader *>(ptr);
				
				if (pFileHeader->magic != 'RSAR') return false;
				
				if (pFileHeader->version < 0x0100) return false;
				
				return pFileHeader->version <= 0x0103;
			}
			
			void SoundArchiveFileReader::Init(const void * ptr)
			{
				if (IsValidFileHeader(ptr)) mHeader = *static_cast<const Header *>(ptr);
			}
			
			const void * SoundArchiveFileReader::GetPtrConst(const void * ptr, u32 offset) const
			{
				return !offset ? NULL : AddOffsetToPtr<u32>(ptr, offset);
			}
			
			void SoundArchiveFileReader::SetStringChunk(const void * ptr, u32)
			{
				const StringBlock * pBlock = static_cast<const StringBlock *>(ptr);
				const StringChunk * pChunk = &pBlock->mChunk;
				
				mStringChunk = pChunk;
				
				mStringTable = static_cast<const Table<u32> *>(GetPtrConst(mStringChunk, pChunk->mTableOffset));
				mSoundStringTree = static_cast<const StringTree *>(GetPtrConst(mStringChunk, pChunk->mSoundTreeOffset));
				mPlayerStringTree = static_cast<const StringTree *>(GetPtrConst(mStringChunk, pChunk->mPlayerTreeOffset));
				mGroupStringTree = static_cast<const StringTree *>(GetPtrConst(mStringChunk, pChunk->mGroupTreeOffset));
				PTR_0x40 = GetPtrConst(mStringChunk, pChunk->OFFSET_0x10);
			}
			
			void SoundArchiveFileReader::SetInfoChunk(const void * ptr, u32)
			{
				mInfoChunk = &static_cast<const InfoBlock *>(ptr)->mChunk;
			}
			
			SoundType SoundArchiveFileReader::GetSoundType(u32 index) const
			{
				const SoundCommonTable * pTable = GetDataRefAddress0(mInfoChunk->mSoundCommonTable, mInfoChunk);
				
				if (!pTable) return SOUND_TYPE_INVALID;
				
				if (index >= pTable->count) return SOUND_TYPE_INVALID;
				
				u8 type;
				
				if (GetVersion() >= 0x0101)
				{
					const SoundCommonInfo * pInfo = GetDataRefAddress0(pTable->items[index], mInfoChunk);
					
					if (!pInfo) return SOUND_TYPE_INVALID;
					
					type = pInfo->soundType;
				}
				else
				{
					type = pTable->items[index].dataType;
				}
				
				switch (type)
				{
					case 1:
						return SOUND_TYPE_SEQ;
					case 2:
						return SOUND_TYPE_STRM;
					case 3:
						return SOUND_TYPE_WAVE;
				}
				
				return SOUND_TYPE_INVALID;
			}
			
			const SoundCommonInfo * SoundArchiveFileReader::impl_GetSoundInfo(u32 index) const
			{
				const SoundCommonTable * pTable = GetDataRefAddress0(mInfoChunk->mSoundCommonTable, mInfoChunk);
				
				if (!pTable) return NULL;
				
				if (index >= pTable->count) return NULL;
				
				if (GetVersion() >= 0x0101) return GetDataRefAddress0(pTable->items[index], mInfoChunk);
				
				return static_cast<const SoundCommonInfo *>(AddOffsetToPtr<u32>(mInfoChunk, pTable->items[index].value));
			}
			
			bool SoundArchiveFileReader::ReadSoundInfo(u32 index, SoundArchive::SoundInfo * pSoundInfo) const
			{
				const SoundCommonInfo * pInfo = impl_GetSoundInfo(index);
				
				if (!pInfo) return false;
				
				pSoundInfo->fileId = pInfo->fileId;
				pSoundInfo->playerId = pInfo->playerId;
				pSoundInfo->playerPriority = pInfo->playerPriority;
				pSoundInfo->volume = pInfo->volume;
				pSoundInfo->remoteFilter = pInfo->remoteFilter;
				
				if (GetVersion() >= NW4R_VERSION(1, 2))
				{
					pSoundInfo->panMode = static_cast<detail::PanMode>(pInfo->panMode);
					pSoundInfo->panCurve = static_cast<detail::PanCurve>(pInfo->panCurve);
				}
				else
				{
					pSoundInfo->panMode = detail::PAN_MODE_BALANCE;
					pSoundInfo->panCurve = detail::PAN_CURVE_SQRT;
				}
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadSound3DParam(u32 index, SoundArchive::Sound3DParam * pSound3DParam) const
			{
				const SoundCommonInfo * pInfo = impl_GetSoundInfo(index);
				
				if (!pInfo) return false;
				
				const SoundArchiveFile::Sound3DParam * pParam = GetDataRefAddress0(pInfo->param3dRef, mInfoChunk);
				
				if (!pParam) return false;
				
				pSound3DParam->flags = pParam->WORD_0x0;
				pSound3DParam->decayCurve = pParam->BYTE_0x4;
				pSound3DParam->decayRatio = pParam->BYTE_0x5;
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadSeqSoundInfo(u32 index, SoundArchive::SeqSoundInfo * pSeqSoundInfo) const
			{
				SoundInfoOffset soundInfoOffset = impl_GetSoundInfoOffset(index);
				
				const SoundArchiveFile::SeqSoundInfo * pInfo = GetDataRefAddress1(soundInfoOffset, mInfoChunk);
				
				if (!pInfo) return false;
				
				pSeqSoundInfo->dataOffset = pInfo->WORD_0x0;
				pSeqSoundInfo->bankId = pInfo->WORD_0x4;
				pSeqSoundInfo->channelPriority = pInfo->BYTE_0xC;
				pSeqSoundInfo->allocTrack = pInfo->WORD_0x8;
				
				if (GetVersion() >= 0x0103)
				{
					pSeqSoundInfo->releasePriorityFixFlag = pInfo->BYTE_0xD;
				}
				else
				{
					pSeqSoundInfo->releasePriorityFixFlag = false;
				}
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadStrmSoundInfo(u32 index, SoundArchive::StrmSoundInfo * pStrmSoundInfo) const
			{
				SoundInfoOffset soundInfoOffset = impl_GetSoundInfoOffset(index);
				
				return GetDataRefAddress2(soundInfoOffset, mInfoChunk);
			}
			
			bool SoundArchiveFileReader::ReadWaveSoundInfo(u32 index, SoundArchive::WaveSoundInfo * pWaveSoundInfo) const
			{
				SoundInfoOffset soundInfoOffset = impl_GetSoundInfoOffset(index);
				
				const SoundArchiveFile::WaveSoundInfo * pInfo = GetDataRefAddress3(soundInfoOffset, mInfoChunk);
				
				if (!pInfo) return false;
				
				pWaveSoundInfo->subNo = pInfo->WORD_0x0;
				pWaveSoundInfo->channelPriority = pInfo->BYTE_0x8;
				
				if (GetVersion() >= 0x0103)
				{
					pWaveSoundInfo->releasePriorityFixFlag = pInfo->BYTE_0x9;
				}
				else
				{
					pWaveSoundInfo->releasePriorityFixFlag = false;
				}
				
				return true;
			}
			
			const BankInfo * SoundArchiveFileReader::impl_GetBankInfo(u32 index) const
			{
				const BankTable * pTable = GetDataRefAddress0(mInfoChunk->mBankTable, mInfoChunk);
				
				if (!pTable) return NULL;
				
				if (index >= pTable->count) return NULL;
				
				return GetDataRefAddress0(pTable->items[index], mInfoChunk);
			}
			
			bool SoundArchiveFileReader::ReadBankInfo(u32 index, SoundArchive::BankInfo * pBankInfo) const
			{
				const BankInfo * pInfo = impl_GetBankInfo(index);
				
				if (!pInfo) return false;
				
				pBankInfo->fileId = pInfo->WORD_0x4;
				
				return true;
			}
			
			const PlayerInfo * SoundArchiveFileReader::impl_GetPlayerInfo(u32 index) const
			{
				const PlayerTable * pTable = GetDataRefAddress0(mInfoChunk->mPlayerTable, mInfoChunk);
				
				if (!pTable) return NULL;
				
				if (index >= pTable->count) return NULL;
				
				return GetDataRefAddress0(pTable->items[index], mInfoChunk);
			}
			
			bool SoundArchiveFileReader::ReadPlayerInfo(u32 index, SoundArchive::PlayerInfo * pPlayerInfo) const
			{
				const PlayerInfo * pInfo = impl_GetPlayerInfo(index);
				
				if (!pInfo) return false;
				
				pPlayerInfo->playableSoundCount = pInfo->BYTE_0x4;
				pPlayerInfo->heapSize = pInfo->WORD_0x8;
				
				return true;
			}
			
			const GroupInfo * SoundArchiveFileReader::impl_GetGroupInfo(u32 index) const
			{
				const GroupTable * pTable = GetDataRefAddress0(mInfoChunk->mGroupTable, mInfoChunk);
				
				if (!pTable) return NULL;
				
				if (index >= pTable->count) return NULL;
				
				return GetDataRefAddress0(pTable->items[index], mInfoChunk);
			}
			
			bool SoundArchiveFileReader::ReadGroupInfo(u32 index, SoundArchive::GroupInfo * pGroupInfo) const
			{
				const GroupInfo * pInfo = impl_GetGroupInfo(index); // at r30
				
				if (!pInfo) return false;
				
				const GroupItemTable * pItemTable = GetDataRefAddress0(pInfo->mGroupItemTable, mInfoChunk);
				
				if (!pItemTable) return false;
				
				pGroupInfo->extFilePath = GetDataRefAddress0(pInfo->mExternalFileName, mInfoChunk);
				pGroupInfo->offset = pInfo->INT_0x10;
				pGroupInfo->size = pInfo->INT_0x14;
				pGroupInfo->waveDataOffset = pInfo->INT_0x18;
				pGroupInfo->waveDataSize = pInfo->INT_0x1C;
				pGroupInfo->itemCount = pItemTable->count;
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadGroupItemInfo(u32 groupIndex, u32 itemIndex, SoundArchive::GroupItemInfo * pGroupItemInfo) const
			{
				const GroupInfo * pInfo = impl_GetGroupInfo(groupIndex);
				
				if (!pInfo) return false;
				
				const GroupItemTable * pItemTable = GetDataRefAddress0(pInfo->mGroupItemTable, mInfoChunk);
				
				if (!pItemTable) return false;
				
				if (itemIndex >= pItemTable->count) return false;
				
				const GroupItemInfo * pItemInfo = GetDataRefAddress0(pItemTable->items[itemIndex], mInfoChunk);
				
				if (!pItemInfo) return false;
				
				pGroupItemInfo->fileId = pItemInfo->WORD_0x0;
				pGroupItemInfo->offset = pItemInfo->INT_0x4;
				pGroupItemInfo->size = pItemInfo->INT_0x8;
				pGroupItemInfo->waveDataOffset = pItemInfo->INT_0xC;
				pGroupItemInfo->waveDataSize = pItemInfo->WORD_0x10;
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadSoundArchivePlayerInfo(SoundArchive::SoundArchivePlayerInfo * pSoundArchivePlayerInfo) const
			{
				const SoundArchivePlayerInfo * pInfo = GetDataRefAddress0(mInfoChunk->mSoundArchivePlayerInfo, mInfoChunk);
				
				if (!pSoundArchivePlayerInfo) return false;
				
				pSoundArchivePlayerInfo->seqSoundCount = pInfo->SIZE_0x0;
				pSoundArchivePlayerInfo->seqTrackCount = pInfo->SHORT_0x2;
				pSoundArchivePlayerInfo->strmSoundCount = pInfo->SIZE_0x4;
				pSoundArchivePlayerInfo->strmTrackCount = pInfo->SHORT_0x6;
				pSoundArchivePlayerInfo->strmChannelCount = pInfo->SHORT_0x8;
				pSoundArchivePlayerInfo->waveSoundCount = pInfo->SIZE_0xA;
				pSoundArchivePlayerInfo->waveTrackCount = pInfo->SHORT_0xC;
				
				return true;
			}
			
			u32 SoundArchiveFileReader::GetPlayerCount() const
			{
				const PlayerTable * pTable = GetDataRefAddress0(mInfoChunk->mPlayerTable, mInfoChunk);
				
				return !pTable ? 0 : pTable->count;
			}
			
			u32 SoundArchiveFileReader::GetGroupCount() const
			{
				const GroupTable * pTable = GetDataRefAddress0(mInfoChunk->mGroupTable, mInfoChunk);
				
				return !pTable ? 0 : pTable->count - 1;
			}
			
			u32 SoundArchiveFileReader::GetSoundStringId(u32 index) const
			{
				const SoundCommonInfo * pInfo = impl_GetSoundInfo(index);
				
				return !pInfo ? -1 : pInfo->stringId;
			}
			
			const char * SoundArchiveFileReader::GetString(u32 id) const
			{
				if (id == -1) return NULL;
				
				return !mStringTable ? NULL : static_cast<const char *>(GetPtrConst(mStringChunk, mStringTable->items[id]));
			}
			
			const char * SoundArchiveFileReader::GetSoundLabelString(u32 index) const
			{
				return GetString(GetSoundStringId(index));
			}
			
			UNKWORD SoundArchiveFileReader::GetSoundUserParam(u32 index) const
			{
				const SoundCommonInfo * pInfo = impl_GetSoundInfo(index);
				
				return !pInfo ? 0 : pInfo->userParam[0];
			}
			
			bool SoundArchiveFileReader::ReadFileInfo(u32 index, SoundArchive::FileInfo * pFileInfo) const
			{
				const FileTable * pTable = GetDataRefAddress0(mInfoChunk->mFileTable, mInfoChunk);
				
				if (!pTable) return false;
				
				if (index >= pTable->count) return false;
				
				const FileInfo * pInfo = GetDataRefAddress0(pTable->items[index], mInfoChunk);
				
				if (!pInfo) return false;
				
				const FilePosTable * pPosTable = GetDataRefAddress0(pInfo->TABLE_0x14, mInfoChunk);
				
				if (!pPosTable) return false;
				
				pFileInfo->fileSize = pInfo->WORD_0x0;
				pFileInfo->waveDataFileSize = pInfo->WORD_0x4;
				pFileInfo->extFilePath = GetDataRefAddress0(pInfo->mExternalFileName, mInfoChunk);
				pFileInfo->filePosCount = pPosTable->count;
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadFilePos(u32 fileIndex, u32 posIndex, SoundArchive::FilePos * pFilePos) const
			{
				const FileTable * pTable = GetDataRefAddress0(mInfoChunk->mFileTable, mInfoChunk);
				
				if (!pTable) return false;
				
				if (fileIndex >= pTable->count) return false;
				
				const FileInfo * pInfo = GetDataRefAddress0(pTable->items[fileIndex], mInfoChunk);
				
				if (!pInfo) return false;
				
				const FilePosTable * pPosTable = GetDataRefAddress0(pInfo->TABLE_0x14, mInfoChunk);
				
				if (!pPosTable) return false;
				
				if (posIndex >= pPosTable->count) return false;
				
				const SoundArchive::FilePos * pPos = GetDataRefAddress0(pPosTable->items[posIndex], mInfoChunk);
				
				if (!pPos) return false;
				
				*pFilePos = *pPos;
				
				return 4;
			}
			
			u32 SoundArchiveFileReader::ConvertLabelStringToId(const StringTree * pStringTree, const char * pLabelString) const
			{
				if (!pStringTree) return -1;
				
				if (pStringTree->mRootIndex >= pStringTree->INT_0x4) return -1;
				
				const StringNode * pNode = pStringTree->mNodes + pStringTree->mRootIndex;
				
				int labelLength = strlen(pLabelString);
				
				while (!(pNode->mFlags & StringNode::FLAG_LEAF))
				{
					//8004325C
					int byteIndex = pNode->SHORT_0x2 >> 3;
					int bitIndex = pNode->SHORT_0x2 & 7;
					u32 nodeIndex;
					
					if (byteIndex < labelLength && (1 << (7 - bitIndex)) & pLabelString[byteIndex])
					{
						nodeIndex = pNode->mRightIndex;
					}
					else
					{
						nodeIndex = pNode->mLeftIndex;
					}
					
					
					pNode = pStringTree->mNodes + nodeIndex;
				}
				
				const char * pString = GetString(pNode->mStringId);
				
				return !strcmp(pLabelString, pString) ? pNode->mId : -1;
			}
			
			SoundInfoOffset SoundArchiveFileReader::impl_GetSoundInfoOffset(u32 index) const
			{
				static SoundInfoOffset INVALID_DATA_REF; // at 0x804BEB00
				
				const SoundCommonTable * pTable = GetDataRefAddress0(mInfoChunk->mSoundCommonTable, mInfoChunk);
				
				if (!pTable) return INVALID_DATA_REF;
				
				if (index >= pTable->count) return INVALID_DATA_REF;
				
				if (GetVersion() >= 0x0101)
				{
					const SoundCommonInfo * pInfo = GetDataRefAddress0(pTable->items[index], mInfoChunk);
					
					return !pInfo ? INVALID_DATA_REF : pInfo->soundInfoRef;
				}
				
				SoundInfoOffset soundInfoOffset;
				
				soundInfoOffset.refType = pTable->items[index].refType;
				soundInfoOffset.dataType = pTable->items[index].dataType;
				soundInfoOffset.value = pTable->items[index].value + 0x1C;
				
				return soundInfoOffset;
			}
		}
	}
}