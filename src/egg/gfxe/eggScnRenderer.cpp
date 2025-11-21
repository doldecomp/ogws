#include "eggScnRenderer.h"
#include "eggDrawPathBase.h"
#include "eggDrawPathLightMap.h"
#include "eggDrawPathShadowVolume.h"
#include "eggDrawPathHDR.h"
#include "eggDrawPathBloom.h"
#include "eggDrawPathDOF.h"
#include "g3d_scnroot.h"

namespace EGG
{
    using namespace nw4r;

    ScnRenderer::ScnRenderer(g3d::ScnRoot *pScnRoot) :
        ScnRootEx(pScnRoot),
        mppPathSet(NULL),
        mpTimingPrioritySet(NULL),
        mFlags(RENDERER_VISIBLE)
    {
    }

    ScnRenderer::~ScnRenderer()
    {
        #line 102
        EGG_ASSERT(mppPathSet);

        for (int i = 0; i < getNumDrawPath(); i++)
        {
            if (mppPathSet[i] != NULL)
            {
                delete mppPathSet[i];
                mppPathSet[i] = NULL;
            }
        }

        delete mppPathSet;
        mppPathSet = NULL;

        delete mpTimingPrioritySet;
        mpTimingPrioritySet = NULL;
    }

    u16 ScnRenderer::getNumDrawPath() const
    {
        return DRAW_PATH_MAX;
    }

    void ScnRenderer::configure()
    {
        #line 122
        EGG_ASSERT(mppPathSet == NULL);
        
        mppPathSet = new DrawPathBase*[getNumDrawPath()];
        for (int i = 0; i < getNumDrawPath(); i++)
        {
            mppPathSet[i] = NULL;
        }

        mpTimingPrioritySet = new TimingPriority[getNumTiming()];
        for (u16 i = 0; i < getNumTiming(); i++)
        {
            TimingPriority *timing = &mpTimingPrioritySet[i];
            timing->localPrio = 0;
            timing->prioMax = 0;
            timing->opa = true;

            switch(i)
            {
                case 0:
                    timing->localPrio = 1;
                    timing->prioMax = 24;
                    break;
                case 1:
                    timing->localPrio = 27;
                    timing->prioMax = 50;
                    break;
                case 2:
                    timing->localPrio = 52;
                    timing->prioMax = 75;
                    break;
                case 3:
                    timing->localPrio = 77;
                    timing->prioMax = 100;
                    break;
                case 4:
                    timing->localPrio = 0;
                    timing->prioMax = 23;
                    timing->opa = false;
                    break;
                case 5:
                    timing->localPrio = 25;
                    timing->prioMax = 48;
                    timing->opa = false;
                    break;
                case 6:
                    timing->localPrio = 58;
                    timing->prioMax = 81;
                    timing->opa = false;
                    break;
                default:
                    #line 186
                    EGG_ASSERT(0);
                    break;
            }
        }
    }

    u16 ScnRenderer::getNumTiming() const
    {
        return NUM_TIMING;
    }

    void ScnRenderer::createPath(u32 type, MEMAllocator *allocator)
    {
        #line 200
        EGG_ASSERT(mppPathSet != NULL);

        for (u16 i = 0; i < getNumDrawPath(); i++)
        {
            if ((type & 1 << i) == 0) continue;

            switch(i)
            {
                case DRAW_PATH_LMAP:
                    mppPathSet[i] = new DrawPathLightMap();
                    break;
                case DRAW_PATH_SV:
                    mppPathSet[i] = new DrawPathShadowVolume();
                    break;
                case DRAW_PATH_HDR:
                    mppPathSet[i] = new DrawPathHDR();
                    break;
                case DRAW_PATH_BLOOM:
                    mppPathSet[i] = new DrawPathBloom();
                    break;
                case DRAW_PATH_DOF:
                    mppPathSet[i] = new DrawPathDOF();
                    break;
            }
            
            #line 235
            EGG_ASSERT(getDrawPathBase( i ));

            DrawPathBase *path = getDrawPathBase(i);
            const int numScnProc = path->getNumScnProc();
            path->createScnProc(numScnProc, allocator);

            switch(i)
            {
                case DRAW_PATH_LMAP:
                    path->setPriorityScnProc(0, 0, true);
                    path->setPriorityScnProc(1, 25, true);
                    path->setPriorityScnProc(2, 24, false);
                    path->setPriorityScnProc(3, 49, false);
                    break;
                case DRAW_PATH_SV:
                    path->setPriorityScnProc(0, 26, true);
                    path->setPriorityScnProc(1, 51, true);
                    path->setPriorityScnProc(2, 76, true);
                    break;
                case DRAW_PATH_HDR:
                    path->setPriorityScnProc(0, 50, false);
                    path->setPriorityScnProc(1, 53, false);
                    break;
                case DRAW_PATH_BLOOM:
                    path->setPriorityScnProc(0, 51, false);
                    path->setPriorityScnProc(1, 54, false);
                    path->setPriorityScnProc(2, 57, false);
                    break;
                case DRAW_PATH_DOF:
                    path->setPriorityScnProc(0, 52, false);
                    path->setPriorityScnProc(1, 55, false);
                    path->setPriorityScnProc(2, 56, false);
                    break;
            }
        }

        if (getDrawPathBase(DRAW_PATH_BLOOM) != NULL)
        {
            if (getDrawPathBase(DRAW_PATH_SV) != NULL)
            {
            }
        }

        mDrawSettings &= ~DRAW_ALPHA_UPDATE_XLU;
    }

    void ScnRenderer::pushBackDrawPath()
    {
        for(u16 i = 0; i < getNumDrawPath(); i++)
        {
            if (mppPathSet[i] != NULL)
                mppPathSet[i]->pushBackToScnGroup(mBase);
        }
    }

    void ScnRenderer::changeScnRoot(g3d::ScnRoot *pScnRoot)
    {
        #line 328
        EGG_ASSERT(pScnRoot != NULL);

        if (pScnRoot != mBase)
        {
            for (u16 i = 0; i < getNumDrawPath(); i++)
            {
                if (mppPathSet[i] != NULL)
                    mppPathSet[i]->removeFromScnGroup(mBase);
            }

            ScnRootEx::changeScnRoot(pScnRoot);

            for (u16 i = 0; i < getNumDrawPath(); i++)
            {
                if (mppPathSet[i] != NULL)
                    mppPathSet[i]->pushBackToScnGroup(mBase);
            }
        }
    }

    namespace
    {
        void UNUSED_ASSERTS_SCNRENDERER()
        {
            EGG_ASSERT_MSG(false, "pObj");
            EGG_ASSERT_MSG(false, "This timing is not opa.");
            EGG_ASSERT_MSG(false, "Local priority range over.");
            EGG_ASSERT_MSG(false, "This timing is not xlu.");
        }
    }

    u16 ScnRenderer::getLocalPriorityMax() const
    {
        return LOCAL_PRIO_MAX;
    }

    void ScnRenderer::setLocalPriorityScnProc(IScnProc *pScnProc, u32 timing, u8 basePrio, u16 procIndex) const
    {
        #line 394
        EGG_ASSERT(pScnProc);

        u8 localPrio, prioMax;
        bool opa = getTimingPriority(timing, &localPrio, &prioMax);

        #line 397
        EGG_ASSERT_MSG(localPrio + basePrio <= prioMax, "Local priority range over.");
        pScnProc->setPriorityScnProc(procIndex, localPrio + basePrio, opa);
    }

    void ScnRenderer::calc_after_CalcWorld()
    {
        ScnRootEx::calc_after_CalcWorld();

        for (u16 i = 0; i < getNumDrawPath(); i++)
        {
            if (mppPathSet[i] != NULL && mppPathSet[i]->isVisible())
                mppPathSet[i]->calc_after_CalcWorld();
        }
    }

    void ScnRenderer::draw_before_CalcView()
    {
        ScnRootEx::draw_before_CalcView();

        if (isVisible())
        {
            if (getDrawPathBase(DRAW_PATH_BLOOM) != NULL)
            {
                if (getDrawPathBase(DRAW_PATH_DOF) != NULL)
                {
                    if (getDrawPathBase(DRAW_PATH_DOF)->isVisible())
                    {
                        DrawPathBloom *bloom = (DrawPathBloom *)getDrawPathBase(DRAW_PATH_BLOOM);
                        bloom->setFlag(0x8);
                        goto clean;
                    }
                }

                DrawPathBloom *bloom = (DrawPathBloom *)getDrawPathBase(DRAW_PATH_BLOOM);
                bloom->clearFlag(0x8);
            }
        }

    clean:
        ScreenEffectBase::clean();
        for (u16 i = 0; i < getNumDrawPath(); i++)
        {
            if (mppPathSet[i] != NULL)
                mppPathSet[i]->CopyGlobalScreen();
        }
    }
}
