#include <Pack/RPSports/RPBowScene/bowling.h>

/**
 * @brief Tests whether the active entry is null
 *
 * @return true if there is no active entry, false otherwise
 */
bool RPBowBallHistoryManager::IsActiveEntryNull() {
    return pActiveEntry == NULL;
}

/**
 * @brief Constructor
 */
RPBowBallHistoryEntry::RPBowBallHistoryEntry() {
    currentState[3] = 0.00000011920929f;
    currentState[4] = 0.00000011920929f;
    currentState[5] = 0.0f;
    currentState[6] = 0.0f;
}

/**
 * @brief Destructor
 */
RPBowBallHistoryEntry::~RPBowBallHistoryEntry() {}

/**
 * @brief Constructor
 */
ThrowPosState_B::ThrowPosState_B() {}

/**
 * @brief Allocates the history arrays based on the requested count
 *
 * @param count Number of entries to allocate
 */
void RPBowBallHistoryManager::Allocate(u32 count) {
    maxCount = count;
    maxCount8 = count * 8;

    if (count != 0) {
        limit20B = 100;

        pEntries = new RPBowBallHistoryEntry[count];
        pArray20A = new ThrowPosState_A[maxCount8];
        pArray20B = new ThrowPosState_B[limit20B];
    } else {
        limit20B = 0;
        pEntries = NULL;
        pArray20A = NULL;
        pArray20B = NULL;
    }
}

/**
 * @brief Resets the manager indices and pointers
 */
void RPBowBallHistoryManager::Reset() {
    currentIndex = 0;
    pActiveEntry = NULL;
    index20A = 0;
    index20B = 0;
}

/**
 * @brief Records a new physics state into the history
 *
 * @param pSrc Source physics state
 */
void RPBowBallHistoryManager::RecordState(BallPhysicsState* pSrc) {
    RPBowBallHistoryEntry *pDst;
    BallPhysicsState **new_var;
    u32 idx;

    if (pEntries == NULL) {
        return;
    }

    idx = currentIndex;
    if (((s32)idx) >= ((s32)maxCount)) {
        return;
    }
    currentIndex = idx + 1;

    pDst = &pEntries[idx];
    pActiveEntry = pDst;

    pDst->unk_0 = pSrc->unk_60;

    // this whole section just feels like one massive fakematch...

    pDst->currentState[0]   = pSrc->currentState[0];
    pDst->currentState[1]   = pSrc->currentState[1];
    pDst->currentState[2]   = pSrc->currentState[2];
    pDst->currentState[3]   = pSrc->currentState[3];
    pDst->currentState[4]   = pSrc->currentState[4];
    pDst->currentState[5]   = pSrc->currentState[5];
    pDst->currentState[6]   = pSrc->currentState[6];
    pDst->currentState[7]   = pSrc->currentState[7];
    pDst->currentState[8]   = pSrc->currentState[8];
    pDst->currentState[9]   = pSrc->currentState[9];
    pDst->currentState[10]  = pSrc->currentState[10];
    pDst->currentState[11]  = pSrc->currentState[11];
    pDst->currentState[12]  = pSrc->currentState[12];
    pDst->currentState[13]  = pSrc->currentState[13];
    pDst->currentState[14]  = pSrc->currentState[14];
    pDst->currentState[15]  = pSrc->currentState[15];
    pDst->currentState[16]  = pSrc->currentState[16];
    pDst->currentState[17]  = pSrc->currentState[17];
    pDst->currentState[18]  = pSrc->currentState[18];
    pDst->currentState[19]  = pSrc->currentState[19];
    pDst->currentState[20]  = pSrc->currentState[20];
    pDst->currentState[21]  = pSrc->currentState[21];
    pDst->currentState[22]  = pSrc->currentState[22];
    pDst->currentState[23]  = pSrc->currentState[23];
    pDst->currentState[24]  = pSrc->currentState[24];
    pDst->currentState[25]  = pSrc->currentState[25];
    pDst->currentState[26]  = pSrc->currentState[26];
    pDst->currentState[27]  = pSrc->currentState[27];
    pDst->currentState[28]  = pSrc->currentState[28];
    pDst->currentState[29]  = pSrc->currentState[29];
    pDst->currentState[30]  = pSrc->currentState[30];
    pDst->currentState[31]  = pSrc->currentState[31];
    pDst->currentState[32]  = pSrc->currentState[32];
    pDst->currentState[33]  = pSrc->currentState[33];
    pDst->currentState[34]  = pSrc->currentState[34];
    pDst->currentState[35]  = pSrc->currentState[35];
    pDst->currentState[36]  = pSrc->currentState[36];
    pDst->currentState[37]  = pSrc->currentState[37];

    pDst->previousState[0]  = pSrc->previousState[0];
    pDst->previousState[1]  = pSrc->previousState[1];
    pDst->previousState[2]  = pSrc->previousState[2];
    pDst->previousState[3]  = pSrc->previousState[3];
    pDst->previousState[4]  = pSrc->previousState[4];
    pDst->previousState[5]  = pSrc->previousState[5];
    pDst->previousState[6]  = pSrc->previousState[6];
    pDst->previousState[7]  = pSrc->previousState[7];
    pDst->previousState[8]  = pSrc->previousState[8];
    pDst->previousState[9]  = pSrc->previousState[9];
    pDst->previousState[10] = pSrc->previousState[10];
    pDst->previousState[11] = pSrc->previousState[11];
    pDst->previousState[12] = pSrc->previousState[12];
    pDst->previousState[13] = pSrc->previousState[13];

    // TODO: fakematch
    pDst->previousState[14] = (*(new_var = &pSrc))->previousState[14];
    pDst->previousState[15] = (*new_var)->previousState[15];
    pDst->previousState[16] = (*new_var)->previousState[16];
    pDst->previousState[17] = (*new_var)->previousState[17];
    pDst->previousState[18] = (*new_var)->previousState[18];

    pActiveEntry->throwCount = 0;
    pActiveEntry->flag_114 = 0;
}

/**
 * @brief Sets rotational/positional vectors for the active entry
 *
 * @param pVec1 First vector
 * @param pVec2 Second vector
 * @param pVec3 Third vector
 */
void RPBowBallHistoryManager::SetVectors(nw4r::math::VEC3* pVec1, nw4r::math::VEC3* pVec2, nw4r::math::VEC3* pVec3) {
    float f0, f1, f2;
    if (!pActiveEntry) {
        return;
    }

    // TODO: fakematch
    RPBowBallHistoryEntry* pTempEntry = pActiveEntry;

    f0 = pVec1->x;
    f1 = pVec1->y;
    pTempEntry->vec1.x = f0;
    f0 = pVec1->z;
    pTempEntry->vec1.y = f1;
    f2 = pVec2->x;
    pTempEntry->vec1.z = f0;
    f1 = pVec2->y;

    pTempEntry = pActiveEntry;

    f0 = pVec2->z;
    pTempEntry->vec2.x = f2;
    f2 = pVec3->x;
    pTempEntry->vec2.y = f1;
    f1 = pVec3->y;
    pTempEntry->vec2.z = f0;
    f0 = pVec3->z;

    pTempEntry = pActiveEntry;

    pTempEntry->vec3.x = f2;
    pTempEntry->vec3.y = f1;
    pTempEntry->vec3.z = f0;

    pActiveEntry->flag_114 = 1;
}

/**
 * @brief Copies an array of position states into the manager's A array
 *
 * @param pSrcArr Source array
 * @param count Number of elements to copy
 */
void RPBowBallHistoryManager::AddThrowPosStateA(ThrowPosState_A* pSrcArr, int count) {
    if (!pActiveEntry) return;

    pActiveEntry->index20A = index20A;
    pActiveEntry->throwCount = count;

    for (int i = 0; i < count; i++) {
        if ((int)index20A < (int)maxCount8) {
            pArray20A[index20A] = *pSrcArr;
            index20A++;
        }
        pSrcArr++;
    }
}

/**
 * @brief Appends a state into the manager's B array
 *
 * @param val1 Flag value
 * @param pVec1 First vector
 * @param pVec2 Second vector
 */
void RPBowBallHistoryManager::AddThrowPosStateB(u8 val1, nw4r::math::VEC3* pVec1, nw4r::math::VEC3* pVec2) {
    float new_var;
    if (pArray20B && (int)index20B < (int)limit20B) {

        ThrowPosState_B* pTarget = &pArray20B[index20B++];

        f32 v1x = pVec1->x;
        pTarget->flag_04 = val1;

        // TODO: fakematch
        new_var = pVec1->y;
        f32 v1y = new_var;
        pTarget->vec1.x = v1x;

        f32 v1z = pVec1->z;
        pTarget->vec1.y = v1y;

        f32 v2x = pVec2->x;
        pTarget->vec1.z = v1z;

        f32 v2y = pVec2->y;
        pTarget->vec2.x = v2x;

        f32 v2z = pVec2->z;
        pTarget->vec2.y = v2y;

        pTarget->vec2.z = v2z;

        pTarget->field_00 = currentIndex;
    }
}
