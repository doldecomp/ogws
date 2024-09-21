#pragma ipa file

#include "eggModelEx.h"
#include "eggModelBoundingInfo.h"
#include "eggIScnProcModel.h"
#include "eggG3DUtility.h"
#include "eggAnalizeDL.h"
#include "g3d_scnobj.h"
#include "g3d_scnmdl.h"
#include "g3d_scnmdlsmpl.h"
#include "g3d_scnmdl1mat1shp.h"
#include "g3d_scnrfl.h"
#include "g3d_calcworld.h"
#include "g3d_calcview.h"
#include "g3d_state.h"
#include "g3d_draw.h"
#include "g3d_draw1mat1shp.h"

using namespace nw4r;

namespace EGG
{
    u32 ModelEx::sDrawFlag = cDrawShape_None;
    const char* ModelEx::sByteCodeCalcStr = "NodeTree";
    const char* ModelEx::sByteCodeMixStr = "NodeMix";

    ModelEx::ModelEx(g3d::ScnObj *obj) :
        mType(cType_None),
        mScnObj(g3d::G3dObj::DynamicCast<g3d::ScnLeaf>(obj))
    {
        if (g3d::G3dObj::DynamicCast<g3d::ScnMdl>(mScnObj) != NULL)
        {
            mType = cType_ScnMdl;
        }
        else if (g3d::G3dObj::DynamicCast<g3d::ScnMdlSimple>(mScnObj) != NULL)
        {
            mType = cType_ScnMdlSimple;
        }
        else if (g3d::G3dObj::DynamicCast<g3d::ScnMdl1Mat1Shp>(mScnObj) != NULL)
        {
            mType = cType_ScnMdl1Mat1Shp;
        }
        else if (g3d::G3dObj::DynamicCast<g3d::ScnRfl>(mScnObj) != NULL)
        {
            mType = cType_ScnRfl;
        }
        
        reset();
    }

    ModelEx::~ModelEx()
    {
        if (mFlag & cFlag_HasOriginalBV)
        {
            #line 100
            EGG_ASSERT(mpBV);
            delete mpBV;
        }
    }

    void ModelEx::reset()
    {
        mpBV = NULL;
        mFlag = 0;
    }

    u16 ModelEx::getNumShape() const
    {
        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                return getScnMdlSimple()->GetResMdl().GetResShpNumEntries();
            case cType_ScnMdl1Mat1Shp:
            case cType_ScnProcModel:
            case cType_ScnRfl:
                return 1;
            default:
                return 0;
        }
    }

    u16 ModelEx::getNumMaterial() const
    {
        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                return getScnMdlSimple()->GetResMdl().GetResMatNumEntries();
            case cType_ScnMdl1Mat1Shp:
                return getScnMdl1Mat1Shp()->GetResMat().IsValid() ? 1 : 0;
            case cType_ScnProcModel:
            case cType_ScnRfl:
                return 0;
            default:
                return 0;
        }
    }

    u16 ModelEx::getNumNode() const
    {
        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                return getScnMdlSimple()->GetResMdl().GetResNodeNumEntries();
            case cType_ScnMdl1Mat1Shp:
            case cType_ScnProcModel:
            case cType_ScnRfl:
                return 0;
            default:
                return 0;
        }
    }

    u16 ModelEx::getNumViewMtx() const
    {
        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                return getScnMdlSimple()->GetNumViewMtx();
            case cType_ScnMdl1Mat1Shp:
            case cType_ScnProcModel:
            case cType_ScnRfl:
                return 0;
            default:
                return 0;
        }
    }

    // https://decomp.me/scratch/zesmA
    void ModelEx::getShapeMinMax(u16 shapeIndex, math::VEC3 *pMin, math::VEC3 *pMax, bool doCalcWorld)
    {
    }

    void ModelEx::setVisible(bool vis)
    {
        if (mScnObj != NULL)
            mScnObj->SetScnObjOption(g3d::ScnObj::OPTION_VISIBLE, !vis);
    }

    void ModelEx::calcWorld(math::MTX34 *pWorldMtxArray) const
    {        
        #line 440
        EGG_ASSERT(pWorldMtxArray != NULL);

        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                // cast for regalloc
                u32 *wldAttrib = (u32 *)getScnMdlSimple()->GetWldMtxAttribArray();
                g3d::ResMdl mdl = getScnMdlSimple()->GetResMdl();
                const math::MTX34 *worldMtx = getScnMdlSimple()->GetMtxPtr(g3d::ScnObj::MTX_TYPE_WORLD);
                
                g3d::CalcWorld(pWorldMtxArray, wldAttrib,
                    mdl.GetResByteCode(sByteCodeCalcStr), worldMtx, mdl, NULL, NULL);

                if (mdl.GetResByteCode(sByteCodeMixStr) != NULL)
                {
                    g3d::CalcSkinning(pWorldMtxArray, wldAttrib, mdl,
                        mdl.GetResByteCode(sByteCodeMixStr));
                }
                break;
            case cType_ScnMdl1Mat1Shp:
            case cType_ScnProcModel:
            case cType_ScnRfl:
                getMtxType0(pWorldMtxArray);
                break;
            case cType_None:
            default:
                break;
        }
    }

    namespace
    {
        void UNUSED_ASSERTS_MODELEX(ModelBoundingInfo *bounding)
        {
            bounding->UNKNOWN_INLINE_0(NULL);
            bounding->UNKNOWN_INLINE_1(NULL);
        }
    }

    void ModelEx::calcView(const math::MTX34 *procArg, math::MTX34 *pViewMtxArray) const
    {        
        #line 491
        EGG_ASSERT(pViewMtxArray != NULL);

        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                g3d::CalcView(pViewMtxArray, NULL, getScnMdlSimple()->GetWldMtxArray(),
                    getScnMdlSimple()->GetWldMtxAttribArray(), getScnMdlSimple()->GetNumViewMtx(),
                    procArg, getScnMdlSimple()->GetResMdl(), NULL);
                break;
            case cType_ScnMdl1Mat1Shp:
            case cType_ScnProcModel:
            case cType_ScnRfl:
                mScnObj->G3dProc(g3d::G3dObj::G3DPROC_CALC_VIEW, 0, (void *)procArg);
                math::MTX34Copy(pViewMtxArray, mScnObj->GetMtxPtr(g3d::ScnObj::MTX_TYPE_VIEW));
                break;
            case cType_None:
            default:
                break;
        }
    }

    void ModelEx::drawShapeDirectly(u32 drawFlag, bool drawOpa, bool drawXlu, const math::MTX34 *viewPosNrm)
    {
        #line 539
        EGG_ASSERT(!( drawFlag & cDrawShape_None ));

        if (!drawOpa && !drawXlu) return;
        sDrawFlag = drawFlag;

        switch(mType)
        {
            case cType_ScnMdlSimple:
            case cType_ScnMdl:
                g3d::G3DState::Invalidate(0x0);
                int drawMode = getDrawMode(drawFlag);
                
                if (viewPosNrm == NULL)
                {
                    if (drawOpa) getScnMdlSimple()->G3dProc(g3d::G3dObj::G3DPROC_DRAW_OPA, 0, &drawMode);
                    if (drawXlu) getScnMdlSimple()->G3dProc(g3d::G3dObj::G3DPROC_DRAW_XLU, 0, &drawMode);
                }
                else
                {
                    g3d::DrawResMdlReplacement *replacement = (getScnMdl() == NULL)
                        ? NULL : getScnMdl()->GetDrawResMdlReplacement();
                    const u8 *byteCodeXlu = (drawXlu)
                        ? getScnMdlSimple()->GetByteCode(g3d::ScnMdlSimple::BYTE_CODE_DRAW_XLU) : NULL;
                    const u8 *byteCodeOpa = (drawOpa)
                        ? getScnMdlSimple()->GetByteCode(g3d::ScnMdlSimple::BYTE_CODE_DRAW_OPA) : NULL;
                    g3d::DrawResMdlDirectly(getScnMdlSimple()->GetResMdl(), viewPosNrm, NULL, NULL,
                        byteCodeOpa, byteCodeXlu, replacement, drawMode);
                }
                break;
            case cType_ScnMdl1Mat1Shp:
                g3d::G3DState::Invalidate(0x0);
                
                bool ctrl = true;
                int matShpDrawMode = getDrawCtrl(drawFlag, &ctrl);
                
                if (viewPosNrm == NULL)
                    viewPosNrm = mScnObj->GetMtxPtr(g3d::ScnObj::MTX_TYPE_VIEW);
                g3d::G3DState::SetViewPosNrmMtxArray(viewPosNrm, NULL, NULL);

                g3d::ResShp shp = getScnMdl1Mat1Shp()->GetResShp();
                g3d::Draw1Mat1ShpDirectly(ctrl ? getScnMdl1Mat1Shp()->GetResMat() : g3d::ResMat(NULL),
                    shp, viewPosNrm, 0, matShpDrawMode, NULL, NULL);
                g3d::G3DState::SetViewPosNrmMtxArray(NULL, NULL, NULL);
                break;
            case cType_ScnProcModel:
                u32 procDrawFlag = 0;
                if (drawFlag & 0x2) procDrawFlag |= 0x1;
                if (drawFlag & 0x4) procDrawFlag |= 0x2;
                if (drawOpa) getScnProcModel()->draw(true, procDrawFlag);
                if (drawXlu) getScnProcModel()->draw(false, procDrawFlag);
                break;
            case cType_ScnRfl:
                if (drawOpa) getScnRfl()->G3dProc(g3d::G3dObj::G3DPROC_DRAW_OPA, 0, NULL);
                if (drawXlu) getScnRfl()->G3dProc(g3d::G3dObj::G3DPROC_DRAW_XLU, 0, NULL);
                break;
        }

        sDrawFlag = cDrawShape_None;
    }

    // https://decomp.me/scratch/0xxAL
    u16 ModelEx::replaceTexture(const char *name, const int& r5, bool r6,
        TextureReplaceResult *result, u16 r8, bool matAccess)
    {
    }

    void ModelEx::attachBoundingInfo(ModelBoundingInfo *bounding)
    {
        #line 797
        EGG_ASSERT(mpBV == NULL);
        mpBV = bounding;
    }

    g3d::ResShp ModelEx::getResShp(u16 shapeIndex) const
    {
        #line 917
        EGG_ASSERT(shapeIndex < getNumShape());

        if (getScnMdlSimple() != NULL)
            return getScnMdlSimple()->GetResMdl().GetResShp(shapeIndex);

        if (getScnMdl1Mat1Shp() != NULL)
            return getScnMdl1Mat1Shp()->GetResShp();

        return g3d::ResShp(NULL);
    }

    g3d::ResMat ModelEx::getResMat(u16 matIndex) const
    {
        #line 938
        EGG_ASSERT(matIndex < getNumMaterial());

        if (getScnMdlSimple() != NULL)
            return getScnMdlSimple()->GetResMdl().GetResMat(matIndex);

        if (getScnMdl1Mat1Shp() != NULL)
            return getScnMdl1Mat1Shp()->GetResMat();

        return g3d::ResMat(NULL);
    }

    int ModelEx::getDrawMode(u32 drawFlag)
    {
        int drawMode = 0x3;

        if ((drawFlag & 0x8) != 0)
        {
            drawMode |= 0xC;
        }
        else
        {
            if (drawFlag & 0x2) drawMode |= 0x4;
            if (drawFlag & 0x4) drawMode |= 0x8;
        }

        return drawMode;
    }

    int ModelEx::getDrawCtrl(u32 drawFlag, bool *r4)
    {
        int drawMode = 1;
        bool phi_r6 = true;
        
        if ((drawFlag & 0x8) != 0)
        {
            phi_r6 = false;
            drawMode |= 0x8;
        }
        else
        {
            if ((drawFlag & 0x2) != 0) phi_r6 = false;
            if ((drawFlag & 0x4) != 0) drawMode |= 0x8;
        }

        if (r4 != NULL) *r4 = phi_r6;
        
        return drawMode;
    }

    g3d::ResTexSrt ModelEx::getResTexSrt(u16 matIndex)
    {
        if (mType == cType_ScnMdl)
        {
            g3d::ScnMdl::CopiedMatAccess matAccess(getScnMdl(), matIndex);
            return matAccess.GetResTexSrtEx();
        }

        if (getScnMdlSimple() != NULL)
            return getScnMdlSimple()->GetResMdl().GetResMat(matIndex).GetResTexSrt();

        return g3d::ResTexSrt(NULL);
    }
}
