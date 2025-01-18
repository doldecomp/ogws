#pragma ipa file
#include "eggCntFile.h"
#include "eggAssert.h"
#include <revolution/ARC/arc.h>

namespace
{
    UNKTYPE INSTANTIATE_WEAK(EGG::CntFile *f)
    {
        f->getFileSize();
    }
}

namespace EGG
{
    using namespace nw4r;

    CntFile::CntFile() : mIsOpen(false)
    {
        initiate();
    }

    CntFile::~CntFile()
    {
        close();
    }

    void CntFile::initiate()
    {
        PTR_0x50 = this;
        mOpenFile = NULL;

        OSInitMutex(&mMutex_0x8);
        OSInitMutex(&mMutex_0x20);
        OSInitMessageQueue(&mMesgQueue_0x78, &mMesgBuffer_0x98, 1);
        OSInitMessageQueue(&mMesgQueue_0x54, &mMesgBuffer_0x74, 1);

        mThread = NULL;
        WORD_0x38 = 0;
    }

    bool CntFile::open(const char *name, CNTHandle *handle)
    {
        s32 entry = contentConvertPathToEntrynumNAND(handle, name);
        if (!mIsOpen && entry != -1)
        {
            if (contentFastOpenNAND(handle, entry, &mFileInfo) == 0)
            {
                mIsOpen = true;
                #line 109
                EGG_ASSERT(sIsInitialized);

                ut::List_Append(&sCntList, this);
                mOpenFile = handle;
            }
            else
            {
                mIsOpen = false;
                mOpenFile = NULL;
            }
        }

        return mIsOpen;
    }

    void CntFile::close()
    {
        if (mIsOpen)
        {
            UNKWORD result = contentCloseNAND(&mFileInfo);
            mOpenFile = NULL;

            if (result == 0)
            {
                mIsOpen = false;
                ut::List_Remove(&sCntList, this);
            }
        }
    }

    s32 CntFile::readData(void *buf, s32 len, s32 pos)
    {
        OSLockMutex(&mMutex_0x8);
        if (mThread)
        {
            OSUnlockMutex(&mMutex_0x8);
            return -1;
        }
        else
        {
            mThread = OSGetCurrentThread();
            s32 ret = contentReadNAND(&mFileInfo, buf, len, pos);
            mThread = NULL;

            OSUnlockMutex(&mMutex_0x8);
            return ret;
        }
    }

    s32 CntFile::writeData(const void *, s32, s32)
    {
        return -1;
    }

    ut::List CntFile::sCntList;
    bool CntFile::sIsInitialized;
}