#ifndef NW4R_UT_FONT_H
#define NW4R_UT_FONT_H
#include "ut_CharStrmReader.h"

namespace nw4r
{
	namespace ut
	{
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
			
			u16 (CharStrmReader::* mReaderFunc)();
			
			void InitReaderFunc(FontEncoding);
			
			/*
			CharStrmReader GetCharStrmReader() const
			{
				return CharStrmReader(PTMF_0x4);
			}
			*/
		};
	}
}

#endif