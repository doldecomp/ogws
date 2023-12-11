#pragma ipa file

#include "ut_DvdFileStream.h"
#include "ut_IOStream.h"

namespace nw4r
{
    namespace ut
    {
        void DvdFileStream::DvdAsyncCallback_(s32 r3, DVDFileInfo *pInfo)
        {
            FileInfoStreamPair *pPair = (FileInfoStreamPair *)pInfo;
            DvdFileStream *pStrm = pPair->mStrm;
            pStrm->mIsBusy = false;
            pStrm->mResult = r3;

            if (pStrm->mCallback)
            {
                pStrm->mCallback(r3, pStrm, pStrm->mCallbackArg);
            }
        }

        void DvdFileStream::DvdCBAsyncCallback_(s32 r3, DVDCommandBlock *pCmd)
        {
            FileInfoStreamPair *pPair = (FileInfoStreamPair *)pCmd;
            DvdFileStream *pStrm = pPair->mStrm;
            pStrm->BYTE_0x24 = 0;

            if (pStrm->ASYNC_0x1C)
            {
                pStrm->ASYNC_0x1C(r3, pStrm, pStrm->PTR_0x20);
            }
        }

        DvdFileStream::DvdFileStream(s32 r3)
        {
            Initialize_();
            Open(r3);
        }

        DvdFileStream::DvdFileStream(const DVDFileInfo *pInfo, bool b)
        {
            Initialize_();
            Open(pInfo, b);
        }

        DvdFileStream::~DvdFileStream()
        {
            if (BOOL_0x6D)
            {
                Close();
            }
        }

        void DvdFileStream::Close()
        {
            if (BOOL_0x6E && mIsOpen)
            {
                DVDClose(&mFileInfo);
                mIsOpen = false;
            }
        }

        s32 DvdFileStream::Read(void *pData, u32 len)
        {
            len = AdjustReadLength_(len);
            u32 pos = mPosition.Tell();
            s32 bytesRead = DVDReadPrio(&mFileInfo, pData, len, mPosition.Tell(), WORD_0x68);
            if (bytesRead > 0)
            {
                mPosition.Skip(bytesRead);
            }
            
            return bytesRead;
        }

        bool DvdFileStream::ReadAsync(void * pData, u32 len, AsyncCallback func, void *r7)
        {
            len = AdjustReadLength_(len);
            bool result = DvdFileStream::PeekAsync(pData, len, func, r7);
            if (result)
            {
                mPosition.Skip(len);
            }
            else
            {
                mIsBusy = false;
            }
            
            return result;
        }

        UNKWORD DvdFileStream::Peek(void *pData, u32 len)
        {
            len = AdjustReadLength_(len);
            u32 pos = mPosition.Tell();
            
            return DVDReadPrio(&mFileInfo, pData, len, pos, WORD_0x68);
        }

        bool DvdFileStream::PeekAsync(void * pData, u32 len, AsyncCallback func, void *r7)
        {
            mCallback = func;
            mCallbackArg = r7;
            mIsBusy = 1;
            len = AdjustReadLength_(len);
            u32 pos = mPosition.Tell();

            return (DVDReadAsyncPrio(&mFileInfo, pData, len, pos, DvdAsyncCallback_, WORD_0x68) != 0);
        }

        void DvdFileStream::Seek(s32 offset, u32 origin)
        {
            mPosition.Seek(offset, origin);
        }

        UNKTYPE DvdFileStream::Cancel()
        {
            DVDCancel(&mFileInfo.block);
        }

        bool DvdFileStream::CancelAsync(AsyncCallback func, void *p)
        {
            ASYNC_0x1C = func;
            PTR_0x20 = p;
            u32 result = DVDCancelAsync(&mFileInfo.block, DvdCBAsyncCallback_);
            if (result)
            {
                BYTE_0x24 = 1;
            }

            return (result != 0);
        }

        u32 DvdFileStream::GetBufferAlign() const
        {
            return 32;
        }

        u32 DvdFileStream::GetSizeAlign() const
        {
            return 32;
        }

        u32 DvdFileStream::GetOffsetAlign() const
        {
            return 4;
        }

        bool DvdFileStream::CanCancel() const
        {
            return true;
        }

        bool DvdFileStream::CanWrite() const
        {
            return false;
        }

        bool DvdFileStream::CanRead() const
        {
            return true;
        }

        bool DvdFileStream::CanSeek() const
        {
            return true;
        }

        bool DvdFileStream::CanAsync() const
        {
            return true;
        }

        u32 DvdFileStream::GetSize() const
        {
            return mPosition.GetFileSize();
        }

        u32 DvdFileStream::Tell() const
        {
            return mPosition.Tell();
        }

        bool DvdFileStream::IsBusy() const
        {
            return mIsBusy;
        }

        const detail::RuntimeTypeInfo * DvdFileStream::GetRuntimeTypeInfo() const
        {
            return &typeInfo;
        }

        detail::RuntimeTypeInfo DvdFileStream::typeInfo(&FileStream::typeInfo);
    }
}