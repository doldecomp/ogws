#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

namespace EGG {

ScnRenderer::ScnRenderer(nw4r::g3d::ScnRoot* pScnRoot)
    : ScnRootEx(pScnRoot),
      mppPathSet(NULL),
      mpTimingPrioritySet(NULL),
      mFlags(cFlag_Visible) {}

ScnRenderer::~ScnRenderer() {
#line 102
    EGG_ASSERT(mppPathSet);

    for (int i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL) {
            delete mppPathSet[i];
            mppPathSet[i] = NULL;
        }
    }

    delete mppPathSet;
    mppPathSet = NULL;

    delete mpTimingPrioritySet;
    mpTimingPrioritySet = NULL;
}

u16 ScnRenderer::getNumDrawPath() const {
    return cDrawPath_Max;
}

void ScnRenderer::configure() {
#line 122
    EGG_ASSERT(mppPathSet == NULL);

    mppPathSet = new DrawPathBase*[getNumDrawPath()];

    for (int i = 0; i < getNumDrawPath(); i++) {
        mppPathSet[i] = NULL;
    }

    mpTimingPrioritySet = new TimingPriority[getNumTiming()];

    for (u16 i = 0; i < getNumTiming(); i++) {
        TimingPriority& rTiming = mpTimingPrioritySet[i];
        rTiming.prioMin = 0;
        rTiming.prioMax = 0;
        rTiming.opa = true;

        switch (i) {
        case cTiming_Opa1st: {
            rTiming.prioMin = PRIO_OPA_1ST;
            rTiming.prioMax = PRIO_OPA_1ST + LOCAL_PRIO_MAX;
            break;
        }

        case cTiming_Opa2nd: {
            rTiming.prioMin = PRIO_OPA_2ND;
            rTiming.prioMax = PRIO_OPA_2ND + LOCAL_PRIO_MAX;
            break;
        }

        case cTiming_Opa3rd: {
            rTiming.prioMin = PRIO_OPA_3RD;
            rTiming.prioMax = PRIO_OPA_3RD + LOCAL_PRIO_MAX;
            break;
        }

        case cTiming_Opa4th: {
            rTiming.prioMin = PRIO_OPA_4TH;
            rTiming.prioMax = PRIO_OPA_4TH + LOCAL_PRIO_MAX;
            break;
        }

        case cTiming_Xlu1st: {
            rTiming.prioMin = PRIO_XLU_1ST;
            rTiming.prioMax = PRIO_XLU_1ST + LOCAL_PRIO_MAX;
            rTiming.opa = false;
            break;
        }

        case cTiming_Xlu2nd: {
            rTiming.prioMin = PRIO_XLU_2ND;
            rTiming.prioMax = PRIO_XLU_2ND + LOCAL_PRIO_MAX;
            rTiming.opa = false;
            break;
        }

        case cTiming_Xlu3rd: {
            rTiming.prioMin = PRIO_XLU_3RD;
            rTiming.prioMax = PRIO_XLU_3RD + LOCAL_PRIO_MAX;
            rTiming.opa = false;
            break;
        }

        default: {
#line 186
            EGG_ASSERT(0);
            break;
        }
        }
    }
}

u16 ScnRenderer::getNumTiming() const {
    return cTiming_Max;
}

void ScnRenderer::createPath(u32 createFlags, MEMAllocator* pAllocator) {
#line 200
    EGG_ASSERT(mppPathSet != NULL);

    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (!(createFlags & 1 << i)) {
            continue;
        }

        switch (i) {
        case cDrawPath_XluSnap: {
            mppPathSet[i] = new DrawPathXluSnap();
            break;
        }

        case cDrawPath_SV: {
            mppPathSet[i] = new DrawPathShadowVolume();
            break;
        }

        case cDrawPath_HDR: {
            mppPathSet[i] = new DrawPathHDR();
            break;
        }

        case cDrawPath_Bloom: {
            mppPathSet[i] = new DrawPathBloom();
            break;
        }

        case cDrawPath_DOF: {
            mppPathSet[i] = new DrawPathDOF();
            break;
        }
        }

#line 235
        EGG_ASSERT(getDrawPathBase( i ));

        DrawPathBase* pPath = getDrawPathBase(i);
        pPath->createScnProc(pPath->getNumStep(), pAllocator);

        switch (i) {
        case cDrawPath_XluSnap: {
            // clang-format off
            pPath->setPriorityScnProc(DrawPathXluSnap::cStep_0, 0,  true);
            pPath->setPriorityScnProc(DrawPathXluSnap::cStep_1, 25, true);
            pPath->setPriorityScnProc(DrawPathXluSnap::cStep_2, 24, false);
            pPath->setPriorityScnProc(DrawPathXluSnap::cStep_3, 49, false);
            // clang-format on
            break;
        }

        case cDrawPath_SV: {
            // clang-format off
            pPath->setPriorityScnProc(DrawPathShadowVolume::cStep_0, 26, true);
            pPath->setPriorityScnProc(DrawPathShadowVolume::cStep_1, 51, true);
            pPath->setPriorityScnProc(DrawPathShadowVolume::cStep_2, 76, true);
            // clang-format on
            break;
        }

        case cDrawPath_HDR: {
            // clang-format off
            pPath->setPriorityScnProc(DrawPathHDR::cStep_Capture, 50, false);
            pPath->setPriorityScnProc(DrawPathHDR::cStep_Draw,    53, false);
            // clang-format on
            break;
        }

        case cDrawPath_Bloom: {
            // clang-format off
            pPath->setPriorityScnProc(DrawPathBloom::cStep_0, 51, false);
            pPath->setPriorityScnProc(DrawPathBloom::cStep_1, 54, false);
            pPath->setPriorityScnProc(DrawPathBloom::cStep_2, 57, false);
            // clang-format on
            break;
        }

        case cDrawPath_DOF: {
            // clang-format off
            pPath->setPriorityScnProc(DrawPathDOF::cStep_0, 52, false);
            pPath->setPriorityScnProc(DrawPathDOF::cStep_1, 55, false);
            pPath->setPriorityScnProc(DrawPathDOF::cStep_2, 56, false);
            // clang-format on
            break;
        }
        }
    }

    if (getDrawPathBase(cDrawPath_Bloom) != NULL) {
        if (getDrawPathBase(cDrawPath_SV) != NULL) {
            // unused
        }
    }

    mDrawSettings &= ~cDrawSetting_AlphaUpdateXlu;
}

void ScnRenderer::pushBackDrawPath() {
    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL) {
            mppPathSet[i]->pushBackToScnGroup(mpScnRoot);
        }
    }
}

void ScnRenderer::changeScnRoot(nw4r::g3d::ScnRoot* pScnRoot) {
#line 328
    EGG_ASSERT(pScnRoot != NULL);

    if (pScnRoot == mpScnRoot) {
        return;
    }

    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL) {
            mppPathSet[i]->removeFromScnGroup(mpScnRoot);
        }
    }

    ScnRootEx::changeScnRoot(pScnRoot);

    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL) {
            mppPathSet[i]->pushBackToScnGroup(mpScnRoot);
        }
    }
}

DECOMP_FORCEACTIVE(eggScnRenderer_cpp,
                  "pObj",
                  "This timing is not opa.",
                  "Local priority range over.",
                  "This timing is not xlu.");

u16 ScnRenderer::getLocalPriorityMax() const {
    return LOCAL_PRIO_MAX;
}

void ScnRenderer::setLocalPriorityScnProc(IScnProc* pScnProc, u32 timing,
                                          u8 prio, u16 procIndex) const {
#line 394
    EGG_ASSERT(pScnProc);

    u8 prioMin, prioMax;
    bool opa = getTimingPriorityRange(timing, &prioMin, &prioMax);

#line 397
    EGG_ASSERT_MSG(prioMin + prio <= prioMax, "Local priority range over.");
    pScnProc->setPriorityScnProc(procIndex, prioMin + prio, opa);
}

void ScnRenderer::calc_after_CalcWorld() {
    ScnRootEx::calc_after_CalcWorld();

    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL && mppPathSet[i]->isEnable()) {
            mppPathSet[i]->internalResetForDraw();
        }
    }
}

void ScnRenderer::draw_before_CalcView() {
    ScnRootEx::draw_before_CalcView();

    if (isVisible() && getDrawPathBase(cDrawPath_Bloom) != NULL) {
        if (getDrawPathBase(cDrawPath_DOF) != NULL &&
            getDrawPathBase(cDrawPath_DOF)->isEnable()) {

            static_cast<DrawPathBloom*>(getDrawPathBase(cDrawPath_Bloom))
                ->setFlag8();
        } else {

            static_cast<DrawPathBloom*>(getDrawPathBase(cDrawPath_Bloom))
                ->clearFlag8();
        }
    }

    ScreenEffectBase::Clean();

    for (u16 i = 0; i < getNumDrawPath(); i++) {
        if (mppPathSet[i] != NULL) {
            mppPathSet[i]->calc();
        }
    }
}

} // namespace EGG
