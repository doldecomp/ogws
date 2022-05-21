#ifndef EGG_GFX_DRAW_PATH_DOF_H
#define EGG_GFX_DRAW_PATH_DOF_H
#include "types_egg.h"
#include "eggDrawPathBase.h"

namespace EGG
{
    class DrawPathDOF : public DrawPathBase
    {
    public:
        DrawPathDOF();
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(u16); // at 0x28
        virtual ~DrawPathDOF(); // at 0x8

    private:
        char UNK_0x7C[0xB4 - 0x7C];
    };
}

#endif