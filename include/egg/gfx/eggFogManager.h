#ifndef EGG_GFX_FOG_MANAGER_H
#define EGG_GFX_FOG_MANAGER_H
#include "types_egg.h"
#include "types_nw4r.h"

namespace EGG
{
    class FogManager
    {
    private:
        static const int cNumFog = 32;

        u8 mFlags; // at 0x0
        Fog *mFog[cNumFog]; // at 0x4
    
        enum
        {
            FLAG_4 = 4,
        };

    public:
        FogManager();
        virtual ~FogManager(); // at 0x8

        // Symbols are unofficial
        // Mostly from EGG coding style and Rii's MKW symbols
        void reset();
        void callVF_0x10();
        void useScreenZ(eggScreen *);
        void setG3D(nw4r::g3d::ScnRoot *);
        void initialize(nw4r::g3d::ResAnmScn *, f32);
        void resetFlags();
    };
}

#endif