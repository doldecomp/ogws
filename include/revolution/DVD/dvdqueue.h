#ifndef RVL_SDK_DVD_QUEUE_H
#define RVL_SDK_DVD_QUEUE_H
#include <revolution/DVD/dvd.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DVD_QUEUE_PRIO_HIGHEST,
    DVD_QUEUE_PRIO_HIGH,
    DVD_QUEUE_PRIO_MEDIUM,
    DVD_QUEUE_PRIO_LOW,

    DVD_QUEUE_PRIO_MAX,
} DVDQueuePriority;

void __DVDClearWaitingQueue(void);
BOOL __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block);
DVDCommandBlock* __DVDPopWaitingQueue(void);
BOOL __DVDCheckWaitingQueue(void);
DVDCommandBlock* __DVDGetNextWaitingQueue(void);
BOOL __DVDDequeueWaitingQueue(const DVDCommandBlock* block);

#ifdef __cplusplus
}
#endif
#endif
