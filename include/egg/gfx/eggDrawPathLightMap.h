#ifndef EGG_GFX_DRAW_PATH_LIGHT_MAP_H
#define EGG_GFX_DRAW_PATH_LIGHT_MAP_H
#include "types_egg.h"
#include "eggDrawPathBase.h"

namespace EGG
{
    class DrawPathLightMap : public DrawPathBase
    {
    public:
        DrawPathLightMap();
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(); // at 0x28
        virtual ~DrawPathLightMap(); // at 0x8

    private:
        char UNK_0x7C[0x90 - 0x7C];
    };
}

#endif