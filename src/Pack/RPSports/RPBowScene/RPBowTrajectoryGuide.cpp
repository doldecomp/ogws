#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

/**
 * @brief Updates the controller state bitmask
 *
 * @param pObj Unknown object data array
 */
void UpdateControllerState(u32* pObj) {
    if (pObj[3] != 0) {
        EGG::CoreController* pCtrl = EGG::CoreControllerMgr::instance()->getNthController(0);

        pObj[3] &= 0x100;
    }
}

/**
 * @brief Destructor
 */
RPBowTrajectoryGuide::~RPBowTrajectoryGuide() {}

/**
 * @brief Sets the main directional indicator models for the trajectory guide
 *
 * @param pMainModel Primary guide model
 * @param pUnkModel Secondary guide model
 */
void RPBowTrajectoryGuide::SetMainModels(RPGrpModel* pMainModel, RPGrpModel* pUnkModel) {
    mpMainModel = pMainModel;
    mpUnkModel = pUnkModel;
}

/**
 * @brief Assigns a dot model to a specific index in the guide path
 *
 * @param index Index of the dot model
 * @param pDotModel Point model along the trajectory
 */
void RPBowTrajectoryGuide::SetDotModel(u32 index, RPGrpModel* pDotModel) {
    mpDotModels[index] = pDotModel;
}

/**
 * @brief Initializes the trajectory guide state upon scene startup
 */
void RPBowTrajectoryGuide::Initialize() {
    mActiveModelIndex = 0;
    mIsVisible = 0;
    mStartX = 0.0f;
    mAngle = 0.0f;
    unk_0x60 = 0;
    mLimitWidth = 0.0f;
    mLimitCenter = 0.0f;
}

/**
 * @brief Resets the trajectory guide state for a new shot
 */
void RPBowTrajectoryGuide::Reset() {
    mActiveModelIndex = 0;
    mIsVisible = 0;
    mStartX = 0.0f;
    mAngle = 0.0f;
    unk_0x60 = 0;
    mLimitWidth = 0.0f;
    mLimitCenter = 0.0f;
}

/**
 * @brief Renders the trajectory guide
 * @details Computes transforms and pushes both the main indicator (arrow) and
 * the individual path dots to the renderer to visually represent the player's aim.
 */
void RPBowTrajectoryGuide::Draw() {
    if (mIsVisible == 0) return;

    f32 cosAngle = std::cos(mAngle);
    f32 nCosAngle = -cosAngle;
    f32 sinAngle = std::sin(mAngle);

    nw4r::math::VEC3 vecB(sinAngle, 0.0f, nCosAngle);
    nw4r::math::VEC3 vecA(0.0f, -1.0f, 0.0f);
    nw4r::math::VEC3 vecCross;
    nw4r::math::VEC3Cross(&vecCross, &vecB, &vecA);

    nw4r::math::MTX34 mtx(
        1.0f, 0.0f, 0.0f, mStartX,
        0.0f, 1.0f, 0.0f, vecB.y + 0.03f,
        0.0f, 0.0f, 1.0f, 20.0f
    );

    nw4r::math::VEC3 vecBase(mStartX, 0.0f, 20.0f);

    if (nw4r::g3d::ScnObj* pScnObj1 = (&mpMainModel)[mActiveModelIndex]->GetScnObj()) {
        pScnObj1->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mtx);
    }

    (&mpMainModel)[mActiveModelIndex]->UpdateFrame();
    (&mpMainModel)[mActiveModelIndex]->Calc();
    (&mpMainModel)[mActiveModelIndex]->Entry();

    nw4r::math::MTX34 mtx2(
        vecCross.x, vecA.x, vecB.x, 0.0f,
        vecCross.y, vecA.y, vecB.y, 0.0f,
        vecCross.z, vecA.z, vecB.z, 0.0f
    );

    for (int i = 0; i < 16; i++) {
        nw4r::math::VEC3 vecFinal = vecBase + ((vecB * 6.0f) * static_cast<f32>(i));

        f32 diffX = vecFinal.x - mLimitCenter;

        if (diffX < -mLimitWidth || diffX > mLimitWidth) {
            if (vecFinal.z < -6.0f) {
                continue;
            }
        }

        mtx2._03 = vecFinal.x;
        mtx2._13 = vecFinal.y + 0.03f;
        mtx2._23 = vecFinal.z;

        if (nw4r::g3d::ScnObj* pScnObj2 = mpDotModels[i]->GetScnObj()) {
            pScnObj2->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mtx2);
        }

        mpDotModels[i]->UpdateFrame();
        mpDotModels[i]->Calc();
        mpDotModels[i]->Entry();
    }
}

} // namespace Bowling
