#ifndef RVL_SDK_SI_SIBIOS_H
#define RVL_SDK_SI_SIBIOS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SI_CHAN_0,
    SI_CHAN_1,
    SI_CHAN_2,
    SI_CHAN_3,

    SI_MAX_CHAN,
    SI_CHAN_NONE = -1,
} SIChannel;

typedef enum {
    SI_TYPE_0,
    SI_TYPE_1,
    SI_TYPE_2,
    SI_TYPE_3,

    SI_MAX_TYPE
} SIType;

typedef void (*SICallback)(s32 chan, u32 status);

void SIInit(void);
u32 SISetXY(u32 lines, u32 times);
BOOL SITransfer(s32 chan, void* outAddr, u32 outSize, void* inAddr, u32 inSize,
                SICallback callback, s64 wait);
u32 SIGetType(s32 chan);

#ifdef __cplusplus
}
#endif
#endif
