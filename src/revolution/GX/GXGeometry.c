#include <revolution/GX.h>

inline void __GXSetAmbMat(u32 dirtyFlags) {
    if (dirtyFlags & GX_DIRTY_AMB_COLOR0) {
        GX_XF_LOAD_REG(GX_XF_REG_AMBIENT0, *(u32*)&gxdt->ambColors[0]);
    }

    if (dirtyFlags & GX_DIRTY_AMB_COLOR1) {
        GX_XF_LOAD_REG(GX_XF_REG_AMBIENT1, *(u32*)&gxdt->ambColors[1]);
    }

    if (dirtyFlags & GX_DIRTY_MAT_COLOR0) {
        GX_XF_LOAD_REG(GX_XF_REG_MATERIAL0, *(u32*)&gxdt->matColors[0]);
    }

    if (dirtyFlags & GX_DIRTY_MAT_COLOR1) {
        GX_XF_LOAD_REG(GX_XF_REG_MATERIAL1, *(u32*)&gxdt->matColors[1]);
    }
}

inline void __GXSetLightChan(volatile s32 dirtyFlags) {
    int i;
    u32 bits;
    u32 addr = GX_XF_REG_COLOR0CNTRL;

    if (dirtyFlags & GX_DIRTY_NUM_COLORS) {
        u32 colors = GX_BP_GET_GENMODE_NUMCOLORS(gxdt->genMode);
        GX_XF_LOAD_REG(GX_XF_REG_NUMCOLORS, colors);
    }

    bits = dirtyFlags;
    bits = (bits >> 12) & 0xF;
    i = 0;
    for (; bits != 0; i++, addr++, bits >>= 1) {
        if (bits & 1) {
            GX_XF_LOAD_REG(addr, gxdt->colorControl[i]);
        }
    }
}

inline void __GXSetTexGen(volatile s32 dirtyFlags) {
    int i;
    u32 bits;
    u32 taddr = GX_XF_REG_TEX0;
    u32 dtaddr;

    if (dirtyFlags & GX_DIRTY_NUM_TEX) {
        u32 gens = GX_BP_GET_GENMODE_NUMTEX(gxdt->genMode);
        GX_XF_LOAD_REG(GX_XF_REG_NUMTEX, gens);
    }

    bits = dirtyFlags;
    bits = (bits >> 16) & 0xFF;
    i = 0;
    for (; bits != 0; taddr++, i++, bits >>= 1) {
        dtaddr = taddr + GX_XF_REG_DUALTEX0 - GX_XF_REG_TEX0;
        if (bits & 1) {
            GX_XF_LOAD_REG(taddr, gxdt->texRegs[i]);
            GX_XF_LOAD_REG(dtaddr, gxdt->dualTexRegs[i]);
        }
    }
}

void __GXSetDirtyState(void) {
    u32 tempFlags;
    u32 dirtyFlags = gxdt->gxDirtyFlags;

    if (dirtyFlags & GX_DIRTY_SU_TEX) {
        __GXSetSUTexRegs();
    }

    if (dirtyFlags & GX_DIRTY_BP_MASK) {
        __GXUpdateBPMask();
    }

    if (dirtyFlags & GX_DIRTY_GEN_MODE) {
        __GXSetGenMode();
    }

    if (dirtyFlags & GX_DIRTY_VCD) {
        __GXSetVCD();
    }

    if (dirtyFlags & GX_DIRTY_VAT) {
        __GXSetVAT();
    }

    if (dirtyFlags & (GX_DIRTY_VCD | GX_DIRTY_VAT)) {
        __GXCalculateVLim();
    }

    dirtyFlags &= ~0xFF;
    if (dirtyFlags) {
        tempFlags = dirtyFlags & GX_AMB_MAT_MASK;
        if (tempFlags != 0) {
            __GXSetAmbMat(tempFlags);
        }

        tempFlags = dirtyFlags & GX_LIGHT_CHAN_MASK;
        if (tempFlags != 0) {
            __GXSetLightChan(tempFlags);
        }

        tempFlags = dirtyFlags & GX_TEX_GEN_MASK;
        if (tempFlags != 0) {
            __GXSetTexGen(tempFlags);
        }

        tempFlags = dirtyFlags & GX_DIRTY_MTX_IDX;
        if (tempFlags != 0) {
            __GXSetMatrixIndex(0);
            __GXSetMatrixIndex(5);
        }

        tempFlags = dirtyFlags & GX_DIRTY_VIEWPORT;
        if (tempFlags != 0) {
            __GXSetViewport();
        }

        tempFlags = dirtyFlags & GX_DIRTY_PROJECTION;
        if (tempFlags != 0) {
            __GXSetProjection();
        }

        gxdt->lastWriteWasXF = TRUE;
    }

    gxdt->gxDirtyFlags = 0;
}

void GXBegin(GXPrimitive prim, GXVtxFmt fmt, u16 verts) {
    if (gxdt->gxDirtyFlags != 0) {
        __GXSetDirtyState();
    }

    if (gxdt->WORD_0x0 == 0) {
        __GXSendFlushPrim();
    }

    WGPIPE.c = fmt | prim;
    WGPIPE.s = verts;
}

void __GXSendFlushPrim(void) {
    u32 i;
    u32 sz = gxdt->SHORT_0x4 * gxdt->vlim;

    WGPIPE.uc = GX_TRIANGLESTRIP;
    WGPIPE.us = gxdt->SHORT_0x4;

    for (i = 0; i < sz; i += 4) {
        WGPIPE.i = 0;
    }

    gxdt->lastWriteWasXF = TRUE;
}

void GXSetLineWidth(u8 width, u32 offset) {
    GX_BP_SET_LINEPTWIDTH_LINESZ(gxdt->linePtWidth, width);
    GX_BP_SET_LINEPTWIDTH_LINEOFS(gxdt->linePtWidth, offset);
    GX_BP_LOAD_REG(gxdt->linePtWidth);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetPointSize(u8 size, u32 offset) {
    GX_BP_SET_LINEPTWIDTH_POINTSZ(gxdt->linePtWidth, size);
    GX_BP_SET_LINEPTWIDTH_POINTOFS(gxdt->linePtWidth, offset);
    GX_BP_LOAD_REG(gxdt->linePtWidth);
    gxdt->lastWriteWasXF = FALSE;
}

void GXEnableTexOffsets(GXTexCoordID id, GXBool lineOfs, GXBool pointOfs) {
    GX_BP_SET_SU_SSIZE_USELINEOFS(gxdt->txcRegs[id], lineOfs);
    GX_BP_SET_SU_SSIZE_USEPOINTOFS(gxdt->txcRegs[id], pointOfs);
    GX_BP_LOAD_REG(gxdt->txcRegs[id]);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetCullMode(GXCullMode mode) {
    // Swap bits to get hardware representation (see nw4r::g3d::fifo::cm2hw)
    GXCullMode bits = (GXCullMode)(mode << 1 & 2 | mode >> 1 & 1);
    GX_BP_SET_GENMODE_CULLMODE(gxdt->genMode, bits);
    gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
}

void GXGetCullMode(GXCullMode* out) {
    // TODO: Fakematch? Should use GX_BP_GET_GENMODE_CULLMODE if possible
    s32 bits = 0;
    bits |= (s32)(gxdt->genMode >> (13 + 1) & 2) >> 1;
    bits |= (s32)(gxdt->genMode >> 13 & 2);
    *out = (GXCullMode)bits;
}

void GXSetCoPlanar(GXBool coplanar) {
    u32 reg;

    GX_BP_SET_GENMODE_COPLANAR(gxdt->genMode, coplanar);

    // TODO: GX_BP_SET_OPCODE doesn't work.
    // Did they really write this out?
    reg = 0;
    reg |= GX_BP_REG_SSMASK << 24;
    reg |= 0x80000;

    GX_BP_LOAD_REG(reg);
    GX_BP_LOAD_REG(gxdt->genMode);
}

void __GXSetGenMode(void) {
    GX_BP_LOAD_REG(gxdt->genMode);
    gxdt->lastWriteWasXF = FALSE;
}
