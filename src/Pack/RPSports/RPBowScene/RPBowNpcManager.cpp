#include <Pack/RPSports/RPBowScene/bowling.h>

extern "C" int rand();

namespace Bowling {

// Extern functions:
void fn_80334270(NpcContext* pContext);
void InitNpcContext(NpcContext* pContext, int laneIdx, int npcIdx);

/**
 * @brief Initializes audio-related structures for the manager
 * @details Allocates memory for sound actors and configures 3D audio settings.
 *
 * @param laneIdx Index of the lane
 */
// void RPBowNpcManager::InitAudioActors(int laneIdx) {
//     ;
// }

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
void RPBowNpcManager::Setup(LaneContext* pLaneContext, NpcContext* pNpc0, NpcContext* pNpc1, NpcContext* pNpc2, int laneIdx, RPBowBallReturnRack* pReturnRack, void* pAudioStruct) {
    mpNpcs[0] = pNpc0;
    mpNpcs[1] = pNpc1;
    mpNpcs[2] = pNpc2;

    mpLaneContext = pLaneContext;
    mLaneIdx = laneIdx;
    mpReturnRack = pReturnRack;
    mpSomeAudioStruct = pAudioStruct;

    memset(&mStateId, 0, 12);

    for (int i = 0; i < 3; i++) {
        fn_80334270(mpNpcs[i]);
        InitNpcContext(mpNpcs[i], mLaneIdx, i);
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
// void RPBowNpcManager::Update() {
//     ;
// }

/**
 * @brief Prints debug information for this NPC manager
 * @details Example string formats: 'NPC[0(1st)] PREPARE phy:0'
 */
// void RPBowNpcManager::DebugPrintNpcState() {
//     ;
// }

} // namespace Bowling
