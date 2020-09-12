#ifndef NW4R_UT_TEXT_WRITER_BASE
#define NW4R_UT_TEXT_WRITER_BASE
#include "types_nw4r.h"
#include "ut_CharWriter.h"

namespace nw4r
{
	namespace ut
	{
		// TODO: Implement the object accurately
		template<typename T>
		struct TextWriterBase : CharWriter
		{
			UNKWORD WORD_0x4C;
			UNKWORD WORD_0x50;
			UNKWORD WORD_0x54;
			u32 mTabWidth;
			
			inline u32 GetTabWidth() const
			{
				return mTabWidth;
			}
			
			float GetLineHeight() const;
		};
	}
}

#endif