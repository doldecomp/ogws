#ifndef RVL_SDK_AXFX_CHORUS_H
#define RVL_SDK_AXFX_CHORUS_H
#include <revolution/AXFX/AXFXChorusExp.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXFX_CHORUS_PARAM {
    u32 delayTime; // at 0x0
    u32 amplitude; // at 0x4
    u32 period;    // at 0x8
} AXFX_CHORUS_PARAM;

typedef struct AXFX_CHORUS {
    AXFX_CHORUS_EXP exp;     // at 0x0
    AXFX_CHORUS_PARAM param; // at 0xA0
} AXFX_CHORUS;

u32 AXFXChorusGetMemSize(const AXFX_CHORUS* fx);
BOOL AXFXChorusInit(AXFX_CHORUS* fx);
BOOL AXFXChorusShutdown(AXFX_CHORUS* fx);
BOOL AXFXChorusSettings(AXFX_CHORUS* fx);
void AXFXChorusCallback(void* chans, void* context);

#ifdef __cplusplus
}
#endif
#endif