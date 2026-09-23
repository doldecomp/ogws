#include <Pack/RPSports/RPBowScene/bowling.h>
#include <Pack/RPUtility/RPUtlRandom.h>

namespace Bowling {

// Extern Functions
int fn_801C3490(int arg0, float arg1, void* pArg2);
u32 fn_801C389C(RPGrpModel* pModel, int arg1, int arg2);
void fn_801C37EC(RPGrpModel* pModel, int arg1, int arg2, void* pColor);

/**
 * @brief Initializes physics constants
 *
 * @param index Rack index
 */
void RPBowBallReturnRack::InitBallReturnRack(s32 index) {
    mRackIndex = index;

    gBallReturnRackConstants.mPositionOffsets[0] = nw4r::math::VEC3( -25.0f, 3.5f, 33.3f );
    gBallReturnRackConstants.mPositionOffsets[1] = nw4r::math::VEC3( 8.8f,   3.5f, 33.3f );
    gBallReturnRackConstants.mPositionOffsets[2] = nw4r::math::VEC3( -58.5f, 3.5f, 33.3f );
    gBallReturnRackConstants.mPositionOffsets[3] = nw4r::math::VEC3( 42.4f,  3.5f, 33.3f );

    gBallReturnRackConstants.mHeightLimit = 11.700001f;
    gBallReturnRackConstants.mRepulsionThreshold = 1.075f;
    gBallReturnRackConstants.mGravity = 0.0012f;
}

/**
 * @brief Initializes the resources associated with a ball slot
 *
 * @param index Rack index
 * @param pRealModel Graphical model of the ball
 * @param pReflectionModel Reflection model of the ball
 * @param slotIndex Ball slot index mapping
 */
void RPBowBallReturnRack::InitBallSlotResources(s32 index, RPGrpModel* pRealModel, RPGrpModel* pReflectionModel, s32 slotIndex) {
    mModels[index + 1].pRealModel = pRealModel;
    mModels[index + 1].pReflectionModel = pReflectionModel;

    mSlotIndices[index] = slotIndex;
}

/**
 * @brief Sets up the graphical models for all of the NPC balls
 */
void RPBowBallReturnRack::ResetRackBallStates() {
    BallReturnBall* pBall;
    BallReturnRackConstants* pConstants = &gBallReturnRackConstants;

    pBall = mBalls;
    for (int i = 0; i < 4; i++, pBall++) {
        memset(pBall, 0, sizeof(BallReturnBall));

        pBall->mIsOnRack = true;

        pBall->mPos.z = pConstants->mHeightLimit - (2.0f * ((float)(i + 1) * pConstants->mRepulsionThreshold));
    }
}

/**
 * @brief Selects an available ball from the rack for an NPC to use on their turn
 *
 * @return The index of the selected ball, or -1 if no balls are available
 */
int RPBowBallReturnRack::SelectBallForNPC() {
    int indices[4];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (mBalls[indices[i]].mPos.z < mBalls[indices[j]].mPos.z) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    u32 randVal = (u32)(RPUtlRandom::getF32() * 3.0f);
    int result = indices[randVal];

    if (mBalls[result].mClaimedByNPC != 0 || mBalls[result].mIsOnRack == 0) {
        result = -1;
    }

    int* pIndex = indices;
    int i = 0;

    while (i < 4 && result == -1) {
        if (mBalls[*pIndex].mClaimedByNPC == 0 && mBalls[*pIndex].mIsOnRack != 0) {
            result = indices[i];
            break;
        }
        pIndex++;
        i++;
    }

    if (result != -1) {
        mBalls[result].mClaimedByNPC = 1;
        return result;
    }
    return -1;
}

/**
 * @brief Removes the ball from rack physics calculations and rendering
 *
 * @param index Ball index
 */
void RPBowBallReturnRack::RemoveBallFromRack(s32 index) {
    mBalls[index].mIsOnRack = 0;
}

/**
 * @brief Tests whether a specific ball slot currently has a ball resting on the rack
 *
 * @param index Ball index
 * @return Non-zero if the ball is resting on the rack, 0 otherwise
 */
u8 RPBowBallReturnRack::IsBallOnRack(s32 index) {
    return mBalls[index].mIsOnRack;
}

/**
 * @brief Spawns or resets a ball at the beginning of the return rack track
 *
 * @param index Ball index
 */
void RPBowBallReturnRack::SpawnBallOnRack(s32 index) {
    mBalls[index].mPos.z = 0.0f;
    mBalls[index].mClaimedByNPC = 0;
    mBalls[index].mIsOnRack = 1;
    mBalls[index].mAngle = 0.0f;
}

/**
 * @brief Removes an NPC's reservation of a ball
 *
 * @param index Ball index
 */
void RPBowBallReturnRack::ReleaseBallFromNPC(s32 index) {
    mBalls[index].mClaimedByNPC = 0;
}

/**
 * @brief Retrieves the default slot index mapping for the rack
 *
 * @param index Ball index
 * @return Default slot index mapping
 */
s32 RPBowBallReturnRack::GetBallSlotIndex(s32 index) {
    return mSlotIndices[index];
}

/**
 * @brief Main update function for the bowling scene entities
 *
 * @param index Rack index
 */
void RPBowBallReturnRack::UpdateBallReturnRack(s32 index) {
    BallReturnBall* pBall;
    RPGrpModelPair* pModelPair;
    BallReturnRackConstants* pConstants = &gBallReturnRackConstants;

    // Part 1: Calculate repulsive forces between entities
    for (int i = 0; i < 4; i++) {
        mBalls[i].mRepulsionForce = 0.0f;
    }

    for (int i = 0; i < 3; i++) {
        if (!mBalls[i].mIsOnRack) continue;

        for (int j = i + 1; j < 4; j++) {
            if (!mBalls[j].mIsOnRack) continue;

            f32 distI = mBalls[i].mPos.z;
            f32 distJ = mBalls[j].mPos.z;
            f32 distDiff = __fabs(distI - distJ);

            if (distDiff < pConstants->mRepulsionThreshold * 2.0f) {
                f32 force = (pConstants->mRepulsionThreshold * 2.0f) - distDiff;
                if (distI < distJ) {
                    mBalls[i].mRepulsionForce += -force;
                    mBalls[i].mSpeed = 0.0f;
                } else {
                    mBalls[j].mRepulsionForce += -force;
                    mBalls[j].mSpeed = 0.0f;
                }
            }
        }
    }

    // Part 2: Update physics and models for each entity
    pModelPair = &mModels[0];
    pBall = mBalls;

    for (int i = 0; i < 4; i++, pModelPair++, pBall++) {
        if (!pBall->mIsOnRack) continue;

        f32 oldZ = pBall->mPos.z;
        pBall->mSpeed += pConstants->mGravity;
        pBall->mPos.z += pBall->mSpeed + pBall->mRepulsionForce;

        if (pBall->mPos.z > pConstants->mHeightLimit) {
            pBall->mPos.z = pConstants->mHeightLimit;
            pBall->mSpeed = 0.0f;
        }

        f32 limit = 6.28318f * pConstants->mRepulsionThreshold;
        f32 diff = pBall->mPos.z - oldZ;
        f32 delta = diff / limit;

        pBall->mAngle += 6.28318f * delta;

        nw4r::math::VEC3 worldPos = pBall->mPos + pConstants->mPositionOffsets[mRackIndex];

        nw4r::math::MTX34 ballMtx, rotMtx;
        MTX34Identity(&ballMtx);
        MTX34Trans(&ballMtx, &worldPos, &ballMtx);

        nw4r::math::MTX34RotXYZFIdx(&rotMtx, 40.743664f * pBall->mAngle, 0.0f, 0.0f);
        PSMTXConcat(ballMtx, rotMtx, ballMtx);

        nw4r::g3d::ScnObj* pRealScnObj = pModelPair[1].pRealModel->GetScnObj();
        if (pRealScnObj != NULL) {
            pRealScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &ballMtx);
        }

        pModelPair[1].pRealModel->UpdateFrame();
        pModelPair[1].pRealModel->Calc();

        if (fn_801C3490(index, pConstants->mRepulsionThreshold, &worldPos) != 0) {
            u32 colorVal = fn_801C389C(pModelPair[1].pRealModel, 0, 0);

            GXColor color;
            GXColor temp;
            temp.r = colorVal >> 24;
            temp.g = colorVal >> 16;
            temp.b = colorVal >> 8;
            temp.a = 255;
            color = temp;

            fn_801C37EC(pModelPair[1].pRealModel, 0, 0, &color);
            pModelPair[1].pRealModel->Entry();
        }

        nw4r::math::MTX34 reflectionMtx = ballMtx;
        reflectionMtx.m[1][0] *= -1.0f;
        reflectionMtx.m[1][1] *= -1.0f;
        reflectionMtx.m[1][2] *= -1.0f;
        reflectionMtx.m[1][3] *= -1.0f;

        nw4r::g3d::ScnObj* pReflScnObj = pModelPair[1].pReflectionModel->GetScnObj();
        if (pReflScnObj != NULL) {
            pReflScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &reflectionMtx);
        }

        pModelPair[1].pReflectionModel->UpdateFrame();
        pModelPair[1].pReflectionModel->Calc();

        nw4r::math::VEC3 reflPosFinal;
        reflPosFinal.x = reflectionMtx.m[0][3];
        reflPosFinal.y = reflectionMtx.m[1][3];
        reflPosFinal.z = reflectionMtx.m[2][3];

        if (fn_801C3490(index, pConstants->mRepulsionThreshold, &reflPosFinal) != 0) {
            pModelPair[1].pReflectionModel->Entry();
        }
    }
}

} // namespace Bowling
