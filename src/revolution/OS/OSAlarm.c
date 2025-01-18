#include <revolution/BASE.h>
#include <revolution/DVD.h>
#include <revolution/OS.h>

static BOOL OnReset(BOOL final, u32 event);
static void DecrementerExceptionHandler(u8 type, OSContext* ctx);

static OSAlarmQueue AlarmQueue;
static OSShutdownFunctionInfo ShutdownFunctionInfo = {OnReset, 0xFFFFFFFF, 0,
                                                      0};

static void SetTimer(const OSAlarm* alarm) {
    s64 timeLeft = alarm->end - __OSGetSystemTime();

    if (timeLeft < 0) {
        PPCMtdec(0);
    } else if (timeLeft < 0x80000000) {
        PPCMtdec(timeLeft);
    } else {
        PPCMtdec(0x7FFFFFFF);
    }
}

void __OSInitAlarm(void) {
    if (__OSGetExceptionHandler(OS_ERR_DECREMENTER) !=
        DecrementerExceptionHandler) {
        AlarmQueue.head = AlarmQueue.tail = NULL;
        __OSSetExceptionHandler(OS_ERR_DECREMENTER,
                                DecrementerExceptionHandler);
        OSRegisterShutdownFunction(&ShutdownFunctionInfo);
    }
}

void OSCreateAlarm(OSAlarm* alarm) {
    alarm->handler = NULL;
    alarm->tag = 0;
}

static void InsertAlarm(OSAlarm* alarm, s64 end, OSAlarmHandler handler) {
    OSAlarm* iter;
    OSAlarm* prev;

    // Calculate periodic alarm end time (caller makes 'end' 0)
    if (alarm->period > 0) {
        s64 time = __OSGetSystemTime();
        end = alarm->start;

        if (alarm->start < time) {
            s64 periodLeft = ((time - alarm->start) / alarm->period);
            end += alarm->period * (periodLeft + 1);
        }
    }

    alarm->handler = handler;
    alarm->end = end;

    // Find position to insert alarm (sorted ascending by end time)
    for (iter = AlarmQueue.head; iter != NULL; iter = iter->next) {
        if (iter->end <= end) {
            continue;
        }

        alarm->prev = iter->prev;
        iter->prev = alarm;
        alarm->next = iter;

        prev = alarm->prev;
        if (prev != NULL) {
            prev->next = alarm;
        } else {
            AlarmQueue.head = alarm;
            SetTimer(alarm);
        }

        return;
    }

    alarm->next = NULL;
    prev = AlarmQueue.tail;
    AlarmQueue.tail = alarm;
    alarm->prev = prev;

    if (prev != NULL) {
        prev->next = alarm;
    } else {
        AlarmQueue.tail = alarm;
        AlarmQueue.head = alarm;
        SetTimer(alarm);
    }
}

void OSSetAlarm(OSAlarm* alarm, s64 tick, OSAlarmHandler handler) {
    BOOL enabled = OSDisableInterrupts();

    alarm->period = 0;
    InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);

    OSRestoreInterrupts(enabled);
}

void OSSetPeriodicAlarm(OSAlarm* alarm, s64 tick, s64 period,
                        OSAlarmHandler handler) {
    BOOL enabled = OSDisableInterrupts();

    alarm->period = period;
    alarm->start = __OSTimeToSystemTime(tick);
    InsertAlarm(alarm, 0, handler);

    OSRestoreInterrupts(enabled);
}

void OSCancelAlarm(OSAlarm* alarm) {
    OSAlarm* next;

    BOOL enabled = OSDisableInterrupts();

    if (alarm->handler == NULL) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == NULL) {
        AlarmQueue.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }

    if (alarm->prev != NULL) {
        alarm->prev->next = next;
    } else {
        AlarmQueue.head = next;
        if (next != NULL) {
            SetTimer(next);
        }
    }

    alarm->handler = NULL;

    OSRestoreInterrupts(enabled);
}

static void DecrementerExceptionCallback(u8 type, OSContext* ctx) {
#pragma unused(type)

    OSAlarmHandler handler;
    OSContext tempCtx;
    OSAlarm* alarm;
    OSAlarm* next;

    s64 time = __OSGetSystemTime();
    alarm = AlarmQueue.head;

    if (alarm == NULL) {
        OSLoadContext(ctx);
    }

    if (time < alarm->end) {
        SetTimer(alarm);
        OSLoadContext(ctx);
    }

    next = alarm->next;
    AlarmQueue.head = next;
    if (next == NULL) {
        AlarmQueue.tail = NULL;
    } else {
        next->prev = NULL;
    }

    handler = alarm->handler;
    alarm->handler = NULL;

    if (alarm->period > 0) {
        InsertAlarm(alarm, 0, handler);
    }

    if (AlarmQueue.head != NULL) {
        SetTimer(AlarmQueue.head);
    }

    OSDisableScheduler();
    OSClearContext(&tempCtx);
    OSSetCurrentContext(&tempCtx);
    handler(alarm, ctx);
    OSClearContext(&tempCtx);
    OSSetCurrentContext(ctx);
    OSEnableScheduler();

    __OSReschedule();
    OSLoadContext(ctx);
}

static asm void DecrementerExceptionHandler(register u8 type,
                                            register OSContext* ctx) {
    // clang-format off
    nofralloc

    stw r0, ctx->gprs[0]
    stw r1, ctx->gprs[1]
    stw r2, ctx->gprs[2]
    stmw r6, ctx->gprs[6]

    mfspr r0, GQR1
    stw r0, ctx->gqrs[1]
    mfspr r0, GQR2
    stw r0, ctx->gqrs[2]
    mfspr r0, GQR3
    stw r0, ctx->gqrs[3]
    mfspr r0, GQR4
    stw r0, ctx->gqrs[4]
    mfspr r0, GQR5
    stw r0, ctx->gqrs[5]
    mfspr r0, GQR6
    stw r0, ctx->gqrs[6]
    mfspr r0, GQR7
    stw r0, ctx->gqrs[7]

    stwu r1, -8(r1)
    b DecrementerExceptionCallback
    // clang-format on
}

void OSSetAlarmTag(OSAlarm* alarm, u32 tag) {
    alarm->tag = tag;
}

static BOOL OnReset(BOOL final, u32 event) {
    OSAlarm* iter;
    OSAlarm* next;

    if (final) {
        iter = AlarmQueue.head;
        next = (iter != NULL) ? iter->next : NULL;

        while (iter != NULL) {
            if (!__DVDTestAlarm(iter)) {
                OSCancelAlarm(iter);
            }

            iter = next;
            next = (next != NULL) ? next->next : NULL;
        }
    }

    return TRUE;
}

void OSSetAlarmUserData(OSAlarm* alarm, void* userData) {
    alarm->userData = userData;
}

void* OSGetAlarmUserData(const OSAlarm* alarm) {
    return alarm->userData;
}
