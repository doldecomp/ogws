#include <revolution/VF.h>

s32 VFipf2_devinf(u8 drv_char, PF_DEV_INF* dev_inf) {
    int result = VFiPFVOL_getdev((s8)drv_char, dev_inf);
    return VFiPFAPI_convertReturnValue(result);
}
