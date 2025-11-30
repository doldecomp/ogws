#ifndef HOME_BUTTON_MINI_LIB_GUI_MANAGER_H
#define HOME_BUTTON_MINI_LIB_GUI_MANAGER_H
#include <homeButtonMiniLib/HBMTypes.h>

#include <nw4r/lyt.h>
#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <revolution/KPAD.h>
#include <revolution/MEM.h>
#include <revolution/MTX.h>

namespace homebutton {
namespace gui {

// Forward declarations
class Manager;
class PaneComponent;

/******************************************************************************
 *
 * Interface
 *
 ******************************************************************************/
class Interface {
public:
    Interface() {}
    virtual void create() {}             // at 0x8
    virtual void init() {}               // at 0xC
    virtual void calc() {}               // at 0x10
    virtual void draw(Mtx& /* mtx */) {} // at 0x14
    virtual void draw() {}               // at 0x18
    virtual ~Interface() {}              // at 0x1C
};

/******************************************************************************
 *
 * EventHandler
 *
 ******************************************************************************/
enum Event {
    HBM_EVENT_TRIG,
    HBM_EVENT_ON_POINT,
    HBM_EVENT_OFF_POINT,
    HBM_EVENT_MOVE,
    HBM_EVENT_4,
    HBM_EVENT_RELEASE,
};

class EventHandler {
public:
    EventHandler() {}

    virtual void onEvent(u32 /* uID */, u32 /* uEvent */, void* /* pData */) //
    {} // at 0x8

    virtual void setManager(Manager* pManager) { // at 0xC
        mpManager = pManager;
    }

protected:
    Manager* mpManager; // at 0x4
};

/******************************************************************************
 *
 * Component
 *
 ******************************************************************************/
class Component : public Interface {
public:
    Component(u32 uID)
        : mDragStartPos(),
          mbDragging(),
          muDraggingButton(),
          muID(uID),
          mbTriggerTarger(),
          mpManager() {
        init();
    }

    virtual void init() { // at 0xC
        mbDragging = false;

        for (int i = 0; i < (int)ARRAY_SIZE(mabPointed); i++) {
            mabPointed[i] = false;
        }
    }

    virtual ~Component() {} // at 0x1C

    virtual u32 getID() { // at 0x20
        return muID;
    }
    virtual int isPointed(int n) { // at 0x24
        return mabPointed[n];
    }
    virtual void setPointed(int n, bool b) { // at 0x28
        mabPointed[n] = b;
    }
    virtual void onPoint() {}                  // at 0x2C
    virtual void offPoint() {}                 // at 0x30
    virtual void onDrag(f32, f32) {}           // at 0x34
    virtual void onMove(f32, f32) {}           // at 0x38
    virtual void onTrig(u32 uFlag, Vec& vec) { // at 0x3C
        if (uFlag & muDraggingButton) {
            mDragStartPos = vec;
            mbDragging = true;
        }
    }
    virtual void setDraggingButton(u32 uDraggingButton) { // at 0x40
        muDraggingButton = uDraggingButton;
    }
    virtual bool update(int, const KPADStatus*, f32, f32, void*) { // at 0x44
        return false;
    }
    virtual bool update(int i, f32 x, f32 y, u32 uTrigFlag, u32 uHoldFlag,
                        u32 uReleaseFlag, void* pData); // at 0x48
    virtual bool isTriggerTarger() {                    // at 0x4C
        return mbTriggerTarger;
    }
    virtual void setTriggerTarget(bool bTriggerTarget) { // at 0x50
        mbTriggerTarger = bTriggerTarget;
    }
    virtual void setManager(Manager* pManager) { // at 0x54
        mpManager = pManager;
    }
    virtual bool isVisible() { // at 0x58
        return true;
    }
    virtual bool contain(f32 x_, f32 y_) = 0; // at 0x5C

protected:
    bool mabPointed[8];   // at 0x4
    Vec mDragStartPos;    // at 0xC
    bool mbDragging;      // at 0x18
    u32 muDraggingButton; // at 0x1C
    u32 muID;             // at 0x20
    bool mbTriggerTarger; // at 0x24
    Manager* mpManager;   // at 0x28
};

/******************************************************************************
 *
 * Manager
 *
 ******************************************************************************/
class Manager : public Interface {
private:
    struct IDToComponent {
    public:
        IDToComponent(u32 uID, Component* pComponent)
            : muID(uID), mpComponent(pComponent) {}

    public:
        u32 muID;                 // at 0x0
        Component* mpComponent;   // at 0x4
        NW4R_UT_LIST_LINK_DECL(); // at 0x8
    };

public:
    Manager(EventHandler* pEventHandler, MEMAllocator* pAllocator)
        : mpEventHandler(pEventHandler), mpAllocator(pAllocator) {
        if (mpEventHandler != NULL) {
            mpEventHandler->setManager(this);
        }

        NW4R_UT_LIST_INIT(mIDToComponent, IDToComponent);
    }

    virtual void init(); // at 0xC
    virtual void calc(); // at 0x10
    virtual void draw(); // at 0x14
    virtual ~Manager();  // at 0x1C

    virtual void addComponent(Component* pComponent);              // at 0x20
    virtual Component* getComponent(u32 uID);                      // at 0x24
    virtual bool update(int, const KPADStatus*, f32, f32, void*) { // at 0x28
        return false;
    }
    virtual bool update(int i, f32 x, f32 y, u32 uTrigFlag, u32 uHoldFlag,
                        u32 uReleaseFlag, void* pData);      // at 0x2C
    virtual void onEvent(u32 uID, u32 uEvent, void* pData) { // at 0x30
        if (mpEventHandler != NULL) {
            mpEventHandler->onEvent(uID, uEvent, pData);
        }
    }

    virtual void setAllComponentTriggerTarget(bool b);          // at 0x34
    virtual void setEventHandler(EventHandler* pEventHandler) { // at 0x38
        mpEventHandler = pEventHandler;

        if (mpEventHandler != NULL) {
            mpEventHandler->setManager(this);
        }
    }

protected:
    EventHandler* mpEventHandler;  // at 0x4
    nw4r::ut::List mIDToComponent; // at 0x8
    MEMAllocator* mpAllocator;     // at 0x14
};

/******************************************************************************
 *
 * PaneManager
 *
 ******************************************************************************/
class PaneManager : public Manager {
private:
    struct PaneToComponent {
    public:
        PaneToComponent(nw4r::lyt::Pane* pPane, PaneComponent* pComponent)
            : mpPane(pPane), mpComponent(pComponent) {}

    public:
        nw4r::lyt::Pane* mpPane;    // at 0x0
        PaneComponent* mpComponent; // at 0x4
        NW4R_UT_LIST_LINK_DECL();   // at 0x8
    };

public:
    PaneManager(EventHandler* pEventHandler,
                const nw4r::lyt::DrawInfo* pDrawInfo, MEMAllocator* pAllocator)
        : Manager(pEventHandler, pAllocator), mpDrawInfo(pDrawInfo) {

        NW4R_UT_LIST_INIT(mPaneToComponent, PaneToComponent);
    }

    virtual ~PaneManager(); // at 0x1C

    virtual void createLayoutScene(const nw4r::lyt::Layout& rLayout); // at 0x3C
    virtual PaneComponent*
    getPaneComponentByPane(nw4r::lyt::Pane* pPane);    // at 0x40
    virtual const nw4r::lyt::DrawInfo* getDrawInfo() { // at 0x44
        return mpDrawInfo;
    }
    virtual void setDrawInfo(const nw4r::lyt::DrawInfo* pDrawInfo) { // at 0x48
        mpDrawInfo = pDrawInfo;
    }
    virtual void setAllBoundingBoxComponentTriggerTarget(bool b); // at 0x4C
    virtual void walkInChildren(nw4r::lyt::PaneList& rPaneList);  // at 0x50

private:
    static u32 suIDCounter;

    nw4r::ut::List mPaneToComponent;       // at 0x18
    const nw4r::lyt::DrawInfo* mpDrawInfo; // at 0x24
    u16 muNumPoint;                        // at 0x28
    u16 muPadding;                         // at 0x2C
};

/******************************************************************************
 *
 * PaneComponent
 *
 ******************************************************************************/
class PaneComponent : public Component {
public:
    PaneComponent(u32 uID) : Component(uID), mpPane() {}
    virtual void draw();        // at 0x18
    virtual ~PaneComponent() {} // at 0x1C

    virtual bool isVisible();             // at 0x58
    virtual bool contain(f32 x_, f32 y_); // at 0x5C

    virtual void setPane(nw4r::lyt::Pane* pPane) { // at 0x60
        mpPane = pPane;
    }
    virtual nw4r::lyt::Pane* getPane() { // at 0x64
        return mpPane;
    }

private:
    nw4r::lyt::Pane* mpPane; // at 0x2C
};

} // namespace gui
} // namespace homebutton

#endif
