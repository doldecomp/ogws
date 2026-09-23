#ifndef EGG_GFXE_SCN_RENDERER_H
#define EGG_GFXE_SCN_RENDERER_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggScnRootEx.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

#include <revolution/MEM.h>

namespace EGG {

class ScnRenderer : public ScnRootEx {
public:
    enum Timing {
        cTiming_Opa1st,
        cTiming_Opa2nd,
        cTiming_Opa3rd,
        cTiming_Opa4th,

        cTiming_Xlu1st,
        cTiming_Xlu2nd,
        cTiming_Xlu3rd,

        cTiming_Max,
    };

    enum DrawPath {
        cDrawPath_XluSnap,
        cDrawPath_SV,
        cDrawPath_HDR,
        cDrawPath_Bloom,
        cDrawPath_DOF,

        cDrawPath_Max
    };

    enum CreateFlag {
        cCreateFlag_XluSnap = 1 << cDrawPath_XluSnap,
        cCreateFlag_SV = 1 << cDrawPath_SV,
        cCreateFlag_HDR = 1 << cDrawPath_HDR,
        cCreateFlag_Bloom = 1 << cDrawPath_Bloom,
        cCreateFlag_DOF = 1 << cDrawPath_DOF
    };

public:
    ScnRenderer(nw4r::g3d::ScnRoot* pScnRoot);
    virtual ~ScnRenderer(); // at 0x8

    virtual void configure();                                 // at 0xC
    virtual void changeScnRoot(nw4r::g3d::ScnRoot* pScnRoot); // at 0x14
    virtual void calc_after_CalcWorld();                      // at 0x1C
    virtual void draw_before_CalcView();                      // at 0x24
    virtual u16 getLocalPriorityMax() const;                  // at 0x30
    virtual u16 getNumDrawPath() const;                       // at 0x34
    virtual u16 getNumTiming() const;                         // at 0x38

    void createPath(u32 createFlags, MEMAllocator* pAllocator);
    void pushBackDrawPath();

    void setLocalPriorityScnProc(IScnProc* pScnProc, u32 timing, u8 prio,
                                 u16 procIndex) const;

    bool isVisible() const {
        return mFlags & cFlag_Visible;
    }

    bool getTimingPriorityRange(u32 timing, u8* pPrioMin, u8* pPrioMax) const {
#line 193
        EGG_ASSERT(timing < getNumTiming());
        EGG_ASSERT(mpTimingPrioritySet != NULL);

        if (pPrioMin != NULL) {
            *pPrioMin = mpTimingPrioritySet[timing].prioMin;
        }

        if (pPrioMax != NULL) {
            *pPrioMax = mpTimingPrioritySet[timing].prioMax;
        }

        return mpTimingPrioritySet[timing].opa;
    }

    DrawPathBase* getDrawPathBase(u16 path) const {
#line 119
        EGG_ASSERT(path < getNumDrawPath());
        return mppPathSet[path];
    }

private:
    struct TimingPriority {
        u8 prioMin; // at 0x0
        u8 prioMax; // at 0x1
        bool opa;   // at 0x2
    };

    enum {
        cFlag_Visible = 1 << 0,
    };

    static const u8 PRIO_XLU_1ST = 0;
    static const u8 PRIO_OPA_1ST = 1;

    static const u8 PRIO_XLU_2ND = 25;
    static const u8 PRIO_OPA_2ND = 27;

    static const u8 PRIO_OPA_3RD = 52;
    static const u8 PRIO_XLU_3RD = 58;

    static const u8 PRIO_OPA_4TH = 77;

    static const u16 LOCAL_PRIO_MAX = 23;

private:
    DrawPathBase** mppPathSet;           // at 0x54
    TimingPriority* mpTimingPrioritySet; // at 0x58
    u16 mFlags;                          // at 0x5C
};

} // namespace EGG

#endif
