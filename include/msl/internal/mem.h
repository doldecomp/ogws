#ifndef MSL_MEM_H
#define MSL_MEM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void*, const void*, size_t);
void* memset(void*, int, size_t);
void* memmove(void*, const void*, size_t);
void* memchr(const void*, int, size_t);
void* __memrchr(const void*, int, size_t);
int memcmp(const void*, const void*, size_t);

#ifdef __cplusplus
}
#endif
#endif
