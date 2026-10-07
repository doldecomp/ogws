#ifndef NW4R_DB_ASSERT_H
#define NW4R_DB_ASSERT_H

#include <nw4r/types_nw4r.h>

#include <decomp/assertion.h>

#include <revolution/OS.h>

namespace nw4r {
namespace db {

// Forward declarations
namespace detail {
struct ConsoleHead;
} // namespace detail
typedef nw4r::db::detail::ConsoleHead* ConsoleHandle;

/* DECL_WEAK */ void VPanic(const char* pFile, int line, const char* pFmt,
                            std::va_list argv, bool halt);
/* DECL_WEAK */ void Panic(const char* pFile, int line, const char* pFmt, ...);

/* DECL_WEAK */ void VWarning(const char* pFile, int line, const char* pFmt,
                              std::va_list argv);
/* DECL_WEAK */ void Warning(const char* pFile, int line, const char* pFmt,
                             ...);

/* DECL_WEAK */ void Log(const char* pFmt, ...);

ConsoleHandle Assertion_SetConsole(ConsoleHandle console);
ConsoleHandle Assertion_GetConsole();

void Assertion_ShowConsole(OSTick time);
void Assertion_SetWarningTime(OSTick time);

} // namespace db
} // namespace nw4r

#if defined(NW4R_FEATURE_ASSERT)

// NW4R does not use line number tuples
#define NW4R_LINES(...) __LINE__

// clang-format off

//! Logs a message
#define NW4R_LOG(...) nw4r::db::Log(__VA_ARGS__)

//! Emits a warning
#define NW4R_WARN(...) DECOMP_ASSERT(NW4R_WARN_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_WARN_IMPL(file, line, ...)                                        \
    nw4r::db::Warning(file, line, __VA_ARGS__)

//! Halts the program
#define NW4R_PANIC(...) DECOMP_ASSERT(NW4R_PANIC_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_PANIC_IMPL(file, line, ...)                                       \
    nw4r::db::Panic(file, line, "NW4R:Fatal Error\n" __VA_ARGS__)

//! Halts the program if the specified condition does not hold
#define NW4R_ASSERT(...) DECOMP_ASSERT(NW4R_ASSERT_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_ASSERT_IMPL(file, line, exp)                                      \
    ((exp) && 1 ||                                                             \
        (nw4r::db::Panic(file, line,                                           \
            "NW4R:Failed assertion " #exp),                                    \
                0))

//! Halts the program if the specified value is misaligned
#define NW4R_ALIGN_ASSERT(...) DECOMP_ASSERT(NW4R_ALIGN_ASSERT_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_ALIGN_ASSERT_IMPL(file, line, value, alignment)                   \
    (reinterpret_cast<u32>(value) % (alignment) == 0 && 1 ||                   \
        (nw4r::db::Panic(file, line,                                           \
            "NW4R:Alignment Error(0x%x)\n" #value                              \
            " must be aligned to " #alignment " bytes boundary."),             \
                0))

//! Halts the program if the specified pointer is NULL
#define NW4R_NULL_ASSERT(...) DECOMP_ASSERT(NW4R_NULL_ASSERT_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_NULL_ASSERT_IMPL(file, line, ptr)                                 \
    ((ptr) != NULL && 1 ||                                                     \
        (nw4r::db::Panic(file, line,                                           \
            "NW4R:Pointer must not be NULL (" #ptr ")"),                       \
                0))

//! Halts the program if the specified pointer is invalid
#define NW4R_POINTER_ASSERT(...) DECOMP_ASSERT(NW4R_POINTER_ASSERT_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_POINTER_ASSERT_IMPL(file, line, ptr)                                 \
    (((reinterpret_cast<u32>(ptr) & 0xFF000000) == 0x80000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xFF800000) == 0x81000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xF8000000) == 0x90000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xFF000000) == 0xC0000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xFF800000) == 0xC1000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xF8000000) == 0xD0000000 ||               \
      (reinterpret_cast<u32>(ptr) & 0xFFFFC000) == 0xE0000000) && 1 ||         \
        (nw4r::db::Panic(file, line,                                           \
            "NW4R:Pointer Error\n" #ptr "(=%p) is not valid pointer.", (ptr)), \
                0))

//! Halts the program if the specified decimal value is invalid
#define NW4R_FLOAT_ASSERT(...) DECOMP_ASSERT(NW4R_FLOAT_ASSERT_IMPL, NW4R_LINES, __VA_ARGS__)
#define NW4R_FLOAT_ASSERT_IMPL(file, line, fp)                                 \
    (isfinite((fp)) && !isnan((fp)) && 1 ||                                    \
        (nw4r::db::Panic(file, line,                                           \
            "NW4R:Floating Point Value Error(%f)\n" #fp                        \
            " is infinite or nan.", (fp)),                                     \
                0))

// clang-format on

#else

#define NW4R_WARN(...)
#define NW4R_PANIC(...)
#define NW4R_ASSERT(...)
#define NW4R_ASSERT_MSG(...)
#define NW4R_ALIGN_ASSERT(...)
#define NW4R_NULL_ASSERT(...)
#define NW4R_POINTER_ASSERT(...)
#define NW4R_FLOAT_ASSERT(...)

#endif

#endif
