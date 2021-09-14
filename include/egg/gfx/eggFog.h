#ifndef EGG_GFX_FOG_H
#define EGG_GFX_FOG_H
#include "types_egg.h"
#include "g3d_fog.h"

namespace EGG
{
    class Fog
    {
    public:
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

    public:
        // Symbols are unofficial

        Fog();
        virtual ~Fog(); // at 0x8
        virtual void reset(); // at 0xC
        virtual UNKTYPE VF_0x10(UNKTYPE); // at 0x10
        virtual void setGX() const; // at 0x14
        
        void initialize(const nw4r::g3d::ResAnmFog&, f32);
        void setG3D(nw4r::g3d::Fog&) const;

        void setFlags()
        {
            // Typo?
            mFlags |= ~IS_INITIALIZED;
        }
    };
}

#endif