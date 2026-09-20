#include <Pack/RPSports/RPBowScene/bowling.h>

// External table used by the priority loop (defined elsewhere)
extern const f32 gLaneXOffsets[];

/**
 * @brief Stub
 */
void RPBowAlleyModelManager::fn_8031EFE0() {
    ;
}

/**
 * @brief Destructor
 */
RPBowAlleyModelManager::~RPBowAlleyModelManager() {}

/**
 * @brief Sets the primary models for the alley scene
 *
 * @param pLaneModel Regular alley Lanes model
 * @param pPowerThrowsRoomModel Power Throws area model (entire room, no culling)
 * @param pStaticPinsModel Regular alley static pins model (outside of the 7 active lanes)
 * @param pLoungeModel Regular alley lounge area model
 * @param pLeftBumperModel Left Power Throws bumper
 * @param pLeftBumperReflModel Left Power Throws bumper reflection
 * @param pRightBumperModel Right Power Throws bumper
 * @param pRightBumperReflModel Right Power Throws bumper reflection
 */
void RPBowAlleyModelManager::SetModels(RPGrpModel* pLaneModel, RPGrpModel* pPowerThrowsRoomModel, RPGrpModel* pStaticPinsModel, RPGrpModel* pLoungeModel, RPGrpModel* pLeftBumperModel, RPGrpModel* pLeftBumperReflModel, RPGrpModel* pRightBumperModel, RPGrpModel* pRightBumperReflModel) {
    mModels[0] = pLaneModel;
    mModels[1] = pPowerThrowsRoomModel;
    mModels[2] = pStaticPinsModel;
    mModels[3] = pLoungeModel;
    mModels[4] = pLeftBumperModel;
    mModels[6] = pLeftBumperReflModel;
    mModels[5] = pRightBumperModel;
    mModels[7] = pRightBumperReflModel;
}

/**
 * @brief Sets a specific model slot for rendering
 *
 * @param index Slot index
 * @param pModel Main model
 * @param pAltModel Alternate model
 */
void RPBowAlleyModelManager::SetModelSlot(int index, RPGrpModel* pModel, RPGrpModel* pAltModel) {
    mSlotModels[index] = pModel;
    mSlotAltModels[index] = pAltModel;
}

/**
 * @brief Resets scene variables to default
 */
void RPBowAlleyModelManager::ResetSceneParams() {
    mSceneFlags = 1;
    mCurrentSlotIndex = 0;
    mBumperPosition = 0.0f;
}

/**
 * @brief Performs the first loop update on the scene models
 *
 * @param pMtx Transformation matrix
 */
inline void RPBowAlleyModelManager::UpdateModelsLoop1(nw4r::math::MTX34* pMtx) {
    int i;
    u32 bit = 1;
    RPBowAlleyModelManager* pThis = this;

    for (i = 0; i < 4; i++) {
        if (mSceneFlags & (bit << i)) {
            nw4r::g3d::ScnObj* pScnObj = pThis->mModels[0]->GetScnObj();
            if (pScnObj != NULL) {
                pScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, pMtx);
            }
            pThis->mModels[0]->UpdateFrame();
            pThis->mModels[0]->Calc();
            pThis->mModels[0]->Entry();
        }

        pThis = (RPBowAlleyModelManager*)((u8*)pThis + 4);
    }
}

/**
 * @brief Performs the second loop update on the scene models
 *
 * @param pMtx Transformation matrix
 */
inline void RPBowAlleyModelManager::UpdateModelsLoop2(nw4r::math::MTX34* pMtx) {
    if (mSceneFlags & 1) {
        const f32* pLaneXOffset = gLaneXOffsets;

        for (int i = 0; i < 4; i++) {
            RPGrpModel* pCurrentModel = (i == mCurrentSlotIndex) ? mSlotAltModels[i] : mSlotModels[i];

            pMtx->m[0][3] = *pLaneXOffset;

            nw4r::g3d::ScnObj* pScnObj = pCurrentModel->GetScnObj();
            if (pScnObj != NULL) {
                pScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, pMtx);
            }

            pCurrentModel->UpdateFrame();
            pCurrentModel->Calc();
            pCurrentModel->Entry();

            pLaneXOffset++;
        }
    }
}

/**
 * @brief Performs the third loop update on the scene models
 *
 * @param pMtx Transformation matrix
 */
inline void RPBowAlleyModelManager::UpdateModelsLoop3(nw4r::math::MTX34* pMtx) {
    if (mSceneFlags & 2) {
        int pass;
        RPBowAlleyModelManager* pThis = this;

        for (pass = 0; pass < 2; pass++) {
            f32 sign = (pass == 0) ? -mBumperPosition : mBumperPosition;
            pMtx->m[0][3] = sign;

            nw4r::g3d::ScnObj* pScnObjA = pThis->mModels[4]->GetScnObj();
            if (pScnObjA != NULL) {
                pScnObjA->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, pMtx);
            }
            pThis->mModels[4]->UpdateFrame();
            pThis->mModels[4]->Calc();
            pThis->mModels[4]->Entry();

            nw4r::math::MTX34 mirrorMtx = *pMtx;
            mirrorMtx.m[1][0] *= -1.0f;
            mirrorMtx.m[1][1] *= -1.0f;
            mirrorMtx.m[1][2] *= -1.0f;
            mirrorMtx.m[1][3] *= -1.0f;

            nw4r::g3d::ScnObj* pScnObjB = pThis->mModels[5]->GetScnObj();
            if (pScnObjB != NULL) {
                pScnObjB->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mirrorMtx);
            }
            pThis->mModels[5]->UpdateFrame();
            pThis->mModels[5]->Calc();
            pThis->mModels[5]->Entry();

            pThis = (RPBowAlleyModelManager*)((u8*)pThis + 8);
        }
    }
}

/**
 * @brief Updates all models bound to the alley manager
 */
void RPBowAlleyModelManager::UpdateModels() {
    nw4r::math::MTX34 mtx;
    PSMTXIdentity(mtx.mtx);

    UpdateModelsLoop1(&mtx);
    UpdateModelsLoop2(&mtx);
    UpdateModelsLoop3(&mtx);
}
