#include <nw4r/ef.h>
#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace {

NW4R_LIB_VERSION(EF, "Jun  8 2007", "11:16:29", "0x4199_60831");

} // namespace

namespace nw4r {
namespace ef {

static DrawOrder gBasicDrawOrder;
static DrawStrategyBuilder gBasicDrawStrategyBuilder;
static EmitFormBuilder gBasicEmitFormBuilder;

bool EffectSystem::mDisplayVersion = true;
EffectSystem EffectSystem::instance;

EffectSystem::EffectSystem() {
    if (mDisplayVersion) {
        mDisplayVersion = false;
        OSRegisterVersion(NW4R_EF_Version_);
    }

    mMemoryManager = NULL;
    mMaxGroupID = 0;
    mXFFlushSafe = false;
}

EffectSystem::~EffectSystem() {
    for (u32 i = 0; i < mMaxGroupID; i++) {
        RetireEffectAll(i);
    }
}

EffectSystem* EffectSystem::GetInstance() {
    return &instance;
}

bool EffectSystem::Initialize(u32 maxGroupID) {
    mMaxGroupID = maxGroupID;

    mActivityList =
        new (mMemoryManager->AllocHeap(mMaxGroupID * sizeof(ActivityList) + 32))
            ActivityList[mMaxGroupID];

    for (int i = 0; i < mMaxGroupID; i++) {
        mActivityList[i].SetOffset(offsetof(Effect, mActivityLink));
        mActivityList[i].Initialize();
    }

    mRandom.Srand(0);

    mDrawOrderFunc = &gBasicDrawOrder;
    mDrawStrategyBuilder = &gBasicDrawStrategyBuilder;
    mEmitFormBuilder = &gBasicEmitFormBuilder;

    return true;
}

bool EffectSystem::Closing(Effect* pEffect) {
    mActivityList[pEffect->mGroupID].ToClosing(pEffect);
    pEffect->mLifeStatus = ReferencedObject::NW4R_EF_LS_CLOSING;

    return true;
}

Effect* EffectSystem::CreateEffect(const char* pName, u32 groupID,
                                   u16 calcRemain) {

    EmitterResource* pResource =
        Resource::GetInstance()->_FindEmitter(pName, NULL);

    if (pResource == NULL) {
        return NULL;
    }

    Effect* pEffect = GetMemoryManager()->AllocEffect();
    if (pEffect == NULL) {
        return NULL;
    }

    if (!pEffect->Initialize(this, pResource, calcRemain)) {
        GetMemoryManager()->FreeEffect(pEffect);
        return NULL;
    }

    pEffect->mGroupID = groupID;

    mActivityList[groupID].ToActive(pEffect);
    pEffect->mLifeStatus = ReferencedObject::NW4R_EF_LS_ACTIVE;

    mActivityList[groupID].ToWait(pEffect);
    pEffect->mLifeStatus = ReferencedObject::NW4R_EF_LS_WAIT;

    return pEffect;
}

u32 EffectSystem::RetireEffect(Effect* pEffect) {
    if (pEffect->mLifeStatus != ReferencedObject::NW4R_EF_LS_ACTIVE) {
        return 0;
    }

    mActivityList[pEffect->mGroupID].ToWait(pEffect);
    pEffect->Destroy();

    return 1;
}

u32 EffectSystem::RetireEffectAll(u32 groupID) {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_EFFECT];

    u16 size = UtlistToArray(&mActivityList[groupID].mActiveList, pArray,
                             UtlistSize(&mActivityList[groupID].mActiveList));

    for (u16 i = 0; i < size; i++) {
        Effect* pEffect = static_cast<Effect*>(pArray[i]);

        if (pEffect->mLifeStatus == ReferencedObject::NW4R_EF_LS_ACTIVE) {
            num += RetireEffect(pEffect);
        }
    }

    return num;
}

u32 EffectSystem::RetireEmitterAll(u32 groupID) {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_EFFECT];

    u16 size = UtlistToArray(&mActivityList[groupID].mActiveList, pArray,
                             UtlistSize(&mActivityList[groupID].mActiveList));

    for (u16 i = 0; i < size; i++) {
        Effect* pEffect = static_cast<Effect*>(pArray[i]);
        num += pEffect->RetireEmitterAll();
    }

    return num;
}

u32 EffectSystem::RetireParticleAll(u32 groupID) {
    u32 num = 0;
    void* pArray[NW4R_EF_MAX_EFFECT];

    u16 size = UtlistToArray(&mActivityList[groupID].mActiveList, pArray,
                             UtlistSize(&mActivityList[groupID].mActiveList));

    for (u16 i = 0; i < size; i++) {
        Effect* pEffect = static_cast<Effect*>(pArray[i]);
        num += pEffect->RetireParticleAll();
    }

    return num;
}

void EffectSystem::Calc(u32 groupID, bool onlyBillboard) {
    void* pArray[NW4R_EF_MAX_EFFECT];

    u16 size = UtlistToArray(&mActivityList[groupID].mActiveList, pArray,
                             UtlistSize(&mActivityList[groupID].mActiveList));

    for (u16 i = 0; i < size; i++) {
        Effect* pEffect = static_cast<Effect*>(pArray[i]);
        pEffect->Calc(onlyBillboard);
    }

    mMemoryManager->GarbageCollection();
}

void EffectSystem::Draw(const DrawInfo& rInfo, u32 groupID) {
    Effect* pIt = NULL;

    while ((pIt = static_cast<Effect*>(ut::List_GetNext(
                &mActivityList[groupID].mActiveList, pIt))) != NULL) {

        pIt->Draw(rInfo);
    }
}

} // namespace ef
} // namespace nw4r
