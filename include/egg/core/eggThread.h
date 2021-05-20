#ifndef EGG_CORE_THREAD_H
#define EGG_CORE_THREAD_H
#include "types_egg.h"
#include "ut_list.h"
#include <RevoSDK/OS/OSThread.h>
#include <RevoSDK/OS/OSMessage.h>

namespace EGG
{
    struct Thread
    {
        Thread(u32, int, int, Heap *);
        Thread(OSThread *, int);
        static Thread * findThread(OSThread *); // inlined
        void initialize();
        static UNKTYPE switchThreadCallback(OSThread *, OSThread *);
        void setCommonMesgQueue(int, Heap *); // inlined
        static UNKWORD start(void *);
        virtual ~Thread(); // at 0x8
        virtual UNKWORD run(); // at 0xC
        virtual void onEnter(); // at 0x10
        virtual void onExit(); // at 0x14

        Heap *mHeap; // at 0x4
        OSThread *mOSThread; // at 0x8
        OSMessageQueue mMesgQueue; // at 0xC
        OSMessage *mMesgBuffer; // at 0x2C
        UNKWORD mMesgCount; // at 0x30
        void * mStackMemory; // at 0x34
        u32 mStackSize; // at 0x38
        nw4r::ut::Node mNode; // at 0x3C

        static nw4r::ut::List sThreadList;
    };
}

#endif