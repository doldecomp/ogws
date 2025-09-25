#ifndef _UART_CONSOLE_IO_GCN_H
#define _UART_CONSOLE_IO_GCN_H

#include "file_struct.h"
#include "types.h"
#include "stdio.h"
#include "UART.h"

#ifdef __cplusplus
extern "C" {
#endif

int __read_console(unsigned long, unsigned char* buffer, size_t* count, void* ref);
int __write_console(unsigned long, unsigned char* buffer, size_t* count, void* ref);
int __close_console(unsigned long);

#ifdef __cplusplus
}
#endif

#endif