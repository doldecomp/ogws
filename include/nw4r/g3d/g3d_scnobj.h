#ifndef NW4R_G3D_SCNOBJ_H
#define NW4R_G3D_SCNOBJ_H
#include "types_nw4r.h"
#include "math_types.h"
#include "g3d_obj.h"

namespace nw4r
{
    namespace g3d
    {
        inline u32 align4(u32 x) { return x + (4 - 1) & ~4; }

        // TO-DO: Refactor G3dObj
        class ScnObj : public G3dObj
        {
        public:
            enum ForEachResult
            {

            };

            typedef ForEachResult (* ForEachAction)(ScnObj *, void *);

            ScnObj(MEMAllocator *);

            virtual bool IsDerivedFrom(const TypeObj&) const; // at 0x8
            virtual UNKTYPE G3dProc(u32, u32, void *) = 0; // at 0xC
            virtual ~ScnObj(); // at 0x10
            virtual const TypeObj GetTypeObj() const; // at 0x14
            virtual const char * GetTypeName() const; // at 0x18
            virtual ForEachResult ForEach(ForEachAction, void *, bool) = 0; // at 0x1C
            virtual UNKTYPE SetScnObjOption(u32, u32); // at 0x20
            virtual UNKTYPE GetScnObjOption(u32, u32 *); // at 0x24
            virtual UNKTYPE GetValueForSortOpa(); // at 0x28
            virtual UNKTYPE GetValueForSortXlu(); // at 0x2C
            virtual void CalcWorldMtx(const math::MTX34 *, u32 *); // at 0x30

            void SetPriorityDrawOpa(int);
            void SetPriorityDrawXlu(int);

        private:
            math::MTX34 MTX34_0xC;
            math::MTX34 mWorldMtx; // at 0x3C
            math::MTX34 mViewMtx; // at 0x6C
            math::AABB AABB_0x9C;
            math::AABB AABB_0xB4;
            u32 mFlags; // at 0xCC
            u8 mPriorityDrawOpa; // at 0xD0
            u8 mPriorityDrawXlu; // at 0xD1
            u8 BYTE_0xD2;
            u8 BYTE_0xD3;
            UNKWORD WORD_0xD4;
            u8 BYTE_0xD8;
            u8 BYTE_0xD9;
            u16 SHORT_0xDA;

            NW4R_G3D_TYPE_OBJ_DECL(ScnObj);
        };

        class ScnLeaf : public ScnObj
        {
        public:
            ScnLeaf(MEMAllocator *allocator) : ScnObj(allocator), VEC3_0xDC(1.0f, 1.0f, 1.0f) {}

            UNKTYPE DefG3dProcScnLeaf(u32, u32, void *);

            virtual bool IsDerivedFrom(const TypeObj&) const; // at 0x8
            virtual UNKTYPE G3dProc(u32, u32, void *) = 0; // at 0xC
            virtual ~ScnLeaf(); // at 0x10
            virtual const TypeObj GetTypeObj() const; // at 0x14
            virtual const char * GetTypeName() const; // at 0x18
            virtual ForEachResult ForEach(ForEachAction, void *, bool); // at 0x1C
            virtual UNKTYPE SetScnObjOption(u32, u32); // at 0x20
            virtual UNKTYPE GetScnObjOption(u32, u32 *); // at 0x24
            virtual UNKTYPE CalcWorldMtx(const math::MTX34 *, u32 *); // at 0x30        

        private:
            math::VEC3 VEC3_0xDC;

            NW4R_G3D_TYPE_OBJ_DECL(ScnLeaf);
        };

        // TO-DO
        class ScnGroup : public ScnObj
        {
        public:
            ScnGroup(MEMAllocator *, ScnObj **, u32);

            bool PushBack(ScnObj *);
            bool Remove(ScnObj *);

        private:
            NW4R_G3D_TYPE_OBJ_DECL(ScnGroup);
        };
    }
}

#endif