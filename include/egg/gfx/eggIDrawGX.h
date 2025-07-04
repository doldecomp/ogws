#ifndef EGG_GFX_I_DRAWGX_H
#define EGG_GFX_I_DRAWGX_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/math.h>

namespace EGG {

// Forward declarations
class Screen;

class IDrawGX {
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
        return sDrawFlag & DRAWFLAG_COLORUPDATE;
    }
    static void enableColorUpdate() {
        sDrawFlag |= DRAWFLAG_COLORUPDATE;
    }
    static void disableColorUpdate() {
        sDrawFlag &= ~DRAWFLAG_COLORUPDATE;
    }

    static bool isEnableAlphaUpdate() {
        return sDrawFlag & DRAWFLAG_ALPHAUPDATE;
    }
    static void enableAlphaUpdate() {
        sDrawFlag |= DRAWFLAG_ALPHAUPDATE;
    }
    static void disableAlphaUpdate() {
        sDrawFlag &= ~DRAWFLAG_ALPHAUPDATE;
    }

    static bool isEnableDither() {
        return sDrawFlag & DRAWFLAG_DITHER;
    }
    static void enableDither() {
        sDrawFlag |= DRAWFLAG_DITHER;
    }
    static void disableDither() {
        sDrawFlag &= ~DRAWFLAG_DITHER;
    }

private:
    typedef void (*SetDrawSettingCallback)(void* pArg, bool opa);

    enum DrawFlag {
        DRAWFLAG_COLORUPDATE = 1 << 0,
        DRAWFLAG_ALPHAUPDATE = 1 << 1,
        DRAWFLAG_DITHER = 1 << 2,
    };

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
