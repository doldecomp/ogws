#ifndef REVOSDK_OS_CACHE
#define REVOSDK_OS_CACHE
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

UNKTYPE LCLoadBlocks(void *, void *, u32);
UNKTYPE LCStoreBlocks(void *, void *, u32);
UNKTYPE LCStoreData(void *, void *, u32);

UNKTYPE LCEnable(void);
UNKTYPE LCDisable(void);

u32 LCQueueLength(UNKTYPE);

UNKTYPE DCFlushRange(UNKTYPE *, u32);
UNKTYPE DCStoreRange(void *, u32);

#ifdef __cplusplus
}
#endif __cplusplus
#endif