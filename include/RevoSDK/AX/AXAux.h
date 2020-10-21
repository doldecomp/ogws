#ifndef REVOSDK_AX_AUX_H
#define REVOSDK_AX_AUX_H
#include <types.h>
#include <AX.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE AXRegisterAuxACallback(AXAuxCallback, UNKWORD);
UNKTYPE AXRegisterAuxBCallback(AXAuxCallback, UNKWORD);
UNKTYPE AXRegisterAuxCCallback(AXAuxCallback, UNKWORD);

UNKTYPE AXGetAuxACallback(AXAuxCallback *, UNKWORD *);
UNKTYPE AXGetAuxBCallback(AXAuxCallback *, UNKWORD *);
UNKTYPE AXGetAuxCCallback(AXAuxCallback *, UNKWORD *);

#ifdef __cplusplus
}
#endif
#endif