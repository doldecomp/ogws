#include <revolution/AX.h>
#include <revolution/AXFX.h>

static void __ParamConvert(AXFX_REVERBHI_DPL2* fx);

u32 AXFXReverbHiGetMemSizeDpl2(AXFX_REVERBHI_DPL2* fx) {
    fx->exp.preDelayTimeMax = fx->preDelay;
    return AXFXReverbHiExpGetMemSizeDpl2(&fx->exp);
}

BOOL AXFXReverbHiInitDpl2(AXFX_REVERBHI_DPL2* fx) {
    if (AXGetMode() != AX_OUTPUT_DPL2) {
        return FALSE;
    }

    __ParamConvert(fx);
    return AXFXReverbHiExpInitDpl2(&fx->exp);
}

BOOL AXFXReverbHiShutdownDpl2(AXFX_REVERBHI_DPL2* fx) {
    AXFXReverbHiExpShutdownDpl2(&fx->exp);
    return TRUE;
}

BOOL AXFXReverbHiSettingsDpl2(AXFX_REVERBHI_DPL2* fx) {
    __ParamConvert(fx);
    return AXFXReverbHiExpSettingsDpl2(&fx->exp);
}

void AXFXReverbHiCallbackDpl2(void* chans, void* context) {
    AXFXReverbHiExpCallbackDpl2((AXFX_BUFFERUPDATE_DPL2*)chans,
                                (AXFX_REVERBHI_EXP_DPL2*)context);
}

static void __ParamConvert(AXFX_REVERBHI_DPL2* fx) {
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