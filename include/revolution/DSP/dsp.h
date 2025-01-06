#ifndef RVL_SDK_DSP_H
#define RVL_SDK_DSP_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct DSPTask DSPTask;

// General-purpose typedef
typedef void* DSPMail;

BOOL DSPCheckMailToDSP(void);
BOOL DSPCheckMailFromDSP(void);
DSPMail DSPReadMailFromDSP(void);
void DSPSendMailToDSP(DSPMail mail);
void DSPAssertInt(void);
void DSPInit(void);
BOOL DSPCheckInit(void);
DSPTask* DSPAddTask(DSPTask* task);
DSPTask* DSPAssertTask(DSPTask* task);

#ifdef __cplusplus
}
#endif
#endif
