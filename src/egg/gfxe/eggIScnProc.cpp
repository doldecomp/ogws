#include <egg/core.h>
#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

namespace EGG {

IScnProc::IScnProc() : mpDataSet(NULL), mNumScnProc(0) {}

IScnProc::~IScnProc() {
#line 28
    EGG_ASSERT(mpDataSet != NULL);

    for (int i = 0; i < getNumScnProc(); i++) {
        mpDataSet[i].mpScnProc->Destroy();
        mpDataSet[i].mpScnProc = NULL;
    }

    delete mpDataSet;
    mpDataSet = NULL;
}

void IScnProc::createScnProc(u16 procNum, MEMAllocator* pAllocator) {
#line 47
    EGG_ASSERT(mpDataSet == NULL);
    EGG_ASSERT(procNum > 0);

    mNumScnProc = procNum;
    mpDataSet = new ProcData[procNum];

    for (u16 i = 0; i < getNumScnProc(); i++) {
        u32 size;

        // clang-format off
        mpDataSet[i].mpScnProc = nw4r::g3d::ScnProc::Construct(
            pAllocator == NULL ? G3DUtility::getAllocator() : pAllocator,
            &size,
            IScnProc::drawProcFunc,
            true,
            false);
        // clang-format on

        mpDataSet[i].mpScnProc->SetUserData(&mpDataSet[i]);
        mpDataSet[i].mStep = i;
        mpDataSet[i].mpThis = this;
        mpDataSet[i].mOpa = true;

        setPriorityScnProc(i, i, true);
    }
}

void IScnProc::setPriorityScnProc(u16 procIndex, u8 priority, bool opa) {
#line 80
    EGG_ASSERT(procIndex < getNumScnProc());

    nw4r::g3d::ScnProc* pScnProc = getData(procIndex)->mpScnProc;

    if (opa) {
        pScnProc->SetDrawProc(IScnProc::drawProcFunc, true, false);
        pScnProc->SetPriorityDrawOpa(priority);
    } else {
        pScnProc->SetDrawProc(IScnProc::drawProcFunc, false, true);
        pScnProc->SetPriorityDrawXlu(priority);
    }

    mpDataSet[procIndex].mOpa = opa;
}

void IScnProc::pushBackToScnGroup(nw4r::g3d::ScnGroup* pScnGroup) {
#line 125
    EGG_ASSERT(pScnGroup);

    for (u16 i = 0; i < getNumScnProc(); i++) {
        bool is_push_back =
            pScnGroup->Insert(pScnGroup->Size(), getData(i)->mpScnProc);

#line 129
        EGG_ASSERT(is_push_back);
    }
}

void IScnProc::removeFromScnGroup(nw4r::g3d::ScnGroup* pScnGroup) {
#line 140
    EGG_ASSERT(pScnGroup);

    for (u16 i = 0; i < getNumScnProc(); i++) {
        bool is_remove = pScnGroup->Remove(getData(i)->mpScnProc);

#line 144
        EGG_ASSERT(is_remove);
    }
}

DECOMP_FORCEACTIVE(eggIScnProc_cpp,
                  "m");

void IScnProc::drawProcFunc(nw4r::g3d::ScnProc* pScnProc, bool opa) {
#line 184
    EGG_ASSERT(pScnProc);

    ProcData* p_data = static_cast<ProcData*>(pScnProc->GetUserData());
#line 186
    EGG_ASSERT(p_data);
    EGG_ASSERT(p_data->mpThis);

    setDrawSettingGX(opa);

    p_data->mpThis->scnProcDraw(p_data->mStep);
    StateGX::resetStateCache();

    setDrawSettingGX(opa);
}

} // namespace EGG
