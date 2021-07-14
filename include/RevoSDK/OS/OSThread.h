#ifndef REVOSDK_OS_THREAD
#define REVOSDK_OS_THREAD
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

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

UNKTYPE OSYieldThread(UNKTYPE);
BOOL OSCreateThread(struct OSThread *, OSThreadFunc, void *, void *, UNKWORD, UNKWORD, UNKWORD);

BOOL OSJoinThread(struct OSThread *, UNKWORD);

UNKTYPE OSResumeThread(struct OSThread *);

UNKTYPE OSSleepThread(struct OSThreadQueue *);
UNKTYPE OSWakeupThread(struct OSThreadQueue *);
UNKTYPE OSInitThreadQueue(struct OSThreadQueue *);
OSThread * OSGetCurrentThread(void);

UNKWORD OSSetSwitchThreadCallback(OSSwitchThreadFunc);
BOOL OSIsThreadTerminated(struct OSThread *);

UNKTYPE OSDetachThread(struct OSThread *);
UNKTYPE OSCancelThread(struct OSThread *);

#ifdef __cplusplus
}
#endif __cplusplus
#endif