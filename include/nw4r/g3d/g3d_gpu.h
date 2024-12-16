#ifndef NW4R_G3D_GPU_H
#define NW4R_G3D_GPU_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {
namespace fifo {

// Swap bits to get hardware representation
static const u8 cm2hw[] = {0b0000, 0b0010, 0b0001, 0b0011};

inline void LoadBPCmd(u32 reg) {
    GXCmd1u8(GX_FIFO_CMD_LOAD_BP_REG);
    GXCmd1u32(reg);
}

inline void LoadCPCmd(u8 addr, u32 value) {
    GXCmd1u8(GX_FIFO_CMD_LOAD_CP_REG);
    GXCmd1u8(addr);
    GXCmd1u32(value);
}

inline void LoadXFCmd(u16 addr, u32 value) {
    GXCmd1u8(GX_FIFO_CMD_LOAD_XF_REG);
    GXCmd1u16(0); // No size (single write)
    GXCmd1u16(addr);
    GXCmd1u32(value);
}

inline void LoadXFCmdHdr(u16 addr, u8 len) {
    GXCmd1u8(GX_FIFO_CMD_LOAD_XF_REG);
    GXCmd1u16(len - 1);
    GXCmd1u16(addr);
}

void GDSetGenMode2(u8 numTexGens, u8 numChans, u8 numTevs, u8 numInds,
                   GXCullMode cullMode);

void GDSetCullMode(GXCullMode cullMode);

void GDSetTexCoordScale2(GXTexCoordID coord, u16 scaleS, u8 biasS, u8 wrapS,
                         u16 scaleT, u8 biasT, u8 wrapT);

void GDSetIndTexMtx(u32 id, const math::MTX34& rMtx);

void GDResetCurrentMtx();
void GDSetCurrentMtx(const u32* pIdArray);

void GDLoadTexMtxImm3x3(const math::MTX33& rMtx, u32 id);

} // namespace fifo
} // namespace g3d
} // namespace nw4r

#endif
