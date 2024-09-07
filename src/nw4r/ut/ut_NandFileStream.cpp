#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(NandFileStream, FileStream);

void NandFileStream::NandAsyncCallback_(s32 result, NANDCommandBlock* pBlock) {
    NandFileStream* p = reinterpret_cast<AsyncContext*>(pBlock)->pStream;

    p->mIsBusy = false;
    p->mResult = result;

    if (p->mCallback != NULL) {
        p->mCallback(result, p, p->mCallbackArg);
    }
}

void NandFileStream::Initialize_() {
    mCanRead = false;
    mCanWrite = false;
    mCloseOnDestroy = false;
    mAllowClose = false;
    mIsOpen = false;
    mIsBusy = false;
    mCallback = NULL;
    mCallbackArg = NULL;
    mResult = NAND_RESULT_OK;
    mAsyncContext.pStream = this;
}

NandFileStream::NandFileStream(const char* pPath, u32 access) {
    Initialize_();
    Open(pPath, access);
}

NandFileStream::NandFileStream(const NANDFileInfo* pInfo, u32 access,
                               bool close) {
    Initialize_();
    Open(pInfo, access, close);
}

NandFileStream::~NandFileStream() {
    if (mCloseOnDestroy) {
        Close();
    }
}

bool NandFileStream::Open(const char* pPath, u32 access) {
    if (mCloseOnDestroy) {
        Close();
    }

    mCanRead = access & NAND_ACCESS_READ;
    mCanWrite = access & NAND_ACCESS_WRITE;

    if (NANDOpen(pPath, &mAsyncContext.info, access) != NAND_RESULT_OK) {
        return false;
    }

    if (mCanRead) {
        u32 fileSize;

        if (NANDGetLength(&mAsyncContext.info, &fileSize) != NAND_RESULT_OK) {
            NANDClose(&mAsyncContext.info);
            return false;
        }

        mFilePosition.SetFileSize(fileSize);
    }

    mFilePosition.Seek(0, SEEK_BEG);

    mCloseOnDestroy = true;
    mAllowClose = true;
    mIsOpen = true;

    return true;
}

bool NandFileStream::Open(const NANDFileInfo* pInfo, u32 access, bool close) {
    if (mCloseOnDestroy) {
        Close();
    }

    mCanRead = access & NAND_ACCESS_READ;
    mCanWrite = access & NAND_ACCESS_WRITE;

    mAsyncContext.info = *pInfo;

    u32 fileSize;
    if (NANDGetLength(&mAsyncContext.info, &fileSize) != NAND_RESULT_OK) {
        if (close) {
            NANDClose(&mAsyncContext.info);
        }

        return false;
    }

    mFilePosition.SetFileSize(fileSize);
    mFilePosition.Seek(0, SEEK_BEG);

    mCloseOnDestroy = false;
    mAllowClose = close;
    mIsOpen = true;

    return true;
}

void NandFileStream::Close() {
    if (mAllowClose && mIsOpen) {
        NANDClose(&mAsyncContext.info);
        mIsOpen = false;
    }
}

s32 NandFileStream::Read(void* pDst, u32 size) {
    NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);

    s32 result = NANDRead(&mAsyncContext.info, pDst, size);
    if (result > 0) {
        mFilePosition.Skip(result);
    }

    return result;
}

bool NandFileStream::ReadAsync(void* pDst, u32 size, AsyncCallback pCallback,
                               void* pCallbackArg) {
    mCallback = pCallback;
    mCallbackArg = pCallbackArg;
    mIsBusy = true;

    NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);

    bool success =
        NANDReadAsync(&mAsyncContext.info, pDst, size, NandAsyncCallback_,
                      &mAsyncContext.block) == NAND_RESULT_OK;

    if (success) {
        mFilePosition.Skip(size);
    } else {
        mIsBusy = false;
    }

    return success;
}

void NandFileStream::Write(const void* pSrc, u32 size) {
    NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);
    s32 result = NANDWrite(&mAsyncContext.info, pSrc, size);

    // @bug Error code will be interpreted as a negative size
    mFilePosition.Append(result);
}

bool NandFileStream::WriteAsync(const void* pSrc, u32 size,
                                AsyncCallback pCallback, void* pCallbackArg) {
    mCallback = pCallback;
    mCallbackArg = pCallbackArg;
    mIsBusy = true;

    NANDSeek(&mAsyncContext.info, mFilePosition.Tell(), NAND_SEEK_BEG);

    s32 result = NANDWriteAsync(&mAsyncContext.info, pSrc, size,
                                NandAsyncCallback_, &mAsyncContext.block);

    if (result == NAND_RESULT_OK) {
        mFilePosition.Append(size);
    } else {
        mIsBusy = false;
    }

    return result == NAND_RESULT_OK;
}

void NandFileStream::Seek(s32 offset, u32 origin) {
    mFilePosition.Seek(offset, origin);
}

} // namespace ut
} // namespace nw4r
