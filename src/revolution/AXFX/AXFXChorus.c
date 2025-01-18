#include <revolution/AXFX.h>

static void __ParamConvert(AXFX_CHORUS* fx);

u32 AXFXChorusGetMemSize(const AXFX_CHORUS* fx) {
    return AXFXChorusExpGetMemSize(&fx->exp);
}

BOOL AXFXChorusInit(AXFX_CHORUS* fx) {
    __ParamConvert(fx);
    return AXFXChorusExpInit(&fx->exp);
}

BOOL AXFXChorusShutdown(AXFX_CHORUS* fx) {
    AXFXChorusExpShutdown(&fx->exp);
    return TRUE;
}

BOOL AXFXChorusSettings(AXFX_CHORUS* fx) {
    __ParamConvert(fx);
    return AXFXChorusExpSettings(&fx->exp);
}

void AXFXChorusCallback(void* chans, void* context) {
    AXFXChorusExpCallback((AXFX_BUFFERUPDATE*)chans, (AXFX_CHORUS_EXP*)context);
}

static void __ParamConvert(AXFX_CHORUS* fx) {
    fx->exp.delayTime = fx->baseDelay;
    fx->exp.depth = fx->variation / fx->exp.delayTime;
    fx->exp.rate = 1000.0f / fx->period;
    fx->exp.feedback = 0.0f;
    fx->exp.busIn = NULL;
    fx->exp.busOut = NULL;
    fx->exp.outGain = 1.0f;
    fx->exp.sendGain = 0.0f;
}