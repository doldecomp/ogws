#ifndef REVOSDK_OS_H
#define REVOSDK_OS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

volatile u32 BUS_SPEED : 0x800000f8;

UNKTYPE OSRegisterVersion(const char *);

static void OSInitFastCast(void)
{
	asm
	{
		li r3, 4
		oris r3, r3, 4
		mtspr 0x392, r3
		li r3, 5
		oris r3, r3, 5
		mtspr 0x393, r3
		li r3, 6
		oris r3, r3, 6
		mtspr 0x394, r3
		li r3, 7
		oris r3, r3, 7
		mtspr 0x395, r3
	}
}

static float __OSu16tof32(register const u16 * arg)
{
	register f32 ret;
	
	asm
	{
		psq_l ret, 0(arg), 1, 3
	}
	
	return ret;
}

static void OSu16tof32(const u16 * in, f32 * out)
{
	*out = __OSu16tof32(in);
}

static int __OSf32tou16(register f32 arg)
{
	u16 ret[2];
	register u16 * ptr = ret;
	
	asm
	{
		psq_st arg, 0(ptr), 1, 3
	}
	
	return *ptr;
}

static void OSf32tou16(const f32 * in, u16 * out)
{
	*out = __OSf32tou16(*in);
}

static float __OSs16tof32(register const s16 * arg)
{
	register f32 ret;
	
	asm
	{
		psq_l ret, 0(arg), 1, 3
	}
	
	return ret;
}

static void OSs16tof32(const s16 * in, f32 * out)
{
	*out = __OSs16tof32(in);
}

static int __OSf32tos16(register f32 arg)
{
	s16 ret[2];
	register s16 * ptr = ret;
	
	asm
	{
		psq_st arg, 0(ptr), 1, 5
	}
	
	return *ptr;
}

static void OSf32tos16(const f32 * in, s16 * out)
{
	*out = __OSf32tos16(*in);
}

#ifdef __cplusplus
}
#endif
#endif