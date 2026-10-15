#include <nw4r/db.h>

#include <revolution/BASE.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace nw4r {
namespace db {

static OSTick sWarningTime = 0;
static ConsoleHandle sAssertionConsole = NULL;
static bool sDispWarningAuto = true;

static void Assertion_Printf_(const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);

    if (sAssertionConsole != NULL) {
        Console_VPrintf(sAssertionConsole, pFmt, argv);
    } else {
        OSVReport(pFmt, argv);
    }

    va_end(argv);
}

#if defined(NW4R_FEATURE_MAPFILE)
static bool ShowMapInfoSubroutine_(u32 address, bool preNewline) {
    if (address < 0x80000000 || address > 0x82FFFFFF) {
        return false;
    }

    // TODO(kiwi) Where does this number come from?
    u8 buffer[256 + 4];
    bool success = MapFile_QuerySymbol(address, buffer, sizeof(buffer));

    if (success) {
        if (preNewline) {
            Assertion_Printf_("\n");
        }

        Assertion_Printf_("%s\n", reinterpret_cast<char*>(buffer));
        return true;
    }

    return false;
    return false;
}
#else
static bool ShowMapInfoSubroutine_(u32 /* address */, bool /* preNewline */) {
    return false;
}
#endif

static void ShowStack_(u32 sp) {
    Assertion_Printf_("-------------------------------- TRACE\n");
    Assertion_Printf_("Address:   BackChain   LR save\n");

    u32* it = reinterpret_cast<u32*>(sp);
    u32 i;

    for (i = 0; i < 16; i++) {
        if (it == NULL || reinterpret_cast<u32>(it) == 0xFFFFFFFF) {
            break;
        }

        if (!(reinterpret_cast<u32>(it) & 0x80000000)) {
            break;
        }

        Assertion_Printf_("%08X:  %08X    %08X ", it, it[0], it[1]);

        if (!ShowMapInfoSubroutine_(it[1], false)) {
            Assertion_Printf_("\n");
        }

        it = reinterpret_cast<u32*>(*it);
    }
}

DECL_WEAK void VPanic(const char* pFile, int line, const char* pFmt,
                      std::va_list argv, bool halt) {
    register u32 sp_;
    ASM (
        mr sp_, r1
        lwz sp_, 0(sp_) // skip VPanic frame
    )

    OSDisableInterrupts();
    OSDisableScheduler();

    VISetPreRetraceCallback(NULL);
    VISetPostRetraceCallback(NULL);

    if (sAssertionConsole != NULL) {
        detail::DirectPrint_SetupFB(NULL);
    }

    ShowStack_(sp_);

    if (sAssertionConsole != NULL) {
        Console_Printf(sAssertionConsole, "%s:%d Panic:", pFile, line);
        Console_VPrintf(sAssertionConsole, pFmt, argv);
        Console_Printf(sAssertionConsole, "\n");

        Console_ShowLatestLine(sAssertionConsole);
        Console_SetVisible(sAssertionConsole, true);
        Console_DrawDirect(sAssertionConsole);
    } else {
        OSReport("%s:%d Panic:", pFile, line);
        OSVReport(pFmt, argv);
        OSReport("\n");
    }

    if (halt) {
        PPCHalt();
    }
}

DECL_WEAK void Panic(const char* pFile, int line, const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    VPanic(pFile, line, pFmt, argv, true);
    va_end(argv);

    PPCHalt();
}

DECL_WEAK void VWarning(const char* pFile, int line, const char* pFmt,
                        std::va_list argv) {
    if (sAssertionConsole != NULL) {
        Console_Printf(sAssertionConsole, "%s:%d Warning:", pFile, line);
        Console_VPrintf(sAssertionConsole, pFmt, argv);
        Console_Printf(sAssertionConsole, "\n");

        Console_ShowLatestLine(sAssertionConsole);

        if (sDispWarningAuto) {
            Assertion_ShowConsole(sWarningTime);
        }
    } else {
        OSReport("%s:%d Warning:", pFile, line);
        OSVReport(pFmt, argv);
        OSReport("\n");
    }
}

DECL_WEAK void Warning(const char* pFile, int line, const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);
    VWarning(pFile, line, pFmt, argv);
    va_end(argv);
}

DECL_WEAK void Log(const char* pFmt, ...) {
    std::va_list argv;
    va_start(argv, pFmt);

    if (sAssertionConsole != NULL) {
        Console_VPrintf(sAssertionConsole, pFmt, argv);
    } else {
        OSVReport(pFmt, argv);
    }

    va_end(argv);
}

ConsoleHandle Assertion_SetConsole(ConsoleHandle console) {
    ConsoleHandle old = sAssertionConsole;
    sAssertionConsole = console;
    return old;
}

ConsoleHandle Assertion_GetConsole() {
    return sAssertionConsole;
}

static OSAlarm& GetWarningAlarm_() {
    static bool sInitializedAlarm = false;
    static OSAlarm sWarningAlarm;

    if (!sInitializedAlarm) {
        OSCreateAlarm(&sWarningAlarm);
        sInitializedAlarm = true;
    }

    return sWarningAlarm;
}

static void WarningAlarmFunc_(OSAlarm* /* pAlarm */,
                              OSContext* /* pContext */) {
    if (sAssertionConsole != NULL) {
        Console_SetVisible(sAssertionConsole, false);
    }
}

void Assertion_ShowConsole(OSTick time) {
    if (sAssertionConsole == NULL) {
        return;
    }

    OSAlarm& rAlarm = GetWarningAlarm_();

    OSCancelAlarm(&rAlarm);
    Console_SetVisible(sAssertionConsole, true);

    if (time > 0) {
        OSSetAlarm(&rAlarm, time, WarningAlarmFunc_);
    }
}

void Assertion_SetWarningTime(OSTick time) {
    sWarningTime = time;
}

} // namespace db
} // namespace nw4r
