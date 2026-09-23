#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

/******************************************************************************
 *
 * RPGrpView
 *
 ******************************************************************************/

/**
 * @brief Default framebuffer clear color
 */
GXColor RPGrpView::DEFAULT_CLEAR_COLOR = {0, 0, 0, 255};

/**
 * @brief View clipper instance
 */
RPGrpView::Clipper RPGrpView::sClipper;

/**
 * @brief Constructor
 *
 * @param no View ID
 */
RPGrpView::RPGrpView(u8 no)
    : mViewNo(no),
      mDrawScene(0),
      mFlags(EFlag_9 | EFlag_SysDraw | EFlag_SysCalc),
      mProjType(EProjType_Max),
      mClearColor(DEFAULT_CLEAR_COLOR),
      mpScreen(NULL),
      unk14(0),
      mpScreenEffect(NULL) {}

/**
 * @brief Initializes this view's state
 */
void RPGrpView::Configure() {}

/**
 * @brief Attaches a screen effect to this view
 */
void RPGrpView::CreateScreenEffect() {
    mpScreenEffect = new ScreenEffect();
}

/**
 * @brief Updates this view's state
 */
void RPGrpView::Calc() {
    RPGrpView::PrepareDraw();
}

/**
 * @brief Prepares this view for a new frame
 */
void RPGrpView::PrepareDraw() {
    if (!IsSysCalc()) {
        return;
    }

    if (mProjType == EProjType_Persp) {
        sClipper.Calc(GetEnableScreen());
    }
}

/**
 * @brief Clears the framebuffer of the attached screen
 */
void RPGrpView::ClearBuffer() {
    GXColor clearColor = EGG::StateGX::getEfbClearColor();
    u8 flags = 0;

    if (mFlags & EFlag_FillBufferColor) {
        clearColor.r = GetClearColor().r;
        clearColor.g = GetClearColor().g;
        clearColor.b = GetClearColor().b;

        flags |= EGG::Screen::FILLBUFFER_COLOR;
        EGG::StateGX::s_flag |= EGG::StateGX::cFlag_0;
    } else {
        EGG::StateGX::s_flag &= ~EGG::StateGX::cFlag_0;
    }

    if (mFlags & EFlag_FillBufferAlpha) {
        clearColor.a = GetClearColor().a;

        flags |= EGG::Screen::FILLBUFFER_ALPHA;
        EGG::StateGX::s_flag |= EGG::StateGX::cFlag_1;
    } else {
        EGG::StateGX::s_flag &= ~EGG::StateGX::cFlag_1;
    }

    if (mFlags & EFlag_FillBufferTexture) {
        flags |= EGG::Screen::FILLBUFFER_TEXTURE;
    }

    if (flags != 0) {
        GetEnableScreen()->FillBufferGX(flags, GetClearColor());
        EGG::StateGX::setEfbClearColor(clearColor);
    }

    if (mpScreenEffect != NULL) {
        mpScreenEffect->Draw(GetEnableScreen());
    }
}

/**
 * @brief Attaches a new screen to this view
 *
 * @param pScreen Screen rendering surface
 * @return Previously attached screen
 */
RPGrpScreen* RPGrpView::AttachScreen(RPGrpScreen* pScreen) {
    RPGrpScreen* pOldScreen = mpScreen;
    mpScreen = pScreen;
    return pOldScreen;
}

/**
 * @brief Configures the GX projection matrix
 */
void RPGrpView::SetProjectionGX() const {
    EGG::DrawGX::SetCameraMtx(GetEnableCamera()->GetSavedCameraMatrix());

    EGG::Screen clone(*GetEnableScreen());

    switch (mProjType) {
    case EProjType_Persp: {
        clone.SetProjectionType(EGG::Screen::PROJ_PERSP);
        break;
    }

    case EProjType_Ortho: {
        if (GetType() == EType_Render2D) {
            clone.SetNearZ(-10000.0f);
            clone.SetFarZ(10000.0f);
        }

        clone.SetProjectionType(EGG::Screen::PROJ_ORTHO);
        break;
    }

    default: {
        break;
    }
    }

    clone.SetProjectionGX();
}

/**
 * @brief Converts a position from world-space to screen-space
 *
 * @param[out] pScreenPos Position in screen-space
 * @param rWorldPos Position in world-space
 */
void RPGrpView::GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                                 const nw4r::math::VEC3& rWorldPos) const {
    if (GetCamera() != NULL) {
        GetCamera()->GetWorldToScreen(pScreenPos, rWorldPos, GetEnableScreen());
    } else {
        GetEnableScreen()->GetViewToScreen(pScreenPos, rWorldPos);
    }
}

/**
 * @brief Converts a position from screen-space to world-space
 *
 * @param[out] pWorldPos Position in world-space
 * @param rScreenPos Position in screen-space
 */
void RPGrpView::GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                                 const nw4r::math::VEC2& rScreenPos) const {
    if (GetCamera() != NULL) {
        GetCamera()->GetScreenToWorld(pWorldPos, rScreenPos, GetEnableScreen());
    } else {
        GetEnableScreen()->GetScreenToView(pWorldPos, rScreenPos);
    }
}

/**
 * @brief Gets the screen used by this view.
 * @details If no screen is attached, this function returns the root screen.
 */
RPGrpScreen* RPGrpView::GetEnableScreen() const {
    if (GetScreen() != NULL) {
        return GetScreen();
    }

    return &RPGrpScreen::GetRootScreen();
}

/**
 * @brief Gets the camera used by this view.
 * @details If no camera is attached, this function returns the default
 * camera.
 */
RPGrpCamera* RPGrpView::GetEnableCamera() const {
    if (GetCamera() != NULL) {
        return GetCamera();
    }

    return &RPGrpCamera::GetDefaultCamera();
}

/**
 * @brief Tests whether the specified bounding sphere falls within the
 * view frustum
 *
 * @param pScreen Screen rendering surface
 * @param rPos Bounding sphere position
 * @param radius Bounding sphere radius
 */
bool RPGrpView::Clip(const nw4r::math::VEC3& rPos, f32 radius) const {
    nw4r::math::VEC3 local;
    nw4r::math::VEC3TransformCoord(
        &local, &GetEnableCamera()->GetSavedCameraMatrix(), &rPos);

    return sClipper.Clip(GetEnableScreen(), local, radius);
}

/******************************************************************************
 *
 * Clipper
 *
 ******************************************************************************/

/**
 * @brief Re-calculates this clipper's clipping planes
 *
 * @param pScreen Screen rendering surface
 */
void RPGrpView::Clipper::Calc(const RPGrpScreen* pScreen) {
    f32 ny = pScreen->GetNearZ() * pScreen->GetTanFovy();
    f32 nx = ny * pScreen->GetWidth() / pScreen->GetHeight();

    nw4r::math::VEC3 bl(-nx, -ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 tl(-nx, ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 tr(nx, ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 br(nx, -ny, -pScreen->GetNearZ());

    nw4r::math::VEC3Cross(&l, &tl, &bl);
    nw4r::math::VEC3Cross(&t, &tr, &tl);
    nw4r::math::VEC3Cross(&r, &br, &tr);
    nw4r::math::VEC3Cross(&b, &bl, &br);

    nw4r::math::VEC3Normalize(&l, &l);
    nw4r::math::VEC3Normalize(&t, &t);
    nw4r::math::VEC3Normalize(&r, &r);
    nw4r::math::VEC3Normalize(&b, &b);
}

/**
 * @brief Tests whether the specified bounding sphere falls within the
 * view frustum
 *
 * @param pScreen Screen rendering surface
 * @param rPos Bounding sphere position
 * @param radius Bounding sphere radius
 */
bool RPGrpView::Clipper::Clip(const RPGrpScreen* pScreen,
                              const nw4r::math::VEC3& rPos, f32 radius) {

    if (-rPos.z < pScreen->GetNearZ() - radius ||
        -rPos.z > pScreen->GetFarZ() + radius) {

        return true;
    }

    if (rPos.x * l.x + rPos.y * l.y + rPos.z * l.z > radius) {
        return true;
    }

    if (rPos.x * t.x + rPos.y * t.y + rPos.z * t.z > radius) {
        return true;
    }

    if (rPos.x * r.x + rPos.y * r.y + rPos.z * r.z > radius) {
        return true;
    }

    if (rPos.x * b.x + rPos.y * b.y + rPos.z * b.z > radius) {
        return true;
    }

    return false;
}

/******************************************************************************
 *
 * ScreenEffect
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
RPGrpView::ScreenEffect::ScreenEffect() {
    mColorMultiply = EGG::DrawGX::WHITE;
    mColorAdd = EGG::DrawGX::BLACK;
    mColorBlend = (GXColor){0, 0, 0, 0};

    mBlurOffset = 1.2f;
    mBlurAlpha = 0;
}

/**
 * @brief Draws this effect to the specified screen
 *
 * @param pScreen Screen rendering surface
 */
void RPGrpView::ScreenEffect::Draw(const RPGrpScreen* pScreen) {
    bool needBlur = mBlurAlpha > 0;

    bool needMul = mColorMultiply.r != 255 || mColorMultiply.g != 255 ||
                   mColorMultiply.b != 255;

    bool needAdd = (mColorAdd.r != 0 || mColorAdd.g != 0 || mColorAdd.b != 0) &&
                   mColorAdd.a > 0;

    bool needNormal = mColorBlend.a > 0;

    if (needBlur || needMul || needAdd || needNormal) {
        EGG::StateGX::GXSetColorUpdate_(true);
        EGG::StateGX::GXSetAlphaUpdate_(false);

        GXInvalidateTexAll();

        EGG::Screen clone(*pScreen);
        clone.SetNearZ(0.0f);
        clone.SetFarZ(1.0f);
        clone.SetCanvasMode(EGG::Screen::CANVAS_LU);
        clone.SetProjectionType(EGG::Screen::PROJ_ORTHO);
        clone.SetProjectionGX();

        const EGG::Screen::DataEfb& rEfb = pScreen->GetDataEfb();
        u16 x = static_cast<u16>(rEfb.vp.x);
        u16 y = static_cast<u16>(rEfb.vp.y);
        // Downscaled for mipmapping
        u16 halfWidth = static_cast<u16>(rEfb.vp.width / 2);
        u16 halfHeight = static_cast<u16>(rEfb.vp.height / 2);

        if (needBlur) {
            // Screenshot used as a base for blurring
            EGG::TextureBuffer* pScreenCapture = EGG::TextureBuffer::alloc( //
                halfWidth,                                                  //
                halfHeight,                                                 //
                GX_TF_RGBA8);

            // Backup of original pixels that will be clobbered by blurring
            EGG::TextureBuffer* pScreenBackup = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                             //
                halfHeight / 2,                                            //
                GX_TF_RGBA8);

            // Blur posteffect result in texture form
            EGG::TextureBuffer* pEffectCapture = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                              //
                halfHeight / 2,                                             //
                GX_TF_RGBA8);

            // Save the appearance of the screen space
            // that will be overwritten by the blur posteffect.
            pScreenBackup->capture(x, y);

            // Take a screenshot to use as a base for blurring
            pScreenCapture->setVFilterBlur();
            pScreenCapture->capture(x, y, true);

            // TODO(kiwi) PostEffectBlurSimple needs work
            EGG::PostEffectBlurSimple eff;
            eff.configure();
            eff.setBlendMode(EGG::PostEffectBase::cBlendMode_None);
            eff.setCapTexture(pScreenCapture);

            // Draw the result of the blur posteffect (downscaled)
            pScreenCapture->setLoadMap(GX_TEXMAP0);
            eff.draw(pScreen->GetWidth() / 4.0f, pScreen->GetHeight() / 4.0f);

            // Capture the posteffect result as a new texture
            pEffectCapture->setVFilterBlur();
            pEffectCapture->capture(x, y);

            nw4r::math::MTX34 proj;
            EGG::DrawGX::BeginDrawScreen(true, true, true);

            // Restore the pixels overwritten by the posteffect work
            PSMTXScale(                      //
                proj,                        //
                pScreen->GetWidth() / 4.0f,  //
                pScreen->GetHeight() / 4.0f, //
                1.0f);
            pScreenBackup->load(GX_TEXMAP0);
            EGG::DrawGX::DrawScreenTexture(proj, EGG::DrawGX::WHITE);

            // Upscale the blur effect to the entire screen
            PSMTXScale(proj, pScreen->GetWidth(), pScreen->GetHeight(), 1.0f);
            pEffectCapture->load(GX_TEXMAP0);
            GXColor color = (GXColor){255, 255, 255, mBlurAlpha};
            EGG::DrawGX::DrawScreenTexture(proj, color);

            pScreenBackup->free();
            pScreenCapture->free();
            pEffectCapture->free();
        }

        if (needMul || needAdd || needNormal) {
            EGG::DrawGX::BeginDrawScreen(true, false, false);

            nw4r::math::MTX34 proj;
            PSMTXScale(proj, pScreen->GetWidth(), pScreen->GetHeight(), 1.0f);

            if (needMul) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_MUL);
                EGG::DrawGX::DrawScreen(proj, mColorMultiply);
            }

            if (needAdd) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_ADD_ALPHA);
                EGG::DrawGX::DrawScreen(proj, mColorAdd);
            }

            if (needNormal) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_NORMAL);
                EGG::DrawGX::DrawScreen(proj, mColorBlend);
            }
        }
    }
}
