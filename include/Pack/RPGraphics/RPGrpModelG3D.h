#ifndef RP_GRAPHICS_MODEL_G3D_H
#define RP_GRAPHICS_MODEL_G3D_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model implementation for nw4r::g3d
 */
class RPGrpModelG3D : public RPGrpModel,
                      public nw4r::g3d::IScnObjCallback,
                      public nw4r::g3d::ICalcWorldCallback {
public:
    RPGrpModelG3D(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                  u32 bufferOption);

    RPGrpModelG3D(RPGrpHandle handle, int idx, u8 viewNo, u32 typeOption,
                  u32 bufferOption);

    RPGrpModelG3D(RPGrpHandle handle, const char* pName, u8 viewNo,
                  u32 typeOption, u32 bufferOption);

    virtual ~RPGrpModelG3D() override {} // at 0x88

    virtual UNKTYPE VF_0x8(UNKTYPE) override {}  // at 0x8
    virtual UNKTYPE VF_0x10(UNKTYPE) override {} // at 0x10
    virtual UNKTYPE VF_0xC(UNKTYPE) override {}  // at 0xC

    virtual Kind GetKind() override { // at 0x14
        return Kind_G3D;
    }

    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback) override; // at 0x18

    virtual void SetCallbackJointIndex(u16 idx) override { // at 0x24
        GetScnMdlSimple()->SetScnMdlCallbackNodeID(idx);
    }

    virtual u16 GetCallbackJointIndex() const override { // at 0x28
        return GetScnMdlSimple()->GetScnMdlCallbackNodeID();
    }

    virtual void SetJointVisible(u32 idx, bool enable) override; // at 0x2C
    virtual bool IsJointVisible(u32 idx) const override;         // at 0x30

    virtual void
    GetWorldMtx(u16 idx,
                nw4r::math::MTX34* pMtx) const override { // at 0x3C

        GetScnMdlSimple()->GetScnMtxPos(pMtx, nw4r::g3d::ScnObj::MTX_WORLD,
                                        idx);
    }

    virtual const nw4r::math::MTX34*
    GetWorldMtx(u16 nodeIdx) const override { // at 0x40
        u32 idx = GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx).GetMtxID();
        return &GetScnMdlSimple()->GetWldMtxArray()[idx];
    }

    virtual nw4r::math::MTX34*
    ReferWorldMtx(u16 nodeIdx) const override { // at 0x44
        u32 idx = GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx).GetMtxID();
        return &spCalcWorldMtxArray[idx];
    }

    virtual void GetViewMtx(nw4r::math::MTX34* pMtx) const override { // at 0x4C
        GetScnMdlSimple()->GetMtx(nw4r::g3d::ScnObj::MTX_VIEW, pMtx);
    }

    virtual void GetViewMtx(u16 nodeIdx,
                            nw4r::math::MTX34* pMtx) const override { // at 0x48
        u32 idx = GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx).GetMtxID();
        nw4r::math::MTX34Copy(pMtx, &spCalcViewMtxArray[idx]);
    }

    virtual const char* GetJointName(u16 idx) const override { // at 0x54
        return GetScnMdlSimple()->GetResMdl().GetResNode(idx).GetName();
    }
    virtual u16 GetJointIndex(const char* pName) const override { // at 0x58
        return GetScnMdlSimple()->GetResMdl().GetResNode(pName).GetID();
    }

    virtual const char* GetMaterialName(u16 idx) const override { // at 0x60
        return GetScnMdlSimple()->GetResMdl().GetResMat(idx).GetName();
    }
    virtual u16 GetMaterialIndex(const char* pName) const override { // at 0x64
        return GetScnMdlSimple()->GetResMdl().GetResMat(pName).GetID();
    }

    virtual const char* GetShapeName(u16 idx) const override { // at 0x6C
        return GetScnMdlSimple()->GetResMdl().GetResShp(idx).GetName();
    }
    virtual u16 GetShapeIndex(const char* pName) const override { // at 0x70
        return GetScnMdlSimple()->GetResMdl().GetResShp(pName).GetID();
    }

    virtual void SetShapeVisible(u32 idx, bool enable) override { // at 0x34
        GetScnMdlSimple()->GetResMdl().GetResShp(idx).SetVisible(enable);
    }

    virtual bool IsShapeVisible(u32 idx) const override { // at 0x38
        return GetScnMdlSimple()->GetResMdl().GetResShp(idx).IsVisible();
    }

    virtual void CalcBeforeDraw() override; // at 0x80

    virtual void Configure() override;    // at 0x8C
    virtual void CreateAnm() override;    // at 0x90
    virtual void InternalCalc() override; // at 0x94

    virtual void ExecCallback_CALC_WORLD(nw4r::g3d::ScnObj::Timing timing,
                                         nw4r::g3d::ScnObj* pObj, u32 param,
                                         void* pInfo) override; // at 0xC

    virtual void ExecCallback_CALC_MAT(nw4r::g3d::ScnObj::Timing timing,
                                       nw4r::g3d::ScnObj* pObj, u32 param,
                                       void* pInfo) override; // at 0x10

    virtual void ExecCallback_CALC_VIEW(nw4r::g3d::ScnObj::Timing /* timing */,
                                        nw4r::g3d::ScnObj* /* pObj */,
                                        u32 /* param */,
                                        void* /* pInfo */) override { // at 0x14
    }

    virtual void ExecCallback_DRAW_OPA(nw4r::g3d::ScnObj::Timing timing,
                                       nw4r::g3d::ScnObj* pObj, u32 param,
                                       void* pInfo) override; // at 0x18

    virtual void ExecCallback_DRAW_XLU(nw4r::g3d::ScnObj::Timing timing,
                                       nw4r::g3d::ScnObj* pObj, u32 param,
                                       void* pInfo) override; // at 0x1C

    virtual void
    ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0xC

    virtual void
    ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0x10

    virtual void
    ExecCallbackC(nw4r::math::MTX34* pMtxArray, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0x14

private:
    static s8 sJointWorldMtxInitialized;
    static nw4r::math::MTX34 sJointWorldMtx;
};

//! @}

#endif
