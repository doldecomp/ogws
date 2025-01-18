#ifndef RVL_SDK_EUART_EUART_H
#define RVL_SDK_EUART_EUART_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EUART_ERROR_OK,
    EUART_ERROR_FATAL,
    EUART_ERROR_INVALID,
    EUART_ERROR_BUSY,
    EUART_ERROR_4,
    EUART_ERROR_EXI,
} EUARTError;

BOOL EUARTInit(void);
EUARTError InitializeUART(void);
EUARTError WriteUARTN(const char* msg, u32 n);

#ifdef __cplusplus
}
#endif
#endif
