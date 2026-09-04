#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <nw4r/ef.h>

#include <revolution/MTX.h>

RP_SINGLETON_IMPL_EX(RPSysEffectMgr);

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysEffectMgr::RPSysEffectMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    for (int i = 0; i < EDrawScene_Max; i++) {
        mpEffectCreators[i] = NULL;
    }

    unk14 = NULL;
    nw4r::ef::EffectSystem::GetInstance()->SetXFFlushSafe(true);
}

/**
 * @brief Attaches a new effect creator to the specified scene
 *
 * @param pCreator Effect creator
 * @param drawScene Effect draw scene
 */
void RPSysEffectMgr::setCreator(RPSysEffectCreator* pCreator, u32 drawScene) {
    if (pCreator == NULL) {
        return;
    }

    mpEffectCreators[drawScene] = pCreator;
}

/**
 * @brief Releases the specified effect creator from its scene
 *
 * @param pCreator Effect creator
 */
void RPSysEffectMgr::resetCreator(RPSysEffectCreator* pCreator) {
    if (pCreator == NULL) {
        return;
    }

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == pCreator) {
            mpEffectCreators[i] = NULL;
            break;
        }
    }
}

/**
 * @brief Kills all effects and particles
 */
void RPSysEffectMgr::stopAllEffect() {
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < RPSysEffectDefine::MAX_GROUP_ID; i++) {
        pSystem->RetireEmitterAll(i);
        pSystem->RetireParticleAll(i);
    }

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL) {
            continue;
        }

        if (mpEffectCreators[i]->isSlowSystem()) {
            mpEffectCreators[i]->stopAllEffect();
        }
    }
}

/**
 * @brief Updates the state of effects
 *
 * @param setting Effect update type
 */
void RPSysEffectMgr::update(ECalcSetting setting) {
    (void)nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL) {
            continue;
        }

        if (i == EDrawScene_Cursor) {
            mpEffectCreators[i]->update();
        } else if (setting == ECalcSetting_All) {
            mpEffectCreators[i]->update();
        }
    }
}

/**
 * @brief Applies a framebuffer capture texture to all effects
 *
 * @param pTexture Framebuffer texture
 * @param rData Framebuffer texture information
 */
void RPSysEffectMgr::setCaptureEfb(void* pTexture, const EfbTexData& rData) {
    nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL || !mpEffectCreators[i]->isActive()) {
            continue;
        }

        nw4r::ef::ResTexture res = pResource->FindTexture(
            "dummy_tex", mpEffectCreators[i]->getTextureProject());

        if (res.IsValid()) {
            res.ptr()->format = rData.format;
            res.ptr()->width = rData.width;
            res.ptr()->height = rData.height;
            res.ptr()->texture = static_cast<u8*>(pTexture);
        }
    }
}

/**
 * @brief Draws the specified set of effects
 *
 * @param rDrawInfo Graphics configuration
 * @param drawGroup Effect draw group
 * @param drawScene Effect draw scene
 */
void RPSysEffectMgr::draw(const nw4r::ef::DrawInfo& rDrawInfo, u32 drawGroup,
                          u32 drawScene) {

    nw4r::ef::DrawInfo sceneDrawInfo;
    sceneDrawInfo.SetViewMtx(*rDrawInfo.GetViewMtx());

    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();
    RPGrpView* pView = RPGrpRenderer::GetCurrentView();

    nw4r::math::MTX34 proj;
    if (pView->GetProjType() == RPGrpView::EProjType_Persp) {
        C_MTXLightPerspective(proj, pScreen->GetFovy(), pScreen->GetAspect(),
                              0.5f, -0.5f, 0.5f, 0.5f);
    } else {
        f32 cx = pScreen->GetWidth() / 2.0f;
        f32 cy = pScreen->GetHeight() / 2.0f;
        C_MTXLightOrtho(proj, cy, -cy, -cx, cx, 0.5f, -0.5f, 0.5f, 0.5f);
    }

    sceneDrawInfo.SetProjMtx(proj);

    if (drawGroup < EDrawGroup_16) {
        for (int i = 0; i < EDrawScene_Max; i++) {
            if (mpEffectCreators[i] == NULL) {
                continue;
            }

            mpEffectCreators[i]->draw(sceneDrawInfo, drawGroup, drawScene);
        }
    }
}

DECOMP_FORCELITERAL(RPSysEffectMgr_cpp,
                    +0.5f,
                    -0.5f,
                    4503599627370496.0);

/**
 * @brief Creates an instance of the specified effect
 *
 * @param pName Effect name
 * @param drawGroup Effect draw group
 * @param drawScene Effect draw scene
 */
nw4r::ef::Effect* RPSysEffectMgr::createEffect(const char* pName, u32 drawGroup,
                                               u32 drawScene) {
    // @bug Effect creator is not validated
#if defined(BUG_FIX)
    if (mpEffectCreators[drawScene] == NULL ||
        !mpEffectCreators[drawScene]->isActive()) {
        return NULL;
    }
#endif

    return mpEffectCreators[drawScene]->createEffect(pName, drawGroup);
}

/**
 * @brief Creates a memory manager using the specified settings
 *
 * @param pArg Effect memory settings
 * @return Effect work memory size
 */
u32 RPSysEffectMgr::createMemoryManager(EffectArg* pArg) {
    u32 workSize = RPSysEffectMemoryManager::CalcMemorySize( //
        pArg->maxEffect,                                     //
        pArg->maxEmitter,                                    //
        pArg->maxParticleManager,                            //
        pArg->maxParticle,                                   //
        RPSysEffectDefine::MAX_GROUP_ID);

    void* pEffectWork = EGG::Heap::alloc(workSize + 32, 32, pArg->pHeap);
    pEffectWork = nw4r::ut::RoundUp(pEffectWork, 32);

    RPSysEffectMemoryManager* pMemoryManager =
        new (pArg->pHeap) RPSysEffectMemoryManager( //
            pEffectWork,                            //
            workSize,                               //
            pArg->maxEffect,                        //
            pArg->maxEmitter,                       //
            pArg->maxParticleManager,               //
            pArg->maxParticle);

    nw4r::ef::EffectSystem::GetInstance()->SetMemoryManager(
        pMemoryManager, RPSysEffectDefine::MAX_GROUP_ID);

    return workSize;
}

/**
 * @brief Loads the assets required by system effect scenes
 */
void RPSysEffectMgr::LoadResource() {
    if (mpEffectCreators[EDrawScene_Cursor] != NULL &&
        !mpEffectCreators[EDrawScene_Cursor]->isActive()) {

        RPSysSceneCreator::EPackID pack =
            RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

        EGG::Archive* pCursorArchive = NULL;

        switch (pack) {
        case RPSysSceneCreator::EPackID_SportsPack: {
        case RPSysSceneCreator::EPackID_PartyPack: {
            pCursorArchive =
                RP_GET_INSTANCE(RPSysResourceManager)->GetStaticCommonArchive();
            break;
        }

        /* EPackID_HealthPack, EPackID_MusicPack */
        default: {
            pCursorArchive =
                RP_GET_INSTANCE(RPSysResourceManager)->GetStaticLayoutArchive();
            break;
        }
        }
        }

        void* pCursorEffect = NULL;
        void* pCursorTexture = NULL;

        switch (pack) {
        case RPSysSceneCreator::EPackID_SportsPack: {
        case RPSysSceneCreator::EPackID_PartyPack: {
            pCursorEffect = RPSysResourceManager::GetFileFromArchive(
                pCursorArchive, "nw4r_defcursor_pack.breff");

            pCursorTexture = RPSysResourceManager::GetFileFromArchive(
                pCursorArchive, "nw4r_defcursor_pack.breft");
            break;
        }

        /* EPackID_HealthPack, EPackID_MusicPack */
        default: {
            pCursorEffect = RPSysResourceManager::GetFileFromArchive(
                pCursorArchive, "pack_cursor_fix.breff");

            pCursorTexture = RPSysResourceManager::GetFileFromArchive(
                pCursorArchive, "pack_cursor_fix.breft");
            break;
        }
        }
        }

        mpEffectCreators[EDrawScene_Cursor]->setEffectResource(pCursorEffect,
                                                               pCursorTexture);
    }

    if (mpEffectCreators[EDrawScene_Static] != NULL &&
        !mpEffectCreators[EDrawScene_Static]->isActive()) {

        EGG::Archive* pStaticArchive = NULL;

        RPSysSceneCreator::EPackID pack =
            RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

        switch (pack) {
        case RPSysSceneCreator::EPackID_SportsPack: {
        case RPSysSceneCreator::EPackID_PartyPack: {
            pStaticArchive =
                RP_GET_INSTANCE(RPSysResourceManager)->GetStaticCommonArchive();
            break;
        }

        /* EPackID_HealthPack, EPackID_MusicPack */
        default: {
            pStaticArchive =
                RP_GET_INSTANCE(RPSysResourceManager)->GetStaticLayoutArchive();
            break;
        }
        }
        }

        void* pStaticEffect;
        void* pStaticTexture;

        const char* pFileNames[][2] = {
            // EPackID_SportsPack
            "sports_common.breff",
            "sports_common.breft",

            // EPackID_PartyPack
            "basic_common.breff",
            "basic_common.breft",

            // EPackID_HealthPack
            NULL, // huh???
            NULL,

            // EPackID_MusicPack
            "effect_music.breff",
            "effect_music.breft",
        };

        if (pFileNames[pack][0] && pFileNames[pack][1] != NULL) {
            pStaticEffect = RPSysResourceManager::GetFileFromArchive(
                pStaticArchive, pFileNames[pack][0]);

            pStaticTexture = RPSysResourceManager::GetFileFromArchive(
                pStaticArchive, pFileNames[pack][1]);

            mpEffectCreators[EDrawScene_Static]->setEffectResource(
                pStaticEffect, pStaticTexture);
        }
    }
}

/**
 * @brief Destructor
 */
RPSysEffectMgr::~RPSysEffectMgr() {
    stopAllEffect();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] != NULL) {
            delete mpEffectCreators[i];
        }
    }

    nw4r::ef::Resource::GetInstance()->Initialize();
    EGG::Heap::free(unk14, NULL);
}
