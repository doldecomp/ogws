#ifndef NW4R_TYPES_H
#define NW4R_TYPES_H
#include <types.h>

#include <nw4r/config.h>

#define NW4R_FILE_VERSION(major, minor) ((major & 0xFF) << 8 | minor & 0xFF)

#define NW4R_LIB_VERSION(NAME, ORIGINAL_DATE, ORIGINAL_TIME, ORIGINAL_CWCC)    \
    const char* NW4R_##NAME##_Version_ =                                       \
        "<< NW4R    - " #NAME " \tfinal   build: " ORIGINAL_DATE               \
        " " ORIGINAL_TIME " (" ORIGINAL_CWCC ") >>"

#endif
