#ifndef MSL_ERRNO_H
#define MSL_ERRNO_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern int errno;

#define ENOERR 0
#define EDOM 33
#define ERANGE 34
#define ESIGPARM 36
#define EFPOS 40
#define EILSEQ 84

#ifdef __cplusplus
}
#endif
#endif
