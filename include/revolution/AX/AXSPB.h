#ifndef RVL_SDK_AX_SPB_H
#define RVL_SDK_AX_SPB_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _AXSTUDIO {
    u8 UNK_0x0[0x78];
} AXSTUDIO;

AXSTUDIO* __AXGetStudio(void);

#ifdef __cplusplus
}
#endif
#endif
