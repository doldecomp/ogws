#ifndef MSL_STDDEF_H
#define MSL_STDDEF_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif // NULL

#define offsetof(ST, M) ((size_t) & (((ST*)0)->M))

typedef signed long intptr_t;
typedef unsigned long uintptr_t;
typedef intptr_t ptrdiff_t;

typedef unsigned long size_t;

#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif

#ifdef __cplusplus
}
#endif
#endif
