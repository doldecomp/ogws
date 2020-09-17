#ifndef REVOSDK_OS_INTERRUPT
#define REVOSDK_OS_INTERRUPT
#ifdef __cplusplus
extern "C" {
#endif
typedef int UNKWORD;

UNKWORD OSDisableInterrupts(void);
void OSRestoreInterrupts(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif