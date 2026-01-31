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

struct bmg_message {
    u32 group;
    u32 index;
};

#define MSG_GROUP(X) (((X) & 0xFFFFFFF0) >> 4)
#define MSG_INDEX(X) ((X) & 0x0000000F)
#define MSG_TUPLE(X) MSG_GROUP(X), MSG_INDEX(X)

#endif
