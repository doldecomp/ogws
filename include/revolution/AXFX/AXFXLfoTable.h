#ifndef RVL_SDK_AXFX_LFO_TABLE_H
#define RVL_SDK_AXFX_LFO_TABLE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern s32 __SinTableFixedPoint[];

s32* __AXFXGetLfoSinTable(void);

#ifdef __cplusplus
}
#endif
#endif
