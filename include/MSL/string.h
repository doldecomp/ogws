#ifndef MSL_STRING_H
#define MSL_STRING_H
#include <types.h>

#include <internal/mem.h>

#include <extras.h>
#ifdef __cplusplus
extern "C" {
#endif

char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);

char* strcat(char*, const char*);
char* strncat(char*, const char*, size_t);

int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);

char* strchr(const char*, int);
char* strstr(const char*, const char*);

size_t strlen(const char*);

#ifdef __cplusplus
}
#endif
#endif
