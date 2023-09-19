#ifndef RVL_SDK_AX_CL_H
#define RVL_SDK_AX_CL_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define AX_MAX_VOLUME 32768

typedef enum {
    AX_OUTPUT_STEREO,
    AX_OUTPUT_SURROUND,
    AX_OUTPUT_DPL2
} AXOutputMode;

extern u32 __AXClMode;

u32 __AXGetCommandListCycles(void);
void* __AXGetCommandListAddress(void);
void __AXWriteToCommandList(u16 cmd);
void __AXNextFrame(u32* surround, u32* lr, u32* rmt);
void __AXClInit(void);
void AXSetMode(u32 mode);
u32 AXGetMode(void);
u16 AXGetAuxAReturnVolume(void);
u16 AXGetAuxBReturnVolume(void);
u16 AXGetAuxCReturnVolume(void);
void AXSetMasterVolume(u16 volume);
void AXSetAuxAReturnVolume(u16 volume);
void AXSetAuxBReturnVolume(u16 volume);
void AXSetAuxCReturnVolume(u16 volume);

#ifdef __cplusplus
}
#endif
#endif