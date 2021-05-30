#ifndef REVOSDK_GX_DISPLAY_LIST_H
#define REVOSDK_GX_DISPLAY_LIST_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

static void GXFastCallDisplayList(void * ptr, u32 cmdSize)
{
	WGPIPE.c = 0x40;
	WGPIPE.p = ptr;
	WGPIPE.i = cmdSize;
}

UNKTYPE GXCallDisplayList(void *list, u32 nbytes);

#ifdef __cplusplus
}
#endif
#endif