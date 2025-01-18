#include <math.h>
#include <revolution/GX.h>

void GXSetFog(GXFogType type, GXColor color, f32 start, f32 end, f32 near,
              f32 far) {
    f32 a, c;
    u32 a_bits, c_bits;

    u32 fogColorReg = 0;
    u32 fogParamReg0 = 0;
    u32 fogParamReg1 = 0;
    u32 fogParamReg2 = 0;
    u32 fogParamReg3 = 0;

    u32 fsel = GX_FOG_GET_FSEL(type);
    BOOL ortho = GX_FOG_GET_PROJ(type);

    if (ortho) {
        if (far == near || end == start) {
            a = 0.0f;
            c = 0.0f;
        } else {
            a = (1.0f / (end - start)) * (far - near);
            c = (1.0f / (end - start)) * (start - near);
        }
    } else {
        f32 f28, f25, f24;
        u32 expB, magB, shiftB;

        if (far == near || end == start) {
            f28 = 0.0f;
            f25 = 0.5f;
            f24 = 0.0f;
        } else {
            f28 = (far * near) / ((far - near) * (end - start));
            f25 = far / (far - near);
            f24 = start / (end - start);
        }

        expB = 0;
        while (f25 > 1.0l) {
            f25 /= 2.0f;
            expB++;
        }
        while (f25 > 0.0f && f25 < 0.5l) {
            f25 *= 2.0f;
            expB--;
        }

        a = f28 / (1 << expB + 1);
        magB = 8388638.0f * f25;
        shiftB = expB + 1;
        c = f24;

        GX_BP_SET_FOGPARAM1_B_MAG(fogParamReg1, magB);
        GX_BP_SET_OPCODE(fogParamReg1, GX_BP_REG_FOGPARAM1);
        GX_BP_SET_FOGPARAM2_B_SHIFT(fogParamReg2, shiftB);
        GX_BP_SET_OPCODE(fogParamReg2, GX_BP_REG_FOGPARAM2);
    }

    a_bits = *(u32*)&a;
    c_bits = *(u32*)&c;

    GX_BP_SET_FOGPARAM0_A_MANT(fogParamReg0, a_bits >> 12 & 0x7FF);
    GX_BP_SET_FOGPARAM0_A_EXP(fogParamReg0, a_bits >> 23 & 0xFF);
    GX_BP_SET_FOGPARAM0_A_SIGN(fogParamReg0, a_bits >> 31);
    GX_BP_SET_OPCODE(fogParamReg0, GX_BP_REG_FOGPARAM0);

    GX_BP_SET_FOGPARAM3_C_MANT(fogParamReg3, c_bits >> 12 & 0x7FF);
    GX_BP_SET_FOGPARAM3_C_EXP(fogParamReg3, c_bits >> 23 & 0xFF);
    GX_BP_SET_FOGPARAM3_C_SIGN(fogParamReg3, c_bits >> 31);
    GX_BP_SET_FOGPARAM3_PROJ(fogParamReg3, ortho);
    GX_BP_SET_FOGPARAM3_FSEL(fogParamReg3, fsel);
    GX_BP_SET_OPCODE(fogParamReg3, GX_BP_REG_FOGPARAM3);

    GX_BP_SET_FOGCOLOR_RGB(fogColorReg, *(u32*)&color >> 8);
    GX_BP_SET_OPCODE(fogColorReg, GX_BP_REG_FOGCOLOR);

    GX_BP_LOAD_REG(fogParamReg0);
    GX_BP_LOAD_REG(fogParamReg1);
    GX_BP_LOAD_REG(fogParamReg2);
    GX_BP_LOAD_REG(fogParamReg3);
    GX_BP_LOAD_REG(fogColorReg);

    gxdt->lastWriteWasXF = FALSE;
}

void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, const Mtx44 proj) {
    f32 f31, f30, f29, f28, f27;
    u32 i;

    if (proj[3][3] == 0.0l) {
        f30 = proj[2][3] / (proj[2][2] - 1.0f);
        f28 = f30 / proj[0][0];
    } else {
        f28 = 1.0f / proj[0][0];
        f30 = M_SQRT3 * f28;
    }

    f29 = 2.0f / width;

    for (i = 0; i < LENGTHOF(table->r); i++) {
        f31 = (i + 1) * 32;
        f31 *= f29;
        f31 *= f28;
        f27 = sqrtf(1.0f + (f31 * f31) / (f30 * f30));
        table->r[i] = (u32)(f27 * 256) & 0xFFF;
    }
}

void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable* table) {
    u32 fogRangeReg;
    u32 fogRangeRegK;
    int i;

    if (enable) {
        for (i = 0; i < LENGTHOF(table->r); i += 2) {
            fogRangeRegK = 0;
            GX_BP_SET_FOGRANGEK_HI(fogRangeRegK, table->r[i]);
            GX_BP_SET_FOGRANGEK_LO(fogRangeRegK, table->r[i + 1]);
            GX_BP_SET_OPCODE(fogRangeRegK, GX_BP_REG_FOGRANGEK0 + (i / 2));
            GX_BP_LOAD_REG(fogRangeRegK);
        }
    }

    fogRangeReg = 0;
    GX_BP_SET_FOGRANGE_CENTER(fogRangeReg, center + 342);
    GX_BP_SET_FOGRANGE_ENABLED(fogRangeReg, enable);
    GX_BP_SET_OPCODE(fogRangeReg, GX_BP_REG_FOGRANGE);
    GX_BP_LOAD_REG(fogRangeReg);

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetBlendMode(GXBlendMode mode, GXBlendFactor src, GXBlendFactor dst,
                    GXLogicOp op) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_SUBTRACT(blendModeReg, mode == GX_BM_SUBTRACT);
    GX_BP_SET_BLENDMODE_BLEND_ENABLE(blendModeReg, mode);
    GX_BP_SET_BLENDMODE_LOGIC_OP_ENABLE(blendModeReg, mode == GX_BM_LOGIC);
    GX_BP_SET_BLENDMODE_LOGIC_MODE(blendModeReg, op);
    GX_BP_SET_BLENDMODE_SRC_FACTOR(blendModeReg, src);
    GX_BP_SET_BLENDMODE_DST_FACTOR(blendModeReg, dst);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetColorUpdate(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_COLOR_UPDATE(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetAlphaUpdate(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_ALPHA_UPDATE(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetZMode(GXBool enableTest, GXCompare func, GXBool enableUpdate) {
    u32 zModeReg = gxdt->zMode;
    GX_BP_SET_ZMODE_TEST_ENABLE(zModeReg, enableTest);
    GX_BP_SET_ZMODE_COMPARE(zModeReg, func);
    GX_BP_SET_ZMODE_UPDATE_ENABLE(zModeReg, enableUpdate);

    GX_BP_LOAD_REG(zModeReg);
    gxdt->zMode = zModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetZCompLoc(GXBool beforeTex) {
    GX_BP_SET_ZCONTROL_BEFORE_TEX(gxdt->zControl, beforeTex);
    GX_BP_LOAD_REG(gxdt->zControl);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt16 zFmt) {
    static u32 p2f[GX_MAX_PIXELFMT] = {
        GX_PF_RGB8_Z24, GX_PF_RGBA6_Z24, GX_PF_RGBA565_Z16, GX_PF_Z24,
        GX_PF_Y8,       GX_PF_Y8,        GX_PF_Y8,          GX_PF_U8};

    u32 zControlRegOld = gxdt->zControl;

    GX_BP_SET_ZCONTROL_PIXEL_FMT(gxdt->zControl, p2f[pixelFmt]);
    GX_BP_SET_ZCONTROL_Z_FMT(gxdt->zControl, zFmt);

    if (zControlRegOld != gxdt->zControl) {
        GX_BP_LOAD_REG(gxdt->zControl);
        GX_BP_SET_GENMODE_MULTISAMPLE(gxdt->genMode,
                                      pixelFmt == GX_PF_RGBA565_Z16);
        gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
    }

    if (p2f[pixelFmt] == GX_PF_Y8) {
        GX_BP_SET_DSTALPHA_YUV_FMT(gxdt->dstAlpha, pixelFmt - GX_PF_Y8);
        GX_BP_SET_OPCODE(gxdt->dstAlpha, GX_BP_REG_DSTALPHA);
        GX_BP_LOAD_REG(gxdt->dstAlpha);
    }

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetDither(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_DITHER(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetDstAlpha(GXBool enable, u8 alpha) {
    u32 dstAlphaReg = gxdt->dstAlpha;
    GX_BP_SET_DSTALPHA_ALPHA(dstAlphaReg, alpha);
    GX_BP_SET_DSTALPHA_ENABLE(dstAlphaReg, enable);

    GX_BP_LOAD_REG(dstAlphaReg);
    gxdt->dstAlpha = dstAlphaReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetFieldMask(GXBool enableEven, GXBool enableOdd) {
    u32 fieldMaskReg = 0;
    GX_BP_SET_FIELDMASK_ODD(fieldMaskReg, enableOdd);
    GX_BP_SET_FIELDMASK_EVEN(fieldMaskReg, enableEven);
    GX_BP_SET_OPCODE(fieldMaskReg, GX_BP_REG_FIELDMASK);

    GX_BP_LOAD_REG(fieldMaskReg);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetFieldMode(GXBool texLOD, GXBool adjustAR) {
    GX_BP_SET_LINEPTWIDTH_ADJUST_AR(gxdt->linePtWidth, adjustAR);
    GX_BP_LOAD_REG(gxdt->linePtWidth);

    __GXFlushTextureState();
    GX_BP_LOAD_REG(GX_BP_REG_FIELDMODE << 24 | texLOD);
    __GXFlushTextureState();
}
