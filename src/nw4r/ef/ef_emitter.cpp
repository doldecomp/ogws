#include <nw4r/ef.h>

#include <revolution/MTX.h>

namespace nw4r {
namespace ef {

Emitter::Emitter() : mActivityList(offsetof(ParticleManager, mActivityLink)) {}

Emitter::~Emitter() {}

u32 Emitter::RetireParticleAll() {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_PARTICLEMANAGER];

    u16 size = UtlistToArray(&mActivityList.mActiveList, pArray,
                             UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < size; i++) {
        ParticleManager* pManager =
            reinterpret_cast<ParticleManager*>(pArray[i]);

        num += pManager->RetireParticleAll();
    }

    return num;
}

void Emitter::SendClosing() {
    mManagerEF->Closing(this);
}

void Emitter::DestroyFunc() {
    void* pArray[NW4R_EF_MAX_EMITTER];

    if (mForm != NULL) {
        mForm = NULL;
    }

    if (mParameter.mComFlags & EmitterDesc::CMN_FLAG_SYNC_LIFE) {
        RetireParticleAll();
    }

    RetireParticleManagerAll();

    if (mParameter.mComFlags & EmitterDesc::CMN_FLAG_SYNC_LIFE) {
        u16 size =
            UtlistToArray(&mManagerEF->mActivityList.mActiveList, pArray,
                          UtlistSize(&mManagerEF->mActivityList.mActiveList));

        for (u16 i = 0; i < size; i++) {
            Emitter* pEmitter = reinterpret_cast<Emitter*>(pArray[i]);

            for (Emitter* pIt = pEmitter->mParent; pIt != NULL;
                 pIt = pIt->mParent) {

                if (pIt != this) {
                    continue;
                }

                pEmitter->RetireParticleAll();

                if (pEmitter->mLifeStatus == NW4R_EF_LS_ACTIVE) {
                    mManagerEF->RetireEmitter(pEmitter);
                }

                break;
            }
        }
    }
}

bool Emitter::Closing(ParticleManager* pManager) {
    mManagerEF->ParticleManagerRemove(pManager);
    pManager->mManagerEM->UnRef();

    mActivityList.ToClosing(pManager);
    pManager->ChangeLifeStatus(NW4R_EF_LS_CLOSING);

    return true;
}

u32 Emitter::RetireParticleManager(ParticleManager* pManager) {
    if (pManager->GetLifeStatus() != NW4R_EF_LS_ACTIVE) {
        return 0;
    }

    mActivityList.ToWait(pManager);
    pManager->Destroy();
    return 1;
}

u32 Emitter::RetireParticleManagerAll() {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_PARTICLEMANAGER];

    u16 size = UtlistToArray(&mActivityList.mActiveList, pArray,
                             UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < size; i++) {
        ParticleManager* pManager =
            reinterpret_cast<ParticleManager*>(pArray[i]);

        if (pManager->GetLifeStatus() != NW4R_EF_LS_ACTIVE) {
            continue;
        }

        num += RetireParticleManager(pManager);
    }

    return num;
}

/******************************************************************************
 * Dummy function required to match float literal order
 ******************************************************************************/
void Emitter::UpdateDatas(EmitterResource* pResource) {
    const EmitterDesc* pDesc = pResource->GetEmitterDesc();

    (void)(pDesc->lodMinEmit / 100.0f);
    (void)(pDesc->emitEmitRandom / 100.0f);
}

bool Emitter::InitializeDatas(EmitterResource* pResource, Effect* pEffect) {
    mTick = 0;
    mLifeStatus = NW4R_EF_LS_ACTIVE;
    mResource = pResource;

    EmitterDesc* pDesc = pResource->GetEmitterDesc();

    mEvalStatus = NW4R_EF_ES_WAIT;
    mCalcRemain = pDesc->emitEmitPast;
    mParameter.mComFlags = pDesc->commonFlag;
    mParameter.mEmitFlags = pDesc->emitFlag;
    mParameter.mEmitSpan = pDesc->emitLife;
    mWaitTime = pDesc->emitEmitStart;
    mEmitIntervalWait = 0;

    mParameter.mLODFar = pDesc->lodFar / 100.0f;
    mParameter.mLODNear = pDesc->lodNear / 100.0f;
    mParameter.mLODMinEmit = pDesc->lodMinEmit / 100.0f;
    mParameter.mEmitRatio = pDesc->emitEmit;
    mParameter.mEmitRandom = pDesc->emitEmitRandom / 100.0f;
    mParameter.mEmitInterval = pDesc->emitEmitInterval;
    mParameter.mEmitEmitDiv = pDesc->emitEmitDiv;
    mParameter.mEmitIntervalRandom = pDesc->emitEmitIntarvalRandom / 100.0f;
    mParameter.mEmitCount = 0.0f;

    mIsFirstEmission = true;

    mParameter.mTranslate = pDesc->translate;
    mParameter.mScale = pDesc->scale;
    mParameter.mRotate = pDesc->rotate;

    mParameter.mInherit = EmitterParameter::INHERIT_FLAG_SCALE |
                          EmitterParameter::INHERIT_FLAG_ROT;

    mParameter.mInheritTranslate = 100;

    mParameter.mVelInitVelocityRandom = pDesc->velInitVelocityRandom;
    mParameter.mVelMomentumRandom = pDesc->velMomentumRandom;
    mParameter.mVelPowerRadiationDir = pDesc->velPowerRadiationDir;
    mParameter.mVelPowerYAxis = pDesc->velPowerYAxis;
    mParameter.mVelPowerRandomDir = pDesc->velPowerRandomDir;
    mParameter.mVelPowerNormalDir = pDesc->velPowerNormalDir;
    mParameter.mVelDiffusionEmitterNormal = pDesc->velDiffusionEmitterNormal;
    mParameter.mVelPowerSpecDir = pDesc->velPowerSpecDir;
    mParameter.mVelDiffusionSpecDir = pDesc->velDiffusionSpecDir;
    mParameter.mVelSpecDir = pDesc->velSpecDir;

    (void)Resource::GetInstance(); // unused

    mRandSeed = pDesc->randomSeed;
    if (mRandSeed == 0) {
        mRandSeed = pEffect->mManagerES->mRandom.Rand();
    }

    mRandom.Srand(mRandSeed);

    for (int i = 0; i < NUM_PARAMS; i++) {
        mParameter.mParams[i] = pDesc->commonParam[i];
    }

    mMtxDirty = true;
    mpReferenceParticle = NULL;
    mForm = pEffect->mManagerES->mEmitFormBuilder->Create(pDesc->GetFormType());
    mParent = NULL;
    mManagerEF = NULL;

    return true;
}

bool Emitter::Initialize(Effect* pParent, EmitterResource* pResource,
                         u8 drawWeight) {

    (void)pResource->GetEmitterDesc(); // unused

    ReferencedObject::Initialize();

    mActivityList.Initialize();

    InitializeDatas(pResource, pParent);
    mManagerEF = pParent;

    ParticleManager* pManager =
        pParent->mManagerES->GetMemoryManager()->AllocParticleManager();

    if (pManager == NULL) {
        return false;
    }
    if (!pManager->Initialize(this, pResource)) {
        return false;
    }

    mManagerEF->Ref();
    mActivityList.ToActive(pManager);
    pManager->ChangeLifeStatus(NW4R_EF_LS_ACTIVE);

    pManager->mFlag = 0;

    if (pResource->GetEmitterDesc()->commonFlag &
        EmitterDesc::CMN_FLAG_INHERIT_PTCL_SCALE) {

        pManager->mFlag |= ParticleManager::FLAG_MTX_INHERIT_SCALE;
    }

    if (pResource->GetEmitterDesc()->commonFlag &
        EmitterDesc::CMN_FLAG_INHERIT_PTCL_ROT) {

        pManager->mFlag |= ParticleManager::FLAG_MTX_INHERIT_ROT;
    }

    pManager->mInheritTranslate =
        pResource->GetEmitterDesc()->inheritPtclTranslate;

    pManager->mWeight = drawWeight;
    mManagerEF->ParticleManagerAdd(pManager);

    return true;
}

Emitter* Emitter::CreateEmitter(EmitterResource* pResource,
                                EmitterInheritSetting* pSetting,
                                Particle* pParticle, u16 calcRemain) {

    Emitter* pEmitter =
        mManagerEF->CreateEmitter(pResource, pSetting->weight, 0);

    if (pEmitter == NULL) {
        return NULL;
    }

    pEmitter->mCalcRemain += calcRemain;
    pEmitter->mParent = this;
    pEmitter->mParent->Ref();
    pEmitter->mParameter.mInherit = 0;

    if (mResource->GetEmitterDesc()->commonFlag &
        EmitterDesc::CMN_FLAG_EMIT_INHERIT_SCALE) {

        pEmitter->mParameter.mInherit |= EmitterParameter::INHERIT_FLAG_SCALE;
    }

    if (mResource->GetEmitterDesc()->commonFlag &
        EmitterDesc::CMN_FLAG_EMIT_INHERIT_ROT) {

        pEmitter->mParameter.mInherit |= EmitterParameter::INHERIT_FLAG_ROT;
    }

    pEmitter->mParameter.mInheritTranslate =
        mResource->GetEmitterDesc()->inheritChildEmitTranslate;

    if (pParticle != NULL) {
        math::VEC3 transSave = pEmitter->mParameter.mTranslate;

        pEmitter->mParameter.mTranslate.x = 0.0f;
        pEmitter->mParameter.mTranslate.y = 0.0f;
        pEmitter->mParameter.mTranslate.z = 0.0f;
        pEmitter->SetMtxDirty();

        math::MTX34 mtx;
        math::MTX34 tmp;

        math::MTX34Identity(&mtx);
        math::MTX34RotXYZRad(&mtx, pEmitter->mParameter.mRotate.x,
                             pEmitter->mParameter.mRotate.y,
                             pEmitter->mParameter.mRotate.z);
        math::MTX34Scale(&mtx, &mtx, &pEmitter->mParameter.mScale);

        pEmitter->CalcGlobalMtx(&tmp);
        math::MTX34Inv(&tmp, &tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        pParticle->mParticleManager->CalcGlobalMtx(&tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        math::MTX34Trans(&mtx, &mtx, &pParticle->mParameter.mPosition);
        math::MTX34RotXYZRad(&tmp, pEmitter->mParameter.mRotate.x,
                             pEmitter->mParameter.mRotate.y,
                             pEmitter->mParameter.mRotate.z);
        math::MTX34Scale(&tmp, &tmp, &pEmitter->mParameter.mScale);

        math::MTX34Inv(&tmp, &tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        pEmitter->mParameter.mTranslate.x = transSave.x + mtx._03;
        pEmitter->mParameter.mTranslate.y = transSave.y + mtx._13;
        pEmitter->mParameter.mTranslate.z = transSave.z + mtx._23;
        pEmitter->SetMtxDirty();

        if (pSetting->speed != 0 || pSetting->scale != 0 ||
            pSetting->alpha != 0 || pSetting->color != 0 ||
            (pSetting->flag & EmitterInheritSetting::FLAG_INHERIT_ROT)) {

            pEmitter->mpReferenceParticle = pParticle;
            pParticle->Ref();

            pEmitter->mInheritSetting = *pSetting;
        }
    }

    return pEmitter;
}

void Emitter::CreateEmitterTmp(EmitterResource* pResource,
                               EmitterInheritSetting* pSetting,
                               Particle* pParticle, u16 calcRemain) {

    Emitter tempEmitter;

    (void)pResource->GetEmitterDesc(); // unused

    tempEmitter.InitializeDatas(pResource, mManagerEF);
    tempEmitter.mCalcRemain += calcRemain;
    tempEmitter.mManagerEF = mManagerEF;
    tempEmitter.mParent = this;

    Emitter* pEmitter = &tempEmitter;

    if ((pSetting->flag & EmitterInheritSetting::FLAG_FOLLOW_EMIT) &&
        pSetting->speed != 0) {

        math::VEC3 dir;
        math::MTX34 dirMtx;
        math::MTX34 tmpMtx;

        pParticle->mParticleManager->CalcGlobalMtx(&tmpMtx);
        tmpMtx._23 = 0.0f;
        tmpMtx._13 = 0.0f;
        tmpMtx._03 = 0.0f;

        pParticle->GetMoveDir(&dir);
        math::VEC3Transform(&dir, &tmpMtx, &dir);

        if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
            math::VEC3Normalize(&dir, &dir);

            if (pSetting->speed < 0) {
                math::VEC3Scale(&dir, &dir, -1.0f);
            }

            GetDirMtxY(&dirMtx, dir);
            math::MTX34RotXYZRad(&tmpMtx, pEmitter->mParameter.mRotate.x,
                                 pEmitter->mParameter.mRotate.y,
                                 pEmitter->mParameter.mRotate.z);

            math::MTX34Mult(&dirMtx, &dirMtx, &tmpMtx);
            MtxGetRotation(dirMtx, &pEmitter->mParameter.mRotate);
        }
    }

    math::VEC3 transSave = pEmitter->mParameter.mTranslate;

    pEmitter->mParameter.mTranslate.x = 0.0f;
    pEmitter->mParameter.mTranslate.y = 0.0f;
    pEmitter->mParameter.mTranslate.z = 0.0f;
    pEmitter->SetMtxDirty();

    math::MTX34 mtx;
    math::MTX34 tmp;

    math::MTX34Identity(&mtx);
    math::MTX34RotXYZRad(&mtx, pEmitter->mParameter.mRotate.x,
                         pEmitter->mParameter.mRotate.y,
                         pEmitter->mParameter.mRotate.z);
    math::MTX34Scale(&mtx, &mtx, &pEmitter->mParameter.mScale);

    pEmitter->CalcGlobalMtx(&tmp);
    math::MTX34Inv(&tmp, &tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    pParticle->mParticleManager->CalcGlobalMtx(&tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    math::MTX34Trans(&mtx, &mtx, &pParticle->mParameter.mPosition);
    math::MTX34RotXYZRad(&tmp, pEmitter->mParameter.mRotate.x,
                         pEmitter->mParameter.mRotate.y,
                         pEmitter->mParameter.mRotate.z);
    math::MTX34Scale(&tmp, &tmp, &pEmitter->mParameter.mScale);

    math::MTX34Inv(&tmp, &tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    pEmitter->mParameter.mTranslate.x = transSave.x + mtx._03;
    pEmitter->mParameter.mTranslate.y = transSave.y + mtx._13;
    pEmitter->mParameter.mTranslate.z = transSave.z + mtx._23;
    pEmitter->SetMtxDirty();

    tempEmitter.CalcEmitter();
    tempEmitter.CalcBillboard();

    // clang-format off
    bool inheritS = (mParameter.mComFlags & EmitterDesc::CMN_FLAG_EMIT_INHERIT_SCALE) &&
        (pResource->GetEmitterDesc()->commonFlag & EmitterDesc::CMN_FLAG_INHERIT_PTCL_SCALE);

    bool inheritR = (mParameter.mComFlags & EmitterDesc::CMN_FLAG_EMIT_INHERIT_ROT) &&
        (pResource->GetEmitterDesc()->commonFlag & EmitterDesc::CMN_FLAG_INHERIT_PTCL_ROT);
    // clang-format on

    s8 inheritT;

    const s8 parentChildT =
        mResource->GetEmitterDesc()->inheritChildEmitTranslate;

    const s8 myPtclT = pResource->GetEmitterDesc()->inheritPtclTranslate;

    if (parentChildT == 0 || myPtclT == 0) {
        inheritT = 0;
    } else if (parentChildT == 100) {
        inheritT = myPtclT;
    } else if (myPtclT == 100) {
        inheritT = parentChildT;
    } else {
        inheritT = mResource->GetEmitterDesc()->inheritChildEmitTranslate *
                   pResource->GetEmitterDesc()->inheritPtclTranslate / 100;
    }

    ParticleManager* pManager = FindParticleManager(
        pResource, inheritS, inheritR, inheritT, pSetting->weight);

    if (pManager == NULL) {
        pManager =
            mManagerEF->mManagerES->GetMemoryManager()->AllocParticleManager();

        if (pManager == NULL) {
            return;
        }
        if (!pManager->Initialize(this, pResource)) {
            return;
        }

        mActivityList.ToActive(pManager);
        pManager->ChangeLifeStatus(NW4R_EF_LS_ACTIVE);
        pManager->mFlag = 0;

        if (inheritS) {
            pManager->mFlag |= ParticleManager::FLAG_MTX_INHERIT_SCALE;
        }
        if (inheritR) {
            pManager->mFlag |= ParticleManager::FLAG_MTX_INHERIT_ROT;
        }

        pManager->mInheritTranslate = inheritT;
        pManager->mWeight = pSetting->weight;
        mManagerEF->ParticleManagerAdd(pManager);
    }

    if (pSetting->speed != 0 || pSetting->scale != 0 || pSetting->alpha != 0 ||
        pSetting->color != 0 ||
        (pSetting->flag & EmitterParameter::INHERIT_FLAG_ROT)) {

        tempEmitter.mpReferenceParticle = pParticle;
        pParticle->Ref();

        tempEmitter.mInheritSetting = *pSetting;
    } else {
        tempEmitter.mpReferenceParticle = NULL;
    }

    math::MTX34 space;
    math::MTX34 pmMtx;

    pManager->CalcGlobalMtx(&pmMtx);
    math::MTX34Inv(&pmMtx, &pmMtx);

    tempEmitter.CalcGlobalMtx(&space);
    math::MTX34Mult(&space, &pmMtx, &space);

    tempEmitter.Emission(pManager, &space);
    tempEmitter.mParent = NULL;
    tempEmitter.mManagerEF = NULL;

    if (tempEmitter.mpReferenceParticle != NULL) {
        pParticle->UnRef();
        tempEmitter.mpReferenceParticle = NULL;
    }

    if (mLifeStatus != NW4R_EF_LS_ACTIVE &&
        pManager->GetLifeStatus() == NW4R_EF_LS_ACTIVE) {

        RetireParticleManager(pManager);
    }
}

ParticleManager* Emitter::FindParticleManager(EmitterResource* pResource,
                                              bool inheritS, bool inheritR,
                                              s8 inheritT, u8 weight) {

    ParticleManager* pIt = static_cast<ParticleManager*>(
        ut::List_GetFirst(&mActivityList.mActiveList));

    // clang-format off
    for (; pIt != NULL; pIt = static_cast<ParticleManager*>(
            ut::List_GetNext(&mActivityList.mActiveList, pIt)))
    // clang-format on
    {
        if (pIt->mResource != pResource) {
            continue;
        }

        // clang-format off
        if (((pIt->mFlag & EmitterParameter::INHERIT_FLAG_SCALE) != 0) != inheritS ||
            ((pIt->mFlag & EmitterParameter::INHERIT_FLAG_ROT) != 0) != inheritR) {
            continue;
        }
        // clang-format on

        if (pIt->mInheritTranslate != inheritT) {
            continue;
        }

        if (pIt->mWeight != weight) {
            continue;
        }

        return pIt;
    }

    return NULL;
}

static f32 GetLODratio(math::VEC3& rEmitPos, math::VEC3& rCamPos, f32 cameraFar,
                       f32 cameraNear, f32 lodFar, f32 lodNear) {

    f32 Gl, Vl, Nl, Fl;
    f32 LODratio;
    f32 Fl_Nl;

    Vl = cameraFar - cameraNear;
    Gl = std::sqrtf(VEC3DistSq(&rCamPos, &rEmitPos)) - cameraNear;
    Nl = Vl * lodNear;
    Fl = Vl * lodFar;

    if (Nl > Gl) {
        LODratio = 1.0f;
    } else if (Fl < Gl) {
        LODratio = 0.0f;
    } else {
        Fl_Nl = Fl - Nl;

        if (Fl_Nl == 0.0f) {
            LODratio = 0.0f;
        } else {
            LODratio = 1.0f - (Gl - Nl) / Fl_Nl;
        }
    }

    return LODratio;
}

void Emitter::Emission(ParticleManager* pManager, const math::MTX34* pSpace) {
    if (mEmitIntervalWait > 0) {
        mEmitIntervalWait--;
        return;
    }

    mEmitIntervalWait = mParameter.mEmitInterval;

    if (mParameter.mEmitIntervalRandom != 0.0f) {
        mEmitIntervalWait += static_cast<u16>(math::FCeil(
            (mParameter.mEmitInterval * mParameter.mEmitIntervalRandom - 1.0f) *
            mRandom.RandFloat()));
    }

    if (mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_17) {
        mParameter.mEmitCount = mParameter.mEmitEmitDiv;
    } else {
        f32 count;
        if (mParameter.mEmitRandom == 0.0f) {
            count = mParameter.mEmitRatio;
        } else {
            count = mParameter.mEmitRatio +
                    mParameter.mEmitRatio * mParameter.mEmitRandom *
                        (2.0f * mRandom.RandFloat() - 1.0f);
        }

        if (mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_8) {
            EffectSystem* pSystem = mManagerEF->mManagerES;

            // clang-format off
            f32 ratio = GetLODratio(
                mParameter.mTranslate,
                pSystem->mProcessCameraPos,
                pSystem->mProcessCameraFar,
                pSystem->mProcessCameraNear,
                mParameter.mLODFar,
                mParameter.mLODNear);
            // clang-format on

            count *= mParameter.mLODMinEmit +
                     (1.0f - mParameter.mLODMinEmit) * ratio;
        }

        mParameter.mEmitCount += count;

        if (mIsFirstEmission && mParameter.mEmitRatio != 0.0f &&
            mParameter.mEmitCount < 1.0f) {

            mParameter.mEmitCount = 1.0f;
        }
    }

    if (mParameter.mEmitCount >= 1.0f) {
        (void)Resource::GetInstance(); // unused

        EmitterDesc* pDesc = mResource->GetEmitterDesc();

        if (mForm != NULL) {
            if (mManagerEF->mCallBack.mPrevEmission != NULL) {
                int count = static_cast<int>(mParameter.mEmitCount);
                u32 flags = mParameter.mEmitFlags;

                f32 params[NUM_PARAMS];
                for (int i = 0; i < NUM_PARAMS; i++) {
                    params[i] = mParameter.mParams[i];
                }

                u16 life = pDesc->ptclLife;
                f32 lifeRnd = pDesc->ptclLifeRandom / 100.0f;
                math::MTX34 newSpace = *pSpace;

                mManagerEF->mCallBack.mPrevEmission(this, pManager, &count,
                                                    &flags, &params, &life,
                                                    &lifeRnd, &newSpace);

                mForm->Emission(this, pManager, count, flags, params, life,
                                lifeRnd, &newSpace);
            } else {
                mForm->Emission(
                    this, pManager, static_cast<int>(mParameter.mEmitCount),
                    mParameter.mEmitFlags, mParameter.mParams, pDesc->ptclLife,
                    pDesc->ptclLifeRandom / 100.0f, pSpace);
            }
        }

        mParameter.mEmitCount -= static_cast<int>(mParameter.mEmitCount);
    }

    if (mIsFirstEmission) {
        mIsFirstEmission = false;
    }
}

void Emitter::CalcEmitter() {
    if (GetFlagDisableCalc()) {
        return;
    }

    if (mLifeStatus != NW4R_EF_LS_ACTIVE) {
        return;
    }

    if (mEvalStatus != NW4R_EF_ES_WAIT) {
        return;
    }

    if (mWaitTime > 0) {
        return;
    }

    if (!(mParameter.mComFlags & EmitterDesc::CMN_FLAG_MAX_LIFE)) {
        if (mTick >= mParameter.mEmitSpan) {
            mManagerEF->RetireEmitter(this);
            return;
        }
    } else if (mTick == 0xFFFFFFFF) {
        mManagerEF->RetireEmitter(this);
        return;
    }

    u32 animTime = mTick;
    u32 animSpan = (mParameter.mComFlags & EmitterDesc::CMN_FLAG_MAX_LIFE)
                       ? 0xFFFFFFFF
                       : mParameter.mEmitSpan;

    bool mtxDirty = false;

    for (u16 i = mTick == 0 ? 0 : mResource->NumEmitInitTrack();
         i < mResource->NumEmitTrack(); i++) {

        u8* pEmitTrack = mResource->GetEmitTrack(i);

#define pTrackAsHeader reinterpret_cast<AnimCurveHeader*>(pEmitTrack)

        if (pTrackAsHeader->processFlag & AnimCurveHeader::PROC_FLAG_STOP) {
            continue;
        }

        if (pTrackAsHeader->magic != NW4R_EF_MAGIC_ANIMCURVE) {
            continue;
        }

        // Load curveFlag and kindEnable
        u16 ctrl = *reinterpret_cast<u16*>(&pTrackAsHeader->curveFlag);
        u8 kind = pTrackAsHeader->kindType;

        switch (ctrl) {
        case (AC_TYPE_PARTICLE_U8 << 8 | 0b001):
        case (AC_TYPE_PARTICLE_U8 << 8 | 0b111): {
            continue;
        }

        case (AC_TYPE_PARTICLE_F32 << 8 | 0b001): {
            f32* pTarget;

            switch (kind) {
            case AC_TARGET_EMIT_SPEED_ORIG: {
                pTarget = &mParameter.mVelPowerRadiationDir;
                break;
            }

            case AC_TARGET_EMIT_SPEED_YAXIS: {
                pTarget = &mParameter.mVelPowerYAxis;
                break;
            }

            case AC_TARGET_EMIT_SPEED_RANDOM: {
                pTarget = &mParameter.mVelPowerRandomDir;
                break;
            }

            case AC_TARGET_EMIT_EMISSION: {
                pTarget = &mParameter.mEmitRatio;
                break;
            }

            default: {
                continue;
            }
            }

            AnimCurveExecuteF32(pEmitTrack, pTarget, animTime, mRandSeed,
                                animSpan);
            continue;
        }

        case (AC_TYPE_PARTICLE_F32 << 8 | 0b011): {
            switch (kind) {
            case AC_TARGET_EMIT_SPEED_NORMAL: {
                AnimCurveExecuteF32(pEmitTrack, &mParameter.mVelPowerNormalDir,
                                    animTime, mRandSeed, animSpan);
            }

            default: {
                continue;
            }
            }
        }

        case (AC_TYPE_PARTICLE_F32 << 8 | 0b111): {
            f32* pTarget;

            switch (kind) {
            case AC_TARGET_EMIT_SCALE: {
                pTarget = reinterpret_cast<f32*>(&mParameter.mScale);
                break;
            }

            case AC_TARGET_EMIT_ROTATE: {
                pTarget = reinterpret_cast<f32*>(&mParameter.mRotate);
                break;
            }

            case AC_TARGET_EMIT_TRANSLATE: {
                pTarget = reinterpret_cast<f32*>(&mParameter.mTranslate);
                break;
            }

            default: {
                continue;
            }
            }

            AnimCurveExecuteF32(pEmitTrack, pTarget, animTime, mRandSeed,
                                animSpan);

            mtxDirty = true;
            continue;
        }

        default: {
            break;
        }
        }

        switch (ctrl & 0xFF00) {
        case (AC_TYPE_PARTICLE_F32 << 8): {
            f32* pTarget;

            switch (kind) {
            case AC_TARGET_EMIT_SPEED_SPECDIR: {
                pTarget = &mParameter.mVelPowerSpecDir;
                break;
            }

            case AC_TARGET_EMIT_COMMONPARAM: {
                pTarget = mParameter.mParams;
                break;
            }

            default: {
                continue;
            }
            }

            AnimCurveExecuteF32(pEmitTrack, pTarget, animTime, mRandSeed,
                                animSpan);
            continue;
        }

        default: {
            break;
        }
        }

#undef pTrackAsHeader
    }

    if (mtxDirty) {
        SetMtxDirty();
    }
}

void Emitter::CalcParticle() {
    void* pArray[NW4R_EF_MAX_PARTICLEMANAGER];

    if (GetFlagDisableCalc()) {
        return;
    }

    u16 size = UtlistToArray(&mActivityList.mActiveList, pArray,
                             UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < size; i++) {
        ParticleManager* pManager =
            reinterpret_cast<ParticleManager*>(pArray[i]);

        pManager->Calc();
    }
}

void Emitter::CalcEmission() {
    if (GetFlagDisableCalc()) {
        return;
    }

    if (mEvalStatus != NW4R_EF_ES_WAIT) {
        return;
    }

    mEvalStatus = NW4R_EF_ES_DONE;

    if (mCalcRemain > 0) {
        mManagerEF->SetFlagExistCalcRemain(true);
    }

    if (mLifeStatus == NW4R_EF_LS_ACTIVE) {
        ParticleManager* pManager = reinterpret_cast<ParticleManager*>(
            ut::List_GetFirst(&mActivityList.mActiveList));

        math::MTX34 space;
        math::MTX34 pmMtx;

        pManager->CalcGlobalMtx(&pmMtx);
        math::MTX34Inv(&pmMtx, &pmMtx);

        CalcGlobalMtx(&space);
        math::MTX34Mult(&space, &pmMtx, &space);

        if (mWaitTime > 0) {
            mWaitTime--;
        } else {
            Emission(pManager, &space);
            mTick++;
        }
    } else {
        if (mWaitTime > 0) {
            mWaitTime--;
        } else {
            mTick++;
        }
    }
}

void Emitter::CalcBillboard() {
    if (mLifeStatus != NW4R_EF_LS_ACTIVE && mLifeStatus != NW4R_EF_LS_WAIT) {
        return;
    }

    if (!(mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_16) &&
        !(mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_15)) {
        return;
    }

    math::MTX34 glbMtx;
    mParameter.mRotate.z = 0.0f;
    mParameter.mRotate.y = 0.0f;
    mParameter.mRotate.x = 0.0f;

    mMtxDirty = true;
    CalcGlobalMtx(&glbMtx);

    math::MTX34 mtx;
    math::MTX34Mult(&mtx, &mManagerEF->mManagerES->mProcessCameraMtx, &glbMtx);

    // clang-format off
    math::MTX34 tmp = mtx;
    tmp._00 = math::FSqrt(tmp._00 * tmp._00 + tmp._10 * tmp._10 + tmp._20 * tmp._20);
    tmp._10 = tmp._20 = 0.0f;

    tmp._11 = math::FSqrt(tmp._01 * tmp._01 + tmp._11 * tmp._11 + tmp._21 * tmp._21);
    tmp._01 = tmp._21 = 0.0f;

    tmp._22 = math::FSqrt(tmp._02 * tmp._02 + tmp._12 * tmp._12 + tmp._22 * tmp._22);
    tmp._02 = tmp._12 = 0.0f;
    // clang-format on

    if ((mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_15)) {
        math::MTX34 base;
        math::MTX34RotXYZRad(&base, NW4R_MATH_PI / 2.0f, 0.0f, 0.0f);
        math::MTX34Mult(&tmp, &tmp, &base);
    }

    math::MTX34Inv(&mtx, &mtx);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    math::VEC3 vec;
    vec.x = 1.0f / mParameter.mScale.x;
    vec.y = 1.0f / mParameter.mScale.y;
    vec.z = 1.0f / mParameter.mScale.z;

    math::MTX34Scale(&mtx, &mtx, &vec);
    math::MTX34Scale(&mtx, &mParameter.mScale, &mtx);
    MtxGetRotation(mtx, &mParameter.mRotate);

    SetMtxDirty();
}

math::MTX34* Emitter::RestructMatrix(math::MTX34* pResult, math::MTX34* pOrig,
                                     bool inheritS, bool inheritR,
                                     s8 inheritT) {

    if (inheritS && inheritR && inheritT == 100) {
        *pResult = *pOrig;
        return pResult;
    }

    if (!inheritS && !inheritR && inheritT == 0) {
        math::MTX34Identity(pResult);
        return pResult;
    }

    math::MTX34Identity(pResult);

    if (inheritT != 0) {
        math::VEC3 trans;
        MtxGetTranslate(*pOrig, &trans);

        math::VEC3Scale(&trans, &trans, static_cast<f32>(inheritT) / 100.0f);
        math::MTX34Trans(pResult, pResult, &trans);
    }

    if (inheritR) {
        math::MTX34 rot;
        MtxGetRotationMtx(*pOrig, &rot);

        math::MTX34Mult(pResult, pResult, &rot);
    }

    if (inheritS) {
        math::VEC3 scale;
        MtxGetScale(*pOrig, &scale);

        math::MTX34Scale(pResult, pResult, &scale);
    }

    return pResult;
}

math::MTX34* Emitter::CalcGlobalMtx(math::MTX34* pResult) {
    if (mMtxDirty) {
        math::MTX34 tmp;

        if (!mParent) {
            math::MTX34Copy(&mMtx, mManagerEF->GetRootMtx());
        } else {
            math::MTX34 orig;
            mParent->CalcGlobalMtx(&orig);

            RestructMatrix(
                &mMtx, &orig,
                mParameter.mInherit & EmitterParameter::INHERIT_FLAG_SCALE,
                mParameter.mInherit & EmitterParameter::INHERIT_FLAG_ROT,
                mParameter.mInheritTranslate);
        }

        math::MTX34Trans(&mMtx, &mMtx, &mParameter.mTranslate);
        math::MTX34RotXYZRad(&tmp, mParameter.mRotate.x, mParameter.mRotate.y,
                             mParameter.mRotate.z);

        math::MTX34Mult(&mMtx, &mMtx, &tmp);
        math::MTX34Scale(&mMtx, &mMtx, &mParameter.mScale);

        mMtxDirty = false;
    }

    if (pResult != NULL) {
        *pResult = mMtx;
        return pResult;
    }

    return &mMtx;
}

void Emitter::SetMtxDirty() {
    mMtxDirty = true;

    ParticleManager* pManager = NULL;
    while ((pManager = reinterpret_cast<ParticleManager*>(ut::List_GetNext(
                &mActivityList.mActiveList, pManager))) != NULL) {

        pManager->SetMtxDirty();
    }

    if (mManagerEF == NULL) {
        return;
    }

    Emitter* pEmitter = NULL;
    while ((pEmitter = reinterpret_cast<Emitter*>(ut::List_GetNext(
                &mManagerEF->mActivityList.mActiveList, pEmitter))) != NULL) {

        if (pEmitter->mMtxDirty) {
            continue;
        }

        for (Emitter* pSearch = pEmitter->mParent; pSearch;
             pSearch = pSearch->mParent) {

            if (pSearch != this) {
                continue;
            }

            pEmitter->mMtxDirty = true;

            ParticleManager* pManager = NULL;
            while ((pManager = reinterpret_cast<ParticleManager*>(
                        ut::List_GetNext(&pEmitter->mActivityList.mActiveList,
                                         pManager))) != NULL) {

                pManager->SetMtxDirty();
            }
        }
    }
}

u16 Emitter::GetNumParticleManager() const {
    return mActivityList.mActiveList.numObjects;
}

ParticleManager* Emitter::GetParticleManager(u16 idx) {
    return reinterpret_cast<ParticleManager*>(
        ut::List_GetNth(&mActivityList.mActiveList, idx));
}

/******************************************************************************
 *
 * For-each implementation
 *
 ******************************************************************************/
struct ForEachContext {
    u32 calls;             // at 0x0
    ForEachFunc pFunc;     // at 0x4
    ForEachParam param;    // at 0x8
    bool ignoreLifeStatus; // at 0xC
};

u32 Emitter::ForeachEmitter(ForEachFunc pFunc, ForEachParam param,
                            bool ignoreLifeStatus) {

    return mManagerEF->ForeachEmitterFrom(pFunc, param, ignoreLifeStatus, this);
}

static void foreachParticleManagerSub(void* pObject, ForEachParam param) {
    Emitter* pEmitter = reinterpret_cast<Emitter*>(pObject);
    ForEachContext* pCtx = reinterpret_cast<ForEachContext*>(param);

    pCtx->calls += pEmitter->ForeachParticleManager(
        pCtx->pFunc, pCtx->param, pCtx->ignoreLifeStatus, false);
}

u32 Emitter::ForeachParticleManager(ForEachFunc pFunc, ForEachParam param,
                                    bool ignoreLifeStatus, bool propogate) {
    u32 calls = 0;

    NW4R_UT_LIST_FOREACH_SAFE (ParticleManager, it, mActivityList.mActiveList, {
        if (!ignoreLifeStatus && it->GetLifeStatus() != NW4R_EF_LS_ACTIVE) {
            continue;
        }

        pFunc(it, param);
        calls++;
    })

    // TODO(kiwi) I think this is doing the same for all sibling emitters?
    if (propogate) {
        ForEachContext data;
        data.calls = 0;
        data.pFunc = pFunc;
        data.param = param;
        data.ignoreLifeStatus = ignoreLifeStatus;

        ForeachEmitter(foreachParticleManagerSub,
                       reinterpret_cast<ForEachParam>(&data), true);

        calls += data.calls;
    }

    return calls;
}

} // namespace ef
} // namespace nw4r
