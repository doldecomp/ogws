#ifndef REVOSDK_OS_THREAD
#define REVOSDK_OS_THREAD
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

#define OS_THREAD_STACK_MAGIC 0xBABE

typedef UNKWORD (* OSThreadFunc)(void *);

struct OSThread
{
    char UNK_0x0[0x318];
};

struct OSThreadQueue
{
    struct OSThread *thread_0x0;
    struct OSThread *thread_0x4;
};

BOOL OSCreateThread(struct OSThread *, OSThreadFunc, void *, void *, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE OSYieldThread(UNKTYPE);
UNKTYPE OSResumeThread(struct OSThread *);
BOOL OSJoinThread(struct OSThread *, UNKWORD);

UNKTYPE OSWakeupThread(struct OSThreadQueue *);
UNKTYPE OSInitThreadQueue(struct OSThreadQueue *);

#ifdef __cplusplus
}
#endif __cplusplus
#endif