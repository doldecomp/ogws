#ifndef REVOSDK_MEM_FRAME_HEAP_H
#define REVOSDK_MEM_FRAME_HEAP_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct MEMFrmHeap
{
    u32 mMagic; // "FRMH"
    // . . .
};

UNKTYPE * MEMCreateFrmHeapEx(void *, u32, UNKWORD);
UNKTYPE MEMDestroyFrmHeap(UNKTYPE *);
void * MEMAllocFromFrmHeapEx(UNKTYPE *, u32, UNKWORD);
UNKTYPE MEMFreeToFrmHeap(UNKTYPE *, UNKWORD);
u32 MEMGetAllocatableSizeForFrmHeapEx(UNKTYPE *, UNKWORD);

UNKWORD MEMRecordStateForFrmHeap(UNKTYPE *, u32);
UNKTYPE MEMFreeByStateToFrmHeap(UNKTYPE *, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif