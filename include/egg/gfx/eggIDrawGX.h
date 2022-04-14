#ifndef EGG_GFX_I_DRAWGX_H
#define EGG_GFX_I_DRAWGX_H
#include "types_egg.h"
#include "eggAssert.h"

namespace EGG
{
    class IDrawGX
    {
    public:
        static Screen& getScreen()
        {
            #line 59
            EGG_ASSERT(spScreen);
            return *spScreen;
        }

        static void setScreen(Screen& pScreen) { spScreen = &pScreen; }
    
    private:
        static Screen *spScreen;
    };
}

#endif