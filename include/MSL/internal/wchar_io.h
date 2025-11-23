#ifndef MSL_WCHAR_IO_H
#define MSL_WCHAR_IO_H
#include <types.h>

#include <file_io.h>
#ifdef __cplusplus
extern "C" {
#endif

int fwide(FILE*, int);

#ifdef __cplusplus
}
#endif
#endif
