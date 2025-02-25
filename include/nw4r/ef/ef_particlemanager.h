#ifndef NW4R_EF_PARTICLE_MANAGER_H
#define NW4R_EF_PARTICLE_MANAGER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_activitylist.h>
#include <nw4r/ef/ef_referencedobject.h>
#include <nw4r/ef/ef_res_emitter.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

// Forward declarations
class DrawInfo;
class DrawStrategy;
class Emitter;
struct EmitterInheritSetting;
struct EmitterResource;
class Particle;

class ParticleManager : public ReferencedObject {
public:
    enum Flag {
        FLAG_MTX_INHERIT_SCALE = (1 << 0),
        FLAG_MTX_INHERIT_ROT = (1 << 1),
    };

    struct ParticleModifier {
        enum SimpleLightType {
            SIMPLELIGHT_OFF,
            SIMPLELIGHT_AMBIENT,
            SIMPLELIGHT_DIFFUSE
        };

        struct SimpleLight {
            u8 mType;             // at 0x0
            GXColor mAmbient;     // at 0x1
            GXColor mDiffuse;     // at 0x5
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
    bool mMtxDirty; // at 0x8A

public:
    math::MTX34 mMtx; // at 0x8C

    static math::MTX34 smDrawMtxPMtoEM;
    static math::MTX34 smMtxInv;
    static s32 smMtxInvId;

public:
    ParticleManager();
    ~ParticleManager();

    virtual void SendClosing(); // at 0x8
    virtual void DestroyFunc(); // at 0xC

    virtual bool Initialize(Emitter* pParent,
                            EmitterResource* pResource); // at 0x10

    virtual Particle* CreateParticle(u16 life, math::VEC3 pos, math::VEC3 vel,
                                     const math::MTX34* pSpace, f32 momentum,
                                     const EmitterInheritSetting* pSetting,
                                     Particle* pReferencePtcl,
                                     u16 calcRemain); // at 0x14

    virtual void Calc();                      // at 0x18
    virtual void Draw(const DrawInfo& rInfo); // at 0x1C

    bool Closing(Particle* pParticle);

    int RetireParticle(Particle* pParticle);
    int RetireParticleAll();

    math::MTX34* CalcGlobalMtx(math::MTX34* pResult);

    void BeginCalc(bool remainOnly);
    void EndCalc();

    void BeginDraw();
    void EndDraw();

    const math::MTX34* Draw_GetMtxPMtoEM() const;

    void Draw_ModifyColor(Particle* pParticle, GXColor* pColorPri,
                          GXColor* pColorSec);

    f32 Draw_ModifyScaleX(Particle* /* pParticle */, f32 sx) {
        return sx * mModifier.mScale.x;
    }
    f32 Draw_ModifyScaleY(Particle* /* pParticle */, f32 sy) {
        return sy * mModifier.mScale.y;
    }

    void Draw_ModifyRotate(Particle* /* pParticle */, math::VEC3* pRot) {
        pRot->x += mModifier.mRotate.x;
        pRot->y += mModifier.mRotate.y;
        pRot->z += mModifier.mRotate.z;
    }

    void Modifier_SetSimpleLightParameter(const EmitterDrawSetting& rSetting) {
        Modifier_SetSimpleLightParameter(
            rSetting.mLighting.mType, rSetting.mLighting.mAmbient,
            rSetting.mLighting.mDiffuse, rSetting.mLighting.mRadius,
            rSetting.mLighting.mPosition);
    }

    void Modifier_SetSimpleLightParameter(u8 type, const GXColor& rAmbient,
                                          const GXColor& rDiffuse, f32 radius,
                                          const math::VEC3& rPos) {
        mModifier.mLight.mType = type;
        mModifier.mLight.mAmbient = rAmbient;
        mModifier.mLight.mDiffuse = rDiffuse;
        mModifier.mLight.mRadius = radius;
        mModifier.mLight.mPosition = rPos;
    }

    ActivityList* GetParticleList() {
        return &mActivityList;
    }

    void ParticleToFree(Particle* pParticle) {
        mActivityList.ToFree(pParticle);
    }

    void SetMtxDirty() {
        mMtxDirty = true;
    }

    static void ModifierTravFunc_SetSimpleLightType(void* pObject,
                                                    ForEachParam param) {

        static_cast<ParticleManager*>(pObject)->mModifier.mLight.mType =
            static_cast<u8>(param);
    }

    static void ModifierTravFunc_SetSimpleLightAmbient(void* pObject,
                                                       ForEachParam param) {

        static_cast<ParticleManager*>(pObject)->mModifier.mLight.mAmbient =
            *reinterpret_cast<GXColor*>(param);
    }

    static void ModifierTravFunc_SetScale(void* pObject, ForEachParam param) {
        static_cast<ParticleManager*>(pObject)->mModifier.mScale =
            *reinterpret_cast<math::VEC2*>(param);
    }

    static void ModifierTravFunc_SetRotate(void* pObject, ForEachParam param) {
        static_cast<ParticleManager*>(pObject)->mModifier.mRotate =
            *reinterpret_cast<math::VEC3*>(param);
    }
};

} // namespace ef
} // namespace nw4r

#endif
