#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

void* VFiPFAPI_convertReturnValue2NULL(int err, void* p_stream);

PF_FILE* VFipf2_fopen(const char* path, const char* mode) {
    s32 open_mode;
    PF_FILE* p_ofile;

    // TODO(Alex9303):
    // Union forces 8-byte alignment, skipping 0xC and pushing stack to 0x30
    union {
        PF_STR str;
        s64 _align; 
    } path_str_u;
    
    s32 err;

    open_mode = VFiPFAPI_ParseOpenModeString(mode);

    if (open_mode == 0) {
        VFipf_vol_set.last_error = 10;
        return NULL;
    } else {
        err = VFiPFSTR_InitStr(&path_str_u.str, (const s8*)path, 1);
        if (err == 0) {
            err = VFiPFFILE_fopen(&path_str_u.str, open_mode, &p_ofile);
        } else {
            VFipf_vol_set.last_error = err;
        }
    }
    return VFiPFAPI_convertReturnValue2NULL(err, p_ofile);
}
