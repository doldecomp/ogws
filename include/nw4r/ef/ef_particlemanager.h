#ifndef NW4R_EF_PARTICLE_MANAGER_H
#define NW4R_EF_PARTICLE_MANAGER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_activitylist.h>
#include <nw4r/ef/ef_referencedobject.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Emitter;
struct EmitterResource;
class DrawStrategy;
class Particle;

class ParticleManager : public ReferencedObject {
public:
    struct ParticleModifier {
        struct SimpleLight {
            u8 mType;             // at 0x0
            ut::Color mAmbient;   // at 0x1
            ut::Color mDiffuse;   // at 0x5
            f32 mRadius;          // at 0xC
            math::VEC3 mPosition; // at 0x10
        };

        math::VEC2 mScale;  // at 0x0
        math::VEC3 mRotate; // at 0x8
        SimpleLight mLight; // at 0x14
    };

public:
    Emitter* mManagerEM;         // at 0x20
    EmitterResource* mResource;  // at 0x24
    u32 mFlag;                   // at 0x28
    DrawStrategy* mDrawStrategy; // at 0x2C
    ut::Link mDrawOrderLink;     // at 0x30
    ActivityList mActivityList;  // at 0x38
    Particle* mLastCalced;       // at 0x54
    ParticleModifier mModifier;  // at 0x58
    s8 mInheritTranslate;        // at 0x88
    u8 mWeight;                  // at 0x89

protected:
    u8 mMtxDirty; // at 0x8A

public:
    math::MTX34 mMtx; // at 0x8C

    static math::MTX34 smDrawMtxPMtoEM;
    static math::MTX34 smMtxInv;
    static s32 smMtxInvId;

public:
    virtual void SendClosing();
    virtual void DestroyFunc();
    // virtual bool Initialize(Emitter*, EmitterResource*);
    // virtual UNKTYPE CreateParticle(u16, math::VEC3, math::VEC3,
    //                                const math::MTX34*, float,
    //                                const EmitterInheritSetting*, Particle*,
    //                                u16);
    // virtual UNKTYPE Calc();
    // virtual UNKTYPE Draw(const DrawInfo&);

    math::MTX34* CalcGlobalMtx(math::MTX34*);

    bool Closing(Particle*);

    void Draw_ModifyRotate(Particle*, math::VEC3*);

    void Draw_ModifyColor(Particle*, GXColor*, GXColor*);

    f32 Draw_ModifyScaleX(Particle* /* pParticle */, f32 sx) {
        return sx * mModifier.mScale.x;
    }

    f32 Draw_ModifyScaleY(Particle* /* pParticle */, f32 sy) {
        return sy * mModifier.mScale.y;
    }
};

} // namespace ef
} // namespace nw4r

#endif
