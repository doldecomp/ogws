#include "ut_RomFont.h"
#include "ut_algorithm.h"
#include <RevoSDK/OS/OSFont.h>

namespace nw4r
{
	
	namespace ut
	{
		namespace
		{
			inline bool IsCP1252Char(u16 ch)
			{
				return (ch >= 0x20) && (ch <= 0xFF);
			}
			
			inline bool IsSJISHalfWidthChar(u16 ch)
			{
				if (ch > 0xFF) return false;
				
				return ((ch >= 0x20) && (ch <= 0x7E)) || ((ch >= 0xA1) && (ch <= 0xDF));
			}
			
			static inline bool IsSJISLeadByte(u8 hi)
			{
				return (hi >= 0x81) && (hi <= 0x98); 
			}
			
			static inline bool IsSJISTrailByte(u8 lo)
			{
				return (lo >= 0x40) && (lo <= 0xFC);
			}
			
			inline bool IsSJISFullWidthChar(u16 ch)
			{
				u8 hi;
				u8 lo;
				
				hi = BitExtract<u16>(ch, 8, 8);
				lo = BitExtract<u16>(ch, 8, 0);
				
				return IsSJISLeadByte(hi) && IsSJISTrailByte(lo);
			}
		}
		
		RomFont::RomFont() : mBuffer(), mAlternateChar('\?')//, mDefaultCharWidths()
		{
			mDefaultCharWidths.BYTE_0x0 = 0;
			mDefaultCharWidths.BYTE_0x1 = 0;
			mDefaultCharWidths.BYTE_0x2 = 0;
		}
		
		RomFont::~RomFont() {}
		
		bool RomFont::Load(void * pBuffer)
		{
			if (mBuffer) return false;
			
			UNKWORD ret = OSInitFont(pBuffer);
			
			if (ret)
			{
				mFontEncode = OSGetFontEncode();
				
				mBuffer = pBuffer;
				
				mDefaultCharWidths.BYTE_0x0 = 0;
				mDefaultCharWidths.BYTE_0x1 = GetCellWidth();
				mDefaultCharWidths.BYTE_0x2 = GetMaxCharWidth();
				
				InitReaderFunc(GetEncoding());
			}
			
			return ret;
		}
		
		u32 RomFont::GetRequireBufferSize()
		{
			switch (OSGetFontEncode())
			{
				case OS_ENCODE_CP1252:
					return 0x00020120;
				case OS_ENCODE_SJIS:
					return 0x00120F00;
			}
			
			return 0;
		}
		
		u32 RomFont::GetWidth() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->charWidth;
		}
		
		u32 RomFont::GetHeight() const
		{
			return GetAscent() + GetDescent();
		}
		
		u32 RomFont::GetAscent() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->ascent;
		}
		
		u32 RomFont::GetDescent() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->descent;
		}
		
		u32 RomFont::GetBaselinePos() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->ascent;
		}
		
		u32 RomFont::GetCellHeight() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->cellHeight;
		}
		
		u32 RomFont::GetCellWidth() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->cellWidth;
		}
		
		u32 RomFont::GetMaxCharWidth() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->charWidth;
		}
		
		UNKWORD RomFont::GetType() const
		{
			return 1;
		}
		
		UNKWORD RomFont::GetTextureFormat() const
		{
			return 0;
		}
		
		int RomFont::GetLineFeed() const
		{
			return static_cast<OSFontHeader *>(mBuffer)->linefeed;
		}
		
		CharWidths RomFont::GetDefaultCharWidths() const
		{
			return mDefaultCharWidths;
		}
		
		void RomFont::SetDefaultCharWidths(const CharWidths & rDefaultCharWidths)
		{
			mDefaultCharWidths = rDefaultCharWidths;
		}
		
		bool RomFont::HandleUndefinedChar(u16 undefChar) const
		{
			switch (mFontEncode)
			{
				case OS_ENCODE_CP1252:
					return IsCP1252Char(undefChar);
				case OS_ENCODE_SJIS:
					return IsSJISHalfWidthChar(undefChar) || IsSJISFullWidthChar(undefChar);
			}
		}
		
		bool RomFont::SetAlternateChar(u16 alt)
		{
			
			u16 prevAlt;
			
			u8 lo;
			u8 hi;
			
			bool cond;
			
			prevAlt = mAlternateChar;
			
			mAlternateChar = 0xFFFF;
			
			//cond = HandleUndefinedChar(alt);
			switch (mFontEncode)
			{
				case OS_ENCODE_CP1252:
					cond = IsCP1252Char(alt);
					break;
				case OS_ENCODE_SJIS:
					cond = IsSJISHalfWidthChar(alt) || (
						hi = BitExtract<u16>(alt, 8, 8),
						lo = BitExtract<u16>(alt, 8, 0),
						IsSJISLeadByte(hi) && IsSJISTrailByte(lo)
					);
					break;
			}
			
			if ((cond ? alt : mAlternateChar) != 0xFFFF)
			{
				mAlternateChar = alt;
				return true;
			}
			
			mAlternateChar = prevAlt;
			return false;
		}
		
		void RomFont::SetLineFeed(int lf)
		{
			static_cast<OSFontHeader *>(mBuffer)->linefeed = lf;
		}
		
		u32 RomFont::GetCharWidth(u16 ch) const
		{
			bool cond;
			
			u8 hi;
			u8 lo;
			
			u8 nch;
			
			u32 width;
			char str[4];
			
			cond = HandleUndefinedChar(ch);
			
			ch = cond ? ch : mAlternateChar;
			
			if ((nch = BitExtract<u16>(ch, 8, 8)) == 0)
			{
				str[0] = ch;
				str[1] = '\0';
			}
			else
			{
				str[0] = nch;
				str[1] = ch;
				str[2] = '\0';
			}
			
			OSGetFontWidth(str, &width);
			
			return width;
		}
		
		CharWidths RomFont::GetCharWidths(u16 ch) const
		{
			u8 chWidth = GetCharWidth(ch);
			
			CharWidths widths;
			
			widths.BYTE_0x1 = chWidth;
			widths.BYTE_0x0 = 0;
			widths.BYTE_0x2 = chWidth;
			
			return widths;
		}
		
		void RomFont::GetGlyph(Glyph * pGlyph, u16 ch) const
		{
			bool cond;
			
			u8 hi;
			u8 lo;
			
			u8 nch;
			
			UNKWORD stack_0x18;
			UNKWORD stack_0x14;
			UNKWORD stack_0x10;
			UNKWORD stack_0xc;
			
			char str[4];
			
			OSFontHeader * header;
			
			cond = HandleUndefinedChar(ch);
			
			ch = cond ? ch : mAlternateChar;
			
			if ((nch = BitExtract<u16>(ch, 8, 8)) == 0)
			{
				str[0] = ch;
				str[1] = '\0';
			}
			else
			{
				str[0] = nch;
				str[1] = ch;
				str[2] = '\0';
			}
			
			OSGetFontTexture(str, &stack_0x18, &stack_0x14, &stack_0x10, &stack_0xc);
			
			pGlyph->WORD_0x0 = stack_0x18;
			
			pGlyph->BYTE_0x4 = 0;
			pGlyph->BYTE_0x5 = stack_0xc;
			pGlyph->BYTE_0x6 = stack_0xc;
			pGlyph->BYTE_0x7 = static_cast<OSFontHeader *>(mBuffer)->cellHeight;
			
			pGlyph->WORD_0x8 = 0;
			
			pGlyph->SHORT_0xC = static_cast<OSFontHeader *>(mBuffer)->SHORT_0x1E;
			pGlyph->SHORT_0xE = static_cast<OSFontHeader *>(mBuffer)->SHORT_0x20;
			pGlyph->SHORT_0x10 = stack_0x14;
			pGlyph->SHORT_0x12 = stack_0x10;
		}
		
		FontEncoding RomFont::GetEncoding() const
		{
			switch (mFontEncode)
			{
				case OS_ENCODE_CP1252:
					return FontEnc_CP1252;
				case OS_ENCODE_SJIS:
					return FontEnc_SJIS;
			}
			
			return FontEnc_CP1252;
		}
		
		u16 RomFont::mFontEncode = -1;
	}
}