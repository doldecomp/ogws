#include <revolution/VF.h>

int VFipf2_remove(const char *path) {
    long err;
    PFSTR path_str;

    err = VFiPFSTR_InitStr(&path_str, (const s8*)path, 1);
    if (err == 0) {
        err = VFiPFFILE_remove(&path_str);
    } else {
        // VFipf_vol_set.UNK_0x0[0x1c] = err;
        *(int*)(VFipf_vol_set.UNK_0x0 + 0x1c) = err;
    }

    return VFiPFAPI_convertReturnValue(err);
}
