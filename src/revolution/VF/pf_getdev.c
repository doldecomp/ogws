#include <revolution/VF.h>

int VFipf2_devinf(s8 drv_char, struct PF_DEV_INF* dev_inf) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFVOL_getdev((s8)drv_char, dev_inf));
    return err;
}
