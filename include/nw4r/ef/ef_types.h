#ifndef NW4R_EF_TYPES_H
#define NW4R_EF_TYPES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

#define NW4R_EF_MAX_EMITTER 1024
#define NW4R_EF_MAX_EFFECT 1024
#define NW4R_EF_MAX_PARTICLEMANAGER 1024
#define NW4R_EF_MAX_PARTICLE 1024

// Epsilon... but not actually epsilon???
#define NW4R_EF_EMIT_ANGLE_MIN (1.917476e-4f)
// 2 * PI... but not actually PI???
#define NW4R_EF_EMIT_ANGLE_MAX (2 * 3.1414969f)

namespace nw4r {
namespace ef {

static const u32 NUM_PARAMS = 6;

enum Axis {
    AXIS_X,
    AXIS_Y,
    AXIS_Z,

    AXIS_MAX
};

enum ColorLayer {
    COLOR_LAYER_0,
    COLOR_LAYER_1,

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
    TEX_LAYER_IND,

    TEX_LAYER_MAX
};

enum EvaluateStatus {
    NW4R_EF_ES_WAIT,
    NW4R_EF_ES_DONE,
    NW4R_EF_ES_STOP,
    NW4R_EF_ES_SKIP,
};

typedef u32 ForEachParam;
typedef void (*ForEachFunc)(void* pObject, ForEachParam param);

inline u8 ConvertF32RadToU8(f32 rad) {
    rad = math::FCeil(rad / NW4R_MATH_PI * 128.0f - 0.5f);
    return static_cast<int>(rad) % 256;
}

} // namespace ef
} // namespace nw4r

#endif
