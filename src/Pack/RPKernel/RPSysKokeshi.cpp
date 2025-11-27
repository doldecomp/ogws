#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/RPUtility.h>

#include <egg/core.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 *
 * @param pGenInfo Mii generation parameters
 */
RPSysKokeshi::RPSysKokeshi(const RPSysKokeshiGenInfo* pGenInfo)
    : RPSysAvatar(pGenInfo) {
    Construct();
}

/**
 * @brief Destructor
 */
RPSysKokeshi::~RPSysKokeshi() {}

/**
 * @brief Loads the assets necessary for this avatar
 *
 * @param pOverloadInfo Overload parameters
 */
void RPSysKokeshi::LoadResource(const RPSysKokeshiOverloadInfo* pOverloadInfo) {
    RPSysAvatar::LoadResource(pOverloadInfo);

    RPSysResourceManager* pResourceManager =
        RP_GET_INSTANCE(RPSysResourceManager);

    RPSysKokeshiManager* pKokeshiManager = RP_GET_INSTANCE(RPSysKokeshiManager);
    IRPSysKokeshiBodyManager* pBodyManager = pKokeshiManager->GetBodyManager();

    // Kokeshi common archive contains all of the assets
    EGG::Archive* pKokeshiArchive = pResourceManager->GetKokeshiArchive();

    // Open the body archive
    const char* pBodyFileName = pBodyManager->GetBodyFileName(
        mGenInfo.GetBodyType(), static_cast<RFLSex>(mAdditionalInfo.sex));

    void* pBodyFile = RPSysResourceManager::GetFileFromArchive(pKokeshiArchive,
                                                               pBodyFileName);

    // Create the body model
    u16 bodyIdx = pBodyManager->GetBodyModelIndex(
        mGenInfo.GetBodyType(), static_cast<RFLSex>(mAdditionalInfo.sex),
        mAdditionalInfo.height, mAdditionalInfo.build);

    mpBodyModel = pKokeshiManager->CreateModel(
        pBodyFile, bodyIdx, mGenInfo.GetViewNo(), mGenInfo.GetModelFlags(),
        mGenInfo.GetBufferOption());

    // Open the hand archive
    const char* pHandFileName =
        pKokeshiManager->GetHandFileName(mGenInfo.GetHandType());

    void* pHandFile = RPSysResourceManager::GetFileFromArchive(pKokeshiArchive,
                                                               pHandFileName);

    // Create the hand models
    mpLeftHandModel = pKokeshiManager->CreateModel(
        pHandFile, 0, mGenInfo.GetViewNo(), mGenInfo.GetModelFlags(),
        mGenInfo.GetBufferOption());

    mpRightHandModel = pKokeshiManager->CreateModel(
        pHandFile, 0, mGenInfo.GetViewNo(), mGenInfo.GetModelFlags(),
        mGenInfo.GetBufferOption());

    // Assign random clothes if requested via the overload info
    u16 clothesType = mOverloadInfo.GetClothesType();

    if (clothesType == RPSysKokeshiManager::ClothesType_Random) {
        switch (mGenInfo.GetGenType()) {
        case RPSysKokeshiManager::GenType_Player: {
            clothesType = mGenInfo.GetPlayerNo();
            break;
        }

        case RPSysKokeshiManager::GenType_Friend:
        case RPSysKokeshiManager::GenType_Kokeshi: {
            clothesType = RPUtlRandom::getU32(
                              pBodyManager->GetFriendClothesIndexRange()) +
                          pBodyManager->GetFriendClothesStartIndex();
            break;
        }

        default: {
            break;
        }
        }
    }

    mOverloadInfo.SetClothesType(clothesType);

    // Change clothes textures
    const char* pClothNameA = NULL;
    const char* pClothNameB = NULL;
    pBodyManager->GetClothesName(mGenInfo.GetBodyType(),
                                 static_cast<RFLSex>(mAdditionalInfo.sex),
                                 &pClothNameA, &pClothNameB);

    pKokeshiManager->ChangeTexture(mpBodyModel, pClothNameA, pClothNameB);
    pKokeshiManager->ChangeTexture(mpLeftHandModel, pClothNameA, pClothNameB);
    pKokeshiManager->ChangeTexture(mpRightHandModel, pClothNameA, pClothNameB);

    GXColor favColor = GetFavoriteColor();
    pKokeshiManager->SetMatColor(mpBodyModel, favColor, favColor);
    pKokeshiManager->SetMatColor(mpLeftHandModel, favColor, favColor);
    pKokeshiManager->SetMatColor(mpRightHandModel, favColor, favColor);

    if (mpNigaoeModel->GetKind() == RPGrpModel::Kind_Rfl) {
        // static_cast<RPGrpModelRfl*>(mpNigaoeModel)->unkA2 = ...
    }
}

/**
 * @brief Applies a generated light texture to this avatar
 *
 * @param idx Lightmap texture index
 */
void RPSysKokeshi::ApplyLightTexture(u8 idx) {
    // TODO
    (void)idx;
}

/**
 * @brief Gets the transformation matrix of the head joint/node
 *
 * @param[out] pMtx Transformation matrix
 */
void RPSysKokeshi::GetHeadJointMtx(EGG::Matrix34f* pMtx) {
    RP_GET_INSTANCE(RPSysKokeshiManager)
        ->GetBodyManager()
        ->GetHeadJointMtx(mGenInfo.GetBodyType(), mpBodyModel, pMtx);
}

/**
 * @brief Gets the transformation matrix of the left hand joint/node
 *
 * @param[out] pMtx Transformation matrix
 */
void RPSysKokeshi::GetLeftHandJointMtx(EGG::Matrix34f* pMtx) {
    RP_GET_INSTANCE(RPSysKokeshiManager)
        ->GetBodyManager()
        ->GetLeftHandJointMtx(mGenInfo.GetBodyType(), mpBodyModel, pMtx);
}

/**
 * @brief Gets the transformation matrix of the right hand joint/node
 *
 * @param[out] pMtx Transformation matrix
 */
void RPSysKokeshi::GetRightHandJointMtx(EGG::Matrix34f* pMtx) {
    RP_GET_INSTANCE(RPSysKokeshiManager)
        ->GetBodyManager()
        ->GetRightHandJointMtx(mGenInfo.GetBodyType(), mpBodyModel, pMtx);
}

/**
 * @brief Handles post-constructor initialization
 */
void RPSysKokeshi::Construct() {
    RPSysAvatar::Construct();

    RPSysKokeshiManager* pKokeshiManager = RP_GET_INSTANCE(RPSysKokeshiManager);
    RPSysKokeshiLocation location;

    switch (mGenInfo.GetGenType()) {
    case RPSysKokeshiManager::GenType_Player: {
        pKokeshiManager->GetLocationPlayer(mGenInfo.GetPlayerNo(), &location);

        mGenInfo.SetLocation(location);
        break;
    }

    case RPSysKokeshiManager::GenType_Friend: {
        pKokeshiManager->GetLocationFriend(
            mGenInfo.GetLocation().GetDataSource(),
            mGenInfo.GetLocation().GetMiddleDB(), &location);

        mGenInfo.SetLocation(location);
        break;
    }

    case RPSysKokeshiManager::GenType_Kokeshi: {
        location = mGenInfo.GetLocation();
        break;
    }

    default: {
        break;
    }
    }

    mpNigaoeModel = pKokeshiManager->CreateNigaoeModel(
        location, mGenInfo.GetResolution(), mGenInfo.GetExpression(),
        mGenInfo.GetViewNo());

    RPSysAvatar::Setup();
}
