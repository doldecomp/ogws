#include <Pack/RPSports/RPBowScene/bowling.h>

#define SWEEPER_BALL_Z_TRIGGER -192.0f
#define SWEEPER_FRAME_LIFT_PINS 0x73
#define SWEEPER_FRAME_START_SWEEP 0xAF
#define SWEEPER_FRAME_PLACE_PINS 0xF5
#define SWEEPER_FRAME_END 0x1B8

/**
 * @brief Resets the pin setter state
 *
 * @param isNewRack Flag indicating if this is a new rack
 */
void LaneContext::ResetPinSetterState(u8 isNewRack) {
    memset(&setterAnimation, 0, 0x10);
    setterAnimation.isNewRack = isNewRack;

    RPBowPinSetterModel* pSetter = pPinSetter;
    pSetter->mSequencePhase = 0;
    pSetter->mPrimaryState = 0;
    pSetter->mFrameTimer = 0.0f;
}

/**
 * @brief Triggers the pin setter animation sequence
 *
 * @param spawnNewRack Flag indicating if a new rack should be spawned
 */
void LaneContext::TriggerPinSetter(int spawnNewRack) {
    if (setterAnimation.sequenceFrameCount == 0) {
        setterAnimation.sequenceFrameCount = 1;
        if (spawnNewRack != 0) {
            setterAnimation.isNewRack = 1;
        }
    }
}

/**
 * @brief Updates the pin setter state and animations
 *
 * @return 1 on success, otherwise 0
 */
int LaneContext::UpdatePinSetter() {
    int currentAnimMode = throwContext.animationMode;
    setterAnimation.animOffsetZ = 0.0f;
    setterAnimation.animRotationY = -180.5f;

    if (currentAnimMode == 2) {
        return 1;
    }

    int sequenceFrame = setterAnimation.sequenceFrameCount;
    if (sequenceFrame == 0) {
        for (int i = 0; i < pinCount; i++) {
            pPinManager->pPinBodies[i]->mode_0x28C = 0;
        }

        float z = throwContext.ballMtx._23;
        float y = throwContext.ballMtx._13;
        float x = throwContext.ballMtx._03;
        nw4r::math::VEC3 ballPos(x, y, z);

        if (ballPos.z < SWEEPER_BALL_Z_TRIGGER) {
            pPinSetter->mSequencePhase = 1;
        }
        return 1;
    }

    if (currentAnimMode != 0) {
        return 1;
    }

    if (sequenceFrame == 1 && setterAnimation.isNewRack == 0) {
        pPinSetter->mSequencePhase = 2;
    }

    if (setterAnimation.sequenceFrameCount == SWEEPER_FRAME_LIFT_PINS && setterAnimation.isNewRack == 0) {
        for (int i = 0; i < pinCount; i++) {
            if (pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pPinManager->pPinBodies[i]->mode_0x28C = 1;
            }
        }
    }

    if (setterAnimation.sequenceFrameCount == SWEEPER_FRAME_START_SWEEP) {
        pPinSetter->mSequencePhase = 3;
    }

    if (setterAnimation.sequenceFrameCount > SWEEPER_FRAME_START_SWEEP) {
        setterAnimation.animOffsetZ = 0.28f * ((float)setterAnimation.sequenceFrameCount - (float)SWEEPER_FRAME_START_SWEEP);
    }

    if (setterAnimation.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && setterAnimation.isNewRack == 0) {
        for (int i = 0; i < pinCount; i++) {
            if (pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pPinManager->pPinBodies[i]->mode_0x28C = 3;
            }
        }
    }

    if (setterAnimation.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && setterAnimation.isNewRack != 0) {
        for (int i = 0; i < pinCount; i++) {
            pPinManager->pPinBodies[i]->VF_0x0C();

            nw4r::math::VEC3 basisZ;
            nw4r::math::VEC3 basisY;
            nw4r::math::VEC3 basisX;

            pPinManager->pPinBodies[i]->isActive = 1;

            PinPhysicsBody* pBody = pPinManager->pPinBodies[i];
            nw4r::math::VEC3 pos = pBody->field_0xFC;
            pos.y = 8.0f;

            pBody->state.position = pos;

            basisX.x = 1.0f;
            basisX.y = 0.0f;
            basisX.z = 0.0f;
            pBody->state.basisX = basisX;

            basisY.x = 0.0f;
            basisY.y = 1.0f;
            basisY.z = 0.0f;
            pBody->state.basisY = basisY;

            basisZ.x = 0.0f;
            basisZ.y = 0.0f;
            basisZ.z = 1.0f;
            pBody->state.basisZ = basisZ;

            pPinManager->pPinBodies[i]->mode_0x28C = 3;
        }
    }

    setterAnimation.sequenceFrameCount++;
    return 1;
}

/**
 * @brief Tests whether the pin setter is currently active
 *
 * @return 1 if active, 0 otherwise
 */
int LaneContext::IsPinSetterActive() {
    int frame = setterAnimation.sequenceFrameCount;
    if (frame != 0 && frame < SWEEPER_FRAME_END) {
        return 1;
    }
    return 0;
}

/**
 * @brief Unknown function (stubbed)
 */
void LaneContext::fn_803345F0() {
    ;
}
