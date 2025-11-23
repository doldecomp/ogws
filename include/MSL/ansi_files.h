#ifndef _ANSI_FILES_H
#define _ANSI_FILES_H

#include "types.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define console_buff_mode _IOLBF
#define console_buff_size 256

typedef unsigned char console_buff[console_buff_size];

extern console_buff stdin_buff;
extern console_buff stdout_buff;
extern console_buff stderr_buff;

void __close_all();
u32 __flush_all();

#ifdef __cplusplus
};
#endif

#endif
