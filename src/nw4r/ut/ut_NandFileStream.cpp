#include "ut_NandFileStream.h"

namespace nw4r
{
	namespace ut
	{
		UNKTYPE NandFileStream::NandAsyncCallback_(s32 r3, NANDCommandBlock * r4)
		{
			NANDCB_UNK * r4_2 = r4->PTR_0x144;
			
			r4_2->BYTE_0x166 = false;
			r4_2->WORD_0x8 = r3;
			if (!r4_2->CALLBACK_0xC) return;
			r4_2->CALLBACK_0xC(r3, r4_2, r4_2->WORD_0x10);
			return;
		}
		
		NandFileStream::NandFileStream(const char * str, u32 num) : mPosition()
		{
			Initialize_();
			Open(str, num);
		}
		
		NandFileStream::NandFileStream(const NANDFileInfo * fileInfo, u32 num, bool b) : mPosition()
		{
			Initialize_();
			Open(fileInfo, num, b);
		}
		
		NandFileStream::~NandFileStream()
		{
			if (BYTE_0x167) this->Close();
		}
		
		bool NandFileStream::Open(const char * str, u32 num)
		{
			u32 fileSize; // at 0x8
			
			if (BYTE_0x167) this->Close();
			
			mReadFlag = num & 0x00000001;
			mWriteFlag = num & 0x00000002;
			
			if (NANDOpen(str, &mFileInfo, num)) return false;
			
			if (mReadFlag)
			{
				if (NANDGetLength(&mFileInfo, &fileSize) != 0)
				{
					NANDClose(&mFileInfo);
					return false;
				}
				
				mPosition.SetFileSize(fileSize);
			}
			
			mPosition.Seek(0, 0);
			
			BYTE_0x167 = 1;
			BYTE_0x168 = 1;
			BOOL_0x4 = true;
			
			return true;
		}
		
		bool NandFileStream::Open(const NANDFileInfo * fileInfo, u32 num, bool b)
		{
			u32 fileSize; // at 0xc
			
			if (BYTE_0x167) this->Close();
			
			mReadFlag = num & 0x00000001;
			mWriteFlag = num & 0x00000002;
			
			mFileInfo = *fileInfo;
			
			if (NANDGetLength(&mFileInfo, &fileSize) != 0)
			{
				if (b) NANDClose(&mFileInfo);
				
				return false;
			}
			
			mPosition.SetFileSize(fileSize);
			mPosition.Seek(0, 0);
			
			BYTE_0x167 = 0;
			BYTE_0x168 = b;
			BOOL_0x4 = true;
			
			return true;
		}
		
		void NandFileStream::Close()
		{
			if (BYTE_0x168 && BOOL_0x4)
			{
				NANDClose(&mFileInfo);
				BOOL_0x4 = false;
			}
		}
		
		int NandFileStream::Read(void * buf, u32 size)
		{
			int ret;
			
			NANDSeek(&mFileInfo, mPosition.mFileOffset, 0);
			ret = NANDRead(&mFileInfo, buf, size);
			if (ret > 0) mPosition.Skip(ret);
			
			return ret;
		}
		
		bool NandFileStream::ReadAsync(void * buf, u32 size, AsyncFunctor async, void * ptr)
		{
			bool ret;
			ASYNC_0xC = async;
			PTR_0x10 = ptr;
			mBusyFlag = true;
			NANDSeek(&mFileInfo, mPosition.mFileOffset, 0);
			ret = NANDReadAsync(&mFileInfo, buf, size, NandAsyncCallback_, UNK_0x1C) == 0;
			
			if (ret)
			{
				mPosition.Skip(size);
			}
			else
			{
				mBusyFlag = false;
			}
			
			return ret;
		}
		
		UNKTYPE NandFileStream::Write(const void * buf, u32 size)
		{
			NANDSeek(&mFileInfo, mPosition.mFileOffset, 0);
			mPosition.Append(NANDWrite(&mFileInfo, buf, size));
		}
		
		bool NandFileStream::WriteAsync(const void * buf, u32 size, AsyncFunctor async, void * ptr)
		{
			ASYNC_0xC = async;
			PTR_0x10 = ptr;
			mBusyFlag = true;
			NANDSeek(&mFileInfo, mPosition.mFileOffset, 0);
			
			UNKWORD ret = NANDWriteAsync(&mFileInfo, buf, size, NandAsyncCallback_, UNK_0x1C);
			
			if (ret == 0)
			{
				mPosition.Append(size);
			}
			else
			{
				mBusyFlag = false;
			}
			
			return ret == 0;
		}
		
		void NandFileStream::Seek(s32 offset, u32 origin)
		{
			mPosition.Seek(offset, origin);
		}
		
		u32 NandFileStream::GetBufferAlign() const { return 0x20; }
		u32 NandFileStream::GetSizeAlign() const { return 0x20; }
		u32 NandFileStream::GetOffsetAlign() const { return 1; }
		
		bool NandFileStream::CanCancel() const { return false; }
		bool NandFileStream::CanWrite() const { return mWriteFlag; }
		bool NandFileStream::CanRead() const { return mReadFlag; }
		bool NandFileStream::CanSeek() const { return true; }
		bool NandFileStream::CanAsync() const { return true; }
		
		u32 NandFileStream::GetSize() const { return mPosition.mFileSize; }
		u32 NandFileStream::Tell() const { return mPosition.mFileOffset; }

		bool NandFileStream::IsBusy() const { return mBusyFlag; }
		
		const detail::RuntimeTypeInfo * NandFileStream::GetRuntimeTypeInfo() const
		{
			return &typeInfo;
		}
		
		detail::RuntimeTypeInfo NandFileStream::typeInfo(&FileStream::typeInfo);
	}
}