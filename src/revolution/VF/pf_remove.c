#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

int VFipf2_remove(const s8* path) {
    s32 err;
    struct PF_STR path_str;

    err = VFiPFSTR_InitStr(&path_str, (const s8*)path, 1);
    if (err == 0) {
        err = VFiPFFILE_remove(&path_str);
    } else {
        VFipf_vol_set.last_error = err;
    }

    return VFiPFAPI_convertReturnValue(err);
}
