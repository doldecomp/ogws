#include "eggModelSnapshot.h"
#include "eggModelEx.h"
#include "eggModelBoundingInfo.h"
#include <revolution/MTX.h>

namespace EGG
{
    ModelSnapshot::ModelSnapshot(u16 w, u16 h, GXTexFmt fmt, u16 mdlMax) :
        CapTexture(w, h, fmt),
        m_mdlMax(mdlMax),
        m_width(w),
        m_height(h),
        m_flags(0),
        WORD_0x38(0),
        m_mdlList(NULL),
        FLOAT_0x50(0.0f),
        FLOAT_0x54(0.0f),
        FLOAT_0x58(0.0f),
        FLOAT_0x5C(0.0f),
        FLOAT_0x60(0.0f),
        FLOAT_0x64(0.0f),
        FLOAT_0x68(0.0f),
        FLOAT_0x6C(0.0f)
    {
        #line 37
        EGG_ASSERT(mdlMax > 0);

        configure();
        allocTexBufferAndHeader();
        m_mdlList = new ModelBind[mdlMax];

        FLOAT_0x44 = 0.0f;
        FLOAT_0x40 = 0.0f;
        FLOAT_0x4C = 0.0f;
        FLOAT_0x48 = 0.0f;
    }

    void ModelSnapshot::DoResetList()
    {
        ResetList();
    }

    void ModelSnapshot::ResetList()
    {
        m_mdlNum = 0;
        
        for (int i = 0; i < m_mdlMax; i++)
        {
            m_mdlList[i].model = NULL;
            m_mdlList[i].FLOAT_0x4 = 1.0f;
            m_mdlList[i].BYTE_0x8 = 0;
        }
    }

    void ModelSnapshot::AddModelEx(ModelEx *pModel, f32 f1)
    {
        #line 83
        EGG_ASSERT(m_mdlNum < m_mdlMax);
        EGG_ASSERT(pModel);
        EGG_ASSERT_MSG(pModel->getBoundingInfo() != NULL, "ModelEx has no bounding info. Please create.");

        m_mdlList[m_mdlNum].model = pModel;
        m_mdlList[m_mdlNum].FLOAT_0x4 = f1;
        m_mdlList[m_mdlNum].BYTE_0x8 = 0;
        m_mdlNum++;
    }

    void ModelSnapshot::GatherModel(f32 f1)
    {
        if (m_mdlNum != 0)
        {
            if (m_flags & SNAPSHOT_0x2)
            {
                FLOAT_0x50 = FLOAT_0x5C;
                FLOAT_0x54 = FLOAT_0x60;
                FLOAT_0x58 = FLOAT_0x64;
                FLOAT_0x68 = FLOAT_0x6C;
            }

            for (int i = 0; i < m_mdlNum; i++)
            {
                ModelEx *pModel = m_mdlList[i].model;
                #line 117
                EGG_ASSERT(pModel);

                ModelBoundingInfo::SphereData *sph = pModel->getBoundingInfo()->getSphere();

                if (i > 0)
                {
                    f32 z = sph->m_shape.FLOAT_0xC - FLOAT_0x58;
                    f32 y = sph->m_shape.FLOAT_0x8 - FLOAT_0x54;
                    f32 x = sph->m_shape.FLOAT_0x4 - FLOAT_0x50;

                    Vec v;
                    v.z = z;
                    v.y = y;
                    v.x = x;
                    f32 mag = PSVECMag(&v);

                    f32 f2 = mag + sph->m_shape.FLOAT_0x0;
                    f32 f4 = f2 - FLOAT_0x68;
                    if (f4 > 0.0f)
                    {
                        f4 *= 0.5f;
                        
                        if (mag > 0.0f)
                        {
                            f32 scale = f4 / mag;
                            FLOAT_0x50 += v.x * scale;
                            FLOAT_0x54 += v.y * scale;
                            FLOAT_0x58 += v.z * scale;
                        }

                        FLOAT_0x68 += f4;
                    }
                }
                else
                {
                    if ((m_flags & SNAPSHOT_0x2) == 0)
                    {
                        FLOAT_0x50 = sph->m_shape.FLOAT_0x4;
                        FLOAT_0x54 = sph->m_shape.FLOAT_0x8;
                        FLOAT_0x58 = sph->m_shape.FLOAT_0xC;
                        FLOAT_0x68 = sph->m_shape.FLOAT_0x0;
                    }
                }
            }

            FLOAT_0x68 *= f1;
            return;
        }

        FLOAT_0x68 = 0.0f;
        FLOAT_0x58 = 0.0f;
        FLOAT_0x54 = 0.0f;
        FLOAT_0x50 = 0.0f;
    }

    ModelSnapshot::~ModelSnapshot()
    {
    }

    namespace
    {
        void UNUSED_ASSERTS_MODELSNAPSHOT()
        {
            EGG_ASSERT_MSG(false, "pScreen");
        }
    }
}
