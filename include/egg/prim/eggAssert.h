#ifndef EGG_PRIM_ASSERT_H
#define EGG_PRIM_ASSERT_H
#include "types_egg.h"

#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE system_halt(const char *str, ...);
UNKTYPE system_print(const char *str, ...);

#ifdef __cplusplus
}
#endif

#define EGG_ASSERT(expr, ...) \
    if (!(expr)) {system_halt(__VA_ARGS__);}

#endif