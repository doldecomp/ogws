#ifndef NW4R_G3D_LIGHT_H
#define NW4R_G3D_LIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

/******************************************************************************
 *
 * LightObj
 *
 ******************************************************************************/
class LightObj {
public:
    LightObj() : mFlag(0) {}
    ~LightObj() {}

    LightObj& operator=(const LightObj& rOther);

    operator GXLightObj*() {
        return &mObj;
    }
    operator const GXLightObj*() const {
        return &mObj;
    }

    void Clear();

    void InitLightColor(GXColor color);
    void InitLightPos(f32 x, f32 y, f32 z);
    void InitLightDir(f32 nx, f32 ny, f32 nz);
    void InitSpecularDir(f32 nx, f32 ny, f32 nz);
    void InitLightSpot(f32 cutoff, GXSpotFn spotFn);
    void InitLightAttnA(f32 aa, f32 ab, f32 ac);
    void InitLightDistAttn(f32 distance, f32 brightness,
                           GXDistAttnFn distAttnFn);
    void InitLightAttnK(f32 ka, f32 kb, f32 kc);
    void InitLightShininess(f32 shininess);

    void GetLightPos(math::VEC3* pPos) const;
    void GetLightDir(math::VEC3* pDir) const;

    void ApplyViewMtx(const math::MTX34& rCamera);

    void Enable() {
        mFlag |= FLAG_ENABLE_LIGHT;
    }
    void Disable() {
        mFlag &= ~FLAG_ENABLE_LIGHT;
    }

    bool IsEnable() const {
        return mFlag & FLAG_ENABLE_LIGHT;
    }

    bool IsSpotLight() const {
        return mFlag & FLAG_SPOT;
    }
    bool IsSpecularLight() const {
        return mFlag & FLAG_SPECULAR;
    }
    bool IsSpecularDir() const {
        return mFlag & FLAG_SPECULAR_DIR;
    }
    bool IsColorEnable() const {
        return mFlag & FLAG_ENABLE_COLOR;
    }
    bool IsAlphaEnable() const {
        return mFlag & FLAG_ENABLE_ALPHA;
    }
    bool IsDiffuseLight() const {
        return !IsSpotLight() && !IsSpecularLight();
    }

private:
    enum LightObjFlag {
        FLAG_SPOT = (1 << 0),
        FLAG_SPECULAR = (1 << 1),
        FLAG_ENABLE_LIGHT = (1 << 2),
        FLAG_SPECULAR_DIR = (1 << 3),
        FLAG_ENABLE_COLOR = (1 << 4),
        FLAG_ENABLE_ALPHA = (1 << 5)
    };

private:
    u32 mFlag;       // at 0x0
    GXLightObj mObj; // at 0x4
};

/******************************************************************************
 *
 * LightSet
 *
 ******************************************************************************/
struct LightSetData {
    static const int NUM_LIGHT_IDX = 8;

    s8 idxLight[NUM_LIGHT_IDX]; // at 0x0
    s8 idxAmbLight;             // at 0x8
    u8 _[0xC - 0X9];            // at 0x9
};

class LightSet {
public:
    LightSet(LightSetting* pSetting, LightSetData* pData)
        : mpSetting(pSetting), mpLightSetData(pData) {}
    ~LightSet() {}

    bool IsValid() const {
        return mpSetting != NULL && mpLightSetData != NULL;
    }

    bool SelectLightObj(u32 lightIdx, int lightObjIdx);
    bool SelectAmbLightObj(int lightObjIdx);

private:
    LightSetting* mpSetting;      // at 0x0
    LightSetData* mpLightSetData; // at 0x4
};

/******************************************************************************
 *
 * LightSetting
 *
 ******************************************************************************/
struct AmbLightObj {
    u8 r, g, b, a;
};

class LightSetting {
public:
    LightSetting(LightObj* pLightObjArray, AmbLightObj* pAmbLightObjArray,
                 u32 numLight, LightSetData* pLightSetDataArray,
                 u32 numLightSet);
    ~LightSetting() {}

    bool Import(const LightSetting& rSetting);
    void ApplyViewMtx(const math::MTX34& rCamera, u32 numLight);

    u32 GetNumLightObj() const {
        return mNumLight;
    }
    u32 GetNumLightSet() const {
        return mNumLightSet;
    }

    LightObj* GetLightObjArray() const {
        return mpLightObjArray;
    }
    AmbLightObj* GetAmbLightObjArray() const {
        return mpAmbLightObjArray;
    }

    LightSet GetLightSet(int i) {
        if (i < mNumLightSet && i > 0) {
            return LightSet(this, &mpLightSetDataArray[i]);
        }

        return LightSet(this, NULL);
    }

private:
    u16 mNumLight;                     // at 0x0
    u16 mNumLightSet;                  // at 0x2
    LightObj* mpLightObjArray;         // at 0x4
    AmbLightObj* mpAmbLightObjArray;   // at 0x8
    LightSetData* mpLightSetDataArray; // at 0xC
};

} // namespace g3d
} // namespace nw4r

#endif
