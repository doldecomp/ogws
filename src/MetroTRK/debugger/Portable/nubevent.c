#include <MetroTRK.h>

#define QUEUE_CAPACITY 2

typedef struct TRKEventQueue {
    char UNK_0x0[0x4];
    int size;                       // at 0x4
    int front;                      // at 0x8
    TRKEvent queue[QUEUE_CAPACITY]; // at 0xC
    unsigned int uid;               // at 0x24
} TRKEventQueue;

TRKEventQueue gTRKEventQueue;

void TRKDestructEvent(TRKEvent* event) { TRKReleaseBuffer(event->buffer); }

void TRKConstructEvent(TRKEvent* event, TRKEventType type) {
    event->type = type;
    event->id = 0;
    event->buffer = -1;
}

DSError TRKPostEvent(TRKEvent* event) {
    s32 id;
    DSError err = kNoError;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.size == QUEUE_CAPACITY) {
        err = kMsgQueueFull;
    } else {
        id = (gTRKEventQueue.front + gTRKEventQueue.size) % QUEUE_CAPACITY;
        TRK_memcpy(&gTRKEventQueue.queue[id], event, sizeof(TRKEvent));
        gTRKEventQueue.queue[id].id = gTRKEventQueue.uid;

        if (++gTRKEventQueue.uid < 256) {
            gTRKEventQueue.uid = 256;
        }

        gTRKEventQueue.size++;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return err;
}

BOOL TRKGetNextEvent(TRKEvent* event) {
    BOOL success = FALSE;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.size > 0) {
        TRK_memcpy(event, &gTRKEventQueue.queue[gTRKEventQueue.front],
                   sizeof(TRKEvent));
        gTRKEventQueue.size--;
        gTRKEventQueue.front++;

        if (gTRKEventQueue.front == QUEUE_CAPACITY) {
            gTRKEventQueue.front = 0;
        }

        success = TRUE;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return success;
}

DSError TRKInitializeEventQueue(TRKEvent* event) {
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);

    gTRKEventQueue.size = 0;
    gTRKEventQueue.front = 0;
    gTRKEventQueue.uid = 256;

    TRKReleaseMutex(&gTRKEventQueue);
    return kNoError;
}
