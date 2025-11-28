#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/math.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>

namespace EGG {

DECOMP_FORCEACTIVE_DTOR(eggPostEffectBase_cpp, PostEffectBase);

PostEffectBase::PostEffectBase()
    : mFlags(0),
      mBlendMode(EBlendMode_None),
      mpCapTexture(NULL),
      mOffsetX(0.0f),
      mOffsetY(0.0f),
      mScaleX(1.0f),
      mScaleY(1.0f) {}

void PostEffectBase::configure() {
    reset();
}

void PostEffectBase::reset() {}

void PostEffectBase::draw(f32 w, f32 h) {
    if (!isVisible()) {
        return;
    }

    setMaterialInternal();
    setVtxState();
    drawScreenInternal(mOffsetX, mOffsetY, mScaleX * w, mScaleY * h);
}

void PostEffectBase::setMaterialInternal() {}

void PostEffectBase::drawTexture() {
#line 61
    EGG_ASSERT(mpCapTexture);
    draw(mpCapTexture->getWidth(), mpCapTexture->getHeight());
}

void PostEffectBase::setVtxState() {
    DrawGX::SetVtxState(DrawGX::VTX_TYPE_SCREEN_TEXTURE_LU);
}

void PostEffectBase::drawScreenInternal(f32 x, f32 y, f32 w, f32 h) {
    nw4r::math::MTX34 mtx;
    PSMTXScale(mtx, w, h, 1.0f);
    PSMTXTransApply(mtx, mtx, x, y, 0.0f);

    DrawGX::DrawScreenTexture(mtx);
}

void PostEffectBase::loadTextureInternal() {
#line 98
    EGG_ASSERT(mpCapTexture);
    mpCapTexture->load(mpCapTexture->getLoadMap());
}

void PostEffectBase::setMatColorChannel() {
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_SIGN, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_SIGN, GX_AF_NONE);
    GXSetCullMode(GX_CULL_BACK);
}

void PostEffectBase::setMatInd() {
    GXSetNumIndStages(0);
}

void PostEffectBase::setMatPE() {
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);

    GXColor black = {0, 0, 0, 255};
    GXSetFog(GX_FOG_NONE, black, 0.0f, 1.0f, 0.0f, 1.0f);
    setBlendModeInternal();
}

void PostEffectBase::setBlendModeInternal() {
    switch (mBlendMode) {
    case EBlendMode_None: {
        DrawGX::SetBlendMode(DrawGX::BLEND_NONE);
        break;
    }

    case EBlendMode_Normal: {
        DrawGX::SetBlendMode(DrawGX::BLEND_NORMAL);
        break;
    }

    case EBlendMode_Add: {
        DrawGX::SetBlendMode(DrawGX::BLEND_ADD);
        break;
    }

    case EBlendMode_MulAdd: {
        DrawGX::SetBlendMode(DrawGX::BLEND_MUL_ADD);
        break;
    }

    case EBlendMode_4: {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCCLR, GX_BL_ONE, GX_LO_CLEAR);
        break;
    }

    case EBlendMode_5: {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCCLR, GX_BL_INVSRCCLR,
                       GX_LO_CLEAR);
        break;
    }

    case EBlendMode_AddAlpha: {
        DrawGX::SetBlendMode(DrawGX::BLEND_ADD_ALPHA);
        break;
    }

    case EBlendMode_7: {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
        break;
    }

    case EBlendMode_8: {
        GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                       GX_LO_CLEAR);
        break;
    }

    case EBlendMode_Mul: {
        DrawGX::SetBlendMode(DrawGX::BLEND_MUL);
        break;
    }
    }
}

void PostEffectBase::scaleRGBA(GXColor* pOut, const GXColor& rIn, f32 scale,
                               bool clamp) {
#line 205
    EGG_ASSERT(scale >= 0.f);

    f32 color[4];
    color[0] = rIn.r * scale;
    color[1] = rIn.g * scale;
    color[2] = rIn.b * scale;
    color[3] = rIn.a * scale;

    if (clamp) {
        pOut->r = color[0] < 255.0f ? color[0] : 255.0f;
        pOut->g = color[1] < 255.0f ? color[1] : 255.0f;
        pOut->b = color[2] < 255.0f ? color[2] : 255.0f;
        pOut->a = color[3] < 255.0f ? color[3] : 255.0f;
    } else {
        pOut->r = color[0];
        pOut->g = color[1];
        pOut->b = color[2];
        pOut->a = color[3];
    }
}

void PostEffectBase::setProjection(const Screen& rScreen) {
    Screen clone(rScreen);

    clone.SetProjectionAbsolute();
    clone.SetCanvasMode(Frustum::CANVASMODE_LU);
    clone.SetProjectionType(Frustum::PROJTYPE_ORTHO);

    clone.SetNearZ(0.0f);
    clone.SetFarZ(1.0f);
    clone.SetScale(nw4r::math::VEC3(1.0f, 1.0f, 1.0f));
    clone.SetOffset(nw4r::math::VEC2(0.0f, 0.0f));

    clone.SetProjectionGX();
}

} // namespace EGG
