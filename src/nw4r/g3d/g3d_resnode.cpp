#include <nw4r/g3d.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

void ResNode::PatchChrAnmResult(ChrAnmResult* pResult) const {
    if (!IsValid()) {
        return;
    }

    const ResNodeData& r = ref();
    u32 flags = pResult->flags;

    if (flags & ChrAnmResult::FLAG_PATCH_S) {
        if (r.flags & FLAG_S_ONE) {
            flags |= ChrAnmResult::FLAG_S_ONE | ChrAnmResult::FLAG_S_UNIFORM;
        } else {
            if (r.flags & FLAG_S_UNIFORM) {
                flags |= ChrAnmResult::FLAG_S_UNIFORM;
            }

            pResult->s = static_cast<math::VEC3&>(r.scale);
        }
    }

    if (flags & ChrAnmResult::FLAG_PATCH_R) {
        if (r.flags & FLAG_R_ZERO) {
            flags |= ChrAnmResult::FLAG_R_ZERO;
        } else {
            math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
            flags &= ~ChrAnmResult::FLAG_R_ZERO;
        }

        flags |= ChrAnmResult::FLAG_R_RAW_FMT;
    }

    if (flags & ChrAnmResult::FLAG_PATCH_T) {
        if (r.flags & FLAG_T_ZERO) {
            flags |= ChrAnmResult::FLAG_T_ZERO;
        } else {
            flags &= ~ChrAnmResult::FLAG_T_ZERO;

            pResult->rt._03 = r.translate.x;
            pResult->rt._13 = r.translate.y;
            pResult->rt._23 = r.translate.z;
        }
    }

    if ((flags & ChrAnmResult::FLAG_R_ZERO) &&
        (flags & ChrAnmResult::FLAG_T_ZERO)) {
        flags |= ChrAnmResult::FLAG_RT_ZERO;

        if (flags & ChrAnmResult::FLAG_S_ONE) {
            flags |= ChrAnmResult::FLAG_MTX_IDENT;
        }
    }

    pResult->flags =
        flags & ~(ChrAnmResult::FLAG_PATCH_S | ChrAnmResult::FLAG_PATCH_R |
                  ChrAnmResult::FLAG_PATCH_T);
}

void ResNode::CalcChrAnmResult(ChrAnmResult* pResult) const {
    if (!IsValid()) {
        return;
    }

    const ResNodeData& r = ref();
    u32 flags = 0;

    if (r.flags & FLAG_S_ONE) {
        flags |= ChrAnmResult::FLAG_S_ONE | ChrAnmResult::FLAG_S_UNIFORM;

        pResult->s.z = 1.0f;
        pResult->s.y = 1.0f;
        pResult->s.x = 1.0f;
    } else {
        if (r.flags & FLAG_S_UNIFORM) {
            flags |= ChrAnmResult::FLAG_S_UNIFORM;
        }

        pResult->s = static_cast<math::VEC3&>(r.scale);
    }

    if (r.flags & FLAG_R_ZERO) {
        PSMTXIdentity(pResult->rt);
        flags |= ChrAnmResult::FLAG_R_ZERO;
    } else {
        pResult->rawR = math::VEC3(r.rot);
        math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
    }

    if (r.flags & FLAG_T_ZERO) {
        flags |= ChrAnmResult::FLAG_T_ZERO;
    } else {
        pResult->rt._03 = r.translate.x;
        pResult->rt._13 = r.translate.y;
        pResult->rt._23 = r.translate.z;
    }

    if (flags & ChrAnmResult::FLAG_R_ZERO) {
        if (flags & ChrAnmResult::FLAG_T_ZERO) {
            flags |= ChrAnmResult::FLAG_RT_ZERO;

            if (flags & ChrAnmResult::FLAG_S_ONE) {
                flags |= ChrAnmResult::FLAG_MTX_IDENT;
            }
        }
    }

    flags |= ChrAnmResult::FLAG_R_RAW_FMT;
    flags |= ChrAnmResult::FLAG_ANM_EXISTS;

    if (r.flags & FLAG_COMP_SCALE) {
        flags |= ChrAnmResult::FLAG_COMP_SCALE;
    }

    if (r.flags & FLAG_COMP_CHILD_SCALE) {
        flags |= ChrAnmResult::FLAG_11;
    }

    pResult->flags = flags;
}

} // namespace g3d
} // namespace nw4r
