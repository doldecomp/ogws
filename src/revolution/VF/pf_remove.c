#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

int VFipf2_remove(const char *path) {
    long err;
    PFSTR path_str;

    err = VFiPFSTR_InitStr(&path_str, (const s8*)path, 1);
    if (err == 0) {
        err = VFiPFFILE_remove(&path_str);
    } else {
        VFipf_vol_set.last_error = err; 
    }

    return VFiPFAPI_convertReturnValue(err);
}
