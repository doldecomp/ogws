#include "ut_IOStream.h"

namespace nw4r
{
	namespace ut
	{
		bool IOStream::ReadAsync(void *, u32, AsyncFunctor, void *)
		{
			return false;
		}
		
		UNKTYPE IOStream::Write(const void *, u32) {}
		
		bool IOStream::WriteAsync(const void *, u32, AsyncFunctor, void *)
		{
			return false;
		}
		
		bool IOStream::IsBusy() const
		{
			return false;
		}
		
		bool IOStream::GetBufferAlign() const
		{
			return true;
		}
		
		bool IOStream::GetSizeAlign() const
		{
			return true;
		}
		
		bool IOStream::GetOffsetAlign() const
		{
			return true;
		}
		
		detail::RuntimeTypeInfo IOStream::typeInfo(NULL);
	}
}