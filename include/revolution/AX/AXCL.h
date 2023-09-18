#ifndef RVL_SDK_AX_CL_H
#define RVL_SDK_AX_CL_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AX_OUTPUT_STEREO,
    AX_OUTPUT_SURROUND,
    AX_OUTPUT_DPL2
} AXOutputMode;

extern u32 __AXClMode;

UNKTYPE AXSetMode(UNKWORD);
UNKTYPE AXSetMasterVolume(u16);
UNKTYPE AXSetAuxAReturnVolume(u16);
UNKTYPE AXSetAuxBReturnVolume(u16);
UNKTYPE AXSetAuxCReturnVolume(u16);

#ifdef __cplusplus
}
#endif
#endif