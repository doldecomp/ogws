#include <egg/gfxe.h>

namespace EGG {

void LightObject::Calc() {
    mLightVector = mDir;

    mLightColor.a = mBrightnessColor.a;
}

void LightObject::CalcView(const nw4r::math::MTX34& cameraMTX) {
    nw4r::math::VEC3 camVec;
    nw4r::math::VEC3 sumVec;

    if (mLightType == cLightType_Dir) {
        camVec.z = -cameraMTX._22;
        camVec.x = -cameraMTX._20;
        camVec.y = -cameraMTX._21;

        if (nw4r::math::VEC3Len(&camVec) > 0.0f) {
            C_VECHalfAngle(mDir, camVec, sumVec);
            PSVECScale(sumVec, mLightVector, -1.0f);
        } else {
            mLightVector.y = 0.0f;
            mLightVector.x = 0.0f;
            mLightVector.z = 1.0f;
        }
    }
}

void LightObject::InitGX(GXLightObj* pObj) const {
#line 281
    EGG_ASSERT(pObj);
    if ((mFlags & 1) && (mFlags & 64)) {
        GXInitLightColor(pObj, mLightColor);
        //! TODO(texline) Variables are incomplete
    }
}

void LightObject::CalcDirDist() {
    mDir.x = mAt.x - mPos.x;
    mDir.y = mAt.y - mPos.y;
    mDir.z = mAt.z - mPos.z;

    mDistance = nw4r::math::VEC3Len(&mDir);
    if (mDistance > 0.0f) {
        mDir /= mDistance;
    } else {
        mDir.z = 0.0f;
        mDir.y = 0.0f;
        mDir.x = 0.0f;
    }
}

void LightObject::CalcAt() {
    //! Calculating all variables at once leads to (non-matching) paired singles
    //! operations
    mAt.x = (mDir.x * mDistance) + mPos.x;
    mAt.y = (mDir.y * mDistance) + mPos.y;
    mAt.z = (mDir.z * mDistance) + mPos.z;
}

} // namespace EGG
