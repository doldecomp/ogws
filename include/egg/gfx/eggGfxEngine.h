#ifndef EGG_GFX_GFX_ENGINE_H
#define EGG_GFX_GFX_ENGINE_H
#include "types_egg.h"

namespace EGG
{
    class GfxEngine
    {
    private:
        char *PTR_0x4;
        char UNK_0x8[0x4];

    public:
        static void initialize(u16, u16, Heap *);
        static void beginDraw();

        GfxEngine();
        virtual ~GfxEngine(); // at 0x8

    private:
        static GfxEngine *spInstance;
    };
}

#endif