#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/RPUtility.h>
#include <Pack/common_message.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

RP_SINGLETON_IMPL(RPSysKokeshiManager);

/**
 * @brief Default value for output alpha
 */
const u8 RPSysKokeshiManager::DEFAULT_OUTPUT_ALPHA = 128;

/**
 * @brief Clothing texture filenames
 */
const char* RPSysKokeshiManager::CLOTHING_TEXTURE_NAMES[ClothingTexture_Max] = {
    "dummy_tex_a",
    "dummy_tex_b",
};

/**
 * @brief Lightmap texture names
 */
const char* RPSysKokeshiManager::LIGHT_TEXTURE_NAMES[LightMap_Max] = {
    "lm_0",
    "lm_1",
};

/**
 * @brief Main material name
 */
const char* RPSysKokeshiManager::MAIN_MATERIAL_NAME = "mt_main";

/**
 * @brief Face library resource filename
 */
const char* RPSysKokeshiManager::RFL_RES_NAME = "RFL_Res.dat";

/**
 * @brief Common message filename
 */
const char* RPSysKokeshiManager::COMMON_MESSAGE_NAME = "common_message.bmg";

/**
 * @brief Hand model filenames
 */
const char* RPSysKokeshiManager::HAND_FILE_NAMES[HandType_Max] = {
    "G3D/ava_handA.brres",
    "G3D/ava_handB.brres",
};

/**
 * @brief Constructor
 */
RPSysKokeshiManager::RPSysKokeshiManager()
    : IRPSysHostIOSocket("Kokeshi Manager") {

    mpNglBuffer = new (32) u8[RFLGetWorkSize(false)];
    mFriendRandomNum = RFL_DB_CHAR_MAX;
    unk28 = unk2C = unk30 = 0.0f;
    mOutputAlpha = DEFAULT_OUTPUT_ALPHA;
    mLoadError = LoadError_Success;

    mBaseScale = 0.08f;
    RPGrpModelRfl::SetBaseScale(mBaseScale);

    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);
    RPGrpModelRfl::SetMtx(mtx);

    mpOfficialDB = new RPSysOfficialDB();

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mppCtrlDataLoaders[i] = new RPSysKokeshiCtrlDataLoader(i);
    }

    mpCtrlMgr = NULL;
    mpBodyManager = NULL;

    RPSysHostIOSocketManager::AddHostIOSocket(this);
}

/**
 * @brief Destructor
 */
RPSysKokeshiManager::~RPSysKokeshiManager() {}

/**
 * @brief Creates all lightmap textures
 *
 * @param drawScene Draw scene index
 */
void RPSysKokeshiManager::CreateLightTexture(u8 drawScene) {
    RPGrpDrawPathLightMap* pLightMap = RPGrpModelManager::GetCurrent()
                                           ->GetDrawPathManager(drawScene)
                                           ->GetDrawPathLightMap();

    for (u8 i = 0; i < LightMap_Max; i++) {
        pLightMap->GetLightTextureManager()->createTexture(
            LIGHT_TEXTURE_NAMES[i]);
    }
}

/**
 * @brief Applies the specified expression to the Mii model
 *
 * @param pModel Mii model
 * @param expr New expression
 */
void RPSysKokeshiManager::ChangeExpression(RPGrpModel* pModel,
                                           RFLExpression expr) {
    if (pModel->GetKind() != RPGrpModel::Kind_RFL) {
        return;
    }

    nw4r::g3d::ScnRfl* pScnRfl = pModel->GetScnRfl();

    if (pScnRfl->GetExpressionFlag() & (1 << expr)) {
        pScnRfl->SetExpression(expr);
    }
}

/**
 * @brief Gets the current expression of the Mii model
 *
 * @param pModel Mii model
 */
RFLExpression RPSysKokeshiManager::GetExpression(RPGrpModel* pModel) {
    if (pModel->GetKind() != RPGrpModel::Kind_RFL) {
        return RFLExp_Normal;
    }

    nw4r::g3d::ScnRfl* pScnRfl = pModel->GetScnRfl();

    RFLExpression expr;
    pScnRfl->GetExpression(&expr);
    return expr;
}

/**
 * @brief Gets the number of valid Miis in the official database
 */
u16 RPSysKokeshiManager::GetOfficialDBValidNum() {
    return RP_GET_INSTANCE(RPSysKokeshiManager)->mpOfficialDB->GetValidNum();
}

/**
 * @brief Finds the official database index holding the Mii with the
 * specified create ID
 *
 * @param pCreateID Mii create ID
 * @return Official database index, or -1 if not found
 */
s16 RPSysKokeshiManager::GetOfficialDBIndexFromCreateID(
    const RFLCreateID* pCreateID) {

    return RP_GET_INSTANCE(RPSysKokeshiManager)
        ->mpOfficialDB->GetIndexFromCreateID(pCreateID);
}

/**
 * @brief Resets the manager state
 */
void RPSysKokeshiManager::Reset() {
    mpOfficialDB->Reset();
    mOutputAlpha = DEFAULT_OUTPUT_ALPHA;
}

/**
 * @brief Sets the material type of the Mii model
 *
 * @param pModel Mii model
 * @param type New material type
 */
void RPSysKokeshiManager::SetMaterialType(RPGrpModel* pModel,
                                          RPGrpModelRfl::MaterialType type) {
    if (pModel->GetKind() != RPGrpModel::Kind_RFL) {
        return;
    }

    static_cast<RPGrpModelRfl*>(pModel)->SetMaterialType(type);
}

/**
 * @brief Sets the brightness color of the Mii model
 *
 * @param pModel Mii model
 * @param color New brightness color
 */
void RPSysKokeshiManager::SetBrightnessColor(RPGrpModel* pModel,
                                             GXColor color) {
    if (pModel->GetKind() != RPGrpModel::Kind_RFL) {
        return;
    }

    static_cast<RPGrpModelRfl*>(pModel)->SetBrightnessColor(color);
}

/**
 * @brief Loads all static lifetime resources required by this manager
 */
void RPSysKokeshiManager::LoadStaticResource() {
    RPSysSystem* pSystem = RP_GET_INSTANCE(RPSysSystem);
    EGG::Heap* pResHeap = pSystem->getResourceHeap();

    RPSysResourceManager* pResourceManager =
        RP_GET_INSTANCE(RPSysResourceManager);

    pResourceManager->LoadKokeshiArchive();
    EGG::Archive* pKokeshiArchive = pResourceManager->GetKokeshiArchive();

    u32 nglSize = 0;
    void* pNglRes = RPSysResourceManager::GetFileFromArchive(
        pKokeshiArchive, RFL_RES_NAME, &nglSize);

    pSystem->startLoadCount();

    RFLErrcode err = RFLErrcode_NANDCommandfail;
    s32 reason = NAND_RESULT_BUSY;

    while (err == RFLErrcode_NANDCommandfail && reason == NAND_RESULT_BUSY) {
        err = RFLInitRes(mpNglBuffer, pNglRes, nglSize, false);

        if (err == RFLErrcode_NANDCommandfail) {
            reason = RFLGetLastReason();
        }

        // Time out eventually
        if (pSystem->isLoadCountEnd()) {
            break;
        }
    }

    switch (err) {
    case RFLErrcode_Success: {
        mLoadError = LoadError_Success;
        break;
    }

    case RFLErrcode_NANDCommandfail: {
        if (RFLGetLastReason() == NAND_RESULT_BUSY) {
            mLoadError = LoadError_Busy;
        } else {
            mLoadError = LoadError_Fail;
        }
        break;
    }

    case RFLErrcode_Loadfail:
    case RFLErrcode_Fatal: {
        mLoadError = LoadError_Fail;
        break;
    }

    case RFLErrcode_NotAvailable:
    default: {
        mLoadError = LoadError_Fail;
        break;
    }
    }

    void* pCommonRes =
        RPSysResourceManager::GetMessageResource(COMMON_MESSAGE_NAME);

    mpCommonMessage = new (pResHeap) RPSysMessage(pCommonRes, pResHeap);

    static const bmg_message GUEST_NAME_MSGS[RFL_DEFAULT_CHAR_MAX] = {
        MSG_UNPACK(MSG_660_000), MSG_UNPACK(MSG_661_000),
        MSG_UNPACK(MSG_662_000), MSG_UNPACK(MSG_663_000),
        MSG_UNPACK(MSG_664_000), MSG_UNPACK(MSG_665_000),
    };

    for (u16 i = 0; i < RFL_DEFAULT_CHAR_MAX; i++) {
        mpGuestNames[i] = mpCommonMessage->GetMsg(GUEST_NAME_MSGS[i].group,
                                                  GUEST_NAME_MSGS[i].index);
    }
}

/**
 * @brief Creates a Kokeshi-related model
 *
 * @param pFile Resource file
 * @param index Model index
 * @param viewNo Renderer view ID
 * @param typeOption Model type option
 * @param bufferOption nw4r::g3d replacement buffer option
 */
RPGrpModel* RPSysKokeshiManager::CreateModel(void* pFile, u16 index, u8 viewNo,
                                             u32 typeOption, u32 bufferOption) {
    RPGrpModelResManager* pResManager = RPGrpModelResManager::GetCurrent();

    s32 chan = -1;
    bool ctrlFile = false;

    if (mpCtrlMgr != NULL) {
        chan = GetCurrentCtrlHeap();

        if (chan != -1 && pResManager->SearchData(pFile) == -1) {
            ctrlFile = true;
        }
    }

    RPGrpHandle fileHandle =
        pResManager->CreateData(RPGrpModelResManager::Type_ResFile, pFile);

    void* pMdlRes = pResManager->GetPtr(RPGrpModelResManager::Type_ResMdl,
                                        fileHandle, index);
    RPGrpHandle mdlHandle =
        pResManager->CreateData(RPGrpModelResManager::Type_ResMdl, pMdlRes);

    RPGrpModel* pModel = RPGrpModel::Construct(
        mdlHandle, viewNo, typeOption,
        bufferOption | nw4r::g3d::ScnMdl::BUFFER_RESTEXOBJ |
            nw4r::g3d::ScnMdl::BUFFER_RESGENMODE |
            nw4r::g3d::ScnMdl::BUFFER_RESTEVCOLOR);

    if (mpCtrlMgr != NULL && chan != -1) {
        if (ctrlFile) {
            mpCtrlMgr->appendFile(chan, fileHandle);
            mpCtrlMgr->appendFile(chan, mdlHandle);
        }

        mpCtrlMgr->appendModel(chan, pModel);
    }

    return pModel;
}

/**
 * @brief Creates a Kokeshi face model
 *
 * @param rLocation Mii location
 * @param resolution Texture resolution
 * @param exprFlag Facial expression flags
 * @param viewNo Renderer view ID
 */
RPGrpModel*
RPSysKokeshiManager::CreateNigaoeModel(const RPSysKokeshiLocation& rLocation,
                                       RFLResolution resolution, u32 exprFlags,
                                       u8 viewNo) {
    s32 chan = -1;

    if (mpCtrlMgr != NULL) {
        chan = GetCurrentCtrlHeap();
    }

    RFLSetCoordinate(RFLCoordinateType_X, RFLCoordinateType_Y);

    u16 index = rLocation.GetIndex();
    RFLMiddleDB* pMiddleDB = NULL;

    if (rLocation.GetDataSource() == RFLDataSource_Middle) {
        rLocation.GetMiddleDB()->GetRFLMiddleDB(index, &pMiddleDB, &index);
    }

    RPGrpModelRfl* pNigaoeModel = RPGrpModelRfl::Construct(
        rLocation.GetDataSource(), index, pMiddleDB, resolution,
        exprFlags | RFLExpFlag_Normal, viewNo);

    if (mpCtrlMgr != NULL && chan != -1) {
        mpCtrlMgr->appendModel(chan, pNigaoeModel);
    }

    return pNigaoeModel;
}

/**
 * @brief Creates a Kokeshi-related texture
 *
 * @param pFile Resource file
 * @param pName Texture name
 */
RPGrpTexture* RPSysKokeshiManager::CreateTexture(void* pFile,
                                                 const char* pName) {
    RPGrpModelResManager* pResManager = RPGrpModelResManager::GetCurrent();

    s32 chan = -1;
    bool ctrlFile = false;

    if (mpCtrlMgr != NULL) {
        chan = GetCurrentCtrlHeap();

        if (chan != -1 && pResManager->SearchData(pFile) == -1) {
            ctrlFile = true;
        }
    }

    RPGrpHandle fileHandle =
        pResManager->CreateData(RPGrpModelResManager::Type_ResFile, pFile);

    void* pTexRes = pResManager->GetPtr(RPGrpModelResManager::Type_ResTex,
                                        fileHandle, pName);
    RPGrpHandle texHandle =
        pResManager->CreateData(RPGrpModelResManager::Type_ResTex, pTexRes);

    RPGrpTexture* pTexture = new RPGrpTexture(fileHandle, pName);

    if (mpCtrlMgr != NULL && chan != -1) {
        if (ctrlFile) {
            mpCtrlMgr->appendFile(chan, fileHandle);
            mpCtrlMgr->appendFile(chan, texHandle);
        }
    }

    return pTexture;
}

/**
 * @brief Creates a Kokeshi-related texture
 *
 * @param pTexData Texture data
 */
RPGrpTexture* RPSysKokeshiManager::CreateTexture(void* pTexData) {
    // TODO(kiwi) I think ResTIMG and GXTexObj have the same layout, but this
    // cast still isn't safe because RPGrpTexture has a vtable!
    return static_cast<RPGrpTexture*>(pTexData);
}

/**
 * @brief Changes the clothing textures of the specified Mii model
 *
 * @param pModel Mii model
 * @param pTextureA Clothing texture A
 * @param pTextureB Clothing texture B
 */
void RPSysKokeshiManager::ChangeTexture(RPGrpModel* pModel,
                                        RPGrpTexture* pTextureA,
                                        RPGrpTexture* pTextureB) {
    pModel->ReplaceTexture(CLOTHING_TEXTURE_NAMES[ClothingTexture_A],
                           *pTextureA, true);

    pModel->ReplaceTexture(CLOTHING_TEXTURE_NAMES[ClothingTexture_B],
                           *pTextureB, true);
}

/**
 * @brief Sets the material colors of the specified Mii model
 *
 * @param pModel Mii model
 * @param body Body color
 * @param skin Skin color
 */
void RPSysKokeshiManager::SetMatColor(RPGrpModel* pModel, GXColor body,
                                      GXColor skin) {
    RPGrpModelMaterial* pMaterial = pModel->GetMaterial(MAIN_MATERIAL_NAME);

    static const RPGrpModelMaterial::ETevColor TEV_REGS[] = {
        RPGrpModelMaterial::ETevColor_Reg0, // body color
        RPGrpModelMaterial::ETevColor_Reg1  // skin color
    };

    pMaterial->SetTevColor(TEV_REGS[0], body);
    pMaterial->SetTevColor(TEV_REGS[1], skin);

    pMaterial->SetSyncFlags(RPGrpModelMaterial::ESyncFlag_ResMatTev);
}

/**
 * @brief Configures the TEV color effect of the specified Mii model
 *
 * @param pModel Mii model
 * @param alpha Effect alpha
 * @param r Red component
 * @param g Green component
 * @param b Blue component
 */
void RPSysKokeshiManager::SetMatTevColorEffect(RPGrpModel* pModel, u8 alpha,
                                               u8 r, u8 g, u8 b) {
    RPGrpModelMaterial* pMaterial = pModel->GetMaterial(MAIN_MATERIAL_NAME);

    pMaterial->SetTevColorAlpha(RPGrpModelMaterial::ETevColor_Reg2, alpha);
    pMaterial->SetTevKColor(RPGrpModelMaterial::ETevKColor_Reg0, r, g, b);

    pMaterial->SetSyncFlags(RPGrpModelMaterial::ESyncFlag_ResMatTev);
}

/**
 * @brief Gets the additional info about the specified Mii
 *
 * @param rLocation Mii location
 * @param[out] pInfo Additional info
 */
void RPSysKokeshiManager::GetAdditionalInfo(
    const RPSysKokeshiLocation& rLocation, RFLAdditionalInfo* pInfo) {

    u16 index = rLocation.GetIndex();
    RFLMiddleDB* pMiddleDB = NULL;

    if (rLocation.GetDataSource() == RFLDataSource_Middle) {
        rLocation.GetMiddleDB()->GetRFLMiddleDB(rLocation.GetIndex(),
                                                &pMiddleDB, &index);
    }

    RFLGetAdditionalInfo(pInfo, rLocation.GetDataSource(), pMiddleDB, index);
}

/**
 * @brief Removes the model's scaling from the transformation matrix
 *
 * @param[out] pOut Transformation matrix with scaling removed
 * @param pModel Model whose scale should be used
 * @param pIn Initial transformation matrix
 */
void RPSysKokeshiManager::GetModelBaseScaleInvalidatedMtx(
    nw4r::math::MTX34* pOut, RPGrpModel* pModel, const nw4r::math::MTX34* pIn) {

    nw4r::math::VEC3 scale = pModel->GetScale();
    nw4r::math::VEC3 scaleInv(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);

    nw4r::math::MTX34Copy(pOut, pIn);

    pOut->_00 *= scaleInv.x;
    pOut->_01 *= scaleInv.y;
    pOut->_02 *= scaleInv.z;

    pOut->_10 *= scaleInv.x;
    pOut->_11 *= scaleInv.y;
    pOut->_12 *= scaleInv.z;

    pOut->_20 *= scaleInv.x;
    pOut->_21 *= scaleInv.y;
    pOut->_22 *= scaleInv.z;
}

/**
 * @brief Gets the archive filename for the specified hand type
 *
 * @param type Hand model type
 */
const char* RPSysKokeshiManager::GetHandFileName(u32 type) {
    return HAND_FILE_NAMES[type];
}

/**
 * @brief Gets the Mii location for the specified player slot
 * @details If the specified index is invalid, this function provides a
 * random guest Mii location.
 *
 * @param idx Player index
 * @param[out] pLocation Mii location
 */
void RPSysKokeshiManager::GetLocationPlayer(u8 idx,
                                            RPSysKokeshiLocation* pLocation) {
    if (RP_GET_INSTANCE(RPSysPlayerMgr)->getPlayerNum() > idx) {
        const RPSysPlayer& rPlayer =
            RP_GET_INSTANCE(RPSysPlayerMgr)->getPlayer(idx);

        RFLDataSource src = static_cast<RFLDataSource>(rPlayer.getDataSource());

        pLocation->SetDataSource(src);
        pLocation->SetIndex(rPlayer.getIndex());
        pLocation->SetMiddleDB(NULL);
    } else {
        // Pick a random guest Mii
        u16 index = RPUtlRandom::getU32(RFL_DEFAULT_CHAR_MAX);

        pLocation->SetDataSource(RFLDataSource_Default);
        pLocation->SetIndex(index);
        pLocation->SetMiddleDB(NULL);
    }
}

/**
 * @brief Gets the Mii location of a "friend" Mii
 *
 * @param src Mii data source
 * @param pMiddleDB Middle database (for RFLDataSource_Middle)
 * @param[out] pLocation Mii location
 */
void RPSysKokeshiManager::GetLocationFriend(RFLDataSource src,
                                            RPSysMiddleDB* pMiddleDB,
                                            RPSysKokeshiLocation* pLocation) {
    switch (src) {
    case RFLDataSource_Official: {
        u16 index = 0;
        bool valid = false;

        // Try picking a random Mii from the official database
        for (u16 i = 0; i < mFriendRandomNum; i++) {
            index = RPUtlRandom::getU32(RFL_DB_CHAR_MAX);

            if (mpOfficialDB->GetState(index) == OfficialDBState_Valid) {
                valid = true;
                pLocation->SetDataSource(RFLDataSource_Official);
                break;
            }
        }

        // Linear search for the first valid Mii
        if (!valid) {
            for (u16 i = 0; i < RFL_DB_CHAR_MAX; i++) {
                index = i;

                if (mpOfficialDB->GetState(i) == OfficialDBState_Valid) {
                    valid = true;
                    pLocation->SetDataSource(RFLDataSource_Official);
                    break;
                }
            }
        }

        // No valid official Miis, select a random guest
        if (!valid) {
            index = RPUtlRandom::getU32(RFL_DEFAULT_CHAR_MAX);
            pLocation->SetDataSource(RFLDataSource_Default);
        }

        pLocation->SetIndex(index);
        pLocation->SetMiddleDB(NULL);

        break;
    }

    case RFLDataSource_Middle: {
        pLocation->SetMiddleDB(pMiddleDB);
        pLocation->SetDataSource(RFLDataSource_Middle);

        u16 index = 0;
        bool valid = false;
        RPSysKokeshiLocation player;

        // Find the next non-player Mii from the middle database
        while (!valid) {
            pLocation->SetIndex(pMiddleDB->GetCurrentIndex());
            valid = true;

            if (pMiddleDB->GetStoredNum() > pMiddleDB->GetCurrentIndex()) {
                RFLAdditionalInfo middleInfo;
                GetAdditionalInfo(*pLocation, &middleInfo);

                // Make sure this Mii was not chosen by any player
                for (u32 i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                    GetLocationPlayer(i, &player);

                    RFLAdditionalInfo playerInfo;
                    GetAdditionalInfo(player, &playerInfo);

                    bool isPlayer = true;

                    for (u32 i = 0; i < RFL_CREATEID_LEN; i++) {
                        if (playerInfo.createID.data[i] !=
                            middleInfo.createID.data[i]) {

                            isPlayer = false;
                            break;
                        }
                    }

                    if (isPlayer) {
                        valid = false;
                        break;
                    }
                }
            }

            pMiddleDB->IncrementCurrentIndex();

            if (valid || ++index >= WPAD_MAX_CONTROLLERS) {
                break;
            }
        }

        break;
    }

    default: {
        break;
    }
    }
}

/**
 * @brief Registers the specified Mii location with the in-memory official
 * database
 *
 * @param rLocation Mii location
 */
void RPSysKokeshiManager::RegistLocation(
    const RPSysKokeshiLocation& rLocation) {

    if (rLocation.GetDataSource() != RFLDataSource_Official) {
        return;
    }

    mpOfficialDB->SetState(rLocation.GetIndex(), OfficialDBState_Registered);
}

/**
 * @brief Sets the active controller manager
 *
 * @param pCtrlMgr Controller manager
 */
void RPSysKokeshiManager::SetCtrlMgr(RPSysKokeshiCtrlMgr* pCtrlMgr) {
    mpCtrlMgr = pCtrlMgr;
}

/**
 * @brief Clears the active controller manager
 */
void RPSysKokeshiManager::ClearCtrlMgr() {
    mpCtrlMgr = NULL;
}

/**
 * @brief Updates the active controller manager's state
 */
void RPSysKokeshiManager::UpdateCtrlMgr() {
    if (mpCtrlMgr != NULL) {
        mpCtrlMgr->calc();
    }
}

/**
 * @brief Gets the index of the controller resource heap that is the current
 * global heap
 *
 * @return Controller channel, or -1 if not applicable
 */
s32 RPSysKokeshiManager::GetCurrentCtrlHeap() const {
    EGG::Heap* pCurrentHeap = EGG::Heap::getCurrentHeap();

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (mpCtrlMgr->getResourceHeap(i) == pCurrentHeap) {
            return i;
        }
    }

    return -1;
}
