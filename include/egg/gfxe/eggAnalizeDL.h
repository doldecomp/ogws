#ifndef EGG_GFXE_ANALIZE_DL_H
#define EGG_GFXE_ANALIZE_DL_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

namespace EGG {

class AnalizeDL {
public:
    enum CmdType {
        TYPE_NONE,
        TYPE_POSMTXINDX,
        TYPE_NRMMTXINDX,
        TYPE_PRIMITIVE,
        TYPE_VERTEX,
        TYPE_NOOP
    };

    struct VtxResult {
        static const int PNMTX_NUM = (GX_TEXMTX0 - GX_PNMTX0) / 3;

        CmdType m_type;             // at 0x0
        s16 m_posMtxIdx[PNMTX_NUM]; // at 0x4
        s16 m_nrmMtxIdx[PNMTX_NUM]; // at 0x18
        u32 WORD_0x2C;
        u8 m_primitive;            // at 0x30
        u16 m_vtxNum;              // at 0x32
        u16 m_vtxRemain;           // at 0x34
        s32 m_mtxIdx;              // at 0x38
        s32 m_vtxIdx;              // at 0x3C
        nw4r::math::VEC3 m_vtxPos; // at 0x40
    };

public:
    explicit AnalizeDL(const nw4r::g3d::ResShp shp);

    CmdType advance();

    const VtxResult& getVtxResult() const {
#line 115
        EGG_ASSERT(s_result.m_type == TYPE_VERTEX);
        return s_result;
    }

private:
    struct VtxPosArray {
        u8 m_stride;        // at 0x0
        const void* m_base; // at 0x4
    };

private:
    void configure();

private:
    const u8* m_DL;    // at 0x0
    const u8* m_DLPtr; // at 0x4

    u8 BYTE_0x8;
    u8 BYTE_0x9;

    u8 m_vtxDescSize;  // at 0xA
    u8 m_vtxAttrSize;  // at 0xB
    u16 m_vtxAttrSend; // at 0xC

    static const s8 s_attrTypeSize[];
    static const u8 s_compTypeSize[];

    static GXVtxDescList s_vtxDesc[nw4r::g3d::ResPrePrimDL::SIZE_GXVTXDESCLIST];

    static GXVtxAttrFmtList
        s_vtxAttr[nw4r::g3d::ResPrePrimDL::SIZE_GXVTXATTRFMTLIST];

    static VtxPosArray s_vtxPos;
    static VtxResult s_result;
};

} // namespace EGG

#endif
