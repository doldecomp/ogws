#ifndef RVL_SDK_VI_H
#define RVL_SDK_VI_H
#include <types.h>

#include <revolution/GX.h>
#ifdef __cplusplus
extern "C" {
#endif

// Merge format/scanmode to one value for TV mode (see GXRenderModeObj)
#define VI_TVMODE(format, scanMode) (((format) << 2) + (scanMode))

// Get TV format from TV mode
#define VI_TVMODE_FORMAT(mode) ((mode) >> 2)
// Get TV scan mode from TV mode
#define VI_TVMODE_SCANMODE(mode) ((mode) & 0b00000011)

typedef enum {
    VI_TVFORMAT_NTSC,
    VI_TVFORMAT_PAL,
    VI_TVFORMAT_MPAL,
    VI_TVFORMAT_DEBUG,
    VI_TVFORMAT_DEBUG_PAL,
    VI_TVFORMAT_EURGB60
} VITVFormat;

typedef enum VIScanMode {
    VI_SCANMODE_INT,
    VI_SCANMODE_DS,
    VI_SCANMODE_PROG
} VIScanMode;

typedef enum VIXFBMode {
    VI_XFBMODE_SF,
    VI_XFBMODE_DF,
} VIXFBMode;

typedef enum VITVMode {
    VI_TVMODE_NTSC_INT = VI_TVMODE(VI_TVFORMAT_NTSC, VI_SCANMODE_INT),
    VI_TVMODE_NTSC_DS = VI_TVMODE(VI_TVFORMAT_NTSC, VI_SCANMODE_DS),
    VI_TVMODE_NTSC_PROG = VI_TVMODE(VI_TVFORMAT_NTSC, VI_SCANMODE_PROG),

    VI_TVMODE_PAL_INT = VI_TVMODE(VI_TVFORMAT_PAL, VI_SCANMODE_INT),
    VI_TVMODE_PAL_DS = VI_TVMODE(VI_TVFORMAT_PAL, VI_SCANMODE_DS),

    VI_TVMODE_EURGB60_INT = VI_TVMODE(VI_TVFORMAT_EURGB60, VI_SCANMODE_INT),
    VI_TVMODE_EURGB60_DS = VI_TVMODE(VI_TVFORMAT_EURGB60, VI_SCANMODE_DS),
    VI_TVMODE_EURGB60_PROG = VI_TVMODE(VI_TVFORMAT_EURGB60, VI_SCANMODE_PROG),

    VI_TVMODE_MPAL_INT = VI_TVMODE(VI_TVFORMAT_MPAL, VI_SCANMODE_INT),
    VI_TVMODE_MPAL_DS = VI_TVMODE(VI_TVFORMAT_MPAL, VI_SCANMODE_DS),
    VI_TVMODE_MPAL_PROG = VI_TVMODE(VI_TVFORMAT_MPAL, VI_SCANMODE_PROG),

    VI_TVMODE_DEBUG_INT = VI_TVMODE(VI_TVFORMAT_DEBUG, VI_SCANMODE_INT),

    VI_TVMODE_DEBUG_PAL_INT = VI_TVMODE(VI_TVFORMAT_DEBUG_PAL, VI_SCANMODE_INT),
    VI_TVMODE_DEBUG_PAL_DS = VI_TVMODE(VI_TVFORMAT_DEBUG_PAL, VI_SCANMODE_DS),
} VITVMode;

typedef void (*VIRetraceCallback)(u32 retraceCount);
typedef void (*VIPositionCallback)(s16 displayX, s16 displayY);

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback);
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback);

void VIInit(void);
void VIWaitForRetrace(void);

void VIConfigure(const GXRenderModeObj* rmo);
void VIConfigurePan(u16 x, u16 y, u16 w, u16 h);
void VIFlush(void);

void VISetNextFrameBuffer(void* fb);
void* VIGetCurrentFrameBuffer(void);

void VISetBlack(BOOL black);
s32 VIGetRetraceCount(void);

VITVFormat VIGetTvFormat(void);
VIScanMode VIGetScanMode(void);
u32 VIGetDTVStatus(void);

#ifdef __cplusplus
}
#endif
#endif
