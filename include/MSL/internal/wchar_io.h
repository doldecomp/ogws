#ifndef MSL_WCHAR_IO_H
#define MSL_WCHAR_IO_H
#include <file_io.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int fwide(FILE*, int);

#ifdef __cplusplus
}
#endif
#endif
