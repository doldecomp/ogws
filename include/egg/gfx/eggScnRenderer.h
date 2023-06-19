#ifndef EGG_GFX_SCN_RENDERER_H
#define EGG_GFX_SCN_RENDERER_H
#include "types_egg.h"
#include "eggScnRootEx.h"
#include "types_nw4r.h"
#include <revolution/MEM/mem_allocator.h>

namespace EGG
{
    class ScnRenderer : ScnRootEx
    {
    public:
        enum DrawPathType
        {
            DRAW_PATH_LMAP,
            DRAW_PATH_SV,
            DRAW_PATH_HDR,
            DRAW_PATH_BLOOM,
            DRAW_PATH_DOF,

            DRAW_PATH_MAX
        };

        enum ScnRendererFlag
        {
            RENDERER_VISIBLE = (1 << 0)
        };

        struct TimingPriority
        {
            u8 localPrio; // at 0x0
            u8 prioMax; // at 0x1
            bool opa; // at 0x2
        };

    public:
        ScnRenderer(nw4r::g3d::ScnRoot *);
        virtual ~ScnRenderer(); // at 0x8
        virtual void configure(); // at 0xC
        virtual void changeScnRoot(nw4r::g3d::ScnRoot *); // at 0x14
        virtual void calc_after_CalcWorld(); // at 0x1C
        virtual void draw_before_CalcView(); // at 0x24
        virtual u16 getLocalPriorityMax() const; // at 0x30
        virtual u16 getNumDrawPath() const; // at 0x34
        virtual u16 getNumTiming() const; // at 0x38

        void createPath(u32, MEMAllocator *);
        void pushBackDrawPath();
        void setLocalPriorityScnProc(IScnProc *, u32, u8, u16) const;

        bool isVisible() const { return mFlags & RENDERER_VISIBLE; }

        bool getTimingPriority(u32 timing, u8 *localPrioOut, u8 *prioMaxOut) const
        {
            #line 193
            EGG_ASSERT(timing < getNumTiming());
            EGG_ASSERT(mpTimingPrioritySet != NULL);

            if (localPrioOut != NULL) *localPrioOut = mpTimingPrioritySet[timing].localPrio;
            if (prioMaxOut != NULL) *prioMaxOut = mpTimingPrioritySet[timing].prioMax;
            return mpTimingPrioritySet[timing].opa;
        }

        DrawPathBase * getDrawPathBase(u16 path) const
        {
            #line 119
            EGG_ASSERT(path < getNumDrawPath());
            return mppPathSet[path];
        }

    private:
        DrawPathBase **mppPathSet; // at 0x54
        TimingPriority *mpTimingPrioritySet; // at 0x58
        u16 mFlags; // at 0x5C

        static const u16 LOCAL_PRIO_MAX = 23;
        static const u16 NUM_TIMING = 7;
    };
}

#endif