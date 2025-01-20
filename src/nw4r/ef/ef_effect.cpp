#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

Effect::Effect() : mActivityList(offsetof(Emitter, mActivityLink)) {
    ut::List_Init(&mParticleManager, offsetof(ParticleManager, mDrawOrderLink));
}

Effect::~Effect() {
    RetireEmitterAll();
}

bool Effect::Initialize(EffectSystem* pSystem, EmitterResource* pResource,
                        u16 calcRemain) {

    ReferencedObject::Initialize();

    mActivityList.Initialize();

    mDrawOrderFunc = pSystem->mDrawOrderFunc;
    math::MTX34Identity(&mRootMtx);
    mManagerES = pSystem;

    mCallBack.mPrevEmission = NULL;
    mCallBack.mPrevPtclCalc = NULL;
    mCallBack.mPostPtclCalc = NULL;

    mFlags = 0;

    mVelocity.x = 0.0f;
    mVelocity.y = 0.0f;
    mVelocity.z = 0.0f;

    Emitter* pEmitter = pSystem->GetMemoryManager()->AllocEmitter();
    if (pEmitter == NULL) {
        return false;
    }

    if (!pEmitter->Initialize(this, pResource, 128)) {
        pSystem->GetMemoryManager()->FreeEmitter(pEmitter);
        return false;
    }

    mActivityList.ToActive(pEmitter);
    pEmitter->mLifeStatus = NW4R_EF_LS_ACTIVE;

    pEmitter->mCalcRemain += calcRemain;

    return true;
}

void Effect::SendClosing() {
    mManagerES->Closing(this);
}

void Effect::DestroyFunc() {
    RetireEmitterAll();
}

bool Effect::Closing(Emitter* pEmitter) {
    if (pEmitter->mParent != NULL) {
        pEmitter->mParent->UnRef();
    }

    if (pEmitter->mpReferenceParticle != NULL) {
        pEmitter->mpReferenceParticle->UnRef();
        pEmitter->mpReferenceParticle = NULL;
    }

    pEmitter->mManagerEF->UnRef();

    mActivityList.ToClosing(pEmitter);
    pEmitter->mLifeStatus = NW4R_EF_LS_CLOSING;

    return true;
}

Emitter* Effect::CreateEmitter(EmitterResource* pResource, u8 drawWeight,
                               u16 calcRemain) {

    Emitter* pEmitter = mManagerES->GetMemoryManager()->AllocEmitter();
    if (pEmitter == NULL) {
        return false;
    }

    if (!pEmitter->Initialize(this, pResource, drawWeight)) {
        mManagerES->GetMemoryManager()->FreeEmitter(pEmitter);
        return false;
    }

    mActivityList.ToActive(pEmitter);
    pEmitter->mLifeStatus = NW4R_EF_LS_ACTIVE;

    pEmitter->mCalcRemain += calcRemain;

    return pEmitter;
}

u32 Effect::RetireEmitter(Emitter* pEmitter) {
    if (pEmitter->mLifeStatus != NW4R_EF_LS_ACTIVE) {
        return 0;
    }

    mActivityList.ToWait(pEmitter);
    pEmitter->Destroy();
    return 1;
}

u32 Effect::RetireEmitterAll() {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_EMITTER];

    u16 size = UtlistToArray(&mActivityList.mActiveList, pArray,
                             UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < size; i++) {
        Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);

        if (pEmitter->mLifeStatus == NW4R_EF_LS_ACTIVE) {
            num += RetireEmitter(pEmitter);
        }
    }

    return num;
}

u32 Effect::RetireParticleAll() {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_EMITTER];

    u16 size = UtlistToArray(&mActivityList.mActiveList, pArray,
                             UtlistSize(&mActivityList.mActiveList));

    for (u16 i = 0; i < size; i++) {
        Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);
        num += pEmitter->RetireParticleAll();
    }

    return num;
}

void Effect::Calc(bool onlyBillboard) {
    if (onlyBillboard) {
        NW4R_UT_LIST_FOREACH (Emitter, it, mActivityList.mActiveList, {
            if (it->mLifeStatus == NW4R_EF_LS_ACTIVE ||
                it->mLifeStatus == NW4R_EF_LS_WAIT) {

                if (!(it->mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_16) &&
                    !(it->mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_15)) {
                    continue;
                }

                it->CalcBillboard();
            }
        });

        return;
    }

    if (GetFlagDisableCalc()) {
        return;
    }

    NW4R_UT_LIST_FOREACH (Emitter, pEmitter, mActivityList.mActiveList, {
        if (pEmitter->mLifeStatus == NW4R_EF_LS_ACTIVE ||
            pEmitter->mLifeStatus == NW4R_EF_LS_WAIT) {

            if (pEmitter->mEvalStatus == NW4R_EF_ES_DONE) {
                pEmitter->mEvalStatus = NW4R_EF_ES_WAIT;
            }
        }

        NW4R_UT_LIST_FOREACH (ParticleManager, pManager, pEmitter->mActivityList.mActiveList,
                              { pManager->BeginCalc(false); });
    });

    SetFlagExistCalcRemain(true);

    while (GetFlagExistCalcRemain()) {
        void* pArray[NW4R_EF_MAX_EMITTER];

        SetFlagExistCalcRemain(false);

        while (true) {
            {
                u16 size =
                    UtlistToArray(&mActivityList.mActiveList, pArray,
                                  UtlistSize(&mActivityList.mActiveList));

                for (u16 i = 0; i < size; i++) {
                    Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);
                    pEmitter->CalcEmitter();
                }
            }

            NW4R_UT_LIST_FOREACH (Emitter, it, mActivityList.mActiveList, {
                if (it->mLifeStatus == NW4R_EF_LS_ACTIVE ||
                    it->mLifeStatus == NW4R_EF_LS_WAIT) {

                    if (!(it->mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_16) &&
                        !(it->mParameter.mEmitFlags & EmitterDesc::EMIT_FLAG_15)) {
                        continue;
                    }

                    it->CalcBillboard();
                }
            });

            {
                u16 size =
                    UtlistToArray(&mActivityList.mActiveList, pArray,
                                  UtlistSize(&mActivityList.mActiveList));

                for (u16 i = 0; i < size; i++) {
                    Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);

                    if (pEmitter->mEvalStatus == NW4R_EF_ES_WAIT) {
                        pEmitter->mTick++;
                    }

                    pEmitter->CalcParticle();

                    if (pEmitter->mEvalStatus == NW4R_EF_ES_WAIT) {
                        pEmitter->mTick--;
                    }
                }
            }

            {
                u16 size =
                    UtlistToArray(&mActivityList.mActiveList, pArray,
                                  UtlistSize(&mActivityList.mActiveList));

                for (u16 i = 0; i < size; i++) {
                    Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);
                    pEmitter->CalcEmission();
                }
            }

            {
                u16 size =
                    UtlistToArray(&mActivityList.mActiveList, pArray,
                                  UtlistSize(&mActivityList.mActiveList));

                for (u16 i = 0; i < size; i++) {
                    Emitter* pEmitter = static_cast<Emitter*>(pArray[i]);
                    pEmitter->CalcParticle();
                }
            }

            if (mManagerES->mCreationQueue.IsEmpty()) {
                break;
            }

            mManagerES->mCreationQueue.Execute();
        }

        if (GetFlagExistCalcRemain()) {
            NW4R_UT_LIST_FOREACH (Emitter, pEmitter, mActivityList.mActiveList, {
                if (pEmitter->mLifeStatus == NW4R_EF_LS_ACTIVE &&
                    pEmitter->mCalcRemain != 0) {

                    if (pEmitter->mCalcRemain != 0) {
                        pEmitter->mCalcRemain--;
                    }

                    if (pEmitter->mEvalStatus == NW4R_EF_ES_DONE) {
                        pEmitter->mEvalStatus = NW4R_EF_ES_WAIT;
                    }
                }

                NW4R_UT_LIST_FOREACH (ParticleManager, pManager, pEmitter->mActivityList.mActiveList,
                                      { pManager->BeginCalc(true); });
            });
        }
    }

    NW4R_UT_LIST_FOREACH (Emitter, pEmitter, mActivityList.mActiveList, {
        if (pEmitter->mLifeStatus == NW4R_EF_LS_ACTIVE ||
            pEmitter->mLifeStatus == NW4R_EF_LS_WAIT) {

            if (pEmitter->mEvalStatus == NW4R_EF_ES_SKIP) {
                pEmitter->mEvalStatus = NW4R_EF_ES_DONE;
            }
        }

        NW4R_UT_LIST_FOREACH (ParticleManager, pManager, pEmitter->mActivityList.mActiveList,
                              { pManager->EndCalc(); });
    });
}

void Effect::Draw(const DrawInfo& rInfo) {
    if (GetFlagDisableDraw()) {
        return;
    }

    mDrawOrderFunc->Draw(this, rInfo);
}

u16 Effect::GetNumEmitter() const {
    return UtlistSize(&mActivityList.mActiveList);
}

Emitter* Effect::GetEmitter(u16 idx) {
    return static_cast<Emitter*>(
        ut::List_GetNth(&mActivityList.mActiveList, idx));
}

/******************************************************************************
 *
 * For-each implementation
 *
 ******************************************************************************/
u32 Effect::ForeachParticleManager(ForEachFunc pFunc, ForEachParam param,
                                   bool ignoreLifeStatus) {
    u32 calls = 0;

    NW4R_UT_LIST_FOREACH_SAFE (Emitter, it, mActivityList.mActiveList, {
        calls += it->ForeachParticleManager(pFunc, param, ignoreLifeStatus, false);
    });

    return calls;
}

u32 Effect::ForeachEmitterFrom(ForEachFunc pFunc, ForEachParam param,
                               bool ignoreLifeStatus, Emitter* pEmitter) {
    u32 calls = 0;

    NW4R_UT_LIST_FOREACH_SAFE (Emitter, it, mActivityList.mActiveList, {
        if (!ignoreLifeStatus && it->mLifeStatus != NW4R_EF_LS_ACTIVE) {
            continue;
        }

        bool isChild = false;
        Emitter* pSearch = it;

        // Only apply function to effects owned by the specified emitter
        while (!isChild && (pSearch = pSearch->mParent) != NULL) {
            if (pSearch == pEmitter) {
                isChild = true;
            }
        }

        if (isChild) {
            pFunc(it, param);
            calls++;
        }
    });

    return calls;
}

void Effect::SetRootMtx(const math::MTX34& rMtx) {
    math::MTX34Copy(&mRootMtx, &rMtx);

    NW4R_UT_LIST_FOREACH (Emitter, it, mActivityList.mActiveList, {
        if (it->mParent == NULL) {
            it->SetMtxDirty();
        }
    });
}

} // namespace ef
} // namespace nw4r
