#ifdef __DECOMP_NON_MATCHING

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

namespace EGG
{
    using namespace nw4r;

    // Non-matching
    ColorFader::ColorFader(f32 originX, f32 originY, f32 widthX, f32 widthY, ut::Color color, EStatus status)
    : mFlags(), mFadeTimer(0), mFrame(DEFAULT_FADE_LEN), mColor()
    {
        // mFrame = DEFAULT_FADE_LEN;
        mFadeTimer = 0;
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
        // Transparency is the responsibility of the fader
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
            return;
        }
        
        if (status != STATUS_PREPARE_OUT) return;
        mStatus = STATUS_PREPARE_OUT;
        mColor.mChannels.a = 0;
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

    // TO-DO: Make this still match with TBitFlag's methods
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
                success = mFlags.value & 1;
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
                    success = mFlags.value & 2;
                }
                fade = mFrame;
            }
            mColor.mChannels.a = (fade * 255) / mFrame;
        }

        return success;
    }

    // Non-matching
    void ColorFader::draw()
    {
        if (mColor.mChannels.a != 0)
        {
            math::MTX44 mtx;
            C_MTXOrtho(mStartY, mEndY, mStartX, mEndX, 0.0f, 1.0f, mtx);
            
            GXSetProjection(mtx, 1);
            GXSetViewport(mStartX, mStartY, mEndX - mStartX, mEndY - mStartY, 0.0f, 1.0f);
            GXSetScissor((u32)(mEndX - mStartX), (u32)(mEndY - mStartY), (u32)mStartY, (u32)mStartX);
            
            math::MTX34 mtx34;
            PSMTXIdentity(mtx34);
            GXLoadPosMtxImm(mtx34, 0);
            GXSetCurrentMtx(0);

            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(9, 1);
            GXSetVtxDesc(11, 0);
            GXSetVtxDesc(13, 0);
            GXSetVtxAttrFmt(0, 9, 1, 4, 0);

            GXSetNumChans(1);
            GXSetChanMatColor(4, mColor);
            GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);

            GXSetNumTexGens(0);
            GXSetNumIndStages(0);
            __GXSetIndirectMask(0);
            GXSetNumTevStages(1);

            GXSetTevOp(0, 4);
            GXSetTevOrder(0, 255, 255, 4);

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

            // 3x4 matrix??
            WGPIPE.f = mStartX;
            WGPIPE.f = mStartY;
            WGPIPE.f = 0.0f;

            WGPIPE.f = mEndX;
            WGPIPE.f = mStartY;
            WGPIPE.f = 0.0f;

            WGPIPE.f = mEndX;
            WGPIPE.f = mEndY;
            WGPIPE.f = 0.0f;

            WGPIPE.f = mStartX;
            WGPIPE.f = mEndY;
            WGPIPE.f = 0.0f;
        }
    }

    Fader::EStatus ColorFader::getStatus() const
    {
        return mStatus;
    }

    ColorFader::~ColorFader()
    {

    }
}

#else
#error This file has yet to be decompiled accurately. Use "eggColorFader.s" instead.
#endif