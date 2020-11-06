#ifndef REVOSDK_AX_FX_REVERB_HI_H
#define REVOSDK_AX_FX_REVERB_HI_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct AXFXReverbHi
{
	char UNK_0x0[0x40];
};

UNKTYPE AXFXReverbHiCallback(void **, AXFXReverbHi *);
u32 AXFXReverbHiGetMemSize(AXFXReverbHi *);

UNKWORD AXFXReverbHiInit(AXFXReverbHi *);
UNKTYPE AXFXReverbHiShutdown(AXFXReverbHi *);
UNKWORD AXFXReverbHiSettings(AXFXReverbHi *);


#ifdef __cplusplus
}
#endif
#endif