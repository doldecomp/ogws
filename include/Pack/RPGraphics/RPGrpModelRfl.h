#ifndef RP_GRAPHICS_MODEL_RFL_H
#define RP_GRAPHICS_MODEL_RFL_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <RVLFaceLib.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model implementation for RFL
 */
class RPGrpModelRfl : public RPGrpModel, public nw4r::g3d::IScnObjCallback {
public:
    enum MaterialType {
        MaterialType_0,
        MaterialType_1,
        MaterialType_2,

        MaterialType_Max
    };

public:
    static RPGrpModelRfl* Construct(RFLDataSource src, u16 index,
                                    RFLMiddleDB* pMiddleDB,
                                    RFLResolution resolution, u32 exprFlags,
                                    u8 viewNo, u32 arg6 = 0);

    RPGrpModelRfl(RFLResolution resolution, u32 exprFlags, u8 viewNo);

    virtual ~RPGrpModelRfl() override {} // at 0x88

    virtual Kind GetKind() override { // at 0x14
        return Kind_RFL;
    }

    virtual u16 ReplaceTexture(const char* pName, const RPGrpTexture& rTexture,
                               bool keepFilterWrap) override; // at 0x20

    virtual void SetCallbackJointIndex(u16 /* idx */) override {} // at 0x24

    virtual u16 GetCallbackJointIndex() const override { // at 0x28
        return 0;
    }

    virtual void
    GetWorldMtx(u16 /* idx */,
                nw4r::math::MTX34* pMtx) const override { // at 0x3C

        nw4r::math::MTX34Copy(
            pMtx, GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_LOCAL));
    }

    virtual const nw4r::math::MTX34*
    GetWorldMtx(u16 /* nodeIdx */) const override { // at 0x40
        return GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_LOCAL);
    }

    virtual nw4r::math::MTX34*
    ReferWorldMtx(u16 /* nodeIdx */) const override { // at 0x44
        return &spCalcWorldMtxArray[0];
    }

    virtual void GetViewMtx(nw4r::math::MTX34* pMtx) const override { // at 0x4C
        GetScnObj()->GetMtx(nw4r::g3d::ScnObj::MTX_VIEW, pMtx);
    }

    virtual void GetViewMtx(u16 /* nodeIdx */,
                            nw4r::math::MTX34* pMtx) const override { // at 0x48
        GetViewMtx(pMtx);
    }

    virtual const char* GetJointName(u16 idx) const override; // at 0x54

    virtual u16
    GetJointIndex(const char* /* pName */) const override { // at 0x58
        return 0;
    }

    virtual const char* GetMaterialName(u16 idx) const override; // at 0x60

    virtual u16
    GetMaterialIndex(const char* /* pName */) const override { // at 0x64
        return 0;
    }

    virtual const char* GetShapeName(u16 idx) const override; // at 0x6C

    virtual u16
    GetShapeIndex(const char* /* pName */) const override { // at 0x70
        return 0;
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

    virtual UNKTYPE VF_0x8(UNKTYPE) override {}  // at 0x8
    virtual UNKTYPE VF_0x10(UNKTYPE) override {} // at 0x10
    virtual UNKTYPE VF_0xC(UNKTYPE) override {}  // at 0xC

    void SetBrightnessColor(const GXColor& rColor) {
        mBrightnessColor = rColor;
    }

    void SetOutputAlpha(u8 alpha) {
        mOutputAlpha = alpha;
    }

    void SetMaterialType(MaterialType type) {
        mMaterialType = type;
    }

    static void SetBaseScale(f32 scale) {
        sBaseScale = scale;
    }

    static void SetMtx(const nw4r::math::MTX34& rMtx) {
        nw4r::math::MTX34Copy(&lbl_804A4608, &rMtx);
    }

private:
    enum {
        EFlag_ReverseCulling = 1 << 4,
        EFlag_5 = 1 << 5,
        EFlag_6 = 1 << 6,
        EFlag_7 = 1 << 7,
        EFlag_8 = 1 << 8,
    };

private:
    static void GetCharModelDrawProc(nw4r::g3d::ScnRfl* pScnRfl,
                                     const RFLCharModel* pModel, u32 diffMask,
                                     u32 specMask, GXColor ambColor, bool opa);

    static void DrawProc(nw4r::g3d::ScnRfl* pScnRfl, const RFLCharModel* pModel,
                         u32 diffMask, u32 specMask, GXColor ambColor,
                         bool opa);

    void DrawGX(const RFLCharModel* pModel, u32 diffMask, u32 specMask,
                GXColor ambColor, bool opa, bool arg5);

private:
    static const int LIGHT_SET_IDX = 2;
    static const int FOG_IDX = 0;

    static RFLDrawCoreSetting sDrawCoreSetting;
    static RPGrpModel* spDrawModel;
    static f32 sBaseScale;
    static nw4r::math::MTX34 lbl_804A4608;

private:
    GXTexObj mLightTexObj0;          // at 0x4C
    GXTexObj mLightTexObj1;          // at 0x6C
    GXColor mBrightnessColor;        // at 0x8C
    u16 mFlagsRfl;                   // at 0x90
    u8 mOutputAlpha;                 // at 0x92
    MaterialType mMaterialType;      // at 0x94
    RPGrpModelRfl* mpRflParent;      // at 0x98
    const RFLCharModel* mpCharModel; // at 0x9C
    RFLDataSource mDataSource;       // at 0xA0
    u16 mIndex;                      // at 0xA4
    RFLMiddleDB* mpMiddleDB;         // at 0xA8
    u32 mExprFlags;                  // at 0xAC
};

//! @}

#endif
