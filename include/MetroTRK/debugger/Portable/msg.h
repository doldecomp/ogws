#ifndef METROTRK_DEBUGGER_PORTABLE_MSG_H
#define METROTRK_DEBUGGER_PORTABLE_MSG_H
#include <MetroTRK/debugger/Portable/dserror.h>
#include <MetroTRK/debugger/Portable/msgbuf.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

DSError TRKMessageSend(TRKMessageBuffer* buf);

#ifdef __cplusplus
}
#endif
#endif