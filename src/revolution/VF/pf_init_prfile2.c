#include <revolution/VF.h>

int VFipf2_init_prfile2(s32 config, void* param) {
    s32 err;
    err = VFiPFFATFS_initializeFATFS(config, param);
    if (err == 0) {
        VFiPFSYS_initializeSYS();
    }
    return VFiPFAPI_convertReturnValue(err);
}
