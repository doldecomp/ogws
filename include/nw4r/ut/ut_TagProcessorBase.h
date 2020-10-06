#ifndef NW4R_UT_TAG_PROCESSOR_BASE
#define NW4R_UT_TAG_PROCESSOR_BASE
#include "types_nw4r.h"
#include "ut_Rect.h"

namespace nw4r
{
	namespace ut
	{		
		template<typename T>
		struct PrintContext
		{
			TextWriterBase<T> * mTextWriter;
			
			const T * PTR_0x4;
			
			float FLOAT_0x8;
			float FLOAT_0xC;
			int WORD_0x10;
		};
		
		template<typename T>
		struct TagProcessorBase
		{
			TagProcessorBase();
			virtual ~TagProcessorBase();
			
			void ProcessTab(PrintContext<T> *); //inlined
			void ProcessLinefeed(PrintContext<T> *); //inlined
			
			virtual int Process(u16, PrintContext<T> *);
			virtual int CalcRect(register Rect *, u16, PrintContext<T> *);			
		};
	}
}

#endif