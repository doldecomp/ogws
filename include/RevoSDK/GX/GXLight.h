#ifndef REVOSDK_GX_LIGHT_H
#define REVOSDK_GX_LIGHT_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXLightID
{

} GXLightID;

UNKTYPE GXSetChanMatColor(GXChannelID, GXColor);
UNKTYPE GXSetNumChans(UNKWORD nChans);
UNKTYPE GXSetChanCtrl(GXChannelID, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif