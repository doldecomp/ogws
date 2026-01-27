#ifndef RP_KERNEL_CONTROLLER_H
#define RP_KERNEL_CONTROLLER_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_kernel
//! @{

class RPSysCoreControllerMgr {
public:
    static u32 isDpdCtrlEnable(s32 chan) {
        return sDpdCtrlEnableFlag & (1 << chan);
    }

private:
    static u32 sDpdCtrlEnableFlag;
};

class RPSysCoreController : public EGG::CoreController {
public:
    bool isPrevDpdCtrlEnable();
};

//! @}

#endif
