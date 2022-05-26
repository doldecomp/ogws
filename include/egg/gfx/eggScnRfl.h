#ifndef EGG_GFX_SCN_RFL_H
#define EGG_GFX_SCN_RFL_H
#include "types_egg.h"
#include "g3d_scnobj.h"

namespace EGG
{
    class g3dScnRfl : public nw4r::g3d::ScnObj
    {
    public:
        virtual bool IsDerivedFrom(TypeObj other) const // at 0x8
        {
            return (other == GetTypeObjStatic());
        }

        static const nw4r::g3d::G3dObj::TypeObj GetTypeObjStatic()
        {
            return TypeObj(TYPE_NAME);
        }

    private:
        NW4R_G3D_TYPE_OBJ_DECL(g3dScnRfl);
    };
}

#endif