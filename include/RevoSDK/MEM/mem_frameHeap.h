#ifndef REVOSDK_MEM_FRAME_HEAP_H
#define REVOSDK_MEM_FRAME_HEAP_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE * MEMCreateFrmHeapEx(void *, u32, UNKWORD);
UNKTYPE MEMDestroyFrmHeap(UNKTYPE *);
void * MEMAllocFromFrmHeapEx(UNKTYPE *, u32, UNKWORD);
UNKTYPE MEMFreeToFrmHeap(UNKTYPE *, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif