#include "ut_FileStream.h"
#include "ut_algorithm.h"

namespace nw4r
{
	namespace ut
	{
		UNKTYPE FileStream::Cancel() {}
		
		bool FileStream::CancelAsync(AsyncFunctor, void *)
		{
			return true;
		}
		
		u32 FileStream::FilePosition::Skip(s32 offset)
		{
			if (offset)
			{
				LONG_0x4 = Clamp<s64>(0, mFileSize, LONG_0x4 + offset);
			}
			
			return this->LONG_0x4;
		}
		
		u32 FileStream::FilePosition::Append(s32 offset)
		{
			s64 r5 = LONG_0x4 + offset;
			
			if (r5 < 0LL)
			{
				LONG_0x4 = 0;
			}
			else
			{
				LONG_0x4 = r5;
				mFileSize = Max<u32>(LONG_0x4, mFileSize);
			}
			
			return this->LONG_0x4;
		}
		
		void FileStream::FilePosition::Seek(s32 offset, u32 origin)
		{
			switch (origin)
			{
				case 0:
					LONG_0x4 = 0;
					break;
				case 2:
					LONG_0x4 = mFileSize;
					break;
				case 1:
				default:
					break;
			}
			
			Skip(offset);
		}
		
		const detail::RuntimeTypeInfo * FileStream::GetRuntimeTypeInfo() const
		{
			return &typeInfo;
		}
		
		detail::RuntimeTypeInfo FileStream::typeInfo(&IOStream::typeInfo);
	}
}