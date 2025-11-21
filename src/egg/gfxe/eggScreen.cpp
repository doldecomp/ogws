#include <egg/gfxe.h>
#include <egg/prim.h>

#include <revolution/SC.h>

namespace EGG {

u16 Screen::sTVModeWidths[TV_MODE_MAX] = {
    600, // TV_MODE_STD
    800  // TV_MODE_WIDE
};
u16 Screen::sTVModeHeights[TV_MODE_MAX] = {
    480, // TV_MODE_STD
    480  // TV_MODE_WIDE
};

Screen::TVMode Screen::sTVMode = TV_MODE_STD;
Screen::TVModeRatio Screen::sTVModeRatios[Screen::TV_MODE_MAX];

Screen* Screen::spRoot = NULL;

Screen::ChangeTVModeFunc Screen::sChangeTVModeFunc = NULL;
void* Screen::spChangeTVModeFuncInfo = NULL;

nw4r::math::VEC2 Screen::sCanvasScale(1.0f, 1.0f);
nw4r::math::VEC2 Screen::sCanvasOffset(0.0f, 0.0f);

void Screen::Initialize(const u16* maxX, const u16* maxY, Screen* pUserRoot) {
#line 47
    EGG_ASSERT(maxX != NULL);
    EGG_ASSERT(maxY != NULL);

    sTVModeWidths[TV_MODE_STD] = maxX[TV_MODE_STD];
    sTVModeHeights[TV_MODE_STD] = maxY[TV_MODE_STD];

    sTVModeWidths[TV_MODE_WIDE] = maxX[TV_MODE_WIDE];
    sTVModeHeights[TV_MODE_WIDE] = maxY[TV_MODE_WIDE];

    static Screen root;
    root.SetProjectionType(PROJTYPE_ORTHO);
    root.SetCanvasMode(CANVASMODE_LU);
    root.SetNearZ(0.0f);
    root.SetFarZ(1.0f);

    pUserRoot = pUserRoot == NULL ? &root : pUserRoot;

    spRoot = pUserRoot;
    pUserRoot->SetParent(NULL);

    CalcRatio();
    SetTVMode(sTVMode);
}

Screen::Screen()
    // @bug Far Z typo of 100,000
    : Frustum(PROJTYPE_PERSP,
              nw4r::math::VEC2(sTVModeWidths[sTVMode], sTVModeHeights[sTVMode]),
              10.0f, 10000.0f, CANVASMODE_LU) {

    mPosition.x = 0.0f;
    mPosition.y = 0.0f;

    SetParent(NULL);
    Configure();
}

Screen::Screen(f32 x, f32 y, f32 width, f32 height, const Screen* pParent,
               CanvasMode canvasMode)
    : Frustum(PROJTYPE_PERSP, nw4r::math::VEC2(width, height), 10.0f, 100000.0f,
              canvasMode) {

    mPosition.x = x;
    mPosition.y = y;

    SetParent(pParent);
    Configure();
}

Screen::Screen(const Screen& rOther)
    : Frustum(rOther), mPosition(rOther.mPosition), mDataEfb(rOther.mDataEfb) {

    SetParent(rOther.mParent);
    Configure();
}

void Screen::Configure() {}

void Screen::SetProjectionGX() const {
    if (!(mFlags & FLAG_PROJ_ABSOLUTE)) {
        f32 sx, sy, ox, oy;
        GetGlobalScaleOffset(&sx, &sy, &ox, &oy);

        SetGlobalScaleOffset(sCanvasScale.x, sCanvasScale.y, sCanvasOffset.x,
                             sCanvasOffset.y);

        Frustum::SetProjectionGX();

        SetGlobalScaleOffset(sx, sy, ox, oy);
    } else {
        Frustum::SetProjectionGX();
    }

    SetViewGX();
}

void Screen::CopyToG3D(nw4r::g3d::Camera camera) const {
    if (!(mFlags & FLAG_PROJ_ABSOLUTE)) {
        f32 sx, sy, ox, oy;
        GetGlobalScaleOffset(&sx, &sy, &ox, &oy);

        SetGlobalScaleOffset(sCanvasScale.x, sCanvasScale.y, sCanvasOffset.x,
                             sCanvasOffset.y);

        Frustum::CopyToG3D(camera);

        SetGlobalScaleOffset(sx, sy, ox, oy);
    } else {
        Frustum::CopyToG3D(camera);
    }

    SetViewG3D(camera);
}

void Screen::SetViewGX() const {
    const DataEfb& rEfb = GetDataEfb();

    StateGX::GXSetViewport_(rEfb.vp.x, rEfb.vp.y, rEfb.vp.width, rEfb.vp.height,
                            rEfb.vp.near, rEfb.vp.far);

    StateGX::GXSetScissor_(rEfb.vp.x, rEfb.vp.y, rEfb.vp.width, rEfb.vp.height);

    StateGX::GXSetScissorBoxOffset_(rEfb.ox, rEfb.oy);
}

void Screen::SetViewG3D(nw4r::g3d::Camera camera) const {
    const DataEfb& rEfb = GetDataEfb();

    f32 width, height;
    height = rEfb.vp.height;
    width = rEfb.vp.width;

    f32 x, y;
    y = rEfb.vp.y;
    x = rEfb.vp.x;

    f32 near, far;
    far = rEfb.vp.far;
    near = rEfb.vp.near;

    camera.SetViewport(x, y, width, height);
    camera.SetViewportZRange(near, far);

    camera.SetScissor(rEfb.vp.x, rEfb.vp.y, rEfb.vp.width, rEfb.vp.height);
    camera.SetScissorBoxOffset(rEfb.ox, rEfb.oy);
}

void Screen::CopyFromAnother(const Screen& rOther) {
    Frustum::CopyFromAnother(rOther);

    SetParent(rOther.mParent);
    mPosition = rOther.mPosition;
    mDataEfb = rOther.mDataEfb;
}

void Screen::GetPosSizeInEfb() const {
    TVMode tvMode = !(mFlags & FLAG_FORCE_STD_ASPECT) ? sTVMode : TV_MODE_STD;
    const TVModeRatio& rRatio = sTVModeRatios[tvMode];

    f32* pX = &mDataEfb.vp.x;
    f32* pY = &mDataEfb.vp.y;

    GetGlobalPos(pX, pY);

    *pX = sCanvasScale.x * *pX;
    *pY = sCanvasScale.y * *pY;

    *pX *= rRatio.widthRatio;
    *pY *= rRatio.heightRatio;

    mDataEfb.oy = 0;
    mDataEfb.ox = 0;

    f32 x = *pX;
    if (x < 0.0f) {
        *pX = 0.0f;

        s32 lx = static_cast<s32>(-x);
        mDataEfb.ox = lx - (lx & 1);
    }

    f32 y = *pY;
    if (y < 0.0f) {
        *pY = 0.0f;

        s32 ly = static_cast<s32>(-y);
        mDataEfb.oy = ly - (ly & 1);
    }

    if (mFlags & FLAG_ALIGN_EFB_POS) {
        *pX -= static_cast<s32>(*pX) & 1;
        *pY -= static_cast<s32>(*pY) & 1;
    }

    *pX = static_cast<s32>(*pX);
    *pY = static_cast<s32>(*pY);

    mDataEfb.vp.width = mSize.x;
    mDataEfb.vp.height = mSize.y;

    if (!(mFlags & FLAG_VPSIZE_ABSOLUTE)) {
        mDataEfb.vp.width = mSize.x * rRatio.widthRatio;
        mDataEfb.vp.height = mSize.y * rRatio.heightRatio;
    }

    if (mFlags & FLAG_ALIGN_EFB_SIZE) {
        mDataEfb.vp.width -= static_cast<s32>(mDataEfb.vp.width) & 3;
        mDataEfb.vp.height -= static_cast<s32>(mDataEfb.vp.height) & 3;
    }

    mDataEfb.vp.width = mDataEfb.vp.width >= 0.0f ? mDataEfb.vp.width : 0.0f;
    mDataEfb.vp.height = mDataEfb.vp.height >= 0.0f ? mDataEfb.vp.height : 0.0f;

    mDataEfb.vp.width = static_cast<s32>(mDataEfb.vp.width);
    mDataEfb.vp.height = static_cast<s32>(mDataEfb.vp.height);
}

const Screen::DataEfb& Screen::GetDataEfb() const {
    if (IsChangeEfb()) {
        GetPosSizeInEfb();

        mDataEfb.vp.near = 0.0f;
        mDataEfb.vp.far = 1.0f;

        mFlags &= ~FLAG_DIRTY;
    }

    return mDataEfb;
}

bool Screen::IsChangeEfb() const {
    if (mFlags & FLAG_DIRTY) {
        return true;
    }

    if (mParent != NULL) {
        return mParent->IsChangeEfb();
    }

    return false;
}

void Screen::CalcMatrixForDrawQuad(nw4r::math::MTX34* pMtx, f32 x, f32 y,
                                   f32 width, f32 height) const {

    PSMTXScale(*pMtx, width, height, 1.0f);

    pMtx->_03 = x;
    pMtx->_23 = 0.0f;

    if (mCanvasMode == CANVASMODE_CC) {
        pMtx->_13 = y - height;
    } else {
        pMtx->_13 = y;
    }
}

void Screen::FillBufferGX(u32 flags, GXColor color, u32 arg2) const {
#pragma unused(arg2)

    if (flags == 0) {
        return;
    }

    Screen clone(*this);
    clone.SetCanvasMode(CANVASMODE_LU);
    clone.SetNearZ(0.0f);
    clone.SetFarZ(1.0f);
    clone.SetProjectionType(PROJTYPE_ORTHO);
    clone.SetProjectionGX();

    nw4r::math::MTX34 drawMtx;
    clone.CalcMatrixForDrawQuad(&drawMtx, 0.0f, 0.0f, mSize.x * mScale.x,
                                mSize.y * mScale.y);

    // clang-format off
    DrawGX::ClearEfb(
        drawMtx,
        (flags & FILLBUFFER_COLOR)   ? true : false,
        (flags & FILLBUFFER_ALPHA)   ? true : false,
        (flags & FILLBUFFER_TEXTURE) ? true : false,
        color,
        true);
    // clang-format on
}

void Screen::GetGlobalPos(f32* pX, f32* pY) const {
    const Screen* parent = GetParent();

    if (parent != NULL) {
        f32 gx, gy;
        parent->GetGlobalPos(&gx, &gy);

        f32 lx, ly;
        parent->ConvertToCanvasLU(mPosition.x, mPosition.y, &lx, &ly);

        *pX = lx + gx;
        *pY = ly + gy;
    } else {
#line 485
        EGG_ASSERT(spRoot == NULL || ( spRoot != NULL && spRoot == this ));

        *pX = mPosition.x;
        *pY = mPosition.y;
    }
}

void Screen::SetTVMode(TVMode tvMode) {
    sTVMode = tvMode;

    if (spRoot != NULL) {
        spRoot->SetSizeX(GetSizeXMax());
        spRoot->SetSizeY(GetSizeYMax());
    }

    if (sChangeTVModeFunc != NULL) {
        sChangeTVModeFunc(spChangeTVModeFuncInfo);
    }
}

void Screen::SetTVModeDefault() {
    SetTVMode(SCGetAspectRatio() == SC_ASPECT_STD ? TV_MODE_STD : TV_MODE_WIDE);
}

void Screen::CalcRatio() {
#line 530
    EGG_ASSERT(GetSizeXMax() > 0);
    EGG_ASSERT(GetSizeYMax() > 0);

    sTVModeRatios[TV_MODE_STD].widthRatio =
        static_cast<f32>(StateGX::getEfbWidth()) /
        static_cast<f32>(sTVModeWidths[TV_MODE_STD]);

    sTVModeRatios[TV_MODE_STD].heightRatio =
        static_cast<f32>(StateGX::getEfbHeight()) /
        static_cast<f32>(sTVModeHeights[TV_MODE_STD]);

    sTVModeRatios[TV_MODE_WIDE].widthRatio =
        static_cast<f32>(StateGX::getEfbWidth()) /
        static_cast<f32>(sTVModeWidths[TV_MODE_WIDE]);

    sTVModeRatios[TV_MODE_WIDE].heightRatio =
        static_cast<f32>(StateGX::getEfbHeight()) /
        static_cast<f32>(sTVModeHeights[TV_MODE_WIDE]);
}

} // namespace EGG
