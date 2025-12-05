#ifndef RP_GRAPHICS_I_MODEL_CALLBACK_H
#define RP_GRAPHICS_I_MODEL_CALLBACK_H
#include <Pack/types_pack.h>

#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Model callback interface
 */
class IRPGrpModelCallback {
public:
    virtual ~IRPGrpModelCallback() = 0; // at 0x8

    virtual void EditJointLocalMtx(RPGrpModel*, u16, nw4r::math::MTX34*,
                                   nw4r::math::VEC3*) {} // at 0xC

    virtual void EditJointWorldMtx(RPGrpModel*, u16, nw4r::math::MTX34*) //
    {} // at 0x10

    virtual void EditWorldMtx(RPGrpModel*) {} // at 0x14
    virtual void ReferViewMtx(RPGrpModel*) {} // at 0x18
};

//! @}

#endif
