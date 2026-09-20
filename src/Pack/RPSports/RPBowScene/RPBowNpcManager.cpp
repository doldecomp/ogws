#include <Pack/RPSports/RPBowScene/bowling.h>

extern "C" int rand();

// Extern symbols
extern u8 lbl_804BF998;
extern u32 lbl_80392C08[];

// Extern functions:
void fn_80334270(RPBowNpcContext* pContext);
void InitNpcContext(RPBowNpcContext* pContext, int laneIdx, int npcIdx);
void fn_80324994(PinStatus* pPinStatus, LaneContext* pLaneContext);
void CalculateNpcBallTransform(nw4r::math::MTX34* pOutMtx, const RPBowNpcContext* pContext);
void CalculateNpcThrowVelocity(nw4r::math::VEC3* pOutVelocity, const RPBowNpcManager* pLane, const nw4r::math::VEC3* pBallPosition, const PinStatus* pPinStatus);
void UpdateNpcLane(u8* pUpdateData, const RPBowNpcContext* pContext);

typedef void (*PlaySoundFunc)(void*, int, int);
typedef void (*UpdateSoundFunc)(void*, void*);

#define PLAY_SOUND(id) ((PlaySoundFunc)(*(void***)((u8*)mpSoundAudioMgr + 0x78))[24])(mpSoundAudioMgr, id, 0)

/**
 * @brief Initializes audio-related structures for the manager
 * @details Allocates memory for sound actors and configures 3D audio settings.
 *
 * @param laneIdx Index of the lane
 */
void RPBowNpcManager::InitAudioActors(int laneIdx) {
    // TODO: Stub
    laneIdx = laneIdx;
}

/**
 * @brief Configures internal pointers and prepares initial contexts
 *
 * @param pLaneContext Pointer to the lane physics and gameplay context
 * @param pNpc0 Pointer to the first NPC object
 * @param pNpc1 Pointer to the second NPC object
 * @param pNpc2 Pointer to the third NPC object
 * @param laneIdx Lane index
 * @param pReturnRack Rack containing usable balls
 * @param pAudioStruct Pointer to the audio structure
 */
void RPBowNpcManager::Setup(LaneContext* pLaneContext, RPBowNpcContext* pNpc0, RPBowNpcContext* pNpc1, RPBowNpcContext* pNpc2, int laneIdx, RPBowBallReturnRack* pReturnRack, void* pAudioStruct) {
    mpNpcs[0] = pNpc0;
    mpNpcs[1] = pNpc1;
    mpNpcs[2] = pNpc2;

    mpLaneContext = pLaneContext;
    mLaneIdx = laneIdx;
    mpReturnRack = pReturnRack;
    mpSomeAudioStruct = pAudioStruct;

    memset(&mStateId, 0, 12);

    for (int i = 0; i < 3; i++) {
        mpNpcs[i]->fn_80334270();
        mpNpcs[i]->InitNpcContext(mLaneIdx, i);
    }

    mpCurrentNpc = mpNpcs[0];
    mCurrentNpcIdx = 0;
}

/**
 * @brief Tests whether the lane is idle
 *
 * @return 1 if idle, 0 otherwise
 */
int RPBowNpcManager::IsLaneIdle() {
    return mStateId == 0;
}

/**
 * @brief Sets the NPC state flag
 *
 * @param flag Status value applied
 */
void RPBowNpcManager::SetStateFlag(u8 flag) {
    mDisableResultSfx = flag;
}

/**
 * @brief Activates a new NPC turn for the lane
 * @details Cycles to the next NPC in the lane (0->1->2->0).
 */
void RPBowNpcManager::ActivateNpcTurn() {
    memset(&mStateId, 0, 12);
    mStateId = 1;
    mStateTimer = -1;
    mpLaneContext->throwContext.throwState = 0;

    mpCurrentNpc = mpNpcs[mCurrentNpcIdx];

    int nextIdx = mCurrentNpcIdx; // TODO: remove?
    mCurrentNpcIdx = mCurrentNpcIdx + 1;
    if (mCurrentNpcIdx == 3) {
        mCurrentNpcIdx = 0;
    }
}

// States for RPBowNpcManager::Update()
enum NpcBowlingStates {
    NPC_BOWLING_STATE_IDLE = 0,               // Inactive, ball hidden off-screen
    NPC_BOWLING_STATE_WAIT_PREPARE_LINE = 1,  // Walk to approach area, pick up ball
    NPC_BOWLING_STATE_PREPARE = 2,            // Idle at line, RNG delay before bowling
    NPC_BOWLING_STATE_RUN = 3,                // Swing and release ball
    NPC_BOWLING_STATE_SEE = 4,                // Watch ball roll, handle result SFX
    NPC_BOWLING_STATE_BACK = 5,               // Walk to ball return or back to seat
};

/**
 * @brief Updates the manager's state machine
 */
void RPBowNpcManager::Update() {
    if (mStateTimer < 0) {
        mStateTimer = 0;
    }

    switch (mStateId) {
        case NPC_BOWLING_STATE_IDLE: { // IDLE
            nw4r::math::MTX34 mtx;
            mtx.m[2][3] = 9999.0f;
            mpLaneContext->throwContext.ballMtx = mtx;
            mActiveSubObjIdx = -1;
            break;
        }

        case NPC_BOWLING_STATE_WAIT_PREPARE_LINE: { // WAIT_PREPARE_LINE
            if (mActiveSubObjIdx < 0) {
                mActiveSubObjIdx = mpReturnRack->SelectBallForNPC();
            }

            if (mActiveSubObjIdx >= 0) {
                mpCurrentNpc->actionState.targetZPos =
                    mpReturnRack->mBalls[mActiveSubObjIdx].mPos.z +
                    gBallReturnRackConstants.mPositionOffsets[mpReturnRack->mRackIndex].z;
            } else {
                mpCurrentNpc->actionState.targetZPos = -999.0f;
            }

            if (mStateTimer == 0) {
                mpCurrentNpc->actionState.npcState = NPC_STATE_WALK_TO_APPROACH_AREA;
                mpCurrentNpc->actionState.stateFrameCounter = -1;
                mpCurrentNpc->actionState.triggerTransition = false;
            }

            if (mpCurrentNpc->actionState.triggerTransition) {
                mStateId = 2;
                mStateTimer = -1;
            }

            if (mpCurrentNpc->isHoldingBall != 0) {
                mpLaneContext->throwContext.throwState = 0;
                *(s32*)((u8*)mpSomeAudioStruct + 0x78) = mpReturnRack->GetBallSlotIndex(mActiveSubObjIdx);

                if (mpReturnRack->IsBallOnRack(mActiveSubObjIdx)) {
                    mpReturnRack->RemoveBallFromRack(mActiveSubObjIdx);
                }
            }

            mHasReleasedBall = false;
            break;
        }

        case NPC_BOWLING_STATE_PREPARE: { // PREPARE
            if ((rand() % 100) != 0) break;
            if (mStateTimer <= 80) break;
            if (!mpLaneContext->IsPinSetterActive()) break;

            mStateId = 3;
            mStateTimer = -1;
            break;
        }

        case NPC_BOWLING_STATE_RUN: { // RUN
            if (mStateTimer == 0) {
                mpCurrentNpc->actionState.npcState = NPC_STATE_BOWL;
                mpCurrentNpc->actionState.stateFrameCounter = -1;
                mpCurrentNpc->actionState.triggerTransition = false;

                mpLaneContext->ResetPinSetterState(mIsSecondThrow);
                mHasPlayedGutterSfx = false;

                if (mIsSecondThrow) {
                    PinStatus tempStatus;
                    fn_80324994(&tempStatus, mpLaneContext);
                    mpLaneContext->fn_80327330(&tempStatus);
                } else {
                    PinStatus tempArray;
                    tempArray.pinBits[0] = -1;
                    tempArray.pinBits[1] = -1;
                    tempArray.pinBits[2] = -1;
                    tempArray.pinBits[3] = -1;
                    tempArray.pinCount = 10;
                    mpLaneContext->fn_80327330(&tempArray);
                }
            }

            if (mpCurrentNpc->actionState.triggerThrow) {
                mpCurrentNpc->actionState.triggerThrow = false;

                nw4r::math::MTX34 mtx3;
                nw4r::math::MTX34 mtx2;
                nw4r::math::MTX34 mtx1;

                CalculateNpcBallTransform(&mtx1, mpCurrentNpc);
                f32 z = mtx1.m[2][3];

                CalculateNpcBallTransform(&mtx2, mpCurrentNpc);
                f32 y = mtx2.m[1][3];

                CalculateNpcBallTransform(&mtx3, mpCurrentNpc);
                f32 x = mtx3.m[0][3];

                nw4r::math::VEC3 ballPosition;
                ballPosition.x = x;
                ballPosition.y = y;
                ballPosition.z = z;

                nw4r::math::VEC3 velocity;
                if (mIsSecondThrow) {
                    nw4r::math::VEC3 velocityCopy;
                    CalculateNpcThrowVelocity(&velocityCopy, 0, &ballPosition, &mPinStatus);
                    velocity = velocityCopy;
                } else {
                    PinStatus tempPinStatus;
                    tempPinStatus.pinBits[0] = -1;
                    tempPinStatus.pinBits[1] = -1;
                    tempPinStatus.pinBits[2] = -1;
                    tempPinStatus.pinBits[3] = -1;
                    tempPinStatus.pinCount = 10;

                    nw4r::math::VEC3 velocityCopy;
                    CalculateNpcThrowVelocity(&velocityCopy, 0, &ballPosition, &tempPinStatus);
                    velocity = velocityCopy;
                }

                nw4r::math::VEC3 finalVelocity = velocity;
                mpLaneContext->fn_80324DD0(&finalVelocity, 0);
                mHasReleasedBall = true;
            }

            if (mpCurrentNpc->actionState.triggerTransition) {
                mStateId = 4;
                mStateTimer = -1;
            }
            break;
        }

        case NPC_BOWLING_STATE_SEE: { // SEE
            u32 arr[11];
            PinStatus pinStatus;
            PinStatus pinStatusCopy;

            if (!mHasPlayedGutterSfx &&
                mpLaneContext->throwContext.isGutterBall != 0 &&
                !mDisableResultSfx) {

                PLAY_SOUND(0x34);
                mHasPlayedGutterSfx = true;
            }

            if (!mpLaneContext->fn_80324B10()) break;

            mpReturnRack->SpawnBallOnRack(mActiveSubObjIdx);
            mActiveSubObjIdx = -1;
            mStateId = 5;
            mStateTimer = -1;

            fn_80324994(&pinStatus, mpLaneContext);

            if (!mDisableResultSfx) {
                if (!mIsSecondThrow) {
                    int count1 = pinStatus.GetStandingPinCount();
                    if (count1 == 0) {
                        PLAY_SOUND(0x2F);
                        PLAY_SOUND(0x50);
                    } else {
                        int count2 = pinStatus.GetStandingPinCount();
                        if (count2 <= 3) {
                            PLAY_SOUND(0x31);
                        } else {
                            int count3 = pinStatus.GetStandingPinCount();
                            if (count3 <= 9) {
                                PLAY_SOUND(0x32);
                            }
                        }
                    }
                } else {
                    int count1 = pinStatus.GetStandingPinCount();
                    if (count1 == 0) {
                        int r0 = 0;
                        if (lbl_804BF998 != 0) {
                            r0 = 1;
                        } else if ((mPinStatus.pinBits[0] & 1) == 0) {
                            r0 = 0;
                        } else {
                            for (int i = 0; i < 11; i++) {
                                arr[i] = lbl_80392C08[i];
                            }

                            u32 mask = 0;
                            for (int i = 0; i < mPinStatus.pinCount; i++) {
                                if (mPinStatus.pinBits[i / 30] & (1 << (i % 30))) {
                                    mask |= (1 << arr[i]);
                                }
                            }

                            r0 = 0;
                            for (int i = 0; i < 5; i++) {
                                if ((mask & (1 << i)) != 0 && (mask & (1 << (i + 1))) == 0) {
                                    for (int j = i + 2; j < 7; j++) {
                                        if ((mask & (1 << j)) != 0) {
                                            r0 = 1;
                                            goto end_split_check;
                                        }
                                    }
                                }
                            }
                        end_split_check:;
                        }

                        if (r0 != 0) {
                            PLAY_SOUND(0x33);
                            PLAY_SOUND(0x52);
                        } else {
                            PLAY_SOUND(0x30);
                            PLAY_SOUND(0x51);
                        }
                    } else {
                        int count2 = pinStatus.GetStandingPinCount();
                        int count3 = pinStatus.GetStandingPinCount();

                        if (count2 == count3) {
                            PLAY_SOUND(0x36);
                        } else if (mHasPlayedGutterSfx) {
                            PLAY_SOUND(0x35);
                        }
                    }
                }
            }

            fn_80324994(&pinStatusCopy, mpLaneContext);
            mPinStatus = pinStatusCopy;
            break;
        }

        case NPC_BOWLING_STATE_BACK: { // BACK
            if (mStateTimer == 0) {
                if (!mIsSecondThrow) {
                    PinStatus tempStatus;
                    fn_80324994(&tempStatus, mpLaneContext);
                    if (tempStatus.GetStandingPinCount() == 0) {
                        mShouldReturnToSeat = true;
                    } else {
                        mShouldReturnToSeat = false;
                    }
                } else {
                    mShouldReturnToSeat = false;
                }
            }

            if (mStateTimer == 0) {
                if (mShouldReturnToSeat) {
                    PinStatus tempStatus2;
                    fn_80324994(&tempStatus2, mpLaneContext);
                    if (tempStatus2.GetStandingPinCount() == 0) {
                        mpCurrentNpc->flag_A5 = 1;
                    } else {
                        mpCurrentNpc->flag_A5 = 0;
                    }

                    mpCurrentNpc->actionState.npcState = NPC_STATE_WALK_BACK_TO_SEAT;
                    mpCurrentNpc->actionState.stateFrameCounter = -1;
                    mpCurrentNpc->actionState.triggerTransition = false;
                } else {
                    mpCurrentNpc->actionState.npcState = NPC_STATE_WALK_TO_BALL_RETURN;
                    mpCurrentNpc->actionState.stateFrameCounter = -1;
                    mpCurrentNpc->actionState.triggerTransition = false;
                }
            }

            if (!mShouldReturnToSeat) {
                if (mActiveSubObjIdx < 0) {
                    mActiveSubObjIdx = mpReturnRack->SelectBallForNPC();
                }

                if (mActiveSubObjIdx >= 0) {
                    mpCurrentNpc->actionState.targetZPos =
                        mpReturnRack->mBalls[mActiveSubObjIdx].mPos.z +
                        gBallReturnRackConstants.mPositionOffsets[mpReturnRack->mRackIndex].z;
                } else {
                    mpCurrentNpc->actionState.targetZPos = -999.0f;
                }
            }

            if (!mShouldReturnToSeat && mpCurrentNpc->isHoldingBall != 0) {
                mpLaneContext->throwContext.throwState = 0;
                *(s32*)((u8*)mpSomeAudioStruct + 0x78) = mpReturnRack->GetBallSlotIndex(mActiveSubObjIdx);

                if (mpReturnRack->IsBallOnRack(mActiveSubObjIdx)) {
                    mpReturnRack->RemoveBallFromRack(mActiveSubObjIdx);
                }
            }

            if (mpCurrentNpc->actionState.triggerTransition) {
                if (mShouldReturnToSeat) {
                    if (mActiveSubObjIdx >= 0) {
                        mpReturnRack->ReleaseBallFromNPC(mActiveSubObjIdx);
                        mActiveSubObjIdx = -1;
                    }
                    mStateId = 0;
                    mStateTimer = -1;
                } else {
                    mIsSecondThrow = true;
                    mStateId = 2;
                    mStateTimer = -1;
                }
                mpLaneContext->throwContext.throwState = 0;
            }
            break;
        }
    }

    mStateTimer++;

    u8 updateStruct[0x4C];
    UpdateNpcLane(updateStruct, mpCurrentNpc);
    // mpCurrentNpc->UpdateNpcLane();

    ((UpdateSoundFunc)(*(void***)((u8*)mpSoundAudioMgr + 0x78))[18])(mpSoundAudioMgr, updateStruct);

    if (mpCurrentNpc->isHoldingBall != 0) {
        nw4r::math::MTX34 mtx;
        CalculateNpcBallTransform(&mtx, mpCurrentNpc);
        mpLaneContext->throwContext.ballMtx = mtx;
    }
}

struct StateStrings {
    const char* str[6];
};

// const char* lbl_80392C30[] = {
//     "IDLE",
//     "WAIT_PREPARE_LINE",
//     "PREPARE",
//     "RUN",
//     "SEE",
//     "BACK NPC[%d(%s)] %s  phy:%d\x00\x32\x6E\x64\x00\x31\x73\x74\x00\x00\x00\x00"
// };

extern StateStrings lbl_80392C30;
extern char lbl_80392C48[];

extern "C" void fn_801C38B8(char* pBuffer, int a, int b, float c, float d, float e);
extern float lbl_804C618C;

/**
 * @brief Prints debug information for this NPC manager
 * @details Example string formats: 'NPC[0(1st)] PREPARE phy:0'
 */
void RPBowNpcManager::DebugPrintNpcState() {
    StateStrings localStrings = lbl_80392C30;

    int laneCalc = (mLaneIdx * 20) + 100;

    char buffer[256];

    const char* pStr2 = (mIsSecondThrow) ? &lbl_80392C48[0x43] : &lbl_80392C48[0x47];
    int throwState = mpLaneContext->throwContext.throwState;

    sprintf(buffer, &lbl_80392C48[0x2C], mLaneIdx, pStr2, localStrings.str[mStateId], throwState);

    int VAL_400 = 400;
    fn_801C38B8(buffer, -1, 1, (float)VAL_400, (float)laneCalc, lbl_804C618C);
}
