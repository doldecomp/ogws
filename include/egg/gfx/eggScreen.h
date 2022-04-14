#ifndef EGG_GFX_SCREEN_H
#define EGG_GFX_SCREEN_H
#include "types_egg.h"
#include "eggFrustum.h"

namespace EGG
{
    class Screen : public Frustum
    {
    public:
        struct EfbData
        {
            f32 FLOAT_0x0;
            f32 FLOAT_0x4;
            f32 FLOAT_0x8;
            f32 FLOAT_0xC;
            f32 FLOAT_0x10;
            f32 FLOAT_0x14;
            f32 FLOAT_0x18;
            f32 FLOAT_0x1C;
        };

    public:
        Screen();
        Screen(const Screen&);

        virtual ~Screen() {} // at 0x8
        virtual void SetProjectionGX() const; // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera) const; // at 0x10

        void CopyFromAnother(const Screen&);

        EfbData * GetDataEfb() const;

    private:
        f32 FLOAT_0x40;
        f32 FLOAT_0x44;
        EfbData mEfbData; // at 0x48
        char UNK_0x64[0x4];
    };
}

#endif