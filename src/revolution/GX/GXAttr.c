// Uses the hacky GXSetVtxAttrFmtv declaration
#define GXATTR_MATCH_HACK

#include <revolution/GX.h>

static void SETVCDATTR(GXAttr name, GXAttrType type);
static void SETVAT(u32* vatA, u32* vatB, u32* vatC, GXAttr attr,
                   GXCompCnt compCnt, GXCompType compType, u8 shift);
static u8 GetFracForNrm(GXCompType compType);

static void __GXXfVtxSpecs(void) {
    unsigned int cmd;
    u32 nrm;
    u32 clr;
    u32 txc;

    nrm = gxdt->binormal ? 2 : (gxdt->normal ? 1 : 0);

    // Both fields in one access
    clr = 32 -
          __cntlzw(GX_BITGET(gxdt->vcdLoReg, GX_CP_VCD_LO_COLORSPECULAR_ST,
                             GX_CP_VCD_LO_COLORSPECULAR_SZ +
                                 GX_CP_VCD_LO_COLORDIFFUSED_SZ)) +
          1;

    // All 16 bits in VCD_Hi
    txc = 32 -
          __cntlzw(GX_BITGET(gxdt->vcdHiReg, GX_CP_VCD_HI_TEX7COORD_ST,
                             sizeof(u16) * 8)) +
          1;

    // TODO: Fakematch? Bitset macros don't work here
    GX_XF_LOAD_REG_HDR(GX_XF_REG_INVERTEXSPEC);
    cmd = 0;
    cmd = cmd | clr >> 1;
    cmd = (txc << 3) & ~0xF | cmd;
    WGPIPE.i = cmd | nrm << 2;

    gxdt->lastWriteWasXF = TRUE;
}

void GXSetVtxDesc(GXAttr name, GXAttrType type) {
    SETVCDATTR(name, type);

    if (gxdt->normal || gxdt->binormal) {
        GX_CP_SET_VCD_LO_NORMAL(gxdt->vcdLoReg, gxdt->normalType);
    } else {
        GX_CP_SET_VCD_LO_NORMAL(gxdt->vcdLoReg, GX_NONE);
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_VCD;
}

static DECOMP_INLINE void SETVCDATTR(GXAttr name, GXAttrType type) {
    switch (name) {
    case GX_VA_PNMTXIDX:
        GX_CP_SET_VCD_LO_POSMATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX0MTXIDX:
        GX_CP_SET_VCD_LO_TEX0MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX1MTXIDX:
        GX_CP_SET_VCD_LO_TEX1MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX2MTXIDX:
        GX_CP_SET_VCD_LO_TEX2MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX3MTXIDX:
        GX_CP_SET_VCD_LO_TEX3MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX4MTXIDX:
        GX_CP_SET_VCD_LO_TEX4MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX5MTXIDX:
        GX_CP_SET_VCD_LO_TEX5MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX6MTXIDX:
        GX_CP_SET_VCD_LO_TEX6MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX7MTXIDX:
        GX_CP_SET_VCD_LO_TEX7MATIDX(gxdt->vcdLoReg, type);
        break;
    case GX_VA_POS:
        GX_CP_SET_VCD_LO_POSITION(gxdt->vcdLoReg, type);
        break;
    case GX_VA_NRM:
        if (type != GX_NONE) {
            gxdt->normal = TRUE;
            // GX_VA_NRM and GX_VA_NBT should not be enabled at the same time
            gxdt->binormal = FALSE;
            gxdt->normalType = type;
        } else {
            gxdt->normal = FALSE;
        }
        break;
    case GX_VA_NBT:
        if (type != GX_NONE) {
            gxdt->binormal = TRUE;
            // GX_VA_NRM and GX_VA_NBT should not be enabled at the same time
            gxdt->normal = FALSE;
            gxdt->normalType = type;
        } else {
            gxdt->binormal = FALSE;
        }
        break;
    case GX_VA_CLR0:
        GX_CP_SET_VCD_LO_COLORDIFFUSED(gxdt->vcdLoReg, type);
        break;
    case GX_VA_CLR1:
        GX_CP_SET_VCD_LO_COLORSPECULAR(gxdt->vcdLoReg, type);
        break;
    case GX_VA_TEX0:
        GX_CP_SET_VCD_HI_TEX0COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX1:
        GX_CP_SET_VCD_HI_TEX1COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX2:
        GX_CP_SET_VCD_HI_TEX2COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX3:
        GX_CP_SET_VCD_HI_TEX3COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX4:
        GX_CP_SET_VCD_HI_TEX4COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX5:
        GX_CP_SET_VCD_HI_TEX5COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX6:
        GX_CP_SET_VCD_HI_TEX6COORD(gxdt->vcdHiReg, type);
        break;
    case GX_VA_TEX7:
        GX_CP_SET_VCD_HI_TEX7COORD(gxdt->vcdHiReg, type);
        break;
    default:
        break;
    }
}

void GXSetVtxDescv(const GXVtxDescList* list) {
    for (; list->attr != GX_VA_NULL; list++) {
        SETVCDATTR(list->attr, list->type);
    }

    if (gxdt->normal || gxdt->binormal) {
        GX_CP_SET_VCD_LO_NORMAL(gxdt->vcdLoReg, gxdt->normalType);
    } else {
        GX_CP_SET_VCD_LO_NORMAL(gxdt->vcdLoReg, GX_NONE);
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_VCD;
}

void __GXSetVCD(void) {
    GX_CP_LOAD_REG(GX_CP_REG_VCD_LO, gxdt->vcdLoReg);
    GX_CP_LOAD_REG(GX_CP_REG_VCD_HI, gxdt->vcdHiReg);
    __GXXfVtxSpecs();
}

void __GXCalculateVLim(void) {
    static u8 tbl1[] = {0, 4, 1, 2};
    static u8 tbl2[] = {0, 8, 1, 2};
    static u8 tbl3[] = {0, 12, 1, 2};

    u32 vlim;
    u32 vcdLo;
    u32 vcdHi;
    s32 compCnt;

    if (gxdt->SHORT_0x4 == 0) {
        return;
    }

    vcdLo = gxdt->vcdLoReg;
    vcdHi = gxdt->vcdHiReg;

    // GXCompCnt bit of normal parameters
    compCnt = gxdt->vatA[GX_VTXFMT0];
    compCnt = (compCnt & 0x200) >> 9;

    vlim = GX_CP_GET_VCD_LO_POSMATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX0MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX1MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX2MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX3MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX4MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX5MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX6MATIDX(vcdLo);
    vlim += GX_CP_GET_VCD_LO_TEX7MATIDX(vcdLo);

    vlim += tbl3[GX_CP_GET_VCD_LO_POSITION(vcdLo)];
    vlim +=
        tbl3[GX_CP_GET_VCD_LO_NORMAL(vcdLo)] * (compCnt == GX_NRM_NBT ? 3 : 1);
    vlim += tbl1[GX_CP_GET_VCD_LO_COLORDIFFUSED(vcdLo)];
    vlim += tbl1[GX_CP_GET_VCD_LO_COLORSPECULAR(vcdLo)];

    vlim += tbl2[GX_CP_GET_VCD_HI_TEX0COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX1COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX2COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX3COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX4COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX5COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX6COORD(vcdHi)];
    vlim += tbl2[GX_CP_GET_VCD_HI_TEX7COORD(vcdHi)];

    gxdt->vlim = vlim;
}

void GXGetVtxDesc(GXAttr name, GXAttrType* type) {
    GXAttrType result;

    switch (name) {
    case GX_VA_PNMTXIDX:
        result = GX_CP_GET_VCD_LO_POSMATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX0MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX0MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX1MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX1MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX2MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX2MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX3MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX3MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX4MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX4MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX5MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX5MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX6MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX6MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX7MTXIDX:
        result = GX_CP_GET_VCD_LO_TEX7MATIDX(gxdt->vcdLoReg);
        break;
    case GX_VA_POS:
        result = GX_CP_GET_VCD_LO_POSITION(gxdt->vcdLoReg);
        break;
    case GX_VA_NRM:
        result =
            gxdt->normal ? GX_CP_GET_VCD_LO_NORMAL(gxdt->vcdLoReg) : GX_NONE;
        break;
    case GX_VA_NBT:
        result =
            gxdt->binormal ? GX_CP_GET_VCD_LO_NORMAL(gxdt->vcdLoReg) : GX_NONE;
        break;
    case GX_VA_CLR0:
        result = GX_CP_GET_VCD_LO_COLORDIFFUSED(gxdt->vcdLoReg);
        break;
    case GX_VA_CLR1:
        result = GX_CP_GET_VCD_LO_COLORSPECULAR(gxdt->vcdLoReg);
        break;
    case GX_VA_TEX0:
        result = GX_CP_GET_VCD_HI_TEX0COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX1:
        result = GX_CP_GET_VCD_HI_TEX1COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX2:
        result = GX_CP_GET_VCD_HI_TEX2COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX3:
        result = GX_CP_GET_VCD_HI_TEX3COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX4:
        result = GX_CP_GET_VCD_HI_TEX4COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX5:
        result = GX_CP_GET_VCD_HI_TEX5COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX6:
        result = GX_CP_GET_VCD_HI_TEX6COORD(gxdt->vcdHiReg);
        break;
    case GX_VA_TEX7:
        result = GX_CP_GET_VCD_HI_TEX7COORD(gxdt->vcdHiReg);
        break;
    default:
        result = GX_NONE;
    }

    *type = result;
}

void GXGetVtxDescv(GXVtxDescList* list) {
    int i;
    GXAttr attr;
    int* new_var2;

    for (i = 0; i <= GX_VA_TEX7; i++) {
        attr = (GXAttr)i;
        list[i].attr = attr;
        GXGetVtxDesc(attr, &list[i].type);
    }

    list[i].attr = GX_VA_NBT;
    GXGetVtxDesc(GX_VA_NBT, &list[i].type);

    // TODO: Fakematch
    attr = 1;
    i = (*(new_var2 = &i)) + attr;
    list[i].attr = GX_VA_NULL;
}

void GXClearVtxDesc(void) {
    gxdt->vcdLoReg = 0;
    // GX_VA_POS is required for every vertex descriptor
    GX_CP_SET_VCD_LO_POSITION(gxdt->vcdLoReg, GX_DIRECT);
    gxdt->vcdHiReg = 0;
    gxdt->normal = FALSE;
    gxdt->binormal = FALSE;
    gxdt->gxDirtyFlags |= GX_DIRTY_VCD;
}

void GXSetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt compCnt,
                     GXCompType compType, u8 shift) {
    u32* vatA;
    u32* vatB;
    u32* vatC;

    vatA = &gxdt->vatA[fmt];
    vatB = &gxdt->vatB[fmt];
    vatC = &gxdt->vatC[fmt];

    SETVAT(vatA, vatB, vatC, attr, compCnt, compType, shift);
    gxdt->gxDirtyFlags |= GX_DIRTY_VAT;
    gxdt->vatDirtyFlags |= (u8)(1 << (u8)fmt);
}

static DECOMP_INLINE void SETVAT(u32* vatA, u32* vatB, u32* vatC, GXAttr attr,
                                 GXCompCnt compCnt, GXCompType compType,
                                 u8 shift) {
    switch (attr) {
    case GX_VA_POS:
        GX_CP_SET_VAT_GROUP0_POS_CNT(*vatA, compCnt);
        GX_CP_SET_VAT_GROUP0_POS_TYPE(*vatA, compType);
        GX_CP_SET_VAT_GROUP0_POS_SHIFT(*vatA, shift);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        GX_CP_SET_VAT_GROUP0_NRM_TYPE(*vatA, compType);
        if (compCnt == GX_NRM_NBT3) {
            // Probably because the compCnt can only be one bit?
            GX_CP_SET_VAT_GROUP0_NRM_CNT(*vatA, GX_NRM_NBT);
            GX_CP_SET_VAT_GROUP0_NORMALINDEX3(*vatA, TRUE);
        } else {
            GX_CP_SET_VAT_GROUP0_NRM_CNT(*vatA, compCnt);
            GX_CP_SET_VAT_GROUP0_NORMALINDEX3(*vatA, FALSE);
        }
        break;
    case GX_VA_CLR0:
        GX_CP_SET_VAT_GROUP0_COLORDIFF_CNT(*vatA, compCnt);
        GX_CP_SET_VAT_GROUP0_COLORDIFF_TYPE(*vatA, compType);
        break;
    case GX_VA_CLR1:
        GX_CP_SET_VAT_GROUP0_COLORSPEC_CNT(*vatA, compCnt);
        GX_CP_SET_VAT_GROUP0_COLORSPEC_TYPE(*vatA, compType);
        break;
    case GX_VA_TEX0:
        GX_CP_SET_VAT_GROUP0_TXC0_CNT(*vatA, compCnt);
        GX_CP_SET_VAT_GROUP0_TXC0_TYPE(*vatA, compType);
        GX_CP_SET_VAT_GROUP0_TXC0_SHIFT(*vatA, shift);
        break;
    case GX_VA_TEX1:
        GX_CP_SET_VAT_GROUP1_TXC1_CNT(*vatB, compCnt);
        GX_CP_SET_VAT_GROUP1_TXC1_TYPE(*vatB, compType);
        GX_CP_SET_VAT_GROUP1_TXC1_SHIFT(*vatB, shift);
        break;
    case GX_VA_TEX2:
        GX_CP_SET_VAT_GROUP1_TXC2_CNT(*vatB, compCnt);
        GX_CP_SET_VAT_GROUP1_TXC2_TYPE(*vatB, compType);
        GX_CP_SET_VAT_GROUP1_TXC2_SHIFT(*vatB, shift);
        break;
    case GX_VA_TEX3:
        GX_CP_SET_VAT_GROUP1_TXC3_CNT(*vatB, compCnt);
        GX_CP_SET_VAT_GROUP1_TXC3_TYPE(*vatB, compType);
        GX_CP_SET_VAT_GROUP1_TXC3_SHIFT(*vatB, shift);
        break;
    case GX_VA_TEX4:
        GX_CP_SET_VAT_GROUP1_TXC4_CNT(*vatB, compCnt);
        GX_CP_SET_VAT_GROUP1_TXC4_TYPE(*vatB, compType);
        GX_CP_SET_VAT_GROUP2_TXC4_SHIFT(*vatC, shift);
        break;
    case GX_VA_TEX5:
        GX_CP_SET_VAT_GROUP2_TXC5_CNT(*vatC, compCnt);
        GX_CP_SET_VAT_GROUP2_TXC5_TYPE(*vatC, compType);
        GX_CP_SET_VAT_GROUP2_TXC5_SHIFT(*vatC, shift);
        break;
    case GX_VA_TEX6:
        GX_CP_SET_VAT_GROUP2_TXC6_CNT(*vatC, compCnt);
        GX_CP_SET_VAT_GROUP2_TXC6_TYPE(*vatC, compType);
        GX_CP_SET_VAT_GROUP2_TXC6_SHIFT(*vatC, shift);
        break;
    case GX_VA_TEX7:
        GX_CP_SET_VAT_GROUP2_TXC7_CNT(*vatC, compCnt);
        GX_CP_SET_VAT_GROUP2_TXC7_TYPE(*vatC, compType);
        GX_CP_SET_VAT_GROUP2_TXC7_SHIFT(*vatC, shift);
        break;
    }
}

void GXSetVtxAttrFmtv(s16 fmt, const GXVtxAttrFmtList* list) {
    u32* vatA;
    u32* vatB;
    u32* vatC;

    vatA = &gxdt->vatA[fmt];
    vatB = &gxdt->vatB[fmt];
    vatC = &gxdt->vatC[fmt];

    for (; list->attr != GX_VA_NULL; list++) {
        SETVAT(vatA, vatB, vatC, list->attr, list->compCnt, list->compType,
               list->shift);
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_VAT;
    gxdt->vatDirtyFlags |= (u8)(1 << (u8)fmt);
}

void __GXSetVAT(void) {
    int i = 0;
    u32 flags = gxdt->vatDirtyFlags;

    do {
        if (flags & 1) {
            GX_CP_LOAD_REG(GX_CP_REG_VAT_GROUP0 | i, gxdt->vatA[i]);
            GX_CP_LOAD_REG(GX_CP_REG_VAT_GROUP1 | i, gxdt->vatB[i]);
            GX_CP_LOAD_REG(GX_CP_REG_VAT_GROUP2 | i, gxdt->vatC[i]);
        }

        i++;
        flags >>= 1;
    } while (flags != 0);

    WGPIPE.c = GX_FIFO_CMD_NOOP;
    gxdt->vatDirtyFlags = 0;
}

void GXGetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt* compCnt,
                     GXCompType* compType, u8* shift) {
    u32* vatA;
    u32* vatB;
    u32* vatC;

    vatA = &gxdt->vatA[fmt];
    vatB = &gxdt->vatB[fmt];
    vatC = &gxdt->vatC[fmt];

    switch (attr) {
    case GX_VA_POS:
        *compCnt = GX_CP_GET_VAT_GROUP0_POS_CNT(*vatA);
        *compType = GX_CP_GET_VAT_GROUP0_POS_TYPE(*vatA);
        *shift = GX_CP_GET_VAT_GROUP0_POS_SHIFT(*vatA);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        *compCnt = GX_CP_GET_VAT_GROUP0_NRM_CNT(*vatA);

        // Undoing what SETVAT did
        if (*compCnt == GX_NRM_NBT &&
            GX_CP_GET_VAT_GROUP0_NORMALINDEX3(*vatA)) {
            *compCnt = GX_NRM_NBT3;
        }

        *compType = GX_CP_GET_VAT_GROUP0_NRM_TYPE(*vatA);
        *shift = GetFracForNrm(*compType);
        break;
    case GX_VA_CLR0:
        *compCnt = GX_CP_GET_VAT_GROUP0_COLORDIFF_CNT(*vatA);
        *compType = GX_CP_GET_VAT_GROUP0_COLORDIFF_TYPE(*vatA);
        *shift = 0;
        break;
    case GX_VA_CLR1:
        *compCnt = GX_CP_GET_VAT_GROUP0_COLORSPEC_CNT(*vatA);
        *compType = GX_CP_GET_VAT_GROUP0_COLORSPEC_TYPE(*vatA);
        *shift = 0;
        break;
    case GX_VA_TEX0:
        *compCnt = GX_CP_GET_VAT_GROUP0_TXC0_CNT(*vatA);
        *compType = GX_CP_GET_VAT_GROUP0_TXC0_TYPE(*vatA);
        *shift = GX_CP_GET_VAT_GROUP0_TXC0_SHIFT(*vatA);
        break;
    case GX_VA_TEX1:
        *compCnt = GX_CP_GET_VAT_GROUP1_TXC1_CNT(*vatB);
        *compType = GX_CP_GET_VAT_GROUP1_TXC1_TYPE(*vatB);
        *shift = GX_CP_GET_VAT_GROUP1_TXC1_SHIFT(*vatB);
        break;
    case GX_VA_TEX2:
        *compCnt = GX_CP_GET_VAT_GROUP1_TXC2_CNT(*vatB);
        *compType = GX_CP_GET_VAT_GROUP1_TXC2_TYPE(*vatB);
        *shift = GX_CP_GET_VAT_GROUP1_TXC2_SHIFT(*vatB);
        break;
    case GX_VA_TEX3:
        *compCnt = GX_CP_GET_VAT_GROUP1_TXC3_CNT(*vatB);
        *compType = GX_CP_GET_VAT_GROUP1_TXC3_TYPE(*vatB);
        *shift = GX_CP_GET_VAT_GROUP1_TXC3_SHIFT(*vatB);
        break;
    case GX_VA_TEX4:
        *compCnt = GX_CP_GET_VAT_GROUP1_TXC4_CNT(*vatB);
        *compType = GX_CP_GET_VAT_GROUP1_TXC4_TYPE(*vatB);
        *shift = GX_CP_GET_VAT_GROUP2_TXC4_SHIFT(*vatC);
        break;
    case GX_VA_TEX5:
        *compCnt = GX_CP_GET_VAT_GROUP2_TXC5_CNT(*vatC);
        *compType = GX_CP_GET_VAT_GROUP2_TXC5_TYPE(*vatC);
        *shift = GX_CP_GET_VAT_GROUP2_TXC5_SHIFT(*vatC);
        break;
    case GX_VA_TEX6:
        *compCnt = GX_CP_GET_VAT_GROUP2_TXC6_CNT(*vatC);
        *compType = GX_CP_GET_VAT_GROUP2_TXC6_TYPE(*vatC);
        *shift = GX_CP_GET_VAT_GROUP2_TXC6_SHIFT(*vatC);
        break;
    case GX_VA_TEX7:
        *compCnt = GX_CP_GET_VAT_GROUP2_TXC7_CNT(*vatC);
        *compType = GX_CP_GET_VAT_GROUP2_TXC7_TYPE(*vatC);
        *shift = GX_CP_GET_VAT_GROUP2_TXC7_SHIFT(*vatC);
        break;
    default:
        *compCnt = GX_POS_XYZ;
        *compType = GX_U8;
        *shift = 0;
    }
}

static u8 GetFracForNrm(GXCompType compType) {
    switch (compType) {
    case GX_S8:
        return 6;
    case GX_S16:
        return 14;
    case GX_U16:
    default:
        return 0;
    }
}

void GXGetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList* list) {
    int i;
    GXAttr attr;

    for (i = GX_VA_POS; i <= GX_VA_TEX7; i++, list++) {
        attr = (GXAttr)i;
        list->attr = attr;
        GXGetVtxAttrFmt(fmt, attr, &list->compCnt, &list->compType,
                        &list->shift);
    }

    list->attr = GX_VA_NULL;
}

void GXSetArray(GXAttr attr, const void* base, u8 stride) {
    u32 idx;

    if (attr == GX_VA_NBT) {
        attr = GX_VA_NRM;
    }

    idx = attr - GX_VA_POS;

    GX_CP_LOAD_REG(GX_BP_REG_SETMODE0_TEX4 | idx,
                   // Address -> offset?
                   (u32)base & ~0xC0000000);

    GX_CP_LOAD_REG(GX_BP_REG_SETIMAGE2_TEX4 | idx, stride);
}

void GXInvalidateVtxCache(void) {
    WGPIPE.c = GX_FIFO_CMD_INVAL_VTX;
}

void GXSetTexCoordGen2(GXTexCoordID id, GXTexGenType type, GXTexGenSrc src,
                       u32 texMtxIdx, GXBool normalize, u32 dualTexMtxIdx) {
    u32 reg;
    u32 inputRow;
    GXXfTexForm inputForm;

    reg = 0;
    inputForm = GX_XF_TEX_FORM_AB11;
    inputRow = 5;

    switch (src) {
    case GX_TG_POS:
        inputRow = 0;
        inputForm = GX_XF_TEX_FORM_ABC1;
        break;
    case GX_TG_NRM:
        inputRow = 1;
        inputForm = GX_XF_TEX_FORM_ABC1;
        break;
    case GX_TG_BINRM:
        inputRow = 3;
        inputForm = GX_XF_TEX_FORM_ABC1;
        break;
    case GX_TG_TANGENT:
        inputRow = 4;
        inputForm = GX_XF_TEX_FORM_ABC1;
        break;
    case GX_TG_COLOR0:
        inputRow = 2;
        break;
    case GX_TG_COLOR1:
        inputRow = 2;
        break;
    case GX_TG_TEX0:
        inputRow = 5;
        break;
    case GX_TG_TEX1:
        inputRow = 6;
        break;
    case GX_TG_TEX2:
        inputRow = 7;
        break;
    case GX_TG_TEX3:
        inputRow = 8;
        break;
    case GX_TG_TEX4:
        inputRow = 9;
        break;
    case GX_TG_TEX5:
        inputRow = 10;
        break;
    case GX_TG_TEX6:
        inputRow = 11;
        break;
    case GX_TG_TEX7:
        inputRow = 12;
        break;
    default:
        break;
    }

    switch (type) {
    case GX_TG_MTX2x4:
        reg = 0;
        GX_XF_SET_TEX_PROJTYPE(reg, GX_XF_TEX_PROJ_ST); // 2x4 projection
        GX_XF_SET_TEX_INPUTFORM(reg, inputForm);
        GX_XF_SET_TEX_SRCROW(reg, inputRow);
        break;
    case GX_TG_MTX3x4:
        reg = 0;
        GX_XF_SET_TEX_PROJTYPE(reg, GX_XF_TEX_PROJ_STQ); // 3x4 projection
        GX_XF_SET_TEX_INPUTFORM(reg, inputForm);
        GX_XF_SET_TEX_SRCROW(reg, inputRow);
        break;
    case GX_TG_BUMP0:
    case GX_TG_BUMP1:
    case GX_TG_BUMP2:
    case GX_TG_BUMP3:
    case GX_TG_BUMP4:
    case GX_TG_BUMP5:
    case GX_TG_BUMP6:
    case GX_TG_BUMP7:
        reg = 0;
        GX_XF_SET_TEX_INPUTFORM(reg, inputForm);
        GX_XF_SET_TEX_TEXGENTYPE(reg, GX_XF_TG_BUMP);
        GX_XF_SET_TEX_SRCROW(reg, inputRow);
        GX_XF_SET_TEX_BUMPSRCTEX(reg, src - GX_TG_TEXCOORD0);
        GX_XF_SET_TEX_BUMPSRCLIGHT(reg, type - GX_TG_BUMP0);
        break;
    case GX_TG_SRTG:
        reg = 0;
        GX_XF_SET_TEX_INPUTFORM(reg, inputForm);

        if (src == GX_TG_COLOR0) {
            GX_XF_SET_TEX_TEXGENTYPE(reg, GX_XF_TG_CLR0);
        } else {
            GX_XF_SET_TEX_TEXGENTYPE(reg, GX_XF_TG_CLR1);
        }

        GX_XF_SET_TEX_SRCROW(reg, 2);
        break;
    default:
        break;
    }

    gxdt->texRegs[id] = reg;
    gxdt->gxDirtyFlags |= GX_DIRTY_TEX0 << id;

    reg = 0;
    GX_XF_SET_DUALTEX_BASEROW(reg, dualTexMtxIdx - GX_DUALMTX0);
    GX_XF_SET_DUALTEX_NORMALIZE(reg, normalize);
    gxdt->dualTexRegs[id] = reg;

    switch (id) {
    case GX_TEXCOORD0:
        GX_XF_SET_MATRIXINDEX0_TEX0(gxdt->matrixIndex0, texMtxIdx);
        break;
    case GX_TEXCOORD1:
        GX_XF_SET_MATRIXINDEX0_TEX1(gxdt->matrixIndex0, texMtxIdx);
        break;
    case GX_TEXCOORD2:
        GX_XF_SET_MATRIXINDEX0_TEX2(gxdt->matrixIndex0, texMtxIdx);
        break;
    case GX_TEXCOORD3:
        GX_XF_SET_MATRIXINDEX0_TEX3(gxdt->matrixIndex0, texMtxIdx);
        break;
    case GX_TEXCOORD4:
        GX_XF_SET_MATRIXINDEX1_TEX4(gxdt->matrixIndex1, texMtxIdx);
        break;
    case GX_TEXCOORD5:
        GX_XF_SET_MATRIXINDEX1_TEX5(gxdt->matrixIndex1, texMtxIdx);
        break;
    case GX_TEXCOORD6:
        GX_XF_SET_MATRIXINDEX1_TEX6(gxdt->matrixIndex1, texMtxIdx);
        break;
    default:
        GX_XF_SET_MATRIXINDEX1_TEX7(gxdt->matrixIndex1, texMtxIdx);
        break;
    }

    gxdt->gxDirtyFlags |= GX_DIRTY_MTX_IDX;
}

void GXSetNumTexGens(u8 num) {
    GX_BP_SET_GENMODE_NUMTEX(gxdt->genMode, num);
    gxdt->gxDirtyFlags |= GX_DIRTY_NUM_TEX;
    gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
}
