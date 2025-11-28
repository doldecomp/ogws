#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

namespace EGG {

u32 ModelEx::sDrawFlag = cDrawShape_None;

DECOMP_FORCEACTIVE(eggModelEx_cpp,
                  "eggModelEx.cpp",
                  "pModel");

ModelEx::ModelEx(nw4r::g3d::ScnObj* pObj)
    : mType(cType_Unknown),
      mScnObj(nw4r::g3d::G3dObj::DynamicCast<nw4r::g3d::ScnLeaf>(pObj)) {

    // clang-format off
    if (nw4r::g3d::G3dObj::DynamicCast<nw4r::g3d::ScnMdl>(mScnObj) != NULL) {
        mType = cType_ScnMdl;
    } else if (nw4r::g3d::G3dObj::DynamicCast<nw4r::g3d::ScnMdlSimple>(mScnObj) != NULL) {
        mType = cType_ScnMdlSimple;
    } else if (nw4r::g3d::G3dObj::DynamicCast<nw4r::g3d::ScnMdl1Mat1Shp>(mScnObj) != NULL) {
        mType = cType_ScnMdl1Mat1Shp;
    } else if (nw4r::g3d::G3dObj::DynamicCast<nw4r::g3d::ScnRfl>(mScnObj) != NULL) {
        mType = cType_ScnRfl;
    }
    // clang-format on

    reset();
}

ModelEx::~ModelEx() {
    if (mFlag & cFlag_HasOriginalBV) {
#line 100
        EGG_ASSERT(mpBV);
        delete mpBV;
    }
}

DECOMP_FORCEACTIVE(eggModelEx_cpp_1,
                  "mpBV == NULL && !( mFlag & cFlag_HasOriginalBV )",
                  "RFL",
                  "Unknown");

void ModelEx::reset() {
    mpBV = NULL;
    mFlag = 0;
}

u16 ModelEx::getNumShape() const {
    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        return getScnMdlSimple()->GetResMdl().GetResShpNumEntries();
    }

    case cType_ScnMdl1Mat1Shp:
    case cType_ScnProcModel:
    case cType_ScnRfl: {
        return 1;
    }

    default: {
        return 0;
    }
    }
}

u16 ModelEx::getNumMaterial() const {
    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        return getScnMdlSimple()->GetResMdl().GetResMatNumEntries();
    }

    case cType_ScnMdl1Mat1Shp: {
        return getScnMdl1Mat1Shp()->GetResMat().IsValid() ? 1 : 0;
    }

    case cType_ScnProcModel:
    case cType_ScnRfl: {
        return 0;
    }

    default: {
        return 0;
    }
    }
}

u16 ModelEx::getNumNode() const {
    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        return getScnMdlSimple()->GetResMdl().GetResNodeNumEntries();
    }

    case cType_ScnMdl1Mat1Shp:
    case cType_ScnProcModel:
    case cType_ScnRfl: {
        return 0;
    }

    default: {
        return 0;
    }
    }
}

u16 ModelEx::getNumViewMtx() const {
    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        return getScnMdlSimple()->GetNumViewMtx();
    }

    case cType_ScnMdl1Mat1Shp:
    case cType_ScnProcModel:
    case cType_ScnRfl: {
        return 0;
    }

    default: {
        return 0;
    }
    }
}

void ModelEx::getShapeMinMax(u16 shapeIndex, nw4r::math::VEC3* pMin,
                             nw4r::math::VEC3* pMax, bool doCalcWorld) {
#line 282
    EGG_ASSERT(pMin);
    EGG_ASSERT(pMax);
    EGG_ASSERT(shapeIndex < getNumShape());

    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl:
    case cType_ScnMdl1Mat1Shp: {
        nw4r::g3d::ResShp shp = getResShp(shapeIndex);
#line 294
        EGG_ASSERT(shp.IsValid());

        G3DUtility::reset();
        u32 worldMtxSize = getNumNode() * sizeof(nw4r::math::MTX34);

        nw4r::math::MTX34* pWorldMtxArray =
            static_cast<nw4r::math::MTX34*>(G3DUtility::alloc(worldMtxSize));

        if (doCalcWorld) {
            calcWorld(pWorldMtxArray);
        }

        (void)shp.GetResVtxPos();

        s32 shpMtxIdx = shp.ref().curMtxIdx;
        AnalizeDL dl(shp);
        bool first = true;

        while (dl.advance() != AnalizeDL::TYPE_NOOP) {
            while (dl.advance() != AnalizeDL::TYPE_VERTEX) {
                ;
            }

            while (dl.advance() == AnalizeDL::TYPE_VERTEX) {
                s32 mtxIdx = dl.getVtxResult().m_mtxIdx;
                if (mtxIdx == -1) {
                    mtxIdx = shpMtxIdx;
                }

                nw4r::math::VEC3 v;
                nw4r::math::VEC3Transform(&v, &pWorldMtxArray[mtxIdx],
                                          &dl.getVtxResult().m_vtxPos);

                if (first) {
                    first = false;

                    *pMax = v;
                    *pMin = *pMax;
                } else {
                    nw4r::math::VEC3Minimize(pMin, pMin, &v);
                    nw4r::math::VEC3Maximize(pMax, pMax, &v);
                }
            }
        }
        break;
    }

    case cType_ScnProcModel: {
        getScnProcModel()->getMinMaxScnProcModel(pMin, pMax);
        break;
    }

    case cType_ScnRfl: {
        static const f32 SCNRFL_MIN[] = {-22.61115f, -55.770135f, -45.93067f};
        static const f32 SCNRFL_MAX[] = {81.17467f, 49.677597f, 45.93065f};

        *pMin = SCNRFL_MIN;
        *pMax = SCNRFL_MAX;
        break;
    }

    case cType_Unknown: {
        static const f32 UNKNOWN_MIN[] = {0.0f, 0.0f, 0.0f};
        static const f32 UNKNOWN_MAX[] = {0.0f, 0.0f, 0.0f};

        *pMin = UNKNOWN_MIN;
        *pMax = UNKNOWN_MAX;
        break;
    }

    default: {
        break;
    }
    }
}

void ModelEx::setVisible(bool enable) {
    if (mScnObj != NULL)
        mScnObj->SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_GATHER_SCNOBJ,
                                 !enable);
}

void ModelEx::calcWorld(nw4r::math::MTX34* pWorldMtxArray) const {
#line 440
    EGG_ASSERT(pWorldMtxArray != NULL);

    static const char* BYTE_CODE_CALC = "NodeTree";
    static const char* BYTE_CODE_MIX = "NodeMix";

    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        u32* const pMtxAttribArray = getScnMdlSimple()->GetWldMtxAttribArray();
        nw4r::g3d::ResMdl mdl = getScnMdlSimple()->GetResMdl();

        const nw4r::math::MTX34* pWorldMtx =
            getScnMdlSimple()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_WORLD);

        nw4r::g3d::CalcWorld(pWorldMtxArray, pMtxAttribArray,
                             mdl.GetResByteCode(BYTE_CODE_CALC), pWorldMtx, mdl,
                             NULL, NULL);

        if (mdl.GetResByteCode(BYTE_CODE_MIX) != NULL) {
            nw4r::g3d::CalcSkinning(pWorldMtxArray, pMtxAttribArray, mdl,
                                    mdl.GetResByteCode(BYTE_CODE_MIX));
        }

        break;
    }

    case cType_ScnMdl1Mat1Shp:
    case cType_ScnProcModel:
    case cType_ScnRfl: {
        getLocalMtx(pWorldMtxArray);
        break;
    }

    case cType_Unknown:
    default: {
        break;
    }
    }
}

void ModelEx::calcView(const nw4r::math::MTX34& rViewMtx,
                       nw4r::math::MTX34* pViewMtxArray) const {
#line 491
    EGG_ASSERT(pViewMtxArray != NULL);

    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        nw4r::g3d::CalcView(pViewMtxArray, NULL,
                            getScnMdlSimple()->GetWldMtxArray(),
                            getScnMdlSimple()->GetWldMtxAttribArray(),
                            getScnMdlSimple()->GetNumViewMtx(), &rViewMtx,
                            getScnMdlSimple()->GetResMdl(), NULL);
        break;
    }

    case cType_ScnMdl1Mat1Shp:
    case cType_ScnProcModel:
    case cType_ScnRfl: {
        mScnObj->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_VIEW, 0,
                         const_cast<nw4r::math::MTX34*>(&rViewMtx));

        nw4r::math::MTX34Copy(pViewMtxArray,
                              mScnObj->GetMtxPtr(nw4r::g3d::ScnObj::MTX_VIEW));
        break;
    }

    case cType_Unknown:
    default: {
        break;
    }
    }
}

void ModelEx::drawShapeDirectly(u32 drawFlag, bool opa, bool xlu,
                                nw4r::math::MTX34* pViewMtx) {
#line 539
    EGG_ASSERT(!(drawFlag & cDrawShape_None));

    if (!opa && !xlu) {
        return;
    }

    sDrawFlag = drawFlag;

    switch (mType) {
    case cType_ScnMdlSimple:
    case cType_ScnMdl: {
        nw4r::g3d::G3DState::Invalidate(nw4r::g3d::G3DState::INVALIDATE_SYNCGX);

        u32 drawMode = getDrawMode(drawFlag);

        if (pViewMtx == NULL) {
            if (opa) {
                getScnMdlSimple()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_OPA,
                                           0, &drawMode);
            }

            if (xlu) {
                getScnMdlSimple()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_XLU,
                                           0, &drawMode);
            }
        } else {
            nw4r::g3d::DrawResMdlReplacement* pReplacement =
                getScnMdl() == NULL ? NULL
                                    : &getScnMdl()->GetDrawResMdlReplacement();

            const u8* pByteCodeXlu =
                xlu ? getScnMdlSimple()->GetByteCode(
                          nw4r::g3d::ScnMdlSimple::BYTE_CODE_DRAW_XLU)
                    : NULL;

            const u8* pByteCodeOpa =
                opa ? getScnMdlSimple()->GetByteCode(
                          nw4r::g3d::ScnMdlSimple::BYTE_CODE_DRAW_OPA)
                    : NULL;

            nw4r::g3d::DrawResMdlDirectly(getScnMdlSimple()->GetResMdl(),
                                          pViewMtx, NULL, NULL, pByteCodeOpa,
                                          pByteCodeXlu, pReplacement, drawMode);
        }

        break;
    }

    case cType_ScnMdl1Mat1Shp: {
        nw4r::g3d::G3DState::Invalidate(nw4r::g3d::G3DState::INVALIDATE_SYNCGX);

        bool useMat = true;
        u32 ctrl = getDrawCtrl(drawFlag, &useMat);

        if (pViewMtx == NULL) {
            pViewMtx = const_cast<nw4r::math::MTX34*>(
                mScnObj->GetMtxPtr(nw4r::g3d::ScnObj::MTX_VIEW));
        }

        nw4r::g3d::G3DState::SetViewPosNrmMtxArray(pViewMtx, NULL, NULL);

        // clang-format off
        nw4r::g3d::Draw1Mat1ShpDirectly(
            useMat ? getScnMdl1Mat1Shp()->GetResMat() : nw4r::g3d::ResMat(),
            getScnMdl1Mat1Shp()->GetResShp(),
            pViewMtx,
            NULL,
            ctrl,
            NULL,
            NULL
        );
        // clang-format on

        nw4r::g3d::G3DState::SetViewPosNrmMtxArray(NULL, NULL, NULL);
        break;
    }

    case cType_ScnProcModel: {
        u32 procFlags = 0;

        if (drawFlag & cDrawFlag_IgnoreMaterial) {
            procFlags |= IScnProcModel::cDrawFlag_IgnoreMaterial;
        }
        if (drawFlag & cDrawFlag_ForceLightOff) {
            procFlags |= IScnProcModel::cDrawFlag_ForceLightOff;
        }

        if (opa) {
            getScnProcModel()->scnProcDraw(true, procFlags);
        }
        if (xlu) {
            getScnProcModel()->scnProcDraw(false, procFlags);
        }

        break;
    }

    case cType_ScnRfl: {
        if (opa) {
            getScnRfl()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_OPA, 0, NULL);
        }
        if (xlu) {
            getScnRfl()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_XLU, 0, NULL);
        }

        break;
    }

    default: {
        break;
    }
    }

    sDrawFlag = cDrawShape_None;
}

DECOMP_FORCEACTIVE(eggModelEx_cpp_3,
                  "type < cSearchType_Max");

// https://decomp.me/scratch/0xxAL
// u16 ModelEx::replaceTexture(const char* name, const int& r5, bool r6,
//                             TextureReplaceResult* result, u16 r8,
//                             bool matAccess) {}

void ModelEx::attachBoundingInfo(ModelBoundingInfo* pBV) {
#line 797
    EGG_ASSERT(mpBV == NULL);
    mpBV = pBV;
}

nw4r::g3d::ResShp ModelEx::getResShp(u16 shapeIndex) const {
#line 917
    EGG_ASSERT(shapeIndex < getNumShape());

    if (getScnMdlSimple() != NULL) {
        return getScnMdlSimple()->GetResMdl().GetResShp(shapeIndex);
    }

    if (getScnMdl1Mat1Shp() != NULL) {
        return getScnMdl1Mat1Shp()->GetResShp();
    }

    return nw4r::g3d::ResShp();
}

nw4r::g3d::ResMat ModelEx::getResMat(u16 matIndex) const {
#line 938
    EGG_ASSERT(matIndex < getNumMaterial());

    if (getScnMdlSimple() != NULL) {
        return getScnMdlSimple()->GetResMdl().GetResMat(matIndex);
    }

    if (getScnMdl1Mat1Shp() != NULL) {
        return getScnMdl1Mat1Shp()->GetResMat();
    }

    return nw4r::g3d::ResMat();
}

u32 ModelEx::getDrawMode(u32 drawFlag) {
    u32 drawMode = nw4r::g3d::RESMDL_DRAWMODE_SORT_OPA_Z |
                   nw4r::g3d::RESMDL_DRAWMODE_SORT_XLU_Z;

    if (drawFlag & cDrawFlag_ShapeOnly) {
        drawMode |= nw4r::g3d::RESMDL_DRAWMODE_IGNORE_MATERIAL |
                    nw4r::g3d::RESMDL_DRAWMODE_FORCE_LIGHTOFF;
    } else {
        if (drawFlag & cDrawFlag_IgnoreMaterial) {
            drawMode |= nw4r::g3d::RESMDL_DRAWMODE_IGNORE_MATERIAL;
        }

        if (drawFlag & cDrawFlag_ForceLightOff) {
            drawMode |= nw4r::g3d::RESMDL_DRAWMODE_FORCE_LIGHTOFF;
        }
    }

    return drawMode;
}

u32 ModelEx::getDrawCtrl(u32 drawFlag, bool* pUseMat) {
    u32 ctrl = nw4r::g3d::DRAW1MAT1SHP_CTRL_NOPPCSYNC;
    bool useMat = true;

    if (drawFlag & cDrawFlag_ShapeOnly) {
        useMat = false;
        ctrl |= nw4r::g3d::DRAW1MAT1SHP_CTRL_FORCE_LIGHTOFF;
    } else {
        if (drawFlag & cDrawFlag_IgnoreMaterial) {
            useMat = false;
        }

        if (drawFlag & cDrawFlag_ForceLightOff) {
            ctrl |= nw4r::g3d::DRAW1MAT1SHP_CTRL_FORCE_LIGHTOFF;
        }
    }

    if (pUseMat != NULL) {
        *pUseMat = useMat;
    }

    return ctrl;
}

nw4r::g3d::ResTexSrt ModelEx::getResTexSrt(u16 matIndex) {
    if (mType == cType_ScnMdl) {
        nw4r::g3d::ScnMdl::CopiedMatAccess matAccess(getScnMdl(), matIndex);
        return matAccess.GetResTexSrtEx();
    }

    if (getScnMdlSimple() != NULL) {
        return getScnMdlSimple()
            ->GetResMdl()
            .GetResMat(matIndex)
            .GetResTexSrt();
    }

    return nw4r::g3d::ResTexSrt();
}

} // namespace EGG
