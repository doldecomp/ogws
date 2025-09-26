#ifndef MSL_INTERNAL_STR_SCAN_H
#define MSL_INTERNAL_STR_SCAN_H

#include "stdio_api.h"

enum scan_states {
    start = 0x01,
    check_for_zero = 0x02,
    leading_zero = 0x04,
    need_digit = 0x08,
    digit_loop = 0x10,
    finished = 0x20,
    failure = 0x40
};

#define final_state(scan_state) ((scan_state) & (finished | failure))
#define success(scan_state) ((scan_state) & (leading_zero | digit_loop | finished))

#define fetch() (count++, (*ReadProc)(ReadProcArg, 0, __GetAChar))
#define unfetch(c) ((*ReadProc)(ReadProcArg, c, __UngetAChar))

#endif // MSL_INTERNAL_STR_SCAN_H