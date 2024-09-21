#pragma ipa file

#include "eggScreenEffectBase.h"
#include "eggStateGX.h"
#include "eggTextureBuffer.h"
#include "eggPostEffectBase.h"
#include "eggPostEffectSimple.h"

namespace EGG
{
    ScreenEffectBase::EffectBuffer ScreenEffectBase::spBufferSet[cBufferType_Max];

    ScreenEffectBase::WorkView ScreenEffectBase::sWorkSpaceV;
    ScreenEffectBase::WorkView ScreenEffectBase::sWorkSpaceHideV;

    u32 ScreenEffectBase::sCaptureFlag;
    u32 ScreenEffectBase::sFlag;
    u32 ScreenEffectBase::D_804BEC58;
    u32 ScreenEffectBase::sPushCount;
    s32 ScreenEffectBase::sWorkBuffer = -1;

    ScreenEffectBase::ScreenEffectBase() : mFlags(EFFECT_VISIBLE)
    {
    }

    void ScreenEffectBase::copyFromAnother(const Screen& screen)
    {
        mScreen.CopyFromAnother(screen);
    }

    // https://decomp.me/scratch/w13Yi
    // - There seems to be some BSS pooling(?) regarding
    //   the workspace views
    // - The loop only increments one pointer somehow,
    //   despite getBuffer not returning the effect buffer
    void ScreenEffectBase::clean()
    {
        sFlag &= ~0x3;
        sWorkBuffer = -1;
        D_804BEC58 = 0;
        sPushCount = 0;

        for (s32 i = 0; i < cBufferType_Max; i++)
        {
            #line 72
            EGG_ASSERT(getBuffer( ( BufferType )i ) == NULL);
            spBufferSet[i].WORD_0x8 = 0;
        }
        
        sWorkSpaceV.x1 = sWorkSpaceHideV.x1 = 0.0f;
        sWorkSpaceV.y1 = sWorkSpaceHideV.y1 = 0.0f;
        sWorkSpaceV.x2 = sWorkSpaceHideV.x2 = 0.0f;
        sWorkSpaceV.y2 = sWorkSpaceHideV.y2 = 0.0f;
        sWorkSpaceV.FLOAT_0x10 = sWorkSpaceHideV.FLOAT_0x10 = 0.0f;
        sWorkSpaceV.FLOAT_0x14 = sWorkSpaceHideV.FLOAT_0x14 = 0.0f;
    }

    // https://decomp.me/scratch/RYUOH
    // - Despite the setBuffer inline being used, it seems like
    //   there is a temp variable for &spBufferSet[type]
    // - The cap texture copy filter application is not yet
    //   understood
    TextureBuffer* ScreenEffectBase::capture(BufferType type, bool clear) const
    {
        TextureBuffer* buffer;
        const Screen::DataEfb& efb = mScreen.GetDataEfb();

        if (getBuffer(type) == NULL)
        {
            f32 cap_x = efb.vp.x1;
            f32 cap_y = efb.vp.y1;

            // Doubles capture resolution
            bool upscale = false;

            switch(type)
            {
                case cBufferType_Hide_1_16:
                case cBufferType_1:
                    const f32 scale =
                        (type == cBufferType_Hide_1_16) ? 0.25f : 0.5f;
                    sWorkSpaceV.x2 = efb.vp.x2 * scale;
                    sWorkSpaceV.y2 = efb.vp.y2 * scale;

                    if (sCaptureFlag & 0x1)
                    {
                        sWorkSpaceHideV.x1 = 640.0f - sWorkSpaceV.x2;
                        sWorkSpaceHideV.y1 = 528.0f - sWorkSpaceV.y2;

                        const f32 overX = 640 - StateGX::getEfbWidth();
                        const f32 overY = 528 - StateGX::getEfbHeight();
                        sWorkSpaceHideV.x2 = sWorkSpaceV.x2 - overX;
                        sWorkSpaceHideV.y2 = sWorkSpaceV.y2 - overY;

                        if (sWorkSpaceHideV.x2 < 0.0f)
                            sWorkSpaceHideV.x2 = 0.0f;
                        if (sWorkSpaceHideV.y2 < 0.0f)
                            sWorkSpaceHideV.y2 = 0.0f;
                    }
                    else
                    {
                        sWorkSpaceHideV.x1 = efb.vp.x1;
                        sWorkSpaceHideV.y1 = efb.vp.y1;
                        sWorkSpaceHideV.x2 = sWorkSpaceV.x2;
                        sWorkSpaceHideV.y2 = sWorkSpaceV.y2;
                    }
                    
                    buffer = TextureBuffer::alloc(sWorkSpaceHideV.x2,
                        sWorkSpaceHideV.y2, GX_TF_RGBA8);
                    setBuffer(type, buffer);
                    
                    if (buffer != NULL)
                        buffer->clearFlag(0x80);
                    break;
                case cBufferType_2:
                    buffer = TextureBuffer::alloc(efb.vp.x2, efb.vp.y2,
                        GX_TF_RGBA8);
                    setBuffer(type, buffer);
                    buffer->clearFlag(0x80);
                    break;
                case cBufferType_3:
                    buffer = TextureBuffer::alloc(efb.vp.x2 / 2.0f,
                        efb.vp.y2 / 2.0f, GX_TF_RGBA8);
                    setBuffer(type, buffer);
                    upscale = true;
                    buffer->setFlag(0x40);
                    // TO-DO: Copy filter args are set here, not colors
                    // buffer->setColor_24((GXColor){21, 0, 0, 22});
                    // buffer->setColor_28((GXColor){21, 0, 0, 22});
                    break;
                default:
                    #line 158
                    EGG_ASSERT(0);
                    break;
            }

            if (getBuffer(type) != NULL)
            {
                spBufferSet[type].mpAllocBase = this;

                if (clear)
                {
                    getBuffer(type)->setFlag(0x10);
                    getBuffer(type)->setClearColor((GXColor){0, 0, 0, 0});
                }
            }

            #line 171
            EGG_ASSERT(cap_x >= 0.f && cap_y >= 0.f);
            getBuffer(type)->capture(cap_x, cap_y, upscale, -1);
        }

        return getBuffer(type);
    }

    bool ScreenEffectBase::release(BufferType type) const
    {
        if (spBufferSet[type].mpTexBuffer != NULL
            && spBufferSet[type].mpAllocBase == this)
        {
            spBufferSet[type].mpTexBuffer->free();
            clearBuffer(type);
            return true;
        }

        return false;
    }

    void ScreenEffectBase::doCapture(int buffer) const
    {
        if (buffer == 0)
        {
            if (sWorkBuffer == 1)
            {
                #line 207
                EGG_ASSERT(spBufferSet[cBufferType_Hide_1_16].mpAllocBase != NULL);
                spBufferSet[cBufferType_Hide_1_16].mpAllocBase->release(cBufferType_Hide_1_16);
            }

            capture(cBufferType_1, false);
            sWorkBuffer = 0;
        }
        else if (buffer == 1 && sWorkBuffer != 0)
        {
            capture(cBufferType_Hide_1_16, false);
            sWorkBuffer = 1;
        }
    }

    void ScreenEffectBase::setupGX(bool cache) const
    {
        BufferType type;

        if (sWorkBuffer != -1)
        {
            type = static_cast<BufferType>(-1);
            
            if (sWorkBuffer == 0)
                type = cBufferType_1;
            else if (sWorkBuffer == 1)
                type = cBufferType_Hide_1_16;

            if (this == spBufferSet[type].mpAllocBase)
            {
                if (!cache)
                {
                    StateGX::ScopedColor color(true);
                    StateGX::ScopedAlpha alpha(true);
                    StateGX::ScopedDither dither(false);

                    PostEffectBase::setProjection(mScreen);
                    
                    StateGX::GXSetViewport_(sWorkSpaceHideV.x1, sWorkSpaceHideV.y1,
                        sWorkSpaceHideV.x2, sWorkSpaceHideV.y2, 0.0f, 1.0f);
                    StateGX::GXSetScissor_(sWorkSpaceHideV.x1, sWorkSpaceHideV.y1,
                        sWorkSpaceHideV.x2, sWorkSpaceHideV.y2);
                    StateGX::GXSetScissorBoxOffset_(0, 0);

                    PostEffectSimple eff;
                    eff.onReset();
                    eff.setCapTexture(getBuffer(type));
                    eff.setBlendMode(0);

                    const f32 sx = mScreen.GetSizeX();
                    const f32 sy = mScreen.GetSizeY();
                    eff.draw(sx, sy);
                }

                release(type);

                sWorkBuffer = -1;
                sPushCount++;
            }
        }
    }

    const ScreenEffectBase::WorkView& ScreenEffectBase::setupView() const
    {
        FullView vp;
        const Screen::DataEfb& efb = mScreen.GetDataEfb();

        vp.x2 = efb.vp.x2 + sWorkSpaceV.x1;
        vp.x1 = sWorkSpaceV.x1;

        vp.y2 = efb.vp.y2 + sWorkSpaceV.y1;
        vp.y1 = sWorkSpaceV.y1;

        // Clamp for X overscan
        const f32 cx = (vp.x2 <= 640.0f) ? 0.0f : vp.x2 - 640.0f;
        vp.cx = efb.vp.x2 - cx;

        // Clamp for Y overscan
        const f32 cy = (vp.y2 <= 528.0f) ? 0.0f : vp.y2 - 528.0f;
        vp.cy = efb.vp.y2 - cy;

        vp.z1 = efb.vp.z1;
        vp.z2 = efb.vp.z2;
        
        StateGX::GXSetViewport_(vp.x1, vp.y1, vp.cx, vp.cy, vp.z1, vp.z2); 
        StateGX::GXSetScissor_(vp.x1, vp.y1, vp.cx, vp.cy);
        StateGX::GXSetScissorBoxOffset_(0, 0);
        
        return sWorkSpaceV;
    }
}
