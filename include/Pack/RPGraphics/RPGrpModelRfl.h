#ifndef RP_GRAPHICS_MODEL_RFL_H
#define RP_GRAPHICS_MODEL_RFL_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model implementation for RFL
 */
class RPGrpModelRfl : public RPGrpModel, public nw4r::g3d::IScnObjCallback {
public:
    RPGrpModelRfl();
    virtual ~RPGrpModelRfl() override {} // at 0x88

    virtual UNKTYPE VF_0x8(UNKTYPE) override {}  // at 0x8
    virtual UNKTYPE VF_0x10(UNKTYPE) override {} // at 0x10
    virtual UNKTYPE VF_0xC(UNKTYPE) override {}  // at 0xC

    virtual Kind GetKind() override { // at 0x14
        return Kind_RFL;
    }

    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback) override; // at 0x18

    virtual u16 ReplaceTexture(const char* pName, const RPGrpTexture& rTexture,
                               bool keepFilterWrap); // at 0x20

    virtual void SetCallbackJointIndex(u16 /* idx */) override {} // at 0x24

    virtual u16 GetCallbackJointIndex() const override { // at 0x28
        return 0;
    }

    virtual void SetJointVisible(u32 idx, bool enable) override; // at 0x2C
    virtual bool IsJointVisible(u32 idx) const override;         // at 0x30

    virtual void
    GetWorldMtx(u16 /* idx */,
                nw4r::math::MTX34* pMtx) const override { // at 0x3C

        nw4r::math::MTX34Copy(
            pMtx, GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_WORLD));
    }

    virtual const nw4r::math::MTX34*
    GetWorldMtx(u16 /* nodeIdx */) const override { // at 0x40
        return GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_WORLD);
    }

    virtual nw4r::math::MTX34*
    ReferWorldMtx(u16 /* nodeIdx */) const override { // at 0x44
        return &spCalcWorldMtxArray[0];
    }

    virtual void GetViewMtx(nw4r::math::MTX34* pMtx) const override { // at 0x4C
        GetScnMdlSimple()->GetMtx(nw4r::g3d::ScnObj::MTX_VIEW, pMtx);
    }

    virtual void GetViewMtx(u16 /* nodeIdx */,
                            nw4r::math::MTX34* pMtx) const override { // at 0x48
        GetViewMtx(pMtx);
    }

    virtual const char* GetJointName(u16 idx) const override { // at 0x54
        return GetScnMdlSimple()->GetResMdl().GetResNode(idx).GetName();
    }
    virtual u16
    GetJointIndex(const char* /* pName */) const override { // at 0x58
        return 0;
    }

    virtual const char* GetMaterialName(u16 idx) const override { // at 0x60
        return GetScnMdlSimple()->GetResMdl().GetResMat(idx).GetName();
    }
    virtual u16
    GetMaterialIndex(const char* /* pName */) const override { // at 0x64
        return 0;
    }

    virtual const char* GetShapeName(u16 idx) const override { // at 0x6C
        return GetScnMdlSimple()->GetResMdl().GetResShp(idx).GetName();
    }
    virtual u16
    GetShapeIndex(const char* /* pName */) const override { // at 0x70
        return 0;
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

    virtual void ExecCallback_CALC_WORLD(nw4r::g3d::ScnObj::Timing /* timing */,
                                         nw4r::g3d::ScnObj* /* pObj */,
                                         u32 /* param */,
                                         void* /* pInfo */) override { // at 0xC
    }

    virtual void ExecCallback_CALC_MAT(nw4r::g3d::ScnObj::Timing /* timing */,
                                       nw4r::g3d::ScnObj* /* pObj */,
                                       u32 /* param */,
                                       void* /* pInfo */) override { // at 0x10
    }

    virtual void ExecCallback_CALC_VIEW(nw4r::g3d::ScnObj::Timing /* timing */,
                                        nw4r::g3d::ScnObj* /* pObj */,
                                        u32 /* param */,
                                        void* /* pInfo */) override { // at 0x14
    }

    virtual void ExecCallback_DRAW_OPA(nw4r::g3d::ScnObj::Timing /* timing */,
                                       nw4r::g3d::ScnObj* /* pObj */,
                                       u32 /* param */,
                                       void* /* pInfo */) override { // at 0x18
    }

    virtual void ExecCallback_DRAW_XLU(nw4r::g3d::ScnObj::Timing /* timing */,
                                       nw4r::g3d::ScnObj* /* pObj */,
                                       u32 /* param */,
                                       void* /* pInfo */) override { // at 0x1C
    }

private:
    GXTexObj mLightTexObj0; // at 0x4C
    GXTexObj mLightTexObj1; // at 0x6C
    u32 unk8C;
    u16 unk90;
    u8 unk92;
    u32 unk94;
    u32 unk98;
    u32 unk9C;
};

//! @}

#endif
