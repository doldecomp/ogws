#ifndef NW4R_SND_COMMON_H
#define NW4R_SND_COMMON_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace snd {

enum AuxBus { AUX_A, AUX_B, AUX_C, AUX_BUS_NUM };

enum OutputMode {
    OUTPUT_MODE_STEREO,
    OUTPUT_MODE_SURROUND,
    OUTPUT_MODE_DPL2,
    OUTPUT_MODE_MONO
};

namespace detail {

struct AdpcmParam {
    u16 coef[16];   // at 0x0
    u16 gain;       // at 0x20
    u16 pred_scale; // at 0x22
    u16 yn1;        // at 0x24
    u16 yn2;        // at 0x26
};

struct AdpcmLoopParam {
    u16 loop_pred_scale; // at 0x0
    u16 loop_yn1;        // at 0x2
    u16 loop_yn2;        // at 0x4
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
