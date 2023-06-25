#ifndef METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#define METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#include <MetroTRK/debugger/portable/dserror.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

DSError TRKReleaseMutex(void* p);
DSError TRKAcquireMutex(void* p);
DSError TRKInitializeMutex(void* p);

#ifdef __cplusplus
}
#endif
#endif