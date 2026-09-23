#include <revolution/AX.h>
#include <revolution/OS.h>

#if defined(VERSION_RSPE01_00)
const char* __AXVersion =
    "<< RVL_SDK - AX \trelease build: Oct  1 2006 03:26:07 (0x4200_60422) >>";
#elif defined(VERSION_RSPE01_01)
const char* __AXVersion =
    "<< RVL_SDK - AX \trelease build: Dec 18 2006 15:43:48 (0x4199_60831) >>";
#endif

static BOOL __init = FALSE;

void AXInit(void) {
    AXInitEx(0);
}

void AXInitEx(u32 mode) {
#if defined(VERSION_RSPE01_00)

    OSRegisterVersion(__AXVersion);

    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit(mode);

#elif defined(VERSION_RSPE01_01)
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
#endif
}
