#ifndef RVL_SDK_VF_PF_SYSTEM_H
#define RVL_SDK_VF_PF_SYSTEM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFDATE {
    /* 0x00 */ u16 year;
    /* 0x02 */ u16 month;
    /* 0x04 */ u16 day;
} PFDATE;

typedef struct PFTIME {
    /* 0x00 */ u16 hour;
    /* 0x02 */ u16 minute;
    /* 0x04 */ u16 second;
    /* 0x06 */ u16 millisecond;
} PFTIME;

#ifdef __cplusplus
}
#endif
#endif
