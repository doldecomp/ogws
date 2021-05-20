#ifndef NW4R_G3D_G3DOBJ_H
#define NW4R_G3D_G3DOBJ_H
#include "types_nw4r.h"
#include <RevoSDK/MEM/mem_allocator.h>

#define NW4R_G3D_TYPE_OBJ_DECL(VAL) static const G3dObj::ResNameDataT<sizeof(#VAL)> TYPE_NAME
#define NW4R_G3D_TYPE_OBJ_DEF(VAL) const G3dObj::ResNameDataT<sizeof(#VAL)> VAL::TYPE_NAME = {sizeof(#VAL), #VAL}

namespace nw4r
{
    namespace g3d
    {
        namespace detail
        {
            inline void * AllocFromAllocator(MEMAllocator *pAllocator, u32 size)
            {
                return MEMAllocFromAllocator(pAllocator, size);
            }

            inline void FreeToAllocator(MEMAllocator *pAllocator, void * pBlock)
            {
                return MEMFreeToAllocator(pAllocator, pBlock);
            }
        }

        struct G3dObj
        {
            enum G3dProcTask
            {
                G3DPROC_CHILD_DETACHED = 0x10001,
            };

            template <u32 N>
            struct ResNameDataT
            {
                u32 mLength;
                char mName[N];
            };

            struct TypeObj
            {
                // Unoffical name, but structure does exist via GPCS
                // It also makes sense because templates need to be resolved at compile-time,
                // so this is a way to store a pointer to one
                struct TypeObjData
                {
                    u32 mLength; // at 0x0
                    char mName[]; // at 0x4
                };

                template <u32 N>
                inline TypeObj(const ResNameDataT<N>& pRes) : mData((const TypeObjData *)&pRes) {}

                inline u32 GetTypeID() const
                {
                    return (u32)mData;
                }

                inline const char * GetTypeName() const
                {
                    return mData->mName;
                }

                inline bool operator==(const TypeObj& rhs) const
                {
                    return GetTypeID() == rhs.GetTypeID();
                }

                const TypeObjData *mData; // at 0x0
            };

            void Destroy();
            virtual bool IsDerivedFrom(const TypeObj&) const; // at 0x8
            // Unofficial
            virtual UNKTYPE G3dProc(u32, u32, void *) = 0; // at 0xC
            virtual ~G3dObj(); // at 0x10
            virtual const G3dObj::TypeObj GetTypeObj() const; // at 0x14
            virtual const char * GetTypeName() const; // at 0x18

            inline G3dObj(MEMAllocator *pAllocator, G3dObj *pObj)
                : mAllocator(pAllocator), mParent(pObj) {}

            inline G3dObj * GetParent() const
            {
                return mParent;
            }

            static inline const G3dObj::TypeObj GetTypeObjStatic()
            {
                return TypeObj(TYPE_NAME);
            }

            static inline void * Alloc(MEMAllocator *pAllocator, u32 size)
            {
                return detail::AllocFromAllocator(pAllocator, size);
            }

            static inline void Dealloc(MEMAllocator *pAllocator, void *pBlock)
            {
                detail::FreeToAllocator(pAllocator, pBlock);
            }

            static inline void * operator new(size_t size, void *pBlock) {return pBlock;}
            static inline void operator delete(void *pBlock) {}

            G3dObj *mParent; // at 0x4
            MEMAllocator *mAllocator; // at 0x8

            NW4R_G3D_TYPE_OBJ_DECL(G3dObj);
        };
    }
}

#endif