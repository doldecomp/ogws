#include <Pack/RPSports/RPBowScene/bowling.h>
#include <Pack/RPUtility/RPUtlRandom.h>

#define nullptr 0

namespace Bowling {

// Forward declarations
extern u8 lbl_804BF9F8;
extern u32 lbl_804BF9F4;

void fn_8034CFC4(NpcIdleState* pIdleState, int param_2, int param_3);
NpcIdleStateSub* fn_8034C95C(NpcIdleState* pIdleState);

BackgroundNpcConfig gBackgroundNpcParams;

class RPGrpModelAccessor : public RPGrpModel {
public:
    static RPGrpModelAnm* GetModelAnm(RPGrpModel* pModel) {
        return pModel->*(&RPGrpModelAccessor::mpModelAnm);
    }

    static void SetScale(RPGrpModel* pModel, const nw4r::math::VEC3& rScale) {
        pModel->*(&RPGrpModelAccessor::mBaseScale) = rScale;
    }
};

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034E96C() {
    ;
}

/**
 * @brief Destructor
 */
RPBowBackgroundNpcManager::~RPBowBackgroundNpcManager() {}

/**
 * @brief Initializes the background NPC configuration
 *
 * @param index Lane index
 */
void RPBowBackgroundNpcManager::InitializeConfig(int index) {
    mConfigIndex = index;

    gBackgroundNpcParams.laneZPositions[0] = 92.0f;
    gBackgroundNpcParams.laneZPositions[1] = 99.0f;
    gBackgroundNpcParams.laneZPositions[2] = 106.0f;
    gBackgroundNpcParams.laneZPositions[3] = 113.0f;

    gBackgroundNpcParams.basePosY = 3.85f;
    gBackgroundNpcParams.seatedPosY = 2.0f;
    gBackgroundNpcParams.mirroredModelZOffset = 6.5f;
    gBackgroundNpcParams.patrolMinX = -120.0f;
    gBackgroundNpcParams.patrolMaxX = 120.0f;
    gBackgroundNpcParams.minWalkSpeed = 0.07f;
    gBackgroundNpcParams.maxWalkSpeed = 0.25f;

    gBackgroundNpcParams.dormantToPatrolChanceDenom = 200;
    gBackgroundNpcParams.patrolToIdleChanceDenom = 400;
    gBackgroundNpcParams.idleToPatrolChanceDenom = 300;

    gBackgroundNpcParams.turnLerpRate = 0.05f;
    gBackgroundNpcParams.idleCenterZoneX = 70.0f;

    gBackgroundNpcParams.minStateDuration = 120;
}

/**
 * @brief Sets the model groups for the manager
 *
 * @param managerIndex Manager index
 * @param pModelGroup0 First model group
 * @param pModelGroup1 Second model group
 */
void RPBowBackgroundNpcManager::SetModelGroups(int managerIndex, NpcModelGroup* pModelGroup0, NpcModelGroup* pModelGroup1) {
    mModelGroups[managerIndex][0] = pModelGroup0;
    mModelGroups[managerIndex][1] = pModelGroup1;
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034E83C() {
    ;
}

/**
 * @brief Resets the manager state
 */
void RPBowBackgroundNpcManager::Reset() {
    mModelGroupSet = 0;
    *(volatile int*)&mMovement.animationState = -1;
    *(volatile int*)&mMovement.animationState = 0;

    for (int i = 0; i < 2; i++) {
        NpcModelGroup* pGroup = mModelGroups[mModelGroupSet][i];
        RPGrpModelAnm* pAnimation = RPGrpModelAccessor::GetModelAnm(pGroup->mModelA8);
        pAnimation->StartBlend(RPGrpModelAnm::Anm_Chr, 0, 60.0f, 0.0f);
    }

    memset(&mMovement, 0, 0x30);

    mMovement.behaviorState = 0;
    mMovement.stateTimer = -1;

    fn_8034CFC4(&mIdleState, 999, 0);
    unk_0x94 = 0;

    for (int j = 0; j < 600; j++) {
        UpdateMovement(nullptr, nullptr);
    }

    lbl_804BF9F8 = 0;
}

/**
 * @brief Updates the movement state and calculates position
 *
 * @param pOutPosition[out] Output position
 * @param pOutStateFlag[out] Output state flag
 */
void RPBowBackgroundNpcManager::UpdateMovement(nw4r::math::VEC3* pOutPosition, bool* pOutStateFlag) {
    bool stateFlag = true;
    BackgroundNpcConfig* pConfig = &gBackgroundNpcParams;

    if (mMovement.stateTimer < 0) {
        mMovement.stateTimer = 0;
    }

    nw4r::math::VEC3 localVec(0.0f, 0.0f, 0.0f);

    switch (mMovement.behaviorState) {
        case 0:
        {
            if (RPUtlRandom::getU32(pConfig->dormantToPatrolChanceDenom) == 0) {
                mModelGroupSet = RPUtlRandom::getU32(2);
                if (mModelGroupSet >= 2) {
                    mModelGroupSet = 1;
                }
                mMovement.animationState = -1;
                mMovement.behaviorState = 1;
                mMovement.stateTimer = -1;
            }
            stateFlag = false;
            break;
        }

        case 1:
        {
            if (mMovement.stateTimer == 0) {
                f32 walkSpeed = pConfig->minWalkSpeed + RPUtlRandom::getF32() * (pConfig->maxWalkSpeed - pConfig->minWalkSpeed);
                if (RPUtlRandom::getU32(2) == 0) {
                    walkSpeed *= -1.0f;
                }

                mMovement.velocity.x = walkSpeed;
                mMovement.velocity.y = 0.0f;
                mMovement.velocity.z = 0.0f;

                if (walkSpeed < 0.0f) {
                    mMovement.position.x = pConfig->patrolMaxX;
                } else {
                    mMovement.position.x = pConfig->patrolMinX;
                }

                mMovement.position.y = pConfig->basePosY;
                mMovement.position.z = pConfig->laneZPositions[mConfigIndex];
            }

            if (mMovement.animationState != 1) {
                mMovement.animationState = 1;
                for (int i = 0; i < 2; i++) {
                    NpcModelGroup* pGroup = mModelGroups[mModelGroupSet][i];
                    RPGrpModelAnm* pAnimation = RPGrpModelAccessor::GetModelAnm(pGroup->mModelA8);

                    pAnimation->StartBlend(RPGrpModelAnm::Anm_Chr, 1, 60.0f, 0.0f);
                }
            }

            if (std::fabs(mMovement.position.x) < pConfig->idleCenterZoneX && (int)pConfig->minStateDuration < mMovement.stateTimer) {
                if (RPUtlRandom::getU32(pConfig->patrolToIdleChanceDenom) == 0) {
                    mMovement.behaviorState = 2;
                    mMovement.stateTimer = -1;
                }
            }

            f32 targetAngle;
            if (mMovement.velocity.x < 0.0f) {
                targetAngle = 270.0f;
            } else {
                targetAngle = 90.0f;
            }

            mMovement.rotation.y += pConfig->turnLerpRate * (targetAngle - mMovement.rotation.y);
            mMovement.position += mMovement.velocity;

            if (mMovement.position.x < pConfig->patrolMinX || mMovement.position.x > pConfig->patrolMaxX) {
                mMovement.behaviorState = 0;
                mMovement.stateTimer = -1;
            }
            break;
        }

        case 2:
        {
            if (mMovement.stateTimer == 0) {
                mIdleState.sub.field_0x2C = true;
                mIdleState.sub.unk_0x8 = lbl_804BF9F4;
            }

            if (mMovement.animationState != 0) {
                mMovement.animationState = 0;
                for (int i = 0; i < 2; i++) {
                    NpcModelGroup* pGroup = mModelGroups[mModelGroupSet][i];
                    RPGrpModelAnm* pAnimation = RPGrpModelAccessor::GetModelAnm(pGroup->mModelA8);

                    pAnimation->StartBlend(RPGrpModelAnm::Anm_Chr, 0, 60.0f, 0.0f);
                }
            }

            NpcIdleStateSub* pRet = fn_8034C95C(&mIdleState);
            localVec = pRet->pos;
            mMovement.rotation.y += pRet->rotationSpeed * (pRet->targetRotation - mMovement.rotation.y);

            if ((int)pConfig->minStateDuration < mMovement.stateTimer) {
                if (RPUtlRandom::getU32(pConfig->idleToPatrolChanceDenom) == 0) {
                    mMovement.behaviorState = 1;
                    mMovement.stateTimer = 0;

                    f32 walkSpeed = pConfig->minWalkSpeed + RPUtlRandom::getF32() * (pConfig->maxWalkSpeed - pConfig->minWalkSpeed);
                    if (RPUtlRandom::getU32(2) == 0) {
                        walkSpeed *= -1.0f;
                    }
                    mMovement.velocity.x = walkSpeed;
                }
            }
            break;
        }
    }

    mMovement.stateTimer++;

    if (pOutPosition != nullptr) {
        *pOutPosition = localVec;
    }
    if (pOutStateFlag != nullptr) {
        *pOutStateFlag = stateFlag;
    }
}

//! Gets the face model
#define GET_FACE(pKokeshi) ((pKokeshi)->mModelA4)
//! Gets the body model
#define GET_BODY(pKokeshi) ((pKokeshi)->mModelA8)
//! Gets the left hand model
#define GET_LHAND(pKokeshi) ((pKokeshi)->mModelAC)
//! Gets the right hand model
#define GET_RHAND(pKokeshi) ((pKokeshi)->mModelB0)

/**
 * @brief Renders the background NPC
 */
void RPBowBackgroundNpcManager::Render() {
    bool stateFlag = true;
    nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
    BackgroundNpcConfig* pConfig = &gBackgroundNpcParams;

    UpdateMovement(&position, &stateFlag);

    if (!stateFlag || !unk_0x94) {
        return;
    }

    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);

    position += mMovement.position;
    if (lbl_804BF9F8 != 0) {
        position.y += pConfig->seatedPosY - pConfig->basePosY;
    }

    nw4r::math::MTX34Trans(&mtx, &position, &mtx);

    nw4r::math::MTX34 mtx2;
    nw4r::math::MTX34RotXYZDeg(&mtx2, mMovement.rotation.x, mMovement.rotation.y, mMovement.rotation.z);

    nw4r::math::MTX34Mult(&mtx, &mtx, &mtx2);

    nw4r::math::VEC3 scale(0.7f, 0.7f, 0.7f);
    nw4r::math::MTX34 mtx3 = mtx;

    mtx3._10 *= -1.0f;
    mtx3._11 *= -1.0f;
    mtx3._12 *= -1.0f;
    mtx3._13 *= -1.0f;
    mtx3._13 += pConfig->mirroredModelZOffset;

    for (int i = 0; i < 2; i++) {
        NpcModelGroup* pGroup = mModelGroups[mModelGroupSet][i];

        nw4r::math::MTX34 leftHandMtx;
        nw4r::math::MTX34 rightHandMtx;
        nw4r::math::MTX34 headMtx;

        if (GET_BODY(pGroup)->GetScnObj() != nullptr) {
            GET_BODY(pGroup)->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, i == 0 ? &mtx : &mtx3);
        }
        RPGrpModelAccessor::SetScale(GET_BODY(pGroup), scale);
        GET_BODY(pGroup)->UpdateFrame();
        GET_BODY(pGroup)->Calc();

        RPSysKokeshi* pKokeshi = reinterpret_cast<RPSysKokeshi*>(pGroup);
        pKokeshi->GetHeadJointMtx(reinterpret_cast<EGG::Matrix34f*>(&headMtx));
        pKokeshi->GetLeftHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&leftHandMtx));
        pKokeshi->GetRightHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&rightHandMtx));

        if (i != 0) {
            nw4r::math::MTX34 flipMtx(
               -1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f
            );
            nw4r::math::MTX34Mult(&headMtx, &headMtx, &flipMtx);
        }

        if (GET_FACE(pGroup)->GetScnObj() != nullptr) {
            GET_FACE(pGroup)->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &headMtx);
        }
        RPGrpModelAccessor::SetScale(GET_FACE(pGroup), scale);
        GET_FACE(pGroup)->UpdateFrame();
        GET_FACE(pGroup)->Calc();

        if (GET_LHAND(pGroup)->GetScnObj() != nullptr) {
            GET_LHAND(pGroup)->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &leftHandMtx);
        }
        RPGrpModelAccessor::SetScale(GET_LHAND(pGroup), scale);
        GET_LHAND(pGroup)->UpdateFrame();
        GET_LHAND(pGroup)->Calc();

        if (GET_RHAND(pGroup)->GetScnObj() != nullptr) {
            GET_RHAND(pGroup)->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &rightHandMtx);
        }
        RPGrpModelAccessor::SetScale(GET_RHAND(pGroup), scale);
        GET_RHAND(pGroup)->UpdateFrame();
        GET_RHAND(pGroup)->Calc();

        if (i == 1 && !lbl_804BF9F8) {
            break;
        }

        GET_BODY(pGroup)->Entry();
        GET_FACE(pGroup)->Entry();
        GET_LHAND(pGroup)->Entry();
        GET_RHAND(pGroup)->Entry();
    }
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034DD14() {
    ;
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034DD0C() {
    ;
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034DD08() {
    ;
}

} // namespace Bowling
