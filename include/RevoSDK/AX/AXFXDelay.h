#ifndef REVOSDK_AX_FX_DELAY
#define REVOSDK_AX_FX_DELAY
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct AXFXDelay
{
	char UNK_0x0[0xA0];
};

UNKTYPE AXFXDelayCallback(void **, AXFXDelay *);
u32 AXFXDelayGetMemSize(AXFXDelay *);

UNKWORD AXFXDelayInit(AXFXDelay *);
UNKTYPE AXFXDelayShutdown(AXFXDelay *);
UNKWORD AXFXDelaySettings(AXFXDelay *);


#ifdef __cplusplus
}
#endif
#endif