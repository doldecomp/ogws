#include "ansi_files.h"

#include "uart_console_io_gcn.h"
#include "stdio.h"
#include "stdlib.h"
#include "file_struct.h"

FILE __stdout_FILE;
FILE __stderr_FILE;

// Force __file_terminator to the .data section instead .bss
#pragma push
#pragma explicit_zero_data on
#pragma section data_type ".data"
FILE __file_terminator = {0}; // lbl_80398888
#pragma pop

#pragma exceptions on

FILE __files[1] = {{
    0,
    { must_exist, read, _IOLBF, file_console, file_unoriented, 0 },
    { neutral, 0, 0, 0 },
    0,
    0,
    0,
    {0},
    {0},
    0,
    stdin_buff,
    console_buff_size,
    stdin_buff,
    0,
    0,
    0,
    0,
    NULL,
    __read_console,
    __write_console,
    __close_console,
    NULL,
    &__stdout_FILE
    }};

FILE __stdout_FILE = {
    1,
    { must_exist, write, _IOLBF, file_console, file_unoriented, 0 },
    { neutral, 0, 0, 0 },
    0,
    0,
    0,
    {0},
    {0},
    0,
    stdout_buff,
    console_buff_size,
    stdout_buff,
    0,
    0,
    0,
    0,
    NULL,
    __read_console,
    __write_console,
    __close_console,
    NULL,
    &__stderr_FILE
};

FILE __stderr_FILE = {
    2,
    { must_exist, write, _IONBF, file_console, file_unoriented, 0 },
    { neutral, 0, 0, 0 },
    0,
    0,
    0,
    {0},
    {0},
    0,
    stderr_buff,
    console_buff_size,
    stderr_buff,
    0,
    0,
    0,
    0,
    NULL,
    __read_console,
    __write_console,
    __close_console,
    NULL,
    &__file_terminator
};

void __close_all() {
    FILE* p = &__files[0];
    FILE* plast;

    while (p) {
        if (p->mode.file != file_closed) {
            fclose(p);
        }

        plast = p;
        p = p->next_file;
        if (plast->is_dyn_alloc) {
            free(plast);
        } else {
            plast->mode.file = file_unavailable;
            if ((p != NULL) && p->is_dyn_alloc) {
                plast->next_file = NULL;
            }
        }
    }
}

u32 __flush_all() {
    u32 retval = 0;
    FILE* __stream;
    __stream = &__files[0];
    while (__stream) {
        if ((__stream->mode.file) && (fflush(__stream))) {
            retval = -1;
        }
        __stream = __stream->next_file;
    };
    return retval;
}
