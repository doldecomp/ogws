#include <revolution/VF.h>

int VFipf2_unmount(s8 drive, u32 mode) {
    s32 err;
    err = VFiPFAPI_convertReturnValue4unmount(VFiPFVOL_unmount(drive, mode));
    return err;
}
