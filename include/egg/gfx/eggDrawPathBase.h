#ifndef EGG_GFX_DRAW_PATH_BASE_H
#define EGG_GFX_DRAW_PATH_BASE_H
#include "types_egg.h"
#include "eggAssert.h"
#include "eggScreenEffectBase.h"
#include "eggIScnProc.h"
#include "eggIDrawGX.h"

namespace EGG
{
    class DrawPathBase : public ScreenEffectBase, public IScnProc
    {
    public:
        DrawPathBase();
        virtual ~DrawPathBase() {} // at 0x8
        virtual int getNumScnProc() const = 0; // at 0x1C
        virtual void calc_after_CalcWorld(); // at 0x20
        virtual void calc(); // at 0x24
        virtual void draw(u16) = 0; // at 0x28
        virtual void doDraw(u16); // at 0x2C

        void CopyGlobalScreen();
    };
}

#endif