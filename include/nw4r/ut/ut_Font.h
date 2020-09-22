#ifndef NW4R_UT_FONT_H
#define NW4R_UT_FONT_H
#include "ut_CharStrmReader.h"
#include "ut_Glyph.h"

namespace nw4r
{
	namespace ut
	{
		struct CharWidths
		{
			char BYTE_0x0;
			char BYTE_0x1;
			char BYTE_0x2;
		};
		
		enum FontEncoding
		{
			FontEnc_UTF8,
			FontEnc_UTF16,
			FontEnc_SJIS,
			FontEnc_CP1252
		};
		
		struct Font
		{
			inline virtual ~Font() {}
			
			virtual u32 GetWidth() const = 0;
			virtual u32 GetHeight() const = 0;
			virtual u32 GetAscent() const = 0;
			virtual u32 GetDescent() const = 0;
			virtual u32 GetBaselinePos() const = 0;
			virtual u32 GetCellHeight() const = 0;
			virtual u32 GetCellWidth() const = 0;
			virtual u32 GetMaxCharWidth() const = 0;
			virtual UNKWORD GetType() const = 0;
			virtual UNKWORD GetTextureFormat() const = 0;
			virtual int GetLineFeed() const = 0;
			virtual CharWidths GetDefaultCharWidths() const = 0;
			virtual void SetDefaultCharWidths(const CharWidths &) = 0;
			virtual bool SetAlternateChar(u16) = 0;
			virtual void SetLineFeed(int) = 0;
			virtual u32 GetCharWidth(u16) const = 0;
			virtual CharWidths GetCharWidths(u16) const = 0;
			virtual void GetGlyph(Glyph *, u16) const = 0;
			virtual FontEncoding GetEncoding() const = 0;
			
			u16 (CharStrmReader::* mReaderFunc)();
			
			void InitReaderFunc(FontEncoding);
			
			/*
			CharStrmReader GetCharStrmReader() const
			{
				return CharStrmReader(PTMF_0x4);
			}
			*/
			
			inline Font() : mReaderFunc(&CharStrmReader::ReadNextCharCP1252) {}
		};
	}
}

#endif