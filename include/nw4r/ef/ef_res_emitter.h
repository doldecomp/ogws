#ifndef NW4R_EF_RES_EMITTER_H
#define NW4R_EF_RES_EMITTER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
struct ParticleParameterDesc;

struct TevStageColor {
    u8 mA; // at 0x0
    u8 mB; // at 0x1
    u8 mC; // at 0x2
    u8 mD; // at 0x3
};

struct TevStageColorOp {
    u8 mOp;     // at 0x0
    u8 mBias;   // at 0x1
    u8 mScale;  // at 0x2
    u8 mClamp;  // at 0x3
    u8 mOutReg; // at 0x4
};

struct TevStageAlpha {
    u8 mA; // at 0x0
    u8 mB; // at 0x1
    u8 mC; // at 0x2
    u8 mD; // at 0x3
};

struct BlendMode {
    u8 mType;      // at 0x0,
    u8 mSrcFactor; // at 0x1,
    u8 mDstFactor; // at 0x2,
    u8 mOp;        // at 0x3,
};

struct ColorInput {
    u8 mRasColor;     // at 0x0
    u8 mTevColor[3];  // at 0x1
    u8 mTevKColor[4]; // at 0x4
};

struct Lighting {
    u8 mMode;             // at 0x0
    u8 mType;             // at 0x1
    GXColor mAmbient;     // at 0x2
    GXColor mDiffuse;     // at 0x6
    f32 mRadius;          // at 0xA
    math::VEC3 mPosition; // at 0xE
};

struct EmitterDrawSetting {
    enum Flag {
        FLAG_XY_SAME_SIZE = (1 << 13),
        FLAG_XY_SAME_SCALE = (1 << 14),
    };

    u16 mFlags;                     // at 0x0
    u8 mACmpComp0;                  // at 0x2
    u8 mACmpComp1;                  // at 0x3
    u8 mACmpOp;                     // at 0x4
    u8 mNumTevs;                    // at 0x5
    u8 mFlagClamp;                  // at 0x6
    u8 mIndirectTargetStage;        // at 0x7
    TevStageColor mTevColor[4];     // at 0xC
    TevStageColorOp mTevColorOp[4]; // at 0x1C
    TevStageAlpha mTevAlpha[4];     // at 0x30
    TevStageColorOp mTevAlphaOp[4]; // at 0x40
    u8 mTevKColorSel[4];            // at 0x54
    u8 mTevKAlphaSel[4];            // at 0x58
    BlendMode mBlendMode;           // at 0x5C
    ColorInput mColorInput;         // at 0x60
    u8 mZCompareFunc;               // at 0x70
    u8 mAlphaFlickType;             // at 0x71
    u16 mAlphaFlickCycle;           // at 0x72
    u8 mAlphaFlickRandom;           // at 0x74
    u8 mAlphaFlickAmplitude;        // at 0x75
    Lighting mLighting;             // at 0x76
    f32 mIndTexOffsetMtx[2][3];     // at 0x90
    s8 mIndTexScaleExp;             // at 0xA8
    s8 pivotX;                      // at 0xA9
    s8 pivotY;                      // at 0xAA
    u8 PADDING_0xAB;                // at 0xAB
    u8 ptcltype;                    // at 0xAC
    u8 typeOption;                  // at 0xAD
    u8 typeDir;                     // at 0xAE
    u8 typeAxis;                    // at 0xAF
    u8 typeOption0;                 // at 0xB0
    u8 typeOption1;                 // at 0xB1
    u8 typeOption2;                 // at 0xB2
    u8 PADDING_0xB3;                // at 0xB3
    f32 zOffset;                    // at 0xB4
};

struct EmitterDesc {
    u32 commonFlag;                 // at 0x0
    u32 emitFlag;                   // at 0x4
    u16 emitLife;                   // at 0x8
    u16 ptclLife;                   // at 0xA
    s8 ptclLifeRandom;              // at 0xC
    s8 inheritChildPtclTranslate;   // at 0xD
    s8 emitEmitIntarvalRandom;      // at 0xE
    s8 emitEmitRandom;              // at 0xF
    f32 emitEmit;                   // at 0x10
    u16 emitEmitStart;              // at 0x14
    u16 emitEmitPast;               // at 0x16
    u16 emitEmitInterval;           // at 0x18
    s8 inheritPtclTranslate;        // at 0x1A
    s8 inheritChildEmitTranslate;   // at 0x1B
    f32 commonParam[6];             // at 0x1C
    u16 emitEmitDiv;                // at 0x34
    s8 velInitVelocityRandom;       // at 0x36
    s8 velMomentumRandom;           // at 0x37
    f32 velPowerRadiationDir;       // at 0x38
    f32 velPowerYAxis;              // at 0x3C
    f32 velPowerRandomDir;          // at 0x40
    f32 velPowerNormalDir;          // at 0x44
    f32 velDiffusionEmitterNormal;  // at 0x48
    f32 velPowerSpecDir;            // at 0x4C
    f32 velDiffusionSpecDir;        // at 0x50
    math::VEC3 velSpecDir;          // at 0x54
    math::VEC3 scale;               // at 0x60
    math::VEC3 rotate;              // at 0x6C
    math::VEC3 translate;           // at 0x78
    u8 lodNear;                     // at 0x84
    u8 lodFar;                      // at 0x85
    u8 lodMinEmit;                  // at 0x86
    u8 lodAlpha;                    // at 0x87
    u32 randomSeed;                 // at 0x88
    u8 userdata[8];                 // at 0x8C
    EmitterDrawSetting drawSetting; // at 0x94
};

struct EmitterResource {
private:
    char* name;     // at 0x0
    u32 headersize; // at 0x4

public:
    // TODO: Many, many weak functions

    EmitterDesc* GetEmitterDesc() {
        return reinterpret_cast<EmitterDesc*>(reinterpret_cast<u8*>(this) +
                                              sizeof(EmitterResource));
    }
    u8* SkipEmitterDesc() {
        u8* pPtr = reinterpret_cast<u8*>(this) +
                   (sizeof(EmitterResource) + headersize);

        return pPtr;
    }

    ParticleParameterDesc* GetParticleParameterDesc() {
        u8* pPtr = SkipEmitterDesc();
        pPtr += 4; // TODO: 4???
        return reinterpret_cast<ParticleParameterDesc*>(pPtr);
    }

    EmitterDrawSetting* GetEmitterDrawSetting() {
        return &GetEmitterDesc()->drawSetting;
    }
};

class ResEmitter {
private:
    EmitterResource* mData; // at 0x0

public:
    EmitterResource* ptr() {
        return mData;
    }
};

} // namespace ef
} // namespace nw4r

#endif
