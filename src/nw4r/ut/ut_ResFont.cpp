#include "ut_ResFont.h"

namespace nw4r
{
	namespace ut
	{
		template <typename T>
		inline void ResolveOffset(T *& t, void * v)
		{
			t = reinterpret_cast<T *>((u8 *)v + (s32)t);
		}
		
		ResFont::ResFont() {}
		ResFont::~ResFont() {}
		
		bool ResFont::SetResource(void * pBuffer)
		{
			BinaryFileHeader * pFile = static_cast<BinaryFileHeader *>(pBuffer);
			
			FontInformation * pFontInfo = NULL;
			
			if (mBuffer) return false;
			
			if (pFile->magic == 'RFNU') //IsManaging?
			{
				BinaryBlockHeader * pCurBlock = (BinaryBlockHeader *)((u8 *)pFile + pFile->headerSize);
				
				for (int i = 0; i < pFile->numBlocks; i++)
				{
					if (pCurBlock->magic == 'FINF')
					{
						pFontInfo = (FontInformation *)(pCurBlock + 1);
						break;
					}
					pCurBlock = (BinaryBlockHeader *)((u8 *)pCurBlock + pCurBlock->length);
				}
			}
			else
			{
				if (pFile->version == 0x0104)
				{
					if (!IsValidBinaryFile(pFile, 'RFNT', 0x0104, 2)) return false;
				}
				else
				{
					if (!IsValidBinaryFile(pFile, 'RFNT', 0x0102, 2)) return false;
				}
				pFontInfo = Rebuild(pFile);
			}
			
			if (pFontInfo == NULL) return false;
			
			SetResourceBuffer(pBuffer, pFontInfo);
			InitReaderFunc(GetEncoding());
			
			return true;
		}
		
		FontInformation * ResFont::Rebuild(BinaryFileHeader * pFile)
		{
			BinaryBlockHeader * pCurBlock = (BinaryBlockHeader *)((u8 *)pFile + pFile->headerSize);
			FontInformation * pFontInfo = NULL;
			
			for (int i = 0; i < pFile->numBlocks; i++)
			{
				switch (pCurBlock->magic)
				{
					case 'FINF': //8000ABD8
						pFontInfo = reinterpret_cast<FontInformation *>(pCurBlock + 1);
						ResolveOffset<FontTextureGlyph>(pFontInfo->mTextureGlyph, pFile);
						if (pFontInfo->mWidthList) ResolveOffset<FontWidth>(pFontInfo->mWidthList, pFile);
						if (pFontInfo->mCodeMapList) ResolveOffset<FontCodeMap>(pFontInfo->mCodeMapList, pFile);
						break;
					case 'TGLP': //8000AC14
						ResolveOffset<u8>(reinterpret_cast<FontTextureGlyph *>(pCurBlock + 1)->PTR_0x14, pFile);
						break;
					case 'CWDH': //8000AC24
						FontWidth * pWidths = reinterpret_cast<FontWidth *>(pCurBlock + 1);
						if (pWidths->mNext) ResolveOffset<FontWidth>(pWidths->mNext, pFile);
						break;
					case 'CMAP': //8000AC3C
						FontCodeMap * pMap = reinterpret_cast<FontCodeMap *>(pCurBlock + 1);
						if (pMap->mNext) ResolveOffset<FontCodeMap>(pMap->mNext, pFile);
						break;
					case 'GLGR':
						break;
					default:
						return NULL;
				}
				
				pCurBlock = (BinaryBlockHeader *)((u8 *)pCurBlock + pCurBlock->length);
			}
			
			pFile->magic = 'RFNU';
			return pFontInfo;
		}
	}
}