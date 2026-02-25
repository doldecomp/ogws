#include <revolution/VF.h>

s32 VFipf2_unmount(s8 drv_char, u32 mode) {
    int result = VFiPFVOL_unmount(drv_char, mode); 
    return VFiPFAPI_convertReturnValue4unmount(result);
}
