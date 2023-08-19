#ifndef REVOSDK_AX_CL_H
#define REVOSDK_AX_CL_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE AXSetMode(UNKWORD);
UNKTYPE AXSetMasterVolume(u16);
UNKTYPE AXSetAuxAReturnVolume(u16);
UNKTYPE AXSetAuxBReturnVolume(u16);
UNKTYPE AXSetAuxCReturnVolume(u16);

#ifdef __cplusplus
}
#endif
#endif