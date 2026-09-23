#ifndef RP_SYSTEM_SCENE_CREATOR_H
#define RP_SYSTEM_SCENE_CREATOR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysScene;

/**
 * @brief Pack Project scene factory
 */
class RPSysSceneCreator : public EGG::SceneCreator {
    RP_SINGLETON_DECL_EX(RPSysSceneCreator);

public:
    /**
     * @brief Pack Project scene ID
     */
    enum ESceneID {
        // RPSystem
        ESceneID_RPSysBootScene,         //!< Logo
        ESceneID_RPSysPlayerSelectScene, //!< Player Select
        ESceneID_RPSysNunchukCheckScene, //!< Nunchuk Check

        // RPSports
        ESceneID_RPBsbScene,                   //!< Baseball
        ESceneID_RPBowScene,                   //!< Bowling
        ESceneID_RPGolScene,                   //!< Golf
        ESceneID_RPTnsScene,                   //!< Tennis
        ESceneID_RPBoxScene,                   //!< Boxing
        ESceneID_RPSportsPackTitleScene,       //!< Sports Pack
        ESceneID_RPSportsMainScene,            //!< Main Menu
        ESceneID_RPSportsTrainingMenuScene,    //!< Training Menu
        ESceneID_RPSportsPhysicalMenuScene,    //!< Physical Test (Menu)
        ESceneID_RPSportsPhysicalPreviewScene, //!< Physical Test (Description)
        ESceneID_RPSportsPhysicalResultScene,  //!< Physical Test (Result)
        ESceneID_RPGolCourseSelectScene,       //!< Golf (Course Select)

#if defined(PACK_SPORTS)
        ESceneID_Max,
#endif

        // RPParty
        ESceneID_Unknown09h,
        ESceneID_RPFshScene,            //!< Fishing
        ESceneID_RPHkyScene,            //!< Laser Hockey
        ESceneID_RPDucScene,            //!< Shooting Range
        ESceneID_RPPnpScene,            //!< Table Tennis
        ESceneID_RPBilScene,            //!< Billiards
        ESceneID_RPCowScene,            //!< Charge!
        ESceneID_RPWlyScene,            //!< Find Mii
        ESceneID_RPTnkScene,            //!< Tanks!
        ESceneID_RPBomScene,            //!< Pose Mii
        ESceneID_RPPartyPackTitleScene, //!< Party Pack
        ESceneID_RPPartyRootScene,      //!< Mii/GameMgr Setup
        ESceneID_RPPartyMainScene,      //!< Main Menu

#if defined(PACK_PARTY)
        ESceneID_Max,
#endif

    // During the development of Wii Sports and Wii Play,
    // Wii Fit and Wii Music were very early in development.
#if defined(PACK_SPORTS) || defined(PACK_PARTY)
        // RPHealth
        ESceneID_RPHealthTitleScene,    //!< Health Pack
        ESceneID_RPHealthCounselScene,  //!< Counseling
        ESceneID_RPHealthYogaScene,     //!< Yoga
        ESceneID_RPHealthTrainingScene, //!< Training (Menu)
        ESceneID_RPHealthRadioGymScene, //!< Radio Calisthenics
        ESceneID_RPHealthGraphScene,    //!< Health Graph
        ESceneID_RPHealthBalanceScene,  //!< Balance Test
        ESceneID_RPHealthSkiScene,      //!< Balance Ski
        ESceneID_Unknown23h,
        ESceneID_Unknown24h,

        // RPMusic
        ESceneID_RPDrmScene,        //!< Drum
        ESceneID_RPOchScene,        //!< Orchestra
        ESceneID_RPMpeScene1,       //!< Music Experiment 1
        ESceneID_RPMpeScene2,       //!< Music Experiment 2
        ESceneID_RPMpeScene3,       //!< Music Experiment 3
        ESceneID_RPMpeScene4,       //!< Music Experiment 4
        ESceneID_RPMpeScene5,       //!< Music Experiment 5
        ESceneID_RPMusicTitleScene, //!< Music Pack

        // Pack Project
        ESceneID_RPAllPackScene,        //!< Pack Project
        ESceneID_RPBasicDebugScene,     //!< Basic
        ESceneID_RPGraphicsDebugScene,  //!< Graphics
        ESceneID_RPSystemDebugScene,    //!< System
        ESceneID_RPLayoutDebugScene,    //!< Layout
        ESceneID_RPCursorDebugScene,    //!< Cursor
        ESceneID_RPVibrationDebugScene, //!< Vibration
        ESceneID_RPResultDebugScene,    //!< Result
        ESceneID_RPUIDebugScene,        //!< UI Test
        ESceneID_RPSmkTrainingScene,    //!< New Recruit Training (Mr. Sumaki)
        ESceneID_RPMntTrainingScene,    //!< New Recruit Training (Mr. Minato)
        ESceneID_RPBsbDebugScene,       //!< Baseball Debug
        ESceneID_RPDrmDebugScene,       //!< Drum Debug
        ESceneID_RPOchDebugScene,       //!< Orchestra Debug
        ESceneID_RPOchSelectScene,      //!< Orchestra Music Select
#endif
    };

    /**
     * @brief Pack Project game ID
     */
    enum EPackID {
        EPackID_SportsPack, //!< Wii Sports
        EPackID_PartyPack,  //!< Wii Play
        EPackID_HealthPack, //!< Wii Fit
        EPackID_MusicPack,  //!< Wii Music

        EPackID_Max,
        EPackID_AllPack = EPackID_Max, //!< Pack Project
    };

    /**
     * @brief Scene create type
     */
    enum ECreateType {
        ECreateType_Standard, //!< Overwrite outgoing scene
        ECreateType_Sibling,  //!< Become sibling of outgoing scene
        ECreateType_Child,    //!< Become child of outgoing scene
    };

    /**
     * @brief Scene load type
     */
    enum ELoadType {
        ELoadType_Blank,   //!< No additional display
        ELoadType_Message, //!< Display "Now Loading" message
    };

    /**
     * @brief Scene exit type
     */
    enum EExitType {
        EExitType_Standard, //!< Incoming scene overwrites this scene
        EExitType_Sibling,  //!< Incoming scene is a sibling of this scene
        EExitType_2,
        EExitType_3,
        EExitType_Child, //!< Incoming scene is a child of this scene
    };

    /**
     * @brief Scene audio type
     */
    enum EAudioType {
        EAudioType_Scene,  //!< Use the scene's sound archive
        EAudioType_Common, //!< Use the common sound archive
    };

    /**
     * @brief Sport ID
     */
    enum ESportID {
        ESportID_Bsb, //!< Baseball
        ESportID_Tns, //!< Tennis
        ESportID_Gol, //!< Golf
        ESportID_Box, //!< Boxing
        ESportID_Bow, //!< Bowling

        ESportID_Max,
    };

    /**
     * @brief Scene attributes
     */
    struct SceneAttr {
        //! Scene ID
        ESceneID scene; // at 0x0
        //! Pack ID
        EPackID pack; // at 0x4

        //! How to create the scene
        ECreateType createType; // at 0x8
        //! How to load the scene
        ELoadType loadType; // at 0xC
        //! How to exit the scene
        EExitType exitType; // at 0x10
        //! How to configure the scene audio
        EAudioType audioType; // at 0x14

        //! Root resource directory
        const char* pResDirName; // at 0x18
        //! Readable name
        const char* pSceneName; // at 0x1C
    };

public:
    /**
     * @brief Creates the specified scene
     *
     * @param id Scene ID
     */
    virtual EGG::Scene* create(s32 id); // at 0x8

    /**
     * @brief Destroys the specified scene
     *
     * @param id Scene ID
     */
    virtual void destroy(s32 id); // at 0xC

    /**
     * @brief Requests a scene change after fading out
     * @details A scene id of -1 will select the current scene.
     *
     * @param id New scene ID
     * @param reconfigure Whether to fully reconfigure the scene
     * @return Success
     */
    bool changeSceneAfterFade(s32 id, bool reconfigure = false)
        DECOMP_DONT_INLINE;

    /**
     * @brief Changes to the title scene
     *
     * @return Success
     */
    bool changeSoftReset();

    /**
     * @brief Gets the specified scene's resource directory
     * @details A scene id of -1 will select the current scene.
     *
     * @param id Scene ID
     */
    const char* getResDirName(s32 id = -1);

    /**
     * @brief Gets the specified scene's sport ID
     * @details A scene id of -1 will select the current scene.
     * @note If no sport corresponds to the scene, this function returns -1.
     *
     * @param id Scene ID
     */
    s32 getSportID(s32 id = -1);

    /**
     * @brief Gets the specified sport's scene ID
     * @note If no scene corresponds to the sport, this function returns -1.
     *
     * @param sport Sport ID
     */
    s32 getSceneID(ESportID sport);

    /**
     * @brief Gets the specified scene's pack ID
     *
     * @param id Scene ID
     */
    EPackID getPackID(s32 id);

    /**
     * @brief Gets the specified scene's creation type
     *
     * @param id Scene ID
     */
    ECreateType getCreateType(s32 id);

    /**
     * @brief Gets the specified scene's load type
     *
     * @param id Scene ID
     */
    ELoadType getLoadType(s32 id);

    /**
     * @brief Gets the specified scene's exit type
     *
     * @param id Scene ID
     */
    EExitType getExitType(s32 id);

    /**
     * @brief Gets the specified scene's audio type
     *
     * @param id Scene ID
     */
    EAudioType getAudioType(s32 id);

private:
    /**
     * @brief Gets the index of the specified scene's entry in the table
     *
     * @param id Scene ID
     * @return Entry index, or -1 if not found
     */
    s32 getEntryIndex(ESceneID id);

#if defined(PACK_SPORTS)
    /**
     * @brief Creates the specified Sports Pack scene
     *
     * @param id Scene ID
     */
    RPSysScene* createSportsScene(s32 id) DECOMP_DONT_INLINE;
#endif

#if defined(PACK_PARTY)
    /**
     * @brief Creates the specified Party Pack scene
     *
     * @param id Scene ID
     */
    RPSysScene* createPartyScene(s32 id) DECOMP_DONT_INLINE;
#endif

#if defined(PACK_HEALTH)
    /**
     * @brief Creates the specified Health Pack scene
     *
     * @param id Scene ID
     */
    RPSysScene* createHealthScene(s32 id) DECOMP_DONT_INLINE;
#endif

#if defined(PACK_MUSIC)
    /**
     * @brief Creates the specified Music Pack scene
     *
     * @param id Scene ID
     */
    RPSysScene* createMusicScene(s32 id) DECOMP_DONT_INLINE;
#endif

private:
    //! Information about every Pack Project scene
    static const SceneAttr SCENE_ATTR_TABLE[];

    //! ID of the previous scene
    s32 mPrevSceneID; // at 0x8
};

//! @}

#endif
