#ifndef EGG_GFXE_MODEL_BOUNDING_INFO_H
#define EGG_GFXE_MODEL_BOUNDING_INFO_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggModelEx.h>
#include <egg/prim.h>

#include <nw4r/math.h>

namespace EGG {

// Forward declarations
class ModelEx;

class ModelBoundingInfo {
public:
    enum BoundFlag {
        cBoundFlag_AABB = 1 << 0,
        cBoundFlag_AABBSet = 1 << 1,
        cBoundFlag_Sphere = 1 << 2,
        cBoundFlag_SphereSet = 1 << 3,
    };

    struct SphereShape {
        f32 r;                   // at 0x0
        nw4r::math::VEC3 center; // at 0x4
    };

    struct AABBShape {
        nw4r::math::VEC3 min; // at 0x0
        nw4r::math::VEC3 max; // at 0xC
    };

private:
    template <typename TShape> struct TData {
        TShape m_shape;
        TShape* m_pShapeSet;
    };

private:
    ModelEx* m_pMdl; // at 0x0
    f32 unk4;
    TData<AABBShape>* m_pBV;       // at 0x8
    TData<AABBShape>* m_pAABB;     // at 0xC
    TData<SphereShape>* m_pSphere; // at 0x10

public:
    ModelBoundingInfo(u32 flags, ModelEx* pMdl);
    virtual ~ModelBoundingInfo(); // at 0x8

    void calc();

    SphereShape& getShapeSphere() const {
#line 99
        EGG_ASSERT(m_pSphere);
        return m_pSphere->m_shape;
    }

private:
    template <typename TShape>
    TData<TShape>* createShape(bool shapeSet) DECOMP_DONT_INLINE {
#line 150
        TData<TShape>* pData = new TData<TShape>();
        EGG_ASSERT(pData);

        pData->m_pShapeSet = NULL;

        if (shapeSet) {
#line 157
            pData->m_pShapeSet = new TShape[m_pMdl->getNumShape()];
            EGG_ASSERT(pData->m_pShapeSet);
        }

        return pData;
    }

    template <typename TShape>
    void deleteShape(TData<TShape>* pData) DECOMP_DONT_INLINE {
        if (pData->m_pShapeSet != NULL) {
            delete[] pData->m_pShapeSet;
        }

        delete pData;
    }

    void setSphere(SphereShape* pSphere, const nw4r::math::VEC3& rMin,
                   const nw4r::math::VEC3& rMax) {
#line 191
        EGG_ASSERT(pSphere);

        pSphere->center.x = (rMax.x + rMin.x) / 2;
        pSphere->center.y = (rMax.y + rMin.y) / 2;
        pSphere->center.z = (rMax.z + rMin.z) / 2;

        nw4r::math::VEC3 dir(rMax.x - rMin.x, rMax.y - rMin.y, rMax.z - rMin.z);
        pSphere->r = 0.5f * nw4r::math::VEC3Len(&dir);
    }

    void setAABB(TData<AABBShape>* pAABB, const nw4r::math::VEC3& rMin,
                 const nw4r::math::VEC3& rMax) {
#line 214
        EGG_ASSERT(pAABB);

        if (rMin.x < pAABB->m_shape.min.x) {
            pAABB->m_shape.min.x = rMin.x;
        }
        if (rMax.x > pAABB->m_shape.max.x) {
            pAABB->m_shape.max.x = rMax.x;
        }

        if (rMin.y < pAABB->m_shape.min.y) {
            pAABB->m_shape.min.y = rMin.y;
        }
        if (rMax.y > pAABB->m_shape.max.y) {
            pAABB->m_shape.max.y = rMax.y;
        }

        if (rMin.z < pAABB->m_shape.min.z) {
            pAABB->m_shape.min.z = rMin.z;
        }
        if (rMax.z > pAABB->m_shape.max.z) {
            pAABB->m_shape.max.z = rMax.z;
        }
    }
};

} // namespace EGG

#endif
