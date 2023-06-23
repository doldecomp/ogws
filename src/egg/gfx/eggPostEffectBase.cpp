#include "eggPostEffectBase.h"
#include "eggAssert.h"
#include "eggCapTexture.h"
#include "eggDrawGX.h"
#include "eggScreen.h"
#include <revolution/MTX.h>
#include <revolution/GX.h>

namespace EGG
{
    using namespace nw4r;

    namespace
    {
        void UNUSED_FUNC_ORDER_POSTEFFECTBASE(PostEffectBase *eff)
        {
            eff->~PostEffectBase();
        }
    }

    PostEffectBase::PostEffectBase()
        : mFlags(0), mBlendMode(0), mpCapTexture(NULL),
        mOffsetX(0.0f), mOffsetY(0.0f), mScaleX(1.0f), mScaleY(1.0f)
    {
    }

    void PostEffectBase::onReset()
    {
        reset();
    }

    void PostEffectBase::reset()
    {
    }

    void PostEffectBase::draw(f32 width, f32 height)
    {
        if (isVisible())
        {
            preDraw();
            setVtxState();
            drawDL(mOffsetX, mOffsetY, mScaleX * width, mScaleY * height);
        }
    }

    void PostEffectBase::preDraw()
    {
    }

    void PostEffectBase::drawTexture()
    {
        #line 61
        EGG_ASSERT(mpCapTexture);
        draw(mpCapTexture->getWidth(), mpCapTexture->getHeight());
    }

    void PostEffectBase::setVtxState()
    {
        DrawGX::SetVtxState(DrawGX::VTX_TYPE_11);
    }

    void PostEffectBase::drawDL(f32 ofsX, f32 ofsY, f32 width, f32 height)
    {
        Mtx pos;
        PSMTXScale(pos, width, height, 1.0f);
        PSMTXTransApply(pos, pos, ofsX, ofsY, 0.0f);
        GXLoadPosMtxImm(pos, 0);

        DrawGX::DisplayList *dlist = DrawGX::GetDisplayList(16);
        GXCallDisplayList(dlist->m_list, dlist->m_size);
    }

    void PostEffectBase::loadTexObj()
    {
        #line 98
        EGG_ASSERT(mpCapTexture);
        mpCapTexture->load(mpCapTexture->getLoadMap());
    }

    void PostEffectBase::setMatColorChannel()
    {
        GXSetNumChans(0);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_SIGN, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR1A1, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_SIGN, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
    }

    void PostEffectBase::setMatInd()
    {
        GXSetNumIndStages(0);
    }

    void PostEffectBase::setMatPE()
    {
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetZMode(0, GX_ALWAYS, 0);

        GXColor black = {0, 0, 0, 255};
        GXSetFog(GX_FOG_NONE, black, 0.0f, 1.0f, 0.0f, 1.0f);
        setBlendModeInternal();
    }

    void PostEffectBase::setBlendModeInternal()
    {
        switch(mBlendMode)
        {
            case 0:
                DrawGX::SetBlendMode(DrawGX::BLEND_9);
                break;
            case 1:
                DrawGX::SetBlendMode(DrawGX::BLEND_0);
                break;
            case 2:
                DrawGX::SetBlendMode(DrawGX::BLEND_2);
                break;
            case 3:
                DrawGX::SetBlendMode(DrawGX::BLEND_4);
                break;
            case 4:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCCLR, GX_BL_ONE, GX_LO_CLEAR);
                break;
            case 5:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCCLR, GX_BL_INVSRCCLR, GX_LO_CLEAR);
                break;
            case 6:
                DrawGX::SetBlendMode(DrawGX::BLEND_3);
                break;
            case 7:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
                break;
            case 8:
                GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                break;
            case 9:
                DrawGX::SetBlendMode(DrawGX::BLEND_6);
                break;
        }
    }

    void PostEffectBase::scaleColor(GXColor& out, const GXColor& in, f32 scale, bool clamp)
    {
        #line 205
        EGG_ASSERT(scale >= 0.f);

        f32 color_f[4];
        color_f[0] = in.r * scale;
        color_f[1] = in.g * scale;
        color_f[2] = in.b * scale;
        color_f[3] = in.a * scale;

        if (clamp)
        {
            out.r = (color_f[0] < 255.0f) ? color_f[0] : 255.0f;
            out.g = (color_f[1] < 255.0f) ? color_f[1] : 255.0f;
            out.b = (color_f[2] < 255.0f) ? color_f[2] : 255.0f;
            out.a = (color_f[3] < 255.0f) ? color_f[3] : 255.0f;
        }
        else
        {
            out.r = color_f[0];
            out.g = color_f[1];
            out.b = color_f[2];
            out.a = color_f[3];
        }
    }

    void PostEffectBase::setProjection(const Screen& screen)
    {
        Screen clone(screen);
        
        clone.SetFlag(0x80);
        clone.SetCanvasMode(Frustum::CANVASMODE_1);
        clone.SetProjectionType(Frustum::PROJ_ORTHO);

        clone.SetNearZ(0.0f);
        clone.SetFarZ(1.0f);
        clone.SetScale(math::VEC3(1.0f, 1.0f, 1.0f));
        clone.SetOffset(math::VEC2(0.0f, 0.0f));

        clone.Screen::SetProjectionGX();
    }
}