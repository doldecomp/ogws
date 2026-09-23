#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <algorithm>

namespace EGG {

ModelBoundingInfo::ModelBoundingInfo(u32 flags, ModelEx* pMdl)
    : m_pMdl(pMdl), unk4(1.0f), m_pAABB(NULL), m_pSphere(NULL) {

#line 148
    EGG_ASSERT(pMdl);
    EGG_ASSERT(m_pMdl->getNumShape() > 0);

    m_pMdl->attachBoundingInfo(this);
    m_pBV = createShape<AABBShape>(true);

    for (u16 i = 0; i < m_pMdl->getNumShape(); i++) {
        AABBShape box;
        pMdl->getShapeMinMax(i, &box.min, &box.max, i == 0);

        if (box.min.x > box.max.x) {
            std::swap(box.min.x, box.max.x);
        }

        if (box.min.y > box.max.y) {
            std::swap(box.min.y, box.max.y);
        }

        if (box.min.z > box.max.z) {
            std::swap(box.min.z, box.max.z);
        }

        if (i != 0) {
            setAABB(m_pBV, box.min, box.max);
        } else {
            m_pBV->m_shape = box;
        }

        m_pBV->m_pShapeSet[i] = box;
    }

    if (flags & cBoundFlag_AABB) {
        m_pAABB = createShape<AABBShape>(flags & cBoundFlag_AABBSet);
    }

    if (flags & cBoundFlag_Sphere) {
        m_pSphere = createShape<SphereShape>(flags & cBoundFlag_SphereSet);
    }

    calc();
}

ModelBoundingInfo::~ModelBoundingInfo() {
    deleteShape(m_pBV);

    if (m_pAABB != NULL) {
        deleteShape(m_pAABB);
    }

    if (m_pSphere != NULL) {
        deleteShape(m_pSphere);
    }
}

void ModelBoundingInfo::calc() {
    nw4r::math::MTX34 mtx;
    m_pMdl->getLocalMtx(&mtx);

    nw4r::math::VEC3 bx, by, bz;
    nw4r::math::VEC3* pBases[] = {&bx, &by, &bz};

    bx.x = mtx._00;
    bx.y = mtx._10;
    bx.z = mtx._20;

    by.x = mtx._01;
    by.y = mtx._11;
    by.z = mtx._21;

    bz.x = mtx._02;
    bz.y = mtx._12;
    bz.z = mtx._22;

    nw4r::math::VEC3 scale;
    nw4r::g3d::ScnLeaf* pScnLeaf = m_pMdl->getScnLeaf();

    if (pScnLeaf != NULL) {
        scale = pScnLeaf->GetScale();
    } else {
        scale.x = scale.y = scale.z = 1.0f;
    }

    mtx._00 *= scale.x;
    mtx._10 *= scale.x;
    mtx._20 *= scale.x;

    mtx._01 *= scale.y;
    mtx._11 *= scale.y;
    mtx._21 *= scale.y;

    mtx._02 *= scale.z;
    mtx._12 *= scale.z;
    mtx._22 *= scale.z;

    nw4r::math::VEC3 min;
    nw4r::math::VEC3Transform(&min, &mtx, &m_pAABB->m_shape.min);

    nw4r::math::VEC3 max;
    nw4r::math::VEC3Transform(&max, &mtx, &m_pAABB->m_shape.max);

    if (unk4 != 1.0f) {
        nw4r::math::VEC3 sp74;
        f32 sc = (unk4 - 1.0f) / 2;

        sp74.x = sc;
        sp74.y = sc * (max.y - min.y);
        sp74.z = sc * (max.z - min.z);

        min.x -= sp74.x;
        min.y -= sp74.y;
        min.z -= sp74.z;

        max.x += sp74.x;
        max.y += sp74.y;
        max.z += sp74.z;
    }

    nw4r::math::VEC3 setMin[128];
    nw4r::math::VEC3 setMax[128];

    if ((m_pAABB != NULL && m_pAABB->m_pShapeSet != NULL) ||
        (m_pSphere != NULL && m_pSphere->m_pShapeSet)) {

        for (u16 i = 0; i < m_pMdl->getNumShape(); i++) {
            nw4r::math::VEC3Transform(&setMin[i], &mtx,
                                      &m_pAABB->m_pShapeSet[i].min);

            nw4r::math::VEC3Transform(&setMax[i], &mtx,
                                      &m_pAABB->m_pShapeSet[i].max);

            if (unk4 != 1.0f) {
                nw4r::math::VEC3 sp68;
                f32 sc = (unk4 - 1.0f) / 2;

                sp68.x = sc;
                sp68.y = sc * (max.y - min.y);
                sp68.z = sc * (max.z - min.z);

                setMin[i].x -= sp68.x;
                setMin[i].y -= sp68.y;
                setMin[i].z -= sp68.z;

                setMax[i].x += sp68.x;
                setMax[i].y += sp68.y;
                setMax[i].z += sp68.z;
            }
        }
    }

    if (m_pAABB != NULL) {
        m_pAABB->m_shape.min = min;
        m_pAABB->m_shape.max = max;
        nw4r::math::VEC3 delta = max - min;

        nw4r::math::VEC3 sp50(nw4r::math::VEC3Dot(&delta, pBases[0]),
                              nw4r::math::VEC3Dot(&delta, pBases[1]),
                              nw4r::math::VEC3Dot(&delta, pBases[2]));

        for (int i = 0; i < 8; i++) {
            if (i < 6) {
                f32 value = i < 3 ? 1.0f : -1.0f;

                // . . .
            }
        }
    }

    if (m_pSphere != NULL) {
        m_pSphere->m_shape.center.x = (max.x + min.x) / 2;
        m_pSphere->m_shape.center.y = (max.y + min.y) / 2;
        m_pSphere->m_shape.center.z = (max.z + min.z) / 2;

        nw4r::math::VEC3 dir(max.x - min.x, max.y - min.y, max.z - min.z);
        m_pSphere->m_shape.r = 0.5f * nw4r::math::VEC3Len(&dir);

        if (m_pSphere->m_pShapeSet != NULL) {
            for (u16 i = 0; i < m_pMdl->getNumShape(); i++) {
                setSphere(&m_pSphere->m_pShapeSet[i], setMin[i], setMax[i]);
            }
        }
    }
}

} // namespace EGG
