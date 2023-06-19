#ifndef REVOSDK_AI_H
#define REVOSDK_AI_H
#ifdef __cplusplus
extern "C" {
#endif

typedef void (* AIDMACallback)(void);

AIDMACallback AIRegisterDMACallback(AIDMACallback);

#ifdef __cplusplus
}
#endif
#endif