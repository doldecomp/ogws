#ifndef RVL_SDK_PAD_H
#define RVL_SDK_PAD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern u32 __PADSpec;

typedef enum {
    PAD_BUTTON_LEFT = (1 << 0),
    PAD_BUTTON_RIGHT = (1 << 1),
    PAD_BUTTON_DOWN = (1 << 2),
    PAD_BUTTON_UP = (1 << 3),

    PAD_BUTTON_A = (1 << 8),
    PAD_BUTTON_B = (1 << 9),
    PAD_BUTTON_X = (1 << 10),
    PAD_BUTTON_Y = (1 << 11),

    PAD_BUTTON_L = (1 << 6),
    PAD_BUTTON_R = (1 << 5),
    PAD_BUTTON_Z = (1 << 4),

    PAD_BUTTON_START = (1 << 12),
} PADButton;

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
