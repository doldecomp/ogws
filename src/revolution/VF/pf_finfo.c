#include <revolution/VF.h>

int VFipf2_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFFILE_finfo(p_file, p_info));
    return err;
}
