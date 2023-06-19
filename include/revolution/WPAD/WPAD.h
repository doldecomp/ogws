#ifndef REVOSDK_WPAD_H
#define REVOSDK_WPAD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*WPADCallback)(s32, s32);

UNKTYPE WPADControlSpeaker(s32, UNKWORD, WPADCallback);
BOOL WPADCanSendStreamData(s32);
UNKWORD WPADSendStreamData(s32, UNKTYPE *, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif