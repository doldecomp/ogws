#ifndef REVOSDK_AX_FX_REVERB_HI_H
#define REVOSDK_AX_FX_REVERB_HI_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct AXFXReverbHi
{
	char UNK_0x0[0x148];
};

UNKTYPE AXFXReverbHiCallback(void **, struct AXFXReverbHi *);
u32 AXFXReverbHiGetMemSize(struct AXFXReverbHi *);

UNKWORD AXFXReverbHiInit(struct AXFXReverbHi *);
UNKTYPE AXFXReverbHiShutdown(struct AXFXReverbHi *);
UNKWORD AXFXReverbHiSettings(struct AXFXReverbHi *);

#ifdef __cplusplus
}
#endif
#endif