#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Resets pin hit states based on obstacle data and mapping
 *
 * @param pPinBitfield[out] Array of pin bitfields to update
 * @param pMgr Obstacle manager instance
 * @param obstacleSetIdx Index of the active obstacle set
 * @param useDirectMapping Flag to bypass the mapping array and use direct indexing
 */
void UpdatePinHitState(PinStatus* pPinStatus, RPBowObstacleManager* pMgr, u32 obstacleSetIdx, u32 useDirectMapping) {
    pPinStatus->pinBits[3] = 0;
    pPinStatus->pinBits[2] = 0;
    pPinStatus->pinBits[1] = 0;
    pPinStatus->pinBits[0] = 0;
    pPinStatus->pinCount = 10;

    const u32 pinMapping[10] = {0, 2, 1, 5, 4, 3, 9, 8, 7, 6};

    for (int i = 0; i < 10; i++) {
        u32 targetPin = useDirectMapping ? i : pinMapping[i];
        if (pMgr->dataPtr[obstacleSetIdx].pins[targetPin].hitTimer >= -1000.0f) {
            if (pMgr->dataPtr[obstacleSetIdx].pins[targetPin].unk_04 >= -1000.0f) {
                pPinStatus->pinBits[i / 30] |= (1 << (i % 30));
            }
        }
    }
}

/**
 * @brief Tests whether the ball has collided with any active obstacle
 *
 * @param obstacleSetIdx Index of the active obstacle set
 * @param pBall Position vector of the ball
 * @return 1 if a collision occurred, 0 otherwise
 */
u32 RPBowObstacleManager::CheckObstacleCollision(u32 obstacleSetIdx, nw4r::math::VEC3* pBall) {
    for (int i = 0; i < 16; i++) {
        if (dataPtr[obstacleSetIdx].obstacles[i].scale > 0.000001f) {
            float threshold = dataPtr[obstacleSetIdx].obstacles[i].offsetZ;
            if (-pBall->z > threshold - 13.0f && -pBall->z < threshold + 4.0f) {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * @brief Tests whether the ball has passed all obstacles in the current lane
 *
 * @param obstacleSetIdx Index of the active obstacle set
 * @param pBall Position vector of the ball
 * @return 1 if all active obstacles have been passed, 0 otherwise
 */
u32 RPBowObstacleManager::CheckObstaclePassed(u32 obstacleSetIdx, nw4r::math::VEC3* pBall) {
    for (int i = 0; i < 16; i++) {
        if (dataPtr[obstacleSetIdx].obstacles[i].scale > 0.000001f) {
            if (-dataPtr[obstacleSetIdx].obstacles[i].offsetZ < pBall->z) {
                return 0;
            }
        }
    }

    return 1;
}

/**
 * @brief Initializes obstacle positions and states for a lane
 *
 * @param obstacleSetIdx Index of the active obstacle set
 * @param isRightSide Flag indicating if the lane is on the right side
 * @param spawnZ Z-coordinate to spawn the obstacles
 */
void RPBowObstacleManager::ResetLaneObstacles(u32 obstacleSetIdx, u32 isRightSide, f32 spawnZ) {
    for (int i = 0; i < 48; i++) {
        obstacles[i].active = 0;
    }

    for (int i = 0; i < 16; i++) {
        ObstacleDef* pObstacleDef = &dataPtr[obstacleSetIdx].obstacles[i];
        ObstacleInstance* pState = &obstacles[i];

        pState->active = 0;

        if (pObstacleDef->scale > 0.000001f) {
            pState->body.fn_80329088(10.0f, 0.5f, 1.0f, 0.0f);
            f32 posZ = -pObstacleDef->offsetZ;
            f32 adj = (isRightSide != 0) ? (pObstacleDef->offsetX) : (-pObstacleDef->offsetX);

            pState->body.state.position = nw4r::math::VEC3(spawnZ + adj, 0.0f, posZ);
            pState->baseScale = pObstacleDef->scale;
            pState->active = 1;
        }
    }
}

/**
 * @brief Represents a single collision triangle
 */
struct CollisionTriangle {
    // total size: 0x24
    nw4r::math::_VEC3 vertex[3];  // offset 0x0, size 0x24
};

/**
 * @brief Represents the geometric hull for an obstacle
 */
struct CollisionHull {
    // total size: 0x1B0
    CollisionTriangle triangles[12];  // offset 0x0, size 0x1B0
};

// Default geometric definitions for an obstacle hull
const CollisionHull sObstacleHullVertices = {{
    { { { -1.0f, -1.0f,  1.0f }, {  1.0f, -1.0f,  1.0f }, {  1.0f,  1.0f,  1.0f } } },
    { { { -1.0f, -1.0f,  1.0f }, {  1.0f,  1.0f,  1.0f }, { -1.0f,  1.0f,  1.0f } } },
    { { { -1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f, -1.0f } } },
    { { { -1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f, -1.0f }, { -1.0f,  1.0f, -1.0f } } },
    { { { -1.0f,  1.0f, -1.0f }, {  1.0f,  1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f } } },
    { { { -1.0f,  1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f } } },
    { { { -1.0f, -1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f }, {  1.0f, -1.0f,  1.0f } } },
    { { { -1.0f, -1.0f, -1.0f }, {  1.0f, -1.0f,  1.0f }, { -1.0f, -1.0f,  1.0f } } },
    { { {  1.0f, -1.0f,  1.0f }, {  1.0f, -1.0f, -1.0f }, {  1.0f,  1.0f, -1.0f } } },
    { { {  1.0f, -1.0f,  1.0f }, {  1.0f,  1.0f, -1.0f }, {  1.0f,  1.0f,  1.0f } } },
    { { { -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f,  1.0f }, { -1.0f,  1.0f,  1.0f } } },
    { { { -1.0f, -1.0f, -1.0f }, { -1.0f,  1.0f,  1.0f }, { -1.0f,  1.0f, -1.0f } } }
}};

/**
 * @brief Updates collision geometry for all active obstacles
 */
void RPBowObstacleManager::UpdateObstacleCollisionBounds() {
    const CollisionHull* pShapeDataSrc = &sObstacleHullVertices;

    f32 scaleY = 2.329f;
    f32 scaleZ = 0.408f;

    for (int i = 0; i < 48; i++) {
        ObstacleInstance* pObstacle = &obstacles[i];

        if (pObstacle->active != 0) {
            nw4r::math::MTX34 mtx1(
                pObstacle->body.state.basisX.x, pObstacle->body.state.basisY.x, pObstacle->body.state.basisZ.x, pObstacle->body.state.position.x,
                pObstacle->body.state.basisX.y, pObstacle->body.state.basisY.y, pObstacle->body.state.basisZ.y, pObstacle->body.state.position.y,
                pObstacle->body.state.basisX.z, pObstacle->body.state.basisY.z, pObstacle->body.state.basisZ.z, pObstacle->body.state.position.z
            );

            CollisionHull shapeData = *pShapeDataSrc;

            for (int j = 0; j < 12; j++) {
                CollisionTriangleState* pPart = &pObstacle->triangles[j];
                f32 scaleX = pObstacle->baseScale;

                pPart->vec0 = nw4r::math::VEC3(
                    scaleX * shapeData.triangles[j].vertex[0].x,
                    scaleY * shapeData.triangles[j].vertex[0].y,
                    scaleZ * shapeData.triangles[j].vertex[0].z
                );

                pPart->vec1 = nw4r::math::VEC3(
                    scaleX * shapeData.triangles[j].vertex[1].x,
                    scaleY * shapeData.triangles[j].vertex[1].y,
                    scaleZ * shapeData.triangles[j].vertex[1].z
                );

                pPart->vec2 = nw4r::math::VEC3(
                    scaleX * shapeData.triangles[j].vertex[2].x,
                    scaleY * shapeData.triangles[j].vertex[2].y,
                    scaleZ * shapeData.triangles[j].vertex[2].z
                );

                // Transforms each vertex by the body matrix (in-place)
                nw4r::math::VEC3Transform(&pPart->vec0, &mtx1, &pPart->vec0);
                nw4r::math::VEC3Transform(&pPart->vec1, &mtx1, &pPart->vec1);
                nw4r::math::VEC3Transform(&pPart->vec2, &mtx1, &pPart->vec2);

                // Computes all four differences before any cross product
                nw4r::math::VEC3 diff10 = pPart->vec1 - pPart->vec0;
                nw4r::math::VEC3 diff20 = pPart->vec2 - pPart->vec0;
                nw4r::math::VEC3 diff21 = pPart->vec2 - pPart->vec1;
                nw4r::math::VEC3 diff02 = pPart->vec0 - pPart->vec2;

                // Primary surface normal
                nw4r::math::VEC3Cross(&pPart->cross0, &diff10, &diff20);
                nw4r::math::VEC3Normalize(&pPart->cross0, &pPart->cross0);

                // Edge normals
                nw4r::math::VEC3Cross(&pPart->cross1, &diff10, &pPart->cross0);
                nw4r::math::VEC3Cross(&pPart->cross2, &diff21, &pPart->cross0);
                nw4r::math::VEC3Cross(&pPart->cross3, &diff02, &pPart->cross0);

                nw4r::math::VEC3Normalize(&pPart->cross1, &pPart->cross1);
                nw4r::math::VEC3Normalize(&pPart->cross2, &pPart->cross2);
                nw4r::math::VEC3Normalize(&pPart->cross3, &pPart->cross3);

                // Compute plane/edge bias
                nw4r::math::VEC3 diff01 = pPart->vec0 - pPart->vec1;
                pPart->edgeBias = -nw4r::math::VEC3Dot(&diff01, &pPart->cross2);
            }
        }
    }
}
