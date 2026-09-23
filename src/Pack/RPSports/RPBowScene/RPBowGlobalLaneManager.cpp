#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

/**
 * @brief Pin target offsets
 * @details Controls where the triangle of pins is set up.
 */
float gLaneXOffsets[8] = {
    0,
    -16.1,
    17.6,
    -33.75,
    33.6,
    -49.85,
    51.15,
    0
};

// Extern Functions
void ResetPinSetterState(LaneContext* pLane, u8 arg);
void fn_80327330(LaneContext* pLane, PinStatus* pStatus);
nw4r::math::MTX34* fn_80316A48(SomeUnkManager0* pSomeMgr, void* pObj, int val);
void fn_8034EADC(void* pArrEntry, int validCount, nw4r::math::MTX34* pResultMtx, nw4r::math::MTX34* pMtx, bool flag);
void fn_8034E974(void* pArrEntry, int validCount);
void fn_80327218(LaneContext* pLane);
void fn_803277B4(LaneContext* pLane);
void fn_803295D0(LaneBvhData* pBvhData, void* pArg1, void* pArg2);
void fn_80325154(LaneContext* pLane);

/**
 * @brief Tests whether the ball's X position falls inside the hit-box radius of any lane boundary
 *
 * @param pBallXPos Ball's X position
 * @param radius Hit-box radius
 * @return True if the ball intersects with a lane boundary, false otherwise
 */
bool CheckBallLaneIntersection(float* pBallXPos, float radius) {
    for (int i = 0; i < 7; i++) {
        if (*pBallXPos > gLaneXOffsets[i] - radius && *pBallXPos < radius + gLaneXOffsets[i]) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Initializes the context state and logic for all 7 lanes
 */
void RPBowGlobalLaneManager::InitializeBallManagerLanes() {
    for (int i = 0; i < 7; i++) {
        fn_803277B4(pLanes[i]);
    }
}

/**
 * @brief Submits parameters to setup secondary components attached to each lane and flags the manager as initialized
 *
 * @param pArg1 First setup parameter
 * @param pArg2 Second setup parameter
 */
void RPBowGlobalLaneManager::SetupBallManagerLaneObjects(void* pArg1, void* pArg2) {
    for (int i = 0; i < 7; i++) {
        fn_803295D0(pLanes[i]->pLaneBvhData, pArg1, pArg2);
    }
    isInitialized = 1;
}

/**
 * @brief Resets the pin layout mask to a fresh set of 10 standing pins for all 7 lanes
 */
void RPBowGlobalLaneManager::ResetLanePinsAndAnimations() {
    for (int i = 0; i < 7; i++) {
        LaneContext* pLane = pLanes[i];
        PinStatus status;
        status.pinBits[3] = -1;
        status.pinBits[2] = -1;
        status.pinBits[1] = -1;
        status.pinBits[0] = -1;
        status.pinCount = 10;

        fn_80327330(pLane, &status);
        ResetPinSetterState(pLanes[i], 0);
    }
    field_0x21 = 0;
}

/**
 * @brief Pushes target state updates to all lanes
 *
 * @param value Target state value
 */
void RPBowGlobalLaneManager::SetLaneUnknownState(int value) {
    for (int i = 0; i < 7; i++) {
        pLanes[i]->laneStateTarget = value;
    }
}

/**
 * @brief Ensures lane position offsets are correctly pushed to memory
 * @details Computes ball physics on NPC lanes, and skips computing it on the player lane unless conditions dictate otherwise.
 */
void RPBowGlobalLaneManager::UpdateBallsPhysics() {
    for (int i = 0; i < 7; i++) {
        pLanes[i]->laneXOffset = gLaneXOffsets[i];
        if (i != 0 || field_0x21 == 0) {
            fn_80327218(pLanes[i]);
        }
    }
}

/**
 * @brief Executes a sub-tick physics/state update on the player lane and all 6 NPC lanes
 */
void RPBowGlobalLaneManager::TickNpcLanes() {
    for (int i = 0; i < 7; i++) {
        fn_80325154(pLanes[i]);
    }
}

/**
 * @brief Iterates the 7 lane item arrays to synthesize their 3D world space transforms and registers them back into the game engine's scene
 *
 * @param val Unknown integer value
 * @param pObj Pointer to an object
 * @param pSomeMgr Manager object
 * @param isPlayerTurn Indicates if it is currently the player's turn
 */
void RPBowGlobalLaneManager::UpdateLaneItems(int val, void* pObj, SomeUnkManager0* pSomeMgr, bool isPlayerTurn) {
    if (isInitialized == 0) return;

    nw4r::math::MTX34* pResultMtx = fn_80316A48(pSomeMgr, pObj, val);

    for (int i = 0; i < 7; i++) {
        void* pArrEntry = pSomeMgr->arr[i];
        int validCount = 0;

        for (int j = 0; j < 10; j++) {
            LaneContext* pLane = pLanes[i];
            int limit = pLane->pinCount;
            u8 isValid;

            if (j >= limit) {
                isValid = 0;
            } else {
                PinPhysicsBody* pBody = pLane->pPinManager->pPinBodies[j];
                isValid = pBody->isActive;
            }

            if (isValid != 0) {
                nw4r::math::MTX34 mtx;
                nw4r::math::MTX34* pMtx;

                if (j >= limit) {
                    nw4r::math::MTX34 mtxTemp;
                    MTX34Identity(&mtxTemp);
                    mtx = mtxTemp;
                    pMtx = &mtx;
                } else {
                    PinPhysicsBody* pBody = pLane->pPinManager->pPinBodies[j];
                    pMtx = &mtx;

                    f32 t23 = pBody->position.z;
                    f32 t22 = pBody->basisZ.z;
                    f32 t21 = pBody->basisZ.y;
                    f32 t20 = pBody->basisZ.x;
                    f32 t13 = pBody->position.y;
                    f32 t12 = pBody->basisY.z;
                    f32 t11 = pBody->basisY.y;
                    f32 t10 = pBody->basisY.x;
                    f32 t03 = pBody->position.x;
                    f32 t02 = pBody->basisX.z;
                    f32 t01 = pBody->basisX.y;
                    // f32 t00 = pBody->basisX.x;

                    mtx._00 = pBody->basisX.x;
                    mtx._01 = t01;
                    mtx._02 = t02;
                    mtx._03 = t03;
                    mtx._10 = t10;
                    mtx._11 = t11;
                    mtx._12 = t12;
                    mtx._13 = t13;
                    mtx._20 = t20;
                    mtx._21 = t21;
                    mtx._22 = t22;
                    mtx._23 = t23;
                }

                bool flag = false;
                if (i == 0 && isPlayerTurn != 0) {
                    flag = true;
                }

                pLanes[i]->VF_0x14();

                fn_8034EADC(pArrEntry, validCount, pResultMtx, pMtx, flag);
                validCount++;
            }
        }
        fn_8034E974(pArrEntry, validCount);
    }
}

/**
 * @brief Applies physics matrix translations onto the game's ball models
 * @details Also artificially moves the ball out of view bounds (y = 9999.0f) if it falls completely below the floor bounds.
 *
 * @param pBallMgr Scene object manager for balls
 */
void RPBowGlobalLaneManager::UpdateBallsMdl(SceneObjectManager* pBallMgr) {
    for (int i = 0; i < 7; i++) {
        LaneContext* pLane = pLanes[i];
        RPBowActiveBall* pBall = pBallMgr->entities.balls[i];

        nw4r::math::MTX34 mtx = pLane->throwContext.ballMtx;
        if (mtx._23 < -210.0f) {
            mtx._23 = 9999.0f;
        }

        float field_110 = gBowlingPhysicsData.field_110;
        pBall->mtx = mtx;
        pBall->field_0x74 = field_110;
    }
}

} // namespace Bowling
