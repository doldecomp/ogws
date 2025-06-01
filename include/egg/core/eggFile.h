#ifndef EGG_CORE_FILE_H
#define EGG_CORE_FILE_H
#include <egg/types_egg.h>

namespace EGG {

class File {
public:
    File() : mIsOpen(false) {}
    virtual ~File() {} // at 0x8

    virtual bool open(const char* pPath) = 0; // at 0xC
    virtual void close() = 0;                 // at 0x10

    virtual s32 readData(void* pDst, s32 size, s32 offset) = 0; // at 0x14
    virtual s32 writeData(const void* pSrc, s32 size,
                          s32 offset) = 0; // at 0x18

    virtual u32 getFileSize() const = 0; // at 0x1C

protected:
    bool mIsOpen; // at 0x4
};

} // namespace EGG

#endif
