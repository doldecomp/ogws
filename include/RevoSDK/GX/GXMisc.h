#ifndef REVOSDK_GX_MISC_H
#define REVOSDK_GX_MISC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (* GXDrawDoneCallback)(void);

UNKTYPE GXFlush(void);

UNKTYPE GXDrawDone(void);

UNKTYPE GXSetDrawDoneCallback(GXDrawDoneCallback);

#ifdef __cplusplus
}
#endif
#endif