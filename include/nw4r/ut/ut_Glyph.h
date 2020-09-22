#ifndef NW4R_UT_GLYPH
#define NW4R_UT_GLYPH
#include <types.h>

namespace nw4r
{
	namespace ut
	{
		struct Glyph
		{
			UNKWORD WORD_0x0;
			///*
			char BYTE_0x4;
			char BYTE_0x5;
			char BYTE_0x6;
			char BYTE_0x7;
			
			//char BYTES_0x4[4];
			
			UNKWORD WORD_0x8;
			
			unsigned short SHORT_0xC;
			unsigned short SHORT_0xE;
			unsigned short SHORT_0x10;
			unsigned short SHORT_0x12;
		};
	}
}

#endif