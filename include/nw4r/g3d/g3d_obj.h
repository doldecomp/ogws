#ifndef NW4R_G3D_G3DOBJ_H
#define NW4R_G3D_G3DOBJ_H
#include "types_nw4r.h"
#include <RevoSDK/MEM/mem_allocator.h>

namespace nw4r
{
    namespace g3d
    {
        struct G3dObj
        {
            template <u32 N>
            struct ResNameDataT
            {
                u32 mLength;
                char mName[N]; // Null-terminated
            };

            struct TypeObj
            {

            };

            inline G3dObj(MEMAllocator *pAllocator, G3dObj *pObj) :
                mAllocator(pAllocator), G3DOBJ_0x4(pObj)
            {

            }

            G3dObj *G3DOBJ_0x4; // Not sure of parent/child relationship yet
            MEMAllocator *mAllocator; // at 0x8

            virtual bool IsDerivedFrom(const G3dObj&) const; // at 0x8
            virtual ~G3dObj(); // at 0x10
            virtual UNKTYPE * GetTypeObj() const; // at 0x14
            virtual UNKTYPE * GetTypeName() const; // at 0x18
        };
    }
}

#endif