#ifndef NW4R_DB_EXCEPTION_H
#define NW4R_DB_EXCEPTION_H

#include <nw4r/types_nw4r.h>

#include <revolution/GX.h>

namespace nw4r {
namespace db {

// Forward declarations
namespace detail {
struct ConsoleHead;
} // namespace detail
typedef nw4r::db::detail::ConsoleHead* ConsoleHandle;

typedef bool (*ExceptionUserCallback)(ConsoleHandle console,
                                      void* pCallbackArg);

enum ExceptionDisplayInfo {
    EXCEPTION_DISPLAY_MAININFO = 1 << 0,
    EXCEPTION_DISPLAY_GPR = 1 << 1,
    EXCEPTION_DISPLAY_GPRMAP = 1 << 2,
    EXCEPTION_DISPLAY_SRR0 = 1 << 3,
    EXCEPTION_DISPLAY_FPR = 1 << 4,
    EXCEPTION_DISPLAY_STACKTRACE = 1 << 5,
};

void Exception_Init();

ConsoleHandle Exception_SetConsole(ConsoleHandle console,
                                   const GXRenderModeObj* pRenderMode);
ConsoleHandle Exception_GetConsole();

void Exception_SetUserCallback(ExceptionUserCallback pCallback,
                               void* pCallbackArg);

u16 Exception_SetDisplayInfo(u16 displayInfo);

} // namespace db
} // namespace nw4r

#endif
