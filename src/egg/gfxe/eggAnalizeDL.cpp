#include <egg/gfxe.h>

#include <nw4r/g3d.h>

namespace EGG {

DECOMP_FORCELITERAL(eggAnalizeDL_cpp,
                    0.0f,
                    4503599627370496.0,
                    4503601774854144.0);

const s8 AnalizeDL::s_attrTypeSize[] = {
    0,           // GX_NONE
    -1,          // GX_DIRECT
    sizeof(u8),  // GX_INDEX8
    sizeof(u16), // GX_INDEX16
};

const u8 AnalizeDL::s_compTypeSize[] = {
    sizeof(u8),  // GX_U8
    sizeof(s8),  // GX_S8
    sizeof(u16), // GX_U16
    sizeof(s16), // GX_S16
    sizeof(f32), // GX_F32
};

GXVtxDescList AnalizeDL::s_vtxDesc[nw4r::g3d::ResPrePrimDL::SIZE_GXVTXDESCLIST];

GXVtxAttrFmtList
    AnalizeDL::s_vtxAttr[nw4r::g3d::ResPrePrimDL::SIZE_GXVTXATTRFMTLIST];

AnalizeDL::VtxPosArray AnalizeDL::s_vtxPos;
AnalizeDL::VtxResult AnalizeDL::s_result;

AnalizeDL::AnalizeDL(const nw4r::g3d::ResShp shp) {
    const u8* p_DL = shp.GetPrimDLTag().GetDL();

    m_DL = p_DL;
    m_DLPtr = p_DL;

    BYTE_0x8 = 0;

    bool vtxDesc = shp.GXGetVtxDescv(s_vtxDesc);
    bool vtxAttr = shp.GXGetVtxAttrFmtv(s_vtxAttr);

#line 45
    EGG_ASSERT(vtxDesc);
    EGG_ASSERT(vtxAttr);

    m_vtxDescSize = 0;
    m_vtxAttrSize = 0;
    m_vtxAttrSend = 0;

    configure();

    nw4r::g3d::ResVtxPos vtxPos = shp.GetResVtxPos();
    vtxPos.GetArray(&s_vtxPos.m_base, &s_vtxPos.m_stride);

    s_result.m_type = TYPE_NONE;
    s_result.m_vtxRemain = 0;

    for (int i = 0; i < VtxResult::PNMTX_NUM; i++) {
        s_result.m_posMtxIdx[i] = -1;
        s_result.m_nrmMtxIdx[i] = -1;
    }
}

AnalizeDL::CmdType AnalizeDL::advance() {
    VtxResult* p_result = &s_result;

    if (s_result.m_vtxRemain > 0) {
        s_result.m_type = TYPE_VERTEX;
        const u8* p_DL = m_DLPtr;

        if (m_vtxAttrSend & (1 << GX_VA_PNMTXIDX)) {
            p_result->m_mtxIdx = p_result->m_posMtxIdx[*p_DL++ / 3];
        } else {
            p_result->m_mtxIdx = -1;
        }

        if (m_vtxAttrSend & (1 << GX_VA_POS)) {
            if (m_vtxAttrSize == sizeof(u8)) {
                p_result->m_vtxIdx = *p_DL;
            } else {
                p_result->m_vtxIdx = *reinterpret_cast<const u16*>(p_DL);
            }

            u8 posShift = s_vtxAttr[GX_VA_POS - GX_VA_POS].shift;
            GXCompType posType = s_vtxAttr[GX_VA_POS - GX_VA_POS].compType;

            const u8* p_vtxCmd = static_cast<const u8*>(s_vtxPos.m_base) +
                                 s_vtxPos.m_stride * p_result->m_vtxIdx;

            switch (posType) {
            case GX_U8: {
                p_result->m_vtxPos.x =
                    *reinterpret_cast<const u8*>(p_vtxCmd + 0) /
                    static_cast<f32>(1 << posShift);

                p_result->m_vtxPos.y =
                    *reinterpret_cast<const u8*>(p_vtxCmd + 1) /
                    static_cast<f32>(1 << posShift);

                p_result->m_vtxPos.z =
                    *reinterpret_cast<const u8*>(p_vtxCmd + 2) /
                    static_cast<f32>(1 << posShift);

                break;
            }

            case GX_S8: {
                p_result->m_vtxPos.x =
                    *reinterpret_cast<const s8*>(p_vtxCmd + 0) /
                    static_cast<f32>(1 << posShift);

                p_result->m_vtxPos.y =
                    *reinterpret_cast<const s8*>(p_vtxCmd + 1) /
                    static_cast<f32>(1 << posShift);

                p_result->m_vtxPos.z =
                    *reinterpret_cast<const s8*>(p_vtxCmd + 2) /
                    static_cast<f32>(1 << posShift);

                break;
            }

            case GX_U16: {
                p_result->m_vtxPos.x =
                    *reinterpret_cast<const u16*>(p_vtxCmd + 0) /
                    static_cast<f32>(1 << posShift);

                // @bug Load from wrong offset
                p_result->m_vtxPos.y =
                    *reinterpret_cast<const u16*>(p_vtxCmd + 1) /
                    static_cast<f32>(1 << posShift);

                // @bug Load from wrong offset
                p_result->m_vtxPos.z =
                    *reinterpret_cast<const u16*>(p_vtxCmd + 2) /
                    static_cast<f32>(1 << posShift);
                break;
            }

            case GX_S16: {
                p_result->m_vtxPos.x =
                    *reinterpret_cast<const s16*>(p_vtxCmd + 0) /
                    static_cast<f32>(1 << posShift);

                // @bug Load from wrong offset
                p_result->m_vtxPos.y =
                    *reinterpret_cast<const s16*>(p_vtxCmd + 1) /
                    static_cast<f32>(1 << posShift);

                // @bug Load from wrong offset
                p_result->m_vtxPos.z =
                    *reinterpret_cast<const s16*>(p_vtxCmd + 2) /
                    static_cast<f32>(1 << posShift);

                break;
            }

            case GX_F32: {
                p_result->m_vtxPos.x =
                    *reinterpret_cast<const f32*>(p_vtxCmd + 0);

                p_result->m_vtxPos.y =
                    *reinterpret_cast<const f32*>(p_vtxCmd + 4);

                p_result->m_vtxPos.z =
                    *reinterpret_cast<const f32*>(p_vtxCmd + 8);

                break;
            }

            default: {
                break;
            }
            }
        } else {
            p_result->m_vtxIdx = -1;

            p_result->m_vtxPos.x = p_result->m_vtxPos.y = p_result->m_vtxPos.z =
                0.0f;
        }

        s_result.m_vtxRemain--;
        m_DLPtr += m_vtxDescSize;
    } else {
        switch (*m_DLPtr) {
        case GX_FIFO_CMD_LOAD_INDX_A: {
            s_result.m_type = TYPE_POSMTXINDX;
            s_result.m_posMtxIdx[m_DLPtr[4] / (4 * 3)] = m_DLPtr[2];
            m_DLPtr += GX_FIFO_CMD_LOAD_INDX_SIZE;
            break;
        }

        case GX_FIFO_CMD_LOAD_INDX_B: {
            s_result.m_type = TYPE_NRMMTXINDX;
            s_result.m_nrmMtxIdx[m_DLPtr[4] / (3 * 3)] = m_DLPtr[2];
            m_DLPtr += GX_FIFO_CMD_LOAD_INDX_SIZE;
            break;
        }

        case GX_FIFO_CMD_LOAD_INDX_C: {
            m_DLPtr += GX_FIFO_CMD_LOAD_INDX_SIZE;
            break;
        }

        case GX_FIFO_CMD_DRAW_POINTS:
        case GX_FIFO_CMD_DRAW_LINES:
        case GX_FIFO_CMD_DRAW_LINESTRIP:
        case GX_FIFO_CMD_DRAW_TRIANGLES:
        case GX_FIFO_CMD_DRAW_TRIANGLESTRIP:
        case GX_FIFO_CMD_DRAW_TRIANGLEFAN:
        case GX_FIFO_CMD_DRAW_QUADS: {
            s_result.m_type = TYPE_PRIMITIVE;
            s_result.m_primitive = m_DLPtr[0];
            s_result.m_vtxNum = *reinterpret_cast<const u16*>(m_DLPtr + 1);
            s_result.m_vtxRemain = s_result.m_vtxNum;
            m_DLPtr += GX_FIFO_CMD_DRAW_SIZE;
            break;
        }

        case GX_FIFO_CMD_NOOP: {
            s_result.m_type = TYPE_NOOP;
            break;
        }
        }
    }

    return s_result.m_type;
}

void AnalizeDL::configure() {
    for (int i = 0; s_vtxDesc[i].attr != GX_VA_NULL; i++) {
        s32 size = s_attrTypeSize[s_vtxDesc[i].type];

        if (size == -1) {
            if (i == GX_VA_PNMTXIDX ||
                i >= GX_VA_TEX0MTXIDX && i <= GX_VA_TEX7MTXIDX) {

                size = sizeof(u8);
            } else {
                int i_idx = -1;

                while (s_vtxAttr[++i_idx].attr != i) {
#line 235
                    // @bug Wrong assert condition??
                    EGG_ASSERT(i_idx >= nw4r::g3d::ResPrePrimDL::SIZE_GXVTXATTRFMTLIST);
                }

                size = s_compTypeSize[s_vtxAttr[i_idx].compType];
            }
        }

        switch (i) {
        case GX_VA_POS: {
            m_vtxAttrSize = size;
            break;
        }
        }

        m_vtxDescSize += size;

        if (size != 0) {
            m_vtxAttrSend |= 1 << i;
        }
    }
}

} // namespace EGG
