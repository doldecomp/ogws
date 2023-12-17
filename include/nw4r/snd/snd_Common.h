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

} // namespace snd
} // namespace nw4r

#endif
