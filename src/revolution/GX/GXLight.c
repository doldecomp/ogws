#include <math.h>
#include <revolution/GX.h>

#define XF_MEM_LOBJ_SIZE 16

void GXInitLightAttn(GXLightObj* light, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb,
                     f32 kc) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;

    impl->aa = aa;
    impl->ab = ab;
    impl->ac = ac;
    impl->ka = ka;
    impl->kb = kb;
    impl->kc = kc;
}

void GXInitLightAttnA(GXLightObj* light, f32 a, f32 b, f32 c) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;

    impl->aa = a;
    impl->ab = b;
    impl->ac = c;
}

void GXInitLightAttnK(GXLightObj* light, f32 a, f32 b, f32 c) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;

    impl->ka = a;
    impl->kb = b;
    impl->kc = c;
}

void GXInitLightSpot(GXLightObj* light, f32 angle, GXSpotFn fn) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;
    f32 a, b, c, d;
    f32 rad;

    if (angle <= 0.0f || angle > 90.0f) {
        fn = GX_SP_OFF;
    }

    rad = cosf(M_PI * angle / 180.0f);

    switch (fn) {
    case GX_SP_FLAT:
        a = -1000.0f * rad;
        b = 1000.0f;
        c = 0.0f;
        break;
    case GX_SP_COS:
        b = 1.0f / (1.0f - rad);
        a = -rad * b;
        c = 0.0f;
        break;
    case GX_SP_COS2:
        c = 1.0f / (1.0f - rad);
        a = 0.0f;
        b = -rad * c;
        break;
    case GX_SP_SHARP:
        d = 1.0f / ((1.0f - rad) * (1.0f - rad));
        a = (rad * (rad - 2.0f)) * d;
        b = 2.0f * d;
        c = -d;
        break;
    case GX_SP_RING1:
        d = 1.0f / ((1.0f - rad) * (1.0f - rad));
        c = -4.0f * d;
        a = c * rad;
        b = 4.0f * (1.0f + rad) * d;
        break;
    case GX_SP_RING2:
        d = 1.0f / ((1.0f - rad) * (1.0f - rad));
        a = 1.0f - 2.0f * rad * rad * d;
        b = 4.0f * rad * d;
        c = -2.0f * d;
        break;
    case GX_SP_OFF:
    default:
        a = 1.0f;
        b = 0.0f;
        c = 0.0f;
        break;
    }

    impl->aa = a;
    impl->ab = b;
    impl->ac = c;
}

void GXInitLightDistAttn(GXLightObj* light, f32 distance, f32 brightness,
                         GXDistAttnFn fn) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;
    f32 a, b, c;

    if (distance < 0.0f) {
        fn = GX_DA_OFF;
    }

    if (brightness <= 0.0f || brightness >= 1.0f) {
        fn = GX_DA_OFF;
    }

    switch (fn) {
    case GX_DA_GENTLE:
        a = 1.0f;
        b = (1.0f - brightness) / (brightness * distance);
        c = 0.0f;
        break;
    case GX_DA_MEDIUM:
        a = 1.0f;
        b = (0.5f * (1.0f - brightness)) / (brightness * distance);
        c = (0.5f * (1.0f - brightness)) / (distance * (brightness * distance));
        break;
    case GX_DA_STEEP:
        a = 1.0f;
        b = 0.0f;
        c = (1.0f - brightness) / (distance * (brightness * distance));
        break;
    case GX_DA_OFF:
    default:
        a = 1.0f;
        b = 0.0f;
        c = 0.0f;
        break;
    }

    impl->ka = a;
    impl->kb = b;
    impl->kc = c;
}

void GXInitLightPos(GXLightObj* light, f32 x, f32 y, f32 z) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;

    impl->posX = x;
    impl->posY = y;
    impl->posZ = z;
}

void GXGetLightPos(const GXLightObj* light, f32* x, f32* y, f32* z) {
    const GXLightObjImpl* impl = (GXLightObjImpl*)light;

    *x = impl->posX;
    *y = impl->posY;
    *z = impl->posZ;
}

void GXInitLightDir(GXLightObj* light, f32 x, f32 y, f32 z) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;

    impl->dirX = -x;
    impl->dirY = -y;
    impl->dirZ = -z;
}

void GXGetLightDir(const GXLightObj* light, f32* x, f32* y, f32* z) {
    const GXLightObjImpl* impl = (GXLightObjImpl*)light;

    *x = -impl->dirX;
    *y = -impl->dirY;
    *z = -impl->dirZ;
}

void GXInitSpecularDir(GXLightObj* light, f32 x, f32 y, f32 z) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;
    f32 dirX, dirY, dirZ;
    f32 mag;

    dirX = -x;
    dirY = -y;
    dirZ = 1.0f + -z;

    mag = dirX * dirX + dirY * dirY + dirZ * dirZ;
    if (mag != 0.0f) {
        mag = 1.0f / sqrtf(mag);
    }

    impl->dirX = dirX * mag;
    impl->dirY = dirY * mag;
    impl->dirZ = dirZ * mag;

    impl->posX = -999999999999999999.0f * x;
    impl->posY = -999999999999999999.0f * y;
    impl->posZ = -999999999999999999.0f * z;
}

void GXInitLightColor(GXLightObj* light, GXColor color) {
    GXLightObjImpl* impl = (GXLightObjImpl*)light;
    *(u32*)&impl->color = *(u32*)&color;
}

// TODO: This inline is fake, and also is a fake match (r6 hardcoded)
inline void WriteLightObj(register volatile void* dst,
                          register const GXLightObjImpl* src) {
    register u32 color;
    register f32 ps_0, ps_1, ps_2, ps_3, ps_4, ps_5;

    // clang-format off
    asm volatile {
        lwz color, src->color
        xor r6, r6, r6 // make zero
        psq_l ps_0, GXLightObjImpl.aa(src),   0, 0
        psq_l ps_1, GXLightObjImpl.ac(src),   0, 0
        psq_l ps_2, GXLightObjImpl.kb(src),   0, 0
        psq_l ps_3, GXLightObjImpl.posX(src), 0, 0
        psq_l ps_4, GXLightObjImpl.posZ(src), 0, 0
        psq_l ps_5, GXLightObjImpl.dirY(src), 0, 0

        stw r6, 0(dst)
        stw r6, 0(dst)
        stw r6, 0(dst)
            
        stw color,   0(dst)
        psq_st ps_0, 0(dst), 0, 0
        psq_st ps_1, 0(dst), 0, 0
        psq_st ps_2, 0(dst), 0, 0
        psq_st ps_3, 0(dst), 0, 0
        psq_st ps_4, 0(dst), 0, 0
        psq_st ps_5, 0(dst), 0, 0
    }
    // clang-format on
}

void GXLoadLightObjImm(const GXLightObj* light, GXLightID id) {
    const GXLightObjImpl* impl;
    u32 num;

    impl = (GXLightObjImpl*)light;
    num = 31 - __cntlzw(id);
    num = (num % 8) * XF_MEM_LOBJ_SIZE;

    GX_XF_LOAD_REGS(XF_MEM_LOBJ_SIZE - 1, num + GX_XF_MEM_LIGHTOBJ);
    WriteLightObj(&WGPIPE, impl);
    gxdt->lastWriteWasXF = TRUE;
}

void GXLoadLightObjIndx(u16 index, GXLightID id) {
    u32 num;

    num = 31 - __cntlzw(id);
    num = (num % 8) * XF_MEM_LOBJ_SIZE;

    GX_FIFO_LOAD_INDX_D(num + GX_XF_MEM_LIGHTOBJ, XF_MEM_LOBJ_SIZE - 1, index);
    gxdt->lastWriteWasXF = TRUE;
}

void GXSetChanAmbColor(GXChannelID chan, GXColor color) {
    u32 ambColor;
    u32 colorId;

    switch (chan) {
    case GX_COLOR0:
        ambColor =
            GX_BITSET_TRUNC(*(u32*)&gxdt->ambColors[0], 0, 24, *(u32*)&color);
        colorId = 0;
        break;
    case GX_COLOR1:
        ambColor =
            GX_BITSET_TRUNC(*(u32*)&gxdt->ambColors[1], 0, 24, *(u32*)&color);
        colorId = 1;
        break;
    case GX_ALPHA0:
        ambColor = GX_BITSET_TRUNC(*(u32*)&gxdt->ambColors[0], 24, 8, color.a);
        colorId = 0;
        break;
    case GX_ALPHA1:
        ambColor = GX_BITSET_TRUNC(*(u32*)&gxdt->ambColors[1], 24, 8, color.a);
        colorId = 1;
        break;
    case GX_COLOR0A0:
        ambColor = *(u32*)&color;
        colorId = 0;
        break;
    case GX_COLOR1A1:
        ambColor = *(u32*)&color;
        colorId = 1;
        break;
    default:
        return;
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_AMB_COLOR0 << colorId;
    *(u32*)&gxdt->ambColors[colorId] = ambColor;
}

void GXSetChanMatColor(GXChannelID chan, GXColor color) {
    u32 matColor;
    u32 colorId;

    switch (chan) {
    case GX_COLOR0:
        matColor =
            GX_BITSET_TRUNC(*(u32*)&gxdt->matColors[0], 0, 24, *(u32*)&color);
        colorId = 0;
        break;
    case GX_COLOR1:
        matColor =
            GX_BITSET_TRUNC(*(u32*)&gxdt->matColors[1], 0, 24, *(u32*)&color);
        colorId = 1;
        break;
    case GX_ALPHA0:
        matColor = GX_BITSET_TRUNC(*(u32*)&gxdt->matColors[0], 24, 8, color.a);
        colorId = 0;
        break;
    case GX_ALPHA1:
        matColor = GX_BITSET_TRUNC(*(u32*)&gxdt->matColors[1], 24, 8, color.a);
        colorId = 1;
        break;
    case GX_COLOR0A0:
        matColor = *(u32*)&color;
        colorId = 0;
        break;
    case GX_COLOR1A1:
        matColor = *(u32*)&color;
        colorId = 1;
        break;
    default:
        return;
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_MAT_COLOR0 << colorId;
    *(u32*)&gxdt->matColors[colorId] = matColor;
}

void GXSetNumChans(u8 num) {
    GX_BP_SET_GENMODE_NUMCOLORS(gxdt->genMode, num);
    gxdt->gxDirtyFlags |= GX_DIRTY_NUM_COLORS;
    gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
}

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc ambSrc,
                   GXColorSrc matSrc, GXLightID lightMask, GXDiffuseFn diffFn,
                   GXAttnFn attnFn) {
    u32 regIdx = (u32)chan % 4;
    u32 reg = 0;

    GX_XF_SET_COLOR0CNTRL_LIGHT(reg, enable);
    GX_XF_SET_COLOR0CNTRL_MATSRC(reg, matSrc);
    GX_XF_SET_COLOR0CNTRL_AMBSRC(reg, ambSrc);
    GX_XF_SET_COLOR0CNTRL_DIFFUSEATTN(reg, attnFn == GX_AF_SPEC ? GX_DF_NONE
                                                                : diffFn);
    GX_XF_SET_COLOR0CNTRL_ATTNENABLE(reg, attnFn != GX_AF_NONE);
    GX_XF_SET_COLOR0CNTRL_ATTNSELECT(reg, attnFn != GX_AF_SPEC);
    GX_XF_SET_COLOR0CNTRL_LMASKHI(reg, (u32)lightMask);
    GX_XF_SET_COLOR0CNTRL_LMASKLO(reg, (u32)lightMask >> 4);

    gxdt->colorControl[regIdx] = reg;
    gxdt->gxDirtyFlags |= GX_DIRTY_CHAN_COLOR0 << (regIdx);

    if (chan == GX_COLOR0A0) {
        gxdt->colorControl[GX_ALPHA0] = reg;
        gxdt->gxDirtyFlags |= GX_DIRTY_CHAN_COLOR0;
        gxdt->gxDirtyFlags |= GX_DIRTY_CHAN_ALPHA0;
    } else if (chan == GX_COLOR1A1) {
        gxdt->colorControl[GX_ALPHA1] = reg;
        gxdt->gxDirtyFlags |= GX_DIRTY_CHAN_COLOR1;
        gxdt->gxDirtyFlags |= GX_DIRTY_CHAN_ALPHA1;
    }
}
