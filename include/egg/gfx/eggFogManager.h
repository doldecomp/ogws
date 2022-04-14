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
            DRAW_READY = 4,
        };

    public:
        FogManager();
        virtual ~FogManager(); // at 0x8

        void Reset();
        void Calc();
        void UseScreenZ(Screen&);
        void CopyToG3D(nw4r::g3d::ScnRoot *) const;
        void LoadScnFog(nw4r::g3d::ResAnmScn *, f32);
        void DoneDraw();
    };
}

#endif