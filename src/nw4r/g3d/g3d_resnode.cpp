#pragma ipa file // TODO: REMOVE AFTER REFACTOR

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

    if (flags & ChrAnmResult::FLAG_7) {
        if (r.flags & FLAG_SCALE_ONE) {
            flags |= ChrAnmResult::FLAG_3 | ChrAnmResult::FLAG_4;
        } else {
            if (r.flags & FLAG_SCALE_UNIFORM) {
                flags |= ChrAnmResult::FLAG_4;
            }

            pResult->s = static_cast<math::VEC3&>(r.scale);
        }
    }

    if (flags & ChrAnmResult::FLAG_8) {
        if (r.flags & FLAG_ROT_ZERO) {
            flags |= ChrAnmResult::FLAG_5;
        } else {
            math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
            flags &= ~ChrAnmResult::FLAG_5;
        }

        flags |= ChrAnmResult::FLAG_31;
    }

    if (flags & ChrAnmResult::FLAG_9) {
        if (r.flags & FLAG_TRANS_ZERO) {
            flags |= ChrAnmResult::FLAG_6;
        } else {
            flags &= ~ChrAnmResult::FLAG_6;

            pResult->rt[0][3] = r.translate.x;
            pResult->rt[1][3] = r.translate.y;
            pResult->rt[2][3] = r.translate.z;
        }
    }

    if ((flags & ChrAnmResult::FLAG_5) && (flags & ChrAnmResult::FLAG_6)) {
        flags |= ChrAnmResult::FLAG_2;

        if (flags & ChrAnmResult::FLAG_3) {
            flags |= ChrAnmResult::FLAG_1;
        }
    }

    pResult->flags = flags & ~(ChrAnmResult::FLAG_7 | ChrAnmResult::FLAG_8 |
                               ChrAnmResult::FLAG_9);
}

void ResNode::CalcChrAnmResult(ChrAnmResult* pResult) const {
    if (!IsValid()) {
        return;
    }

    const ResNodeData& r = ref();
    u32 flags = 0;

    if (r.flags & FLAG_SCALE_ONE) {
        flags |= ChrAnmResult::FLAG_3 | ChrAnmResult::FLAG_4;

        pResult->s.z = 1.0f;
        pResult->s.y = 1.0f;
        pResult->s.x = 1.0f;
    } else {
        if (r.flags & FLAG_SCALE_UNIFORM) {
            flags |= ChrAnmResult::FLAG_4;
        }

        pResult->s = static_cast<math::VEC3&>(r.scale);
    }

    if (r.flags & FLAG_ROT_ZERO) {
        PSMTXIdentity(pResult->rt);
        flags |= ChrAnmResult::FLAG_5;
    } else {
        pResult->rawR = math::VEC3(r.rot);
        math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
    }

    if (r.flags & FLAG_TRANS_ZERO) {
        flags |= ChrAnmResult::FLAG_6;
    } else {
        pResult->rt[0][3] = r.translate.x;
        pResult->rt[1][3] = r.translate.y;
        pResult->rt[2][3] = r.translate.z;
    }

    if (flags & ChrAnmResult::FLAG_5) {
        if (flags & ChrAnmResult::FLAG_6) {
            flags |= ChrAnmResult::FLAG_2;

            if (flags & ChrAnmResult::FLAG_3) {
                flags |= ChrAnmResult::FLAG_1;
            }
        }
    }

    flags |= ChrAnmResult::FLAG_31;
    flags |= ChrAnmResult::FLAG_ANM_EXISTS;

    if (r.flags & FLAG_COMP_SCALE) {
        flags |= ChrAnmResult::FLAG_10;
    }

    if (r.flags & FLAG_COMP_CHILD_SCALE) {
        flags |= ChrAnmResult::FLAG_11;
    }

    pResult->flags = flags;
}

} // namespace g3d
} // namespace nw4r
