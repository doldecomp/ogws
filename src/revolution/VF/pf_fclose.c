#include <revolution/VF.h>

s32 VFipf2_fclose(PF_FILE* p_file) {
    return VFiPFAPI_convertReturnValue(VFiPFFILE_fclose(p_file));
}
