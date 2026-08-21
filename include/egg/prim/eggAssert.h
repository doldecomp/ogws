#ifndef EGG_PRIM_ASSERT_H
#define EGG_PRIM_ASSERT_H
#include <egg/types_egg.h>

#define EGG_PRINT(...) system_print(true, __FILE__, __VA_ARGS__)

#define EGG_ASSERT(EXP)                                                        \
    if (!(EXP))                                                                \
    system_halt(__FILE__, __LINE__, #EXP)

#define EGG_ASSERT_MSG(EXP, ...)                                               \
    if (!(EXP))                                                                \
    system_halt(__FILE__, __LINE__, __VA_ARGS__)

#if defined(NONMATCHING)
#define EGG_ASSERT_LINE(_, EXP)                                                \
    if (!(EXP))                                                                \
    system_halt(__FILE__, __LINE__, #EXP)

#define EGG_ASSERT_LINE_MSG(_, EXP)                                            \
    if (!(EXP))                                                                \
    system_halt(__FILE__, __LINE__, #EXP)
#else
// TODO(kiwi) Eventually phase out the other macros...
#define EGG_ASSERT_LINE(LINE, EXP)                                             \
    if (!(EXP))                                                                \
    system_halt(__FILE__, LINE, #EXP)

#define EGG_ASSERT_LINE_MSG(LINE, EXP)                                         \
    if (!(EXP))                                                                \
    system_halt(__FILE__, LINE, #EXP)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NONMATCHING) || defined(COMPAT_ANY)
void system_print(bool visible, const char* pFile, const char* pMsg, ...);
#else
void system_print(bool visible, char* pFile, char* pMsg, ...);
#endif

#if defined(NONMATCHING) || defined(COMPAT_ANY)
void system_halt(const char* pFile, int line, const char* pMsg, ...);
#else
void system_halt(char* pFile, int line, char* pMsg, ...);
#endif

#ifdef __cplusplus
}
#endif
#endif
