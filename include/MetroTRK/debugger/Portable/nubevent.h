#ifndef METROTRK_DEBUGGER_PORTABLE_NUBEVENT_H
#define METROTRK_DEBUGGER_PORTABLE_NUBEVENT_H
#include <MetroTRK/debugger/portable/dserror.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EVENT_TYPE_NONE,
    EVENT_TYPE_WAIT,
    EVENT_TYPE_MESSAGE,
    EVENT_TYPE_EXCEPTION,
    EVENT_TYPE_BREAKPOINT,
    EVENT_TYPE_SUPPORT_REQ
} TRKEventType;

typedef struct TRKEvent {
    TRKEventType type; // at 0x0
    unsigned int id;   // at 0x4
    int buffer;        // at 0x8
} TRKEvent;

void TRKDestructEvent(TRKEvent* event);
void TRKConstructEvent(TRKEvent* event, TRKEventType type);
DSError TRKPostEvent(TRKEvent* event);
BOOL TRKGetNextEvent(TRKEvent* event);
DSError TRKInitializeEventQueue(TRKEvent* event);

#ifdef __cplusplus
}
#endif
#endif