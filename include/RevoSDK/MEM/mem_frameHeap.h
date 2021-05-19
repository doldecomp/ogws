#ifndef REVOSDK_MEM_FRAME_HEAP_H
#define REVOSDK_MEM_FRAME_HEAP_H
#include <types.h>
#include "mem_heapCommon.h"
#ifdef __cplusplus
extern "C" {
#endif

MEMiHeapHead * MEMCreateFrmHeapEx(void *, u32, UNKWORD);
UNKTYPE MEMDestroyFrmHeap(struct MEMiHeapHead *);
void * MEMAllocFromFrmHeapEx(struct MEMiHeapHead *, u32, UNKWORD);
UNKTYPE MEMFreeToFrmHeap(struct MEMiHeapHead *, UNKWORD);
UNKWORD MEMGetAllocatableSizeForFrmHeapEx(struct MEMiHeapHead *, UNKWORD);

UNKWORD MEMRecordStateForFrmHeap(UNKTYPE *, u32);
UNKTYPE MEMFreeByStateToFrmHeap(UNKTYPE *, UNKWORD);
UNKWORD MEMAdjustFrmHeap(struct MEMiHeapHead *);
UNKWORD MEMResizeForMBlockFrmHeap(struct MEMiHeapHead *, void *, u32); 

#ifdef __cplusplus
}
#endif
#endif