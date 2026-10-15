#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Stub
 */
void RPBowPowerThrowsPinManager::fn_80340304() {
    ;
}

// Calls destructor
// fn_803402FC()

// Calls RPBowPowerThrowsPinManager::CopyMatrices
// fn_803402F4()

/**
 * @brief Destructor
 */
RPBowPowerThrowsPinManager::~RPBowPowerThrowsPinManager() {}

/**
 * @brief Sets the real and reflection models
 *
 * @param pRealModel Real pin model
 * @param pReflectionModel Reflection pin model
 */
void RPBowPowerThrowsPinManager::SetModels(RPGrpModel* pRealModel, RPGrpModel* pReflectionModel) {
    mpModels[0] = pRealModel;
    mpModels[1] = pReflectionModel;

    mpModels[0]->SetCallback(this);
    mpModels[1]->SetCallback(this);
}

/**
 * @brief Stub
 */
void RPBowPowerThrowsPinManager::fn_8034021C() {
    ;
}

/**
 * @brief Updates frames and matrices for the models
 */
void RPBowPowerThrowsPinManager::UpdateModels() {
    nw4r::math::MTX34 identityMtx;
    PSMTXIdentity(identityMtx);

    for (int i = 0; i < 2; i++) {
        nw4r::g3d::ScnObj* pScnObj = mpModels[i]->GetScnObj();

        if (pScnObj != NULL) {
            pScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &identityMtx);
        }

        mpModels[i]->UpdateFrame();
        mpModels[i]->Calc();
        mpModels[i]->Entry();
    }
}

/**
 * @brief Stub
 */
void RPBowPowerThrowsPinManager::fn_80340194() {
    ;
}

/**
 * @brief Copies matrices to the specified model
 *
 * @param pOther Target model
 */
void RPBowPowerThrowsPinManager::CopyMatrices(RPGrpModel* pOther) {
    for (int i = 0; i < 2; i++) {
        if (pOther == mpModels[i]) {
            for (u16 j = 0; j < 91; j++) {
                nw4r::math::MTX34* pDst = pOther->ReferWorldMtx(j + 1);
                const nw4r::math::MTX34* pSrc = &mMatrixPairs[j].realMtx;
                *pDst = *pSrc;
            }
        }
    }
}

/**
 * @brief Transforms the matrix for a given pin
 *
 * @param pinIndex Index of the pin
 * @param pMtx Base matrix
 * @param yOffset Y-axis translation offset
 */
void RPBowPowerThrowsPinManager::TransformMatrix(int pinIndex, const nw4r::math::MTX34* pMtx, f32 yOffset) {
    nw4r::math::MTX34 workMtx4;
    workMtx4._00 = 1.0f;  workMtx4._01 = 0.0f;  workMtx4._02 = 0.0f;  workMtx4._03 = 0.0f;
    workMtx4._10 = 0.0f;  workMtx4._11 = 1.0f;  workMtx4._12 = 0.0f;  workMtx4._13 = -yOffset;
    workMtx4._20 = 0.0f;  workMtx4._21 = 0.0f;  workMtx4._22 = 1.0f;  workMtx4._23 = 0.0f;

    nw4r::math::MTX34 workMtx3;
    MTX34Mult(&workMtx3, pMtx, &workMtx4);
    mMatrixPairs[pinIndex].realMtx = workMtx3;

    nw4r::math::MTX34 workMtx2;
    workMtx2._00 = 1.0f;  workMtx2._01 = 0.0f;  workMtx2._02 = 0.0f;  workMtx2._03 = 0.0f;
    workMtx2._10 = 0.0f;  workMtx2._11 = 1.0f;  workMtx2._12 = 0.0f;  workMtx2._13 = -yOffset;
    workMtx2._20 = 0.0f;  workMtx2._21 = 0.0f;  workMtx2._22 = 1.0f;  workMtx2._23 = 0.0f;

    nw4r::math::MTX34 workMtx1;
    nw4r::math::MTX34 workMtx0 = *pMtx;

    // Invert scale/rotation mapping for the reflection calculation
    workMtx0._10 *= -1.0f;
    workMtx0._11 *= -1.0f;
    workMtx0._12 *= -1.0f;
    workMtx0._13 *= -1.0f;

    MTX34Mult(&workMtx1, &workMtx0, &workMtx2);
    mMatrixPairs[pinIndex].reflectionMtx = workMtx1;
}

/**
 * @brief Clears matrices from the specified start index
 *
 * @param startIndex Starting pin index
 */
void RPBowPowerThrowsPinManager::ClearMatrices(int startIndex) {
    for (s32 i = startIndex; i < 91; i++) {
        mMatrixPairs[i].realMtx = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        mMatrixPairs[i].reflectionMtx = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}
