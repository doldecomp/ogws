#include <revolution/OS.h>
#include <revolution/SI.h>
#include <revolution/VI.h>

typedef struct SIPollSetting {
    struct {
        u16 lines; // at 0x0
        u8 times;  // at 0x2
    } params[SI_MAX_SAMPLE_RATE + 1];
} SIPollSetting;

static u32 SamplingRate = 0;

static SIPollSetting XYNTSC = {
    // clang-format off
    246,  2, // 0 msec
    14,  19, // 1 msec
    30,   9, // 2 msec
    44,   6, // 3 msec
    52,   5, // 4 msec
    65,   4, // 5 msec
    87,   3, // 6 msec
    87,   3, // 7 msec
    87,   3, // 8 msec
    131,  2, // 9 msec
    131,  2, // 10 msec
    131,  2  // 11 msec
    // clang-format on
};

static SIPollSetting XYPAL = {
    // clang-format off
    296,  2, // 0 msec
    15,  21, // 1 msec
    29,  11, // 2 msec
    45,   7, // 3 msec
    52,   6, // 4 msec
    63,   5, // 5 msec
    78,   4, // 6 msec
    104,  3, // 7 msec
    104,  3, // 8 msec
    104,  3, // 9 msec
    104,  3, // 10 msec
    156,  2  // 11 msec
    // clang-format on
};

void SISetSamplingRate(u32 msec) {
    BOOL enabled;
    SIPollSetting* xy;
    s32 m;

    if (msec > SI_MAX_SAMPLE_RATE) {
        msec = SI_MAX_SAMPLE_RATE;
    }

    enabled = OSDisableInterrupts();

    SamplingRate = msec;

    switch (VIGetTvFormat()) {
    case VI_TV_FMT_NTSC:
    case VI_TV_FMT_MPAL:
    case VI_TV_FMT_EURGB60:
        xy = &XYNTSC;
        break;
    case VI_TV_FMT_PAL:
        xy = &XYPAL;
        break;
    default:
        OSReport("SISetSamplingRate: unknown TV format. Use default.");
        msec = 0;
        xy = &XYNTSC;
        break;
    }

    m = (VI_HW_REGS[VI_VICLK] & VI_VICLK_SPEED) != VI_VICLK_27MHZ ? 2 : 1;
    SISetXY(m * xy->params[msec].lines, xy->params[msec].times);

    OSRestoreInterrupts(enabled);
}

void SIRefreshSamplingRate(void) {
    SISetSamplingRate(SamplingRate);
}
