#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(DvdFileStream, FileStream);

void DvdFileStream::DvdAsyncCallback_(s32 result, DVDFileInfo* pInfo) {
    DvdFileStream* p = reinterpret_cast<DvdFileStreamInfo*>(pInfo)->stream;

    p->mIsBusy = false;
    p->mAsyncResult = result;

    if (p->mCallback != NULL) {
        p->mCallback(result, p, p->mArg);
    }
}

void DvdFileStream::DvdCBAsyncCallback_(s32 result, DVDCommandBlock* pBlock) {
    DvdFileStream* p = reinterpret_cast<DvdFileStreamInfo*>(pBlock)->stream;

    p->mIsCanceling = false;

    if (p->mCancelCallback != NULL) {
        p->mCancelCallback(result, p, p->mCancelArg);
    }
}

void DvdFileStream::Initialize_() {
    mCloseOnDestroyFlg = false;
    mCloseEnableFlg = false;

    mAvailable = false;
    mPriority = DVD_PRIO_MEDIUM;
    mIsBusy = false;

    mCallback = NULL;
    mArg = NULL;
    mAsyncResult = DVD_RESULT_OK;

    mCancelCallback = NULL;
    mIsCanceling = false;
    mCancelArg = NULL;

    mFileInfo.stream = this;
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
    if (mCloseOnDestroyFlg) {
        Close();
    }
}

bool DvdFileStream::Open(s32 entrynum) {
    if (mCloseOnDestroyFlg) {
        Close();
    }

    if (DVDFastOpen(entrynum, &mFileInfo.dvdInfo)) {
        mFilePosition.SetFileSize(mFileInfo.dvdInfo.size);
        mFilePosition.Seek(0, SEEK_BEG);

        mCloseOnDestroyFlg = true;
        mCloseEnableFlg = true;
        mAvailable = true;

        return true;
    }

    return false;
}

bool DvdFileStream::Open(const DVDFileInfo* pInfo, bool close) {
    if (mCloseOnDestroyFlg) {
        Close();
    }

    mFileInfo.dvdInfo = *pInfo;
    mFilePosition.SetFileSize(mFileInfo.dvdInfo.size);
    mFilePosition.Seek(0, SEEK_BEG);

    mCloseOnDestroyFlg = false;
    mCloseEnableFlg = close;
    mAvailable = true;

    return true;
}

void DvdFileStream::Close() {
    if (mCloseEnableFlg && mAvailable) {
        DVDClose(&mFileInfo.dvdInfo);
        mAvailable = false;
    }
}

s32 DvdFileStream::Read(void* pDst, u32 size) {
    size = AdjustReadLength_(size);

    s32 result = DVDReadPrio(&mFileInfo.dvdInfo, pDst, size,
                             mFilePosition.Tell(), mPriority);

    if (result > 0) {
        mFilePosition.Skip(result);
    }

    return result;
}

bool DvdFileStream::ReadAsync(void* pDst, u32 size, StreamCallback pCallback,
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

    return DVDReadPrio(&mFileInfo.dvdInfo, pDst, size, mFilePosition.Tell(),
                       mPriority);
}

bool DvdFileStream::PeekAsync(void* pDst, u32 size, StreamCallback pCallback,
                              void* pCallbackArg) {
    mCallback = pCallback;
    mArg = pCallbackArg;
    mIsBusy = true;

    size = AdjustReadLength_(size);

    return DVDReadAsyncPrio(&mFileInfo.dvdInfo, pDst, size,
                            mFilePosition.Tell(), DvdAsyncCallback_, mPriority);
}

void DvdFileStream::Seek(s32 offset, u32 origin) {
    mFilePosition.Seek(offset, origin);
}

void DvdFileStream::Cancel() {
    DVDCancel(&mFileInfo.dvdInfo.block);
}

bool DvdFileStream::CancelAsync(StreamCallback pCallback, void* pCallbackArg) {
    mCancelCallback = pCallback;
    mCancelArg = pCallbackArg;

    BOOL success =
        DVDCancelAsync(&mFileInfo.dvdInfo.block, DvdCBAsyncCallback_);

    if (success) {
        mIsCanceling = true;
    }

    return success;
}

u32 DvdFileStream::AdjustReadLength_(u32 len) {
    u32 currOffset = mFilePosition.Tell();
    u32 fileSize = mFilePosition.GetFileSize();

    if (RoundUp(currOffset + len, 32) > RoundUp(fileSize, 32)) {
        len = RoundUp(fileSize - currOffset, 32);
    }

    return len;
}

} // namespace ut
} // namespace nw4r
