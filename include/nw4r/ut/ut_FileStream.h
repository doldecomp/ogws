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
				u32 mFileSize;
				u32 mFileOffset;
				
				u32 Skip(s32);
				u32 Append(s32);
				void Seek(s32, u32);
				
				inline FilePosition() : mFileSize(), mFileOffset() {}
				
				inline void SetFileSize(u32 fileSize)
				{
					mFileSize = fileSize;
				}
			};
			
			bool BOOL_0x4;
			UNKWORD WORD_0x8;
			AsyncFunctor ASYNC_0xC;
			void * PTR_0x10;
			
			inline FileStream() : BOOL_0x4(false), ASYNC_0xC(NULL), PTR_0x10(NULL) {}
			
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			UNKTYPE Cancel();
			bool CancelAsync(AsyncFunctor, void *);
			
			inline virtual ~FileStream() {}
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}

#endif