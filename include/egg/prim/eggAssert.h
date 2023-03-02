#ifndef EGG_PRIM_ASSERT_H
#define EGG_PRIM_ASSERT_H
#include <types.h>

#define EGG_ASSERT(EXP) if (!(EXP)) system_halt(__FILE__, __LINE__, #EXP)
#define EGG_ASSERT_MSG(EXP, ...) if (!(EXP)) system_halt(__FILE__, __LINE__, __VA_ARGS__)
#define EGG_PRINT(...) system_print(true, __FILE__, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

void system_halt(char *file, int line, char *msg, ...);
void system_print(bool bVisible, char *file, char *msg, ...);

#ifdef __cplusplus
}
#endif
#endif