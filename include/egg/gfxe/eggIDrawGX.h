#ifndef EGG_GFXE_I_DRAWGX_H
#define EGG_GFXE_I_DRAWGX_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/math.h>

namespace EGG {

// Forward declarations
class Screen;

class IDrawGX {
public:
    enum {
        EFlag_ColorUpdate = 1 << 0,
        EFlag_AlphaUpdate = 1 << 1,
        EFlag_Dither = 1 << 2,
    };

public:
    static const Screen& getScreen() {
#line 59
        EGG_ASSERT(spScreen);
        return *spScreen;
    }

    static void beginDrawView(u16 cameraId, const nw4r::math::MTX34& rCameraMtx,
                              const Screen& rScreen);

    static void setDrawSettingGX(bool opa);

    static bool isEnableColorUpdate() {
        return sDrawFlag & EFlag_ColorUpdate;
    }
    static void enableColorUpdate() {
        sDrawFlag |= EFlag_ColorUpdate;
    }
    static void disableColorUpdate() {
        sDrawFlag &= ~EFlag_ColorUpdate;
    }

    static bool isEnableAlphaUpdate() {
        return sDrawFlag & EFlag_AlphaUpdate;
    }
    static void enableAlphaUpdate() {
        sDrawFlag |= EFlag_AlphaUpdate;
    }
    static void disableAlphaUpdate() {
        sDrawFlag &= ~EFlag_AlphaUpdate;
    }

    static bool isEnableDither() {
        return sDrawFlag & EFlag_Dither;
    }
    static void enableDither() {
        sDrawFlag |= EFlag_Dither;
    }
    static void disableDither() {
        sDrawFlag &= ~EFlag_Dither;
    }

    static void setDrawFlag(u32 flag) {
        sDrawFlag = flag;
    }

private:
    typedef void (*SetDrawSettingCallback)(void* pArg, bool opa);

private:
    static const Screen* spScreen;

    static SetDrawSettingCallback spSetDrawSetttingCallback;
    static void* spSetDrawSetttingCallbackArg;

    static u16 sCameraID;
    static nw4r::math::MTX34 sCameraMatrix;

    static u32 sDrawFlag;
};

} // namespace EGG

#endif
