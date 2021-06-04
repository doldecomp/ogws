#ifndef EGG_CORE_FILE_H
#define EGG_CORE_FILE_H
#include "types_egg.h"

namespace EGG
{
    struct File
    {
        virtual ~File() {}
        virtual bool open(const char *) = 0;
        virtual void close() = 0;
        virtual s32 readData(void *, s32, s32) = 0;
        virtual s32 writeData(const void *, s32, s32) = 0;
        virtual UNKWORD getFileSize() const = 0;
        virtual bool open(int) = 0;
        virtual bool open(const char *, void *) = 0;
    };
}

#endif