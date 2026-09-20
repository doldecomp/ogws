#include <Pack/RPSports/RPBowScene/bowling.h>

// Extern functions:
bool fn_801C3490(nw4r::math::MTX34* pMtxA, nw4r::math::VEC3* pPos);

extern char lbl_803C5428[];
extern char lbl_803C5418[];

/**
 * @brief Destructor
 */
RPBowRegularPinManager::~RPBowRegularPinManager() {}

/**
 * @brief Initializes the main pin models
 *
 * @param pRealModel Physical scene model
 * @param pReflectionModel Reflection visual model
 */
void RPBowRegularPinManager::InitializeModels(RPGrpModel* pRealModel, RPGrpModel* pReflectionModel) {
    mModels[0] = pRealModel;
    mModels[1] = pReflectionModel;

    mModels[0]->SetCallback(this);

    if (mModels[1] != NULL) {
        mModels[1]->SetCallback(this);
    }

    mModels[0]->CreateBoundingInfo(1);
}

/**
 * @brief Stub
 */
void RPBowRegularPinManager::fn_8034F440() {
    ;
}

/**
 * @brief Calculates bounding volume and shadow rendering matrices
 */
void RPBowRegularPinManager::Calc() {
    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);

    if (mUseShadows == 0) {
        mpShadowTexture->AddModel(mModels[0], 1.0f);

        nw4r::math::VEC3 minBox(0.0f, 0.0f, 0.0f);
        nw4r::math::VEC3 maxBox(0.0f, 0.0f, 0.0f);

        for (int i = 0; i < 10; i++) {
            nw4r::math::VEC3 pos(
                mMatrices[i][0]._03,
                mMatrices[i][0]._13,
                mMatrices[i][0]._23
            );

            if (i == 0 || minBox.x > pos.x) minBox.x = pos.x;
            if (i == 0 || minBox.y > pos.y) minBox.y = pos.y;
            if (i == 0 || minBox.z > pos.z) minBox.z = pos.z;

            if (i == 0 || maxBox.x < pos.x) maxBox.x = pos.x;
            if (i == 0 || maxBox.y < pos.y) maxBox.y = pos.y;
            if (i == 0 || maxBox.z < pos.z) maxBox.z = pos.z;
        }

        nw4r::math::VEC3 center = (minBox + maxBox) * 0.5f;

        float maxDist = 0.0f;
        for (int i = 0; i < 10; i++) {
            nw4r::math::VEC3 pos(
                mMatrices[i][0]._03,
                mMatrices[i][0]._13,
                mMatrices[i][0]._23
            );

            nw4r::math::VEC3 diff = pos - center;
            float dist = nw4r::math::VEC3Len(&diff);

            if (maxDist < dist) {
                maxDist = dist;
            }
        }

        if ((4.0f + maxDist) * 0.5f < 0.0f) {
            system_halt(lbl_803C5428, 191, lbl_803C5418);
        }

        // TODO: 0x74 is part of unknown block in eggShadowTexture.h
        *reinterpret_cast<f32*>((u8*)mpShadowTexture + 0x74) = (4.0f + maxDist) * 0.5f;

        mtx._03 = center.x;
        mtx._13 = center.y;
        mtx._23 = center.z;
    }

    for (int i = 0; i < 2; i++) {
        if (mModels[i] != NULL) {
            if (mModels[i]->GetModelEx()->getScnObj() != 0) {
                mModels[i]->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mtx);
            }
        }

        mModels[i]->UpdateFrame();
        mModels[i]->Calc();
        mModels[i]->Entry();
    }
}

/**
 * @brief Stub
 */
void RPBowRegularPinManager::fn_8034F164() {
    ;
}

/**
 * @brief Copies transformation matrices out to the target model
 *
 * @param pModel Target render model
 */
void RPBowRegularPinManager::CopyMatricesToModel(RPGrpModel* pModel) {
    for (int j = 0; j < 2; j++) {
        if (pModel == mModels[j]) {
            for (u16 i = 0; i < 10; i++) {
                nw4r::math::MTX34* pOutMtx = pModel->ReferWorldMtx(i + 1);
                *pOutMtx = mMatrices[i][j];
            }
        }
    }
}

/**
 * @brief Calculates individual transforms for regular pin positioning
 *
 * @param index Pin index
 * @param yOffset Y-axis position offset
 * @param pMtxA First check matrix
 * @param pMtxB Second transform matrix
 * @param pMtxC Third reference matrix
 */
void RPBowRegularPinManager::CalculatePinTransforms(int index, f32 yOffset, nw4r::math::MTX34* pMtxA, nw4r::math::MTX34* pMtxB, nw4r::math::MTX34* pMtxC) {
    nw4r::math::VEC3 checkVecs[6];

    nw4r::math::MTX34 transMtx1(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -yOffset,
        0.0f, 0.0f, 1.0f, 0.0f
    );

    nw4r::math::MTX34 outMtx1;
    nw4r::math::MTX34Mult(&outMtx1, pMtxB, &transMtx1);

    nw4r::math::VEC3 pos1(outMtx1._03, outMtx1._13, outMtx1._23);

    if (!fn_801C3490(pMtxA, &pos1)) {
        nw4r::math::MTX34 dummyMtx1(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -193.0f
        );
        mMatrices[index][0] = dummyMtx1;
    } else {
        mMatrices[index][0] = outMtx1;
    }

    if (pMtxB->_23 < -196.0f) {
        nw4r::math::MTX34 dummyMtx2(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -193.0f
        );
        mMatrices[index][1] = dummyMtx2;
        return;
    }

    nw4r::math::MTX34 localMtxB = *pMtxB;
    localMtxB._10 *= -1.0f;
    localMtxB._11 *= -1.0f;
    localMtxB._12 *= -1.0f;
    localMtxB._13 *= -1.0f;

    nw4r::math::MTX34 transMtx2(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -yOffset,
        0.0f, 0.0f, 1.0f, 0.0f
    );

    nw4r::math::MTX34 outMtx2;
    nw4r::math::MTX34Mult(&outMtx2, &localMtxB, &transMtx2);

    if (pMtxC != NULL) {
        checkVecs[0] = nw4r::math::VEC3(0.0f, 0.6f, 0.0f);
        checkVecs[1] = nw4r::math::VEC3(0.0f, 1.2f, 0.0f);
        checkVecs[2] = nw4r::math::VEC3(0.0f, 1.8f, 0.0f);
        checkVecs[3] = nw4r::math::VEC3(0.0f, 2.4f, 0.0f);
        checkVecs[4] = nw4r::math::VEC3(0.0f, 2.9f, 0.0f);
        checkVecs[5] = nw4r::math::VEC3(0.0f, 3.3f, 0.0f);

        f32 minDiff = 0.0f;
        for (int i = 0; i < 6; i++) {
            nw4r::math::VEC3 outVec;
            nw4r::math::VEC3Transform(&outVec, &outMtx2, &checkVecs[i]);

            if (outVec.y > -0.6f && outVec.z > -191.4f) {
                f32 diff = -0.6f - outVec.y;
                if (minDiff > diff) {
                    minDiff = diff;
                }
            }
        }
        outMtx2._13 += minDiff;
    }

    nw4r::math::VEC3 pos2(outMtx2._03, outMtx2._13, outMtx2._23);

    if (!fn_801C3490(pMtxA, &pos2)) {
        nw4r::math::MTX34 dummyMtx3(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -193.0f
        );
        mMatrices[index][1] = dummyMtx3;
    } else {
        mMatrices[index][1] = outMtx2;
    }
}

/**
 * @brief Hides excess pins when fewer than 10 are active
 *
 * @param count Number of active pins to leave visible
 */
void RPBowRegularPinManager::HideExcessPins(int count) {
    f32 f2 = (count == 0) ? 0.0f : mMatrices[0][0]._03;

    for (int i = count; i < 10; i++) {
        nw4r::math::MTX34 mtx1(0.0f, 0.0f, 0.0f, f2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -193.0f);
        mMatrices[i][0] = mtx1;

        nw4r::math::MTX34 mtx2(0.0f, 0.0f, 0.0f, f2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -193.0f);
        mMatrices[i][1] = mtx2;
    }
}
