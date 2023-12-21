#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

void LfoParam::Init() {
    depth = 0.0f;
    range = 1;
    speed = 6.25f;
    delay = 0;
}

void Lfo::Reset() {
    mDelayCounter = 0;
    mCounter = 0.0f;
}

void Lfo::Update(int msec) {
    if (mDelayCounter < mParam.delay) {
        if (mDelayCounter + msec <= mParam.delay) {
            mDelayCounter += msec;
            return;
        }

        msec -= mParam.delay - mDelayCounter;
        mDelayCounter = mParam.delay;
    }

    mCounter += mParam.speed * msec / 1000.0f;
    mCounter -= static_cast<int>(mCounter);
}

s8 Lfo::GetSinIdx(int i) {
    static const u8 sinTable[32 + 1] = {
        0,   6,   12,  19,  25,  31,  37,  43,  49,  54,  60,
        65,  71,  76,  81,  85,  90,  94,  98,  102, 106, 109,
        112, 115, 117, 120, 122, 123, 125, 126, 126, 127, 127};

    if (i < 32) {
        return sinTable[i];
    }

    if (i < 64) {
        return sinTable[32 - static_cast<int>(i - 32)];
    }

    if (i < 96) {
        return -sinTable[i - 64];
    }

    return -sinTable[32 - (i - 96)];
}

f32 Lfo::GetValue() const {
    if (mParam.depth == 0.0f) {
        return 0.0f;
    }

    if (mDelayCounter < mParam.delay) {
        return 0.0f;
    }

    f32 value = GetSinIdx(4.0f * (32.0f * mCounter)) / 127.0f;
    value *= mParam.depth;
    value *= mParam.range;

    return value;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
