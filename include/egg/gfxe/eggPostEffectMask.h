#ifndef EGG_GFXE_POST_EFFECT_MASK_H
#define EGG_GFXE_POST_EFFECT_MASK_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggPostEffectBase.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class TextureBuffer;

class PostEffectMask : public PostEffectBase {
public:
    PostEffectMask();

    virtual void reset();               // at 0x14
    virtual void setMaterialInternal(); // at 0x18

private:
    u32 unk20;
    GXColor mColor;             // at 0x24
    f32 mIntensity;             // at 0x28
    TextureBuffer* mpDstScreen; // at 0x2C
    f32 unk30;
    char unk34[0x1B4 - 0x34];
};

} // namespace EGG

#endif
