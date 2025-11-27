#ifndef RP_KERNEL_LYT_WINDOW_H
#define RP_KERNEL_LYT_WINDOW_H
#include <Pack/types_pack.h>

#include <nw4r/lyt.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief NW4R layout window extension
 */
class RPSysLytWindow : public nw4r::lyt::Window {
public:
    /**
     * @brief Applies the specified player material color to the window frame
     * @details The color is applied to TEV color register 1
     *
     * @param idx Player index
     * @param content Whether to also apply the color to the content
     */
    void applyPlayerColor(u32 idx, bool content);

    /**
     * @brief Applies the CPU player material color to the window frame
     * @details The color is applied to TEV color register 1
     *
     * @param content Whether to also apply the color to the content
     */
    void applyCpuColor(bool content);
};

//! @}

#endif
