#ifndef REVOSDK_GX_PIXEL_H
#define REVOSDK_GX_PIXEL_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE GXSetZMode(UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetAlphaUpdate(UNKWORD);
UNKTYPE GXSetColorUpdate(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif