#include <revolution/VF.h>

int VFipf2_detach(s8 drive) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFVOL_detach(drive));
    return err;
}
