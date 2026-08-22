#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

/**
 * @brief Lightmap texture names
 */
const char* RPSysKokeshiIcon::LIGHT_TEXTURE_NAMES[ELightMap_Max] = {
    "lm_0",
    "lm_1",
};

/**
 * @brief Lightmap texture file names
 */
const char* RPSysKokeshiIcon::LIGHT_TEXTURE_FILE_NAMES[ELightMap_Max] = {
    "lm_0.bti",
    "lm_1.bti",
};

/**
 * @brief Constructor
 *
 * @param pGenInfo Mii generation parameters
 */
RPSysKokeshiIcon::RPSysKokeshiIcon(const RPSysKokeshiGenInfo* pGenInfo)
    : RPSysAvatar(pGenInfo) {

    Construct();
}

/**
 * @brief Destructor
 */
RPSysKokeshiIcon::~RPSysKokeshiIcon() {}

/**
 * @brief Loads the assets necessary for this avatar
 *
 * @param pOverloadInfo Overload parameters
 */
void RPSysKokeshiIcon::LoadResource(
    const RPSysKokeshiOverloadInfo* pOverloadInfo) {

    RPSysAvatar::LoadResource(pOverloadInfo);
}

/**
 * @brief Configures a model for use with icon rendering
 *
 * @param pModel Mii model
 */
void RPSysKokeshiIcon::SetupModel(RPGrpModel* pModel) {
    RPSysResourceManager* pResourceManager =
        RP_GET_INSTANCE(RPSysResourceManager);

    EGG::Archive* pCommonArchive = pResourceManager->GetStaticCommonArchive();

    for (u8 i = 0; i < ELightMap_Max; i++) {
        void* pTextureFile = RPSysResourceManager::GetFileFromArchive(
            pCommonArchive, LIGHT_TEXTURE_FILE_NAMES[i]);

        RPGrpTexture tex(static_cast<EGG::ResTIMG*>(pTextureFile));
        pModel->ReplaceTexture(LIGHT_TEXTURE_NAMES[i], tex, true);
    }

    if (pModel->GetKind() == RPGrpModel::Kind_RFL) {
        static_cast<RPGrpModelRfl*>(pModel)-> //
            SetMaterialType(RPGrpModelRfl::MaterialType_1);
    }

    f32 scale = 1.0f / RP_GET_INSTANCE(RPSysKokeshiManager)->GetBaseScale();
    pModel->SetBaseScale(scale);
    pModel->Calc();

    if (pModel->GetKind() == RPGrpModel::Kind_RFL) {
        static_cast<RPGrpModelRfl*>(pModel)->SetOutputAlpha(255);
    }
}

/**
 * @brief Gets the texture created for this icon
 */
EGG::ResTIMG* RPSysKokeshiIcon::GetResTIMG() {
    return mpCapTexture->getResTIMG();
}

/**
 * @brief Applies all lightmap textures to this avatar
 *
 * @param drawScene Draw scene index
 */
void RPSysKokeshiIcon::ApplyLightTexture(u8 /* drawScene */) {}

/**
 * @brief Configures a NW4R camera to capture view this icon's model
 *
 * @param cam G3D camera
 * @param width Texture width
 * @param height Texture heigth
 * @param view Icon viewpoint
 */
void RPSysKokeshiIcon::SetupCamera(nw4r::g3d::Camera cam, u16 width, u16 height,
                                   RPSysKokeshiManager::IconView view) {
    switch (view) {
    case RPSysKokeshiManager::IconView_Front: {
        cam.SetPosition(32.5f, 600.0f, 0.0f);
        break;
    }

    case RPSysKokeshiManager::IconView_Back: {
        cam.SetPosition(32.5f, -600.0f, 0.0f);
        break;
    }

    case RPSysKokeshiManager::IconView_CloseUp: {
        cam.SetPosition(32.5f, 450.0f, 0.0f);
        break;
    }

    default: {
        break;
    }
    }

    nw4r::math::VEC3 target(32.5f, 0.0f, 0.0f);
    nw4r::math::VEC3 up(1.0f, 0.0f, 0.0f);

    nw4r::g3d::Camera::PostureInfo posture;
    posture.tp = nw4r::g3d::Camera::POSTURE_LOOKAT;
    posture.cameraUp = up;
    posture.cameraTarget = target;

    cam.SetPosture(posture);

    f32 fovy;
    f32 aspect = static_cast<f32>(width) / static_cast<f32>(height);

    if (width < height) {
        fovy = nw4r::math::Atan2Rad(43.2f / aspect, 500.0f);
        fovy = 2.0f * NW4R_MATH_RAD_TO_DEG(fovy);
    } else {
        fovy = nw4r::math::Atan2Rad(43.2f, 500.0f);
        fovy = 2.0f * NW4R_MATH_RAD_TO_DEG(fovy);
    }

    cam.SetPerspective(fovy, aspect, 1.0f, 1000.0f);

    if (mGenInfo.GetMipMap()) {
        cam.SetScissor(0, 0, width * 2, height * 2);
    } else {
        cam.SetScissor(0, 0, width, height);
    }

    if (mGenInfo.GetMipMap()) {
        cam.SetViewport(0.0f, 0.0f, width * 2.0f, height * 2.0f);
        cam.SetViewportZRange(0.0f, 1.0f);
    } else {
        cam.SetViewport(0.0f, 0.0f, width, height);
        cam.SetViewportZRange(0.0f, 1.0f);
    }
}

/**
 * @brief Renders this icon and captures it to a texture
 *
 * @param pModel Mii model
 * @param rLocation Mii storage location
 * @param pAllocator Memory allocator
 * @param width Texture width
 * @param height Texture height
 * @param format Texture format
 * @param bgType Background color type
 * @param bgColor Background color (for RFLIconBG_Direct)
 * @param view Icon viewpoint
 */
void RPSysKokeshiIcon::MakeTexture(RPGrpModel* pModel,
                                   const RPSysKokeshiLocation& rLocation,
                                   EGG::Allocator* pAllocator, u16 width,
                                   u16 height, GXTexFmt format,
                                   RFLIconBGType bgType, GXColor bgColor,
                                   RPSysKokeshiManager::IconView view) {

    SetupModel(pModel);
    ModifyBgColor(rLocation, width, height, format, bgType, bgColor);

    nw4r::g3d::ScnRoot* pScnRoot = nw4r::g3d::ScnRoot::Construct(pAllocator);
}

/**
 * @brief Applies the background color to the icon texture
 *
 * @param rLocation Mii storage location
 * @param width Texture width
 * @param height Texture height
 * @param format Texture format
 * @param bgType Background color type
 * @param bgColor Background color (for RFLIconBG_Direct)
 */
void RPSysKokeshiIcon::ModifyBgColor(const RPSysKokeshiLocation& rLocation,
                                     u16 width, u16 height, GXTexFmt format,
                                     RFLIconBGType bgType, GXColor bgColor) {

    EGG::ResTIMG* pResTIMG = mpCapTexture->getResTIMG();

    if (bgType == RFLIconBG_Favorite) {
        RFLAdditionalInfo info;

        RP_GET_INSTANCE(RPSysKokeshiManager)
            ->GetAdditionalInfo(rLocation, &info);

        bgColor =
            RFLGetFavoriteColor(static_cast<RFLFavoriteColor>(info.color));
    }

    bgColor.a = 0;

    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDstAlpha(GX_FALSE, 0);

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);

    GXSetCopyFilter(GX_FALSE, NULL, GX_FALSE, NULL);
    GXSetCopyClamp(GX_CLAMP_ALL);

    if (mGenInfo.GetMipMap()) {
        GXSetTexCopySrc(0, 0, width * 2, height * 2);
        GXSetTexCopyDst(width, height, format, GX_TRUE);
    } else {
        GXSetTexCopySrc(0, 0, width, height);
        GXSetTexCopyDst(width, height, format, GX_FALSE);
    }

    GXSetCopyClear(bgColor, GX_CLEAR_Z_MAX);

    GXCopyTex(reinterpret_cast<u8*>(pResTIMG) + pResTIMG->imageOffset, GX_TRUE);
    GXPixModeSync();
}

/**
 * @brief Handles post-constructor initialization
 */
void RPSysKokeshiIcon::Construct() {
    RPSysAvatar::Construct();

    // unused
    RPSysSystem* pSystem = RP_GET_INSTANCE(RPSysSystem);
    (void)pSystem->getFBWidth();
    (void)pSystem->getFBHeight();

    u16 height = mGenInfo.GetIconHeight();
    u16 width = mGenInfo.GetIconWidth();

    mpCapTexture = new EGG::CapTexture(width, height, GX_TF_RGB5A3);
    mpCapTexture->configure();

    mpCapTexture->allocWithHeaderDebug();
    mpCapTexture->invalidate();

    mpCapTexture->setMinFilter(GX_CLAMP);
    mpCapTexture->setMagFilter(GX_CLAMP);

    EGG::Heap* pOldHeap = EGG::Heap::getCurrentHeap();
    EGG::Allocator* pOldAllocator = RPGrpModel::GetAllocator();

    // TODO(kiwi) I guess 0x200 would cover the ExpHeap + Allocator?
    u32 nglSize = RFLGetWorkSize(TRUE) + 0x200;
    void* pNglWork = pOldHeap->alloc(nglSize, -4);

    EGG::ExpHeap* pNglHeap = EGG::ExpHeap::create(pNglWork, nglSize);
    EGG::Allocator* pNglAllocator = new (pNglHeap) EGG::Allocator(pNglHeap);

    // Take ownership of any graphics allocations
    pNglHeap->becomeCurrentHeap();
    RPGrpModel::SetAllocator(pNglAllocator);

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

    case RPSysKokeshiManager::GenType_Direct: {
        location = mGenInfo.GetLocation();
        break;
    }

    default: {
        break;
    }
    }

    RFLResolution resolution = RFLResolution_64;
    if (mGenInfo.GetIconWidth() > 128 || mGenInfo.GetIconHeight() > 128) {
        resolution = RFLResolution_256;
    } else if (mGenInfo.GetIconWidth() > 64 || mGenInfo.GetIconHeight() > 64) {
        resolution = RFLResolution_128;
    }

    // TODO(kiwi) View ID constants
    // clang-format off
    RPGrpModel* pNigaoeModel = pKokeshiManager->CreateNigaoeModel(
        location,
        resolution,
        ((1 << mGenInfo.GetIconExpression()) & ALLOWED_EXPFLAG) | RFLExpFlag_Normal,
        1);
    // clang-format on

    pKokeshiManager->ChangeExpression(pNigaoeModel,
                                      mGenInfo.GetIconExpression());

    // clang-format off
    MakeTexture(
        pNigaoeModel,
        mGenInfo.GetLocation(),
        pNglAllocator,
        mGenInfo.GetIconWidth(),
        mGenInfo.GetIconHeight(),
        GX_TF_RGB5A3,
        mGenInfo.GetIconBGType(),
        mGenInfo.GetIconBGColor(),
        mGenInfo.GetIconView());
    // clang-format on

    if (mGenInfo.GetIconEdge()) {
        MakeEdge();
    }

    pKokeshiManager->CreateTexture(mpCapTexture->getResTIMG());
    pNigaoeModel->RemoveGenList();

    // Restore original management
    pNglHeap->destroy();
    RPGrpModel::SetAllocator(pOldAllocator);
    pOldHeap->becomeCurrentHeap();

    RPSysAvatar::Setup();
}
