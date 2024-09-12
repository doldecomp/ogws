#ifndef NW4R_G3D_ANMCHR_H
#define NW4R_G3D_ANMCHR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

struct ChrAnmResult {
    u32 flags;       // at 0x0
    math::VEC3 s;    // at 0x4
    math::VEC3 rawR; // at 0x10
    math::MTX34 rt;  // at 0x1C

    // TODO: Give these better names
    enum Flag {
        FLAG_ANM_EXISTS = (1 << 0),
        FLAG_1 = (1 << 1),
        FLAG_2 = (1 << 2),
        FLAG_3 = (1 << 3),
        FLAG_4 = (1 << 4),
        FLAG_5 = (1 << 5),
        FLAG_6 = (1 << 6),
        FLAG_7 = (1 << 7),
        FLAG_8 = (1 << 8),
        FLAG_9 = (1 << 9),
        FLAG_10 = (1 << 10),
        FLAG_11 = (1 << 11),

        FLAG_31 = (1 << 31),
    };
};

struct AnmObjChr {};

struct AnmObjChrNode {};

struct AnmObjChrBlend {};

struct AnmObjChrRes {};

} // namespace g3d
} // namespace nw4r

#endif
