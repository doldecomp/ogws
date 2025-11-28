#ifndef EGG_GFXE_POST_EFFECT_BASE_H
#define EGG_GFXE_POST_EFFECT_BASE_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class CapTexture;

class PostEffectBase {
public:
    enum EBlendMode {
        EBlendMode_None,
        EBlendMode_Normal,
        EBlendMode_Add,
        EBlendMode_MulAdd,
        EBlendMode_4,
        EBlendMode_5,
        EBlendMode_AddAlpha,
        EBlendMode_7,
        EBlendMode_8,
        EBlendMode_Mul,
    };

protected:
    u16 mFlags;               // at 0x0
    EBlendMode mBlendMode;    // at 0x4
    CapTexture* mpCapTexture; // at 0x8
    f32 mOffsetX;             // at 0xC
    f32 mOffsetY;             // at 0x10
    f32 mScaleX;              // at 0x14
    f32 mScaleY;              // at 0x18

public:
    PostEffectBase();
    virtual ~PostEffectBase() {}                                 // at 0x8
    virtual void configure();                                    // at 0xC
    virtual void draw(f32 w, f32 h);                             // at 0x10
    virtual void reset();                                        // at 0x14
    virtual void setMaterialInternal();                          // at 0x18
    virtual void drawScreenInternal(f32 x, f32 y, f32 w, f32 h); // at 0x1C
    virtual void loadTextureInternal();                          // at 0x20

    static void setProjection(const Screen& rScreen);
    void drawTexture();

    bool isVisible() const {
        return !(mFlags & EFlag_Hide);
    }

    void setBlendMode(EBlendMode mode) {
        mBlendMode = mode;
    }

    CapTexture* getCapTexture() const {
        return mpCapTexture;
    }
    void setCapTexture(CapTexture* pCapTexture) {
#line 95
        EGG_ASSERT(pCapTexture);
        mpCapTexture = pCapTexture;
    }

protected:
    void setVtxState();
    void setMatColorChannel();
    void setMatInd();
    void setMatPE();
    void setBlendModeInternal();

    static void scaleRGBA(GXColor* pOut, const GXColor& rIn, f32 scale,
                          bool clamp);

private:
    enum {
        EFlag_Hide = 1 << 0,
    };
};

} // namespace EGG

#endif
