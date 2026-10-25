#include <nw4r/db.h>

#include <revolution/OS.h>

#include <cstdio>

#define DEFAULT_VIEW_X 30
#define DEFAULT_VIEW_Y 50

namespace nw4r {
namespace db {

/******************************************************************************
 *
 * Text utilities
 *
 ******************************************************************************/

static u8* GetTextPtr_(ConsoleHandle console, u16 line, u16 x) {
    return console->textBuf + x + (console->width + 1) * line;
}

static u8* NextLine_(ConsoleHandle console) {
    *GetTextPtr_(console, console->printTop, console->printXPos) = '\0';

    console->printXPos = 0;
    console->printTop++;
    console->printTopUsed = 0;

    if (console->printTop == console->height &&
        !(console->attr & CONSOLE_ATTR_NO_OVERFLOW)) {

        console->printTop = 0;
    }

    if (console->printTop == console->ringTop) {
        console->ringTopLineCnt++;

        if (++console->ringTop == console->height) {
            console->ringTop = 0;
        }
    }

    return GetTextPtr_(console, console->printTop, 0);
}

static void TerminateLine_(ConsoleHandle console) {
    *GetTextPtr_(console, console->printTop, console->printXPos) = '\0';
}

static const u8* SearchEndOfLine_(const u8* pStr) {
    while (*pStr != '\n' && *pStr != '\0') {
        pStr++;
    }

    return pStr;
}

static u32 GetTabSize_(ConsoleHandle console) {
    s32 tab =
        (console->attr & (CONSOLE_ATTR_INDENT_4 | CONSOLE_ATTR_INDENT_8)) >> 2;

    return 2 << tab;
}

static u8* PutTab_(ConsoleHandle console, u8* pDst) {
    u32 width = GetTabSize_(console);

    do {
        *pDst++ = ' ';
        console->printXPos += 1;

        if (console->printXPos >= console->width) {
            break;
        }
    } while ((console->printXPos & (width - 1)) != 0);

    return pDst;
}

static u32 CodeWidth_(const u8* pPtr) {
    return *pPtr >= 0x81 ? 2 : 1;
}

static u32 PutChar_(ConsoleHandle console, const u8* pSrc, u8* pDst) {
    u32 width = CodeWidth_(pSrc);

    if (console->printXPos + width > console->width) {
        return 0;
    }

    console->printXPos += width;

    u32 remain = width;
    while (remain > 0) {
        *pDst++ = *pSrc++;
        remain--;
    }

    return width;
}

/******************************************************************************
 *
 * Console
 *
 ******************************************************************************/

static ConsoleHandle sConsoleList = NULL;
static OSMutex sMutex;
static bool sInitialized = false;

static u16 GetRingUsedLines_(ConsoleHandle console) {
    NW4R_NULL_ASSERT(console);

    s32 lines = console->printTop - console->ringTop;
    if (lines < 0) {
        lines += console->height;
    }

    return static_cast<u16>(lines);
}

static u16 GetActiveLines_(ConsoleHandle console) {
    u16 lines = GetRingUsedLines_(console);

    if (console->printTopUsed > 0) {
        lines++;
    }

    return lines;
}

static ConsoleHandle SearchConsoleFromListByPriority_(u16 priority) {
    ConsoleHandle console = sConsoleList;

    if (console == NULL || console->priority < priority) {
        return NULL;
    }

    for (; console->next != NULL; console = console->next) {
        if (console->next->priority < priority) {
            return console;
        }
    }

    return console;
}

static void AppendConsoleToList_(ConsoleHandle console) {
    NW4R_NULL_ASSERT(console);

    OSLockMutex(&sMutex);

    ConsoleHandle it = SearchConsoleFromListByPriority_(console->priority);

    if (it == NULL) {
        console->next = sConsoleList;
        sConsoleList = console;
    } else {
        console->next = it->next;
        it->next = console;
    }

    OSUnlockMutex(&sMutex);
}

static void RemoveConsoleFromList_(ConsoleHandle console) DECOMP_DONT_INLINE {
    NW4R_NULL_ASSERT(console);

    OSLockMutex(&sMutex);

    ConsoleHandle it = sConsoleList;

    if (it == console) {
        sConsoleList = console->next;
        console->next = NULL;
        goto _cleanup;
    }

    for (; it->next != NULL; it = it->next) {
        if (it->next == console) {
            it->next = console->next;
            console->next = NULL;
            goto _cleanup;
        }
    }

    OS_PANIC(LINE(332), "illegal console handle");

_cleanup:
    OSUnlockMutex(&sMutex);
}

ConsoleHandle Console_Create(void* pConsoleWork, u16 width, u16 height,
                             u16 viewLines, u16 priority, u16 attr) {
    if (!sInitialized) {
        OSInitMutex(&sMutex);
        sInitialized = true;
    }

    ConsoleHandle console = static_cast<ConsoleHandle>(pConsoleWork);

    console->textBuf =
        static_cast<u8*>(pConsoleWork) + sizeof(detail::ConsoleHead);

    console->width = width;
    console->height = height;
    console->priority = priority;
    console->attr = attr;
    console->isVisible = false;
    console->printTop = 0;
    console->printXPos = 0;
    console->printTopUsed = 0;
    console->ringTop = 0;
    console->ringTopLineCnt = 0;
    console->viewTopLine = 0;
    console->viewPosX = DEFAULT_VIEW_X;
    console->viewPosY = DEFAULT_VIEW_Y;
    console->viewLines = viewLines;
    console->writer = NULL;

    Console_Clear(console);
    AppendConsoleToList_(console);

    return console;
}

ConsoleHandle Console_Destroy(ConsoleHandle console) {
    NW4R_NULL_ASSERT(console);

    RemoveConsoleFromList_(console);
    return console;
}

void Console_Clear(ConsoleHandle console) {
    NW4R_NULL_ASSERT(console);

    OSLockMutex(&sMutex);

    console->printTop = 0;
    console->printXPos = 0;
    console->printTopUsed = 0;
    console->ringTop = 0;
    console->ringTopLineCnt = 0;
    console->viewTopLine = 0;

    OSUnlockMutex(&sMutex);
}

static void DoDrawString_(ConsoleHandle console, u32 line, const u8* pStr,
                          ut::TextWriter* pWriter) {

    if (pWriter != NULL) {
        pWriter->Printf("%s\n", pStr);
    } else {
        s32 height = console->viewPosY + line * NW4R_DB_FONT_LEADING;
        DirectPrint_DrawString(console->viewPosX, height, false, "%s\n", pStr);
    }
}

static void DoDrawConsole_(ConsoleHandle console, ut::TextWriter* pWriter) {
    s32 viewOffset = console->viewTopLine - console->ringTopLineCnt;
    u16 line;
    u16 printLines = 0;

    if (viewOffset < 0) {
        viewOffset = 0;
    } else if (viewOffset > GetActiveLines_(console)) {
        return;
    }

    line = console->ringTop + viewOffset;
    if (line >= console->height) {
        line -= console->height;
    }

    do {
        if (line == console->printTop && console->printTopUsed == 0) {
            break;
        }

        DoDrawString_(console, printLines, GetTextPtr_(console, line, 0),
                      pWriter);

        printLines++;

        if (line == console->printTop) {
            break;
        }

        line++;

        if (line == console->height) {
            if (console->attr & CONSOLE_ATTR_NO_OVERFLOW) {
                break;
            }

            line = 0;
        }
    } while (printLines < console->viewLines);
}

void Console_DrawDirect(ConsoleHandle console) {
    NW4R_NULL_ASSERT(LINE(682), console);

    if (!DirectPrint_IsActive()) {
        return;
    }

    if (!console->isVisible) {
        return;
    }

    OSLockMutex(&sMutex);

    int width = console->width * NW4R_DB_FONT_CHAR_WIDTH + 12;
    int height = console->viewLines * NW4R_DB_FONT_LEADING + 4;

    DirectPrint_EraseXfb(console->viewPosX - 6, console->viewPosY - 3, width,
                         height);

    DoDrawConsole_(console, NULL);
    DirectPrint_StoreCache();

    OSUnlockMutex(&sMutex);
}

static void PrintToBuffer_(ConsoleHandle console, const u8* str) {
    NW4R_NULL_ASSERT(LINE(806), console);
    NW4R_NULL_ASSERT(LINE(807), str);

    u8* pDst;
    bool newline;
    u32 bytes;

    pDst = GetTextPtr_(console, console->printTop, console->printXPos);

    while (*str != '\0') {
        if (console->attr & CONSOLE_ATTR_NO_OVERFLOW &&
            console->printTop == console->height) {

            break;
        }

        while (*str != '\0') {
            newline = false;

            if (*str == '\n') {
                str++;
                pDst = NextLine_(console);
                break;
            } else if (*str == '\t') {
                str++;
                pDst = PutTab_(console, pDst);
                console->printTopUsed = 1;
            } else {
                bytes = PutChar_(console, str, pDst);

                if (bytes > 0) {
                    str += bytes;
                    pDst += bytes;
                    console->printTopUsed = 1;
                } else {
                    newline = true;
                }
            }

            if (console->printXPos >= console->width) {
                newline = true;
            }

            if (newline) {
                if (console->attr & CONSOLE_ATTR_NO_WRAP) {
                    str = SearchEndOfLine_(str);
                } else {
                    if (*str == '\n') {
                        str++;
                    }

                    pDst = NextLine_(console);
                }
                break;
            }
        }
    }
}

static void Console_PrintString_(ConsoleOutputType output,
                                 ConsoleHandle console, const u8* pStr) {

    NW4R_NULL_ASSERT(LINE(909), console);

    if (output & CONSOLE_OUTPUT_TERMINAL) {
        OSReport("%s", pStr);
    }

    if (output & CONSOLE_OUTPUT_DISPLAY) {
        PrintToBuffer_(console, pStr);
    }
}

void Console_VFPrintf(ConsoleOutputType output, ConsoleHandle console,
                      const char* pFmt, std::va_list argv) {

    NW4R_NULL_ASSERT(LINE(941), console);

    OSLockMutex(&sMutex);

    static u8 sStrBuf[1024];
    std::vsnprintf(reinterpret_cast<char*>(sStrBuf), sizeof(sStrBuf), pFmt,
                   argv);

    Console_PrintString_(output, console, sStrBuf);

    OSUnlockMutex(&sMutex);
}

void Console_FPrintf(ConsoleOutputType output, ConsoleHandle console,
                     const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    Console_VFPrintf(output, console, pFmt, argv);
    va_end(argv);
}

void Console_Printf(ConsoleHandle console, const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    Console_VFPrintf(CONSOLE_OUTPUT_ALL, console, pFmt, argv);
    va_end(argv);
}

void Console_PrintfD(ConsoleHandle console, const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    Console_VFPrintf(CONSOLE_OUTPUT_DISPLAY, console, pFmt, argv);
    va_end(argv);
}

void Console_PrintfT(ConsoleHandle console, const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    Console_VFPrintf(CONSOLE_OUTPUT_TERMINAL, console, pFmt, argv);
    va_end(argv);
}

s32 Console_GetTotalLines(ConsoleHandle console) {
    NW4R_NULL_ASSERT(LINE(1128), console);

    OSLockMutex(&sMutex);
    s32 count = console->ringTopLineCnt + GetActiveLines_(console);
    OSUnlockMutex(&sMutex);

    return count;
}

} // namespace db
} // namespace nw4r
