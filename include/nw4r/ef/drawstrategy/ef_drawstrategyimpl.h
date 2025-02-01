#ifndef NW4R_EF_DRAW_STRATEGY_DRAW_STRATEGY_IMPL_H
#define NW4R_EF_DRAW_STRATEGY_DRAW_STRATEGY_IMPL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_drawstrategy.h>
#include <nw4r/ef/ef_types.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

#include <limits>

namespace nw4r {
namespace ef {

// Forward declarations
class Particle;
class ParticleManager;
struct TextureData;

class DrawStrategyImpl : public DrawStrategy {
public:
    typedef Particle* (*GetFirstDrawParticleFunc)(ParticleManager* pManager);
    typedef Particle* (*GetNextDrawParticleFunc)(ParticleManager* pManager,
                                                 Particle* pParticle);

    enum ParticleDrawOrder { DRAWORDER_YOUNGERS_FIRST, DRAWORDER_ELDERS_FIRST };

    struct AheadContext {
        struct {
            ParticleManager* mParticleManager;  // at 0x0
            const math::MTX34* mViewMtx;        // at 0x4
            math::MTX34 mEmitterMtx;            // at 0x8
            math::MTX34 mParticleManagerMtx;    // at 0x38
            math::MTX34 mParticleManagerMtxInv; // at 0x68
            math::VEC3 mEmitterAxisY;           // at 0x98
            math::VEC3 mEmitterCenter;          // at 0xA4
        } mCommon;                              // at 0x0

        struct {
            math::_VEC3 mWorldYAxis; // at 0x0
        } mNoDesign;                 // at 0xB0

        AheadContext(const math::MTX34& rViewMtx, ParticleManager* pManager);
    };

    typedef void (*CalcAheadFunc)(math::VEC3* pAxisY, AheadContext* pContext,
                                  Particle* pParticle);

    struct PrevTexture {
        const TextureData* data; // at 0x0
        f32 scaleS;              // at 0x4
        f32 scaleT;              // at 0x8
        f32 transS;              // at 0xC
        f32 transT;              // at 0x10
        GXTexWrapMode wrapS;     // at 0x14
        GXTexWrapMode wrapT;     // at 0x18
        math::VEC2 scale;        // at 0x1C
        f32 rotate;              // at 0x24
        math::VEC2 translate;    // at 0x28

        PrevTexture() {
            data = NULL;
            scaleS = 1.0f;
            scaleT = 1.0f;
            transS = 1.0f;
            transT = 1.0f;
            wrapS = GX_CLAMP;
            wrapT = GX_CLAMP;
            scale.x = 1.0f;
            scale.y = 1.0f;
            rotate = 0.0f;
            translate.x = 0.0f;
            translate.y = 0.0f;
        }

        bool IsEqual(const TextureData* _pData, f32 _scaleS, f32 _scaleT,
                     f32 _transS, f32 _transT, GXTexWrapMode _wrapS,
                     GXTexWrapMode _wrapT, math::VEC2 _scale, f32 _rotate,
                     math::VEC2 _translate) {

            if (data != _pData || scaleS != _scaleS || scaleT != _scaleT ||
                transS != _transS || transT != _transT || wrapS != _wrapS ||
                wrapT != _wrapT || scale.x != _scale.x || scale.y != _scale.y ||
                rotate != _rotate || translate.x != _translate.x ||
                translate.y != _translate.y) {
                return false;
            }

            return true;
        }

        void Set(const TextureData* _pData, f32 _scaleS, f32 _scaleT,
                 f32 _transS, f32 _transT, GXTexWrapMode _wrapS,
                 GXTexWrapMode _wrapT, math::VEC2 _scale, f32 _rotate,
                 math::VEC2 _translate) {

            data = _pData;
            scaleS = _scaleS;
            scaleT = _scaleT;
            transS = _transS;
            transT = _transT;
            wrapS = _wrapS;
            wrapT = _wrapT;
            scale.x = _scale.x;
            scale.y = _scale.y;
            rotate = _rotate;
            translate.x = _translate.x;
            translate.y = _translate.y;
        }
    };

public:
    DrawStrategyImpl();

    virtual GetFirstDrawParticleFunc
    GetGetFirstDrawParticleFunc(int drawOrder); // at 0x10

    virtual GetNextDrawParticleFunc
    GetGetNextDrawParticleFunc(int drawOrder); // at 0x14

protected:
    void InitTexture(const EmitterDrawSetting& rSetting);
    void InitTev(const EmitterDrawSetting& rSetting, const DrawInfo& rInfo);
    void InitColor(ParticleManager* pManager,
                   const EmitterDrawSetting& rSetting, const DrawInfo& rInfo);

    void SetupGP(Particle* pParticle, const EmitterDrawSetting& rSetting,
                 const DrawInfo& rInfo, bool first, bool xfDirty);

    static void CalcAhead_Speed(math::VEC3* pAxisY, AheadContext* pContext,
                                Particle* pParticle) {

        pParticle->GetMoveDir(pAxisY);

        if (!Normalize(pAxisY)) {
            *pAxisY = pContext->mCommon.mEmitterAxisY;
        }
    }

    static void CalcAhead_EmitterCenter(math::VEC3* pAxisY,
                                        AheadContext* pContext,
                                        Particle* pParticle) {

        math::VEC3Sub(pAxisY, &pParticle->mParameter.mPosition,
                      &pContext->mCommon.mEmitterCenter);

        if (!Normalize(pAxisY)) {
            *pAxisY = pContext->mCommon.mEmitterAxisY;
        }
    }

    static void CalcAhead_EmitterDesign(math::VEC3* pAxisY,
                                        AheadContext* pContext) {

        *pAxisY = pContext->mCommon.mEmitterAxisY;
    }

    static void CalcAhead_Particle(math::VEC3* pAxisY, AheadContext* pContext,
                                   Particle* pParticle) {

        Particle* pElder =
            GetElderDrawParticle(pContext->mCommon.mParticleManager, pParticle);

        if (pElder != NULL) {
            math::VEC3Sub(pAxisY, &pElder->mParameter.mPosition,
                          &pParticle->mParameter.mPosition);
        } else {
            math::VEC3Sub(pAxisY, &pParticle->mParameter.mPosition,
                          &pContext->mCommon.mEmitterCenter);
        }

        if (!Normalize(pAxisY)) {
            *pAxisY = pContext->mCommon.mEmitterAxisY;
        }
    }

    static void CalcAhead_NoDesign(math::VEC3* pAxisY, AheadContext* pContext) {
        *pAxisY = math::VEC3(pContext->mNoDesign.mWorldYAxis);
    }

    static void CalcAhead_ParticleBoth(math::VEC3* pAxisY,
                                       AheadContext* pContext,
                                       Particle* pParticle) {

        Particle* pElder =
            GetElderDrawParticle(pContext->mCommon.mParticleManager, pParticle);

        Particle* pYounger = GetYoungerDrawParticle(
            pContext->mCommon.mParticleManager, pParticle);

        math::VEC3 elderPos(0.0f, 0.0f, 0.0f);

        if (pElder != NULL) {
            math::VEC3Sub(&elderPos, &pElder->mParameter.mPosition,
                          &pParticle->mParameter.mPosition);

            if (!Normalize(&elderPos)) {
                elderPos = math::VEC3(0.0f, 0.0f, 0.0f);
            }
        }

        math::VEC3 youngerPos(0.0f, 0.0f, 0.0f);

        if (pYounger != NULL) {
            math::VEC3Sub(&youngerPos, &pYounger->mParameter.mPosition,
                          &pParticle->mParameter.mPosition);

            if (!Normalize(&youngerPos)) {
                youngerPos = math::VEC3(0.0f, 0.0f, 0.0f);
            }
        }

        math::VEC3Sub(pAxisY, &elderPos, &youngerPos);

        if (!Normalize(pAxisY)) {
            *pAxisY = pContext->mCommon.mEmitterAxisY;
        }
    }

    int GetNumDrawParticle(ParticleManager* pManager) {
        return pManager->mActivityList.GetNumActive();
    }

    static Particle* GetElderParticle(ParticleManager* pManager,
                                      Particle* pParticle) {

        return static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(pManager->mActivityList.mActiveList,
                                  pParticle)
                ->prevObject);
    }
    static Particle* GetYoungerParticle(ParticleManager* pManager,
                                        Particle* pParticle) {

        return static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(pManager->mActivityList.mActiveList,
                                  pParticle)
                ->nextObject);
    }

    static Particle* GetOldestParticle(ParticleManager* pManager) {
        return static_cast<Particle*>(
            pManager->mActivityList.mActiveList.headObject);
    }
    static Particle* GetYoungestParticle(ParticleManager* pManager) {
        return static_cast<Particle*>(
            pManager->mActivityList.mActiveList.tailObject);
    }

    static Particle* GetElderDrawParticle(ParticleManager* pManager,
                                          Particle* pParticle) {

        Particle* pIt = GetElderParticle(pManager, pParticle);

        while (pIt != NULL &&
               pIt->GetLifeStatus() != ReferencedObject::NW4R_EF_LS_ACTIVE) {

            pIt = GetElderParticle(pManager, pIt);
        }

        return pIt;
    }
    static Particle* GetYoungerDrawParticle(ParticleManager* pManager,
                                            Particle* pParticle) {

        Particle* pIt = GetYoungerParticle(pManager, pParticle);

        while (pIt != NULL &&
               pIt->GetLifeStatus() != ReferencedObject::NW4R_EF_LS_ACTIVE) {

            pIt = GetYoungerParticle(pManager, pIt);
        }

        return pIt;
    }

    static Particle* GetOldestDrawParticle(ParticleManager* pManager) {
        Particle* pIt = GetOldestParticle(pManager);

        while (pIt != NULL &&
               pIt->GetLifeStatus() != ReferencedObject::NW4R_EF_LS_ACTIVE) {

            pIt = GetYoungerParticle(pManager, pIt);
        }

        return pIt;
    }
    static Particle* GetYoungestDrawParticle(ParticleManager* pManager) {
        Particle* pIt = GetYoungestParticle(pManager);

        while (pIt != NULL &&
               pIt->GetLifeStatus() != ReferencedObject::NW4R_EF_LS_ACTIVE) {

            pIt = GetElderDrawParticle(pManager, pIt);
        }

        return pIt;
    }

    static bool Normalize(math::VEC3* pVec) {
        f32 sqMag = math::VEC3Dot(pVec, pVec);

        if (sqMag < std::numeric_limits<f32>::epsilon()) {
            return false;
        }

        *pVec /= math::FSqrt(sqMag);
        return true;
    }

    static const math::VEC3& GetXUnitVec() {
        return mXUnitVec;
    }
    static const math::VEC3& GetYUnitVec() {
        return mYUnitVec;
    }
    static const math::VEC3& GetZUnitVec() {
        return mZUnitVec;
    }

private:
    bool _SetupACmp(Particle* pParticle, const EmitterDrawSetting& rSetting,
                    bool first);
    bool _SetupTevReg(Particle* pParticle, const EmitterDrawSetting& rSetting,
                      bool first);
    bool _SetupTexture(Particle* pParticle, const EmitterDrawSetting& rSetting,
                       const DrawInfo& rInfo, bool first);

    static Particle*
    GetFirstDrawParticle_EldersFirst(ParticleManager* pManager);

    static Particle*
    GetFirstDrawParticle_YoungersFirst(ParticleManager* pManager);

    static Particle* GetNextDrawParticle_EldersFirst(ParticleManager* pManager,
                                                     Particle* pParticle);

    static Particle*
    GetNextDrawParticle_YoungersFirst(ParticleManager* pManager,
                                      Particle* pParticle);

protected:
    PrevTexture mPrevTexture[TEX_LAYER_MAX];            // at 0x4
    GXColor mPrevColor[COLOR_LAYER_MAX][COLOR_IDX_MAX]; // at 0x94
    int mPrevARef0;                                     // at 0xA4
    int mPrevARef1;                                     // at 0xA8
    bool mUseColor1;                                    // at 0xAC
    bool mUseColor2;                                    // at 0xAD
    u8 mNumTexmap;                                      // at 0xAE
    int mTexmapMap[TEX_LAYER_MAX];                      // at 0xB0

    static const math::VEC3 mXUnitVec;
    static const math::VEC3 mYUnitVec;
    static const math::VEC3 mZUnitVec;

    static const math::VEC3 mZeroVec;
    static const math::MTX34 mIdentityMtx;
};

} // namespace ef
} // namespace nw4r

#endif
