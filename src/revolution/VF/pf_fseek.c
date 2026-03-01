#include <revolution/VF.h>

int VFipf2_fseek(PF_FILE* p_file, int lOffset, int nOrigin) {
    return VFiPFAPI_convertReturnValue(VFiPFFILE_fseek(p_file, lOffset, nOrigin));
}
