#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

ScreenEffectBase::EffectBuffer ScreenEffectBase::spBufferSet[cBufferType_Max];

f32 ScreenEffectBase::sWorkSpaceV[GX_VIEWPORT_SZ];
f32 ScreenEffectBase::sWorkSpaceHideV[GX_VIEWPORT_SZ];

u16 ScreenEffectBase::sCaptureFlag = 0;
u32 ScreenEffectBase::sFlag = 0;

u32 ScreenEffectBase::D_804BEC58 = 0;
u32 ScreenEffectBase::sPushCount = 0;

ScreenEffectBase::WorkBuffer ScreenEffectBase::sWorkBuffer = cWorkBuffer_None;

ScreenEffectBase::ScreenEffectBase() : mFlags(cFlag_Enable) {}

void ScreenEffectBase::setScreen(const Screen& rScreen) {
    mScreen.CopyFromAnother(rScreen);
}

void ScreenEffectBase::Clean() {
    sFlag &= ~(cGlobalFlag_0 | cGlobalFlag_1);
    sWorkBuffer = cWorkBuffer_None;
    D_804BEC58 = 0;
    sPushCount = 0;

    for (int i = 0; i < cBufferType_Max; i++) {
#line 72
        EGG_ASSERT(getBuffer( ( BufferType )i ) == NULL);
        spBufferSet[i].unk8 = 0;
    }

    for (int i = 0; i < GX_VIEWPORT_SZ; i++) {
        sWorkSpaceV[i] = 0.0f;
        sWorkSpaceHideV[i] = 0.0f;
    }
}

TextureBuffer* ScreenEffectBase::captureEfb(BufferType type, bool alpha) const {
    const Screen::DataEfb& rEfb = mScreen.GetDataEfb();
    TextureBuffer* pTexture = NULL;

    if (getBuffer(type) == NULL) {
        f32 cap_x = rEfb.vp.x;
        f32 cap_y = rEfb.vp.y;

        bool mipmap = false;

        switch (type) {
        case cBufferType_Hide_1_16:
        case cBufferType_1: {
            f32 scale = type == cBufferType_Hide_1_16 ? 0.25f : 0.5f;

            sWorkSpaceV[GX_VIEWPORT_W] = rEfb.vp.width * scale;
            sWorkSpaceV[GX_VIEWPORT_H] = rEfb.vp.height * scale;

            if (sCaptureFlag & 0x1) {
                // clang-format off
                sWorkSpaceV[GX_VIEWPORT_L]     = EFFECT_WIDTH - sWorkSpaceV[GX_VIEWPORT_W];
                sWorkSpaceHideV[GX_VIEWPORT_L] = sWorkSpaceV[GX_VIEWPORT_L];
                sWorkSpaceV[GX_VIEWPORT_T]     = EFFECT_HEIGHT - sWorkSpaceV[GX_VIEWPORT_H];
                sWorkSpaceHideV[GX_VIEWPORT_T] = sWorkSpaceV[GX_VIEWPORT_T];
                // clang-format on

                sWorkSpaceHideV[GX_VIEWPORT_W] =
                    sWorkSpaceV[GX_VIEWPORT_W] -
                    (EFFECT_WIDTH - StateGX::getEfbWidth());

                sWorkSpaceHideV[GX_VIEWPORT_H] =
                    sWorkSpaceV[GX_VIEWPORT_H] -
                    (EFFECT_HEIGHT - StateGX::getEfbHeight());

                if (sWorkSpaceHideV[GX_VIEWPORT_W] < 0.0f) {
                    sWorkSpaceHideV[GX_VIEWPORT_W] = 0.0f;
                }

                if (sWorkSpaceHideV[GX_VIEWPORT_H] < 0.0f) {
                    sWorkSpaceHideV[GX_VIEWPORT_H] = 0.0f;
                }

            } else {
                sWorkSpaceHideV[GX_VIEWPORT_L] = rEfb.vp.x;
                sWorkSpaceHideV[GX_VIEWPORT_T] = rEfb.vp.y;
                sWorkSpaceHideV[GX_VIEWPORT_W] = sWorkSpaceV[GX_VIEWPORT_W];
                sWorkSpaceHideV[GX_VIEWPORT_H] = sWorkSpaceV[GX_VIEWPORT_H];
            }

            cap_x = sWorkSpaceV[GX_VIEWPORT_L];
            cap_y = sWorkSpaceV[GX_VIEWPORT_T];

            pTexture = TextureBuffer::alloc(sWorkSpaceHideV[GX_VIEWPORT_W],
                                            sWorkSpaceHideV[GX_VIEWPORT_H],
                                            GX_TF_RGBA8);

            setBuffer(type, pTexture);

            if (pTexture != NULL) {
                pTexture->disablePixModeSync();
            }
            break;
        }

        case cBufferType_2: {
            pTexture = TextureBuffer::alloc(rEfb.vp.width, rEfb.vp.height,
                                            GX_TF_RGBA8);

            setBuffer(type, pTexture);
            pTexture->disablePixModeSync();
            break;
        }

        case cBufferType_3: {
            pTexture = TextureBuffer::alloc(rEfb.vp.width / 2,
                                            rEfb.vp.height / 2, GX_TF_RGBA8);

            setBuffer(type, pTexture);
            pTexture->setVFilterBlur();
            mipmap = true;
            break;
        }

        default: {
#line 158
            EGG_ASSERT(0);
            break;
        }
        }

        if (getBuffer(type) != NULL) {
            spBufferSet[type].mpAllocBase = this;

            if (alpha) {
                getBuffer(type)->enableAlphaUpdate();
                getBuffer(type)->setClearColor((GXColor){0, 0, 0, 0});
            }

#line 171
            EGG_ASSERT(cap_x >= 0.f && cap_y >= 0.f);
            getBuffer(type)->capture(cap_x, cap_y, mipmap);
        }
    }

    return getBuffer(type);
}

bool ScreenEffectBase::releaseEfb(BufferType type) const {
    if (spBufferSet[type].mpTexBuffer != NULL &&
        spBufferSet[type].mpAllocBase == this) {

        spBufferSet[type].mpTexBuffer->free();
        clearBuffer(type);
        return true;
    }

    return false;
}

void ScreenEffectBase::pushWorkBuffer(WorkBuffer buffer) const {
    if (buffer == cWorkBuffer_0) {
        if (sWorkBuffer == cWorkBuffer_1) {
#line 207
            EGG_ASSERT(spBufferSet[cBufferType_Hide_1_16].mpAllocBase != NULL);

            spBufferSet[cBufferType_Hide_1_16].mpAllocBase-> //
                releaseEfb(cBufferType_Hide_1_16);
        }

        captureEfb(cBufferType_1, false);
        sWorkBuffer = cWorkBuffer_0;

    } else if (buffer == cWorkBuffer_1 && sWorkBuffer != cWorkBuffer_0) {
        captureEfb(cBufferType_Hide_1_16, false);
        sWorkBuffer = cWorkBuffer_1;
    }
}

void ScreenEffectBase::popWorkBuffer(bool hide) const {
    BufferType type;

    if (sWorkBuffer != cWorkBuffer_None) {
        type = cBufferType_None;

        if (sWorkBuffer == cWorkBuffer_0) {
            type = cBufferType_1;
        } else if (sWorkBuffer == cWorkBuffer_1) {
            type = cBufferType_Hide_1_16;
        }

        if (this == spBufferSet[type].mpAllocBase) {
            if (!hide) {
                StateGX::AutoColorUpdate colorLock(true);
                StateGX::AutoAlphaUpdate alphaLock(true);
                StateGX::AutoDither ditherLock(false);

                PostEffectBase::setProjection(mScreen);

                StateGX::GXSetViewport_(sWorkSpaceHideV[GX_VIEWPORT_L],
                                        sWorkSpaceHideV[GX_VIEWPORT_T],
                                        sWorkSpaceHideV[GX_VIEWPORT_W],
                                        sWorkSpaceHideV[GX_VIEWPORT_H], //
                                        0.0f, 1.0f);

                StateGX::GXSetScissor_(sWorkSpaceHideV[GX_VIEWPORT_L],
                                       sWorkSpaceHideV[GX_VIEWPORT_T],
                                       sWorkSpaceHideV[GX_VIEWPORT_W],
                                       sWorkSpaceHideV[GX_VIEWPORT_H]);

                StateGX::GXSetScissorBoxOffset_(0, 0);

                PostEffectSimple eff;
                eff.configure();
                eff.setCapTexture(getBuffer(type));
                eff.setBlendMode(PostEffectBase::cBlendMode_None);
                eff.draw(mScreen.GetSize().x, mScreen.GetSize().y);
            }

            releaseEfb(type);

            sWorkBuffer = cWorkBuffer_None;
            sPushCount++;
        }
    }
}

const f32* ScreenEffectBase::shiftWorkSpaceViewportGX() const {
    const Screen::DataEfb& rEfb = mScreen.GetDataEfb();

    struct {
        f32 real_w, real_h;
        f32 vp[GX_VIEWPORT_SZ];
    } param;

    param.real_w = rEfb.vp.width + sWorkSpaceV[GX_VIEWPORT_L];
    param.real_h = rEfb.vp.height + sWorkSpaceV[GX_VIEWPORT_T];

    param.vp[GX_VIEWPORT_L] = sWorkSpaceV[GX_VIEWPORT_L];
    param.vp[GX_VIEWPORT_T] = sWorkSpaceV[GX_VIEWPORT_T];

    f32 over_x =
        param.real_w <= EFFECT_WIDTH ? 0.0f : param.real_w - EFFECT_WIDTH;

    param.vp[GX_VIEWPORT_W] = rEfb.vp.width - over_x;

    f32 over_y =
        param.real_h <= EFFECT_HEIGHT ? 0.0f : param.real_h - EFFECT_HEIGHT;

    param.vp[GX_VIEWPORT_H] = rEfb.vp.height - over_y;

    param.vp[GX_VIEWPORT_N] = rEfb.vp.near;
    param.vp[GX_VIEWPORT_F] = rEfb.vp.far;

    StateGX::GXSetViewport_(param.vp[GX_VIEWPORT_L], param.vp[GX_VIEWPORT_T],
                            param.vp[GX_VIEWPORT_W], param.vp[GX_VIEWPORT_H],
                            param.vp[GX_VIEWPORT_N], param.vp[GX_VIEWPORT_F]);

    StateGX::GXSetScissor_(param.vp[GX_VIEWPORT_L], param.vp[GX_VIEWPORT_T],
                           param.vp[GX_VIEWPORT_W], param.vp[GX_VIEWPORT_H]);

    StateGX::GXSetScissorBoxOffset_(0, 0);

    return sWorkSpaceV;
}

} // namespace EGG
