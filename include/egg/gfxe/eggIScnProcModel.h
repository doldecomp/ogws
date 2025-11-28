#ifndef EGG_GFXE_I_SCN_PROC_MODEL_H
#define EGG_GFXE_I_SCN_PROC_MODEL_H
#include <egg/types_egg.h>

#include <nw4r/math.h>

namespace EGG {

class IScnProcModel {
public:
    enum EDrawFlag {
        cDrawFlag_IgnoreMaterial = 1 << 0,
        cDrawFlag_ForceLightOff = 1 << 1,
    };

public:
    IScnProcModel() {}
    virtual ~IScnProcModel() {} // at 0x8

    virtual void scnProcDraw(bool opa, u32 flags) = 0; // at 0xC
    virtual UNKTYPE VF_0x10(UNKTYPE) = 0;              // at 0x10

    virtual void
    getMinMaxScnProcModel(nw4r::math::VEC3* pMin,
                          nw4r::math::VEC3* pMax) const = 0; // at 0x14
};

} // namespace EGG

#endif
