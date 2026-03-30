#include <revolution/VF.h>

s32 VFiPFFATFS_initializeFATFS(u32 config, void* param) {
    VFiPFVOL_InitModule(config, param);
}
