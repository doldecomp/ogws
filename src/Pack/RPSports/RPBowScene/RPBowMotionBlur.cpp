#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

// Appears to check frustum culling
extern bool fn_801C3490(void* pCullingCtx, const nw4r::math::VEC3* pos, f32 radius);

/**
 * @brief Destructor
 */
RPBowMotionBlur::~RPBowMotionBlur() {}

/**
 * @brief Sets the models used for the motion blur effect
 *
 * @param pReal1 Real model 1
 * @param pReal2 Real model 2
 * @param pReal3 Real model 3
 * @param pRefl1 Reflection model 1
 * @param pRefl2 Reflection model 2
 * @param pRefl3 Reflection model 3
 */
void RPBowMotionBlur::SetBlurModels(RPGrpModel* pReal1, RPGrpModel* pReal2, RPGrpModel* pReal3, RPGrpModel* pRefl1, RPGrpModel* pRefl2, RPGrpModel* pRefl3) {
    models[0].pRealModel = pReal1;
    models[0].pReflectionModel = pRefl1;
    models[1].pRealModel = pReal2;
    models[1].pReflectionModel = pRefl2;
    models[2].pRealModel = pReal3;
    models[2].pReflectionModel = pRefl3;
}

/**
 * @brief Deactivates the motion blur effect
 */
void RPBowMotionBlur::DeactivateBlur() {
    isActive = false;
}

/**
 * @brief Updates the transform matrices for the motion blur
 *
 * @param pBaseMtx Base transform matrix
 * @param blurSpeed Speed of the blur effect
 */
void RPBowMotionBlur::UpdateBlurTransform(const nw4r::math::MTX34* pBaseMtx, f32 blurSpeed) {
    if (blurSpeed > 0.001f) {
        isActive = true;
    } else {
        isActive = false;
        return;
    }

    f32 stretchFactor = (blurSpeed * 2.0f) / 5.267f;

    blurMtxs[2] = *pBaseMtx;
    blurMtxs[1] = *pBaseMtx;
    blurMtxs[0] = *pBaseMtx;

    blurMtxs[0]._03 -= pBaseMtx->_00 * blurSpeed;
    blurMtxs[0]._13 -= pBaseMtx->_10 * blurSpeed;
    blurMtxs[0]._23 -= pBaseMtx->_20 * blurSpeed;

    blurMtxs[2]._03 += pBaseMtx->_00 * blurSpeed;
    blurMtxs[2]._13 += pBaseMtx->_10 * blurSpeed;
    blurMtxs[2]._23 += pBaseMtx->_20 * blurSpeed;

    blurMtxs[1]._00 *= stretchFactor;
    blurMtxs[1]._10 *= stretchFactor;
    blurMtxs[1]._20 *= stretchFactor;

    speed = blurSpeed;
}

/**
 * @brief Renders the motion blur models
 *
 * @param pCullingCtx Frustum culling context
 */
void RPBowMotionBlur::DrawBlur(void* pCullingCtx) {
    if (!isActive) {
        return;
    }

    nw4r::math::VEC3 pos(blurMtxs[1]._03, blurMtxs[1]._13, blurMtxs[1]._23);
    if (!fn_801C3490(pCullingCtx, &pos, speed * 2.0f)) {
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (models[i].pRealModel->GetScnObj() != NULL) {
            models[i].pRealModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &blurMtxs[i]);
        }
        models[i].pRealModel->Calc();
        models[i].pRealModel->Entry();

        nw4r::math::MTX34 reflectionMtx = blurMtxs[i];
        reflectionMtx._10 *= -1.0f;
        reflectionMtx._11 *= -1.0f;
        reflectionMtx._12 *= -1.0f;
        reflectionMtx._13 *= -1.0f;

        if (models[i].pReflectionModel->GetScnObj() != NULL) {
            models[i].pReflectionModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &reflectionMtx);
        }
        models[i].pReflectionModel->Calc();
        models[i].pReflectionModel->Entry();
    }
}

} // namespace Bowling
