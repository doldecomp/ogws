#include <nw4r/ef.h>

#include <revolution/MTX.h>

namespace nw4r {
namespace ef {

struct ForeachData {
    u32 count;
    void (*func)(void*, u32);
    u32 param;
    bool all;
};

Emitter::Emitter() : mActivityList(offsetof(ParticleManager, mActivityLink)) {}

Emitter::~Emitter() {}

u32 Emitter::RetireParticleAll() {
    u32 count = 0;
    void* array[NW4R_EF_MAX_PARTICLEMANAGER];

    // "UtlistSize(&mActivityList.mActiveList) < NW4R_EF_MAX_PARTICLEMANAGER"
    u16 listsize = UtlistToArray(&mActivityList.mActiveList, array,
                                 UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < listsize; ++i) {
        ParticleManager* pm = reinterpret_cast<ParticleManager*>(array[i]);
        count += pm->RetireParticleAll();
    }

    return count;
}

void Emitter::SendClosing() {
    mManagerEF->Closing(this);
}

void Emitter::DestroyFunc() {
    void* array[NW4R_EF_MAX_EMITTER];

    if (mForm) {
        mForm = NULL;
    }

    // TODO magic constant
    if (mParameter.mComFlags & 1) {
        RetireParticleAll();
    }

    RetireParticleManagerAll();

    if (!(mParameter.mComFlags & 1)) {
        return;
    }

    // "UtlistSize(&mManagerEF->mActivityList.mActiveList) <
    // NW4R_EF_MAX_EMITTER"
    u16 listsize =
        UtlistToArray(&mManagerEF->mActivityList.mActiveList, array,
                      UtlistSize(&mManagerEF->mActivityList.mActiveList));

    for (u16 i = 0; i < listsize; ++i) {
        Emitter* em = reinterpret_cast<Emitter*>(array[i]);

        for (Emitter* p = em->mParent; p; p = p->mParent) {
            if (p != this) {
                continue;
            }

            em->RetireParticleAll();
            if (em->mLifeStatus == NW4R_EF_LS_ACTIVE) {
                mManagerEF->RetireEmitter(em);
            }

            break;
        }
    }
}

bool Emitter::Closing(ParticleManager* target) {
    // "target(=%p) is not a valid pointer"
    mManagerEF->ParticleManagerRemove(target);
    target->mManagerEM->UnRef();
    mActivityList.ToClosing(target);
    target->ChangeLifeStatus(NW4R_EF_LS_CLOSING);
    return true;
}

u32 Emitter::RetireParticleManager(ParticleManager* target) {
    // "target(=%p) is not a valid pointer"
    if (target->GetLifeStatus() != NW4R_EF_LS_ACTIVE) {
        return 0;
    }

    mActivityList.ToWait(target);
    target->Destroy();
    return 1;
}

u32 Emitter::RetireParticleManagerAll() {
    u32 count = 0;
    void* array[NW4R_EF_MAX_PARTICLEMANAGER];

    // "UtlistSize(&mActivityList.mActiveList) < NW4R_EF_MAX_PARTICLEMANAGER"
    u16 listsize = UtlistToArray(&mActivityList.mActiveList, array,
                                 UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < listsize; ++i) {
        ParticleManager* pm = reinterpret_cast<ParticleManager*>(array[i]);
        if (pm->GetLifeStatus() != NW4R_EF_LS_ACTIVE) {
            continue;
        }

        count += RetireParticleManager(pm);
    }

    return count;
}

// Not much is known about this function, as there's no definition for it
// Sample code is required to match the float order
void Emitter::UpdateDatas(EmitterResource* eh) {
    EmitterDesc* ed = eh->GetEmitterDesc();

    mParameter.mLODMinEmit = static_cast<f32>(ed->lodMinEmit) / 100.0f;
    mParameter.mEmitRandom = static_cast<f32>(ed->emitEmitRandom) / 100.0f;
}

bool Emitter::InitializeDatas(EmitterResource* eh, Effect* ef) {
    // "eh(=%p) is not a valid pointer"
    // "ef(=%p) is not a valid pointer"
    mTick = 0;
    mLifeStatus = NW4R_EF_LS_ACTIVE;
    mResource = eh;

    EmitterDesc* ed = eh->GetEmitterDesc();

    mEvalStatus = NW4R_EF_ES_WAIT;
    mCalcRemain = ed->emitEmitPast;
    mParameter.mComFlags = ed->commonFlag;
    mParameter.mEmitFlags = ed->emitFlag;
    mParameter.mEmitSpan = ed->emitLife;
    mWaitTime = ed->emitEmitStart;
    mEmitIntervalWait = 0;
    mParameter.mLODFar = static_cast<f32>(ed->lodFar) / 100.0f;
    mParameter.mLODNear = static_cast<f32>(ed->lodNear) / 100.0f;
    mParameter.mLODMinEmit = static_cast<f32>(ed->lodMinEmit) / 100.0f;
    mParameter.mEmitRatio = ed->emitEmit;
    mParameter.mEmitRandom = static_cast<f32>(ed->emitEmitRandom) / 100.0f;
    mParameter.mEmitInterval = ed->emitEmitInterval;
    mParameter.mEmitEmitDiv = ed->emitEmitDiv;
    mParameter.mEmitIntervalRandom =
        static_cast<f32>(ed->emitEmitIntarvalRandom) / 100.0f;
    mParameter.mEmitCount = 0.0f;
    mIsFirstEmission = true;
    mParameter.mTranslate = ed->translate;
    mParameter.mScale = ed->scale;
    mParameter.mRotate = ed->rotate;

    // TODO scale | rotate
    mParameter.mInherit = 3;
    mParameter.mInheritTranslate = 100;
    mParameter.mVelInitVelocityRandom = ed->velInitVelocityRandom;
    mParameter.mVelMomentumRandom = ed->velMomentumRandom;
    mParameter.mVelPowerRadiationDir = ed->velPowerRadiationDir;
    mParameter.mVelPowerYAxis = ed->velPowerYAxis;
    mParameter.mVelPowerRandomDir = ed->velPowerRandomDir;
    mParameter.mVelPowerNormalDir = ed->velPowerNormalDir;
    mParameter.mVelDiffusionEmitterNormal = ed->velDiffusionEmitterNormal;
    mParameter.mVelPowerSpecDir = ed->velPowerSpecDir;
    mParameter.mVelDiffusionSpecDir = ed->velDiffusionSpecDir;
    mParameter.mVelSpecDir = ed->velSpecDir;

    // Does nothing
    Resource* res = Resource::GetInstance();

    mRandSeed = ed->randomSeed;
    if (mRandSeed == 0) {
        mRandSeed = ef->mManagerES->mRandom.Rand();
    }
    mRandom.Srand(mRandSeed);

    for (int i = 0; i < LENGTHOF(ed->commonParam); ++i) {
        mParameter.mParams[i] = ed->commonParam[i];
    }

    mMtxDirty = true;
    mpReferenceParticle = NULL;
    mForm = ef->mManagerES->mEmitFormBuilder->Create(ed->GetFormType());
    mParent = NULL;
    mManagerEF = NULL;

    return true;
}

bool Emitter::Initialize(Effect* aParentEF, EmitterResource* eh,
                         u8 drawWeight) {
    // "aParentEF(=%p) is not a valid pointer"
    // "eh(=%p) is not a valid pointer"

    // Does nothing
    EmitterDesc* ed = eh->GetEmitterDesc();

    ReferencedObject::Initialize();
    mActivityList.Initialize();
    InitializeDatas(eh, aParentEF);
    mManagerEF = aParentEF;

    ParticleManager* pm =
        aParentEF->mManagerES->GetMemoryManager()->AllocParticleManager();
    if (!pm) {
        return false;
    }

    if (!pm->Initialize(this, eh)) {
        // "false"
        return false;
    }

    mManagerEF->Ref();
    mActivityList.ToActive(pm);
    pm->ChangeLifeStatus(NW4R_EF_LS_ACTIVE);
    // TODO magic constant
    pm->mFlag = 0;

    // TODO all magic constants
    if (eh->GetEmitterDesc()->commonFlag & 0x20) {
        // NOTE inherit scale
        pm->mFlag |= 1;
    }
    if (eh->GetEmitterDesc()->commonFlag & 0x40) {
        // NOTE inherit rotate
        pm->mFlag |= 2;
    }

    pm->mInheritTranslate = eh->GetEmitterDesc()->inheritPtclTranslate;
    pm->mWeight = drawWeight;
    mManagerEF->ParticleManagerAdd(pm);
    return true;
}

Emitter* Emitter::CreateEmitter(EmitterResource* eh,
                                EmitterInheritSetting* setting, Particle* pp,
                                u16 calcRemain) {
    // "eh(=%p) is not a valid pointer"
    // "incomplete relocation (emitter:%s)"
    Emitter* em = mManagerEF->CreateEmitter(eh, setting->weight, 0);
    if (!em) {
        return NULL;
    }

    em->mCalcRemain += calcRemain;
    em->mParent = this;
    em->mParent->Ref();
    em->mParameter.mInherit = 0;

    // TODO all magic constants
    if (mResource->GetEmitterDesc()->commonFlag & 0x80) {
        // NOTE inherit scale
        em->mParameter.mInherit |= 1;
    }
    if (mResource->GetEmitterDesc()->commonFlag & 0x100) {
        // NOTE inherit rotate
        em->mParameter.mInherit |= 2;
    }

    em->mParameter.mInheritTranslate =
        mResource->GetEmitterDesc()->inheritChildEmitTranslate;

    if (pp) {
        math::VEC3 transSave = em->mParameter.mTranslate;

        em->mParameter.mTranslate.x = 0.0f;
        em->mParameter.mTranslate.y = 0.0f;
        em->mParameter.mTranslate.z = 0.0f;
        em->SetMtxDirty();

        math::MTX34 mtx;
        math::MTX34 tmp;
        math::MTX34Identity(&mtx);
        math::MTX34RotXYZRad(&mtx, em->mParameter.mRotate.x,
                             em->mParameter.mRotate.y,
                             em->mParameter.mRotate.z);
        math::MTX34Scale(&mtx, &mtx, &em->mParameter.mScale);

        em->CalcGlobalMtx(&tmp);
        math::MTX34Inv(&tmp, &tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        pp->mParticleManager->CalcGlobalMtx(&tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        math::MTX34Trans(&mtx, &mtx, &pp->mParameter.mPosition);
        math::MTX34RotXYZRad(&tmp, em->mParameter.mRotate.x,
                             em->mParameter.mRotate.y,
                             em->mParameter.mRotate.z);
        math::MTX34Scale(&tmp, &tmp, &em->mParameter.mScale);
        math::MTX34Inv(&tmp, &tmp);
        math::MTX34Mult(&mtx, &mtx, &tmp);

        em->mParameter.mTranslate.x = transSave.x + mtx[0][3];
        em->mParameter.mTranslate.y = transSave.y + mtx[1][3];
        em->mParameter.mTranslate.z = transSave.z + mtx[2][3];
        em->SetMtxDirty();

        // TODO magic constant
        if (setting->speed != 0 || setting->scale != 0 || setting->alpha != 0 ||
            setting->color != 0 || setting->flag & 2) {
            em->mpReferenceParticle = pp;
            pp->Ref();
            em->mInheritSetting = *setting;
        }
    }

    return em;
}

void Emitter::CreateEmitterTmp(EmitterResource* eh,
                               EmitterInheritSetting* setting, Particle* pp,
                               u16 calcRemain) {
    // "eh(=%p) is not valid pointer"
    // "incomplete relocation (emitter:%s)"
    Emitter tmpEm;

    // Does nothing
    EmitterDesc* ed = eh->GetEmitterDesc();

    tmpEm.InitializeDatas(eh, mManagerEF);
    tmpEm.mCalcRemain += calcRemain;
    tmpEm.mManagerEF = mManagerEF;
    tmpEm.mParent = this;

    // This is used on and off in the function
    // In its current state, its usages are the base minimum to get it to match
    // TODO consistency
    Emitter* em = &tmpEm;

    if (setting->flag & 1 && setting->speed != 0) {
        math::VEC3 dir;
        math::MTX34 dirMtx;
        math::MTX34 tmpMtx;

        pp->mParticleManager->CalcGlobalMtx(&tmpMtx);
        // Set translation to zero
        tmpMtx[2][3] = 0.0f;
        tmpMtx[1][3] = 0.0f;
        tmpMtx[0][3] = 0.0f;

        pp->GetMoveDir(&dir);
        math::VEC3Transform(&dir, &tmpMtx, &dir);
        if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
            math::VEC3Normalize(&dir, &dir);
            if (setting->speed < 0) {
                math::VEC3Scale(&dir, &dir, -1.0f);
            }

            GetDirMtxY(&dirMtx, dir);
            math::MTX34RotXYZRad(&tmpMtx, tmpEm.mParameter.mRotate.x,
                                 tmpEm.mParameter.mRotate.y,
                                 tmpEm.mParameter.mRotate.z);
            math::MTX34Mult(&dirMtx, &dirMtx, &tmpMtx);
            MtxGetRotation(dirMtx, &em->mParameter.mRotate);
        }
    }

    math::VEC3 transSave = em->mParameter.mTranslate;

    tmpEm.mParameter.mTranslate.x = 0.0f;
    tmpEm.mParameter.mTranslate.y = 0.0f;
    tmpEm.mParameter.mTranslate.z = 0.0f;
    em->SetMtxDirty();

    math::MTX34 mtx;
    math::MTX34 tmp;
    math::MTX34Identity(&mtx);
    math::MTX34RotXYZRad(&mtx, tmpEm.mParameter.mRotate.x,
                         tmpEm.mParameter.mRotate.y,
                         tmpEm.mParameter.mRotate.z);
    math::MTX34Scale(&mtx, &mtx, &em->mParameter.mScale);

    em->CalcGlobalMtx(&tmp);
    math::MTX34Inv(&tmp, &tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    pp->mParticleManager->CalcGlobalMtx(&tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    math::MTX34Trans(&mtx, &mtx, &pp->mParameter.mPosition);
    math::MTX34RotXYZRad(&tmp, tmpEm.mParameter.mRotate.x,
                         tmpEm.mParameter.mRotate.y,
                         tmpEm.mParameter.mRotate.z);
    math::MTX34Scale(&tmp, &tmp, &em->mParameter.mScale);
    math::MTX34Inv(&tmp, &tmp);
    math::MTX34Mult(&mtx, &mtx, &tmp);

    tmpEm.mParameter.mTranslate.x = transSave.x + mtx[0][3];
    tmpEm.mParameter.mTranslate.y = transSave.y + mtx[1][3];
    tmpEm.mParameter.mTranslate.z = transSave.z + mtx[2][3];
    em->SetMtxDirty();
    tmpEm.CalcEmitter();
    tmpEm.CalcBillboard();

    // TODO all magic constants
    bool isInheritS = (mParameter.mComFlags & 0x80) &&
                      (eh->GetEmitterDesc()->commonFlag & 0x20);
    bool isInheritR = (mParameter.mComFlags & 0x100) &&
                      (eh->GetEmitterDesc()->commonFlag & 0x40);
    s8 inheritT; // DWARF implies this must be declared before it's defined
    const s8 parentChildT =
        mResource->GetEmitterDesc()->inheritChildEmitTranslate;
    const s8 myPtclT = eh->GetEmitterDesc()->inheritPtclTranslate;
    if (parentChildT == 0 || myPtclT == 0) {
        inheritT = 0;
    } else if (parentChildT == 100) {
        inheritT = myPtclT;
    } else if (myPtclT == 100) {
        inheritT = parentChildT;
    } else {
        inheritT = mResource->GetEmitterDesc()->inheritChildEmitTranslate *
                   eh->GetEmitterDesc()->inheritPtclTranslate / 100;
    }

    ParticleManager* pm = FindParticleManager(eh, isInheritS, isInheritR,
                                              inheritT, setting->weight);
    if (!pm) {
        pm = mManagerEF->mManagerES->GetMemoryManager()->AllocParticleManager();
        if (!pm) {
            return;
        }

        if (!pm->Initialize(this, eh)) {
            // "false"
            return;
        }

        mActivityList.ToActive(pm);
        pm->ChangeLifeStatus(NW4R_EF_LS_ACTIVE);
        // TODO magic constant
        pm->mFlag = 0;

        // TODO all magic constants
        // NOTE flag hints!!
        if (isInheritS) {
            pm->mFlag |= 1;
        }
        if (isInheritR) {
            pm->mFlag |= 2;
        }

        pm->mInheritTranslate = inheritT;
        pm->mWeight = setting->weight;
        mManagerEF->ParticleManagerAdd(pm);
    }

    // TODO magic constant
    if (setting->speed != 0 || setting->scale != 0 || setting->alpha != 0 ||
        setting->color != 0 || setting->flag & 2) {
        tmpEm.mpReferenceParticle = pp;
        pp->Ref();
        tmpEm.mInheritSetting = *setting;
    } else {
        tmpEm.mpReferenceParticle = NULL;
    }

    math::MTX34 space;
    math::MTX34 pmmtx;

    pm->CalcGlobalMtx(&pmmtx);
    math::MTX34Inv(&pmmtx, &pmmtx);
    tmpEm.CalcGlobalMtx(&space);
    math::MTX34Mult(&space, &pmmtx, &space);

    tmpEm.Emission(pm, &space);
    tmpEm.mParent = NULL;
    tmpEm.mManagerEF = NULL;

    if (tmpEm.mpReferenceParticle) {
        pp->UnRef();
        tmpEm.mpReferenceParticle = NULL;
    }

    if (mLifeStatus != NW4R_EF_LS_ACTIVE) {
        if (pm->GetLifeStatus() == NW4R_EF_LS_ACTIVE) {
            RetireParticleManager(pm);
        }
    }
}

ParticleManager* Emitter::FindParticleManager(EmitterResource* eh,
                                              bool inheritScale,
                                              bool inheritRotate,
                                              s8 inheritTranslate, u8 weight) {
    // "eh(=%p) is not valid pointer"
    for (ParticleManager* pm = reinterpret_cast<ParticleManager*>(
             ut::List_GetFirst(&mActivityList.mActiveList));
         pm; pm = reinterpret_cast<ParticleManager*>(
                 ut::List_GetNext(&mActivityList.mActiveList, pm))) {
        if (pm->mResource == eh && !!(pm->mFlag & 1) == inheritScale &&
            !!(pm->mFlag & 2) == inheritRotate &&
            pm->mInheritTranslate == inheritTranslate &&
            pm->mWeight == weight) {
            return pm;
        }
    }

    return NULL;
}

static f32 GetLODratio(math::VEC3& emPos, math::VEC3& cameraPos, f32 cameraFar,
                       f32 cameraNear, f32 LODf, f32 LODn) {
    // DWARF info indicates Gl comes before Vl
    // Yet it also indicates that Vl is written to first
    // Therefore, we declare first and define later
    f32 Gl;
    f32 Vl;
    f32 Nl;
    f32 Fl;
    f32 LODratio;
    f32 Fl_Nl;

    Vl = cameraFar - cameraNear;
    Gl = static_cast<f32>(sqrt(VEC3DistSq(&cameraPos, &emPos))) - cameraNear;
    Nl = Vl * LODn;
    Fl = Vl * LODf;

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

void Emitter::Emission(ParticleManager* pm, const math::MTX34* space) {
    // "pm(=%p) is not valid pointer"
    if (mEmitIntervalWait > 0) {
        --mEmitIntervalWait;
        return;
    }

    mEmitIntervalWait = mParameter.mEmitInterval;
    if (mParameter.mEmitIntervalRandom != 0.0f) {
        mEmitIntervalWait += static_cast<u16>(
            math::FCeil((static_cast<f32>(mParameter.mEmitInterval) *
                             mParameter.mEmitIntervalRandom -
                         1.0f) *
                        mRandom.RandFloat()));
    }

    // TODO magic constant
    if (mParameter.mEmitFlags & 0x20000) {
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

        // TODO magic constant
        if (mParameter.mEmitFlags & 0x100) {
            EffectSystem* es = mManagerEF->mManagerES;
            f32 ratio =
                GetLODratio(mParameter.mTranslate, es->mProcessCameraPos,
                            es->mProcessCameraFar, es->mProcessCameraNear,
                            mParameter.mLODFar, mParameter.mLODNear);
            count = (mParameter.mLODMinEmit +
                     (1.0f - mParameter.mLODMinEmit) * ratio) *
                    count;
        }

        mParameter.mEmitCount += count;

        if (mIsFirstEmission && mParameter.mEmitRatio != 0.0f &&
            mParameter.mEmitCount < 1.0f) {
            mParameter.mEmitCount = 1.0f;
        }
    }

    if (mParameter.mEmitCount >= 1.0f) {
        Resource* res = Resource::GetInstance();
        EmitterDesc* ed = mResource->GetEmitterDesc();

        if (mForm) {
            // "mManagerEF(=%p) is not valid pointer"
            if (mManagerEF->mCallBack.mPrevEmission) {
                int count = static_cast<int>(mParameter.mEmitCount);
                u32 flags = mParameter.mEmitFlags;
                f32 params[6];
                for (int i = 0; i < LENGTHOF(params); ++i) {
                    params[i] = mParameter.mParams[i];
                }
                u16 life = ed->ptclLife;
                f32 lifeRnd = ed->ptclLifeRandom / 100.0f;

                math::MTX34 newSpace = *space;
                mManagerEF->mCallBack.mPrevEmission(this, pm, &count, &flags,
                                                    &params, &life, &lifeRnd,
                                                    &newSpace);
                mForm->Emission(this, pm, count, flags, params, life, lifeRnd,
                                &newSpace);
            } else {
                mForm->Emission(
                    this, pm, static_cast<int>(mParameter.mEmitCount),
                    mParameter.mEmitFlags, mParameter.mParams, ed->ptclLife,
                    ed->ptclLifeRandom / 100.0f, space);
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

    if (!(mParameter.mComFlags & 4)) {
        if (mTick >= mParameter.mEmitSpan) {
            mManagerEF->RetireEmitter(this);
            return;
        }
    } else {
        if (mTick == -1) {
            mManagerEF->RetireEmitter(this);
            return;
        }
    }

    u32 animTime = mTick;
    u32 animSpan = !!(mParameter.mComFlags & 4) ? -1 : mParameter.mEmitSpan;
    bool mtxDirty = false;

    for (u16 i = mTick == 0 ? 0 : mResource->NumEmitInitTrack();
         i < mResource->NumEmitTrack(); ++i) {
        u8* ptr = mResource->GetEmitTrack(i);
        // TODO magic constants
        if (ptr[4] & 8) {
            continue;
        }

        // TODO magic constants
        if (ptr[0] != 0xac) {
            continue;
        }

        // TODO magic constants
        u16 ctrl = *reinterpret_cast<u16*>(ptr + 2); // Not in DWARF info
        u8 kind = ptr[1];

        switch (ctrl) {
        case 0x1:
        case 0x7:
            continue;
        case 0x301: {
            f32* targetF32;
            switch (kind) {
            case 0x44:
                targetF32 = &mParameter.mVelPowerRadiationDir;
                break;
            case 0x45:
                targetF32 = &mParameter.mVelPowerYAxis;
                break;
            case 0x46:
                targetF32 = &mParameter.mVelPowerRandomDir;
                break;
            case 0x49:
                targetF32 = &mParameter.mEmitRatio;
                break;
            default:
                continue;
            }

            AnimCurveExecuteF32(ptr, targetF32, animTime, mRandSeed, animSpan);
            continue;
        }
        case 0x303:
            switch (kind) {
            case 0x47:
                AnimCurveExecuteF32(ptr, &mParameter.mVelPowerNormalDir,
                                    animTime, mRandSeed, animSpan);
            default:
                continue;
            }
        case 0x307: {
            f32* targetF32;
            switch (kind) {
            case 0x41:
                targetF32 = &mParameter.mScale.x;
                break;
            case 0x42:
                targetF32 = &mParameter.mRotate.x;
                break;
            case 0x43:
                targetF32 = &mParameter.mTranslate.x;
                break;
            default:
                continue;
            }

            AnimCurveExecuteF32(ptr, targetF32, animTime, mRandSeed, animSpan);
            mtxDirty = true;
            continue;
        }
        default:
            break;
        }

        switch (ctrl & 0xFF00) {
        case 0x300: {
            f32* targetF32;
            switch (kind) {
            case 0x48:
                targetF32 = &mParameter.mVelPowerSpecDir;
                break;
            case 0x40:
                targetF32 = &mParameter.mParams[0];
                break;
            default:
                continue;
            }

            AnimCurveExecuteF32(ptr, targetF32, animTime, mRandSeed, animSpan);
            continue;
        }
        default:
            break;
        }
    }

    if (mtxDirty) {
        SetMtxDirty();
    }
}

void Emitter::CalcParticle() {
    if (GetFlagDisableCalc()) {
        return;
    }

    void* array[NW4R_EF_MAX_PARTICLEMANAGER];
    // "UtlistSize(&mActivityList.mActiveList) < NW4R_EF_MAX_PARTICLEMANAGER"
    u16 listsize = UtlistToArray(&mActivityList.mActiveList, array,
                                 UtlistSize(&mActivityList.mActiveList));
    for (u16 i = 0; i < listsize; ++i) {
        ParticleManager* pm = reinterpret_cast<ParticleManager*>(array[i]);
        pm->Calc();
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
        ParticleManager* pm = reinterpret_cast<ParticleManager*>(
            ut::List_GetFirst(&mActivityList.mActiveList));

        math::MTX34 space;
        math::MTX34 pmmtx;

        pm->CalcGlobalMtx(&pmmtx);
        math::MTX34Inv(&pmmtx, &pmmtx);
        CalcGlobalMtx(&space);
        math::MTX34Mult(&space, &pmmtx, &space);

        if (mWaitTime > 0) {
            --mWaitTime;
        } else {
            Emission(pm, &space);
            ++mTick;
        }
    } else {
        if (mWaitTime > 0) {
            --mWaitTime;
        } else {
            ++mTick;
        }
    }
}

void Emitter::CalcBillboard() {
    if (mLifeStatus != NW4R_EF_LS_ACTIVE && mLifeStatus != NW4R_EF_LS_WAIT) {
        return;
    }

    // TODO magic constants
    if (!(mParameter.mEmitFlags & 0x10000) &&
        !(mParameter.mEmitFlags & 0x8000)) {
        return;
    }

    math::MTX34 globalMtx;
    mParameter.mRotate.z = 0.0f;
    mParameter.mRotate.y = 0.0f;
    mParameter.mRotate.x = 0.0f;

    mMtxDirty = true;
    CalcGlobalMtx(&globalMtx);

    math::MTX34 mtx;
    math::MTX34Mult(&mtx, &mManagerEF->mManagerES->mProcessCameraMtx,
                    &globalMtx);

    math::MTX34 tmp = mtx;
    tmp[0][0] = math::FSqrt(tmp[0][0] * tmp[0][0] + tmp[1][0] * tmp[1][0] +
                            tmp[2][0] * tmp[2][0]);
    tmp[2][0] = 0.0f;
    tmp[1][0] = 0.0f;
    tmp[1][1] = math::FSqrt(tmp[0][1] * tmp[0][1] + tmp[1][1] * tmp[1][1] +
                            tmp[2][1] * tmp[2][1]);
    tmp[2][1] = 0.0f;
    tmp[0][1] = 0.0f;
    tmp[2][2] = math::FSqrt(tmp[0][2] * tmp[0][2] + tmp[1][2] * tmp[1][2] +
                            tmp[2][2] * tmp[2][2]);
    tmp[1][2] = 0.0f;
    tmp[0][2] = 0.0f;

    if (!!(mParameter.mEmitFlags & 0x8000)) {
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

math::MTX34* Emitter::RestructMatrix(math::MTX34* result, math::MTX34* orig,
                                     bool isInheritS, bool isInheritR,
                                     s8 inheritT) {
    // "result(=%p) is not valid pointer"
    // "orig(=%p) is not valid pointer"
    // "result != orig"

    // Full copy
    if (isInheritS && isInheritR && inheritT == 100) {
        *result = *orig;
        return result;
    }

    // No copy
    if (!isInheritS && !isInheritR && inheritT == 0) {
        return math::MTX34Identity(result);
    }

    // Partial copy
    math::MTX34Identity(result);

    if (inheritT != 0) {
        math::VEC3 tra;
        MtxGetTranslate(*orig, &tra);

        math::VEC3Scale(&tra, &tra, static_cast<f32>(inheritT) / 100.0f);
        math::MTX34Trans(result, result, &tra);
    }

    if (isInheritR) {
        math::MTX34 rot;
        MtxGetRotationMtx(*orig, &rot);
        math::MTX34Mult(result, result, &rot);
    }

    if (isInheritS) {
        math::VEC3 sca;
        MtxGetScale(*orig, &sca);
        math::MTX34Scale(result, result, &sca);
    }

    return result;
}

math::MTX34* Emitter::CalcGlobalMtx(math::MTX34* result) {
    if (mMtxDirty) {
        math::MTX34 tmp;

        if (!mParent) {
            math::MTX34Copy(&mMtx, mManagerEF->GetRootMtx());
        } else {
            math::MTX34 orig;
            mParent->CalcGlobalMtx(&orig);
            RestructMatrix(&mMtx, &orig, mParameter.mInherit & 1,
                           mParameter.mInherit & 2,
                           mParameter.mInheritTranslate);
        }

        math::MTX34Trans(&mMtx, &mMtx, &mParameter.mTranslate);
        math::MTX34RotXYZRad(&tmp, mParameter.mRotate.x, mParameter.mRotate.y,
                             mParameter.mRotate.z);
        math::MTX34Mult(&mMtx, &mMtx, &tmp);
        math::MTX34Scale(&mMtx, &mMtx, &mParameter.mScale);
        mMtxDirty = false;
    }

    if (result) {
        *result = mMtx;
        return result;
    }

    return &mMtx;
}

void Emitter::SetMtxDirty() {
    mMtxDirty = true;

    ParticleManager* pm = NULL;
    while (pm = reinterpret_cast<ParticleManager*>(
               ut::List_GetNext(&mActivityList.mActiveList, pm))) {
        pm->SetMtxDirty();
    }

    if (!mManagerEF) {
        return;
    }

    Emitter* em = NULL;
    while (em = reinterpret_cast<Emitter*>(
               ut::List_GetNext(&mManagerEF->mActivityList.mActiveList, em))) {
        if (em->mMtxDirty) {
            continue;
        }

        for (Emitter* search = em->mParent; search; search = search->mParent) {
            if (search != this) {
                continue;
            }

            em->mMtxDirty = true;
            ParticleManager* pm = NULL;
            while (pm = reinterpret_cast<ParticleManager*>(
                       ut::List_GetNext(&em->mActivityList.mActiveList, pm))) {
                pm->SetMtxDirty();
            }
        }
    }
}

u16 Emitter::GetNumParticleManager() const {
    return mActivityList.mActiveList.numObjects;
}

ParticleManager* Emitter::GetParticleManager(u16 i) {
    return reinterpret_cast<ParticleManager*>(
        ut::List_GetNth(&mActivityList.mActiveList, i));
}

// TODO uintptr_t
u32 Emitter::ForeachEmitter(void (*func)(void*, u32), u32 param, bool b) {
    return mManagerEF->ForeachEmitterFrom(func, param, b, this);
}

// TODO uintptr_t
static void foreachParticleManagerSub(void* param, u32 data) {
    Emitter* em = reinterpret_cast<Emitter*>(param);
    ForeachData* pData = reinterpret_cast<ForeachData*>(data);
    pData->count += em->ForeachParticleManager(pData->func, pData->param,
                                               pData->all, false);
}

u32 Emitter::ForeachParticleManager(void (*func)(void*, u32), u32 param,
                                    bool all, bool iterate) {
    u32 count = 0;
    ParticleManager* pm = reinterpret_cast<ParticleManager*>(
        ut::List_GetFirst(&mActivityList.mActiveList));
    ParticleManager* next = NULL;
    for (; pm; pm = next) {
        next = reinterpret_cast<ParticleManager*>(
            ut::List_GetNext(&mActivityList.mActiveList, pm));

        if (all || pm->GetLifeStatus() == NW4R_EF_LS_ACTIVE) {
            (*func)(pm, param);
            ++count;
        }
    }

    if (iterate) {
        ForeachData data;
        data.count = 0;
        data.func = func;
        data.param = param;
        data.all = all;

        // TODO uintptr_t
        ForeachEmitter(foreachParticleManagerSub, reinterpret_cast<u32>(&data),
                       true);
        count += data.count;
    }

    return count;
}

} // namespace ef
} // namespace nw4r
