#ifndef RP_KERNEL_LYT_BOUNDING_H
#define RP_KERNEL_LYT_BOUNDING_H
#include <Pack/types_pack.h>

#include <egg/math.h>

#include <nw4r/lyt.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief NW4R layout bounding extension
 */
class RPSysLytBounding : public nw4r::lyt::Bounding {
public:
    /**
     * @brief Tests whether a point falls within this bounding pane
     *
     * @param rInfo Pane draw info
     * @param rPoint Point to test
     */
    bool isInsideBounding(const nw4r::lyt::DrawInfo& rInfo,
                          const EGG::Vector2f& rPoint);
};

//! @}

#endif
