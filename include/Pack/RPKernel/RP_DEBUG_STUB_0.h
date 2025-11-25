#ifndef RP_KERNEL_DEBUG_STUB_0_H
#define RP_KERNEL_DEBUG_STUB_0_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

class RP_DEBUG_STUB_0 {
    RP_SINGLETON_DECL(RP_DEBUG_STUB_0);

public:
    void Calculate();
    void DebugDraw();
};

//! @}

#endif
