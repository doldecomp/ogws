#include "g3d_obj.h"

namespace nw4r
{
    namespace g3d
    {
        G3dObj::~G3dObj()
        {
            Dealloc(mAllocator, this);
        }

        void G3dObj::Destroy()
        {
            G3dObj *pParent = GetParent();
            if (pParent) pParent->G3dProc(G3DPROC_CHILD_DETACHED, 0, this);

            delete this;
        }

        bool G3dObj::IsDerivedFrom(const TypeObj& rhs) const
        {
            // Interestingly, the comparison has to be done this order,
            // otherwise the subtraction occurs in the wrong order
            return rhs == GetTypeObjStatic();
        }

        const char * G3dObj::GetTypeName() const
        {
            return GetTypeObj().GetTypeName();
        }

        const G3dObj::TypeObj G3dObj::GetTypeObj() const
        {
            return TypeObj(TYPE_NAME);
        }

        NW4R_G3D_TYPE_OBJ_DEF(G3dObj);
    }
}