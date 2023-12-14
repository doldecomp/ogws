#include "eggColorFader.h"
#include "eggAssert.h"
#include "math_types.h"
#include <revolution/MTX.h>
#include <revolution/GX.h>

#define DEFAULT_FADE_LEN 20

namespace EGG
{
    using namespace nw4r;

    ColorFader::ColorFader(f32 originX, f32 originY, f32 widthX, f32 widthY, ut::Color color, EStatus status)
        : mFlags(), mFadeTimer(0), mFrame(DEFAULT_FADE_LEN), mColor()
    {
        mStartX = originX;
        mStartY = originY;
        mEndX = originX + widthX;
        mEndY = originY + widthY;

        setColor(color);
        setStatus(status);

        mFlags.set(2);
    }

    void ColorFader::setFrame(u16 frame)
    {
        #line 63
        EGG_ASSERT(frame != 0);

        mFrame = frame;
    }

    void ColorFader::setColor(ut::Color color)
    {
        mColor.r = color.r;
        mColor.g = color.g;
        mColor.b = color.b;
    }

    void ColorFader::setStatus(Fader::EStatus status)
    {
        if (status == STATUS_PREPARE_IN)
        {
            mStatus = STATUS_PREPARE_IN;
            mColor.a = 255;
        }
        else if (status == STATUS_PREPARE_OUT)
        {
            mStatus = STATUS_PREPARE_OUT;
            mColor.a = 0;
        }
    }

    bool ColorFader::fadeIn()
    {
        bool b = (mStatus == STATUS_PREPARE_IN);
        if (b)
        {
            mStatus = STATUS_FADE_IN;
            mFadeTimer = 0;
        }

        return b;
    }

    bool ColorFader::fadeOut()
    {
        bool b = (mStatus == STATUS_PREPARE_OUT);
        if (b)
        {
            mStatus = STATUS_FADE_OUT;
            mFadeTimer = 0;
        }

        return b;
    }

    bool ColorFader::calc()
    {
        bool success = false;

        if (mStatus == STATUS_PREPARE_OUT)
        {
            mColor.a = 0;
        }
        else if (mStatus == STATUS_PREPARE_IN)
        {
            mColor.a = 255;
        }
        else if (mStatus == STATUS_FADE_IN)
        {
            u16 fade = mFadeTimer;
            if (mFadeTimer++ > mFrame)
            {
                mStatus = STATUS_PREPARE_OUT;
                success = mFlags.onBit(0);
                fade = mFrame;
            }
            mColor.a = 255 - (fade * 255) / mFrame;
        }
        else if (mStatus == STATUS_FADE_OUT)
        {
            u16 fade = mFadeTimer++;
            if (fade > mFrame)
            {
                if (fade > mFrame + 1)
                {
                    mStatus = STATUS_PREPARE_IN;
                    success = mFlags.onBit(1);
                }
                fade = mFrame;
            }
            mColor.a = (fade * 255) / mFrame;
        }

        return success;
    }

    void ColorFader::draw()
    {
        if (mColor.a == 0) return;

        math::MTX44 mtx;
        C_MTXOrtho(mtx, mStartY, mEndY, mStartX, mEndX, 0.0f, 1.0f);
        
        GXSetProjection(mtx, GX_ORTHOGRAPHIC);
        
        GXSetViewport(mStartX, mStartY, getWidth(), getHeight(), 0.0f, 1.0f);
        GXSetScissor((u32)mStartX, (u32)mStartY, (u32)getWidth(), (u32)getHeight());
        
        math::MTX34 mtx34;
        PSMTXIdentity(mtx34);
        GXLoadPosMtxImm(mtx34, 0);
        GXSetCurrentMtx(0);

        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_NONE);
        GXSetVtxDesc(GX_VA_TEX0, GX_NONE);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

        GXSetNumChans(1);
        GXSetChanMatColor(GX_COLOR0A0, mColor);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXSetNumTexGens(0);
        GXSetNumIndStages(0);
        __GXSetIndirectMask(0);

        GXSetNumTevStages(1);
        GXSetTevOp(GX_TEVSTAGE0, GX_BLEND);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

        if (mColor.a == 255)
        {
            GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
        }
        else
        {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        }

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(1);

        GXSetZMode(0, GX_NEVER, 0);
        GXSetCullMode(GX_CULL_BACK);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);

        GXPosition3f32(mStartX, mStartY, 0.0f);
        GXPosition3f32(mEndX, mStartY, 0.0f);
        GXPosition3f32(mEndX, mEndY, 0.0f);
        GXPosition3f32(mStartX, mEndY, 0.0f);

        GXEnd();
    }

    Fader::EStatus ColorFader::getStatus() const
    {
        return mStatus;
    }

    ColorFader::~ColorFader()
    {

    }
}