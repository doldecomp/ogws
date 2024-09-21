#include "eggAssert.h"
#include <revolution/OS/OSError.h>
#include <string.h>
#include <stdio.h>

void system_print(bool bVisible, char *file, char *msg, ...)
{
    if (!bVisible) return;

    char filename_buf[0x100];
    for (int i = 0; i < strlen(file); i++)
    {
        if (i >= 0x100) return;

        filename_buf[i] = file[i];

        if (file[i] == '.')
        {
            filename_buf[i] = '\0';
            break;
        }
    }
    OSReport("%s:", filename_buf);

    char msg_buf[0x800];
    va_list list;
    va_start(list, msg);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);
    OSReport("%s", msg_buf);
}

void system_halt(char *file, int line, char *msg, ...)
{
    OSReport("---------- HALT -------------\n");

    char filename_buf[0x100];
    for (int i = 0; i < strlen(file); i++)
    {
        filename_buf[i] = file[i];

        if (file[i] == '.')
        {
            filename_buf[i] = '\0';
            break;
        }
    }
    OSReport("%s(%d):", filename_buf, line);

    char msg_buf[0x800];
    va_list list;
    va_start(list, msg);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);
    OSReport("%s\n", msg_buf);

    #line 190
    OSError("Program Halt");
}
