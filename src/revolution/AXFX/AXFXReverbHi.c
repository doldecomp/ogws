#include <revolution/AXFX.h>

static void __ParamConvert(AXFX_REVERBHI* fx);

u32 AXFXReverbHiGetMemSize(AXFX_REVERBHI* fx) {
    fx->exp.preDelayTimeMax = fx->preDelay;
    return AXFXReverbHiExpGetMemSize(&fx->exp);
}

BOOL AXFXReverbHiInit(AXFX_REVERBHI* fx) {
    __ParamConvert(fx);
    return AXFXReverbHiExpInit(&fx->exp);
}

BOOL AXFXReverbHiShutdown(AXFX_REVERBHI* fx) {
    AXFXReverbHiExpShutdown(&fx->exp);
    return TRUE;
}

BOOL AXFXReverbHiSettings(AXFX_REVERBHI* fx) {
    __ParamConvert(fx);
    return AXFXReverbHiExpSettings(&fx->exp);
}

void AXFXReverbHiCallback(void* chans, void* context) {
    AXFXReverbHiExpCallback((AXFX_BUFFERUPDATE*)chans,
                            (AXFX_REVERBHI_EXP*)context);
}

static void __ParamConvert(AXFX_REVERBHI* fx) {
    fx->exp.earlyMode = 5;
    fx->exp.preDelayTimeMax = fx->preDelay;
    fx->exp.preDelayTime = fx->preDelay;
    fx->exp.fusedMode = 0;
    fx->exp.fusedTime = fx->time;
    fx->exp.coloration = fx->coloration;
    fx->exp.damping = fx->damping;
    fx->exp.crosstalk = fx->crosstalk;
    fx->exp.earlyGain = 0.0f;
    fx->exp.fusedGain = 1.0f;
    fx->exp.busIn = NULL;
    fx->exp.busOut = NULL;
    fx->exp.outGain = fx->mix;
    fx->exp.sendGain = 0.0f;
}