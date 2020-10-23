#ifndef REVOSDK_AX_FX_HOOKS_H
#define REVOSDK_AX_FX_HOOKS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*AXFXAllocHook)(u32);
typedef void (*AXFXFreeHook)(void *);

UNKTYPE AXFXGetHooks(AXFXAllocHook *, AXFXFreeHook *);
UNKTYPE AXFXSetHooks(AXFXAllocHook, AXFXFreeHook);

#ifdef __cplusplus
}
#endif
#endif