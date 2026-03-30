#include <revolution/VF.h>

int VFipf2_fseek(struct PF_FILE* pFile, s32 lOffset, int nOrigin) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFFILE_fseek(pFile, lOffset, nOrigin));
    return err;
}
