#include <revolution/AX.h>

const char* __AXVersion =
    "<< RVL_SDK - AX \trelease build: Dec 18 2006 15:43:48 (0x4199_60831) >>";

static BOOL __init = FALSE;

void AXInit(void) {
    AXInitEx(0);
}

void AXInitEx(u32 mode) {
    if (!__init) {
        OSRegisterVersion(__AXVersion);

        __AXAllocInit();
        __AXVPBInit();
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(mode);

        __init = TRUE;
    }
}
