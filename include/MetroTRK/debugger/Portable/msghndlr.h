#ifndef METROTRK_DEBUGGER_PORTABLE_MSGHNDLR_H
#define METROTRK_DEBUGGER_PORTABLE_MSGHNDLR_H
#include <MetroTRK/debugger/Portable/dserror.h>
#include <MetroTRK/debugger/Portable/msgbuf.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

DSError TRKDoConnect(TRKMessageBuffer* buf);
DSError TRKDoDisconnect(TRKMessageBuffer* buf);
DSError TRKDoReset(TRKMessageBuffer* buf);
DSError TRKDoOverride(TRKMessageBuffer* buf);
DSError TRKDoVersions(TRKMessageBuffer* buf);
DSError TRKDoSupportMask(TRKMessageBuffer* buf);
DSError TRKDoReadMemory(TRKMessageBuffer* buf);
DSError TRKDoWriteMemory(TRKMessageBuffer* buf);
DSError TRKDoReadRegisters(TRKMessageBuffer* buf);
DSError TRKDoWriteRegisters(TRKMessageBuffer* buf);
DSError TRKDoContinue(TRKMessageBuffer* buf);
DSError TRKDoStep(TRKMessageBuffer* buf);
DSError TRKDoStop(TRKMessageBuffer* buf);
DSError TRKDoSetOption(TRKMessageBuffer* buf);

#ifdef __cplusplus
}
#endif
#endif