#pragma ipa file
#include "eggDvdFile.h"

namespace EGG
{
    using namespace nw4r;

    void DvdFile::initialize()
    {
        if (!sIsInitialized)
        {
            ut::List_Init(&sDvdList, offsetof(DvdFile, mNode));
            sIsInitialized = true;
        }
    }

    DvdFile::DvdFile() : mIsOpen(false)
    {
        initiate();
    }

    DvdFile::~DvdFile()
    {
        close();
    }

    void DvdFile::initiate()
    {
        PTR_0x78 = this;

        OSInitMutex(&mMutex_0x8);
        OSInitMutex(&mMutex_0x20);
        OSInitMessageQueue(&mMesgQueue_0xA0, &mMesg_0xC0, 1);
        OSInitMessageQueue(&mMesgQueue_0x7C, &mMesg_0x9C, 1);

        mThread = NULL;
        WORD_0x38 = 0;
    }

    bool DvdFile::open(int id)
    {
        if (!mIsOpen && id != -1)
        {
            mIsOpen = (DVDFastOpen(id, &mFileInfo) != 0);
            if (mIsOpen)
            {
                ut::List_Append(&sDvdList, this);
                (void)DVDGetCommandBlockStatus(&mCmdBlock);
            }
        }

        return mIsOpen;
    }

    bool DvdFile::open(const char *name)
    {
        s32 entry = DVDConvertPathToEntrynum(name);
        return open(entry);
    }

    bool DvdFile::open(const char *name, void *buf)
    {
        return open(name);
    }

    void DvdFile::close()
    {
        if (mIsOpen && DVDClose(&mFileInfo))
        {
            mIsOpen = false;
            ut::List_Remove(&sDvdList, this);
        }
    }

    s32 DvdFile::readData(void *buf, s32 len, s32 pos)
    {
        OSLockMutex(&mMutex_0x8);
        if (mThread)
        {
            OSUnlockMutex(&mMutex_0x8);
            return -1;
        }
        
        mThread = OSGetCurrentThread();
        s32 result = -1;
        u32 success = DVDReadAsyncPrio(&mFileInfo, buf, len, pos, DvdFile::doneProcess, DVD_PRIO_MEDIUM);
        
        if (success != 0)
        {
            OSLockMutex(&mMutex_0x8);

            OSMessage mesg;
            OSReceiveMessage(&mMesgQueue_0xA0, &mesg, 1);

            mThread = NULL;
            OSUnlockMutex(&mMutex_0x8);
            result = (s32)mesg;
        }

        mThread = NULL;
        OSUnlockMutex(&mMutex_0x8);

        return result;
    }

    s32 DvdFile::writeData(const void *, s32, s32)
    {
        return -1;
    }

    void DvdFile::doneProcess(s32 mesg, DVDFileInfo *pInfo)
    {
        FileInfoPair *pPair = (FileInfoPair *)pInfo;
        OSSendMessage(&pPair->pDvdFile->mMesgQueue_0xA0, (OSMessage)mesg, 0);
    }

    ut::List DvdFile::sDvdList;
    bool DvdFile::sIsInitialized;
}