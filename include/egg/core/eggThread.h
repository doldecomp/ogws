#ifndef EGG_CORE_THREAD_H
#define EGG_CORE_THREAD_H
#include "types_egg.h"
#include "ut_list.h"
#include <revolution/OS/OSThread.h>
#include <revolution/OS/OSMessage.h>

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
        static void* start(void *);
        virtual ~Thread(); // at 0x8
        virtual void* run(); // at 0xC
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
		
		inline bool sendMessage(OSMessage message)
		{
			return OSSendMessage(&mMesgQueue, message, 0);
		}
		
		inline void resume()
		{
			OSResumeThread(mOSThread);
		}
		
		inline OSMessage waitMessageBlock()
		{
			OSMessage message;
			
			OSReceiveMessage(&mMesgQueue, &message, 1);
			
			return message;
		}
		
		inline OSMessage waitMessage(BOOL * pSuccess)
		{
			OSMessage message;
			
			*pSuccess = OSReceiveMessage(&mMesgQueue, &message, 0);
			
			return message;
		}
    };
}

#endif