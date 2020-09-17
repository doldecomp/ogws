#ifndef REVOSDK_OS_MUTEX
#define REVOSDK_OS_MUTEX
#ifdef __cplusplus
extern "C" {
#endif

struct OSMutex
{
	char UNK_0x0[0x18];
};

void OSLockMutex(struct OSMutex *);
void OSInitMutex(struct OSMutex *);
void OSUnlockMutex(struct OSMutex *);

#ifdef __cplusplus
}
#endif
#endif