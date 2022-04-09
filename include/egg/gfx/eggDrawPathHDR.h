#ifndef EGG_GFX_DRAW_PATH_HDR_H
#define EGG_GFX_DRAW_PATH_HDR_H
#include "types_egg.h"
#include "eggDrawPathBase.h"

namespace EGG
{
    class DrawPathHDR : public DrawPathBase
    {
    public:
        DrawPathHDR();
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(); // at 0x28
        virtual ~DrawPathHDR(); // at 0x8

    private:
        char UNK_0x7C[0x80 - 0x7C];
    };
}

#endif