#ifndef EGG_CORE_TASK_THREAD_H
#define EGG_CORE_TASK_THREAD_H
#include <egg/types_egg.h>

#include <egg/core/eggThread.h>

namespace EGG {

// Forward declarations
class Heap;

class TaskThread : public Thread {
public:
    typedef void (*TaskFunc)(void* pTaskArg);

    struct TJob {
        TaskFunc pTask;    // at 0x0
        void* pTaskArg;    // at 0x4
        OSMessage endMesg; // at 0x8

        TaskFunc pOnEnter; // at 0xC
        TaskFunc pOnExit;  // at 0x10
        TaskFunc pOnDone;  // at 0x14

        TJob() : pOnEnter(NULL), pOnExit(NULL), pOnDone(NULL) {}

        void clearFunctions() {
            pTask = NULL;
            pOnEnter = NULL;
            pOnExit = NULL;
            pOnDone = NULL;
        }
    };

public:
    static TaskThread* create(int capacity, int priority, u32 stackSize,
                              Heap* pHeap);
    static OSMessageQueue* createTaskEndMessageQueue(int size, Heap* pHeap);

    TaskThread(int capacity, int priority, u32 stackSize);
    virtual ~TaskThread(); // at 0x8

    virtual void* run(); // at 0xC

    virtual void onEnter(); // at 0x10
    virtual void onExit();  // at 0x14

    bool request(TaskFunc pTask, void* pTaskArg, OSMessage endMesg);
    bool isTaskExist() const;

    static OSMessage waitQueueMessage(OSMessageQueue* pQueue, BOOL* pSuccess);

    bool isTaskWorking() const {
        return mCurrentJob != NULL;
    }

    void setEndMessageQueue(OSMessageQueue* pQueue) {
        mEndMesgQueue = pQueue;
    }
    OSMessage waitTaskEndMessage(BOOL* pSuccess) {
        OSMessage msg;
        *pSuccess = OSReceiveMessage(mEndMesgQueue, &msg, 0);
        return msg;
    }

private:
    TJob* findBlank();

private:
    TJob* mCurrentJob;             // at 0x44
    TJob* mJobList;                // at 0x48
    int mJobNum;                   // at 0x4C
    OSMessageQueue* mEndMesgQueue; // at 0x50

    static OSMessage* sEndMesgBuffer;
    static int sEndMesgBufSize;

    static OSMessageQueue sEndMesgQueue;
};

} // namespace EGG

#endif
