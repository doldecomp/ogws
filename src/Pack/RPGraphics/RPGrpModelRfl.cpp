#include <Pack/RPGraphics.h>

#include <RVLFaceLib.h>

#include <egg/gfxe.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

#include <cstring>

RFLDrawCoreSetting RPGrpModelRfl::sDrawCoreSetting;
f32 RPGrpModelRfl::sBaseScale = 1.0f;

// clang-format off
nw4r::math::MTX34 RPGrpModelRfl::lbl_804A4608(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f
);
// clang-format on

RPGrpModelRfl* RPGrpModelRfl::Construct(RFLDataSource src, u16 index,
                                        RFLMiddleDB* pMiddleDB,
                                        RFLResolution resolution, u32 exprFlags,
                                        u8 viewNo, u32 /* arg6 */) {

    RPGrpModelRfl* p = new RPGrpModelRfl(resolution, exprFlags, viewNo);

    p->Configure();

    if (!p->GetScnRfl()->SetupCharModel(src, index, pMiddleDB)) {
        src = RFLDataSource_Default;
        index = 0;
        pMiddleDB = NULL;

        p->GetScnRfl()->SetupCharModel(RFLDataSource_Default, 0, NULL);
    }

    p->mDataSource = src;
    p->mIndex = index;
    p->mpMiddleDB = pMiddleDB;

    // Manually fire the DrawProc callback as a way to get the char model
    p->GetScnRfl()->SetDrawProc(GetCharModelDrawProc);
    p->GetScnRfl()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_OPA, 0, NULL);

    p->GetScnRfl()->SetDrawProc(DrawProc);

    return p;
}

RPGrpModelRfl::RPGrpModelRfl(RFLResolution resolution, u32 exprFlags, u8 viewNo)
    : RPGrpModel(viewNo),
      mFlagsRfl(EFlag_5 | EFlag_6 | EFlag_7),
      mOutputAlpha(128),
      mMaterialType(MaterialType_0),
      mpRflParent(NULL),
      mpCharModel(NULL),
      mExprFlags(exprFlags) {

    u32 size;
    nw4r::g3d::ScnRfl* pScnRfl = nw4r::g3d::ScnRfl::Construct(
        spAllocator, &size, resolution, exprFlags, sizeof(RPGrpModelRfl*));

    *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData()) = this;

    mpModelEx = new EGG::ModelEx(pScnRfl);
}

void RPGrpModelRfl::Configure() {
    RPGrpModel::Configure();

    sDrawCoreSetting.txcGenNum = 3;
    sDrawCoreSetting.txcID = GX_TEXCOORD0;
    sDrawCoreSetting.texMapID = GX_TEXMAP0;
    sDrawCoreSetting.tevStageNum = 4;
    sDrawCoreSetting.tevSwapTable = GX_TEV_SWAP0;
    sDrawCoreSetting.tevKColorID = GX_KCOLOR0;
    sDrawCoreSetting.tevOutRegID = GX_TEVREG2;
    sDrawCoreSetting.posNrmMtxID = GX_PNMTX0;
    sDrawCoreSetting.reverseCulling = false;

    GetScnRfl()->SetLightSetIdx(LIGHT_SET_IDX);
    GetScnRfl()->SetFogIdx(FOG_IDX);
    GetScnRfl()->SetAmbientColor((GXColor){255, 255, 255, 255});
    mBrightnessColor = (GXColor){255, 255, 255, 255};

    InternalCalc();
}

void RPGrpModelRfl::CreateAnm() {}

u16 RPGrpModelRfl::ReplaceTexture(const char* pName,
                                  const RPGrpTexture& rTexture,
                                  bool /* keepFilterWrap */) {
    if (std::strcmp(pName, "lm_0") == 0) {
        mLightTexObj0 = rTexture.GetTexObj();
        mFlagsRfl |= 1;
    } else if (std::strcmp(pName, "lm_1") == 0) {
        mLightTexObj1 = rTexture.GetTexObj();
        mFlagsRfl |= 2;
    } else {
        return 0;
    }

    return 1;
}

void RPGrpModelRfl::InternalCalc() {
    if (!mReverseCulling) {
        nw4r::math::VEC3 scale(mScale.x * sBaseScale, mScale.y * sBaseScale,
                               mScale.z * sBaseScale);

        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(scale);
        }

        mFlagsRfl &= ~EFlag_ReverseCulling;
    } else {
        const nw4r::math::_VEC3& rMag = GEOMETRY_MAGNIFY[mReverseCulling - 1];

        nw4r::math::VEC3 scale(mScale.x * rMag.x * sBaseScale,
                               mScale.y * rMag.y * sBaseScale,
                               mScale.z * rMag.z * sBaseScale);

        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(scale);
        }

        mFlagsRfl |= EFlag_ReverseCulling;
    }

    if (GetScnObj() != NULL) {
        GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_WORLD, 0, NULL);
    }

    if (mpRecord != NULL) {
        nw4r::math::MTX34 worldMtx;
        spCalcWorldMtxArray = &worldMtx;

        GetScnRfl()->GetMtx(nw4r::g3d::ScnObj::MTX_WORLD, spCalcWorldMtxArray);
        mpRecord->Calc(this);
        GetScnRfl()->SetMtx(nw4r::g3d::ScnObj::MTX_WORLD, spCalcWorldMtxArray);

        spCalcWorldMtxArray = NULL;
    }
}

void RPGrpModelRfl::CalcBeforeDraw() {
    RPGrpModel::CalcBeforeDraw();

    if (mFlagsRfl & 0x100) {
        mpModelEx->setVisible(false);
        mFlagsRfl |= 0x200;
    } else {
        mFlagsRfl &= ~0x200;
    }
}

void RPGrpModelRfl::DrawProc(nw4r::g3d::ScnRfl* pScnRfl,
                             const RFLCharModel* pModel, u32 diffMask,
                             u32 specMask, GXColor ambColor, bool opa) {

    RPGrpModelRfl* p = *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData());
    p->DrawGX(pModel, diffMask, specMask, ambColor, opa, false);
}

void RPGrpModelRfl::GetCharModelDrawProc(nw4r::g3d::ScnRfl* pScnRfl,
                                         const RFLCharModel* pModel,
                                         u32 /* diffMask */, u32 /* specMask */,
                                         GXColor /* ambColor */,
                                         bool /* opa */) {
    RPGrpModelRfl* p = *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData());
    p->mpCharModel = pModel;
}

void RPGrpModelRfl::DrawGX(const RFLCharModel* pModel, u32 diffMask,
                           u32 specMask, GXColor ambColor, bool opa,
                           bool arg5) {

    bool bVar4 = !(mFlagsRfl & EFlag_8) || (arg5 && spDrawModel == NULL);

    bool bVar6 = !arg5 || ((mFlags & 0x2) && IsVisible());

    bool useMat =
        !(EGG::ModelEx::getDrawFlag() & EGG::ModelEx::cDrawFlag_IgnoreMaterial);

    bool bVar3 = ((unkC & 0x20) || (mFlagsRfl & 0x8)) && mDrawGroup == 1;
    bool bVar2 = !(mFlagsRfl & 0x400) || mDrawGroup == 1;

    bool bVar3_2 = opa && (mFlagsRfl & 0x40);
    bool bVar5 = mFlagsRfl & 0x80;

    if (!useMat) {
        if (bVar3) {
            RFLDrawShape(mpCharModel);
        }
        return;
    }

    bool bVar9 = bVar3 || bVar5;
    u32 diffMaskSub = diffMask;

    // Accidental bitwise AND?
    if (bVar6 & bVar9) {
        if (bVar4) {
            static const u8 TEV_STAGE_NUM[MaterialType_Max] = {4, 4, 3};
            sDrawCoreSetting.tevStageNum = TEV_STAGE_NUM[mMaterialType];
            spDrawModel = this;
            sDrawCoreSetting.reverseCulling = mFlagsRfl & EFlag_ReverseCulling;

            RFLLoadMaterialSetting(&sDrawCoreSetting);
            RFLLoadVertexSetting(&sDrawCoreSetting);

            if (mMaterialType == MaterialType_1) {
                ambColor = (GXColor){0, 0, 0, 255};
            }

            diffMaskSub = diffMask;

            if (!(mFlagsRfl & EFlag_5)) {
                diffMaskSub = 0;
                ambColor.a = 255;
            }

            diffMask = 0;

            GXSetNumChans(1);

            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, (mFlagsRfl & EFlag_5) ? GX_TRUE : GX_FALSE,
                          GX_SRC_REG, GX_SRC_REG,
                          static_cast<GXLightID>(diffMaskSub), GX_DF_CLAMP,
                          GX_AF_SPOT);
            GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG,
                          GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

            GXSetChanAmbColor(GX_COLOR0A0, ambColor);
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){255, 255, 255, 255});

            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

            GXLoadTexObj(&mLightTexObj0, GX_TEXMAP1);
            GXLoadTexObj(&mLightTexObj1, GX_TEXMAP2);

            GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                              GX_TRUE, GX_PTTEXMTX0);
        }

        nw4r::math::MTX34 viewMtx;
        GetScnRfl()->GetMtx(nw4r::g3d::ScnObj::MTX_VIEW, &viewMtx);
        viewMtx._03 = viewMtx._13 = viewMtx._23 = 0.0f;

        GXLoadTexMtxImm(viewMtx, GX_TEXMTX0, GX_MTX_3x4);

        nw4r::math::MTX34 trans, scale;
        PSMTXScale(scale, 0.5f, -0.5f, 0.0f);
        PSMTXTrans(trans, 0.5f, 0.5f, 1.0f);

        nw4r::math::MTX34 postMtx;
        nw4r::math::MTX34Mult(&postMtx, &trans, &scale);
        GXLoadTexMtxImm(postMtx, GX_PTTEXMTX0, GX_MTX_3x4);

        GXTevStageID stage = GX_TEVSTAGE1;

        if (bVar4) {
            GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN,
                                  GX_CH_BLUE, GX_CH_ALPHA);

            GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_RED, GX_CH_RED,
                                  GX_CH_ALPHA);

            GXSetTevDirect(GX_TEVSTAGE0);

            switch (mMaterialType) {
            case MaterialType_0: {
            case MaterialType_1:
                GXSetTevDirect(GX_TEVSTAGE1);
                GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1,
                              GX_COLOR0A0);
                GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC,
                                GX_CC_RASA, GX_CC_RASC);
                GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A2);
                GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE2);
                GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_CPREV,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE3);
                GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD1, GX_TEXMAP2,
                              GX_COLOR0A0);
                GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_TEXC,
                                GX_CC_RASA, GX_CC_CPREV);
                GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                stage = GX_TEVSTAGE3;
                break;
            }

            case MaterialType_2: {
                GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K2);
                GXSetTevKColor(GX_KCOLOR2, mBrightnessColor);

                GXSetTevDirect(GX_TEVSTAGE1);
                GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO,
                                GX_CC_ZERO, GX_CC_KONST);
                GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A2);
                GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE2);
                GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO,
                                GX_CC_ZERO, GX_CC_CPREV);
                GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                stage = GX_TEVSTAGE2;
                break;
            }

            default: {
                break;
            }
            }
        }

        if (bVar3) {
            if (bVar4) {
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_NEVER, 0);
                GXSetTevKAlphaSel(stage, GX_TEV_KASEL_K3_A);
                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_KONST);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                               GX_LO_COPY);
            }

            GXColor tevColor = (GXColor){0, 0, 0, mOutputAlpha};
            GXSetTevColor(GX_TEVREG2, tevColor);
            RFLDrawOpaCore(mpCharModel, &sDrawCoreSetting);
        }

        if (bVar5) {
            if (bVar4) {
                GXSetZCompLoc(GX_FALSE);

                if (!bVar2) {
                    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_NEVER, 0);
                } else {
                    GXSetAlphaCompare(GX_GREATER, 128, GX_AOP_OR, GX_NEVER, 0);
                }

                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_APREV);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                               GX_LO_COPY);
            }

            RFLDrawXluCore(mpCharModel, &sDrawCoreSetting);
        }
    }

    if (mpRflParent != NULL) {
        mpRflParent->DrawGX(pModel, diffMask, specMask, ambColor, opa, true);
    }

    if (spDrawModel == this) {
        spDrawModel = NULL;
    }
}

const char* RPGrpModelRfl::GetJointName(u16 /* idx */) const {
    static const char JOINT_NAME[] = "dummy";
    return JOINT_NAME;
}

const char* RPGrpModelRfl::GetMaterialName(u16 /* idx */) const {
    static const char MATERIAL_NAME[] = "dummy";
    return MATERIAL_NAME;
}

const char* RPGrpModelRfl::GetShapeName(u16 /* idx */) const {
    static const char SHAPE_NAME[] = "dummy";
    return SHAPE_NAME;
}
