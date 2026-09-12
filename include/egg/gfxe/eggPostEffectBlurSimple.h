#ifndef EGG_GFXE_POST_EFFECT_BLUR_SIMPLE_H
#define EGG_GFXE_POST_EFFECT_BLUR_SIMPLE_H
#include "eggPostEffectBase.h"
#include "types_egg.h"

namespace EGG {

class PostEffectBlurSimple : public PostEffectBase {
public:
    PostEffectBlurSimple();
    virtual ~PostEffectBlurSimple() {}  // at 0x8
    virtual void reset();               // at 0x14
    virtual void setMaterialInternal(); // at 0x18

public:
    char unk20[0x34 - 0x20];
};

} // namespace EGG

#endif
