#ifndef REVOSDK_WPAD_H
#define REVOSDK_WPAD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*WPADCallback)(s32 chan, s32 result);

typedef enum {
    WPAD_CHAN_0,
    WPAD_CHAN_1,
    WPAD_CHAN_2,
    WPAD_CHAN_3,
    WPAD_MAX_CONTROLLERS
} WPADChan;

typedef enum {
    WPAD_ERR_CORRUPTED = -7,
    WPAD_ERR_6,
    WPAD_ERR_5,
    WPAD_ERR_INVALID,
    WPAD_ERR_TRANSFER,
    WPAD_ERR_BUSY,
    WPAD_ERR_NO_CONTROLLER,

    WPAD_ERR_OK = 0,
} WPADResult;

typedef enum {
    WPAD_SPEAKER_OFF,
    WPAD_SPEAKER_ON,

    WPAD_SPEAKER_PLAY = 4,
} WPADSpeakerCommand;

s32 WPADControlSpeaker(s32, UNKWORD, WPADCallback);
BOOL WPADCanSendStreamData(s32);
s32 WPADSendStreamData(s32, UNKTYPE*, UNKWORD);

s32 WPADProbe(s32 chan, u32* type);
s32 WPADReadFaceData(s32 chan, void* dst, u32 size, u32 src, WPADCallback cb);

#ifdef __cplusplus
}
#endif
#endif