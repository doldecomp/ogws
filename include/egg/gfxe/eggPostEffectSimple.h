#ifndef EGG_GFXE_POST_EFFECT_SIMPLE_H
#define EGG_GFXE_POST_EFFECT_SIMPLE_H
#include "eggPostEffectBase.h"
#include "types_egg.h"

namespace EGG {
class PostEffectSimple : public PostEffectBase {
public:
    PostEffectSimple();
    virtual ~PostEffectSimple() {} // at 0x8
    virtual void reset();          // at 0x14
    virtual void preDraw();        // at 0x18

private:
    GXColor mColor; // at 0x20
    f32 FLOAT_0x24;
    char UNK_0x28[0x4];
    UNKWORD WORD_0x2C;
};
} // namespace EGG

#endif
