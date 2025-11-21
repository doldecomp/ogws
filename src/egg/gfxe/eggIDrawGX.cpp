#include <egg/gfxe.h>

namespace EGG {

const Screen* IDrawGX::spScreen = NULL;

IDrawGX::SetDrawSettingCallback IDrawGX::spSetDrawSetttingCallback = NULL;
void* IDrawGX::spSetDrawSetttingCallbackArg = NULL;

u16 IDrawGX::sCameraID = 0;
nw4r::math::MTX34 IDrawGX::sCameraMatrix;

u32 IDrawGX::sDrawFlag = 0;

void IDrawGX::beginDrawView(u16 cameraId, const nw4r::math::MTX34& rCameraMtx,
                            const Screen& rScreen) {

    spScreen = &rScreen;
    sCameraID = cameraId;
    nw4r::math::MTX34Copy(&sCameraMatrix, &rCameraMtx);
}

void IDrawGX::setDrawSettingGX(bool opa) {
    StateGX::GXSetColorUpdate_(isEnableColorUpdate());
    StateGX::GXSetAlphaUpdate_(isEnableAlphaUpdate());
    StateGX::GXSetDither_(isEnableDither());

    if (spSetDrawSetttingCallback != NULL) {
        spSetDrawSetttingCallback(spSetDrawSetttingCallbackArg, opa);
    }

    getScreen().SetProjectionGX();
}

} // namespace EGG
