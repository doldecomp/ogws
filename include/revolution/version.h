#ifndef RVL_SDK_VERSION_H
#define RVL_SDK_VERSION_H
#include <types.h>

#define RVL_LIB_VERSION(NAME, ORIGINAL_DATE, ORIGINAL_TIME, ORIGINAL_CWCC)     \
    const char* __##NAME##Version =                                            \
        "<< RVL_SDK    - " #NAME " \trelease   build: " ORIGINAL_DATE          \
        " " ORIGINAL_TIME " (" ORIGINAL_CWCC ") >>"

#endif
