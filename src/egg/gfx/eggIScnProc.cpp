#include "eggIScnProc.h"
#include "eggHeap.h"
#include "eggG3DUtility.h"
#include "eggGXUtility.h"
#include "eggStateGX.h"
#include "g3d_scnproc.h"

namespace EGG
{
    IScnProc::IScnProc()
    {
        mpDataSet = NULL;
        mNumScnProc = 0;
    }

    IScnProc::~IScnProc()
    {
        #line 28
        EGG_ASSERT(mpDataSet != NULL);

        for (int i = 0; i < getNumScnProc(); i++)
        {
            mpDataSet[i].mpScnProc->Destroy();
            mpDataSet[i].mpScnProc = NULL;
        }

        delete mpDataSet;
        mpDataSet = NULL;
    }

    void IScnProc::createScnProc(u16 procNum, MEMAllocator *pAllocator)
    {
        #line 47
        EGG_ASSERT(mpDataSet == NULL);
        EGG_ASSERT(procNum > 0);

        mNumScnProc = procNum;
        mpDataSet = new ProcData[procNum];

        for (u16 i = 0; i < getNumScnProc(); i++)
        {
            u32 sp8;
            MEMAllocator *allocator = (pAllocator == NULL) ? G3DUtility::getAllocator() : pAllocator;

            mpDataSet[i].mpScnProc = nw4r::g3d::ScnProc::Construct(allocator, &sp8,
                IScnProc::drawProcFunc, true, false, 0);

            mpDataSet[i].mpScnProc->SetUserData(&mpDataSet[i]);
            mpDataSet[i].mIndex = i;
            mpDataSet[i].mpThis = this;
            mpDataSet[i].bUseOpa = true;

            setPriorityScnProc(i, i, true);
        }
    }

    void IScnProc::setPriorityScnProc(u16 procIndex, u8 priority, bool bUseOpa)
    {
        #line 80
        EGG_ASSERT(procIndex < getNumScnProc());

        nw4r::g3d::ScnProc *pScnProc = getData(procIndex)->mpScnProc;
        if (bUseOpa)
        {
            pScnProc->SetDrawProc(IScnProc::drawProcFunc, true, false);
            pScnProc->SetPriorityDrawOpa(priority);
        }
        else
        {
            pScnProc->SetDrawProc(IScnProc::drawProcFunc, false, true);
            pScnProc->SetPriorityDrawXlu(priority);
        }

        mpDataSet[procIndex].bUseOpa = bUseOpa;
    }

    void IScnProc::pushBackToScnGroup(nw4r::g3d::ScnGroup *pScnGroup)
    {
        #line 125
        EGG_ASSERT(pScnGroup);

        for (u16 i = 0; i < getNumScnProc(); i++)
        {
            bool is_push_back = pScnGroup->Insert(
                pScnGroup->Size(), getData(i)->mpScnProc);

            #line 129
            EGG_ASSERT(is_push_back);
        }
    }

    void IScnProc::removeFromScnGroup(nw4r::g3d::ScnGroup *pScnGroup)
    {
        #line 140
        EGG_ASSERT(pScnGroup);

        for (u16 i = 0; i < getNumScnProc(); i++)
        {
            bool is_remove = pScnGroup->Remove(getData(i)->mpScnProc);

            #line 144
            EGG_ASSERT(is_remove);
        }
    }

    namespace
    {
        void UNUSED_ASSERTS_ISCNPROC()
        {
            EGG_ASSERT_MSG(false, "m");
        }
    }

    void IScnProc::drawProcFunc(nw4r::g3d::ScnProc *pScnProc, bool b)
    {
        #line 184
        EGG_ASSERT(pScnProc);
        ProcData *p_data = (ProcData *)pScnProc->GetUserData();
        EGG_ASSERT(p_data);
        EGG_ASSERT(p_data->mpThis);

        GXUtility::setScreenProjection(b);

        p_data->mpThis->doDraw(p_data->mIndex);
        StateGX::resetStateCache();

        GXUtility::setScreenProjection(b);
    }
}
