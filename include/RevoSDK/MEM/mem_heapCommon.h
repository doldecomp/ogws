#ifndef REVOSDK_MEM_HEAP_COMMON_H
#define REVOSDK_MEM_HEAP_COMMON_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct MEMiHeapHead
{

};

struct MEMHeap
{
	char UNK_0x0[0x1C];
	u8 * PTR_0x1C;
};

static u32 MEMGetHeapTotalSize(MEMHeap * pHeap)
{
	return pHeap->PTR_0x1C - (u8 *)pHeap;
}

#ifdef __cplusplus
}
#endif
#endif