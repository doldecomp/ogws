#ifndef EGG_GFXE_MODEL_BOUNDING_INFO_H
#define EGG_GFXE_MODEL_BOUNDING_INFO_H
#include "eggAssert.h"
#include "types_egg.h"

namespace EGG {
class ModelBoundingInfo {
public:
    enum BoundFlag {
        BoundFlag_AABB = 1 << 0,
        BoundFlag_AABBSet = 1 << 1,
        BoundFlag_Sphere = 1 << 2,
        BoundFlag_SphereSet = 1 << 3,
    };

    struct AABBData {
        struct AABBShape {
            f32 FLOAT_0x0;
            f32 FLOAT_0x4;
            f32 FLOAT_0x8;
            f32 FLOAT_0xC;
            f32 FLOAT_0x10;
            f32 FLOAT_0x14;
        };

        AABBShape m_shape;      // at 0x0
        AABBShape* m_pShapeSet; // at 0x18
    };

    struct SphereData {
        struct SphereShape {
            f32 FLOAT_0x0;
            f32 FLOAT_0x4;
            f32 FLOAT_0x8;
            f32 FLOAT_0xC;
        };

        SphereShape m_shape;      // at 0x0
        SphereShape* m_pShapeSet; // at 0x10
    };

protected:
    ModelEx* m_pMdl; // at 0x0
    f32 FLOAT_0x4;
    AABBData* m_pAABB; // at 0x8
    AABBData* AABB_0xC;
    SphereData* m_pSphere; // at 0x10

public:
    ModelBoundingInfo(u32, ModelEx*);
    virtual ~ModelBoundingInfo();

    void Calc();

    SphereData* getSphere() const {
#line 99
        EGG_ASSERT(m_pSphere);
        return m_pSphere;
    }

    // 80094b64, stub inline for weak data in eggModelEx.o
    UNKTYPE UNKNOWN_INLINE_1(SphereData* pSphere) {
#line 191
        EGG_ASSERT(pSphere);
    }

    // 80093db8, stub inline for weak data in eggModelEx.o
    UNKTYPE UNKNOWN_INLINE_0(AABBData* pAABB) {
#line 214
        EGG_ASSERT(pAABB);
    }
};
} // namespace EGG

#endif
