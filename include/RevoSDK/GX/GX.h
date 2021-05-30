#ifndef REVOSDK_GX_H
#define REVOSDK_GX_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern volatile union {
	char c;
	short s;
	int i;
	void * p;
	float f;
} WGPIPE : 0xcc008000;

typedef struct _GXColor
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} GXColor;

typedef enum _GXColorSrc
{

} GXColorSrc;

typedef struct _GXColorS10
{
	u16 r;
	u16 g;
	u16 b;
	u16 a;
} GXColorS10;

typedef enum _GXChannelID
{
	GX_CHANNEL_ID_0,
	GX_CHANNEL_ID_1,
	GX_CHANNEL_ID_2,
	GX_CHANNEL_ID_3,
	GX_CHANNEL_ID_4,
	GX_CHANNEL_ID_5,
	GX_CHANNEL_ID_6,
	GX_CHANNEL_ID_7,
	GX_CHANNEL_ID_8,
	GX_CHANNEL_ID_INVALID = 0xFF
} GXChannelID;

typedef enum _GXDiffuseFn
{
    
} GXDiffuseFn;

typedef enum _GXAttnFn
{

} GXAttnFn;

#ifdef __cplusplus
}
#endif
#endif