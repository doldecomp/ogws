#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

s16 DecodeDspAdpcm(AXPBADPCM* adpcm, u8 bits) {
    s16 yn1 = adpcm->yn1;
    s16 yn2 = adpcm->yn2;

    s16 scale = 1 << (adpcm->pred_scale & 0x0F);
    s16 bits2 = bits << 12;
    s16 index = adpcm->pred_scale >> 4;

    s16 coef0 = adpcm->a[index][0];
    s16 coef1 = adpcm->a[index][1];

    s32 sample = coef0 * yn1;
    sample += coef1 * yn2;
    sample += scale * (bits2 >> 1);
    sample >>= 10;
    sample += 1;
    sample >>= 1;

    if (sample > 32767) {
        sample = 32767;
    } else if (sample < -32768) {
        sample = -32768;
    }

    adpcm->yn2 = adpcm->yn1;
    adpcm->yn1 = sample;
    return sample;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
