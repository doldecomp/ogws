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

    /**
     * @brief Generates a random unsigned 32-bit integer
     */
    static u32 getU32() {
        return calc();
    }

    /**
     * @brief Generates a random unsigned 32-bit integer in the range [0, max)
     *
     * @param max Upper bound (exclusive)
     */
    static u32 getU32(u32 max) {
        return max * getF32();
    }

    /**
     * @brief Generates a random floating point value in the range [0, 1)
     */
    static f32 getF32() {
        // Limited to u16 bounds
        u16 iRnd = static_cast<u16>(RANDF_MAX & (getU32() >> RANDF_SHIFT));

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
        return (sSeed = sSeed * MULT + 1);
    }

private:
    //! Seed multiplier
    static const u32 MULT;

    //! Integer limit for random floating point generation
    static const u32 RANDF_MAX;
    //! Bit shift amount for random floating point generation
    static const u32 RANDF_SHIFT;

    //! Global generator seed
    static u32 sSeed;
};

#endif
