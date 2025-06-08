#ifndef EGG_CORE_THREAD_H
#define EGG_CORE_THREAD_H
#include <egg/types_egg.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace EGG {

// Forward declarations
class Heap;

class Thread {
public:
    static void initialize();
    static Thread* findThread(OSThread* pOSThread);

    Thread(u32 stackSize, int capacity, int priority, Heap* pHeap);
    Thread(OSThread* pOSThread, int capacity);
    virtual ~Thread(); // at 0x8

    virtual void* run() {
        return NULL;
    } // at 0xC

    virtual void onEnter() {} // at 0x10
    virtual void onExit() {}  // at 0x14

    void resume() {
        OSResumeThread(mOSThread);
    }

    bool sendMessage(OSMessage msg) {
        return OSSendMessage(&mMesgQueue, msg, 0);
    }
    bool jamMessage(OSMessage msg) {
        return OSJamMessage(&mMesgQueue, msg, 0);
    }

    OSMessage waitMessage(BOOL* pSuccess) {
        OSMessage msg;
        *pSuccess = OSReceiveMessage(&mMesgQueue, &msg, 0);
        return msg;
    }
    OSMessage waitMessageBlock() {
        OSMessage msg;
        OSReceiveMessage(&mMesgQueue, &msg, OS_MSG_BLOCKING);
        return msg;
    }

    OSThread* getOSThread() const {
        return mOSThread;
    }

    void* getStack() const {
        return mStackMemory;
    }
    u32 getStackSize() const {
        return mStackSize;
    }

    static nw4r::ut::List& getList() {
        return sThreadList;
    }

private:
    void setCommonMesgQueue(int capacity, Heap* pHeap);

    static void switchThreadCallback(OSThread* pCurrOSThread,
                                     OSThread* pNewOSThread);
    static void* start(void* pArg);

private:
    Heap* mContainHeap;        // at 0x4
    OSThread* mOSThread;       // at 0x8
    OSMessageQueue mMesgQueue; // at 0xC
    OSMessage* mMesgBuffer;    // at 0x2C
    int mMesgNum;              // at 0x30
    void* mStackMemory;        // at 0x34
    u32 mStackSize;            // at 0x38

public:
    NW4R_UT_LIST_LINK_DECL(); // at 0x3C

private:
    static nw4r::ut::List sThreadList;
};

} // namespace EGG

#endif
