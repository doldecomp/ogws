#include <revolution/VF.h>

int VFipf2_errnum(void) {
    return VFiPFAPI_convertError(VFiPFVOL_errnum());
}
