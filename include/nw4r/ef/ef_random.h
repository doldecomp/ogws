#ifndef NW4R_EF_RANDOM_H
#define NW4R_EF_RANDOM_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ef {

class Random {
private:
    u32 mSeed; // at 0x0

public:
    void Srand(u32 seed) {
        mSeed = seed;
    }

    int Rand() {
        MixRandomSeed();
        return static_cast<int>(mSeed >> 16);
    }

    f32 RandFloat() {
        MixRandomSeed();
        return static_cast<f32>(mSeed >> 16) / 0x10000;
    }

private:
    void MixRandomSeed() {
        mSeed = mSeed * 0x343FD + 0x269EC3;
    }
};

} // namespace ef
} // namespace nw4r

#endif
