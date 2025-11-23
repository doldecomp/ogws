#include "file_io.h"

#pragma exceptions on

int fclose(FILE* pFile) {
    int flush_res, close_res;

    if (pFile == 0) {
        return -1;
    }

    if (pFile->mode.file == file_closed) {
        return 0;
    }

    flush_res = fflush(pFile);
    close_res = (*pFile->close_proc)(pFile->handle);
    pFile->mode.file = file_closed;
    pFile->handle = 0;

    if (pFile->state.free_buffer) {
        free(pFile->buffer);
    }

    return ((flush_res || close_res) ? -1 : 0);
}

int fflush(FILE* pFile) {
    long pos;

    if (pFile == 0) {
        return __flush_all();
    }

    if (pFile->state.error || pFile->mode.file == file_closed) {
        return -1;
    }

    if (pFile->mode.io == read) {
        return 0;
    }

    if (pFile->state.io_state >= rereading) {
        pFile->state.io_state = reading;
    }

    if (pFile->state.io_state == reading) {
        pFile->buffer_len = 0;
    }

    if (pFile->state.io_state != writing) {
        pFile->state.io_state = neutral;
        return 0;
    }

    if (pFile->mode.file != file_disk) {
        pos = 0;
    } else {
        pos = ftell(pFile);
    }

    if (__flush_buffer(pFile, 0)) {
        pFile->state.error = 1;
        pFile->buffer_len = 0;
        return -1;
    }

    pFile->state.io_state = neutral;
    pFile->pos = pos;
    pFile->buffer_len = 0;
    return 0;
}
