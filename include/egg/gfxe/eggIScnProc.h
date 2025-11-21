#ifndef EGG_GFXE_I_SCN_PROC_H
#define EGG_GFXE_I_SCN_PROC_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggIDrawGX.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>

#include <revolution/MEM.h>

namespace EGG {

class IScnProc : public IDrawGX {
public:
    struct ProcData {
        IScnProc* mpThis;              // at 0x0
        nw4r::g3d::ScnProc* mpScnProc; // at 0x4
        u16 mIndex;                    // at 0x8
        bool mOpa;                     // at 0xA
    };

public:
    IScnProc();
    virtual ~IScnProc();                   // at 0x8
    virtual void scnProcDraw(u16 idx) = 0; // at 0xC

    void createScnProc(u16 procNum, MEMAllocator* pAllocator);
    void setPriorityScnProc(u16 procIndex, u8 priority, bool opa);

    void pushBackToScnGroup(nw4r::g3d::ScnGroup* pScnGroup);
    void removeFromScnGroup(nw4r::g3d::ScnGroup* pScnGroup);

    ProcData* getData(u16 procIndex) {
#line 86
        EGG_ASSERT(procIndex < getNumScnProc());
        return &mpDataSet[procIndex];
    }
    u16 getNumScnProc() const {
        return mNumScnProc;
    }

private:
    static void drawProcFunc(nw4r::g3d::ScnProc* pScnProc, bool opa);

private:
    ProcData* mpDataSet; // at 0x4
    u16 mNumScnProc;     // at 0x8
};

} // namespace EGG

#endif
