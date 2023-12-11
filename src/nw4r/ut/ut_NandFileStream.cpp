#include "ut_NandFileStream.h"

namespace nw4r
{
	namespace ut
	{
		void NandFileStream::NandAsyncCallback_(s32 result, NANDCommandBlock* block) {
			NandFileStream* strm = reinterpret_cast<AsyncContext*>(block)->stream;

			strm->mBusyFlag = false;
			strm->mResult = result;

			if (strm->mCallback != NULL) {
				strm->mCallback(result, strm, strm->mCallbackArg);
			}
		}
		
		NandFileStream::NandFileStream(const char * str, u32 num) : mFilePosition()
		{
			Initialize_();
			Open(str, num);
		}
		
		NandFileStream::NandFileStream(const NANDFileInfo * fileInfo, u32 num, bool b) : mFilePosition()
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
			
			if (NANDOpen(str, &mAsyncContext.info, num)) return false;
			
			if (mReadFlag)
			{
				if (NANDGetLength(&mAsyncContext.info, &fileSize) != 0)
				{
					NANDClose(&mAsyncContext.info);
					return false;
				}
				
				mFilePosition.SetFileSize(fileSize);
			}
			
			mFilePosition.Seek(0, 0);
			
			BYTE_0x167 = 1;
			BYTE_0x168 = 1;
			mIsOpen = true;
			
			return true;
		}
		
		bool NandFileStream::Open(const NANDFileInfo * fileInfo, u32 num, bool b)
		{
			u32 fileSize; // at 0xc
			
			if (BYTE_0x167) this->Close();
			
			mReadFlag = num & 0x00000001;
			mWriteFlag = num & 0x00000002;
			
			mAsyncContext.info = *fileInfo;
			
			if (NANDGetLength(&mAsyncContext.info, &fileSize) != 0)
			{
				if (b) NANDClose(&mAsyncContext.info);
				
				return false;
			}
			
			mFilePosition.SetFileSize(fileSize);
			mFilePosition.Seek(0, 0);
			
			BYTE_0x167 = 0;
			BYTE_0x168 = b;
			mIsOpen = true;
			
			return true;
		}
		
		void NandFileStream::Close()
		{
			if (BYTE_0x168 && mIsOpen)
			{
				NANDClose(&mAsyncContext.info);
				mIsOpen = false;
			}
		}
		
		s32 NandFileStream::Read(void * buf, u32 size)
		{
			int ret;
			
			NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);
			ret = NANDRead(&mAsyncContext.info, buf, size);
			if (ret > 0) mFilePosition.Skip(ret);
			
			return ret;
		}
		
		bool NandFileStream::ReadAsync(void * buf, u32 size, AsyncCallback async, void * ptr)
		{
			bool ret;
			mCallback = async;
			mCallbackArg = ptr;
			mBusyFlag = true;
			NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);
			ret = NANDReadAsync(&mAsyncContext.info, buf, size, NandAsyncCallback_, &mAsyncContext.block) == 0;
			
			if (ret)
			{
				mFilePosition.Skip(size);
			}
			else
			{
				mBusyFlag = false;
			}
			
			return ret;
		}
		
		UNKTYPE NandFileStream::Write(const void * buf, u32 size)
		{
			NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);
			mFilePosition.Append(NANDWrite(&mAsyncContext.info, buf, size));
		}
		
		bool NandFileStream::WriteAsync(const void * buf, u32 size, AsyncCallback async, void * ptr)
		{
			mCallback = async;
			mCallbackArg = ptr;
			mBusyFlag = true;
			NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);
			
			UNKWORD ret = NANDWriteAsync(&mAsyncContext.info, buf, size, NandAsyncCallback_, &mAsyncContext.block);
			
			if (ret == 0)
			{
				mFilePosition.Append(size);
			}
			else
			{
				mBusyFlag = false;
			}
			
			return ret == 0;
		}
		
		void NandFileStream::Seek(s32 offset, u32 origin)
		{
			mFilePosition.Seek(offset, origin);
		}
		
		u32 NandFileStream::GetBufferAlign() const { return 0x20; }
		u32 NandFileStream::GetSizeAlign() const { return 0x20; }
		u32 NandFileStream::GetOffsetAlign() const { return 1; }
		
		bool NandFileStream::CanCancel() const { return false; }
		bool NandFileStream::CanWrite() const { return mWriteFlag; }
		bool NandFileStream::CanRead() const { return mReadFlag; }
		bool NandFileStream::CanSeek() const { return true; }
		bool NandFileStream::CanAsync() const { return true; }
		
		u32 NandFileStream::GetSize() const { return mFilePosition.GetFileSize(); }
		u32 NandFileStream::Tell() const { return mFilePosition.Tell(); }

		bool NandFileStream::IsBusy() const { return mBusyFlag; }
		
		const detail::RuntimeTypeInfo * NandFileStream::GetRuntimeTypeInfo() const
		{
			return &typeInfo;
		}
		
		detail::RuntimeTypeInfo NandFileStream::typeInfo(&FileStream::typeInfo);
	}
}