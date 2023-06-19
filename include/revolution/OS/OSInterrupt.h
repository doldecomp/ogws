#ifndef REVOSDK_OS_INTERRUPT
#define REVOSDK_OS_INTERRUPT
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKWORD OSDisableInterrupts(void);
UNKTYPE OSRestoreInterrupts(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif