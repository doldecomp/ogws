#ifndef NW4R_EF_TYPES_H
#define NW4R_EF_TYPES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

enum Axis {
    AXIS_X,
    AXIS_Y,
    AXIS_Z,

    AXIS_MAX
};

enum ColorLayer {
    COLOR_LAYER_1,
    COLOR_LAYER_2,

    COLOR_LAYER_MAX
};

enum ColorIndex {
    COLOR_IDX_PRI,
    COLOR_IDX_SEC,

    COLOR_IDX_MAX
};

enum TextureLayer {
    TEX_LAYER_1,
    TEX_LAYER_2,
    TEX_LAYER_3,

    TEX_LAYER_MAX
};

enum EvaluateStatus {
    NW4R_EF_ES_WAIT,
    NW4R_EF_ES_DONE,
    NW4R_EF_ES_STOP,
    NW4R_EF_ES_SKIP,
};

typedef void (*ModifierTravFunc)(void* pObject, u32 arg);

inline u8 ConvertF32RadToU8(f32 rad) {
    rad = math::FCeil(rad / NW4R_MATH_PI * 128.0f - 0.5f);
    return static_cast<int>(rad) % 256;
}

} // namespace ef
} // namespace nw4r

#endif
