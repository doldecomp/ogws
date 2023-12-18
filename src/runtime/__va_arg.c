#include <types.h>

void* __va_arg(va_list argp, int type) {
    char* pRegNo = &argp->gpr;
    int regNo = argp->gpr;
    int maxRegNo = 8;

    void* arg;
    int argSize = 4;

    int regsUsed = 1;
    int regAddend = 0;

    int savedRegBase = 0;
    int savedRegSize = 4;

    // Float/double argument (floats are passed as doubles)
    if (type == arg_ARGREAL) {
        // These use FPRs instead of GPRs
        regNo = argp->fpr;
        pRegNo = &argp->fpr;

        // These are 8 bytes
        argSize = 8;
        // These are saved after GPRs on the stack
        savedRegBase = 8 * 4;
        // These are saved as doubles (8-bytes)
        savedRegSize = 8;
    }

    // 64-bit ("double word") integral argument
    if (type == arg_DOUBLEWORD) {
        // These are 8 bytes
        argSize = 8;
        // These use two registers, so they cannot start after GPR 7
        maxRegNo = 7;

        // These do not start at even registers (aside from GPR 3).
        // An uneven reg ID means this is the first *of two* registers
        if (regNo & 1 != 0) {
            regAddend = 1;
        }

        // These use two GPRs
        regsUsed = 2;
    }

    // Argument was passed via a register
    if (regNo < maxRegNo) {
        // Correct for double-register args
        regNo += regAddend;

        // Access arg in the saved area
        arg = argp->reg_save_area + savedRegBase + (regNo * savedRegSize);
        // Advance register index
        *pRegNo = regNo + regsUsed;
    }
    // Argument was passed via the stack
    else {
        // Fix register index to stop further saved area access
        // May be a fix for double word args (maxRegNo would be 7)?
        *pRegNo = 8;

        // Access arg in the input area
        arg = ROUND_UP_PTR(argp->input_arg_area, argSize);
        // Advance input area pointer
        argp->input_arg_area = (char*)arg + argSize;
    }

    // Object reference
    if (type == arg_ARGPOINTER) {
        // Dereference pointer
        arg = *(void**)arg;
    }

    return arg;
}
