#ifndef RP_GRAPHICS_MODEL_G3D_H
#define RP_GRAPHICS_MODEL_G3D_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <nw4r/g3d.h>

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

    virtual ~RPGrpModelG3D() override; // at 0x88

    virtual UNKTYPE VF_0x8(UNKTYPE) override;  // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) override;  // at 0xC
    virtual UNKTYPE VF_0x10(UNKTYPE) override; // at 0x10

    virtual Kind GetKind() override; // at 0x14

    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback) override; // at 0x18

    virtual void SetCallbackJointIndex(u16 idx) override; // at 0x24
    virtual u16 GetCallbackJointIndex() const override;   // at 0x28

    virtual void SetJointVisible(u32 id, bool enable) override; // at 0x2C
    virtual bool IsJointVisible() const override;               // at 0x30

    virtual void SetShapeVisible(u32 id, bool enable) override; // at 0x34
    virtual bool IsShapeVisible() const override;               // at 0x38

    virtual void GetWorldMtx(u16 idx,
                             EGG::Matrix34f* pMtx) const override; // at 0x3C
    virtual EGG::Matrix34f* GetWorldMtx(u16 idx) const override;   // at 0x40
    virtual EGG::Matrix34f* ReferWorldMtx(u16 idx) const override; // at 0x44

    virtual void GetViewMtx(u16 idx,
                            EGG::Matrix34f* pMtx) const override; // at 0x48
    virtual EGG::Matrix34f* GetViewMtx(u16 idx) const override;   // at 0x4C

    virtual const char* GetJointName(u16 idx) const override;    // at 0x54
    virtual u16 GetJointIndex(const char* pName) const override; // at 0x58

    virtual const char* GetMaterialName(u16 idx) const override;    // at 0x60
    virtual u16 GetMaterialIndex(const char* pName) const override; // at 0x64

    virtual const char* GetShapeName(u16 idx) const override;    // at 0x6C
    virtual u16 GetShapeIndex(const char* pName) const override; // at 0x70

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

    virtual void ExecCallback_CALC_VIEW(nw4r::g3d::ScnObj::Timing timing,
                                        nw4r::g3d::ScnObj* pObj, u32 param,
                                        void* pInfo) override; // at 0x14

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
};

//! @}

#endif
