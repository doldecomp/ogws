#ifndef METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#define METROTRK_DEBUGGER_PORTABLE_MUTEX_TRK_H
#include <types.h>

#include <MetroTRK/debugger/portable/dserror.h>
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
