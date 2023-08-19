#ifndef NW4R_UT_NAND_FILE_STREAM
#define NW4R_UT_NAND_FILE_STREAM
#include <types.h>
#include "ut_IOStream.h"
#include "ut_FileStream.h"
#include <revolution/NAND.h>

namespace nw4r
{
	namespace ut
	{
		struct NandFileStream : FileStream
		{
			struct AsyncContext {
				NANDCommandBlock block; // at 0x0
				NANDFileInfo info;      // at 0xB8
				NandFileStream* stream; // at 0x144
			};

			FilePosition mFilePosition; // at 0x14
			AsyncContext mAsyncContext; // at 0x1C
			
			bool mReadFlag; // at 0x164
			bool mWriteFlag; // at 0x165
			bool mBusyFlag; // at 0x166
			bool BYTE_0x167; // at 0x167
			bool BYTE_0x168; // at 0x168
			
			static void NandAsyncCallback_(s32, NANDCommandBlock *);
			
			NandFileStream(const char *, u32);
			NandFileStream(const NANDFileInfo *, u32, bool);
			
			~NandFileStream();
			
			bool Open(const char *, u32);
			bool Open(const NANDFileInfo *, u32, bool);
			
			UNKTYPE Close();
			
			int Read(void *, u32);
			bool ReadAsync(void *, u32, AsyncFunctor, void *);
			
			UNKTYPE Write(const void *, u32);
			bool WriteAsync(const void *, u32, AsyncFunctor, void *);
			
			UNKTYPE Seek(s32, u32);
			
			u32 GetBufferAlign() const;
			u32 GetSizeAlign() const;
			u32 GetOffsetAlign() const;
			
			bool CanCancel() const;
			bool CanWrite() const;
			bool CanRead() const;
			bool CanSeek() const;
			bool CanAsync() const;
			
			u32 GetSize() const;
			
			u32 Tell() const;
			
			bool IsBusy() const;
			
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			inline void Initialize_()
			{
				mReadFlag = false;
				mWriteFlag = false;
				BYTE_0x167 = false;
				BYTE_0x168 = false;
				BOOL_0x4 = false;
				mBusyFlag = false;
				ASYNC_0xC = NULL;
				PTR_0x10 = NULL;
				WORD_0x8 = 0;
				mAsyncContext.stream = this;
			}
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}

#endif