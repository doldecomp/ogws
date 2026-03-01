#include <revolution/VF.h>

int VFipf2_detach(s8 drive) {
    return VFiPFAPI_convertReturnValue(VFiPFVOL_detach(drive));
}
