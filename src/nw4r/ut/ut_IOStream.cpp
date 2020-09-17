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
		
		u32 IOStream::GetBufferAlign() const
		{
			return 1;
		}
		
		u32 IOStream::GetSizeAlign() const
		{
			return 1;
		}
		
		u32 IOStream::GetOffsetAlign() const
		{
			return 1;
		}
		
		detail::RuntimeTypeInfo IOStream::typeInfo(NULL);
	}
}