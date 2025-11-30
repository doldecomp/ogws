#include <homeButtonMiniLib.h>

#include <nw4r/lyt.h>
#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/KPAD.h>
#include <revolution/MEM.h>
#include <revolution/MTX.h>

namespace homebutton {
namespace gui {

u32 PaneManager::suIDCounter = 0;

static bool is_visible(nw4r::lyt::Pane* pPane);

void drawLine_(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 uWidth,
               GXColor& rColor) {
    static const f32 cubeScale = 1.0f;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    GXSetCullMode(GX_CULL_NONE);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, false, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);

    Mtx modelMtx;
    PSMTXTrans(modelMtx, 0.0f, 0.0f, 0.0f);
    GXLoadPosMtxImm(modelMtx, GX_PNMTX0);

    GXSetLineWidth(uWidth, 0);

    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    {
        GXPosition3f32(x0, y0, z);
        GXColor1u32(*reinterpret_cast<u32*>(&rColor));

        GXPosition3f32(x1, y1, z);
        GXColor1u32(*reinterpret_cast<u32*>(&rColor));
    }
    GXEnd();
}

bool Component::update(int i, f32 x, f32 y, u32 /* uTrigFlag */,
                       u32 /* uHoldFlag */, u32 /* uReleaseFlag */,
                       void* pData) {
    bool bTouched = false;

    if (isVisible()) {
        if (contain(x, y)) {
            if (isPointed(i)) {
                onMove(x, y);
                mpManager->onEvent(getID(), HBM_EVENT_MOVE, pData);
            } else {
                setPointed(i, true);
                onPoint();
                mpManager->onEvent(getID(), HBM_EVENT_ON_POINT, pData);
            }

            bTouched = true;
        } else {
            if (isPointed(i)) {
                setPointed(i, false);
                offPoint();
                mpManager->onEvent(getID(), HBM_EVENT_OFF_POINT, pData);
            }
        }
    }

    return bTouched;
}

Manager::~Manager() {
    void* p = nw4r::ut::List_GetFirst(&mIDToComponent);

    for (; p; p = nw4r::ut::List_GetFirst(&mIDToComponent)) {
        nw4r::ut::List_Remove(&mIDToComponent, p);

        if (mpAllocator != NULL) {
            MEMFreeToAllocator(mpAllocator, p);
        } else {
            delete static_cast<IDToComponent*>(p);
        }
    }
}

void Manager::init() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* p = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        p->mpComponent->init();
    }
}

void Manager::addComponent(Component* pComponent) {
    u32 uID = pComponent->getID();
    pComponent->setManager(this);

    if (mpAllocator != NULL) {
        void* p = MEMAllocFromAllocator(mpAllocator, sizeof(IDToComponent));
        nw4r::ut::List_Append(&mIDToComponent,
                              new (p) IDToComponent(uID, pComponent));
    } else {
        nw4r::ut::List_Append(&mIDToComponent,
                              new IDToComponent(uID, pComponent));
    }
}

Component* Manager::getComponent(u32 uID) {
    const IDToComponent* p = static_cast<const IDToComponent*>(
        nw4r::ut::List_GetNthConst(&mIDToComponent, uID));

    return p->mpComponent;
}

bool Manager::update(int i, f32 x, f32 y, u32 uTrigFlag, u32 uHoldFlag,
                     u32 uReleaseFlag, void* pData) {
    bool bTouched = false;
    Component* pLastContainedComponent = NULL;

    for (u32 n = 0; n < nw4r::ut::List_GetSize(&mIDToComponent); n++) {
        const IDToComponent* p = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, n));

        if (p->mpComponent->update(i, x, y, uTrigFlag, uHoldFlag, uReleaseFlag,
                                   pData)) {
            if (p->mpComponent->isTriggerTarger())
                pLastContainedComponent = p->mpComponent;

            bTouched = true;
        }
    }

    if (pLastContainedComponent) {
        if (uTrigFlag) {
            Vec pos;
            pLastContainedComponent->onTrig(uTrigFlag, pos);

            onEvent(pLastContainedComponent->getID(), HBM_EVENT_TRIG, pData);
        }

        if (uReleaseFlag) {
            Vec pos;
            pLastContainedComponent->onTrig(uReleaseFlag, pos);

            onEvent(pLastContainedComponent->getID(), HBM_EVENT_RELEASE, pData);
        }
    }

    return bTouched;
}

void Manager::calc() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* p = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        p->mpComponent->calc();
    }
}

void Manager::draw() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* p = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        p->mpComponent->draw();
    }
}

void Manager::setAllComponentTriggerTarget(bool b) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* p = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        p->mpComponent->setTriggerTarget(b);
    }
}

PaneManager::~PaneManager() {
    PaneToComponent* pPaneToComponent = static_cast<PaneToComponent*>(
        nw4r::ut::List_GetFirst(&mPaneToComponent));

    for (; pPaneToComponent; pPaneToComponent = static_cast<PaneToComponent*>(
                                 nw4r::ut::List_GetFirst(&mPaneToComponent))) {
        nw4r::ut::List_Remove(&mPaneToComponent, pPaneToComponent);

        if (mpAllocator != NULL) {
            MEMFreeToAllocator(mpAllocator, pPaneToComponent->mpComponent);
            MEMFreeToAllocator(mpAllocator, pPaneToComponent);
        } else {
            delete pPaneToComponent->mpComponent;
            delete pPaneToComponent;
        }
    }
}

void PaneManager::createLayoutScene(const nw4r::lyt::Layout& rLayout) {
    suIDCounter = 0;

    nw4r::lyt::Pane* pRootPane = rLayout.GetRootPane();

    walkInChildren(pRootPane->GetChildList());
}

void PaneManager::walkInChildren(nw4r::lyt::PaneList& rPaneList) {
    NW4R_UT_LINKLIST_FOREACH(it, rPaneList, {
        PaneComponent* pPaneComponent = NULL;
        PaneToComponent* pPaneToComponent = NULL;

        if (mpAllocator != NULL) {
            void* p1 = MEMAllocFromAllocator(mpAllocator, sizeof(PaneComponent));
            void* p2 = MEMAllocFromAllocator(mpAllocator, sizeof(PaneToComponent));

            pPaneComponent = new (p1) PaneComponent(suIDCounter);
            pPaneToComponent = new (p2) PaneToComponent(&(*it), pPaneComponent);
        } else {
            pPaneComponent = new PaneComponent(suIDCounter);
            pPaneToComponent = new PaneToComponent(&(*it), pPaneComponent);
        }

        nw4r::ut::List_Append(&mPaneToComponent, pPaneToComponent);
        suIDCounter++;

        pPaneComponent->setPane(&(*it));

        if (nw4r::ut::DynamicCast<nw4r::lyt::Picture*>(&(*it)) != NULL) {
            pPaneComponent->setTriggerTarget(true);
        }

        if (nw4r::ut::DynamicCast<nw4r::lyt::Window*>(&(*it)) != NULL) {
            pPaneComponent->setTriggerTarget(true);
        }

        addComponent(pPaneComponent);
        walkInChildren(it->GetChildList());
    });
}

PaneComponent* PaneManager::getPaneComponentByPane(nw4r::lyt::Pane* pPane) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        PaneToComponent* p = static_cast<PaneToComponent*>(
            nw4r::ut::List_GetNth(&mPaneToComponent, i));

        if (p->mpPane == pPane) {
            return p->mpComponent;
        }
    }

    return NULL;
}

#pragma push
#pragma opt_propagation off // ???

void PaneManager::setAllBoundingBoxComponentTriggerTarget(bool b) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        PaneToComponent* p = static_cast<PaneToComponent*>(
            nw4r::ut::List_GetNth(&mPaneToComponent, i));

        if (nw4r::ut::DynamicCast<nw4r::lyt::Bounding*>(p->mpPane) != NULL) {
            p->mpComponent->setTriggerTarget(b);
        }
    }
}

#pragma pop

bool PaneComponent::contain(f32 x_, f32 y_) {
    if (mpManager == NULL) {
        return false;
    }

    const nw4r::lyt::DrawInfo* pDrawInfo =
        static_cast<PaneManager*>(mpManager)->getDrawInfo();

    if (pDrawInfo == NULL) {
        return false;
    }

    nw4r::math::MTX34 invGlbMtx;
    PSMTXInverse(mpPane->GetGlobalMtx(), invGlbMtx);

    nw4r::math::VEC3 lclPos;
    PSMTXMultVec(invGlbMtx, nw4r::math::VEC3(x_, y_, 0.0f), lclPos);

    nw4r::ut::Rect rect = mpPane->GetPaneRect(*pDrawInfo);

    if (rect.left <= lclPos.x && lclPos.x <= rect.right &&
        rect.bottom <= lclPos.y && lclPos.y <= rect.top) {
        return true;
    } else {
        return false;
    }
}

void PaneComponent::draw() {
    const nw4r::lyt::DrawInfo* pDrawInfo =
        static_cast<PaneManager*>(mpManager)->getDrawInfo();

    if (pDrawInfo == NULL) {
        return;
    }

    (void)mpPane->GetTranslate();
    nw4r::lyt::Size size = mpPane->GetSize();
    const nw4r::math::MTX34& gmtx = mpPane->GetGlobalMtx();

    f32 x = gmtx.mtx[0][3];
    f32 y = gmtx.mtx[1][3];

    GXColor color = {255, 0, 0, 255}; // red

    if (mabPointed[0]) {
        color.r = 0;
        color.b = 255; // now blue
    }

    // start at top left, go clockwise
    drawLine_(x - size.width / 2.0f, y - size.height / 2.0f,
              x + size.width / 2.0f, y - size.height / 2.0f, 0.0f, 8, color);

    drawLine_(x + size.width / 2.0f, y - size.height / 2.0f,
              x + size.width / 2.0f, y + size.height / 2.0f, 0.0f, 8, color);

    drawLine_(x + size.width / 2.0f, y + size.height / 2.0f,
              x - size.width / 2.0f, y + size.height / 2.0f, 0.0f, 8, color);

    drawLine_(x - size.width / 2.0f, y + size.height / 2.0f,
              x - size.width / 2.0f, y - size.height / 2.0f, 0.0f, 8, color);
}

static bool is_visible(nw4r::lyt::Pane* pPane) {
    if (!pPane->IsVisible()) {
        return false;
    }

    if (pPane->GetParent() == NULL) {
        return true;
    }

    return is_visible(pPane->GetParent()) ? true : false;
}

bool PaneComponent::isVisible() {
    return is_visible(mpPane);
}

} // namespace gui
} // namespace homebutton
