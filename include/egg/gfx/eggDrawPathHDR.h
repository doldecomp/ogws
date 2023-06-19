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
        virtual ~DrawPathHDR(); // at 0x8
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(u16); // at 0x28

    private:
        PostEffectHDR *mPostEffect; // at 0x7C

        static const int NUM_SCNPROC = 2;
    };
}

#endif