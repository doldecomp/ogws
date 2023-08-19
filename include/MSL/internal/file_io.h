#ifndef MSL_FILE_IO_H
#define MSL_FILE_IO_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct FILE {
    u8 dummy;
} FILE;

int fclose(FILE*);
int fflush(FILE*);

#ifdef __cplusplus
}
#endif
#endif
