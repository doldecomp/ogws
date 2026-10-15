#include <Pack/RPSports/RPBowScene/bowling.h>

extern bool gGameStateFlag1_804BF9E8;
extern bool gGameStateFlag2_804BF9E9;

/**
 * @brief Min and max frame boundaries for pinsetter animation stages
 */
struct StageRange {
    f32 min;
    f32 max;
};

const StageRange scStageRanges[4] = {
    {   0.0f,   0.0f },
    {   0.0f,  51.0f },
    {  75.0f, 250.0f },
    { 250.0f, 505.0f },
};

/**
 * @brief Destructor
 */
RPBowPinSetterModel::~RPBowPinSetterModel() {}

/**
 * @brief Sets the visual models for the pinsetter
 *
 * @param pModel0 Main pinsetter model
 * @param pModel1 Reflection pinsetter model
 */
void RPBowPinSetterModel::SetModels(RPGrpModel* pModel0, RPGrpModel* pModel1) {
    mpModel[0] = pModel0;
    mpModel[1] = pModel1;
}

/**
 * @brief Resets the pinsetter's animation and state tracking variables
 */
void RPBowPinSetterModel::Reset() {
    for (int i = 0; i < 2; i++) {
        mpModel[i]->GetModelAnm()->Start(RPGrpModelAnm::Anm_Chr, 0, 0.0f);
        mpModel[i]->GetModelAnm()->SetUpdateRate(RPGrpModelAnm::Anm_Chr, 0, 0.0f);
    }

    mPrimaryState = 0;
    mSequencePhase = 0;
    mAngle = -175.0f;
    mFrameTimer = 0.0f;

    gGameStateFlag1_804BF9E8 = false;
    gGameStateFlag2_804BF9E9 = false;
}

/**
 * @brief Sets the world position offset of the pinsetter
 *
 * @param x X-axis offset
 * @param z Z-axis offset
 */
void RPBowPinSetterModel::SetOffsetXZ(f32 x, f32 z) {
    nw4r::math::VEC3 trans(x, 0.0f, z);
    MTX34Identity(&mMtx);
    MTX34Trans(&mMtx, &trans, &mMtx);
}

/**
 * @brief Calculates animation progression and updates the model transformation matrices
 */
void RPBowPinSetterModel::Calc() {
    struct StageRangeArray {
        float data[8];
    };

    StageRangeArray stageRanges;

    float* pMax = &stageRanges.data[1];

    stageRanges = *(StageRangeArray*)scStageRanges;

    float maxVal = pMax[mPrimaryState * 2];

    bool reachedTarget = false;
    if (!(mFrameTimer < maxVal)) {
        mFrameTimer = maxVal;
        reachedTarget = true;
    } else {
        mFrameTimer += 1.0f;
    }

    if (mPrimaryState != mSequencePhase && reachedTarget) {
        mPrimaryState = mSequencePhase;
        mFrameTimer = stageRanges.data[mSequencePhase * 2];
    }

    if (!gGameStateFlag1_804BF9E8) {
        if (mFrameTimer < 0.1f || mFrameTimer > 504.0f) {
            return;
        }
    }

    for (int i = 0; i < 2; ++i) {
        mpModel[i]->GetModelAnm()->SetFrame(RPGrpModelAnm::Anm_Chr, 0, mFrameTimer);
    }

    nw4r::math::MTX34 mtx0 = mMtx;

    if (mpModel[0]->GetScnObj() != NULL) {
        mpModel[0]->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mtx0);
    }
    mpModel[0]->UpdateFrame();
    mpModel[0]->Calc();

    nw4r::math::MTX34 mtx1 = mtx0;
    const f32 neg = -1.0f;
    mtx1._10 *= neg;
    mtx1._11 *= neg;
    mtx1._12 *= neg;
    mtx1._13 *= neg;

    if (mpModel[1]->GetScnObj() != NULL) {
        mpModel[1]->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mtx1);
    }
    mpModel[1]->UpdateFrame();
    mpModel[1]->Calc();
    mpModel[1]->Entry();

    if (!(std::fabs(mMtx._03) < 0.1f && gGameStateFlag2_804BF9E9)) {
        mpModel[0]->Entry();
    }
}
