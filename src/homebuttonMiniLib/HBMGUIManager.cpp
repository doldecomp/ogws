#include <homebuttonMiniLib.h>

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

void drawLine_(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 width,
               GXColor& rColor) {
    static const f32 cubeScale = 1.0f;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    GXSetCullMode(GX_CULL_NONE);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);

    Mtx modelMtx;
    PSMTXTrans(modelMtx, 0.0f, 0.0f, 0.0f);
    GXLoadPosMtxImm(modelMtx, GX_PNMTX0);

    GXSetLineWidth(width, 0);

    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    {
        GXPosition3f32(x0, y0, z);
        GXColor1u32(*reinterpret_cast<u32*>(&rColor));

        GXPosition3f32(x1, y1, z);
        GXColor1u32(*reinterpret_cast<u32*>(&rColor));
    }
    GXEnd();
}

bool Component::update(int i, f32 x, f32 y, u32 /* trig */, u32 /* hold */,
                       u32 /* release */, void* pData) {
    bool touch = false;

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

            touch = true;
        } else {
            if (isPointed(i)) {
                setPointed(i, false);
                offPoint();
                mpManager->onEvent(getID(), HBM_EVENT_OFF_POINT, pData);
            }
        }
    }

    return touch;
}

Manager::~Manager() {
    void* pIt = nw4r::ut::List_GetFirst(&mIDToComponent);

    for (; pIt != NULL; pIt = nw4r::ut::List_GetFirst(&mIDToComponent)) {
        nw4r::ut::List_Remove(&mIDToComponent, pIt);

        if (mpAllocator != NULL) {
            MEMFreeToAllocator(mpAllocator, pIt);
        } else {
            delete static_cast<IDToComponent*>(pIt);
        }
    }
}

void Manager::init() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* pIt = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        pIt->mpComponent->init();
    }
}

void Manager::addComponent(Component* pComponent) {
    u32 id = pComponent->getID();
    pComponent->setManager(this);

    if (mpAllocator != NULL) {
        void* p = MEMAllocFromAllocator(mpAllocator, sizeof(IDToComponent));
        nw4r::ut::List_Append(&mIDToComponent,
                              new (p) IDToComponent(id, pComponent));
    } else {
        nw4r::ut::List_Append(&mIDToComponent,
                              new IDToComponent(id, pComponent));
    }
}

Component* Manager::getComponent(u32 id) {
    const IDToComponent* p = static_cast<const IDToComponent*>(
        nw4r::ut::List_GetNthConst(&mIDToComponent, id));

    return p->mpComponent;
}

bool Manager::update(int i, f32 x, f32 y, u32 trig, u32 hold, u32 release,
                     void* pData) {
    bool touch = false;
    Component* pLastContained = NULL;

    for (u32 n = 0; n < nw4r::ut::List_GetSize(&mIDToComponent); n++) {
        const IDToComponent* pIt = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, n));

        if (pIt->mpComponent->update(i, x, y, trig, hold, release, pData)) {
            if (pIt->mpComponent->isTriggerTarger()) {
                pLastContained = pIt->mpComponent;
            }

            touch = true;
        }
    }

    if (pLastContained != NULL) {
        if (trig) {
            Vec pos;
            pLastContained->onTrig(trig, pos);

            onEvent(pLastContained->getID(), HBM_EVENT_TRIG, pData);
        }

        if (release) {
            Vec pos;
            pLastContained->onTrig(release, pos);

            onEvent(pLastContained->getID(), HBM_EVENT_RELEASE, pData);
        }
    }

    return touch;
}

void Manager::calc() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* pIt = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        pIt->mpComponent->calc();
    }
}

void Manager::draw() {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* pIt = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        pIt->mpComponent->draw();
    }
}

void Manager::setAllComponentTriggerTarget(bool target) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        const IDToComponent* pIt = static_cast<const IDToComponent*>(
            nw4r::ut::List_GetNthConst(&mIDToComponent, i));

        pIt->mpComponent->setTriggerTarget(target);
    }
}

PaneManager::~PaneManager() {
    PaneToComponent* pIt = static_cast<PaneToComponent*>(
        nw4r::ut::List_GetFirst(&mPaneToComponent));

    for (; pIt != NULL; pIt = static_cast<PaneToComponent*>(
                            nw4r::ut::List_GetFirst(&mPaneToComponent))) {

        nw4r::ut::List_Remove(&mPaneToComponent, pIt);

        if (mpAllocator != NULL) {
            MEMFreeToAllocator(mpAllocator, pIt->mpComponent);
            MEMFreeToAllocator(mpAllocator, pIt);
        } else {
            delete pIt->mpComponent;
            delete pIt;
        }
    }
}

void PaneManager::createLayoutScene(const nw4r::lyt::Layout& rLayout) {
    suIDCounter = 0;
    walkInChildren(rLayout.GetRootPane()->GetChildList());
}

void PaneManager::walkInChildren(nw4r::lyt::PaneList& rPaneList) {
    NW4R_UT_LINKLIST_FOREACH(it, rPaneList, {
        PaneComponent* pComponent = NULL;
        PaneToComponent* pLink = NULL;

        if (mpAllocator != NULL) {
            void* pBufComponent = MEMAllocFromAllocator(mpAllocator, sizeof(PaneComponent));
            void* pBufLink = MEMAllocFromAllocator(mpAllocator, sizeof(PaneToComponent));

            pComponent = new (pBufComponent) PaneComponent(suIDCounter);
            pLink = new (pBufLink) PaneToComponent(&*it, pComponent);
        } else {
            pComponent = new PaneComponent(suIDCounter);
            pLink = new PaneToComponent(&*it, pComponent);
        }

        nw4r::ut::List_Append(&mPaneToComponent, pLink);
        suIDCounter++;

        pComponent->setPane(&*it);

        if (nw4r::ut::DynamicCast<nw4r::lyt::Picture*>(&*it) != NULL) {
            pComponent->setTriggerTarget(true);
        }

        if (nw4r::ut::DynamicCast<nw4r::lyt::Window*>(&*it) != NULL) {
            pComponent->setTriggerTarget(true);
        }

        addComponent(pComponent);
        walkInChildren(it->GetChildList());
    });
}

PaneComponent* PaneManager::getPaneComponentByPane(nw4r::lyt::Pane* pPane) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        PaneToComponent* pIt = static_cast<PaneToComponent*>(
            nw4r::ut::List_GetNth(&mPaneToComponent, i));

        if (pIt->mpPane == pPane) {
            return pIt->mpComponent;
        }
    }

    return NULL;
}

#pragma push
#pragma opt_propagation off // ???

void PaneManager::setAllBoundingBoxComponentTriggerTarget(bool target) {
    for (u32 i = 0; i < nw4r::ut::List_GetSize(&mIDToComponent); i++) {
        PaneToComponent* pIt = static_cast<PaneToComponent*>(
            nw4r::ut::List_GetNth(&mPaneToComponent, i));

        if (nw4r::ut::DynamicCast<nw4r::lyt::Bounding*>(pIt->mpPane) != NULL) {
            pIt->mpComponent->setTriggerTarget(target);
        }
    }
}

#pragma pop

bool PaneComponent::contain(f32 x, f32 y) {
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
    PSMTXMultVec(invGlbMtx, nw4r::math::VEC3(x, y, 0.0f), lclPos);

    nw4r::ut::Rect rect = mpPane->GetPaneRect(*pDrawInfo);

    if (rect.left <= lclPos.x && lclPos.x <= rect.right &&
        rect.bottom <= lclPos.y && lclPos.y <= rect.top) {
        return true;
    }

    return false;
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

    f32 x = gmtx._03;
    f32 y = gmtx._13;

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
