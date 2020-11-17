#ifndef REVOSDK_OS_ALARM_H
#define REVOSDK_OS_ALARM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct OSAlarm
{
	char UNK_0x0[0x30];
} __attribute__ ((aligned(4)));

typedef void (*OSAlarmHandler)(struct OSAlarm *, struct OSContext *);

UNKTYPE OSCreateAlarm(struct OSAlarm *);

UNKTYPE OSSetAlarmUserData(struct OSAlarm *, void *);
void * OSGetAlarmUserData(struct OSAlarm *);

UNKTYPE OSCancelAlarm(struct OSAlarm *);

UNKTYPE OSSetAlarm(struct OSAlarm *, s64, OSAlarmHandler);
UNKTYPE OSSetPeriodicAlarm(struct OSAlarm *, s64, s64, OSAlarmHandler);

#ifdef __cplusplus
}
#endif
#endif