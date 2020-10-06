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
			
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;
			virtual int GetAscent() const = 0;
			virtual int GetDescent() const = 0;
			virtual int GetBaselinePos() const = 0;
			virtual int GetCellHeight() const = 0;
			virtual int GetCellWidth() const = 0;
			virtual int GetMaxCharWidth() const = 0;
			virtual UNKWORD GetType() const = 0;
			virtual UNKWORD GetTextureFormat() const = 0;
			virtual int GetLineFeed() const = 0;
			virtual CharWidths GetDefaultCharWidths() const = 0;
			virtual void SetDefaultCharWidths(const CharWidths &) = 0;
			virtual bool SetAlternateChar(u16) = 0;
			virtual void SetLineFeed(int) = 0;
			virtual int GetCharWidth(u16) const = 0;
			virtual CharWidths GetCharWidths(u16) const = 0;
			virtual void GetGlyph(Glyph *, u16) const = 0;
			virtual FontEncoding GetEncoding() const = 0;
			
			u16 (CharStrmReader::* mReaderFunc)();
			
			void InitReaderFunc(FontEncoding);
			
			
			inline CharStrmReader GetCharStrmReader() const __attribute__((never_inline))
			{
				return CharStrmReader(mReaderFunc);
			}
			
			
			inline Font() : mReaderFunc(&CharStrmReader::ReadNextCharCP1252) {}
		};
	}
}

#endif