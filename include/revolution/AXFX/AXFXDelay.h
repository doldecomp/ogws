#ifndef RVL_SDK_AXFX_DELAY_H
#define RVL_SDK_AXFX_DELAY_H
#include <revolution/AXFX/AXFXDelayExp.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXFX_DELAY_PARAM {
    u32 INT_0x0;
    u32 INT_0x4;
    u32 INT_0x8;

    u32 INT_0xC;
    u32 INT_0x10;
    u32 INT_0x14;

    u32 INT_0x18;
    u32 INT_0x1C;
    u32 INT_0x20;
} AXFX_DELAY_PARAM;

typedef struct AXFX_DELAY {
    AXFX_DELAY_EXP exp;     // at 0x0
    AXFX_DELAY_PARAM param; // at 0x58
} AXFX_DELAY;

u32 AXFXDelayGetMemSize(const AXFX_DELAY* fx);
BOOL AXFXDelayInit(AXFX_DELAY* fx);
BOOL AXFXDelaySettings(AXFX_DELAY* fx);
void AXFXDelayShutdown(AXFX_DELAY* fx);
void AXFXDelayCallback(void* chans, void* context);

#ifdef __cplusplus
}
#endif
#endif
