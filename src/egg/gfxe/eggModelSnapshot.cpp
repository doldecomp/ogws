#include <egg/gfxe.h>

#include <nw4r/math.h>

namespace EGG {

ModelSnapshot::ModelSnapshot(u16 width, u16 height, GXTexFmt format, u16 mdlMax)
    : CapTexture(width, height, format),
      m_mdlMax(mdlMax),
      m_width(width),
      m_height(height),
      m_flags(0),
      unk38(0),
      m_mdlList(NULL),
      m_center(0.0f, 0.0f, 0.0f),
      unk5C(0.0f, 0.0f, 0.0f),
      m_radius(0.0f),
      unk6C(0.0f) {

#line 37
    EGG_ASSERT(mdlMax > 0);

    configure();
    allocWithHeaderDebug();
    m_mdlList = new ModelBind[mdlMax];

    unk40 = unk44 = 0.0f;
    unk48 = unk4C = 0.0f;
}

void ModelSnapshot::InitList() {
    ResetList();
}

void ModelSnapshot::ResetList() {
    m_mdlNum = 0;

    for (int i = 0; i < m_mdlMax; i++) {
        m_mdlList[i].pModel = NULL;
        m_mdlList[i].adjust = 1.0f;
        m_mdlList[i].useMat = false;
    }
}

void ModelSnapshot::AddModelEx(ModelEx* pModel, f32 adjust) {
#line 83
    EGG_ASSERT(m_mdlNum < m_mdlMax);
    EGG_ASSERT(pModel);
    EGG_ASSERT_MSG(pModel->getBoundingInfo() != NULL, "ModelEx has no bounding info. Please create.");

    m_mdlList[m_mdlNum].pModel = pModel;
    m_mdlList[m_mdlNum].adjust = adjust;
    m_mdlList[m_mdlNum].useMat = false;
    m_mdlNum++;
}

void ModelSnapshot::GatherModel(f32 adjust) {
    if (m_mdlNum != 0) {
        if (m_flags & cFlag_1) {
            m_center = unk5C;
            m_radius = unk6C;
        }

        for (int i = 0; i < m_mdlNum; i++) {
#line 116
            ModelEx* pModel = m_mdlList[i].pModel;
            EGG_ASSERT(pModel);

            ModelBoundingInfo::SphereShape& rSphere =
                pModel->getBoundingInfo()->getShapeSphere();

            if (i > 0) {
                nw4r::math::VEC3 delta(rSphere.center.x - m_center.x,
                                       rSphere.center.y - m_center.y,
                                       rSphere.center.z - m_center.z);

                // Distance from the gather sphere to the bounding sphere
                f32 dist = nw4r::math::VEC3Len(&delta);

                // Farthest point of the bounding
                f32 farEdge = dist + rSphere.r;
                // Amount of the bounding outside of the gather sphere
                f32 outside = farEdge - m_radius;

                if (outside > 0.0f) {
                    outside /= 2;

                    // Shift the gather sphere towards the new model
                    if (dist > 0.0f) {
                        f32 scale = outside / dist;
                        m_center.x += delta.x * scale;
                        m_center.y += delta.y * scale;
                        m_center.z += delta.z * scale;
                    }

                    m_radius += outside;
                }

            } else if (!(m_flags & cFlag_1)) {
                m_center.x = rSphere.center.x;
                m_center.y = rSphere.center.y;
                m_center.z = rSphere.center.z;
                m_radius = rSphere.r;
            }
        }

        m_radius *= adjust;

    } else {
        m_center.x = m_center.y = m_center.z = m_radius = 0.0f;
    }
}

DECOMP_FORCEACTIVE(eggModelSnapshot_cpp,
                  "pScreen");

} // namespace EGG
