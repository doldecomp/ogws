#include "snd_BankFile.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			using namespace Util;
			
			bool BankFileReader::IsValidFileHeader(const void * ptr)
			{
				const BinaryFileHeader * pFileHeader = static_cast<const BinaryFileHeader *>(ptr);
				
				if (pFileHeader->magic != 'RBNK') return false;
				
				if (pFileHeader->version < 0x0100) return false;
				
				return pFileHeader->version <= 0x0101;
			}
			
			BankFileReader::BankFileReader(const void * ptr) : mFile(), PTR_0x4(), PTR_0x8()
			{
				const BankFile * pFile = static_cast<const BankFile *>(ptr);
				
				if (IsValidFileHeader(ptr))
				{
					mFile = pFile;
					PTR_0x4 = (UNKBLOCK_DATA *)AddOffsetToPtr<u32>(ptr, pFile->OFFSET_0x10);
					PTR_0x8 = (UNKBLOCK_WAVE *)AddOffsetToPtr<u32>(ptr, pFile->OFFSET_0x18);
				}
			}
			
			bool BankFileReader::ReadInstInfo(InstInfo * pInfo, int r_5, int r_6, int r30_7) const
			{
				// r31 <- pInfo
				// r29 <- this
				if (!mFile) return false;
				
				if (r_5 < 0 || r_5 >= PTR_0x4->INT_0x8) return false;
				
				const BankFile::Region * r4 = PTR_0x4->ARR_0xC + r_5;
				
				if (r4->BYTE_0x1 == 4) return false;
				
				if (r4->BYTE_0x1 != 1)
				{
					r4 = GetReferenceToSubRegion(r4, r_6);
					
					if (!r4) return false;
				}
				
				if (r4->BYTE_0x1 == 4) return false;
				
				//80035E44
				if (r4->BYTE_0x1 != 1)
				{
					r4 = GetReferenceToSubRegion(r4, r30_7);
					
					if (!r4) return false;
				}
				
				if (r4->BYTE_0x1 != 1) return false;
				
				//80035E80
				
				//const BankFile::InstParam * r3 = (BankFile::InstParam *)GetDataRefAddressImpl(r4->REFBYTE_0x0, r4->INT_0x4, &PTR_0x4->INT_0x8);
				const BankFile::InstParam * r3 = GetDataRefAddress1(*r4, &PTR_0x4->INT_0x8);
				
				if (!r3) return false;
				
				if (r3->WORD_0x0 < 0) return false;
				
				pInfo->WORD_0x0 = r3->WORD_0x0;
				pInfo->mAttack = r3->mAttack;
				pInfo->mDecay = r3->mDecay;
				pInfo->mSustain = r3->mSustain;
				pInfo->mRelease = r3->mRelease;
				pInfo->BYTE_0x8 = r3->BYTE_0xC;
				pInfo->BYTE_0x9 = r3->BYTE_0xE;
				
				if (mFile->mHeader.version >= 0x0101)
				{
					pInfo->BYTE_0xA = r3->BYTE_0xD;
					pInfo->FLOAT_0xC = r3->FLOAT_0x10;
				}
				else
				{
					pInfo->BYTE_0xA = 0x7F;
					pInfo->FLOAT_0xC = 1.0f;
				}
				
				return true;
			}
			
			const BankFile::Region * BankFileReader::GetReferenceToSubRegion(const BankFile::Region * pRegion, int r31_5) const
			{
				const BankFile::Region * ret = NULL;
				
				switch (pRegion->BYTE_0x1)
				{
					case 0:
						break;
					case 1:
						ret = pRegion;
						break;
					case 2:
						//const BankFile::RangeTable * pRangeTable = (const BankFile::RangeTable *)GetDataRefAddressImpl(pRegion->REFBYTE_0x0, pRegion->INT_0x4, &PTR_0x4->INT_0x8);
						const BankFile::RangeTable * pRangeTable = GetDataRefAddress2(*pRegion, &PTR_0x4->INT_0x8);
						//80035FA0
						
						if (!pRangeTable) return NULL;
						
						int i = 0;
						
						while (r31_5 > pRangeTable->BYTES_0x1[i])
						{
							if (++i >= pRangeTable->BYTE_0x0) return NULL;
						}
						
						u32 a = (u32)pRangeTable + 8 * i;
						u32 b = RoundUp<u32>(pRangeTable->BYTE_0x0 + 1, 4);
						ret = (const BankFile::Region *)(a + b);
						//80035FF8
						break;
					case 3:
						//const BankFile::IndexTable * pIndexTable = (const BankFile::IndexTable *)GetDataRefAddressImpl(pRegion->REFBYTE_0x0, pRegion->INT_0x4, &PTR_0x4->INT_0x8);
						const BankFile::IndexTable * pIndexTable = GetDataRefAddress3(*pRegion, &PTR_0x4->INT_0x8);
						
						if (!pIndexTable) return NULL;
						
						if (r31_5 < pIndexTable->BYTE_0x0 || r31_5 > pIndexTable->BYTE_0x1) return NULL;
						
						ret = (const BankFile::Region *)((u32)pIndexTable + (r31_5 - pIndexTable->BYTE_0x0) * 8 + 4);
						break;
				}
				
				return ret;
			}
			
			bool BankFileReader::ReadWaveParam(WaveData * pData, int r_5, const void * r31_6) const
			{
				// r30 <- pData
				
				if (!mFile) return false;
				
				if (!PTR_0x8) return false;
				
				if (r_5 >= PTR_0x8->INT_0x8) return false;
				
				const WaveFile::Region * pRegion = PTR_0x8->ARR_0xC + r_5;
				
				//const WaveFile::WaveInfo * pWaveInfo = (const WaveFile::WaveInfo *)GetDataRefAddressImpl(pRegion->REFBYTE_0x0, pRegion->INT_0x4, &PTR_0x8->INT_0x8);
				const WaveFile::WaveInfo * pWaveInfo = GetDataRefAddress0(*pRegion, &PTR_0x8->INT_0x8);
				
				if (!pWaveInfo) return false;
				
				WaveFileReader wfr(pWaveInfo);
				
				return wfr.ReadWaveParam(pData, r31_6);
			}
		}
	}
}