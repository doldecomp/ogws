#ifndef RVL_SDK_AXFX_REVERB_HI_H
#define RVL_SDK_AXFX_REVERB_HI_H
#include <revolution/AXFX/AXFXReverbHiExp.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXFX_REVERBHI_PARAM {
    f32 coloration;   // at 0x0
    f32 outGain;      // at 0x4
    f32 fusedTime;    // at 0x8
    f32 damping;      // at 0xC
    f32 preDelayTime; // at 0x10
    f32 crosstalk;    // at 0x14
} AXFX_REVERBHI_PARAM;

typedef struct AXFX_REVERBHI {
    AXFX_REVERBHI_EXP exp;     // at 0x0
    AXFX_REVERBHI_PARAM param; // at 0x148
} AXFX_REVERBHI;

u32 AXFXReverbHiGetMemSize(AXFX_REVERBHI* fx);
BOOL AXFXReverbHiInit(AXFX_REVERBHI* fx);
BOOL AXFXReverbHiShutdown(AXFX_REVERBHI* fx);
BOOL AXFXReverbHiSettings(AXFX_REVERBHI* fx);
void AXFXReverbHiCallback(void* chans, void* context);

#ifdef __cplusplus
}
#endif
#endif