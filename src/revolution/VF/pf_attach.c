#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

int VFipf2_attach(PF_DRV_TBL** drv_tbl) {
    s32 err;
    if (drv_tbl == 0 || !*drv_tbl) {
        err = 10;
        VFipf_vol_set.last_error = err;
    } else {
        while (*drv_tbl) {
            err = VFiPFVOL_attach(*drv_tbl);
            if (err != 0) {
                return VFiPFAPI_convertReturnValue(err);
            }
            drv_tbl++;
        }
    }
    return VFiPFAPI_convertReturnValue(err);
}
