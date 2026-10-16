#ifndef RP_UTILITY_RANDOM_H
#define RP_UTILITY_RANDOM_H
#include <Pack/types_pack.h>

/**
 * @brief LCG random number generator
 */
class RPUtlRandom {
public:
    /**
     * @brief Seeds the generator using the system clock
     */
    static void initialize();
    void initRand();

    /**
     * @brief Generates a random unsigned 32-bit integer
     */
    static u32 getU32() {
        return sRandom.getRandU32();
    }
    u32 getRandU32() {
        return calcRand();
    }

    /**
     * @brief Generates a random unsigned 32-bit integer in the range [0, max)
     *
     * @param max Upper bound (exclusive)
     */
    static u32 getU32(u32 max) {
        return sRandom.getRandU32(max);
    }
    u32 getRandU32(u32 max) {
        return max * getRandF32();
    }

    /**
     * @brief Generates a random floating point value in the range [0, 1)
     */
    static f32 getF32() {
        return sRandom.getRandF32();
    }
    f32 getRandF32() {
        // Limited to u16 bounds
        u16 iRnd = static_cast<u16>(RANDF_MAX & (getRandU32() >> RANDF_SHIFT));

        // Convert to float
        f32 fRnd = static_cast<f32>(iRnd);

        // Convert to percentage (+1 makes the upper bound exclusive!)
        return fRnd / static_cast<f32>(RANDF_MAX + 1);
    }

private:
    /**
     * @brief Advances the generator seed
     */
    static u32 calc() {
        return sRandom.calcRand();
    }
    u32 calcRand() {
        return (mSeed = mSeed * MULT + 1);
    }

private:
    //! Seed multiplier
    static const u32 MULT;

    //! Integer limit for random floating point generation
    static const u32 RANDF_MAX;
    //! Bit shift amount for random floating point generation
    static const u32 RANDF_SHIFT;

    //! Global RNG
    static RPUtlRandom sRandom;
    
    //! Generator seed
    u32 mSeed;
};

#endif
