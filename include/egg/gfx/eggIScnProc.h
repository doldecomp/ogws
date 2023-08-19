#ifndef EGG_GFX_I_SCN_PROC_H
#define EGG_GFX_I_SCN_PROC_H
#include "types_egg.h"
#include "eggAssert.h"
#include "types_nw4r.h"
#include <revolution/MEM/mem_allocator.h>

namespace EGG
{
    class IScnProc
    {
    public:
        // Unofficial name
        struct ProcData
        {
            IScnProc *mpThis; // at 0x0
            nw4r::g3d::ScnProc *mpScnProc; // at 0x4
            u16 mIndex; // at 0x8
            bool bUseOpa; // at 0xA
        };

    public:
        IScnProc();
        virtual ~IScnProc(); // at 0x8
        virtual void doDraw(u16) = 0; // at 0xC

        void createScnProc(u16 procNum, MEMAllocator *allocator);
        void setPriorityScnProc(u16, u8, bool);
        void pushBackToScnGroup(nw4r::g3d::ScnGroup *);
        void removeFromScnGroup(nw4r::g3d::ScnGroup *);
        static void drawProcFunc(nw4r::g3d::ScnProc *, bool);

        u16 getNumScnProc() { return mNumScnProc; }
        ProcData * getData(u16 procIndex)
        {
            #line 86
            EGG_ASSERT(procIndex < getNumScnProc());
            return &mpDataSet[procIndex];
        }

    private:
        ProcData *mpDataSet; // at 0x4
        u16 mNumScnProc; // at 0x8
    };
}

#endif