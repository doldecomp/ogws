#include <egg/gfx.h>
#include <egg/prim.h>

namespace EGG {

nw4r::math::VEC2 Frustum::sGlobalScale(1.0f, 1.0f);
nw4r::math::VEC2 Frustum::sGlobalOffset(0.0f, 0.0f);

Frustum::Frustum(ProjectionType projType, const nw4r::math::VEC2& rSize,
                 f32 nearZ, f32 farZ, CanvasMode canvasMode)
    : mProjType(projType),
      mCanvasMode(canvasMode),
      mSize(rSize),
      mFovY(45.0f),
      mTanFovY(0.41421357f), // sin(fovy/2) / cos(fovy/2)
      mNearZ(nearZ),
      mFarZ(farZ),
      mOffset(0.0f, 0.0f),
      mScale(1.0f, 1.0f, 1.0f),
      mFlags(FLAG_DIRTY) {}

Frustum::Frustum(const Frustum& rOther)
    : mProjType(rOther.mProjType),
      mCanvasMode(rOther.mCanvasMode),
      mSize(rOther.mSize),
      mFovY(rOther.mFovY),
      mTanFovY(rOther.mTanFovY),
      mNearZ(rOther.mNearZ),
      mFarZ(rOther.mFarZ),
      mOffset(rOther.mOffset),
      mScale(rOther.mScale),
      mFlags(rOther.mFlags) {}

void Frustum::SetProjectionGX() const {
    if (mProjType == PROJTYPE_ORTHO) {
        SetProjectionOrthographicGX_();
    } else {
        SetProjectionPerspectiveGX_();
    }
}

void Frustum::CopyToG3D(nw4r::g3d::Camera camera) const {
    if (mProjType == PROJTYPE_ORTHO) {
        CopyToG3D_Orthographic_(camera);
    } else {
        CopyToG3D_Perspective_(camera);
    }
}

void Frustum::SetProjectionPerspectiveGX_() const {
    f32 proj[GX_PROJECTION_SZ];
    GetPerspectiveParam_(proj);
    StateGX::GXSetProjectionv_(proj);
}

void Frustum::SetProjectionOrthographicGX_() const {
    nw4r::math::MTX44 projMtx;
    GetOrthographicParam_(&projMtx);
    StateGX::GXSetProjection_(projMtx, GX_ORTHOGRAPHIC);
}

void Frustum::CopyToG3D_Perspective_(nw4r::g3d::Camera camera) const {
    camera.SetPerspective(mFovY, GetAspect(), mNearZ, mFarZ);

    nw4r::math::MTX44 projMtx;
    CalcMtxPerspective_(&projMtx);
    camera.SetProjectionMtxDirectly(&projMtx);
}

void Frustum::CopyToG3D_Orthographic_(nw4r::g3d::Camera camera) const {
    f32 t, b, l, r;
    GetOrthographicParam_(&t, &b, &l, &r);

    camera.SetOrtho(t, b, l, r, mNearZ, mFarZ);
}

void Frustum::CalcMtxPerspective_(nw4r::math::MTX44* pMtx) const {
    f32 proj[GX_PROJECTION_SZ];
    GetPerspectiveParam_(proj);

    pMtx->_03 = 0.0f;
    pMtx->_01 = 0.0f;
    pMtx->_00 = proj[1];
    pMtx->_02 = proj[2];

    pMtx->_13 = 0.0f;
    pMtx->_10 = 0.0f;
    pMtx->_11 = proj[3];
    pMtx->_12 = proj[4];

    pMtx->_21 = 0.0f;
    pMtx->_20 = 0.0f;
    pMtx->_22 = proj[5];
    pMtx->_23 = proj[6];

    pMtx->_33 = 0.0f;
    pMtx->_31 = 0.0f;
    pMtx->_30 = 0.0f;
    pMtx->_32 = -1.0f;
}

void Frustum::GetOrthographicParam_(nw4r::math::MTX44* pMtx) const {
#line 267
    EGG_ASSERT(pMtx);

    f32 t, b, l, r;
    GetOrthographicParam_(&t, &b, &l, &r);

    C_MTXOrtho(*pMtx, t, b, l, r, mNearZ, mFarZ);
}

void Frustum::LoadScnCamera(const nw4r::g3d::ResAnmScn anmScn, u8 refNumber,
                            f32 frame, u32 flags) {

    if (!anmScn.IsValid()) {
        return;
    }

    const nw4r::g3d::ResAnmCamera anmCamera =
        anmScn.GetResAnmCameraByRefNumber(refNumber);

#line 296
    EGG_ASSERT_MSG(anmCamera.IsValid(), "Illegal camera number.");

    nw4r::g3d::CameraAnmResult result;
    anmCamera.GetAnmResult(&result, frame);

    switch (result.projType) {
    case GX_PERSPECTIVE: {
        SetProjectionType(PROJTYPE_PERSP);

        if (!(flags & LOAD_SCN_KEEP_FOVY)) {
            SetFovY(result.perspFovy);
        }

        if (!(flags & LOAD_SCN_KEEP_CANVAS)) {
            SetSizeX(mSize.y * result.aspect);
            SetScale(nw4r::math::VEC3(1.0f, 1.0f, 1.0f));
        }
        break;
    }

    case GX_ORTHOGRAPHIC: {
        SetProjectionType(PROJTYPE_ORTHO);

        if (!(flags & LOAD_SCN_KEEP_CANVAS)) {
            SetCanvasMode(CANVASMODE_CC);

            SetSizeY(result.perspFovy);
            SetSizeX(mSize.y * result.aspect);

            SetScale(nw4r::math::VEC3(1.0f, 1.0f, 1.0f));
            SetOffset(nw4r::math::VEC2(0.0f, 0.0f));
        }
        break;
    }

    default: {
#line 331
        EGG_ASSERT_MSG(false, "Unknown GXProjectionType");
        break;
    }
    }

    if (!(flags & LOAD_SCN_KEEP_Z)) {
        SetNearZ(result.near);
        SetFarZ(result.far);
    }
}

void Frustum::GetPerspectiveParam_(f32* p) const {
#line 352
    EGG_ASSERT(p != NULL);

    f32 cot = 1.0f / mTanFovY;

    p[0] = 0.0f;
    p[1] = cot / GetAspect() / mScale.x;
    p[2] = mOffset.x / (0.5f * mSize.x);
    p[3] = cot / mScale.y;
    p[4] = mOffset.y / (0.5f * mSize.y);

    // Multiply by -N early
    f32 invrange = -mNearZ / (mFarZ - mNearZ);

    p[5] = invrange;
    p[6] = mFarZ * invrange;

    GXUtility::setScaleOffsetPerspective(p, sGlobalScale.x, sGlobalScale.y,
                                         sGlobalOffset.x / (0.5f * mSize.x),
                                         sGlobalOffset.y / (0.5f * mSize.y));
}

void Frustum::GetOrthographicParam_(f32* pT, f32* pB, f32* pL, f32* pR) const {
#line 387
    EGG_ASSERT(pT);
    EGG_ASSERT(pB);
    EGG_ASSERT(pL);
    EGG_ASSERT(pR);

    if (mCanvasMode == CANVASMODE_CC) {
        nw4r::math::VEC2 scale(mScale.x * sGlobalScale.x,
                               mScale.y * sGlobalScale.y);

        *pT = scale.y * (mOffset.y + sGlobalOffset.y + 0.5f * mSize.y);
        *pB = scale.y * (mOffset.y + sGlobalOffset.y + -0.5f * mSize.y);
        *pL = scale.x * (mOffset.x + sGlobalOffset.x + -0.5f * mSize.x);
        *pR = scale.x * (mOffset.x + sGlobalOffset.x + 0.5f * mSize.x);
    } else if (mCanvasMode == CANVASMODE_LU) {
        *pT = mOffset.y + sGlobalOffset.y;

        // TODO: Fakematch
        f32 new_var2 = mOffset.y + sGlobalOffset.y;
        *pB = new_var2 + -1.0f * mSize.y * mScale.y;
        *pL = mOffset.x + sGlobalOffset.x;
        *pR = mOffset.x + sGlobalOffset.x + mSize.x * mScale.x;

        *pT *= -sGlobalScale.y;
        *pB *= -sGlobalScale.y;
        *pL *= sGlobalScale.x;
        *pR *= sGlobalScale.x;

        f32 x = -(sGlobalScale.x - 1.0f) * (0.5f * mSize.x);
        f32 y = -(sGlobalScale.y - 1.0f) * (0.5f * mSize.y);
        *pT += y;
        *pB += y;
        *pL += x;
        *pR += x;
    }
}

void Frustum::CopyFromAnother(const Frustum& rOther) {
    mProjType = rOther.mProjType;
    mCanvasMode = rOther.mCanvasMode;
    mSize = rOther.mSize;
    mFovY = rOther.mFovY;
    mTanFovY = rOther.mTanFovY;
    mNearZ = rOther.mNearZ;
    mFarZ = rOther.mFarZ;
    mOffset = rOther.mOffset;
    mScale = rOther.mScale;
    mFlags = rOther.mFlags;
}

// void Frustum::GetViewToScreen(nw4r::math::VEC3* pScreenPos,
//                               const nw4r::math::VEC3& rViewPos) const {
// #line 458
//     EGG_ASSERT(pScreenPos);

//     f32 z = rViewPos.z;
//     bool r3 = true;

//     if (-z < mNearZ) {
//         z = -mNearZ;
//         r3 = false;
//     }

//     !!r3 ? 1 : 0;

//     f32 range = mFarZ - mNearZ;

//     switch (mProjType) {
//     case PROJTYPE_PERSP: {
//         f32 cot = 1.0f / mTanFovY;
//         ;

//         break;
//     }

//     case PROJTYPE_ORTHO: {
//         pScreenPos->x = rViewPos.x * mScale.x;
//         pScreenPos->y = rViewPos.y * mScale.y;
//         pScreenPos->z = (-rViewPos.z - mNearZ) / mNearZ;
//         break;
//     }
//     }
// }

void Frustum::GetScreenToView(nw4r::math::VEC3* pViewPos,
                              const nw4r::math::VEC3& rScreenPos) const {
#line 519
    EGG_ASSERT(pViewPos);

    switch (mProjType) {
    case PROJTYPE_PERSP: {
        nw4r::math::VEC2 pos;
        ConvertToNormalCC(rScreenPos.x, rScreenPos.y, &pos.x, &pos.y);

        f32 div = (rScreenPos.z - 1.0f) * (mFarZ - mNearZ) - mNearZ;
#line 529
        EGG_ASSERT(div != 0.f);

        f32 z = mFarZ * mNearZ / div;
        pViewPos->z = z;

        pos.x *= -z;
        pos.y *= -z;

        f32 ox = mOffset.x + sGlobalOffset.x;
        f32 oy = mOffset.y + sGlobalOffset.y;

        ox = ox / (mSize.x / 2);
        oy = oy / (mSize.y / 2);

        f32 cot = 1.0f / mTanFovY;

        pViewPos->x = GetAspect() * (z * ox + pos.x) / cot;
        pViewPos->y = (z * oy + pos.y) / cot;
        break;
    }

    case PROJTYPE_ORTHO: {
        pViewPos->x = rScreenPos.x / mScale.x;
        pViewPos->y = rScreenPos.y / mScale.y;
        pViewPos->z = -(rScreenPos.z * (mFarZ - mNearZ) + mNearZ);
        break;
    }
    }
}

void Frustum::GetScreenToView(nw4r::math::VEC3* pPosView,
                              const nw4r::math::VEC2& rPosScreen) const {
#line 568
    EGG_ASSERT(pPosView);

    switch (mProjType) {
    case PROJTYPE_PERSP: {
        nw4r::math::VEC2 pos;
        ConvertToCanvasCC(rPosScreen.x, rPosScreen.y, &pos.x, &pos.y);

        pPosView->x = pos.x;
        pPosView->y = pos.y;
        pPosView->z = -(mSize.y / 2) / mTanFovY;
        break;
    }

    case PROJTYPE_ORTHO: {
        pPosView->x = rPosScreen.x / mScale.x;
        pPosView->y = rPosScreen.y / mScale.y;
        pPosView->z = mNearZ;
        break;
    }
    }
}

} // namespace EGG
