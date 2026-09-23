#ifndef NW4R_DB_CONSOLE_H
#define NW4R_DB_CONSOLE_H

#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace nw4r {
namespace db {

enum ConsoleOutputType {
    CONSOLE_OUTPUT_NONE,
    CONSOLE_OUTPUT_DISPLAY,
    CONSOLE_OUTPUT_TERMINAL,
    CONSOLE_OUTPUT_ALL,
};

namespace detail {
//! Forward declaration required for ConsoleHandle
typedef struct ConsoleHead ConsoleHead;
} // namespace detail

typedef nw4r::db::detail::ConsoleHead* ConsoleHandle;

namespace detail {

struct ConsoleHead {
    u8* textBuf; // at 0x0
    u16 width;   // at 0x4
    u16 height;  // at 0x6
    u16 UNK_0x8;
    u16 UNK_0xA;
    u16 firstPrint; // at 0xC
    u16 xPosPrint;  // at 0xE
    u16 UNK_0x10;
    s32 UNK_0x14;
    s32 topLine;    // at 0x18
    s16 posX;       // at 0x1C
    s16 posY;       // at 0x1E
    u16 linesShown; // at 0x20
    bool isVisible; // at 0x22
    u8 PAD_0x23;
    nw4r::ut::TextWriter* writer; // at 0x24
    ConsoleHandle next;           // at 0x28
};

} // namespace detail

void Console_VFPrintf(ConsoleOutputType type, ConsoleHandle handle,
                      const char* fmt, std::va_list vlist);

} // namespace db
} // namespace nw4r

#endif
