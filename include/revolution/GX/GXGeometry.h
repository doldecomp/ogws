#ifndef REVOSDK_GX_GEOMETRY_H
#define REVOSDK_GX_GEOMETRY_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXCullMode
{
    
} GXCullMode;

UNKTYPE GXBegin(UNKWORD, UNKWORD formatIndex, UNKWORD);
static void GXEnd(void) {}

UNKTYPE GXSetCullMode(UNKWORD);

UNKTYPE GXSetCoPlanar(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif