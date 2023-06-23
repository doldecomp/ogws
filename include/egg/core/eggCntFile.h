#ifndef EGG_CORE_CNTFILE_H
#define EGG_CORE_CNTFILE_H
#include "types_egg.h"
#include "eggAssert.h"
#include "ut_list.h"
#include "eggFile.h"
#include <revolution/CNT/cnt.h>
#include <revolution/ARC/arc.h>
#include <revolution/OS/OSMutex.h>
#include <revolution/OS/OSMessage.h>
#include <revolution/OS/OSThread.h>

namespace EGG
{
    class CntFile : File
    {
    public:
        CntFile();
        virtual ~CntFile(); // at 0x8
        virtual bool open(const char *name)  // at 0xC
        {
            #line 57
            EGG_ASSERT(false);
            return false;
        }
        virtual void close(); // at 0x10
        virtual s32 readData(void *, s32, s32); // at 0x14
        virtual s32 writeData(const void *, s32, s32); // at 0x18
        virtual UNKWORD getFileSize() const { return contentGetLengthNAND(&mFileInfo); }; // at 0x1C

        void initiate();
        bool open(const char *, CNTHandle *);

    private:
        bool mIsOpen; // at 0x4
        OSMutex mMutex_0x8;
        OSMutex mMutex_0x20; // at 0x20
        UNKWORD WORD_0x38;
        CNTFileInfo mFileInfo; // at 0x3C
        CNTHandle *mOpenFile; // at 0x4C
        CntFile *PTR_0x50;
        OSMessageQueue mMesgQueue_0x54;
        OSMessage mMesgBuffer_0x74;
        OSMessageQueue mMesgQueue_0x78;
        OSMessage mMesgBuffer_0x98;
        OSThread *mThread; // at 0x9C
        nw4r::ut::Node mNode; // at 0xA0

        // Unofficial symbol
        static nw4r::ut::List sCntList;
        static bool sIsInitialized;
    };
}

#endif