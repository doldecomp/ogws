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
			
			UNKWORD SoundArchiveFileReader::GetSoundType(u32 index) const
			{
				const SoundCommonTable * pTable = GetDataRefAddress0(mInfoChunk->mSoundCommonTable, mInfoChunk);
				
				if (!pTable) return 0;
				
				if (index >= pTable->count) return 0;
				
				u8 type;
				
				if (GetVersion() >= 0x0101)
				{
					const SoundCommonInfo * pInfo = GetDataRefAddress0(pTable->items[index], mInfoChunk);
					
					if (!pInfo) return 0;
					
					type = pInfo->mType;
				}
				else
				{
					type = pTable->items[index].dataType;
				}
				
				switch (type)
				{
					case 1:
						return 1;
					case 2:
						return 2;
					case 3:
						return 3;
				}
				
				return 0;
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
				
				pSoundInfo->WORD_0x0 = pInfo->WORD_0x4;
				pSoundInfo->WORD_0x4 = pInfo->WORD_0x8;
				pSoundInfo->WORD_0x8 = pInfo->BYTE_0x15;
				pSoundInfo->WORD_0xC = pInfo->BYTE_0x14;
				pSoundInfo->WORD_0x10 = pInfo->BYTE_0x17;
				
				if (GetVersion() >= 0x0102)
				{
					pSoundInfo->WORD_0x14 = pInfo->BYTE_0x28;
					pSoundInfo->WORD_0x18 = pInfo->BYTE_0x29;
				}
				else
				{
					pSoundInfo->WORD_0x14 = 1;
					pSoundInfo->WORD_0x18 = 0;
				}
				
				return true;
			}
			
			bool SoundArchiveFileReader::ReadSound3DParam(u32 index, SoundArchive::Sound3DParam * pSound3DParam) const
			{
				const SoundCommonInfo * pInfo = impl_GetSoundInfo(index);
				
				if (!pInfo) return false;
				
				const SoundArchiveFile::Sound3DParam * pParam = GetDataRefAddress0(pInfo->mSound3DParam, mInfoChunk);
				
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
				
				pSeqSoundInfo->WORD_0x0 = pInfo->WORD_0x0;
				pSeqSoundInfo->WORD_0x4 = pInfo->WORD_0x4;
				pSeqSoundInfo->WORD_0xC = pInfo->BYTE_0xC;
				pSeqSoundInfo->WORD_0x8 = pInfo->WORD_0x8;
				
				if (GetVersion() >= 0x0103)
				{
					pSeqSoundInfo->BOOL_0x10 = pInfo->BYTE_0xD;
				}
				else
				{
					pSeqSoundInfo->BOOL_0x10 = false;
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
				
				pWaveSoundInfo->WORD_0x0 = pInfo->WORD_0x0;
				pWaveSoundInfo->WORD_0x4 = pInfo->BYTE_0x8;
				
				if (GetVersion() >= 0x0103)
				{
					pWaveSoundInfo->BOOL_0x8 = pInfo->BYTE_0x9;
				}
				else
				{
					pWaveSoundInfo->BOOL_0x8 = false;
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
				
				pBankInfo->WORD_0x0 = pInfo->WORD_0x4;
				
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
				
				pPlayerInfo->WORD_0x0 = pInfo->BYTE_0x4;
				pPlayerInfo->WORD_0x4 = pInfo->WORD_0x8;
				
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
				
				return !pInfo ? -1 : pInfo->mSoundStringId;
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
				
				return !pInfo ? 0 : pInfo->mSoundUserParam;
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
				
				pFileInfo->WORD_0x0 = pInfo->WORD_0x0;
				pFileInfo->WORD_0x4 = pInfo->WORD_0x4;
				pFileInfo->mExternalFileName = GetDataRefAddress0(pInfo->mExternalFileName, mInfoChunk);
				pFileInfo->SIZE_0xC = pPosTable->count;
				
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
					
					return !pInfo ? INVALID_DATA_REF : pInfo->mSoundInfoOffset;
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