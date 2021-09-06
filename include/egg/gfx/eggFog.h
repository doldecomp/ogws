#ifndef EGG_GFX_FOG_H
#define EGG_GFX_FOG_H
#include "types_egg.h"
#include "g3d_fog.h"

namespace EGG
{
    class Fog
    {
    private:
        GXColor mColor; // at 0x0
        f32 mStartZ; // at 0x4
        f32 mEndZ; // at 0x8
        f32 mNearZ; // at 0xC
        f32 mFarZ; // at 0x10
        GXFogType mFogType; // at 0x14
        u8 mFlags; // at 0x18

    public:
        enum FogFlag
        {
            IS_INITIALIZED = 1,
        };

        // Symbols are unofficial

        Fog();
        virtual ~Fog();
        virtual void reset();
        virtual UNKTYPE VF_0x10(UNKTYPE);
        virtual void setGX() const;
        
        void initialize(const nw4r::g3d::ResAnmFog&, f32);
        void setG3D(nw4r::g3d::Fog&) const;

        void resetFlags()
        {
            // Typo?
            mFlags |= ~IS_INITIALIZED;
        }
    };
}

#endif