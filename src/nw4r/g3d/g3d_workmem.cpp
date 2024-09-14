#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {
namespace detail {
namespace workmem {
namespace {

const int WORKMEM_SIZE = 0x18000;
const int WORKMEM_OBJS = 2048;

union {
    u8 mem[WORKMEM_SIZE]; // at 0x0
    struct {
        math::_VEC3 tmpScale[WORKMEM_OBJS]; // at 0x0
        u32 mtxID[WORKMEM_OBJS];            // at 0x6000
    };
    u8 byteCode[WORKMEM_SIZE];                                  // at 0x0
    MdlZ mdlZ[WORKMEM_OBJS];                                    // at 0x0
    math::_MTX34 skinningMtx[WORKMEM_OBJS];                     // at 0x0
    math::_MTX34 bbMtx[WORKMEM_OBJS];                           // at 0x0
    u8 shpAnmResultBuf[WORKMEM_SIZE / sizeof(ShpAnmResultBuf)]; // at 0x0
} sTemp ALIGN(128);

} // namespace

math::VEC3* GetScaleTemporary() {
    return reinterpret_cast<math::VEC3*>(sTemp.tmpScale);
}

u32* GetMtxIDTemporary() {
    return sTemp.mtxID;
}

MdlZ* GetMdlZTemporary() {
    return sTemp.mdlZ;
}

math::MTX34* GetSkinningMtxTemporary() {
    return reinterpret_cast<math::MTX34*>(sTemp.skinningMtx);
}

math::MTX34* GetBillboardMtxTemporary() {
    return reinterpret_cast<math::MTX34*>(sTemp.bbMtx);
}

ShpAnmResultBuf* GetShpAnmResultBufTemporary() {
    return reinterpret_cast<ShpAnmResultBuf*>(sTemp.shpAnmResultBuf);
}

} // namespace workmem
} // namespace detail
} // namespace g3d
} // namespace nw4r
