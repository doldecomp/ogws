#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <cmath>

/**
 * @brief Default camera
 */
RPGrpCamera RPGrpCamera::sDefaultCamera;

/**
 * @brief Initializes the camera system
 */
void RPGrpCamera::Initialize() {}

/**
 * @brief Constructor
 */
RPGrpCamera::RPGrpCamera() : mCameraType(ECameraType_LookAt), mFlags(0) {
    Identity();
}

/**
 * @brief Copies the state from another camera
 *
 * @param rOther Camera from which to copy
 */
void RPGrpCamera::CopyFromAnother(const RPGrpCamera& rOther) {
    if (this == &rOther) {
        return;
    }

    nw4r::math::MTX34Copy(&mViewMtx, &rOther.mViewMtx);
    nw4r::math::MTX34Copy(&mWorldMtx, &rOther.mWorldMtx);
    nw4r::math::MTX34Copy(&mAnmViewMtx, &rOther.mAnmViewMtx);
    nw4r::math::MTX34Copy(&mDirectWorldMtx, &rOther.mDirectWorldMtx);

    mPosition = rOther.mPosition;
    mTarget = rOther.mTarget;
    mRotation = rOther.mRotation;

    mDistance = rOther.mDistance;
    mRight = rOther.mRight;
    mUp = rOther.mUp;
    mForward = rOther.mForward;

    mCameraType = rOther.mCameraType;
    mFlags = rOther.mFlags;

    nw4r::math::MTX34Copy(&mWorldMtxOld, &rOther.mWorldMtxOld);
    nw4r::math::MTX34Copy(&mSavedViewMtx, &rOther.mSavedViewMtx);
}

/**
 * @brief Resets the camera transformation
 */
void RPGrpCamera::Identity() {
    nw4r::math::MTX34Identity(&mViewMtx);
    nw4r::math::MTX34Identity(&mWorldMtxOld);
    nw4r::math::MTX34Identity(&mSavedViewMtx);

    mPosition.x = mPosition.y = mPosition.z = 0.0f;

    mTarget.x = mTarget.y = 0.0f;
    mTarget.z = -1.0f;

    mRotation.x = mRotation.y = mRotation.z = 0.0f;

    mDistance = -1.0f;

    mUp.x = mUp.z = 0.0f;
    mUp.y = 1.0f;

    CalcMatrix();
    mFlags &= ~EFlag_5;
}

/**
 * @brief Updates the camera state based on the camera type
 */
void RPGrpCamera::CalcMatrix() {
    nw4r::math::MTX34Copy(&mWorldMtxOld, &mWorldMtx);

    switch (mCameraType) {
    case ECameraType_Anm: {
        nw4r::math::MTX34Copy(&mViewMtx, &mAnmViewMtx);
        SyncFromMatrix(ESyncFlag_ForAnmCamera);
        break;
    }

    case ECameraType_Direct: {
        nw4r::math::MTX34Copy(&mWorldMtx, &mDirectWorldMtx);
        SyncFromMatrix(ESyncFlag_ForDirectCamera);
        break;
    }

    case ECameraType_LookAt: {
        nw4r::math::MTX34LookAt(&mViewMtx, &mPosition, &mUp, &mTarget);
        SyncFromMatrix(ESyncFlag_ForLookAtCamera);
        break;
    }

    case ECameraType_Orbit: {
        nw4r::math::MTX34 rot;
        PSMTXTrans(mViewMtx, -mTarget.x, -mTarget.y, -mTarget.z);

        PSMTXRotRad(rot, 'Y', NW4R_MATH_DEG_TO_RAD(-mRotation.y));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        PSMTXRotRad(rot, 'X', NW4R_MATH_DEG_TO_RAD(-mRotation.x));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        PSMTXRotRad(rot, 'Z', NW4R_MATH_DEG_TO_RAD(-mRotation.z));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        PSMTXTransApply(mViewMtx, mViewMtx, 0.0f, 0.0f, mDistance);

        SyncFromMatrix(ESyncFlag_ForOrbitCamera);
        break;
    }

    case ECameraType_Free: {
        nw4r::math::MTX34 rot;
        nw4r::math::MTX34Identity(&mWorldMtx);

        PSMTXRotRad(rot, 'Z', NW4R_MATH_DEG_TO_RAD(mRotation.z));
        nw4r::math::MTX34Mult(&mWorldMtx, &rot, &mWorldMtx);

        PSMTXRotRad(rot, 'X', NW4R_MATH_DEG_TO_RAD(mRotation.x));
        nw4r::math::MTX34Mult(&mWorldMtx, &rot, &mWorldMtx);

        PSMTXRotRad(rot, 'Y', NW4R_MATH_DEG_TO_RAD(mRotation.y));
        nw4r::math::MTX34Mult(&mWorldMtx, &rot, &mWorldMtx);

        PSMTXTransApply(mWorldMtx, mWorldMtx, mPosition.x, mPosition.y,
                        mPosition.z);

        SyncFromMatrix(ESyncFlag_ForFreeCamera);
        break;
    }
    }

    mRight.x = mWorldMtx._00;
    mRight.y = mWorldMtx._10;
    mRight.z = mWorldMtx._20;

    mForward.x = mWorldMtx._02;
    mForward.y = mWorldMtx._12;
    mForward.z = mWorldMtx._22;

    mFlags &= ~EFlag_7;
}

/**
 * @brief Saves the current state of the view matrix
 */
void RPGrpCamera::SaveCameraMatrix() {
    nw4r::math::MTX34Copy(&mSavedViewMtx, &mViewMtx);
}

/**
 * @brief Converts a position from world-space to screen-space
 *
 * @param[out] pScreenPos Position in screen-space
 * @param rWorldPos Position in world-space
 * @param pScreen Screen
 */
void RPGrpCamera::GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                                   const nw4r::math::VEC3& rWorldPos,
                                   const RPGrpScreen* pScreen) const {

    nw4r::math::VEC3TransformCoord(pScreenPos, &mViewMtx, &rWorldPos);
    pScreen->GetViewToScreen(pScreenPos, *pScreenPos);
}

/**
 * @brief Converts a position from screen-space to world-space
 *
 * @param[out] pWorldPos Position in world-space
 * @param rScreenPos Position in screen-space
 * @param pScreen Screen
 */
void RPGrpCamera::GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                                   const nw4r::math::VEC3& rScreenPos,
                                   const RPGrpScreen* pScreen) const {

    pScreen->GetScreenToView(pWorldPos, rScreenPos);
    nw4r::math::VEC3TransformCoord(pWorldPos, &mWorldMtx, pWorldPos);
}

/**
 * @brief Converts a position from screen-space to world-space
 *
 * @param[out] pWorldPos Position in world-space
 * @param rScreenPos Position in screen-space
 * @param pScreen Screen
 */
void RPGrpCamera::GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                                   const nw4r::math::VEC2& rScreenPos,
                                   const RPGrpScreen* pScreen) const {

    pScreen->GetScreenToView(pWorldPos, rScreenPos);
    nw4r::math::VEC3TransformCoord(pWorldPos, &mWorldMtx, pWorldPos);
}

/**
 * @brief Derives components of the camera state from the world matrix
 *
 * @param flags Flags controlling which components to update
 */
void RPGrpCamera::SyncFromMatrix(u16 flags) {
    if (flags & ESyncFlag_ViewMtx) {
        nw4r::math::MTX34Inv(&mViewMtx, &mWorldMtx);
    } else if (flags & ESyncFlag_WorldMtx) {
        nw4r::math::MTX34Inv(&mWorldMtx, &mViewMtx);
    }

    if (flags & ESyncFlag_AnmViewMtx) {
        nw4r::math::MTX34Copy(&mAnmViewMtx, &mViewMtx);
    }

    if (flags & ESyncFlag_DirectWorldMtx) {
        nw4r::math::MTX34Copy(&mDirectWorldMtx, &mWorldMtx);
    }

    if (flags & ESyncFlag_Position) {
        mPosition.x = mWorldMtx._03;
        mPosition.y = mWorldMtx._13;
        mPosition.z = mWorldMtx._23;
    }

    if (flags & ESyncFlag_Up) {
        mUp.x = mWorldMtx._01;
        mUp.y = mWorldMtx._11;
        mUp.z = mWorldMtx._21;
    }

    if (flags & ESyncFlag_Target) {
        mTarget.x = mDistance * mWorldMtx._02 + mWorldMtx._03;
        mTarget.y = mDistance * mWorldMtx._12 + mWorldMtx._13;
        mTarget.z = mDistance * mWorldMtx._22 + mWorldMtx._23;
    }

    if (flags & ESyncFlag_Rotation) {
        f32 _12 = mWorldMtx._12;

        if (_12 - 1.0f >= -1e-22f) {
            mRotation.x = -90.0f;
            mRotation.y = -nw4r::math::Atan2Deg(mWorldMtx._20, mWorldMtx._00);
            mRotation.z = 0.0f;
            return;

        } else if (_12 + 1.0f <= 1e-22f) {
            mRotation.x = +90.0f;
            mRotation.y = -nw4r::math::Atan2Deg(mWorldMtx._20, mWorldMtx._00);
            mRotation.z = 0.0f;
            return;

        } else {
            mRotation.x = -std::asinf(_12) * 180 / NW4R_MATH_PI;
            mRotation.y = -nw4r::math::Atan2Deg(-mWorldMtx._02, mWorldMtx._22);
            mRotation.z = -nw4r::math::Atan2Deg(-mWorldMtx._10, mWorldMtx._11);
        }
    }

    if (flags & ESyncFlag_Distance) {
        f32 length = nw4r::math::VEC3DistSq(&mPosition, &mTarget);
        mDistance = -nw4r::math::FSqrt(length);
    }
}

/**
 * @brief Applies camera settings from the specified scene resource
 *
 * @param scn Scene resource
 * @param refNumber Camera reference number
 * @param frame Animation frame (defaults to the first frame)
 */
void RPGrpCamera::LoadScnCameraMatrix(const nw4r::g3d::ResAnmScn scn,
                                      u8 refNumber, f32 frame) {
    if (!scn.IsValid()) {
        return;
    }

    const nw4r::g3d::ResAnmCamera cam =
        scn.GetResAnmCameraByRefNumber(refNumber);

    nw4r::g3d::CameraAnmResult result;
    cam.GetAnmResult(&result, frame);

    static nw4r::g3d::CameraData cameraData;
    nw4r::g3d::Camera workCamera(&cameraData);
    workCamera.Init();

    nw4r::g3d::Camera::PostureInfo posture;

    switch (result.flags & nw4r::g3d::CameraAnmResult::FLAG_CAMERA_TYPE_MASK) {
    case nw4r::g3d::CameraAnmResult::CAMERATYPE_ROTATE: {
        posture.tp = nw4r::g3d::Camera::POSTURE_ROTATE;

        posture.cameraRotate = result.rotate.rot;
        break;
    }

    case nw4r::g3d::CameraAnmResult::CAMERATYPE_AIM: {
        posture.tp = nw4r::g3d::Camera::POSTURE_AIM;

        posture.cameraTarget = result.rotate.rot;
        posture.cameraTwist = result.aim.twist;

        nw4r::math::VEC3 dir = posture.cameraTarget - result.pos;
        mDistance = -nw4r::math::VEC3Len(&dir);
        break;
    }
    }

    workCamera.SetPosition(result.pos);
    workCamera.SetPosture(posture);

    // Briefly change camera types so we can apply the G3D result
    ECameraType oldType = mCameraType;
    mCameraType = ECameraType_Anm;
    {
        workCamera.GetCameraMtx(&mAnmViewMtx);
        CalcMatrix();
    }
    mCameraType = oldType;
}

DECOMP_FORCELITERAL(RPGrpCamera_cpp, 0.0f);
