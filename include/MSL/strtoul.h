#ifndef _STRTOUL_H
#define _STRTOUL_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long __strtoul(int base, int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg,
                        int* chars_scanned, int* negative, int* overflow);
unsigned long long __strtoull(int base, int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg,
                              int* chars_scanned, int* negative, int* overflow);
int atoi(const char* str);

#ifdef __cplusplus
}
#endif

#endif
