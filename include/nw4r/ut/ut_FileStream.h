#ifndef UT_FILE_STREAM_H
#define UT_FILE_STREAM_H
#include "ut_IOStream.h"

namespace nw4r
{
	namespace ut
	{
		struct FileStream : IOStream
		{
			struct FilePosition
			{
				u32 LONG_0x0;
				u32 LONG_0x4;
				
				u32 Skip(s32);
				u32 Append(s32);
				void Seek(s32, u32);
			};
			
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			UNKTYPE Cancel();
			bool CancelAsync(AsyncFunctor, void *);
			
			inline virtual ~FileStream() {}
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}

#endif