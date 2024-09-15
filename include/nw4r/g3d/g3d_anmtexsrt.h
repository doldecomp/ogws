#ifndef NW4R_G3D_ANMTEXSRT_H
#define NW4R_G3D_ANMTEXSRT_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace g3d {

// TODO: Moved to this file to resolve circular dependency
struct ResAnmTexSrtDataTypedef {
    static const int NUM_OF_MAT_TEX_MTX = 8;
    static const int NUM_OF_IND_TEX_MTX = 3;
    static const int NUM_OF_TEX_MTX = NUM_OF_MAT_TEX_MTX + NUM_OF_IND_TEX_MTX;
};

struct TexSrtTypedef {
    enum TexMatrixMode {
        TEXMATRIXMODE_MAYA,
        TEXMATRIXMODE_XSI,
        TEXMATRIXMODE_3DSMAX
    };
};

struct TexSrt : TexSrtTypedef {
    f32 Su; // at 0x0
    f32 Sv; // at 0x4
    f32 R;  // at 0x8
    f32 Tu; // at 0xc
    f32 Tv; // at 0x10

    enum Flag {};
};

struct TexSrtAnmResult : ResAnmTexSrtDataTypedef, TexSrtTypedef {
    u32 flags;                  // at 0x0
    u32 indFlags;               // at 0x4
    TexMatrixMode texMtxMode;   // at 0x8
    TexSrt srt[NUM_OF_TEX_MTX]; // at 0xC

    enum Flag {
        // TODO: Naming
        FLAG_0 = (1 << 0),
        FLAG_SCALE_ONE = (1 << 1),
        FLAG_ROT_ZERO = (1 << 2),
        FLAG_TRANS_ZERO = (1 << 3),

        NUM_OF_FLAGS = 4
    };
};

} // namespace g3d
} // namespace nw4r

#endif
