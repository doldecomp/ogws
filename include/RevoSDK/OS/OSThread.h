#ifndef REVOSDK_OS_THREAD
#define REVOSDK_OS_THREAD
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

#define OS_THREAD_STACK_MAGIC 0xBABE

typedef int (* OSThreadFunc)(void *);

struct OSThread
{
    char UNK_0x0[0x318];
};

struct OSThreadQueue
{
    OSThread *thread_0x0;
    OSThread *thread_0x4;
};

bool OSCreateThread(OSThread *, OSThreadFunc, void *, void *, u32, s32, u8);
UNKTYPE OSYieldThread(UNKTYPE);
UNKTYPE OSResumeThread(OSThread *);
bool OSJoinThread(OSThread *, int);

UNKTYPE OSWakeupThread(OSThreadQueue *);
UNKTYPE OSInitThreadQueue(OSThreadQueue *);

#ifdef __cplusplus
}
#endif __cplusplus
#endif