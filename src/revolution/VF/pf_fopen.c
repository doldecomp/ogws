#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

void* VFiPFAPI_convertReturnValue2NULL(s32 err, void* p_stream);

struct PF_FILE* VFipf2_fopen(const s8* path, const s8* mode) {
    s32 open_mode;
    struct PF_FILE* p_file;
    struct PF_STR path_str;
    s32 err;

    open_mode = VFiPFAPI_ParseOpenModeString(mode);

    if (open_mode == 0) {
        VFipf_vol_set.last_error = 10;
        return NULL;
    } else {
        err = VFiPFSTR_InitStr(&path_str, (const s8*)path, 1);
        if (err == 0) {
            err = VFiPFFILE_fopen(&path_str, open_mode, &p_file);
        } else {
            VFipf_vol_set.last_error = err;
        }
    }
    return VFiPFAPI_convertReturnValue2NULL(err, p_file);
}
