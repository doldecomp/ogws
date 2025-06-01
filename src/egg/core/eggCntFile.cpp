// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/CNT.h>
#include <revolution/OS.h>

namespace EGG {

nw4r::ut::List CntFile::sCntList;
bool CntFile::sIsInitialized = false;

DECOMP_FORCEACTIVE(eggCntFile_cpp,
                   CntFile::getFileSize);

CntFile::CntFile() {
    initiate();
}

CntFile::~CntFile() {
    close();
}

void CntFile::initiate() {
    mAsyncContext.pFile = this;
    mAsyncContext.pHandle = NULL;

    OSInitMutex(&mSyncMutex);
    OSInitMutex(&mAsyncMutex);

    OSInitMessageQueue(&mSyncQueue, mSyncBuffer, ARRAY_SIZE(mAsyncBuffer));
    OSInitMessageQueue(&mAsyncQueue, mAsyncBuffer, ARRAY_SIZE(mAsyncBuffer));

    mSyncThread = NULL;
    mAsyncThread = NULL;
}

bool CntFile::open(const char* pPath, CNTHandle* pHandle) {
    s32 entryNum = contentConvertPathToEntrynumNAND(pHandle, pPath);

    if (!mIsOpen && entryNum != -1) {
        s32 result =
            contentFastOpenNAND(pHandle, entryNum, &mAsyncContext.fileInfo);

        if (result == CNT_RESULT_OK) {
            mIsOpen = true;

#line 109
            EGG_ASSERT(sIsInitialized);

            nw4r::ut::List_Append(&sCntList, this);
            mAsyncContext.pHandle = pHandle;

        } else {
            mIsOpen = false;
            mAsyncContext.pHandle = NULL;
        }
    }

    return mIsOpen;
}

void CntFile::close() {
    if (!mIsOpen) {
        return;
    }

    s32 result = contentCloseNAND(&mAsyncContext.fileInfo);
    mAsyncContext.pHandle = NULL;

    if (result == CNT_RESULT_OK) {
        mIsOpen = false;
        nw4r::ut::List_Remove(&sCntList, this);
    }
}

s32 CntFile::readData(void* pDst, s32 size, s32 offset) {
    OSLockMutex(&mSyncMutex);

    if (mSyncThread != NULL) {
        OSUnlockMutex(&mSyncMutex);
        return -1;
    }

    mSyncThread = OSGetCurrentThread();

    s32 result = contentReadNAND(&mAsyncContext.fileInfo, pDst, size, offset);

    mSyncThread = NULL;

    OSUnlockMutex(&mSyncMutex);
    return result;
}

s32 CntFile::writeData(const void* pSrc, s32 size, s32 offset) {
#pragma unused(pSrc)
#pragma unused(size)
#pragma unused(offset)

    return -1;
}

} // namespace EGG
