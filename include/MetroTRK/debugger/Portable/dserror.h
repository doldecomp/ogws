#ifndef METROTRK_DEBUGGER_PORTABLE_DSERROR_H
#define METROTRK_DEBUGGER_PORTABLE_DSERROR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kNoError = 0x0000,
    kMsgQueueFull = 0x0100,
    kInvalidMemory = 0x0700,
} DSError;

#ifdef __cplusplus
}
#endif
#endif