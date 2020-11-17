#ifndef REVOSDK_AX_OUT_H
#define REVOSDK_AX_OUT_H
#include <types.h>
#include "AX.h"
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE AXSetMode(UNKWORD);
AXCallback AXRegisterCallback(AXCallback);

UNKWORD AXRmtGetSamplesLeft(void);
UNKTYPE AXRmtGetSamples(int, UNKTYPE *, UNKWORD);
UNKTYPE AXRmtAdvancePtr(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif