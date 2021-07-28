#ifndef REVOSDK_GX_LIGHT_H
#define REVOSDK_GX_LIGHT_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXLightObj
{
    char UNK_0x0[64];
} GXLightObj;

typedef enum _GXLightID
{

} GXLightID;

typedef enum _GXSpotFn
{
    GX_SPOT_FN_0
} GXSpotFn;

typedef enum _GXDistAttnFn
{
    GX_DIST_ATTN_FN_0
} GXDistAttnFn;

UNKTYPE GXInitLightColor(GXLightObj *, GXColor *);
UNKTYPE GXInitLightPos(GXLightObj *, float, float, float);
UNKTYPE GXInitLightDir(GXLightObj *, float, float, float);
UNKTYPE GXInitSpecularDir(GXLightObj *, float, float, float);
UNKTYPE GXInitLightSpot(GXLightObj *, float, GXSpotFn);
UNKTYPE GXInitLightAttnA(GXLightObj *, float, float, float);
UNKTYPE GXInitLightDistAttn(GXLightObj *, float, float, GXDistAttnFn);
UNKTYPE GXInitLightAttnK(GXLightObj *, float, float, float);
UNKTYPE GXInitLightAttn(GXLightObj *, float, float, float, float, float, float);
UNKTYPE GXGetLightPos(const GXLightObj *, float *, float *, float *);
UNKTYPE GXGetLightDir(const GXLightObj *, float *, float *, float *);

UNKTYPE GXSetChanMatColor(GXChannelID, GXColor);
UNKTYPE GXSetNumChans(UNKWORD nChans);
UNKTYPE GXSetChanCtrl(GXChannelID, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif