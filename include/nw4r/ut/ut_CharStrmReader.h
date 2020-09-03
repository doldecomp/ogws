#ifndef NW4R_UT_CHAR_STRM_READER
#define NW4R_UT_CHAR_STRM_READER
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		struct CharStrmReader
		{
			const char * mStrm;
			
			inline CharStrmReader(u16 (CharStrmReader::*)())
			{
				
			}
			
			u16 ReadNextCharUTF8();
			u16 ReadNextCharUTF16();
			u16 ReadNextCharCP1252();
			u16 ReadNextCharSJIS();
			
			template <typename T>
			inline T GetChar(int offset) const
			{
				const T * strm = reinterpret_cast<const T *>(mStrm);
				return strm[offset];
			}
			
			template <typename T>
			inline void StepStrm(int offset) volatile
			{
				mStrm += sizeof(T) * offset;
			}
		};
	}
}

#endif