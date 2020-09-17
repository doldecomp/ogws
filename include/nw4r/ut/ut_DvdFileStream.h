#ifndef NW4R_UT_DVD_FILE_STREAM
#define NW4R_UT_DVD_FILE_STREAM
#include "ut_IOStream.h"
#include "ut_FileStream.h"
#include <RevoSDK/DVD/dvd.h>

extern char a[];

namespace nw4r
{
	namespace ut
	{
		struct DvdFileStream : FileStream
		{
			static UNKTYPE DvdAsyncCallback_(s32, DVDFileInfo *);
			static UNKTYPE DvdCBAsyncCallback_(s32, DVDCommandBlock *);
			
			virtual ~DvdFileStream();
			
			DvdFileStream(s32);
			DvdFileStream(const DVDFileInfo *, bool);
			UNKTYPE Close();
			UNKWORD Read(void *, u32);
			bool ReadAsync(void *, u32, AsyncFunctor, void *);
			UNKWORD Peek(void *, u32);
			bool PeekAsync(void *, u32, AsyncFunctor, void *);
			UNKTYPE Seek(s32, u32);
			UNKTYPE Cancel();
			bool CancelAsync(AsyncFunctor, void *);
			u32 GetBufferAlign() const;
			u32 GetSizeAlign() const;
			u32 GetOffsetAlign() const;
			bool CanCancel() const;
			bool CanWrite() const;
			bool CanRead() const;
			bool CanSeek() const;
			bool CanAsync() const;
			u32 GetSize() const;
			UNKTYPE Tell() const;
			bool IsBusy() const;
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			char BYTE_0x4;
			UNKWORD WORD_0x8;
			UNKWORD WORD_0xC;
			UNKWORD WORD_0x10;
			FilePosition mPosition; // at 0x14
			UNKWORD WORD_0x1C;
			UNKWORD WORD_0x20;
			UNKWORD WORD_0x24;
			char UNK_0x28[0x34];
			UNKWORD WORD_0x5C;
			UNKWORD UNK_0x60;
			DvdFileStream * THIS_0x64;
			UNKWORD WORD_0x68;
			char BYTE_0x6C;
			char BYTE_0x6D;
			char BYTE_0x6E;
			
			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}
#endif