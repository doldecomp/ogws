#ifndef EGG_GFX_I_SCN_PROC_MODEL_H
#define EGG_GFX_I_SCN_PROC_MODEL_H
#include "types_egg.h"
#include "types_nw4r.h"

namespace EGG
{
    class IScnProcModel
    {
    public:
        IScnProcModel() {}
        virtual ~IScnProcModel() {} // at 0x8
        virtual void draw(bool, u32) = 0; // at 0xC
        virtual UNKTYPE VF_0x10(UNKTYPE) = 0; // at 0x10
        virtual void getMinMaxScnProcModel(
            nw4r::math::VEC3 *, nw4r::math::VEC3 *) const = 0; // at 0x14
    };
}

#endif