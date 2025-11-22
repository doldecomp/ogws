#ifndef RP_TYPES_H
#define RP_TYPES_H
#include <types.h>

/**
 * @brief Holds year, month, month day
 * @note Only years after (and including) 2000 can be represented.
 */
typedef u16 RPTime16;

/**
 * @brief Holds year, month, month day, week day, hour
 * @note Only years after (and including) 2000 can be represented.
 */
typedef u32 RPTime32;

#endif
