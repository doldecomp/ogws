#ifndef RVL_SDK_PAD_H
#define RVL_SDK_PAD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern u32 __PADSpec;

typedef struct PADStatus {
    u8 dummy;
} PADStatus;

typedef enum {
    PAD_FLAG_NO_RECALIBRATE = (1 << 6),
} PADFlag;

BOOL __PADDisableRecalibration(BOOL disable);

#ifdef __cplusplus
}
#endif
#endif
