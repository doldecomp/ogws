#ifndef METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#define METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#include <MetroTRK/debugger/portable/dserror.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Unused?
typedef struct TRKMutex {
    char dummy[4];
} TRKMutex;

DSError TRKReleaseMutex(TRKMutex* mutex);
DSError TRKAcquireMutex(TRKMutex* mutex);
DSError TRKInitializeMutex(TRKMutex* mutex);

#ifdef __cplusplus
}
#endif
#endif