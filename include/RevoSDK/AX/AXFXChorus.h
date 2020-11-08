#ifndef REVOSDK_AX_FX_CHORUS
#define REVOSDK_AX_FX_CHORUS
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct AXFXChorus
{
	char UNK_0x0[0xA0];
};

UNKTYPE AXFXChorusCallback(void **, struct AXFXChorus *);
u32 AXFXChorusGetMemSize(struct AXFXChorus *);

UNKWORD AXFXChorusInit(struct AXFXChorus *);
UNKTYPE AXFXChorusShutdown(struct AXFXChorus *);
UNKWORD AXFXChorusSettings(struct AXFXChorus *);

#ifdef __cplusplus
}
#endif
#endif