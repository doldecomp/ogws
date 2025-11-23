#ifndef METROTRK_DEBUGGER_PORTABLE_DISPATCH_H
#define METROTRK_DEBUGGER_PORTABLE_DISPATCH_H
#include <types.h>

#include <MetroTRK/debugger/portable/dserror.h>
#include <MetroTRK/debugger/portable/msgbuf.h>
#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeDispatcher(void);
DSError TRKDispatchMessage(TRKMessageBuffer* buf);

#ifdef __cplusplus
}
#endif
#endif
