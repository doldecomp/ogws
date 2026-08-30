#include <Pack/RPAudio.h>
#include <Pack/RPSystem.h>

#if defined(PACK_SPORTS)
#include <Pack/RPSports/RPBowScene.h>
#include <Pack/RPSports/RPBoxScene.h>
#include <Pack/RPSports/RPBsbScene.h>
#include <Pack/RPSports/RPGolScene.h>
#include <Pack/RPSports/RPSportsCommon.h>
#include <Pack/RPSports/RPTnsScene.h>
#elif defined(PACK_PARTY)
#include <Pack/RPParty/RPBilScene.h>
#include <Pack/RPParty/RPBomScene.h>
#include <Pack/RPParty/RPCowScene.h>
#include <Pack/RPParty/RPDucScene.h>
#include <Pack/RPParty/RPFshScene.h>
#include <Pack/RPParty/RPHkyScene.h>
#include <Pack/RPParty/RPPartyCommon.h>
#include <Pack/RPParty/RPPnpScene.h>
#include <Pack/RPParty/RPTnkScene.h>
#include <Pack/RPParty/RPWlyScene.h>
#endif

RP_SINGLETON_IMPL_EX(RPSysSceneCreator);

#if defined(PACK_SPORTS)
#define RP_COMMON_DIR "RPCommon/"
#elif defined(PACK_PARTY)
#define RP_COMMON_DIR "RPPartyCommon/"
#endif

/**
 * @brief Information about every Pack Project scene
 */
const RPSysSceneCreator::SceneAttr RPSysSceneCreator::SCENE_ATTR_TABLE[] = {
    // clang-format off
    {ESceneID_RPSysBootScene,               EPackID_AllPack,    ECreateType_Standard, ELoadType_Blank, EExitType_Sibling,  EAudioType_Common, RP_COMMON_DIR,           /* Logo                         */ "ロゴ"},
    {ESceneID_RPSysPlayerSelectScene,       EPackID_AllPack,    ECreateType_Standard, ELoadType_Blank, EExitType_2,        EAudioType_Common, RP_COMMON_DIR,           /* Player Select                */ "プレイヤーセレクト"},
    {ESceneID_RPSysNunchukCheckScene,       EPackID_AllPack,    ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Scene,  RP_COMMON_DIR,           /* Nunchuk Check                */ "ヌンチャクチェック"},

#if defined(PACK_SPORTS)
    {ESceneID_RPBsbScene,                   EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPBsbScene/",           /* Baseball                     */ "野球"},
    {ESceneID_RPBowScene,                   EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPBowScene/",           /* Bowling                      */ "ボウリング"},
    {ESceneID_RPGolScene,                   EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPGolScene/",           /* Golf                         */ "ゴルフ"},
    {ESceneID_RPTnsScene,                   EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPTnsScene/",           /* Tennis                       */ "テニス"},
    {ESceneID_RPBoxScene,                   EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPBoxScene/",           /* Boxing                       */ "ボクシング"},
    {ESceneID_RPSportsPackTitleScene,       EPackID_SportsPack, ECreateType_Standard, ELoadType_Blank, EExitType_Sibling,  EAudioType_Common, "RPSportsTitle/",        /* Sports Pack                  */ "スポーツパック"},
    {ESceneID_RPSportsMainScene,            EPackID_SportsPack, ECreateType_Standard, ELoadType_Blank, EExitType_2,        EAudioType_Common, "RPSportsCommon/",       /* Sports Menu Select           */ "スポーツメニューセレクト"},
    {ESceneID_RPSportsTrainingMenuScene,    EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Common, "RPSportsTrainingMenu/", /* Training Menu                */ "トレーニングメニュー"},
    {ESceneID_RPSportsPhysicalMenuScene,    EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Common, "RPSportsPhysical/",     /* Physical Measure Menu        */ "体力測定メニュー"},
    {ESceneID_RPSportsPhysicalPreviewScene, EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Common, "RPSportsPhysical/",     /* Physical Measure Explanation */ "体力測定説明"},
    {ESceneID_RPSportsPhysicalResultScene,  EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Common, "RPSportsPhysical/",     /* Physical Measure Results     */ "体力測定結果"},
    {ESceneID_RPGolCourseSelectScene,       EPackID_SportsPack, ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPGolScene/",           /* Golf Course Select           */ "ゴルフコースセレクト"},
#endif
    
#if defined(PACK_PARTY)
    {ESceneID_RPFshScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPFshScene/",           /* Fishing                      */ "釣り"},
    {ESceneID_RPHkyScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPHkyScene/",           /* Hockey                       */ "ホッケー"},
    {ESceneID_RPDucScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPDucScene/",           /* Shooting                     */ "射撃"},
    {ESceneID_RPPnpScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPPnpScene/",           /* Table Tennis                 */ "卓球"},
    {ESceneID_RPBilScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPBilScene/",           /* Billiards                    */ "ビリヤード"},
    {ESceneID_RPCowScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPCowScene/",           /* Cow Race                     */ "牛レース"},
    {ESceneID_RPWlyScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPWlyScene/",           /* Wally                        */ "ウォーリー"},
    {ESceneID_RPTnkScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPTnkScene/",           /* Tank                         */ "タンク"},
    {ESceneID_RPBomScene,                   EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_Standard, EAudioType_Scene,  "RPBomScene/",           /* Bomb                         */ "爆弾"},
    {ESceneID_RPPartyPackTitleScene,        EPackID_PartyPack,  ECreateType_Standard, ELoadType_Blank, EExitType_Sibling,  EAudioType_Common, "RPPartyTitle/",         /* Party Pack                   */ "パーティパック"},
    {ESceneID_RPPartyRootScene,             EPackID_PartyPack,  ECreateType_Standard, ELoadType_Blank, EExitType_Child,    EAudioType_Common, "RPPartyCommon/",        /* Tour Menu                    */ "ツアーメニュー"},
    {ESceneID_RPPartyMainScene,             EPackID_PartyPack,  ECreateType_Sibling,  ELoadType_Blank, EExitType_3,        EAudioType_Common, "RPPartyCommon/",        /* Tour Menu                    */ "ツアーメニュー"},
#endif
    // clang-format on
};

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysSceneCreator::RPSysSceneCreator(EGG::Heap* pHeap)
    : mpParentHeap(pHeap), mPrevSceneID(-1) {}

/**
 * @brief Gets the index of the specified scene's entry in the table
 *
 * @param id Scene ID
 * @return Entry index, or -1 if not found
 */
s32 RPSysSceneCreator::getEntryIndex(ESceneID id) {
    for (s32 i = 0; i < LENGTHOF(SCENE_ATTR_TABLE); i++) {
        if (SCENE_ATTR_TABLE[i].scene == id) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Requests a scene change after fading out
 * @details A scene id of -1 will select the current scene.
 *
 * @param id New scene ID
 * @param reconfigure Whether to fully reconfigure the scene
 * @return Success
 */
bool RPSysSceneCreator::changeSceneAfterFade(s32 id, bool reconfigure) {
    bool success = false;

    if (RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished()) {
        int current = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();

        if (reconfigure) {
            id = current;
        }

        success = RP_GET_INSTANCE(RPSysSceneMgr)
                      ->changeNextSceneAfterFade(id, reconfigure);

        if (success && current >= 0) {
            // Fade out audio before switching sound archives
            if (getAudioType(current) != getAudioType(id)) {
                u16 frames = RP_GET_INSTANCE(RPSysSceneMgr)->getFadeFrame();
                RP_GET_INSTANCE(RPSndAudioMgr)->fadeOutAllSound(frames);
            }

            if (getExitType(id) != EExitType_Child) {
                mPrevSceneID = current;
            }
        }
    }

    return success;
}

/**
 * @brief Changes to the title scene
 *
 * @return Success
 */
bool RPSysSceneCreator::changeSoftReset() {
#if defined(PACK_SPORTS)
    return changeSceneAfterFade(ESceneID_RPSportsPackTitleScene);
#elif defined(PACK_PARTY)
    return changeSceneAfterFade(ESceneID_RPPartyPackTitleScene);
#endif
}

/**
 * @brief Creates the specified scene
 *
 * @param id Scene ID
 */
EGG::Scene* RPSysSceneCreator::create(s32 id) {
    RPSysScene* pScene = NULL;

    switch (getPackID(id)) {
    case EPackID_SportsPack: {
#if defined(PACK_SPORTS)
        pScene = createSportsScene(id);
#else
        pScene = NULL;
#endif
        break;
    }

    case EPackID_PartyPack: {
#if defined(PACK_PARTY)
        pScene = createPartyScene(id);
#else
        pScene = NULL;
#endif
        break;
    }

    case EPackID_HealthPack: {
#if defined(PACK_HEALTH)
        pScene = createHealthScene(id);
#else
        pScene = NULL;
#endif
        break;
    }

    case EPackID_MusicPack: {
#if defined(PACK_MUSIC)
        pScene = createMusicScene(id);
#else
        pScene = NULL;
#endif
        break;
    }

    case EPackID_AllPack: {
        switch (id) {
        case ESceneID_RPSysBootScene: {
            pScene = new RPSysBootScene();
            break;
        }

        case ESceneID_RPSysPlayerSelectScene: {
            pScene = new RPSysPlayerSelectScene();
            break;
        }

        case ESceneID_RPSysNunchukCheckScene: {
            pScene = new RPSysNunchukCheckScene();
            break;
        }

        default: {
            pScene = NULL;
            break;
        }
        }

        break;
    }

    default: {
        break;
    }
    }

    if (pScene != NULL) {
        if (getLoadType(id) == ELoadType_Message) {
            pScene->enableLoadMessage();
        }

        if (getExitType(id) == EExitType_Child) {
            pScene->setChildScene();
        }

        pScene->setCreatorSceneID(mPrevSceneID);
    }

    return pScene;
}

/**
 * @brief Destroys the specified scene
 *
 * @param id Scene ID
 */
void RPSysSceneCreator::destroy(s32 /* id */) {
    if (RP_GET_INSTANCE(RPSysSceneMgr)->isApplicationEndReserved()) {
        RP_GET_INSTANCE(RPSysSystem)->systemShutDown();
    }
}

/**
 * @brief Gets the specified scene's resource directory
 * @details A scene id of -1 will select the current scene.
 *
 * @param id Scene ID
 */
const char* RPSysSceneCreator::getResDirName(s32 id) {
    if (id < 0) {
        id = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    }

    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return RP_COMMON_DIR;
    }
#endif

    return SCENE_ATTR_TABLE[index].pResDirName;
}

/**
 * @brief Gets the specified scene's sport ID
 * @details A scene id of -1 will select the current scene.
 * @note If no sport corresponds to the scene, this function returns -1.
 *
 * @param id Scene ID
 */
s32 RPSysSceneCreator::getSportID(s32 id) {
    if (id < 0) {
        id = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    }

    switch (id) {
    case ESceneID_RPBsbScene: {
        return ESportID_Bsb;
    }

    case ESceneID_RPTnsScene: {
        return ESportID_Tns;
    }

    case ESceneID_RPGolScene: {
        return ESportID_Gol;
    }

    case ESceneID_RPBoxScene: {
        return ESportID_Box;
    }

    case ESceneID_RPBowScene: {
        return ESportID_Bow;
    }

    default: {
        return -1;
    }
    }
}

/**
 * @brief Gets the specified sport's scene ID
 * @note If no scene corresponds to the sport, this function returns -1.
 *
 * @param sport Sport ID
 */
s32 RPSysSceneCreator::getSceneID(ESportID sport) {
    switch (sport) {
    case ESportID_Bsb: {
        return ESceneID_RPBsbScene;
    }

    case ESportID_Tns: {
        return ESceneID_RPTnsScene;
    }

    case ESportID_Gol: {
        return ESceneID_RPGolScene;
    }

    case ESportID_Box: {
        return ESceneID_RPBoxScene;
    }

    case ESportID_Bow: {
        return ESceneID_RPBowScene;
    }

    default: {
        return -1;
    }
    }
}

/**
 * @brief Gets the specified scene's pack ID
 *
 * @param id Scene ID
 */
RPSysSceneCreator::EPackID RPSysSceneCreator::getPackID(s32 id) {
    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return EPackID_AllPack;
    }
#endif

    return SCENE_ATTR_TABLE[index].pack;
}

/**
 * @brief Gets the specified scene's creation type
 *
 * @param id Scene ID
 */
RPSysSceneCreator::ECreateType RPSysSceneCreator::getCreateType(s32 id) {
    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return ECreateType_Standard;
    }
#endif

    return SCENE_ATTR_TABLE[index].createType;
}

/**
 * @brief Gets the specified scene's load type
 *
 * @param id Scene ID
 */
RPSysSceneCreator::ELoadType RPSysSceneCreator::getLoadType(s32 id) {
    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return ELoadType_Blank;
    }
#endif

    return SCENE_ATTR_TABLE[index].loadType;
}

/**
 * @brief Gets the specified scene's exit type
 *
 * @param id Scene ID
 */
RPSysSceneCreator::EExitType RPSysSceneCreator::getExitType(s32 id) {
    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return EExitType_Standard;
    }
#endif

    return SCENE_ATTR_TABLE[index].exitType;
}

/**
 * @brief Gets the specified scene's audio type
 *
 * @param id Scene ID
 */
RPSysSceneCreator::EAudioType RPSysSceneCreator::getAudioType(s32 id) {
    s32 index = getEntryIndex(static_cast<ESceneID>(id));

// @bug Table index is not validated
#if defined(BUG_FIX)
    if (index < 0) {
        return EAudioType_Scene;
    }
#endif

    return SCENE_ATTR_TABLE[index].audioType;
}

#if defined(PACK_SPORTS)
/**
 * @brief Creates the specified Sports Pack scene
 *
 * @param id Scene ID
 */
RPSysScene* RPSysSceneCreator::createSportsScene(s32 id) {
    switch (id) {
    case ESceneID_RPBsbScene: {
        return new RPBsbScene();
    }

    case ESceneID_RPBowScene: {
        return new RPBowScene();
    }

    case ESceneID_RPGolScene: {
        return new RPGolScene();
    }

    case ESceneID_RPTnsScene: {
        return new RPTnsScene();
    }

    case ESceneID_RPBoxScene: {
        return new RPBoxScene();
    }

    case ESceneID_RPSportsPackTitleScene: {
        return new RPSportsPackTitleScene();
    }

    case ESceneID_RPSportsMainScene: {
        return new RPSportsMainScene();
    }

    case ESceneID_RPSportsTrainingMenuScene: {
        return new RPSportsTrainingMenuScene();
    }

    case ESceneID_RPSportsPhysicalMenuScene: {
        return new RPSportsPhysicalMenuScene();
    }

    case ESceneID_RPSportsPhysicalPreviewScene: {
        return new RPSportsPhysicalPreviewScene();
    }

    case ESceneID_RPSportsPhysicalResultScene: {
        return new RPSportsPhysicalResultScene();
    }

    case ESceneID_RPGolCourseSelectScene: {
        return new RPGolCourseSelectScene();
    }

    default: {
        return NULL;
    }
    }
}
#endif

#if defined(PACK_PARTY)
/**
 * @brief Creates the specified Party Pack scene
 *
 * @param id Scene ID
 */
RPSysScene* RPSysSceneCreator::createPartyScene(s32 id) {
    switch (id) {
    case ESceneID_RPFshScene: {
        return new RPFshScene();
    }

    case ESceneID_RPHkyScene: {
        return new RPHkyScene();
    }

    case ESceneID_RPDucScene: {
        return new RPDucScene();
    }

    case ESceneID_RPPnpScene: {
        return new RPPnpScene();
    }

    case ESceneID_RPBilScene: {
        return new RPBilScene();
    }

    case ESceneID_RPCowScene: {
        return new RPCowScene();
    }

    case ESceneID_RPWlyScene: {
        return new RPWlyScene();
    }

    case ESceneID_RPTnkScene: {
        return new RPTnkScene();
    }

    case ESceneID_RPBomScene: {
        return new RPBomScene();
    }

    case ESceneID_RPPartyPackTitleScene: {
        return new RPPartyPackTitleScene();
    }

    case ESceneID_RPPartyRootScene: {
        return new RPPartyRootScene();
    }

    case ESceneID_RPPartyMainScene: {
        return new RPPartyMainScene();
    }

    default: {
        return NULL;
    }
    }
}
#endif

/**
 * @brief Destructor
 */
RPSysSceneCreator::~RPSysSceneCreator() {}
