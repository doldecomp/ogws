#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <string.h>

static OSStateFlags StateFlags ALIGN(32);

static u32 CheckSum(const OSStateFlags* state) {
    int i;
    const u32* ptr = (const u32*)&state->BYTE_0x4;
    u32 checksum = 0;

    for (i = 0; i < (sizeof(OSStateFlags) / sizeof(u32)) - 1; i++) {
        checksum += *ptr++;
    }

    return checksum;
}

BOOL __OSWriteStateFlags(const OSStateFlags* state) {
    NANDFileInfo file;

    memcpy(&StateFlags, state, sizeof(OSStateFlags));
    StateFlags.checksum = CheckSum(&StateFlags);

    if (NANDOpen("/title/00000001/00000002/data/state.dat", &file,
                 NAND_ACCESS_WRITE) == NAND_RESULT_OK) {
        if (NANDWrite(&file, &StateFlags, sizeof(OSStateFlags)) !=
            sizeof(OSStateFlags)) {
            NANDClose(&file);
            return FALSE;
        }
        if (NANDClose(&file) != NAND_RESULT_OK) {
            return FALSE;
        }
    } else {
        return FALSE;
    }

    return TRUE;
}

BOOL __OSReadStateFlags(OSStateFlags* state) {
    NANDFileInfo file;

    if (NANDOpen("/title/00000001/00000002/data/state.dat", &file,
                 NAND_ACCESS_READ) == NAND_RESULT_OK) {

        s32 bytesRead = NANDRead(&file, &StateFlags, sizeof(OSStateFlags));
        NANDClose(&file);

        if (bytesRead != sizeof(OSStateFlags)) {
            NANDDelete("/title/00000001/00000002/data/state.dat");
            memset(state, 0, sizeof(OSStateFlags));
            return FALSE;
        }
    } else {
        memset(state, 0, sizeof(OSStateFlags));
        return FALSE;
    }

    if (CheckSum(&StateFlags) != StateFlags.checksum) {
        memset(state, 0, sizeof(OSStateFlags));
        return FALSE;
    }

    memcpy(state, &StateFlags, sizeof(OSStateFlags));
    return TRUE;
}
