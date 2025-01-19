#include <nw4r/ef.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <cstring>

namespace nw4r {
namespace ef {

math::MTX34 ParticleManager::smDrawMtxPMtoEM;
math::MTX34 ParticleManager::smMtxInv;

s32 ParticleManager::smMtxInvId = 0;

ParticleManager::ParticleManager()
    : mActivityList(offsetof(Particle, mActivityLink)) {}

void ParticleManager::SendClosing() {
    mManagerEM->Closing(this);
}

void ParticleManager::DestroyFunc() {}

bool ParticleManager::Closing(Particle* pParticle) {
    pParticle->mParticleManager->UnRef();

    mActivityList.ToClosing(pParticle);
    pParticle->mLifeStatus = NW4R_EF_LS_CLOSING;

    return true;
}

int ParticleManager::RetireParticle(Particle* pParticle) {
    if (pParticle->mLifeStatus != NW4R_EF_LS_ACTIVE) {
        return 0;
    }

    mActivityList.ToWait(pParticle);
    pParticle->Destroy();
    return 1;
}

int ParticleManager::RetireParticleAll() {
    int num = 0;

    Particle* pIt;
    Particle* pNext;

    for (pIt = static_cast<Particle*>(mActivityList.mActiveList.headObject);
         pIt != NULL; pIt = pNext) {

        pNext = static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(mActivityList.mActiveList, pIt)->nextObject);

        if (pIt->mLifeStatus == NW4R_EF_LS_ACTIVE) {
            num += RetireParticle(pIt);
        }
    }

    return num;
}

bool ParticleManager::Initialize(Emitter* pParent, EmitterResource* pResource) {
    ReferencedObject::Initialize();

    mActivityList.Initialize();

    mModifier.mScale.x = 1.0f;
    mModifier.mScale.y = 1.0f;

    mModifier.mRotate.x = 0.0f;
    mModifier.mRotate.y = 0.0f;
    mModifier.mRotate.z = 0.0f;

    mManagerEM = pParent;
    pParent->Ref();

    mResource = pResource;
    mFlag = 0;
    SetMtxDirty();

    EmitterDesc* pDesc = mResource->GetEmitterDesc();

    mDrawStrategy =
        mManagerEM->mManagerEF->mManagerES->mDrawStrategyBuilder->Create(
            pDesc->drawSetting.ptcltype);

    mLastCalced = NULL;

    Modifier_SetSimpleLightParameter(pDesc->drawSetting);

    return true;
}

ParticleManager::~ParticleManager() {}

Particle*
ParticleManager::CreateParticle(u16 life, math::VEC3 pos, math::VEC3 vel,
                                const math::MTX34* pSpace, f32 momentum,
                                const EmitterInheritSetting* pSetting,
                                Particle* pReferencePtcl, u16 calcRemain) {

    Particle* pParticle =
        mManagerEM->mManagerEF->mManagerES->GetMemoryManager()->AllocParticle();

    if (pParticle == NULL) {
        return NULL;
    }

    if (!pParticle->Initialize(life, pos, vel, this, pSpace, momentum, pSetting,
                               pReferencePtcl)) {
        return NULL;
    }

    pParticle->mCalcRemain += calcRemain;
    mActivityList.ToActive(pParticle);
    pParticle->mLifeStatus = ReferencedObject::NW4R_EF_LS_ACTIVE;

    return pParticle;
}

void ParticleManager::Calc() {
    Particle* pFirst = static_cast<Particle*>(
        ut::List_GetNext(&mActivityList.mActiveList, mLastCalced));

    if (pFirst == NULL) {
        return;
    }

    Particle* pIt = pFirst;

    if (mManagerEM->mManagerEF->mCallBack.mPrevPtclCalc != NULL) {
        mManagerEM->mManagerEF->mCallBack.mPrevPtclCalc(
            this, &mActivityList.mActiveList, pFirst);
    }

    math::MTX34 mtxLocToGlb;
    CalcGlobalMtx(&mtxLocToGlb);

    math::MTX34 mtxGlbToLoc;
    math::MTX34Inv(&mtxGlbToLoc, &mtxLocToGlb);

    math::MTX34 mtxEmToGlb;
    mManagerEM->CalcGlobalMtx(&mtxEmToGlb);

    math::MTX34 mtxEmToLoc;
    math::MTX34Mult(&mtxEmToLoc, &mtxGlbToLoc, &mtxEmToGlb);

    math::MTX34 mtxLocToEm;
    math::MTX34Inv(&mtxLocToEm, &mtxEmToLoc);

    math::MTX34 mtxGlbToLocNoTrans = mtxGlbToLoc;
    mtxGlbToLocNoTrans._03 = 0.0f;
    mtxGlbToLocNoTrans._13 = 0.0f;
    mtxGlbToLocNoTrans._23 = 0.0f;

    math::MTX34 mtxLocToGlbNoTrans;
    math::MTX34Inv(&mtxLocToGlbNoTrans, &mtxGlbToLocNoTrans);

    math::MTX34 mtxLocToEmNoTrans = mtxLocToEm;
    mtxLocToEmNoTrans._03 = 0.0f;
    mtxLocToEmNoTrans._13 = 0.0f;
    mtxLocToEmNoTrans._23 = 0.0f;

    math::MTX34 mtxEmToLocNoTrans = mtxEmToLoc;
    mtxEmToLocNoTrans._03 = 0.0f;
    mtxEmToLocNoTrans._13 = 0.0f;
    mtxEmToLocNoTrans._23 = 0.0f;

    Particle* pNext;

    for (; pIt != NULL; pIt = pNext) {
        pNext = static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(mActivityList.mActiveList, pIt)->nextObject);

        if (pIt->mLifeStatus != NW4R_EF_LS_ACTIVE) {
            continue;
        }

        if (pIt->mEvalStatus != NW4R_EF_ES_WAIT) {
            continue;
        }

        pIt->mEvalStatus = NW4R_EF_ES_DONE;

        if (pIt->mCalcRemain != 0) {
            mManagerEM->mManagerEF->SetFlagExistCalcRemain(true);
        }

        math::VEC3 prevPos = pIt->mParameter.mPosition;
        math::VEC3 prevVel = pIt->mParameter.mVelocity;

        math::VEC3 prevDir;
        pIt->GetMoveDir(&prevDir);

        pIt->mParameter.mPrevPosition = pIt->mParameter.mPosition;

        if (pIt->mLife <= pIt->mTick) {
            RetireParticle(pIt);
            continue;
        }

        math::VEC3 addVel(0.0f, 0.0f, 0.0f);
        math::VEC3 addPos(0.0f, 0.0f, 0.0f);
        math::VEC3 affect(0.0f, 0.0f, 0.0f);

        bool findEmitterTiming = false;

        for (u16 i = pIt->mTick == 0 ? 0 : mResource->NumPtclInitTrack();
             i < mResource->NumPtclTrack(); i++) {

            u8* pPtclTrack = mResource->GetPtclTrack(i);

#define pTrackAsHeader reinterpret_cast<AnimCurveHeader*>(pPtclTrack)

            if (pTrackAsHeader->processFlag & AnimCurveHeader::PROC_FLAG_STOP) {
                continue;
            }

            if (pIt->mTick != 0 && pTrackAsHeader->frameLength <= 1 &&
                pTrackAsHeader->kindType < AC_TARGET_TEXTUREINDTRANSLATE + 1) {
                continue;
            }

            u32 tick;
            u32 life;
            u16 seed;

            if (pTrackAsHeader->processFlag &
                AnimCurveHeader::PROC_FLAG_TIMING) {

                findEmitterTiming = true;

                tick = pIt->mParticleManager->mManagerEM->mTick;

                if (pIt->mParticleManager->mManagerEM->mParameter.mComFlags &
                    EmitterDesc::CMN_FLAG_MAX_LIFE) {
                    life = 0xFFFFFFFF;
                } else {
                    life =
                        pIt->mParticleManager->mManagerEM->mParameter.mEmitSpan;
                }

                seed = pIt->mParticleManager->mManagerEM->mRandSeed;
            } else {
                tick = pIt->mTick;
                life = pIt->mLife;
                seed = pIt->mRandSeed;
            }

            if (pTrackAsHeader->magic != NW4R_EF_MAGIC_ANIMCURVE) {
                continue;
            }

            // Load curveFlag and kindEnable
            u16 ctrl = *reinterpret_cast<u16*>(&pTrackAsHeader->curveFlag);
            u8 kind = pTrackAsHeader->kindType;

            switch (ctrl >> 4) {
            case AC_TYPE_PARTICLE_U8: {
                u8* pTarget;

                switch (kind) {
                case AC_TARGET_ALPHA0PRI: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_0][COLOR_IDX_PRI].a;
                    break;
                }
                case AC_TARGET_ALPHA0SEC: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_0][COLOR_IDX_SEC].a;
                    break;
                }
                case AC_TARGET_ALPHA1PRI: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_1][COLOR_IDX_PRI].a;
                    break;
                }
                case AC_TARGET_ALPHA1SEC: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_1][COLOR_IDX_SEC].a;
                    break;
                }

                case AC_TARGET_ACMPREF0: {
                    pTarget = &pIt->mParameter.mACmpRef0;
                    break;
                }
                case AC_TARGET_ACMPREF1: {
                    pTarget = &pIt->mParameter.mACmpRef1;
                    break;
                }

                case AC_TARGET_COLOR0PRI: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_0][COLOR_IDX_PRI].r;
                    break;
                }
                case AC_TARGET_COLOR0SEC: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_0][COLOR_IDX_SEC].r;
                    break;
                }
                case AC_TARGET_COLOR1PRI: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_1][COLOR_IDX_PRI].r;
                    break;
                }
                case AC_TARGET_COLOR1SEC: {
                    pTarget =
                        &pIt->mParameter.mColor[COLOR_LAYER_1][COLOR_IDX_SEC].r;
                    break;
                }
                }

                AnimCurveExecuteU8(pPtclTrack, pTarget, tick, seed, life);
                break;
            }

            case AC_TYPE_PARTICLE_F32: {
                f32* pTarget;

                switch (kind) {
                case AC_TARGET_SIZE: {
                    pTarget = reinterpret_cast<f32*>(&pIt->mParameter.mSize);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_SCALE: {
                    pTarget = reinterpret_cast<f32*>(&pIt->mParameter.mScale);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE1SCALE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureScale[TEX_LAYER_1]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE2SCALE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureScale[TEX_LAYER_2]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTUREINDSCALE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureScale[TEX_LAYER_IND]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE1TRANSLATE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureTranslate[TEX_LAYER_1]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE2TRANSLATE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureTranslate[TEX_LAYER_2]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTUREINDTRANSLATE: {
                    pTarget = reinterpret_cast<f32*>(
                        &pIt->mParameter.mTextureTranslate[TEX_LAYER_IND]);
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE1ROTATE: {
                    pTarget = &pIt->mParameter.mTextureRotate[TEX_LAYER_1];
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTURE2ROTATE: {
                    pTarget = &pIt->mParameter.mTextureRotate[TEX_LAYER_2];
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_TEXTUREINDROTATE: {
                    pTarget = &pIt->mParameter.mTextureRotate[TEX_LAYER_IND];
                    AnimCurveExecuteF32(pPtclTrack, pTarget, tick, seed, life);
                    break;
                }

                case AC_TARGET_FIELD_SPEED: {
                    f32 speed;
                    AnimCurveExecuteF32(pPtclTrack, &speed, tick, seed, life);
                    math::VEC3Scale(&affect, &affect, speed - 1.0f);
                    addVel += affect;
                    break;
                }

                case AC_TARGET_UNK32: {
                    // 80019ec0
                    break;
                }

                case AC_TARGET_UNK34: {
                    // 8001a51c
                    break;
                }

                case AC_TARGET_UNK35: {
                    // 8001a6f0
                    break;
                }

                case AC_TARGET_UNK36: {
                    // 8001a904
                    break;
                }

                case AC_TARGET_UNK38: {
                    // 8001a364
                    break;
                }

                case AC_TARGET_UNK39: {
                    // 80019fac
                    break;
                }
                }
                break;
            }

            case AC_TYPE_PARTICLE_ROTATE: {
                if (kind == AC_TARGET_12) {
                    break;
                }

                f32* pTarget = reinterpret_cast<f32*>(&pIt->mParameter.mRotate);
                AnimCurveExecuteRotate(pPtclTrack, pTarget, tick, seed, life);
                break;
            }

            case AC_TYPE_PARTICLE_TEXTURE: {
                AnimCurveExecuteTexture(pPtclTrack, pIt, tick, seed, life);
                break;
            }

            case AC_TYPE_CHILD: {
                AnimCurveExecuteChild(pPtclTrack, pIt, tick, seed, life);
                break;
            }

            default: {
                break;
            }
            }

#undef pTrackAsHeader
        }

        pIt->mTick++;
    }

    mLastCalced =
        static_cast<Particle*>(ut::List_GetLast(&mActivityList.mActiveList));

    if (mManagerEM->mManagerEF->mCallBack.mPostPtclCalc != NULL) {
        mManagerEM->mManagerEF->mCallBack.mPostPtclCalc(
            this, &mActivityList.mActiveList, pFirst);
    }
}

void ParticleManager::Draw(const DrawInfo& rInfo) {
    const EmitterDesc* pDesc = mResource->GetEmitterDesc();

    if ((pDesc->drawSetting.mFlags & EmitterDrawSetting::FLAG_HIDDEN) ||
        (mManagerEM->mParameter.mComFlags &
         EmitterDesc::CMN_FLAG_DISABLE_DRAW)) {
        return;
    }

    mDrawStrategy->Draw(rInfo, this);
}

math::MTX34* ParticleManager::CalcGlobalMtx(math::MTX34* pResult) {
    if (mMtxDirty) {
        math::MTX34 orig;
        mManagerEM->CalcGlobalMtx(&orig);

        mManagerEM->RestructMatrix(&mMtx, &orig, mFlag & FLAG_MTX_INHERIT_SCALE,
                                   mFlag & FLAG_MTX_INHERIT_ROT,
                                   mInheritTranslate);

        mMtxDirty = false;
    }

    *pResult = mMtx;
    return pResult;
}

void ParticleManager::BeginCalc(bool onlyIfRemain) {
    mLastCalced = NULL;

    // clang-format off
    for (Particle* pIt = static_cast<Particle*>(mActivityList.mActiveList.headObject);
         pIt != NULL; 
         pIt = static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(mActivityList.mActiveList, pIt)->nextObject))
    // clang-format on
    {
        if (!onlyIfRemain || pIt->mCalcRemain != 0) {
            if (pIt->mCalcRemain != 0) {
                pIt->mCalcRemain--;
            }

            if (pIt->GetLifeStatus() == ReferencedObject::NW4R_EF_LS_ACTIVE &&
                pIt->mEvalStatus == NW4R_EF_ES_DONE) {

                pIt->mEvalStatus = NW4R_EF_ES_WAIT;
            }
        }
    }
}

void ParticleManager::EndCalc() {
    // clang-format off
    for (Particle* pIt = static_cast<Particle*>(mActivityList.mActiveList.headObject);
         pIt != NULL; 
         pIt = static_cast<Particle*>(
            NW4R_UT_LIST_GET_LINK(mActivityList.mActiveList, pIt)->nextObject))
    // clang-format on
    {
        if (pIt->GetLifeStatus() == ReferencedObject::NW4R_EF_LS_ACTIVE &&
            pIt->mEvalStatus == NW4R_EF_ES_SKIP) {

            pIt->mEvalStatus = NW4R_EF_ES_DONE;
        }
    }
}

void ParticleManager::BeginDraw() {
    math::MTX34 emMtx;
    math::MTX34 pmMtx;

    mManagerEM->CalcGlobalMtx(&emMtx);
    CalcGlobalMtx(&pmMtx);

    math::MTX34Inv(&emMtx, &emMtx);
    math::MTX34Mult(&smDrawMtxPMtoEM, &emMtx, &pmMtx);
}

const math::MTX34* ParticleManager::Draw_GetMtxPMtoEM() const {
    return &smDrawMtxPMtoEM;
}

void ParticleManager::EndDraw() {}

void ParticleManager::Draw_ModifyColor(Particle* pParticle, GXColor* pColorPri,
                                       GXColor* pColorSec) {
    switch (mModifier.mLight.mType) {
    case ParticleModifier::SIMPLELIGHT_AMBIENT: {
        pColorPri->r = (pColorPri->r * mModifier.mLight.mAmbient.r + 128) >> 8;
        pColorPri->g = (pColorPri->g * mModifier.mLight.mAmbient.g + 128) >> 8;
        pColorPri->b = (pColorPri->b * mModifier.mLight.mAmbient.b + 128) >> 8;
        pColorPri->a = (pColorPri->a * mModifier.mLight.mAmbient.a + 128) >> 8;

        pColorSec->r = (pColorSec->r * mModifier.mLight.mAmbient.r + 128) >> 8;
        pColorSec->g = (pColorSec->g * mModifier.mLight.mAmbient.g + 128) >> 8;
        pColorSec->b = (pColorSec->b * mModifier.mLight.mAmbient.b + 128) >> 8;
        pColorSec->a = (pColorSec->a * mModifier.mLight.mAmbient.a + 128) >> 8;
        break;
    }

    case ParticleModifier::SIMPLELIGHT_DIFFUSE: {
        if (mModifier.mLight.mRadius < NW4R_MATH_FLT_EPSILON) {
            // clang-format off
            pColorPri->r = (pColorPri->r * mModifier.mLight.mAmbient.r + 128) >> 8;
            pColorPri->g = (pColorPri->g * mModifier.mLight.mAmbient.g + 128) >> 8;
            pColorPri->b = (pColorPri->b * mModifier.mLight.mAmbient.b + 128) >> 8;
            pColorPri->a = (pColorPri->a * mModifier.mLight.mAmbient.a + 128) >> 8;

            pColorSec->r = (pColorSec->r * mModifier.mLight.mAmbient.r + 128) >> 8;
            pColorSec->g = (pColorSec->g * mModifier.mLight.mAmbient.g + 128) >> 8;
            pColorSec->b = (pColorSec->b * mModifier.mLight.mAmbient.b + 128) >> 8;
            pColorSec->a = (pColorSec->a * mModifier.mLight.mAmbient.a + 128) >> 8;
            // clang-format on
        } else {
            const math::MTX34* pMtxPMtoEM = Draw_GetMtxPMtoEM();

            math::VEC3 pos;
            math::VEC3Transform(&pos, pMtxPMtoEM,
                                &pParticle->mParameter.mPosition);

            math::VEC3Sub(&pos, &pos, &mModifier.mLight.mPosition);
            f32 dist = math::VEC3Len(&pos);

            if (dist > mModifier.mLight.mRadius) {
                // clang-format off
                pColorPri->r = (pColorPri->r * mModifier.mLight.mAmbient.r + 128) >> 8;
                pColorPri->g = (pColorPri->g * mModifier.mLight.mAmbient.g + 128) >> 8;
                pColorPri->b = (pColorPri->b * mModifier.mLight.mAmbient.b + 128) >> 8;
                pColorPri->a = (pColorPri->a * mModifier.mLight.mAmbient.a + 128) >> 8;

                pColorSec->r = (pColorSec->r * mModifier.mLight.mAmbient.r + 128) >> 8;
                pColorSec->g = (pColorSec->g * mModifier.mLight.mAmbient.g + 128) >> 8;
                pColorSec->b = (pColorSec->b * mModifier.mLight.mAmbient.b + 128) >> 8;
                pColorSec->a = (pColorSec->a * mModifier.mLight.mAmbient.a + 128) >> 8;
                // clang-format on
            } else {
                s32 attn = (256 * dist) / mModifier.mLight.mRadius;

                u16 lr = mModifier.mLight.mDiffuse.r * 256 +
                         attn * (mModifier.mLight.mAmbient.r -
                                 mModifier.mLight.mDiffuse.r);

                u16 lg = mModifier.mLight.mDiffuse.g * 256 +
                         attn * (mModifier.mLight.mAmbient.g -
                                 mModifier.mLight.mDiffuse.g);

                u16 lb = mModifier.mLight.mDiffuse.b * 256 +
                         attn * (mModifier.mLight.mAmbient.b -
                                 mModifier.mLight.mDiffuse.b);

                u16 la = mModifier.mLight.mDiffuse.a * 256 +
                         attn * (mModifier.mLight.mAmbient.a -
                                 mModifier.mLight.mDiffuse.a);

                pColorPri->r = (pColorPri->r * lr + 128) >> 16;
                pColorPri->g = (pColorPri->g * lg + 128) >> 16;
                pColorPri->b = (pColorPri->b * lb + 128) >> 16;
                pColorPri->a = (pColorPri->a * la + 128) >> 16;

                pColorSec->r = (pColorSec->r * lr + 128) >> 16;
                pColorSec->g = (pColorSec->g * lg + 128) >> 16;
                pColorSec->b = (pColorSec->b * lb + 128) >> 16;
                pColorSec->a = (pColorSec->a * la + 128) >> 16;
            }
        }
        break;
    }

    default: {
        break;
    }
    }
}

} // namespace ef
} // namespace nw4r
