// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/prim.h>

#include <revolution/OS.h>

#include <cstdio>
#include <cstring>

#if defined(NONMATCHING) || defined(COMPAT_ANY)
void system_print(bool visible, const char* pFile, const char* pMsg, ...) {
#else
void system_print(bool visible, char* pFile, char* pMsg, ...) {
#endif
    if (!visible) {
        return;
    }

    char fileName[256];

    for (int i = 0; i < std::strlen(pFile); i++) {
        if (i >= 256) {
            return;
        }

        fileName[i] = pFile[i];

        if (pFile[i] == '.') {
            fileName[i] = '\0';
            break;
        }
    }

    OSReport("%s:", fileName);

    char msgBuf[2048];

    std::va_list list;
    va_start(list, pMsg);
    std::vsnprintf(msgBuf, sizeof(msgBuf), pMsg, list);
    va_end(list);

    OSReport("%s", msgBuf);
}

#if defined(NONMATCHING) || defined(COMPAT_ANY)
void system_halt(const char* pFile, int line, const char* pMsg, ...) {
#else
void system_halt(char* pFile, int line, char* pMsg, ...) {
#endif
    OSReport("---------- HALT -------------\n");

    char fileName[256];
    for (int i = 0; i < std::strlen(pFile); i++) {
        fileName[i] = pFile[i];

        if (pFile[i] == '.') {
            fileName[i] = '\0';
            break;
        }
    }

    OSReport("%s(%d):", fileName, line);

    char msg_buf[2048];

    std::va_list list;
    va_start(list, pMsg);
    std::vsnprintf(msg_buf, sizeof(msg_buf), pMsg, list);
    va_end(list);

    OSReport("%s\n", msg_buf);

#line 190
    OS_ERROR("Program Halt");
}
