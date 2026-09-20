#include <Pack/RPSports/RPBowScene/bowling.h>

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

extern void* lbl_803CA5F0[];

// Extern Functions
void fn_803295D0(LaneBvhData* pBvhData, void* pArg1, void* pArg2);

/**
 * @brief Creates and initializes the seven lane contexts
 *
 * @param objectManager Scene object manager
 */
void RPBowGlobalLaneManager::InitializeLaneContexts(RPBowSceneObjectManager* objectManager) {
    for (int i = 0; i < 7; i++) {
        LaneContext* ctx = new LaneContext();
        pLanes[i] = ctx;
        ctx->fn_80327858(0, 10, gLaneXOffsets[i], objectManager->entities.setters[i]);
    }
}

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
        pLanes[i]->fn_803277B4();
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

        pLane->fn_80327330(&status);
        pLanes[i]->ResetPinSetterState(0);
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
            pLanes[i]->fn_80327218();
        }
    }
}

/**
 * @brief Executes a sub-tick physics/state update on the player lane and all 6 NPC lanes
 */
void RPBowGlobalLaneManager::TickNpcLanes() {
    for (int i = 0; i < 7; i++) {
        pLanes[i]->fn_80325154();
    }
}

/**
 * @brief Iterates the 7 lane item arrays to synthesize their 3D world space transforms and registers them back into the game engine's scene
 *
 * @param val Unknown integer value
 * @param pObj Pointer to an object
 * @param pObjectManager Manager object
 * @param isPlayerTurn Indicates if it is currently the player's turn
 */
void RPBowGlobalLaneManager::UpdateLaneItems(RPBowCameraTransform* transform, CameraProjection* pObj, RPBowSceneObjectManager* pObjectManager, bool isPlayerTurn) {
    if (isInitialized == 0) return;

    nw4r::math::MTX34* pResultMtx = pObjectManager->ProcessCamera(pObj, transform);

    for (int i = 0; i < 7; i++) {
        RPBowRegularPinManager* pinManager = pObjectManager->entities.pinManagers[i];
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

                    // Same issue occurs in fn_8034C230
                    f32 t23 = pBody->state.position.z;
                    f32 t22 = pBody->state.basisZ.z;
                    f32 t21 = pBody->state.basisZ.y;
                    f32 t20 = pBody->state.basisZ.x;
                    f32 t13 = pBody->state.position.y;
                    f32 t12 = pBody->state.basisY.z;
                    f32 t11 = pBody->state.basisY.y;
                    f32 t10 = pBody->state.basisY.x;
                    f32 t03 = pBody->state.position.x;
                    f32 t02 = pBody->state.basisX.z;
                    f32 t01 = pBody->state.basisX.y;
                    // f32 t00 = pBody->state.basisX.x;

                    mtx._00 = pBody->state.basisX.x;
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

                u32 flag = 0;
                if (i == 0 && isPlayerTurn != 0) {
                    flag = 1;
                }

                pinManager->CalculatePinTransforms(validCount, pLanes[i]->VF_0x14(), pResultMtx, pMtx, (nw4r::math::MTX34*)flag);
                validCount++;
            }
        }
        pinManager->HideExcessPins(validCount);
    }
}

/**
 * @brief Applies physics matrix translations onto the game's ball models
 * @details Also artificially moves the ball out of view bounds (y = 9999.0f) if it falls completely below the floor bounds.
 *
 * @param pObjectManager Scene object manager for balls
 */
void RPBowGlobalLaneManager::UpdateBallsMdl(RPBowSceneObjectManager* pObjectManager) {
    for (int i = 0; i < 7; i++) {
        LaneContext* pLane = pLanes[i];
        RPBowActiveBall* pBall = pObjectManager->entities.balls[i];

        nw4r::math::MTX34 mtx = pLane->throwContext.ballMtx;
        if (mtx._23 < -210.0f) {
            mtx._23 = 9999.0f;
        }

        float field_110 = gBowlingPhysicsData.field_110;
        pBall->mtx = mtx;
        pBall->field_0x74 = field_110;
    }
}
