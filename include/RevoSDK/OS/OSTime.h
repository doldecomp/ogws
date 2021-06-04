#ifndef REVOSDK_OS_TIME_H
#define REVOSDK_OS_TIME_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 OSGetTick(void);
s64 OSGetTime(void);

#ifdef __cplusplus
}
#endif
#endif