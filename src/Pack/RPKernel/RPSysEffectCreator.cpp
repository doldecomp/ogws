#include <Pack/RPKernel.h>

#include <egg/core.h>

#include <nw4r/ef.h>
#include <nw4r/ut.h>

#include <cstring>

#define MY_EPSILON 0.0001f

/**
 * @brief Constructor
 *
 * @param drawScene Effect draw scene
 */
RPSysEffectCreator::RPSysEffectCreator(u32 drawScene) {
    // 6 bits needed to represent [0, MAX_GROUP_ID]
    mBaseGroupID = drawScene << 7;

    mpEffectProject = NULL;
    mpTextureProject = NULL;

    mBackSaveBuffer = ESaveBuffer_2nd;
    mIsSlowEffect = false;

    mFrame = 0.0f;
    mFrameRate = 1.0f;

    mpSlowSystem = NULL;
    mpMemoryManager = NULL;

    for (int i = 0; i < ESaveBuffer_Max; i++) {
        mEmitterParamSave[i] = NULL;
        mParticleParamSave[i] = NULL;
    }
}

/**
 * @brief Destructor
 */
RPSysEffectCreator::~RPSysEffectCreator() {
    resetEffectResource();
}

/**
 * @brief Attaches new effect resource files
 *
 * @param pEffectProject Binary effect data project (.BREFF)
 * @param pTextureProject Binary effect texture project (.BREFT)
 */
void RPSysEffectCreator::setEffectResource(void* pEffectProject,
                                           void* pTextureProject) {

    if (mpEffectProject == NULL && mpTextureProject == NULL) {
        nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

        mpEffectProject = pResource->Add(static_cast<u8*>(pEffectProject));
        mpTextureProject =
            pResource->AddTexture(static_cast<u8*>(pTextureProject));

        pResource->RelocateCommand();
    }
}

/**
 * @brief Releases the attached effect resource files
 */
void RPSysEffectCreator::resetEffectResource() {
    stopAllEffect();

    bool relocate = false;
    nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

    if (mpEffectProject != NULL) {
        pResource->RemoveEffectProject(mpEffectProject);
        mpEffectProject = NULL;
        relocate = true;
    }

    if (mpTextureProject != NULL) {
        pResource->RemoveTextureProject(mpTextureProject);
        mpTextureProject = NULL;
        relocate = true;
    }

    if (relocate) {
        pResource->RelocateCommand();
    }
}

/**
 * @brief Creates the effect system for slow-motion effects
 */
void RPSysEffectCreator::createSlowSystem() {
    u32 workSize = RPSysEffectMemoryManager::CalcMemorySize( //
        SLOW_MAX_EFFECT,                                     //
        SLOW_MAX_EMITTER,                                    //
        SLOW_MAX_PARTICLE_MANAGER,                           //
        SLOW_MAX_PARTICLE,                                   //
        RPSysEffectDefine::MAX_GROUP_ID);

    void* pEffectWork = EGG::Heap::alloc(workSize + 32, 32, NULL);
    pEffectWork = nw4r::ut::RoundUp(pEffectWork, 32);

    mpMemoryManager = new RPSysEffectMemoryManager( //
        pEffectWork,                                //
        workSize,                                   //
        SLOW_MAX_EFFECT,                            //
        SLOW_MAX_EMITTER,                           //
        SLOW_MAX_PARTICLE_MANAGER,                  //
        SLOW_MAX_PARTICLE);

    mpSlowSystem = new nw4r::ef::EffectSystem();
    mpSlowSystem->SetMemoryManager(mpMemoryManager,
                                   RPSysEffectDefine::MAX_GROUP_ID);

    for (int i = 0; i < ESaveBuffer_Max; i++) {
        mEmitterParamSave[i] = //
            new nw4r::ef::EmitterParameter[SLOW_MAX_EMITTER];
        mParticleParamSave[i] = //
            new nw4r::ef::ParticleParameter[SLOW_MAX_PARTICLE];
    }
}

/**
 * @brief Sets the frame rate of the slow-motion system
 *
 * @param frameRate Frame rate (0, 1)
 */
void RPSysEffectCreator::setFrameRate(f32 frameRate) {
    if (frameRate >= 1.0f - MY_EPSILON) {
        mFrameRate = 1.0f - MY_EPSILON;

    } else if (frameRate <= MY_EPSILON) {
        mFrameRate = MY_EPSILON;

    } else {
        mFrameRate = frameRate;
    }
}

/**
 * @brief Tests whether the slow-motion effect system exists
 */
bool RPSysEffectCreator::isSlowSystem() const {
    return mpSlowSystem != NULL;
}

/**
 * @brief Tests whether effects are currently updating in slow motion
 */
bool RPSysEffectCreator::isSlowEffect() const {
    return mIsSlowEffect;
}

/**
 * @brief Kills all effects owned by this creator
 */
void RPSysEffectCreator::stopAllEffect() {
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max; i++) {
        u32 groupID = mBaseGroupID | i;
        pSystem->RetireEmitterAll(groupID);
        pSystem->RetireParticleAll(groupID);
    }

    if (mpSlowSystem != NULL) {
        for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max; i++) {
            u32 groupID = mBaseGroupID | i;
            mpSlowSystem->RetireEmitterAll(groupID);
            mpSlowSystem->RetireParticleAll(groupID);
        }
    }
}

/**
 * @brief Creates an instance of the specified effect
 *
 * @param pName Effect name
 * @param drawGroup Effect draw group
 */
nw4r::ef::Effect* RPSysEffectCreator::createEffect(const char* pName,
                                                   u32 drawGroup) {
    u32 groupID = mBaseGroupID | drawGroup;

    nw4r::ef::ResEmitter res =
        nw4r::ef::Resource::GetInstance()->FindEmitter(pName, NULL);

    u16 flags = res.ptr()->GetEmitterDesc()->userdata[2] << 8 |
                res.ptr()->GetEmitterDesc()->userdata[3];

    // TODO(kiwi) These should be EDrawGroup values I think?
    if (flags & RPSysEffectDefine::EUserFlag_15) {
        if (flags & RPSysEffectDefine::EUserFlag_0) {
            groupID |= 0x30;
        } else {
            groupID |= 0x20;
        }
    } else if (!(flags & RPSysEffectDefine::EUserFlag_0)) {
        groupID |= 0x10;
    }

    if (mpSlowSystem != NULL &&
        flags & RPSysEffectDefine::EUserFlag_SlowSystem) {

        return mpSlowSystem->CreateEffect(pName, groupID, 0);
    } else {
        return nw4r::ef::EffectSystem::GetInstance() //
            ->CreateEffect(pName, groupID, 0);
    }
}

/**
 * @brief Updates all effects owned by this creator
 */
void RPSysEffectCreator::update() {
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max; i++) {
        pSystem->Calc(mBaseGroupID | i, false);
    }

    if (mpSlowSystem != NULL) {
        const nw4r::ut::List *pListEmitter, *pListParticle;

        const nw4r::ef::EmitterParameter* pLoadEmitter =
            mEmitterParamSave[mBackSaveBuffer == ESaveBuffer_1st
                                  ? ESaveBuffer_2nd
                                  : ESaveBuffer_1st];

        const nw4r::ef::ParticleParameter* pLoadParticle =
            mParticleParamSave[mBackSaveBuffer == ESaveBuffer_1st
                                   ? ESaveBuffer_2nd
                                   : ESaveBuffer_1st];

        nw4r::ef::EmitterParameter* pSaveEmitter =
            mEmitterParamSave[mBackSaveBuffer];

        nw4r::ef::ParticleParameter* pSaveParticle =
            mParticleParamSave[mBackSaveBuffer];

        pListEmitter = &mpMemoryManager->mEmitterOM->mLeasedList;
        pListParticle = &mpMemoryManager->mParticleOM->mLeasedList;

        if (mIsSlowEffect) {
            for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max; i++) {
                mpSlowSystem->Calc(mBaseGroupID | i, false);
            }

            RP_NW4R_LIST_FOREACH (nw4r::ef::Emitter, it, *pListEmitter) {
                std::memcpy(&pSaveEmitter[it->GetObjectIdx()], &it->mParameter,
                            sizeof(nw4r::ef::EmitterParameter));
            }

            RP_NW4R_LIST_FOREACH (nw4r::ef::Particle, it, *pListParticle) {
                std::memcpy(&pSaveParticle[it->GetObjectIdx()], &it->mParameter,
                            sizeof(nw4r::ef::ParticleParameter));
            }
        }

        RP_NW4R_LIST_FOREACH (nw4r::ef::Emitter, it, *pListEmitter) {
            const nw4r::ef::EmitterParameter* pT0 =
                &pLoadEmitter[it->GetObjectIdx()];

            const nw4r::ef::EmitterParameter* pT1 =
                &pSaveEmitter[it->GetObjectIdx()];

            if (it->mTick <= ESaveBuffer_Max - 1) {
                it->mParameter.mComFlags |=
                    nw4r::ef::EmitterDesc::CMN_FLAG_DISABLE_DRAW;

                continue;
            }

            if (it->mTick == ESaveBuffer_Max) {
                it->mParameter.mComFlags &=
                    ~nw4r::ef::EmitterDesc::CMN_FLAG_DISABLE_DRAW;
            }

            // clang-format off
            it->mParameter.mRotate.x = pT0->mRotate.x + (pT1->mRotate.x - pT0->mRotate.x) * mFrame;
            it->mParameter.mRotate.y = pT0->mRotate.y + (pT1->mRotate.y - pT0->mRotate.y) * mFrame;
            it->mParameter.mRotate.z = pT0->mRotate.z + (pT1->mRotate.z - pT0->mRotate.z) * mFrame;

            it->mParameter.mTranslate.x = pT0->mTranslate.x + (pT1->mTranslate.x - pT0->mTranslate.x) * mFrame;
            it->mParameter.mTranslate.y = pT0->mTranslate.y + (pT1->mTranslate.y - pT0->mTranslate.y) * mFrame;
            it->mParameter.mTranslate.z = pT0->mTranslate.z + (pT1->mTranslate.z - pT0->mTranslate.z) * mFrame;

            it->mParameter.mScale.x = pT0->mScale.x + (pT1->mScale.x - pT0->mScale.x) * mFrame;
            it->mParameter.mScale.y = pT0->mScale.y + (pT1->mScale.y - pT0->mScale.y) * mFrame;
            it->mParameter.mScale.z = pT0->mScale.z + (pT1->mScale.z - pT0->mScale.z) * mFrame;
            // clang-format on

            it->SetMtxDirty();
        }

        RP_NW4R_LIST_FOREACH (nw4r::ef::Particle, it, *pListParticle) {
            const nw4r::ef::ParticleParameter* pT0 =
                &pLoadParticle[it->GetObjectIdx()];

            const nw4r::ef::ParticleParameter* pT1 =
                &pSaveParticle[it->GetObjectIdx()];

            if (it->mTick <= 1) {
                continue;
            }

            // clang-format off
            it->mParameter.mScale.x = pT0->mScale.x + (pT1->mScale.x - pT0->mScale.x) * mFrame;
            it->mParameter.mScale.y = pT0->mScale.y + (pT1->mScale.y - pT0->mScale.y) * mFrame;

            it->mParameter.mRotate.x = pT0->mRotate.x + (pT1->mRotate.x - pT0->mRotate.x) * mFrame;
            it->mParameter.mRotate.y = pT0->mRotate.y + (pT1->mRotate.y - pT0->mRotate.y) * mFrame;
            it->mParameter.mRotate.z = pT0->mRotate.z + (pT1->mRotate.z - pT0->mRotate.z) * mFrame;

            for (int i = 0; i < nw4r::ef::TEX_LAYER_MAX; i++) {
                it->mParameter.mTextureScale[i].x = pT0->mTextureScale[i].x + (pT1->mTextureScale[i].x - pT0->mTextureScale[i].x) * mFrame;
                it->mParameter.mTextureScale[i].y = pT0->mTextureScale[i].y + (pT1->mTextureScale[i].y - pT0->mTextureScale[i].y) * mFrame;
            
                it->mParameter.mTextureRotate[i] = pT0->mTextureRotate[i] + (pT1->mTextureRotate[i] - pT0->mTextureRotate[i]) * mFrame;

                it->mParameter.mTextureTranslate[i].x = pT0->mTextureTranslate[i].x + (pT1->mTextureTranslate[i].x - pT0->mTextureTranslate[i].x) * mFrame;
                it->mParameter.mTextureTranslate[i].y = pT0->mTextureTranslate[i].y + (pT1->mTextureTranslate[i].y - pT0->mTextureTranslate[i].y) * mFrame;
            }

            it->mParameter.mVelocity.x = pT0->mVelocity.x + (pT1->mVelocity.x - pT0->mVelocity.x) * mFrame;
            it->mParameter.mVelocity.y = pT0->mVelocity.y + (pT1->mVelocity.y - pT0->mVelocity.y) * mFrame;
            it->mParameter.mVelocity.z = pT0->mVelocity.z + (pT1->mVelocity.z - pT0->mVelocity.z) * mFrame;

            it->mParameter.mPosition.x = pT0->mPosition.x + (pT1->mPosition.x - pT0->mPosition.x) * mFrame;
            it->mParameter.mPosition.y = pT0->mPosition.y + (pT1->mPosition.y - pT0->mPosition.y) * mFrame;
            it->mParameter.mPosition.z = pT0->mPosition.z + (pT1->mPosition.z - pT0->mPosition.z) * mFrame;

            for (int i = 0; i < nw4r::ef::COLOR_LAYER_MAX; i++) {
                for (int j = 0; j < nw4r::ef::COLOR_IDX_MAX; j++) {
                    it->mParameter.mColor[i][j].r = pT0->mColor[i][j].r + (pT1->mColor[i][j].r - pT0->mColor[i][j].r) * mFrame;
                    it->mParameter.mColor[i][j].g = pT0->mColor[i][j].g + (pT1->mColor[i][j].g - pT0->mColor[i][j].g) * mFrame;
                    it->mParameter.mColor[i][j].b = pT0->mColor[i][j].b + (pT1->mColor[i][j].b - pT0->mColor[i][j].b) * mFrame;
                    it->mParameter.mColor[i][j].a = pT0->mColor[i][j].a + (pT1->mColor[i][j].a - pT0->mColor[i][j].a) * mFrame;
                }
            }

            it->mParameter.mMomentum = pT0->mMomentum + (pT1->mMomentum - pT0->mMomentum) * mFrame;
            // clang-format on
        }

        mFrame += mFrameRate;

        if (mFrame >= 1.0f) {
            mIsSlowEffect = true;
            mBackSaveBuffer ^= 1;
            mFrame -= 1.0f;
        } else {
            mIsSlowEffect = false;
        }
    }
}

/**
 * @brief Draws the specified set of effects
 *
 * @param rDrawInfo Graphics configuration
 * @param drawGroup Effect draw group
 * @param drawScene Effect draw scene
 */
void RPSysEffectCreator::draw(const nw4r::ef::DrawInfo& rDrawInfo,
                              u32 drawGroup, u32 drawScene) {

    nw4r::ef::EffectSystem::GetInstance() //
        ->Draw(rDrawInfo, mBaseGroupID | drawScene | drawGroup);

    if (mpSlowSystem != NULL) {
        mpSlowSystem->Draw(rDrawInfo, mBaseGroupID | drawScene | drawGroup);
    }
}
