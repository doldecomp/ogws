#ifndef NW4R_EF_EFFECT_H
#define NW4R_EF_EFFECT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_activitylist.h>
#include <nw4r/ef/ef_draworder.h>
#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/ef/ef_referencedobject.h>
#include <nw4r/ef/ef_res_emitter.h>
#include <nw4r/ef/ef_types.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Emitter;
class ParticleManager;
class Particle;
class EffectSystem;
class DrawOrderBase;

class Effect : public ReferencedObject {
    friend class EffectSystem;
    friend class DrawOrderBase;

private:
    enum Flag {
        FLAG_DISABLE_CALC = (1 << 0),
        FLAG_DISABLE_DRAW = (1 << 1),
        FLAG_EXIST_CALC_REMAIN = (1 << 16),
    };

    struct CallBack {
        typedef void (*PrevEmissionFunc)(Emitter* pEmitter,
                                         ParticleManager* pManager, int* pCount,
                                         u32* pFlags,
                                         f32 (*pParams)[NUM_PARAMS], u16* pLife,
                                         f32* pLifeRnd, math::MTX34* pSpace);

        typedef void (*PtclCalcFunc)(ParticleManager* pManager, ut::List* pList,
                                     Particle* pParticle);

        PrevEmissionFunc mPrevEmission; // at 0x0
        PtclCalcFunc mPrevPtclCalc;     // at 0x4
        PtclCalcFunc mPostPtclCalc;     // at 0x8
    };

public:
    EffectSystem* mManagerES;   // at 0x20
    ActivityList mActivityList; // at 0x24
    u32 mGroupID;               // at 0x40
    CallBack mCallBack;         // at 0x44

protected:
    u32 mFlags;                    // at 0x50
    math::MTX34 mRootMtx;          // at 0x54
    math::VEC3 mVelocity;          // at 0x84
    ut::List mParticleManager;     // at 0x90
    DrawOrderBase* mDrawOrderFunc; // at 0x9C

public:
    Effect();
    ~Effect();

    virtual void SendClosing(); // at 0x8
    virtual void DestroyFunc(); // at 0xC

    virtual bool Initialize(EffectSystem* pSystem, EmitterResource* pResource,
                            u16 calcRemain); // at 0x10
    virtual Emitter* CreateEmitter(ResEmitter res, u8 drawWeight,
                                   u16 calcRemain) {
        return CreateEmitter(res.ptr(), drawWeight, calcRemain);
    } // at 0x14

    virtual void Calc(bool onlyBillboard);    // at 0x18
    virtual void Draw(const DrawInfo& rInfo); // at 0x1C

    bool Closing(Emitter* pEmitter);

    Emitter* CreateEmitter(EmitterResource* pResource, u8 drawWeight,
                           u16 calcRemain);
    u32 RetireEmitter(Emitter* pEmitter);

    u32 RetireEmitterAll();
    u32 RetireParticleAll();

    u16 GetNumEmitter() const;
    Emitter* GetEmitter(u16 idx);

    u32 ForeachParticleManager(ForEachFunc pFunc, ForEachParam param,
                               bool ignoreLifeStatus);
    u32 ForeachEmitterFrom(ForEachFunc pFunc, ForEachParam param,
                           bool ignoreLifeStatus, Emitter* pEmitter);

    void ParticleManagerAdd(ParticleManager* pManager) {
        mDrawOrderFunc->Add(this, pManager);
    }
    void ParticleManagerRemove(ParticleManager* pManager) {
        mDrawOrderFunc->Remove(this, pManager);
    }

    void Modifier_SetSimpleLightType(u8 type, bool ignoreLifeStatus) {
        ForeachParticleManager(
            ParticleManager::ModifierTravFunc_SetSimpleLightType,
            static_cast<u32>(type), ignoreLifeStatus);
    }

    void Modifier_SetSimpleLightAmbient(const GXColor& rColor,
                                        bool ignoreLifeStatus) {
        ForeachParticleManager(
            ParticleManager::ModifierTravFunc_SetSimpleLightAmbient,
            reinterpret_cast<u32>(&rColor), ignoreLifeStatus);
    }

    // @bug Surely meant to be a const reference...
    void Modifier_SetScale(math::VEC2& rScale, bool ignoreLifeStatus) {
        ForeachParticleManager(ParticleManager::ModifierTravFunc_SetScale,
                               reinterpret_cast<u32>(&rScale),
                               ignoreLifeStatus);
    }

    void Modifier_SetRotate(const math::VEC3& rRot, bool ignoreLifeStatus) {
        ForeachParticleManager(ParticleManager::ModifierTravFunc_SetRotate,
                               reinterpret_cast<u32>(&rRot), ignoreLifeStatus);
    }

    bool GetFlagDisableCalc() const {
        return mFlags & FLAG_DISABLE_CALC;
    }
    void SetFlagDisableCalc(bool disable) {
        if (disable) {
            mFlags |= FLAG_DISABLE_CALC;
        } else {
            mFlags &= ~FLAG_DISABLE_CALC;
        }
    }

    bool GetFlagDisableDraw() const {
        return mFlags & FLAG_DISABLE_DRAW;
    }
    void SetFlagDisableDraw(bool disable) {
        if (disable) {
            mFlags |= FLAG_DISABLE_DRAW;
        } else {
            mFlags &= ~FLAG_DISABLE_DRAW;
        }
    }

    bool GetFlagExistCalcRemain() const {
        return mFlags & FLAG_EXIST_CALC_REMAIN;
    }
    void SetFlagExistCalcRemain(bool exist) {
        if (exist) {
            mFlags |= FLAG_EXIST_CALC_REMAIN;
        } else {
            mFlags &= ~FLAG_EXIST_CALC_REMAIN;
        }
    }

    const math::MTX34* GetRootMtx() const {
        return &mRootMtx;
    }

    void SetRootMtx(const math::MTX34& rMtx);

    const math::VEC3* GetVelocity() const {
        return &mVelocity;
    }
};

} // namespace ef
} // namespace nw4r

#endif
