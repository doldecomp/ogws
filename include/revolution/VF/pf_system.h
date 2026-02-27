#ifndef RVL_SDK_VF_PF_SYSTEM_H
#define RVL_SDK_VF_PF_SYSTEM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFDATE {
    u16 year;
    u16 month;
    u16 day;
} PFDATE;

typedef struct PFTIME {
    u16 hour;
    u16 minute;
    u16 second;
    u16 millisecond;
} PFTIME;

#ifdef __cplusplus
}
#endif
#endif
