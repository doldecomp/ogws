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

        namespace
        {
            // Force order of weak functions
            void UNUSED_FUNC_ORDER_G3DOBJ(G3dObj *obj)
            {
                (void)obj->GetTypeObj();
                (void)obj->GetTypeName();
                (void)obj->IsDerivedFrom(obj->GetTypeObjStatic());
            }
        }

        NW4R_G3D_TYPE_OBJ_DEF(G3dObj);
    }
}