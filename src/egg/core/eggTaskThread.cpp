// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/OS.h>

namespace EGG {

OSMessage* TaskThread::sEndMesgBuffer = NULL;
int TaskThread::sEndMesgBufSize = 0;

OSMessageQueue TaskThread::sEndMesgQueue;

TaskThread* TaskThread::create(int capacity, int priority, u32 stackSize,
                               Heap* pHeap) {

    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    TaskThread* pThread = new (pHeap) TaskThread(capacity, priority, stackSize);
    if (pThread == NULL) {
        return NULL;
    }

    pThread->mCurrentJob = NULL;
    pThread->mJobList = new (pHeap) TJob[capacity];
    pThread->mJobNum = capacity;

    if (pThread->mJobList == NULL) {
        delete pThread;
        return NULL;
    }

    for (int i = 0; i < capacity; i++) {
        pThread->mJobList[i].pTask = NULL;
        pThread->mJobList[i].clearFunctions();
    }

    return pThread;
}

bool TaskThread::request(TaskFunc pTask, void* pTaskArg, OSMessage endMesg) {
    TJob* pJob = findBlank();
    if (pJob == NULL) {
        return false;
    }

    pJob->pTask = pTask;
    pJob->pTaskArg = pTaskArg;
    pJob->endMesg = endMesg;

    bool success = sendMessage(pJob);
    if (!success) {
        pJob->pTask = NULL;
    }

    return success;
}

OSMessageQueue* TaskThread::createTaskEndMessageQueue(int size, Heap* pHeap) {
#line 378
    EGG_ASSERT(size > 0);

    sEndMesgBufSize = size;

    sEndMesgBuffer = static_cast<OSMessage*>(
        Heap::alloc(size * sizeof(OSMessage), 4, pHeap));
#line 389
    EGG_ASSERT(sEndMesgBuffer);

    OSInitMessageQueue(&sEndMesgQueue, sEndMesgBuffer, sEndMesgBufSize);
    return &sEndMesgQueue;
}

bool TaskThread::isTaskExist() const {
    for (int i = 0; i < mJobNum; i++) {
        if (mJobList[i].pTask != NULL) {
            return true;
        }
    }

    return false;
}

TaskThread::~TaskThread() {}

void TaskThread::onEnter() {
    if (mCurrentJob != NULL && mCurrentJob->pOnEnter != NULL) {
        mCurrentJob->pOnEnter(mCurrentJob->pTaskArg);
    }
}

void TaskThread::onExit() {
    if (mCurrentJob != NULL && mCurrentJob->pOnExit != NULL) {
        mCurrentJob->pOnExit(mCurrentJob->pTaskArg);
    }
}

void* TaskThread::run() {
    OSInitFastCast();

    while (true) {
        TJob* pJob = static_cast<TJob*>(waitMessageBlock());
        mCurrentJob = pJob;

        if (pJob->pTask != NULL) {
            pJob->pTask(pJob->pTaskArg);

            if (mEndMesgQueue != NULL) {
                OSSendMessage(mEndMesgQueue, pJob->endMesg, 0);
            }
        }

        pJob->pTask = NULL;

        if (mCurrentJob != NULL && mCurrentJob->pOnDone != NULL) {
            mCurrentJob->pOnDone(mCurrentJob->pTaskArg);
        }

        mCurrentJob = NULL;

        pJob->clearFunctions();
    }
}

TaskThread::TaskThread(int capacity, int priority, u32 stackSize)
    : Thread(stackSize, capacity, priority, NULL), mEndMesgQueue(NULL) {

    resume();
}

OSMessage TaskThread::waitQueueMessage(OSMessageQueue* pQueue, BOOL* pSuccess) {
    OSMessage msg = NULL;
    BOOL success = FALSE;

    if (pQueue != NULL) {
        success = OSReceiveMessage(pQueue, &msg, 0);
    }

    if (pSuccess != NULL) {
        *pSuccess = success;
    }

    return msg;
}

TaskThread::TJob* TaskThread::findBlank() {
    for (int i = 0; i < mJobNum; i++) {
        if (mJobList[i].pTask != NULL) {
            continue;
        }

        mJobList[i].clearFunctions();
        return &mJobList[i];
    }

    return NULL;
}

} // namespace EGG
