#ifndef MSL_WMEM_H
#define MSL_WMEM_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

wchar_t* wmemcpy(wchar_t*, const wchar_t*, size_t);
wchar_t* wmemchr(wchar_t*, wchar_t, size_t);

#ifdef __cplusplus
}
#endif
#endif
