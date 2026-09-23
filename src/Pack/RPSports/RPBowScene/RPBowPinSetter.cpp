#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

#define SWEEPER_BALL_Z_TRIGGER -192.0f
#define SWEEPER_FRAME_LIFT_PINS 0x73
#define SWEEPER_FRAME_START_SWEEP 0xAF
#define SWEEPER_FRAME_PLACE_PINS 0xF5
#define SWEEPER_FRAME_END 0x1B8

/**
 * @brief Resets the pin setter state
 *
 * @param pContext Lane context
 * @param isNewRack Flag indicating if this is a new rack
 */
void ResetPinSetterState(LaneContext* pContext, u8 isNewRack) {
    memset(&pContext->setterAnm, 0, 0x10);
    pContext->setterAnm.isNewRack = isNewRack;

    PinSetter* pSetter = pContext->pPinSetter;
    pSetter->sequencePhase = 0;
    pSetter->primaryState = 0;
    pSetter->frameTimer = 0.0f;
}

/**
 * @brief Triggers the pin setter animation sequence
 *
 * @param pContext Lane context
 * @param spawnNewRack Flag indicating if a new rack should be spawned
 */
void TriggerPinSetter(LaneContext* pContext, int spawnNewRack) {
    if (pContext->setterAnm.sequenceFrameCount == 0) {
        pContext->setterAnm.sequenceFrameCount = 1;
        if (spawnNewRack != 0) {
            pContext->setterAnm.isNewRack = 1;
        }
    }
}

/**
 * @brief Updates the pin setter state and animations
 *
 * @param pContext Lane context
 * @return 1 on success, otherwise 0
 */
int UpdatePinSetter(LaneContext* pContext) {
    int currentAnimMode = pContext->throwContext.animationMode;
    pContext->setterAnm.animOffsetZ = 0.0f;
    pContext->setterAnm.animRotationY = -180.5f;

    if (currentAnimMode == 2) {
        return 1;
    }

    int sequenceFrame = pContext->setterAnm.sequenceFrameCount;
    if (sequenceFrame == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            pContext->pPinManager->pPinBodies[i]->mode_0x28C = 0;
        }

        float z = pContext->throwContext.ballMtx._23;
        float y = pContext->throwContext.ballMtx._13;
        float x = pContext->throwContext.ballMtx._03;
        nw4r::math::VEC3 ballPos(x, y, z);

        if (ballPos.z < SWEEPER_BALL_Z_TRIGGER) {
            pContext->pPinSetter->sequencePhase = 1;
        }
        return 1;
    }

    if (currentAnimMode != 0) {
        return 1;
    }

    if (sequenceFrame == 1 && pContext->setterAnm.isNewRack == 0) {
        pContext->pPinSetter->sequencePhase = 2;
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_LIFT_PINS && pContext->setterAnm.isNewRack == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            if (pContext->pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pContext->pPinManager->pPinBodies[i]->mode_0x28C = 1;
            }
        }
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_START_SWEEP) {
        pContext->pPinSetter->sequencePhase = 3;
    }

    if (pContext->setterAnm.sequenceFrameCount > SWEEPER_FRAME_START_SWEEP) {
        pContext->setterAnm.animOffsetZ = 0.28f * ((float)pContext->setterAnm.sequenceFrameCount - (float)SWEEPER_FRAME_START_SWEEP);
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && pContext->setterAnm.isNewRack == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            if (pContext->pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pContext->pPinManager->pPinBodies[i]->mode_0x28C = 3;
            }
        }
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && pContext->setterAnm.isNewRack != 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            pContext->pPinManager->pPinBodies[i]->VF_0x0C();

            nw4r::math::VEC3 basisZ;
            nw4r::math::VEC3 basisY;
            nw4r::math::VEC3 basisX;

            pContext->pPinManager->pPinBodies[i]->isActive = 1;

            PinPhysicsBody* pBody = pContext->pPinManager->pPinBodies[i];
            nw4r::math::VEC3 pos = pBody->field_0xFC;
            pos.y = 8.0f;

            pBody->position = pos;

            basisX.x = 1.0f;
            basisX.y = 0.0f;
            basisX.z = 0.0f;
            pBody->basisX = basisX;

            basisY.x = 0.0f;
            basisY.y = 1.0f;
            basisY.z = 0.0f;
            pBody->basisY = basisY;

            basisZ.x = 0.0f;
            basisZ.y = 0.0f;
            basisZ.z = 1.0f;
            pBody->basisZ = basisZ;

            pContext->pPinManager->pPinBodies[i]->mode_0x28C = 3;
        }
    }

    pContext->setterAnm.sequenceFrameCount++;
    return 1;
}

/**
 * @brief Tests whether the pin setter is currently active
 *
 * @param pContext Lane context
 * @return 1 if active, 0 otherwise
 */
int IsPinSetterActive(LaneContext* pContext) {
    int frame = pContext->setterAnm.sequenceFrameCount;
    if (frame != 0 && frame < SWEEPER_FRAME_END) {
        return 1;
    }
    return 0;
}

/**
 * @brief Unknown function (stubbed)
 */
void fn_803345F0(LaneContext* /* unused */) {
    ;
}

} // namespace Bowling
