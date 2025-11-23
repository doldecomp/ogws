// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace EGG {

nw4r::ut::List Thread::sThreadList;

Thread::Thread(u32 stackSize, int capacity, int priority, Heap* pHeap) {
    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    mContainHeap = pHeap;
    mStackSize = ROUND_DOWN(stackSize, 32);

    mStackMemory = Heap::alloc(mStackSize, 32, mContainHeap);
#line 70
    EGG_ASSERT(mStackMemory);

    mOSThread =
        static_cast<OSThread*>(Heap::alloc(sizeof(OSThread), 32, mContainHeap));
#line 80
    EGG_ASSERT(mOSThread);

    OSCreateThread(mOSThread, Thread::start, this,
                   reinterpret_cast<u8*>(mStackMemory) + mStackSize, mStackSize,
                   priority, OS_THREAD_DETACHED);

    setCommonMesgQueue(capacity, mContainHeap);
}

Thread::Thread(OSThread* pOSThread, int capacity) {
    mContainHeap = NULL;
    mOSThread = pOSThread;

    mStackSize =
        nw4r::ut::GetOffsetFromPtr(pOSThread->stackBegin, pOSThread->stackEnd);

    mStackMemory = pOSThread->stackBegin;

    setCommonMesgQueue(capacity, Heap::getCurrentHeap());
}

Thread::~Thread() {
    nw4r::ut::List_Remove(&sThreadList, this);

    if (mContainHeap != NULL) {
        if (!OSIsThreadTerminated(mOSThread)) {
            OSDetachThread(mOSThread);
            OSCancelThread(mOSThread);
        }

        Heap::free(mStackMemory, mContainHeap);
        Heap::free(mOSThread, mContainHeap);
    }

    Heap::free(mMesgBuffer, NULL);
}

Thread* Thread::findThread(OSThread* pOSThread) {
    NW4R_UT_LIST_FOREACH(Thread, it, sThreadList, {
        if (it->mOSThread == pOSThread) {
            return it;
        }
    })

    return NULL;
}

void Thread::initialize() {
    NW4R_UT_LIST_INIT(sThreadList, Thread);
    OSSetSwitchThreadCallback(Thread::switchThreadCallback);
}

void Thread::switchThreadCallback(OSThread* pCurrOSThread,
                                  OSThread* pNewOSThread) {

    Thread* pCurrThread =
        pCurrOSThread != NULL ? findThread(pCurrOSThread) : NULL;

    // clang-format off
    Thread* pNewThread =
        pNewOSThread != NULL ? findThread(pNewOSThread) : NULL;
    // clang-format on

    if (pCurrThread != NULL) {
        pCurrThread->onExit();
    }
    if (pNewThread != NULL) {
        pNewThread->onEnter();
    }
}

void Thread::setCommonMesgQueue(int capacity, Heap* pHeap) {
    mMesgNum = capacity;

    mMesgBuffer = static_cast<OSMessage*>(
        Heap::alloc(capacity * sizeof(OSMessage), 4, pHeap));
#line 262
    EGG_ASSERT(mMesgBuffer);

    OSInitMessageQueue(&mMesgQueue, mMesgBuffer, mMesgNum);
    nw4r::ut::List_Append(&sThreadList, this);
}

void* Thread::start(void* pArg) {
    return static_cast<Thread*>(pArg)->run();
}

} // namespace EGG
