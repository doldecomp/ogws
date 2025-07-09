#ifndef RVL_SDK_AI_HARDWARE_H
#define RVL_SDK_AI_HARDWARE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * AI hardware registers
 */
volatile u32 AI_HW_REGS ARRAY_AT_ADDRESS(0xCD006C00);

/**
 * Hardware register indexes
 */
typedef enum {
    AI_AICR,   //!< 0xCD006C00
    AI_AIVR,   //!< 0xCD006C04
    AI_AISCNT, //!< 0xCD006C08
    AI_AIIT,   //!< 0xCD006C0C
};

// AICR - AI Control Register
#define AI_AICR_SAMPLERATE (1 << 6)
#define AI_AICR_SCRESET (1 << 5)
#define AI_AICR_AIINTVLD (1 << 4)
#define AI_AICR_AIINT (1 << 3)
#define AI_AICR_AIINTMSK (1 << 2)
#define AI_AICR_AFR (1 << 1)
#define AI_AICR_PSTAT (1 << 0)

#ifdef __cplusplus
}
#endif
#endif
