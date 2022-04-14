#include "eggPostEffectBase.h"
#include "eggAssert.h"
#include "eggCapTexture.h"
#include "eggDrawGX.h"
#include "eggScreen.h"
#include <RevoSDK/math/mtx.h>
#include <RevoSDK/GX/GXTransform.h>
#include <RevoSDK/GX/GXDisplayList.h>
#include <RevoSDK/GX/GXLight.h>
#include <RevoSDK/GX/GXGeometry.h>
#include <RevoSDK/GX/GXBump.h>
#include <RevoSDK/GX/GXPixel.h>

namespace EGG
{
    using namespace nw4r;
    
    PostEffectBase::~PostEffectBase()
    {
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
        GXSetChanCtrl(GX_CHANNEL_ID_4, 0, 0, 0, 0, 1, 2);
        GXSetChanCtrl(GX_CHANNEL_ID_5, 0, 0, 0, 0, 1, 2);
        GXSetCullMode(2);
    }

    void PostEffectBase::setMatInd()
    {
        GXSetNumIndStages(0);
    }

    void PostEffectBase::setMatPE()
    {
        GXSetAlphaCompare(7, 0, 1, 7, 0);
        GXSetZMode(0, 7, 0);

        GXColor black = {0, 0, 0, 255};
        GXSetFog(GX_FOG_TYPE_0, black, 0.0f, 1.0f, 0.0f, 1.0f);
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
                GXSetBlendMode(1, 3, 1, 0);
                break;
            case 5:
                GXSetBlendMode(1, 3, 3, 0);
                break;
            case 6:
                DrawGX::SetBlendMode(DrawGX::BLEND_3);
                break;
            case 7:
                GXSetBlendMode(1, 5, 1, 0);
                break;
            case 8:
                GXSetBlendMode(3, 4, 5, 0);
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
        
        clone.setFlag(0x80);

        if (clone.getCanvasMode() != Frustum::CANVASMODE_1)
        {
            clone.setFlag(0x1);
            clone.setCanvasMode(Frustum::CANVASMODE_1);
        }

        clone.setProjectionType(Frustum::PROJ_ORTHO);

        clone.setNearZ(0.0f);
        clone.setFarZ(1.0f);
        clone.setScale(math::VEC3(1.0f, 1.0f, 1.0f));
        clone.setOffset(math::VEC2(0.0f, 0.0f));

        clone.Screen::SetProjectionGX();
    }
}