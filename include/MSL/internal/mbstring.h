#ifndef MSL_MBSTRING_H
#define MSL_MBSTRING_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int mbtowc(wchar_t*, const char*, size_t);
size_t mbstowcs(wchar_t*, const char*, size_t);
size_t wcstombs(char*, const wchar_t*, size_t);

#ifdef __cplusplus
}
#endif
#endif
