#ifndef REVOSDK_OS_THREAD
#define REVOSDK_OS_THREAD
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

#define OS_THREAD_STACK_MAGIC 0xBABE

struct OSThread
{
    char UNK_0x0[0x304];
    void *mStackTop;
    void *mStackBottom;
    char UNK_0x30C[0xC];
};

struct OSThreadQueue
{
    struct OSThread *thread_0x0;
    struct OSThread *thread_0x4;
};

typedef UNKWORD (* OSThreadFunc)(void *);
typedef void (* OSSwitchThreadFunc)(OSThread *, OSThread *);

BOOL OSCreateThread(struct OSThread *, OSThreadFunc, void *, void *, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE OSYieldThread(UNKTYPE);
UNKTYPE OSResumeThread(struct OSThread *);
BOOL OSJoinThread(struct OSThread *, UNKWORD);

UNKTYPE OSWakeupThread(struct OSThreadQueue *);
UNKTYPE OSInitThreadQueue(struct OSThreadQueue *);

UNKWORD OSSetSwitchThreadCallback(OSSwitchThreadFunc);
BOOL OSIsThreadTerminated(struct OSThread *);

UNKTYPE OSDetachThread(struct OSThread *);
UNKTYPE OSCancelThread(struct OSThread *);

#ifdef __cplusplus
}
#endif __cplusplus
#endif