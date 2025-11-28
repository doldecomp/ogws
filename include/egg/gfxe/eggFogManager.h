#ifndef EGG_GFXE_FOG_MANAGER_H
#define EGG_GFXE_FOG_MANAGER_H
#include <egg/types_egg.h>

#include <nw4r/g3d.h>

namespace EGG {

// Forward declarations
class Fog;
class Screen;

class FogManager {
private:
    static const int FOG_MAX = 32;

private:
    u8 mFlags;          // at 0x0
    Fog* mFog[FOG_MAX]; // at 0x4

public:
    FogManager();
    virtual ~FogManager() {} // at 0x8

    void Reset();
    void Calc();
    void LoadScreenClip(const Screen& rScreen);
    void CopyToG3D(nw4r::g3d::ScnRoot* pScnRoot) const;
    void LoadScnFog(const nw4r::g3d::ResAnmScn scn, f32 frame);
    void DoneDraw();

private:
    enum {
        EFlag_AwaitDraw = 1 << 2,
    };
};

} // namespace EGG

#endif
