#ifndef EGG_PRIM_ASSERT_H
#define EGG_PRIM_ASSERT_H

#define EGG_ASSERT(EXP) (void)((EXP) || (system_halt(__FILE__, __LINE__, #EXP),0))
#define EGG_ASSERT_MSG(EXP, ...) (void)((EXP) || (system_halt(__FILE__, __LINE__, __VA_ARGS__),0))

#ifdef __cplusplus
extern "C" {
#endif

void system_halt(char const * file, int line, char const * msg, ...);

#ifdef __cplusplus
}
#endif
#endif