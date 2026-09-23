#include <Pack/RPKernel.h>

#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <cmath>
#include <cstring>

/**
 * @brief Dummy effect handle
 */
const nw4r::ef::Handle<nw4r::ef::Effect> RPSysEffect::INVALID_HANDLE;

/**
 * @brief Constructor
 *
 * @param pName Effect name
 * @param drawGroup Effect draw group
 * @param drawScene Effect draw scene
 */
RPSysEffect::RPSysEffect(const char* pName, u32 drawGroup, u32 drawScene) {
    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::strncpy(mName, pName, ARRAY_SIZE(mName));
#else
    std::strcpy(mName, pName);
#endif

    mDrawGroup = drawGroup;
    mDrawScene = drawScene;

    reset();
}

/**
 * @brief Destructor
 */
RPSysEffect::~RPSysEffect() {}

/**
 * @brief Creates this effect if it does not yet exist
 *
 * @return Success
 */
bool RPSysEffect::create() {
    if (isValid() && !isAlive()) {
        mHandle = INVALID_HANDLE;
    }

    if (!isValid()) {
        reset();

        mHandle = RP_GET_INSTANCE(RPSysEffectMgr)
                      ->createEffect(mName, mDrawGroup, mDrawScene);

        return isValid();
    }

    return false;
}

/**
 * @brief Fades away and destroys this effect
 */
void RPSysEffect::fade() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
        mHandle = INVALID_HANDLE;
    }
}

/**
 * @brief Fades away this effect without destroying the handle
 */
void RPSysEffect::followFade() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
    }
}

/**
 * @brief Destroys this effect and all of its particles
 */
void RPSysEffect::forceKill() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
        mHandle.GetPtr()->RetireParticleAll();
        mHandle = INVALID_HANDLE;
    }
}

/**
 * @brief Toggles whether this effect will update
 *
 * @param disable Whether to disable updating
 */
void RPSysEffect::setDisableCalc(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableCalc(disable);
    }
}

/**
 * @brief Toggles whether this effect will draw
 *
 * @param disable Whether to disable drawing
 */
void RPSysEffect::setDisableDraw(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableDraw(disable);
    }
}

/**
 * @brief Toggles whether this effect will update and draw
 *
 * @param disable Whether to disable both updating and drawing
 */
void RPSysEffect::setDisableCalcDraw(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableCalc(disable);
        mHandle.GetPtr()->SetFlagDisableDraw(disable);
    }
}

/**
 * @brief Sets the lifetime of all particles
 *
 * @param life Lifetime, in ticks
 */
void RPSysEffect::setLife(u16 life) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);

            if (pEmitter == NULL) {
                continue;
            }

            int numParticleManager = pEmitter->GetNumParticleManager();

            for (int j = 0; j < numParticleManager; j++) {
                // clang-format off
                RPSysParticleManager* pParticleManager =
                    static_cast<RPSysParticleManager*>(pEmitter->GetParticleManager(j));
                // clang-format on

                if (pParticleManager == NULL) {
                    continue;
                }

                pParticleManager->SetParticleLife(life);
            }
        }
    }
}

/**
 * @brief Sets the emission ratio of all emitters
 *
 * @param ratio Emission ratio
 */
void RPSysEffect::setEmitRatio(f32 ratio) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mEmitRatio = ratio;
        }
    }
}

/**
 * @brief Sets the emission interval of all emitters
 *
 * @param ratio Emission interval
 */
void RPSysEffect::setEmitInterval(u16 interval) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mEmitInterval = interval;
        }
    }
}

/**
 * @brief Sets the number of circular divisions of all emitters
 *
 * @param emitDiv Number of emitter divisions
 */
void RPSysEffect::setEmitEmitDiv(u16 emitDiv) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mEmitEmitDiv = emitDiv;
        }
    }
}

/**
 * @brief Sets the emission power in the radiation direction
 *
 * @param power Emission power
 */
void RPSysEffect::setPowerRadiationDir(f32 power) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mVelPowerRadiationDir = power;
        }
    }
}

/**
 * @brief Sets the emission power in the specified direction
 *
 * @param power Emission power
 */
void RPSysEffect::setPowerSpecDir(f32 power) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mVelPowerSpecDir = power;
        }
    }
}

/**
 * @brief Adds emission power in the specified direction
 *
 * @param add Emission power addend
 */
void RPSysEffect::setPowerSpecDirAdd(f32 add) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            nw4r::ef::EmitterResource* pResource = pEmitter->mResource;
            if (pResource == NULL) {
                continue;
            }

            nw4r::ef::EmitterDesc* pDesc = pResource->GetEmitterDesc();
            if (pDesc == NULL) {
                continue;
            }

            pEmitter->mParameter.mVelPowerSpecDir =
                pDesc->velPowerSpecDir + add;
        }
    }
}

/**
 * @brief Sets the specified direction of emission
 *
 * @param rDir Specified direction
 */
void RPSysEffect::setSpecDir(const nw4r::math::VEC3& rDir) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            nw4r::math::MTX34 localMtx;
            nw4r::math::MTX34 globalMtx;

            pEmitter->CalcGlobalMtx(&globalMtx);
            globalMtx._03 = 0.0f;
            globalMtx._13 = 0.0f;
            globalMtx._23 = 0.0f;

            if (!nw4r::math::MTX34Inv(&localMtx, &globalMtx)) {
                continue;
            }

            nw4r::math::VEC3 localDir;
            nw4r::math::VEC3Transform(&localDir, &localMtx, &rDir);

            pEmitter->mParameter.mVelSpecDir.x = //
                std::acosf(localDir.y);

            pEmitter->mParameter.mVelSpecDir.y = //
                std::atan2f(localDir.x, localDir.z);

            pEmitter->mParameter.mVelSpecDir.z = 0.0f;
        }
    }
}

/**
 * @brief Adds to the specified direction of emission
 *
 * @param rDir Specified direction addend
 */
void RPSysEffect::setSpecDirAdd(const nw4r::math::VEC3& rAdd) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            nw4r::ef::EmitterResource* pResource = pEmitter->mResource;
            if (pResource == NULL) {
                continue;
            }

            nw4r::ef::EmitterDesc* pDesc = pResource->GetEmitterDesc();
            if (pDesc == NULL) {
                continue;
            }

            nw4r::math::MTX34 rot;
            nw4r::math::VEC3 dir(0.0f, 1.0f, 0.0f);
            nw4r::math::MTX34 localMtx;
            nw4r::math::MTX34 globalMtx;

            pEmitter->CalcGlobalMtx(&globalMtx);
            globalMtx._03 = 0.0f;
            globalMtx._13 = 0.0f;
            globalMtx._23 = 0.0f;

            nw4r::math::MTX34RotXYZRad(&rot, pDesc->velSpecDir.x,
                                       pDesc->velSpecDir.y,
                                       pDesc->velSpecDir.z);

            nw4r::math::VEC3Transform(&dir, &rot, &dir);
            nw4r::math::VEC3Transform(&dir, &globalMtx, &dir);

            dir += rAdd;
            nw4r::math::VEC3Normalize(&dir, &dir);

            if (!nw4r::math::MTX34Inv(&localMtx, &globalMtx)) {
                continue;
            }

            nw4r::math::VEC3 localDir;
            nw4r::math::VEC3Transform(&localDir, &localMtx, &dir);

            pEmitter->mParameter.mVelSpecDir.x = //
                std::acosf(localDir.y);

            pEmitter->mParameter.mVelSpecDir.y = //
                std::atan2f(localDir.x, localDir.z);

            pEmitter->mParameter.mVelSpecDir.z = 0.0f;
        }
    }
}

/**
 * @brief Sets this effect's velocity
 *
 * @param rVelocity Velocity
 */
void RPSysEffect::setVelocity(const nw4r::math::VEC3& rVelocity) {
    if (isValid()) {
        mHandle.GetPtr()->SetVelocity(rVelocity);
    }
}

/**
 * @brief Sets the color of all particles
 *
 * @param r Color red component
 * @param g Color green component
 * @param b Color blue component
 * @param a Color alpha component
 */
void RPSysEffect::setColor(u8 r, u8 g, u8 b, u8 a) {
    if (isValid()) {
        GXColor color = {r, g, b, a};

        mHandle.GetPtr()->Modifier_SetSimpleLightType(
            nw4r::ef::ParticleManager::ParticleModifier::SIMPLELIGHT_AMBIENT);

        mHandle.GetPtr()->Modifier_SetSimpleLightAmbient(color);
    }
}

/**
 * @brief Sets the color of all particles
 * @details This function assumes full alpha
 *
 * @param r Color red component
 * @param g Color green component
 * @param b Color blue component
 */
void RPSysEffect::setColor(u8 r, u8 g, u8 b) {
    setColor(r, g, b, 255);
}

/**
 * @brief Sets the color alpha component of all particles
 * @details This function assumes a white color
 *
 * @param a Color alpha component
 */
void RPSysEffect::setColor(u8 a) {
    setColor(255, 255, 255, a);
}

/**
 * @brief Sets the default size of all particles
 *
 * @param rSize Default particle size
 */
void RPSysEffect::setDefaultParticleSize(const nw4r::math::VEC2& rSize) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);

            if (pEmitter == NULL) {
                continue;
            }

            int numParticleManager = pEmitter->GetNumParticleManager();

            for (int j = 0; j < numParticleManager; j++) {
                // clang-format off
                RPSysParticleManager* pParticleManager =
                    static_cast<RPSysParticleManager*>(pEmitter->GetParticleManager(j));
                // clang-format on

                if (pParticleManager == NULL) {
                    continue;
                }

                pParticleManager->SetParticleSize(rSize);
            }
        }
    }
}

/**
 * @brief Sets the scale of all particles
 *
 * @param rSize Particle scale
 */
void RPSysEffect::setParticleScale(nw4r::math::VEC2& rScale) {
    if (!isValid()) {
        return;
    }

    mHandle.GetPtr()->Modifier_SetScale(rScale);
}

/**
 * @brief Sets the default rotation of all particles
 *
 * @param rRotate Default particle rotation
 */
void RPSysEffect::setDefaultParticleRotate(const nw4r::math::VEC3& rRotate) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);

            if (pEmitter == NULL) {
                continue;
            }

            int numParticleManager = pEmitter->GetNumParticleManager();

            for (int j = 0; j < numParticleManager; j++) {
                // clang-format off
                RPSysParticleManager* pParticleManager =
                    static_cast<RPSysParticleManager*>(pEmitter->GetParticleManager(j));
                // clang-format on

                if (pParticleManager == NULL) {
                    continue;
                }

                pParticleManager->SetParticleRotate(rRotate);
            }
        }
    }
}

/**
 * @brief Sets the rotation of all particles
 *
 * @param rRotate Particle rotation
 */
void RPSysEffect::setParticleRotate(const nw4r::math::VEC3& rRotate) {
    if (isValid()) {
        mHandle.GetPtr()->Modifier_SetRotate(rRotate);
    }
}

/**
 * @brief Sets the scale of all emitters
 *
 * @param rScale Emitter scale
 */
void RPSysEffect::setLocalScale(const nw4r::math::VEC3& rScale) {
    if (isValid()) {
        int numEmitter = mHandle.GetPtr()->GetNumEmitter();

        for (int i = 0; i < numEmitter; i++) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(i);
            if (pEmitter == NULL) {
                continue;
            }

            pEmitter->mParameter.mScale = rScale;
            pEmitter->SetMtxDirty();
        }
    }
}

/**
 * @brief Sets this effect's scale without also indirectly scaling particles
 *
 * @param rScale New effect scale
 * @param pParticleScale Current particle scale (optional)
 */
void RPSysEffect::setDynamicsScale(const nw4r::math::VEC3& rScale,
                                   const nw4r::math::VEC2* pParticleScale) {
    nw4r::math::VEC2 particleScale(1.0f, 1.0f);

    if (pParticleScale != NULL) {
        particleScale = *pParticleScale;
    } else {
        f32 sx = rScale.x > 0.0f ? rScale.x : -rScale.x;
        if (sx < EGG::Mathf::epsilon()) {
            particleScale.x = 0.0f;
        } else {
            particleScale.x /= rScale.x;
        }

        f32 sy = rScale.y > 0.0f ? rScale.y : -rScale.y;
        if (sy < EGG::Mathf::epsilon()) {
            particleScale.y = 0.0f;
        } else {
            particleScale.y /= rScale.y;
        }
    }

    setScale(rScale);
    setParticleScale(particleScale);
}

/**
 * @brief Sets this effect's scale
 *
 * @param scale Effect scale (uniform)
 */
void RPSysEffect::setScale(f32 scale) {
    mFlags.setBit(EFlag_ScaleDirty);
    mScale.x = scale;
    mScale.y = scale;
    mScale.z = scale;
}

/**
 * @brief Sets this effect's scale
 *
 * @param rScale Effect scale
 */
void RPSysEffect::setScale(const nw4r::math::VEC3& rScale) {
    mFlags.setBit(EFlag_ScaleDirty);
    mScale = rScale;
}

/**
 * @brief Sets this effect's position
 *
 * @param rPosition Effect position
 */
void RPSysEffect::setPos(const nw4r::math::VEC3& rPosition) {
    mFlags.setBit(EFlag_PositionDirty);
    mPosition = rPosition;
}

/**
 * @brief Sets this effect's transformation matrix
 *
 * @param rTransform Effect transformation matrix
 */
void RPSysEffect::setMtx(const nw4r::math::MTX34& rTransform) {
    mFlags.setBit(EFlag_TransformDirty);
    mTransform = rTransform;
}

/**
 * @brief Toggles whether a particle animation is enabled
 *
 * @param idx Particle animation index
 * @param enable Whether to enable the animation
 */
void RPSysEffect::setPtclAnim(int idx, bool enable) {
    bool stop = !enable;

    if (isValid()) {
        if (mHandle.GetPtr()->GetNumEmitter() > 0) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(0);

            if (pEmitter != NULL && pEmitter->mResource != NULL) {
                // clang-format off
                if (idx < 0) {
                    for (int i = 0; i < pEmitter->mResource->NumPtclTrack(); i++) {
                        nw4r::ef::ResAnimCurve res(pEmitter->mResource->GetPtclTrack(i));
                        res.SetStop(stop);
                    }
                } else {
                    nw4r::ef::ResAnimCurve res(pEmitter->mResource->GetPtclTrack(idx));
                    res.SetStop(stop);
                }
                // clang-format on

                return;
            }
        }
    }

    nw4r::ef::ResEmitter res =
        nw4r::ef::Resource::GetInstance()->FindEmitter(mName, NULL);

    if (idx < 0) {
        for (int i = 0; i < res.ptr()->NumPtclTrack(); i++) {
            res.GetPtclTrack(i).SetStop(stop);
        }
    } else {
        res.GetPtclTrack(idx).SetStop(stop);
    }
}

/**
 * @brief Flushes this effect's configuration
 */
void RPSysEffect::update() {
    if (isValid()) {
        nw4r::math::MTX34 mtx;

        if (isAlive()) {
            if (mFlags.onBit(EFlag_TransformDirty)) {
                nw4r::math::MTX34Copy(&mtx, &mTransform);
            } else {
                nw4r::math::MTX34Identity(&mtx);
            }

            if (mFlags.onBit(EFlag_ScaleDirty)) {
                mtx._00 *= mScale.x;
                mtx._10 *= mScale.x;
                mtx._20 *= mScale.x;

                mtx._01 *= mScale.y;
                mtx._11 *= mScale.y;
                mtx._21 *= mScale.y;

                mtx._02 *= mScale.z;
                mtx._12 *= mScale.z;
                mtx._22 *= mScale.z;
            }

            if (mFlags.onBit(EFlag_PositionDirty)) {
                mtx._03 = mPosition.x;
                mtx._13 = mPosition.y;
                mtx._23 = mPosition.z;
            }

            mHandle.GetPtr()->SetRootMtx(mtx);
        } else {
            mHandle = INVALID_HANDLE;
        }
    }
}

/**
 * @brief Tests whether the specified flag in emitter userdata is set
 *
 * @param idx Userdata bitflag index
 */
bool RPSysEffect::getUserFlag(int idx) const {
    if (isValid()) {
        if (mHandle.GetPtr()->GetNumEmitter() > 0) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(0);

            if (pEmitter != NULL && pEmitter->mResource != NULL) {
                // clang-format off
                u16 flags = pEmitter->mResource->GetEmitterDesc()->userdata[2] << 8 |
                            pEmitter->mResource->GetEmitterDesc()->userdata[3];
                // clang-format on

                return 1 << idx & flags;
            }
        }
    }

    nw4r::ef::ResEmitter res =
        nw4r::ef::Resource::GetInstance()->FindEmitter(mName, NULL);

    u16 flags = res.ptr()->GetEmitterDesc()->userdata[2] << 8 |
                res.ptr()->GetEmitterDesc()->userdata[3];

    return 1 << idx & flags;
}

u8 RPSysEffect::fn_801941BC(int idx) const {
    if (isValid()) {
        if (mHandle.GetPtr()->GetNumEmitter() > 0) {
            nw4r::ef::Emitter* pEmitter = mHandle.GetPtr()->GetEmitter(0);

            if (pEmitter != NULL && pEmitter->mResource != NULL) {
                return pEmitter->mResource->GetEmitterDesc()->userdata[idx ^ 1];
            }
        }
    }

    nw4r::ef::ResEmitter res =
        nw4r::ef::Resource::GetInstance()->FindEmitter(mName, NULL);

    return res.ptr()->GetEmitterDesc()->userdata[idx ^ 1];
}

/**
 * @brief Clears this effect's configuration
 */
void RPSysEffect::reset() {
    mFlags.makeAllZero();

    mScale.x = 1.0f;
    mScale.y = 1.0f;
    mScale.z = 1.0f;

    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mPosition.z = 0.0f;

    nw4r::math::MTX34Identity(&mTransform);

    mHandle = INVALID_HANDLE;
}
