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
				mFileOffset = Clamp<s64>(0, mFileSize, mFileOffset + offset);
			}
			
			return mFileOffset;
		}
		
		u32 FileStream::FilePosition::Append(s32 offset)
		{
			s64 r5 = mFileOffset + offset;
			
			if (r5 < 0LL)
			{
				mFileOffset = 0;
			}
			else
			{
				mFileOffset = r5;
				mFileSize = Max<u32>(mFileOffset, mFileSize);
			}
			
			return mFileOffset;
		}
		
		void FileStream::FilePosition::Seek(s32 offset, u32 origin)
		{
			switch (origin)
			{
				case 0:
					mFileOffset = 0;
					break;
				case 2:
					mFileOffset = mFileSize;
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