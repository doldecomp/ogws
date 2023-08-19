#include <revolution/GX.h>

void GXSetTevIndirect(GXTevStageID tevStage, GXIndTexStageID texStage,
                      GXIndTexFormat texFmt, GXIndTexBiasSel biasSel,
                      GXIndTexMtxID mtxId, GXIndTexWrap wrapS,
                      GXIndTexWrap wrapT, GXBool addPrev, GXBool utcLod,
                      GXIndTexAlphaSel alphaSel) {
    u32 opcode = tevStage + GX_BP_REG_INDTEVSTAGE0;

    u32 cmd = 0;
    GX_BP_SET_INDTEVSTAGE_STAGE(cmd, texStage);
    GX_BP_SET_INDTEVSTAGE_FORMAT(cmd, texFmt);
    GX_BP_SET_INDTEVSTAGE_BIAS(cmd, biasSel);
    GX_BP_SET_INDTEVSTAGE_ALPHA(cmd, alphaSel);
    GX_BP_SET_INDTEVSTAGE_MTX(cmd, mtxId);
    GX_BP_SET_INDTEVSTAGE_WRAPS(cmd, wrapS);
    GX_BP_SET_INDTEVSTAGE_WRAPT(cmd, wrapT);
    GX_BP_SET_INDTEVSTAGE_UTCLOD(cmd, utcLod);
    GX_BP_SET_INDTEVSTAGE_ADDPREV(cmd, addPrev);
    GX_BP_SET_OPCODE(cmd, opcode);

    GX_BP_LOAD_REG(cmd);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetIndTexMtx(GXIndTexMtxID id, const f32 offset[2][3], s8 scaleExp) {
    u32 index;
    u32 cmd;

    switch (id) {
    case GX_ITM_0:
    case GX_ITM_1:
    case GX_ITM_2:
        index = id - GX_ITM_0;
        break;
    case GX_ITM_S0:
    case GX_ITM_S1:
    case GX_ITM_S2:
        index = id - GX_ITM_S0;
        break;
    case GX_ITM_T0:
    case GX_ITM_T1:
    case GX_ITM_T2:
        index = id - GX_ITM_T0;
        break;
    case 4:
    case 8:
    default:
        index = 0;
    }

    scaleExp += 17;

    cmd = 0;
    GX_BP_SET_INDMTXA_M00(cmd, 1024.0f * offset[0][0]);
    GX_BP_SET_INDMTXA_M10(cmd, 1024.0f * offset[1][0]);
    GX_BP_SET_INDMTXA_EXP(cmd, scaleExp);
    GX_BP_SET_OPCODE(cmd, index * 3 + GX_BP_REG_INDMTX0A);
    GX_BP_LOAD_REG(cmd);

    // TODO: Match using GX_BP_SET_INDMTXB_EXP
    cmd = 0;
    GX_BP_SET_INDMTXB_M01(cmd, 1024.0f * offset[0][1]);
    GX_BP_SET_INDMTXB_M11(cmd, 1024.0f * offset[1][1]);
    cmd = __rlwimi(cmd, scaleExp, 20, 8, 9);
    GX_BP_SET_OPCODE(cmd, index * 3 + GX_BP_REG_INDMTX0B);
    GX_BP_LOAD_REG(cmd);

    // TODO: Match using GX_BP_SET_INDMTXC_EXP
    cmd = 0;
    GX_BP_SET_INDMTXC_M02(cmd, 1024.0f * offset[0][2]);
    GX_BP_SET_INDMTXC_M12(cmd, 1024.0f * offset[1][2]);
    cmd = __rlwimi(cmd, scaleExp, 18, 8, 9);
    GX_BP_SET_OPCODE(cmd, index * 3 + GX_BP_REG_INDMTX0C);
    GX_BP_LOAD_REG(cmd);

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetIndTexCoordScale(GXIndTexStageID stage, GXIndTexScale scaleS,
                           GXIndTexScale scaleT) {
    switch (stage) {
    case GX_INDTEXSTAGE0:
        GX_BP_SET_RAS1_SS0_S0(gxdt->ras1_ss0, scaleS);
        GX_BP_SET_RAS1_SS0_T0(gxdt->ras1_ss0, scaleT);
        GX_BP_SET_OPCODE(gxdt->ras1_ss0, GX_BP_REG_RAS1_SS0);
        GX_BP_LOAD_REG(gxdt->ras1_ss0);
        break;
    case GX_INDTEXSTAGE1:
        GX_BP_SET_RAS1_SS0_S1(gxdt->ras1_ss0, scaleS);
        GX_BP_SET_RAS1_SS0_T1(gxdt->ras1_ss0, scaleT);
        GX_BP_SET_OPCODE(gxdt->ras1_ss0, GX_BP_REG_RAS1_SS0);
        GX_BP_LOAD_REG(gxdt->ras1_ss0);
        break;
    case GX_INDTEXSTAGE2:
        GX_BP_SET_RAS1_SS1_S2(gxdt->ras1_ss1, scaleS);
        GX_BP_SET_RAS1_SS1_T2(gxdt->ras1_ss1, scaleT);
        GX_BP_SET_OPCODE(gxdt->ras1_ss1, GX_BP_REG_RAS1_SS1);
        GX_BP_LOAD_REG(gxdt->ras1_ss1);
        break;
    case GX_INDTEXSTAGE3:
        GX_BP_SET_RAS1_SS1_S3(gxdt->ras1_ss1, scaleS);
        GX_BP_SET_RAS1_SS1_T3(gxdt->ras1_ss1, scaleT);
        GX_BP_SET_OPCODE(gxdt->ras1_ss1, GX_BP_REG_RAS1_SS1);
        GX_BP_LOAD_REG(gxdt->ras1_ss1);
        break;
    }

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetIndTexOrder(GXIndTexStageID stage, GXTexCoordID coord,
                      GXTexMapID map) {
    if (map == GX_TEXMAP_NULL) {
        map = GX_TEXMAP0;
    }

    if (coord == GX_TEXCOORD_NULL) {
        coord = GX_TEXCOORD0;
    }

    switch (stage) {
    case GX_INDTEXSTAGE0:
        GX_BP_SET_RAS1_IREF_MAP0(gxdt->ras1_iref, map);
        GX_BP_SET_RAS1_IREF_TXC0(gxdt->ras1_iref, coord);
        break;
    case GX_INDTEXSTAGE1:
        GX_BP_SET_RAS1_IREF_MAP1(gxdt->ras1_iref, map);
        GX_BP_SET_RAS1_IREF_TXC1(gxdt->ras1_iref, coord);
        break;
    case GX_INDTEXSTAGE2:
        GX_BP_SET_RAS1_IREF_MAP2(gxdt->ras1_iref, map);
        GX_BP_SET_RAS1_IREF_TXC2(gxdt->ras1_iref, coord);
        break;
    case GX_INDTEXSTAGE3:
        GX_BP_SET_RAS1_IREF_MAP3(gxdt->ras1_iref, map);
        GX_BP_SET_RAS1_IREF_TXC3(gxdt->ras1_iref, coord);
        break;
    }

    GX_BP_LOAD_REG(gxdt->ras1_iref);
    gxdt->gxDirtyFlags |= GX_DIRTY_SU_TEX;
    gxdt->gxDirtyFlags |= GX_DIRTY_BP_MASK;
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetNumIndStages(u8 num) {
    GX_BP_SET_GENMODE_NUMINDSTAGES(gxdt->genMode, num);
    gxdt->gxDirtyFlags |= GX_DIRTY_BP_MASK;
    gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
}

void GXSetTevDirect(GXTevStageID stage) {
    GXSetTevIndirect(stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF,
                     GX_ITW_OFF, GX_ITW_OFF, FALSE, FALSE, GX_ITBA_OFF);
}

void __GXUpdateBPMask(void) {}

void __GXSetIndirectMask(u32 mask) {
    GX_BP_SET_INDIMASK_IMASK(gxdt->ind_imask, mask);
    GX_BP_LOAD_REG(gxdt->ind_imask);
    gxdt->lastWriteWasXF = FALSE;
}

void __GXFlushTextureState(void) {
    GX_BP_LOAD_REG(gxdt->ind_imask);
    gxdt->lastWriteWasXF = FALSE;
}
