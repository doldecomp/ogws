#include <revolution/VF.h>

s32 VFipf2_init_prfile2(long config, void* param) {
    s32 err = VFiPFFATFS_initializeFATFS(config, param); 
    if (err == 0) {
        VFiPFSYS_initializeSYS();
    }
    return VFiPFAPI_convertReturnValue(err);
}
