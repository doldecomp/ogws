#pragma ipa file
#include "eggThread.h"
#include "eggHeap.h"
#include "eggAssert.h"
#include "ut_list.h"
#include "ut_algorithm.h"

namespace EGG
{
    using namespace nw4r;

    Thread::Thread(u32 stackSize, int mesgCount, int r6, Heap *pHeap)
    {
        if (!pHeap) pHeap = Heap::getCurrentHeap();
        mHeap = pHeap;

        mStackSize = ut::RoundDown<u32>(stackSize, 32);
        mStackMemory = Heap::alloc(mStackSize, 32, pHeap);
        #line 70
        EGG_ASSERT(mStackMemory);

        mOSThread = static_cast<OSThread *>(Heap::alloc(sizeof(OSThread), 32, mHeap));
        #line 80
        EGG_ASSERT(mOSThread);

        OSCreateThread(mOSThread, Thread::start, this, (u8 *)mStackMemory + mStackSize, mStackSize, r6, 1);

        setCommonMesgQueue(mesgCount, mHeap);
    }

    Thread::Thread(OSThread *pThread, int mesgCount)
    {
        mHeap = NULL;
        mOSThread = pThread;
        mStackSize = ut::GetOffsetFromPtr(pThread->stackBegin, pThread->stackEnd);
        mStackMemory = pThread->stackBegin;
        
        setCommonMesgQueue(mesgCount, Heap::getCurrentHeap());
    }

    Thread::~Thread()
    {
        ut::List_Remove(&sThreadList, this);
        if (mHeap)
        {
            if (!OSIsThreadTerminated(mOSThread))
            {
                OSDetachThread(mOSThread);
                OSCancelThread(mOSThread);
            }

            Heap::free(mStackMemory, mHeap);
            Heap::free(mOSThread, mHeap);
        }

        Heap::free(mMesgBuffer, NULL);
    }

    Thread * Thread::findThread(OSThread *pThread)
    {
        Thread *node = NULL;
        while (node = (Thread *)ut::List_GetNext(&sThreadList, node))
        {
            if (node->mOSThread == pThread) return node;
        }

        return NULL;
    }

    void Thread::initialize()
    {
        ut::List_Init(&sThreadList, offsetof(Thread, mNode));
        OSSetSwitchThreadCallback(Thread::switchThreadCallback);
    }

    void Thread::switchThreadCallback(OSThread *r3, OSThread *r4)
    {
        Thread * oldThread;
        if (r3) oldThread = findThread(r3);
        else oldThread = NULL;

        Thread * newThread;
        if (r4) newThread = findThread(r4);
        else newThread = NULL;

        if (oldThread) oldThread->onExit();
        if (newThread) newThread->onEnter();
    }

    void Thread::setCommonMesgQueue(int mesgCount, Heap *pHeap)
    {
        mMesgCount = mesgCount;
        mMesgBuffer = static_cast<OSMessage *>(Heap::alloc(mesgCount * sizeof(OSMessage), 4, pHeap));
        #line 262
        EGG_ASSERT(mMesgBuffer);

        OSInitMessageQueue(&mMesgQueue, mMesgBuffer, mMesgCount);
        ut::List_Append(&sThreadList, this);
    }

    void Thread::onExit()
    {

    }

    void Thread::onEnter()
    {

    }

    void* Thread::start(void *pThread)
    {
        return static_cast<Thread *>(pThread)->run();
    }

    void* Thread::run()
    {
        return NULL;
    }

    ut::List Thread::sThreadList;
}