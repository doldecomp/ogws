#include "ut_ResFontBase.h"

namespace nw4r
{
	namespace ut
	{
		namespace detail
		{
			ResFontBase::ResFontBase() : mBuffer(), mFontInfo() {}
			ResFontBase::~ResFontBase() {}
			
			u16 ResFontBase::FindGlyphIndex(u16 ch) const
			{
				for (FontCodeMap * pCodeMap = mFontInfo->mCodeMapList; pCodeMap; pCodeMap = pCodeMap->mNext)
				{
					if (pCodeMap->mFirstChar <= ch && ch <= pCodeMap->mLastChar) return FindGlyphIndex(pCodeMap, ch);
				}
				
				return 0xFFFF;
			}
			
			u16 ResFontBase::GetGlyphIndex(u16 ch) const
			{
				u16 glyphIndex = FindGlyphIndex(ch);
				
				return (glyphIndex != 0xFFFF) ? glyphIndex : mFontInfo->mAlternateChar;
			}
			
			const CharWidths & ResFontBase::GetCharWidthsFromIndex(const FontWidth * pWidths, u16 ch) const
			{
				return pWidths->mWidthTable[ch - pWidths->mFirstChar];
			}
			
			const CharWidths & ResFontBase::GetCharWidthsFromIndex(u16 ch) const
			{
				for (const FontWidth * pWidth = mFontInfo->mWidthList; pWidth; pWidth = pWidth->mNext)
				{
					if (pWidth->mFirstChar <= ch && ch <= pWidth->mLastChar) return GetCharWidthsFromIndex(pWidth, ch);
				}
				
				return mFontInfo->mDefaultCharWidths;
			}
			
			void ResFontBase::SetResourceBuffer(void * pBuffer, FontInformation * pFontInfo)
			{
				mBuffer = pBuffer;
				mFontInfo = pFontInfo;
			}
			
			int ResFontBase::GetWidth() const
			{
				return mFontInfo->mWidth;
			}
			
			int ResFontBase::GetHeight() const
			{
				return mFontInfo->mHeight;
			}
			
			int ResFontBase::GetAscent() const
			{
				return mFontInfo->mAscent;
			}
			
			int ResFontBase::GetDescent() const
			{
				return mFontInfo->mHeight - mFontInfo->mAscent;
			}
			
			int ResFontBase::GetBaselinePos() const
			{
				return mFontInfo->mTextureGlyph->mBaselinePos;
			}
			
			int ResFontBase::GetCellHeight() const
			{
				return mFontInfo->mTextureGlyph->mCellHeight;
			}
			
			int ResFontBase::GetCellWidth() const
			{
				return mFontInfo->mTextureGlyph->mCellWidth;
			}
			
			int ResFontBase::GetMaxCharWidth() const
			{
				return mFontInfo->mTextureGlyph->mMaxCharWidth;
			}
			
			UNKWORD ResFontBase::GetType() const
			{
				return 2;
			}
			
			UNKWORD ResFontBase::GetTextureFormat() const
			{
				return mFontInfo->mTextureGlyph->mFormat;
			}
			
			int ResFontBase::GetLineFeed() const
			{
				return mFontInfo->mLineFeed;
			}
			
			CharWidths ResFontBase::GetDefaultCharWidths() const
			{
				return mFontInfo->mDefaultCharWidths;
			}
			
			void ResFontBase::SetDefaultCharWidths(const CharWidths & rDefaultCharWidths)
			{
				mFontInfo->mDefaultCharWidths = rDefaultCharWidths;
			}
			
			bool ResFontBase::SetAlternateChar(u16 ch)
			{
				u16 r5;
				
				r5 = FindGlyphIndex(ch);
				
				if (r5 != 0xFFFF)
				{
					mFontInfo->mAlternateChar = r5;
					return true;
				}
				
				return false;
			}
			
			void ResFontBase::SetLineFeed(int lf)
			{
				mFontInfo->mLineFeed = lf;
			}
			
			int ResFontBase::GetCharWidth(u16 ch) const
			{
				return GetCharWidths(ch).BYTE_0x2;
			}
			
			CharWidths ResFontBase::GetCharWidths(u16 ch) const
			{
				return GetCharWidthsFromIndex(GetGlyphIndex(ch));
			}
			
			void ResFontBase::GetGlyph(Glyph * pGlyph, u16 ch) const
			{
				GetGlyphFromIndex(pGlyph, GetGlyphIndex(ch));
			}
			
			FontEncoding ResFontBase::GetEncoding() const
			{
				return (FontEncoding)mFontInfo->mEncoding;
			}
			
			u16 ResFontBase::FindGlyphIndex(const FontCodeMap * pMap, u16 ch) const
			{
				struct Pair
				{
					u16 chr;
					u16 glph;
				};
				
				u16 ret = 0xFFFF;
				
				switch (pMap->mType)
				{
					case FontMap_Linear:
						ret = pMap->mGlyphTable[0] + (ch - pMap->mFirstChar);
						break;
					case FontMap_Array:
						ret = pMap->mGlyphTable[ch - pMap->mFirstChar];
						break;
					case FontMap_Morphism:
						const u16 * pTable = pMap->mGlyphTable;
						
						const Pair * s = reinterpret_cast<const Pair *>(pTable + 1);
						const Pair * e = reinterpret_cast<const Pair *>(++pTable + (2 * (*pTable - 1)));
						
						while (s <= e)
						{
							const Pair * m = s + (e - s) / 2;
							
							if (m->chr < ch) s = m + 1;
							else if (ch < m->chr) e = m - 1;
							else return m->glph;
						}
						
						break;
				}
				
				return ret;
			}
			
			void ResFontBase::GetGlyphFromIndex(Glyph * pGlyph, u16 glyphIndex) const
			{
				FontTextureGlyph * r3 = mFontInfo->mTextureGlyph;
				
				u32 r31 = r3->SHORT_0xC * r3->SHORT_0xE;
				
				u32 r30 = glyphIndex % r31;
				u32 r11 = glyphIndex / r31;
				
				u32 i = r30 / r3->SHORT_0xC;
				u32 j = r30 % r3->SHORT_0xC;
				
				u32 r8 =  j * (r3->mCellWidth + 1);
				u32 r9 =  i * (r3->mCellHeight + 1);
				pGlyph->PTR_0x0 = r3->PTR_0x14 + (r11 * r3->WORD_0x4);//stw r0,0(r4)
				
				const CharWidths & r7_2 = GetCharWidthsFromIndex(glyphIndex);
				
				pGlyph->BYTE_0x4=r7_2.BYTE_0x0;
				pGlyph->cellWidth=r7_2.BYTE_0x1;
				pGlyph->BYTE_0x6=r7_2.BYTE_0x2;
				
				pGlyph->cellHeight=r3->mCellHeight;
				
				pGlyph->WORD_0x8=r3->mFormat;
				
				pGlyph->SHORT_0xC=r3->SHORT_0x10;
				pGlyph->SHORT_0xE=r3->SHORT_0x12;
				
				pGlyph->SHORT_0x10=r8+1;
				pGlyph->SHORT_0x12=r9+1;
			}
		}
	}
}