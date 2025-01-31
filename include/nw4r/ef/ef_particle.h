#ifndef NW4R_EF_PARTICLE_H
#define NW4R_EF_PARTICLE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/ef/ef_referencedobject.h>
#include <nw4r/ef/ef_res_emitter.h>
#include <nw4r/ef/ef_types.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace ef {

// Forward declarations
struct EmitterInheritSetting;
struct TextureData;

struct ParticleParameterDesc {
    GXColor mColor[COLOR_LAYER_MAX][COLOR_IDX_MAX]; // at 0x0
    math::VEC2 size;                                // at 0x10
    math::VEC2 scale;                               // at 0x18
    math::VEC3 rotate;                              // at 0x20
    math::VEC2 textureScale[TEX_LAYER_MAX];         // at 0x2C
    f32 textureRotate[TEX_LAYER_MAX];               // at 0x44
    math::VEC2 textureTranslate[TEX_LAYER_MAX];     // at 0x50
    TextureData* mTexture[TEX_LAYER_MAX];           // at 0x68
    u16 textureWrap;                                // at 0x74
    u8 textureReverse;                              // at 0x76
    u8 mACmpRef0;                                   // at 0x77
    u8 mACmpRef1;                                   // at 0x78
    u8 rotateOffsetRandom[AXIS_MAX];                // at 0x79
    f32 rotateOffset[AXIS_MAX];                     // at 0x7C
    u8 textureNames[1];                             // at 0x88
};

class ParticleParameter {
public:
    GXColor mColor[COLOR_LAYER_MAX][COLOR_IDX_MAX]; // at 0x0
    math::VEC2 mSize;                               // at 0x10
    math::VEC2 mScale;                              // at 0x18
    math::VEC3 mRotate;                             // at 0x20
    math::VEC2 mTextureScale[TEX_LAYER_MAX];        // at 0x2C
    f32 mTextureRotate[TEX_LAYER_MAX];              // at 0x44
    math::VEC2 mTextureTranslate[TEX_LAYER_MAX];    // at 0x50
    TextureData* mTexture[TEX_LAYER_MAX];           // at 0x68
    u16 mTextureWrap;                               // at 0x74
    u8 mTextureReverse;                             // at 0x76
    u8 mACmpRef0;                                   // at 0x77
    u8 mACmpRef1;                                   // at 0x78
    s8 mAlphaFlickRnd;                              // at 0x79
    u8 mRotateOffset[AXIS_MAX];                     // at 0x7A
    u8 mCollisionStatus;                            // at 0x7D
    math::VEC3 mVelocity;                           // at 0x80
    math::VEC3 mPosition;                           // at 0x8C
    math::VEC3 mPrevPosition;                       // at 0x98
    f32 mMomentum;                                  // at 0xA4

public:
    void Initialize(ParticleParameterDesc* pDesc, ParticleManager* pManager);
};

class Particle : public ReferencedObject {
    friend class ParticleManager;

public:
    ParticleParameter mParameter;      // at 0x20
    ParticleManager* mParticleManager; // at 0xC8
    math::VEC3 mPrevAxis;              // at 0xCC
    EvaluateStatus mEvalStatus;        // at 0xD8
    u16 mTick;                         // at 0xDC
    u16 mRandSeed;                     // at 0xDE
    u16 mLife;                         // at 0xE0
    u16 mCalcRemain;                   // at 0xE2

public:
    Particle();
    ~Particle();

    virtual void SendClosing(); // at 0x8
    virtual void DestroyFunc(); // at 0xC
    virtual bool Initialize(u16 life, math::VEC3 pos, math::VEC3 vel,
                            ParticleManager* pManager,
                            const math::MTX34* pSpace, float momentum,
                            const EmitterInheritSetting* pSetting,
                            Particle* pReferencePtcl); // at 0x10

    void Draw_GetColor(int layer, GXColor* pColorPri, GXColor* pColorSec);

    void GetColor(int layer, int index, GXColor* pColor) {
        pColor->r = mParameter.mColor[layer][index].r;
        pColor->g = mParameter.mColor[layer][index].g;
        pColor->b = mParameter.mColor[layer][index].b;
        pColor->a = mParameter.mColor[layer][index].a;
    }

    f32 Draw_GetSizeX() {
        f32 sx = mParameter.mSize.x * mParameter.mScale.x;
        return mParticleManager->Draw_ModifyScaleX(this, sx);
    }
    f32 Draw_GetSizeY() {
        f32 sy;

        switch (mParticleManager->mResource->GetEmitterDrawSetting()->mFlags &
                (EmitterDrawSetting::FLAG_XY_SAME_SIZE |
                 EmitterDrawSetting::FLAG_XY_SAME_SCALE)) {

        case EmitterDrawSetting::FLAG_XY_SAME_SCALE: {
            sy = mParameter.mSize.y * mParameter.mScale.x;
            break;
        }

        case EmitterDrawSetting::FLAG_XY_SAME_SIZE: {
            sy = mParameter.mSize.x * mParameter.mScale.y;
            break;
        }

        case (EmitterDrawSetting::FLAG_XY_SAME_SIZE |
              EmitterDrawSetting::FLAG_XY_SAME_SCALE): {
            sy = mParameter.mSize.x * mParameter.mScale.x;
            break;
        }

        default: {
            sy = mParameter.mSize.y * mParameter.mScale.y;
            break;
        }
        }

        return mParticleManager->Draw_ModifyScaleY(this, sy);
    }

    void Draw_GetRotate(math::VEC3* pRot) {
        *pRot = mParameter.mRotate;

        if (mParameter.mRotateOffset[AXIS_X] > 0) {
            pRot->x += NW4R_MATH_FIDX_TO_RAD(mParameter.mRotateOffset[AXIS_X]);
        }

        if (mParameter.mRotateOffset[AXIS_Y] > 0) {
            pRot->y += NW4R_MATH_FIDX_TO_RAD(mParameter.mRotateOffset[AXIS_Y]);
        }

        if (mParameter.mRotateOffset[AXIS_Z] > 0) {
            pRot->z += NW4R_MATH_FIDX_TO_RAD(mParameter.mRotateOffset[AXIS_Z]);
        }

        mParticleManager->Draw_ModifyRotate(this, pRot);
    }

    int Draw_GetTextureScaleS(int layer) const {
        int scale = 1;

        if (GetTextureWrapS(layer) == GX_MIRROR) {
            scale = 2;
        }

        u8 reverse =
            (mParameter.mTextureReverse >> (layer * NUM_OF_TEX_REVERSE) &
             TEX_REVERSE_ST);

        if (static_cast<u32>(reverse) == TEX_REVERSE_S ||
            static_cast<u32>(reverse) == TEX_REVERSE_ST) {
            scale -= scale * 2;
        }

        return scale;
    }
    int Draw_GetTextureScaleT(int layer) const {
        int scale = 1;

        if (GetTextureWrapT(layer) == GX_MIRROR) {
            scale = 2;
        }

        u8 reverse =
            (mParameter.mTextureReverse >> (layer * NUM_OF_TEX_REVERSE) &
             TEX_REVERSE_ST);

        if (static_cast<u32>(reverse) == TEX_REVERSE_T ||
            static_cast<u32>(reverse) == TEX_REVERSE_ST) {
            scale -= scale * 2;
        }

        return scale;
    }

    int Draw_GetTextureTransS(int layer) const {
        int trans = 0;

        u8 reverse =
            (mParameter.mTextureReverse >> (layer * NUM_OF_TEX_REVERSE) &
             TEX_REVERSE_ST);

        if (static_cast<u32>(reverse) == TEX_REVERSE_S ||
            static_cast<u32>(reverse) == TEX_REVERSE_ST) {
            trans = 1;
        }

        if (GetTextureWrapS(layer) == GX_MIRROR) {
            trans *= 2;
        }

        return trans;
    }
    int Draw_GetTextureTransT(int layer) const {
        int trans = 0;

        u8 reverse =
            (mParameter.mTextureReverse >> (layer * NUM_OF_TEX_REVERSE) &
             TEX_REVERSE_ST);

        if (static_cast<u32>(reverse) == TEX_REVERSE_T ||
            static_cast<u32>(reverse) == TEX_REVERSE_ST) {
            trans = 1;
        }

        if (GetTextureWrapT(layer) == GX_MIRROR) {
            trans *= 2;
        }

        return trans;
    }

    GXTexWrapMode GetTextureWrapS(int layer) const {
        // clang-format off
        return static_cast<GXTexWrapMode>(mParameter.mTextureWrap >>
                (layer * NUM_OF_TEX_WRAP_ST + 0) & TEX_WRAP_MASK);
        // clang-format on
    }
    GXTexWrapMode GetTextureWrapT(int layer) const {
        // clang-format off
        return static_cast<GXTexWrapMode>(mParameter.mTextureWrap >>
                (layer * NUM_OF_TEX_WRAP_ST + NUM_OF_TEX_WRAP_S) & TEX_WRAP_MASK);
        // clang-format on
    }

    math::VEC3& GetMoveDir(math::VEC3* pDir) {
        *pDir = mParameter.mPosition - mParameter.mPrevPosition;
        return *pDir;
    }

    math::VEC3& AddPosition(const math::VEC3* pDelta) {
        mParameter.mPosition.x += pDelta->x * mParameter.mMomentum;
        mParameter.mPosition.y += pDelta->y * mParameter.mMomentum;
        mParameter.mPosition.z += pDelta->z * mParameter.mMomentum;
        return mParameter.mPosition;
    }

private:
    enum TextureReverseFlag {
        TEX_REVERSE_S = (1 << 0),
        TEX_REVERSE_T = (1 << 1),
        TEX_REVERSE_ST = TEX_REVERSE_S | TEX_REVERSE_T,

        // 1 bit for each S/T
        NUM_OF_TEX_REVERSE = 2
    };

    enum TextureWrapFlag {
        TEX_WRAP_MASK = (1 << 0) | (1 << 1),

        // 2 bits for each S/T
        NUM_OF_TEX_WRAP_S = 2,
        NUM_OF_TEX_WRAP_T = 2,

        NUM_OF_TEX_WRAP_ST = 4
    };
};

} // namespace ef
} // namespace nw4r

#endif
