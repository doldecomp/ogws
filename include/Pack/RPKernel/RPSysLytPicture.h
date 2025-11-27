#ifndef RP_KERNEL_LYT_PICTURE_H
#define RP_KERNEL_LYT_PICTURE_H
#include <Pack/types_pack.h>

#include <nw4r/lyt.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief NW4R layout picture extension
 */
class RPSysLytPicture : public nw4r::lyt::Picture {
public:
    /**
     * @brief Applies the specified player material color
     * @details The color is applied to TEV color register 1
     *
     * @param idx Player index
     */
    void applyPlayerColor(u32 idx);

    /**
     * @brief Applies the CPU player material color
     * @details The color is applied to TEV color register 1
     */
    void applyCpuColor();
};

//! @}

#endif
