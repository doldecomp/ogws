#ifndef RP_ASSERT_H
#define RP_ASSERT_H
#include <Pack/types_pack.h>

#include <egg/prim.h>

/**
 * @brief Logs a formatted message to the console
 */
#define RP_PRINT(...) EGG_PRINT(__VA_ARGS__)

/**
 * @brief Asserts that a condition holds true
 * @details If the assertion fails, program execution is halted and the
 * expression is displayed.
 */
#define RP_ASSERT(EXP) EGG_ASSERT(EXP)

/**
 * @brief Asserts that a condition holds true
 * @details If the assertion fails, program execution is halted and the provided
 * message is displayed.
 */
#define RP_ASSERT_MSG(EXP, ...) EGG_ASSERT_MSG(EXP, __VA_ARGS__)

#endif
