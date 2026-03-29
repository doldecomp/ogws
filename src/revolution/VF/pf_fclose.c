#include <revolution/VF.h>

int VFipf2_fclose(struct PF_FILE* p_file) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFFILE_fclose(p_file));
    return err;
}
