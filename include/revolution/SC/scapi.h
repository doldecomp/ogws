#ifndef REVOSDK_SC_SCAPI_H
#define REVOSDK_SC_SCAPI_H
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SCAspectRatio
{
    SC_ASPECT_4_3,
    SC_ASPECT_16_9
} SCAspectRatio;

u8 SCGetAspectRatio(void);

#ifdef __cplusplus
}
#endif
#endif