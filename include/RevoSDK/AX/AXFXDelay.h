#ifndef REVOSDK_AX_FX_DELAY_H
#define REVOSDK_AX_FX_DELAY_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct AXFXDelay
{
	char UNK_0x0[0x40];
};

UNKTYPE AXFXDelayCallback(void **, struct AXFXDelay *);
u32 AXFXDelayGetMemSize(struct AXFXDelay *);

UNKWORD AXFXDelayInit(struct AXFXDelay *);
UNKTYPE AXFXDelayShutdown(struct AXFXDelay *);
UNKWORD AXFXDelaySettings(struct AXFXDelay *);


#ifdef __cplusplus
}
#endif
#endif