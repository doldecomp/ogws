#ifndef NW4R_G3D_SCN_RFL_H
#define NW4R_G3D_SCN_RFL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_scnobj.h>

#include <RVLFaceLib.h>

namespace nw4r {
namespace g3d {

class ScnRfl : public ScnLeaf {
public:
    typedef void (*DrawProc)(ScnRfl* pScnRfl, const RFLCharModel* pModel,
                             u32 diffMask, u32 specMask, GXColor ambColor,
                             bool opa);

public:
    static ScnRfl* Construct(MEMAllocator* pAllocator, u32* pSize,
                             RFLResolution resolution, u32 exprFlags,
                             u32 userDataSize);

    ScnRfl(MEMAllocator* pAllocator, void* pNglBuffer, void* pUserData,
           RFLResolution resolution, u32 exprFlag);

    virtual void G3dProc(u32 task, u32 param, void* pInfo); // at 0xC

    virtual ~ScnRfl() {
        ReleaseCharModel();
    } // at 0x10

    bool SetupCharModel(RFLDataSource src, u16 index, RFLMiddleDB* pMiddleDB);
    void ReleaseCharModel();

    bool SetExpression(RFLExpression expression);
    bool GetExpression(RFLExpression* pExpression);

    void SetLightSetIdx(int idx);
    s8 GetLightSetIdx() const {
        return mIdxLightSet;
    }

    void SetFogIdx(int idx);
    s8 GetFogIdx() const {
        return mIdxFog;
    }

    void GXSetZCompLoc(GXBool beforeTex) {
        mZCompLoc = beforeTex;
    }
    GXBool GXGetZCompLoc() const {
        return mZCompLoc;
    }

    bool IsCharModelReady() const {
        return mCharModelReady != FALSE;
    }

    void SetAmbientColor(GXColor color) {
        mAmbientColor = color;
    }
    GXColor GetAmbientColor() const {
        return mAmbientColor;
    }

    GXDiffuseFn GetDiffuseFunc() const {
        return mDiffuseFn;
    }
    GXAttnFn GetAttnFunc() const {
        return mAttnFn;
    }

    void SetDrawProc(DrawProc pProc) {
        mpDrawProc = pProc;
    }
    DrawProc GetDrawProc() const {
        return mpDrawProc;
    }

private:
    void CallDrawProc(bool opa);
    void LoadDrawSetting();

private:
    RFLResolution mResolution; // at 0xE8
    u32 mExpressionFlag;       // at 0xEC
    s8 mIdxLightSet;           // at 0xF0
    s8 mIdxFog;                // at 0xF1
    GXBool mZCompLoc;          // at 0xF2
    s8 mCharModelReady;        // at 0xF3
    GXColor mAmbientColor;     // at 0xF4
    GXDiffuseFn mDiffuseFn;    // at 0xF8
    GXAttnFn mAttnFn;          // at 0xFC
    void* mpNglBuffer;         // at 0x100
    RFLErrcode mRFLErrCode;    // at 0x104
    DrawProc mpDrawProc;       // at 0x108
    void* mpUserData;          // at 0x10C
    RFLCharModel mCharModel;   // at 0x110

    NW4R_G3D_RTTI_DECL_DERIVED(ScnRfl, ScnLeaf);
};

} // namespace g3d
} // namespace nw4r

#endif
