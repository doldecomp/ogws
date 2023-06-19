#include "eggColorFader.h"
#include "eggAssert.h"
#include "math_types.h"
#include <RevoSDK/math/mtx44.h>
#include <RevoSDK/GX/GXTransform.h>
#include <RevoSDK/GX/GXAttr.h>
#include <RevoSDK/GX/GXLight.h>
#include <RevoSDK/GX/GXBump.h>
#include <RevoSDK/GX/GXPixel.h>
#include <RevoSDK/GX/GXGeometry.h>
#include <RevoSDK/GX/GXVert.h>

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
        mColor.mChannels.r = color.mChannels.r;
        mColor.mChannels.g = color.mChannels.g;
        mColor.mChannels.b = color.mChannels.b;
    }

    void ColorFader::setStatus(Fader::EStatus status)
    {
        if (status == STATUS_PREPARE_IN)
        {
            mStatus = STATUS_PREPARE_IN;
            mColor.mChannels.a = 255;
        }
        else if (status == STATUS_PREPARE_OUT)
        {
            mStatus = STATUS_PREPARE_OUT;
            mColor.mChannels.a = 0;
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
            mColor.mChannels.a = 0;
        }
        else if (mStatus == STATUS_PREPARE_IN)
        {
            mColor.mChannels.a = 255;
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
            mColor.mChannels.a = 255 - (fade * 255) / mFrame;
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
            mColor.mChannels.a = (fade * 255) / mFrame;
        }

        return success;
    }

    void ColorFader::draw()
    {
        if (mColor.mChannels.a == 0) return;

        math::MTX44 mtx;
        C_MTXOrtho(mtx, mStartY, mEndY, mStartX, mEndX, 0.0f, 1.0f);
        
        GXSetProjection(mtx, 1);
        
        GXSetViewport(mStartX, mStartY, getWidth(), getHeight(), 0.0f, 1.0f);
        GXSetScissor((u32)mStartX, (u32)mStartY, (u32)getWidth(), (u32)getHeight());
        
        math::MTX34 mtx34;
        PSMTXIdentity(mtx34);
        GXLoadPosMtxImm(mtx34, 0);
        GXSetCurrentMtx(0);

        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_ATTR_VTX, 1);
        GXSetVtxDesc(GX_ATTR_VTX_CLR, 0);
        GXSetVtxDesc(GX_ATTR_VTX_TEX_COORD, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX, 1, 4, 0);

        GXSetNumChans(1);
        GXSetChanMatColor(GX_CHANNEL_ID_4, mColor);
        GXSetChanCtrl(GX_CHANNEL_ID_4, 0, 0, 0, 0, 0, 2);

        GXSetNumTexGens(0);
        GXSetNumIndStages(0);
        __GXSetIndirectMask(0);

        GXSetNumTevStages(1);
        GXSetTevOp(GX_TEV_STAGE_ID_0, 4);
        GXSetTevOrder(GX_TEV_STAGE_ID_0, GX_TEX_COORD_ID_INVALID, GX_TEX_MAP_ID_INVALID, 4);

        if (mColor.mChannels.a == 255)
        {
            GXSetBlendMode(0, 1, 0, 15);
        }
        else
        {
            GXSetBlendMode(1, 4, 5, 15);
        }

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(1);

        GXSetZMode(0, 0, 0);
        GXSetCullMode(2);

        GXBegin(0x80, 0, 4);

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