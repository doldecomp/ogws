#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(DvdFileStream, FileStream);

void DvdFileStream::DvdAsyncCallback_(s32 result, DVDFileInfo* pInfo) {
    DvdFileStream* p = reinterpret_cast<AsyncContext*>(pInfo)->pStream;

    p->mIsBusy = false;
    p->mResult = result;

    if (p->mCallback != NULL) {
        p->mCallback(result, p, p->mCallbackArg);
    }
}

void DvdFileStream::DvdCBAsyncCallback_(s32 result, DVDCommandBlock* pBlock) {
    DvdFileStream* p = reinterpret_cast<AsyncContext*>(pBlock)->pStream;

    p->mIsCancelling = false;

    if (p->mCancelCallback != NULL) {
        p->mCancelCallback(result, p, p->mCancelCallbackArg);
    }
}

void DvdFileStream::Initialize_() {
    mCloseOnDestroy = false;
    mAllowClose = false;
    mIsOpen = false;
    mPriority = DVD_PRIO_MEDIUM;
    mIsBusy = false;
    mCallback = NULL;
    mCallbackArg = NULL;
    mResult = DVD_RESULT_OK;
    mCancelCallback = NULL;
    mIsCancelling = false;
    mCancelCallbackArg = NULL;
    mAsyncContext.pStream = this;
}

DvdFileStream::DvdFileStream(s32 entrynum) {
    Initialize_();
    Open(entrynum);
}

DvdFileStream::DvdFileStream(const DVDFileInfo* pInfo, bool close) {
    Initialize_();
    Open(pInfo, close);
}

DvdFileStream::~DvdFileStream() {
    if (mCloseOnDestroy) {
        Close();
    }
}

bool DvdFileStream::Open(s32 entrynum) {
    if (mCloseOnDestroy) {
        Close();
    }

    if (DVDFastOpen(entrynum, &mAsyncContext.info)) {
        mFilePosition.SetFileSize(mAsyncContext.info.size);
        mFilePosition.Seek(0, SEEK_BEG);

        mCloseOnDestroy = true;
        mAllowClose = true;
        mIsOpen = true;

        return true;
    }

    return false;
}

bool DvdFileStream::Open(const DVDFileInfo* pInfo, bool close) {
    if (mCloseOnDestroy) {
        Close();
    }

    mAsyncContext.info = *pInfo;
    mFilePosition.SetFileSize(mAsyncContext.info.size);
    mFilePosition.Seek(0, SEEK_BEG);

    mCloseOnDestroy = false;
    mAllowClose = close;
    mIsOpen = true;

    return true;
}

void DvdFileStream::Close() {
    if (mAllowClose && mIsOpen) {
        DVDClose(&mAsyncContext.info);
        mIsOpen = false;
    }
}

s32 DvdFileStream::Read(void* pDst, u32 size) {
    size = AdjustReadLength_(size);

    s32 result = DVDReadPrio(&mAsyncContext.info, pDst, size,
                             mFilePosition.Tell(), mPriority);

    if (result > 0) {
        mFilePosition.Skip(result);
    }

    return result;
}

bool DvdFileStream::ReadAsync(void* pDst, u32 size, AsyncCallback pCallback,
                              void* pCallbackArg) {
    size = AdjustReadLength_(size);

    bool success =
        DvdFileStream::PeekAsync(pDst, size, pCallback, pCallbackArg);

    if (success) {
        mFilePosition.Skip(size);
    } else {
        mIsBusy = false;
    }

    return success;
}

s32 DvdFileStream::Peek(void* pDst, u32 size) {
    size = AdjustReadLength_(size);

    return DVDReadPrio(&mAsyncContext.info, pDst, size, mFilePosition.Tell(),
                       mPriority);
}

bool DvdFileStream::PeekAsync(void* pDst, u32 size, AsyncCallback pCallback,
                              void* pCallbackArg) {
    mCallback = pCallback;
    mCallbackArg = pCallbackArg;
    mIsBusy = true;

    size = AdjustReadLength_(size);

    return DVDReadAsyncPrio(&mAsyncContext.info, pDst, size,
                            mFilePosition.Tell(), DvdAsyncCallback_, mPriority);
}

void DvdFileStream::Seek(s32 offset, u32 origin) {
    mFilePosition.Seek(offset, origin);
}

void DvdFileStream::Cancel() {
    DVDCancel(&mAsyncContext.info.block);
}

bool DvdFileStream::CancelAsync(AsyncCallback pCallback, void* pCallbackArg) {
    mCancelCallback = pCallback;
    mCancelCallbackArg = pCallbackArg;

    BOOL success =
        DVDCancelAsync(&mAsyncContext.info.block, DvdCBAsyncCallback_);

    if (success) {
        mIsCancelling = true;
    }

    return success;
}

u32 DvdFileStream::AdjustReadLength_(u32 len) {
    u32 fileOffset = mFilePosition.Tell();
    u32 fileSize = mFilePosition.GetFileSize();

    u32 alignSize = RoundUp(fileSize, 32);
    u32 alignPos = RoundUp(fileOffset + len, 32);

    if (alignPos > alignSize) {
        len = RoundUp(fileSize - fileOffset, 32);
    }

    return len;
}

} // namespace ut
} // namespace nw4r
