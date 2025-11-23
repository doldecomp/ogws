#ifndef MSL_WCHAR_H
#define MSL_WCHAR_H
#include <mbstring.h>
#include <internal/wprintf.h>
#include <wstring.h>
#include <limits.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define WCHAR_MIN SHRT_MIN
#define WCHAR_MAX USHRT_MAX

typedef wchar_t wint_t;	

#ifdef __cplusplus
}
#endif
#endif
