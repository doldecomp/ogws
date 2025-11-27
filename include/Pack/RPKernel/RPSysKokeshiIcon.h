#ifndef RP_KERNEL_KOKESHI_ICON_H
#define RP_KERNEL_KOKESHI_ICON_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysAvatar.h>

#include <egg/core.h>
#include <egg/gfx.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii icon texture
 */
class RPSysKokeshiIcon : public RPSysAvatar {
public:
    EGG::ResTIMG* GetResTIMG();
};

//! @}

#endif
