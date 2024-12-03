#ifndef NW4R_G3D_SCNRFL_H
#define NW4R_G3D_SCNRFL_H
#include "types_nw4r.h"
#include <RVLFaceLib/RFL_Model.h>
#include <RVLFaceLib/RFL_MiddleDatabase.h>

namespace nw4r
{
    namespace g3d
    {
        class ScnRfl : public ScnLeaf
        {
        public:
            struct RflData
            {
                bool SetupCharModel(RFLDataSource, u16, RFLMiddleDB *);
            };

        public:
            static ScnRfl * Construct(MEMAllocator *, u32 *, RFLResolution, u32, u32);
            ScnRfl(MEMAllocator *, ScnRfl *, RflData *, void *, u32);

            virtual void G3dProc(u32, u32, void *); // at 0xC
            virtual ~ScnRfl(); // at 0x10

            bool GetExpression(RFLExpression *);
            bool SetExpression(RFLExpression);

            void SetFogIdx(int);
            void SetLightSetIdx(int);

        public:
            NW4R_G3D_RTTI_DECL_DERIVED(ScnRfl, ScnLeaf);
        };
    }
}

#endif
