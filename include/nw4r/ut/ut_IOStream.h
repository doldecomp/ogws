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
			
			inline virtual ~IOStream()
			{
				
			}
			
			virtual UNKTYPE Close() = 0;
			virtual UNKWORD Read(void *, u32) = 0;
			virtual bool ReadAsync(void *, u32, AsyncFunctor, void *);
			virtual UNKTYPE Write(const void *, u32);
			virtual bool WriteAsync(const void *, u32, AsyncFunctor, void *);
			virtual bool IsBusy() const;
			virtual bool CanAsync() const = 0;
			virtual bool CanRead() const = 0;
			virtual bool CanWrite() const = 0;
			virtual u32 GetOffsetAlign() const;
			virtual u32 GetSizeAlign() const;
			virtual u32 GetBufferAlign() const;
			virtual u32 GetSize() const = 0;
			virtual UNKTYPE Seek(s32, u32) = 0;
			virtual UNKTYPE Cancel() = 0;
			virtual bool CancelAsync(AsyncFunctor, void *) = 0;
			virtual bool CanSeek() const = 0;
			virtual bool CanCancel() const = 0;
			virtual u32 Tell() const = 0;
			//virtual UNKWORD Peek(void *, u32) = 0;
			//virtual bool PeekAsync(void *, u32, AsyncFunctor, void *) = 0;
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}

#endif