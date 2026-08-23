#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <RVLFaceLib.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>

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
        void* pTexFile = RPSysResourceManager::GetFileFromArchive(
            pCommonArchive, LIGHT_TEXTURE_FILE_NAMES[i]);

        RPGrpTexture tex(static_cast<EGG::ResTIMG*>(pTexFile));

        pModel->ReplaceTexture(RPSysKokeshiManager::GetLightTextureName(i), tex,
                               true);
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
 * @brief Creates a cap texture for icon rendering
 *
 * @param width Texture width
 * @param height Texture height
 * @param format Texture format
 */
void RPSysKokeshiIcon::InitCapTexture(u16 width, u16 height, GXTexFmt format) {
    mpCapTexture = new EGG::CapTexture(width, height, format);
    mpCapTexture->configure();

    mpCapTexture->allocWithHeaderDebug();
    mpCapTexture->invalidate();

    mpCapTexture->setMinFilter(GX_CLAMP);
    mpCapTexture->setMagFilter(GX_CLAMP);
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

    if (mGenInfo.GetIconMipMap()) {
        cam.SetScissor(0, 0, width * 2, height * 2);
    } else {
        cam.SetScissor(0, 0, width, height);
    }

    if (mGenInfo.GetIconMipMap()) {
        cam.SetViewport(0.0f, 0.0f, width * 2.0f, height * 2.0f);
        cam.SetViewportZRange(0.0f, 1.0f);
    } else {
        cam.SetViewport(0.0f, 0.0f, width, height);
        cam.SetViewportZRange(0.0f, 1.0f);
    }
}

/**
 * @brief Prepares the GP rendering state
 */
void RPSysKokeshiIcon::BeginMakeTexture() const {
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_NEVER, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_FALSE);

    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDither(GX_FALSE);

    GXSetDstAlpha(GX_FALSE, 0);
    GXSetNumChans(0);

    nw4r::g3d::G3dReset();
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

    nw4r::g3d::ScnRoot* pScnRoot =
        nw4r::g3d::ScnRoot::Construct(pAllocator, NULL, 32, 256);

    pScnRoot->SetCurrentCamera(0);

    nw4r::g3d::Camera cam = pScnRoot->GetCurrentCamera();
    SetupCamera(cam, width, height, view);

    BeginMakeTexture();
    {
        pScnRoot->Clear();
        nw4r::g3d::ScnObj* pScnObj = NULL;

        if (pModel->GetKind() == RPGrpModel::Kind_RFL) {
            pScnObj = pModel->GetScnRfl();
        } else {
            pScnObj = pModel->GetScnMdlSimple();
        }

        pScnRoot->PushBack(pScnObj);

        pScnRoot->CalcWorld();
        pScnRoot->CalcMaterial();
        pScnRoot->CalcView();

        pScnRoot->GatherDrawScnObj();
        pScnRoot->ZSort();
        pScnRoot->DrawOpa();
        pScnRoot->DrawXlu();
    }
    EndMakeTexture();

    mpCapTexture->enableColorUpdate();
    mpCapTexture->enableAlphaUpdate();

    GXColor black = {0, 0, 0, 0};
    mpCapTexture->setClearColor(black);

    mpCapTexture->enableZBufferUpdate();
    mpCapTexture->setClearZ(GX_CLEAR_Z_MAX);

    mpCapTexture->disableVFilter();
    mpCapTexture->enablePixModeSync();

    if (mGenInfo.GetIconMipMap()) {
        mpCapTexture->capture(0, 0, true);
    } else {
        mpCapTexture->capture(0, 0, false);
    }

    mpCapTexture->flush();
}

/**
 * @brief Finalizes the GP rendering state
 */
void RPSysKokeshiIcon::EndMakeTexture() const {
    GXDrawDone();
}

/**
 * @brief Renders an outline in the icon around the Mii's face
 */
void RPSysKokeshiIcon::MakeEdge() {
    nw4r::math::MTX34 proj;
    C_MTXOrtho(proj, 0.0f, mGenInfo.GetIconWidth(), 0.0f,
               mGenInfo.GetIconHeight(), -10000.0f, 10000.0f);

    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_BACK);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    GXSetNumIndStages(0);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    GXSetAlphaUpdate(GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    RPGrpTexture tex(GetResTIMG());
    GXLoadTexObj(&tex.GetTexObj(), GX_TEXMAP0);

    nw4r::math::MTX34 ident;
    nw4r::math::MTX34Identity(&ident);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXLoadNrmMtxImm(ident, GX_PNMTX0);

    GXSetChanMatColor(GX_COLOR0A0, mGenInfo.GetIconEdgeColor());

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                    GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_KONST,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_GT, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    //
    // Draw edge outline
    //

    f32 angle = 0.0f;
    f32 step = 90.0f / static_cast<f32>(mGenInfo.GetIconEdgeWidth());

    while (angle < 360.0f) {
        // clang-format off
        f32 x2 = mGenInfo.GetIconWidth() + nw4r::math::CosDeg(angle) * mGenInfo.GetIconEdgeWidth();
        f32 x1 = nw4r::math::CosDeg(angle) * mGenInfo.GetIconEdgeWidth();
        f32 y2 = mGenInfo.GetIconHeight() + nw4r::math::SinDeg(angle) * mGenInfo.GetIconEdgeWidth();
        f32 y1 = nw4r::math::SinDeg(angle) * mGenInfo.GetIconEdgeWidth();
        // clang-format on

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(x1, y1, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);

            GXPosition3f32(x2, y1, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);

            GXPosition3f32(x2, y2, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);

            GXPosition3f32(x1, y2, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
        }
        GXEnd();

        angle += step;
    }

    //
    // Draw icon background
    //

    GXColor bgColor = mGenInfo.GetIconBGColor();

    if (mGenInfo.GetIconBGType() == RFLIconBG_Favorite) {
        RPSysKokeshiLocation location = mGenInfo.GetLocation();
        RFLAdditionalInfo info;

        RP_GET_INSTANCE(RPSysKokeshiManager)
            ->GetAdditionalInfo(location, &info);

        bgColor =
            RFLGetFavoriteColor(static_cast<RFLFavoriteColor>(info.color));
    }

    bgColor.a = 0;
    GXSetChanMatColor(GX_COLOR0A0, bgColor);

    {
        f32 w = mGenInfo.GetIconWidth();
        f32 h = mGenInfo.GetIconHeight();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);

            GXPosition3f32(w, 0.0f, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);

            GXPosition3f32(w, h, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);

            GXPosition3f32(0.0f, h, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
        }
        GXEnd();
    }

    //
    // Draw icon face texture
    //

    GXColor white = {255, 255, 255, 255};
    GXSetChanMatColor(GX_COLOR0A0, white);

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC,
                    GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    {
        f32 w = mGenInfo.GetIconWidth();
        f32 h = mGenInfo.GetIconHeight();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);

            GXPosition3f32(w, 0.0f, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);

            GXPosition3f32(w, h, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);

            GXPosition3f32(0.0f, h, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
        }
        GXEnd();
    }

    //
    // ???
    //

    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXSetChanMatColor(GX_COLOR0A0, mGenInfo.GetIconEdgeColor());

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                    GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                    GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, TRUE,
                    GX_TEVPREV);

    {
        f32 w = mGenInfo.GetIconWidth();
        f32 t = mGenInfo.GetIconEdgeWidth();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXPosition3f32(w, 0.0f, 0.0f);
            GXPosition3f32(w, t, 0.0f);
            GXPosition3f32(0.0f, t, 0.0f);
        }
        GXEnd();
    }

    {
        f32 w = mGenInfo.GetIconWidth();
        f32 h = mGenInfo.GetIconHeight();
        f32 b = mGenInfo.GetIconWidth() - mGenInfo.GetIconEdgeWidth();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(h, 0.0f, 0.0f);
            GXPosition3f32(w, 0.0f, 0.0f);
            GXPosition3f32(w, b, 0.0f);
            GXPosition3f32(h, b, 0.0f);
        }
        GXEnd();
    }

    {
        f32 w = mGenInfo.GetIconWidth();
        f32 h = mGenInfo.GetIconHeight();
        f32 l = mGenInfo.GetIconHeight() - mGenInfo.GetIconEdgeWidth();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(0.0f, l, 0.0f);
            GXPosition3f32(w, l, 0.0f);
            GXPosition3f32(w, h, 0.0f);
            GXPosition3f32(0.0f, h, 0.0f);
        }
        GXEnd();
    }

    {
        f32 w = mGenInfo.GetIconEdgeWidth();
        f32 r = mGenInfo.GetIconHeight();

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXPosition3f32(w, 0.0f, 0.0f);
            GXPosition3f32(w, r, 0.0f);
            GXPosition3f32(0.0f, r, 0.0f);
        }
        GXEnd();
    }

    GXDrawDone();

    mpCapTexture->disableVFilter();
    mpCapTexture->enablePixModeSync();

    if (mGenInfo.GetIconMipMap()) {
        mpCapTexture->capture(0, 0, true);
    } else {
        mpCapTexture->capture(0, 0, false);
    }

    mpCapTexture->flush();
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

    EGG::ResTIMG* pResTIMG = GetResTIMG();

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

    if (mGenInfo.GetIconMipMap()) {
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

    InitCapTexture(mGenInfo.GetIconWidth(), mGenInfo.GetIconHeight(),
                   GX_TF_RGB5A3);

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
        (1 << mGenInfo.GetIconExpression()) | RFLExpFlag_Normal,
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

    pKokeshiManager->CreateTexture(GetResTIMG());
    pNigaoeModel->RemoveGenList();

    // Restore original management
    pNglHeap->destroy();
    RPGrpModel::SetAllocator(pOldAllocator);
    pOldHeap->becomeCurrentHeap();

    RPSysAvatar::Setup();
}
