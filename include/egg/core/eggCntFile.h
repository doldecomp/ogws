#ifndef EGG_CORE_CNTFILE_H
#define EGG_CORE_CNTFILE_H
#include "types_egg.h"
#include "eggAssert.h"
#include "ut_list.h"
#include "eggFile.h"
#include <RevoSDK/CNT/cnt.h>
#include <RevoSDK/ARC/arc.h>
#include <RevoSDK/OS/OSMutex.h>
#include <RevoSDK/OS/OSMessage.h>
#include <RevoSDK/OS/OSThread.h>

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
        virtual UNKWORD getFileSize() const; // at 0x1C

        void initiate();
        // Unofficial symbol
        bool open(const char *, struct ARCHandle *);

    private:
        bool mIsOpen; // at 0x4
        OSMutex mMutex_0x8;
        OSMutex mMutex_0x20; // at 0x20
        UNKWORD WORD_0x38;
        CNTFileInfo mFileInfo; // at 0x3C
        struct ARCHandle *mOpenFile; // at 0x4C
        CntFile *PTR_0x50;
        OSMessageQueue mMesgQueue_0x54;
        OSMessage mMesgBuffer_0x74;
        OSMessageQueue mMesgQueue_0x78;
        OSMessage mMesgBuffer_0x98;
        OSThread *mThread; // at 0x9C

        // Unofficial symbol
        static nw4r::ut::List sCntList;
        static bool sIsInitialized;
    };
}

#endif