#ifndef NW4R_UT_IO_STREAM
#define NW4R_UT_IO_STREAM
#include "types_nw4r.h"
#include "ut_RTTI.h"

namespace nw4r
{
	namespace ut
	{
		struct IOStream : Polymorphic
		{
			typedef void (* AsyncFunctor)(s32, IOStream *, void *);
			
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			virtual UNKTYPE Close() = 0;
			inline virtual ~IOStream()
			{
				
			}
			
			virtual UNKTYPE Read(void *, u32) = 0;
			virtual bool ReadAsync(void *, u32, AsyncFunctor, void *);
			virtual UNKTYPE Write(const void *, u32);
			virtual bool WriteAsync(const void *, u32, AsyncFunctor, void *);
			virtual bool IsBusy() const;
			virtual bool CanAsync() const = 0;
			virtual bool CanRead() const = 0;
			virtual bool CanWrite() const = 0;
			virtual bool GetOffsetAlign() const;
			virtual bool GetSizeAlign() const;
			virtual bool GetBufferAlign() const;
			virtual bool GetSize() const = 0;
			virtual UNKTYPE Seek(s32, u32) = 0;
			virtual UNKTYPE Cancel() = 0;
			virtual UNKTYPE CancelAsync(AsyncFunctor, void *) = 0;
			virtual bool CanSeek() const = 0;
			virtual bool CanCancel() const = 0;
			virtual UNKTYPE Tell() const = 0;
			virtual UNKTYPE Peek(void *, u32) = 0;
			virtual UNKTYPE PeekAsync(void *, u32, AsyncFunctor, void *) = 0;
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}

#endif