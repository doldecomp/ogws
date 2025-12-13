#ifndef RP_KERNEL_KOKESHI_MANAGER_H
#define RP_KERNEL_KOKESHI_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel/IRPSysHostIOSocket.h>
#include <Pack/RPSingleton.h>

#include <RVLFaceLib.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class IRPSysKokeshiBodyManager;
class RPSysKokeshiCtrlDataLoader;
class RPSysKokeshiCtrlMgr;
class RPSysKokeshiLocation;
class RPSysMessage;
class RPSysMiddleDB;
class RPSysOfficialDB;

/**
 * @brief Mii manager
 */
class RPSysKokeshiManager : public IRPSysHostIOSocket {
    RP_SINGLETON_DECL(RPSysKokeshiManager);

public:
    /**
     * @brief Mii clothes type
     */
    enum ClothesType {
        ClothesType_Random = 0xFFFF, //!< Use a random color
        ClothesType_P1,              //!< Use Player 1's blue color
        ClothesType_P2,              //!< Use Player 2's red color
        ClothesType_P3,              //!< Use Player 3's yellow color
        ClothesType_P4,              //!< Use Player 4's green color
        ClothesType_Favorite,        //!< Use the Mii's favorite color
    };

    /**
     * @brief Generation parameter type
     */
    enum GenType {
        GenType_Player,  //!< Use the Mii associated with the info's player
        GenType_Friend,  //!< Pick a random friend Mii
        GenType_Kokeshi, //!< Use the Mii already set in the Kokeshi object
        GenType_None,    //!< Use the default location values
    };

    /**
     * @brief Mii icon camera view
     */
    enum IconView {
        IconView_Front,   //!< Camera sees the front of the Mii
        IconView_Back,    //!< Camera sees the back of the Mii
        IconView_CloseUp, //!< Camera sees a close-up of the front of the Mii
    };

    /**
     * @brief Official DB Mii state
     */
    enum OfficialDBState {
        OfficialDBState_Unused,     //!< Database index is unused
        OfficialDBState_Valid,      //!< Database index holds a valid Mii
        OfficialDBState_Registered, //!< A location has been registered here
    };

    /**
     * @brief Light map texture index
     */
    enum LightMap {
        LightMap_lm_0, //!< "lm_0" texture
        LightMap_lm_1, //!< "lm_1" texture

        LightMap_Max
    };

    /**
     * @brief Clothing texture index
     */
    enum ClothingTexture {
        ClothingTexture_A, //!< "dummy_tex_a" texture
        ClothingTexture_B, //!< "dummy_tex_b" texture

        ClothingTexture_Max
    };

    /**
     * @brief Hand model type
     */
    enum HandType {
        HandType_Human,  //!< Model with fingers
        HandType_Sphere, //!< Spherical model

        HandType_Max
    };

public:
    /**
     * @brief Creates all lightmap textures
     *
     * @param drawScene Draw scene index
     */
    static void CreateLightTexture(u8 drawScene);

    /**
     * @brief Applies the specified expression to the Mii model
     *
     * @param pModel Mii model
     * @param expr New expression
     */
    static void ChangeExpression(RPGrpModel* pModel, RFLExpression expr);

    /**
     * @brief Gets the current expression of the Mii model
     *
     * @param pModel Mii model
     */
    static RFLExpression GetExpression(RPGrpModel* pModel);

    /**
     * @brief Gets the number of valid Miis in the official database
     */
    static u16 GetOfficialDBValidNum();

    /**
     * @brief Finds the official database index holding the Mii with the
     * specified create ID
     *
     * @param pCreateID Mii create ID
     * @return Official database index, or -1 if not found
     */
    static s16 GetOfficialDBIndexFromCreateID(const RFLCreateID* pCreateID);

    /**
     * @brief Resets the manager state
     */
    void Reset();

    /**
     * @brief Sets the material type of the Mii model
     *
     * @param pModel Mii model
     * @param type New material type
     */
    void SetMaterialType(RPGrpModel* pModel, RPGrpModelRfl::MaterialType type);

    /**
     * @brief Sets the brightness color of the Mii model
     *
     * @param pModel Mii model
     * @param color New brightness color
     */
    void SetBrightnessColor(RPGrpModel* pModel, GXColor color);

    /**
     * @brief Loads all static lifetime resources required by this manager
     */
    void LoadStaticResource();

    /**
     * @brief Creates a Kokeshi-related model
     *
     * @param pFile Resource file
     * @param index Model index
     * @param viewNo Renderer view ID
     * @param typeOption Model type option
     * @param bufferOption nw4r::g3d replacement buffer option
     */
    RPGrpModel* CreateModel(void* pFile, u16 index, u8 viewNo, u32 typeOption,
                            u32 bufferOption);

    /**
     * @brief Creates a Kokeshi face model
     *
     * @param rLocation Mii location
     * @param resolution Texture resolution
     * @param exprFlag Facial expression flags
     * @param viewNo Renderer view ID
     */
    RPGrpModel* CreateNigaoeModel(const RPSysKokeshiLocation& rLocation,
                                  RFLResolution resolution, u32 exprFlag,
                                  u8 viewNo);

    /**
     * @brief Creates a Kokeshi-related texture
     *
     * @param pFile Resource file
     * @param pName Texture name
     */
    RPGrpTexture* CreateTexture(void* pFile, const char* pName);

    /**
     * @brief Creates a Kokeshi-related texture
     *
     * @param pTexData Texture data
     */
    RPGrpTexture* CreateTexture(void* pTexData);

    /**
     * @brief Changes the clothing textures of the specified Mii model
     *
     * @param pModel Mii model
     * @param pTextureA Clothing texture A
     * @param pTextureB Clothing texture B
     */
    void ChangeTexture(RPGrpModel* pModel, RPGrpTexture* pTextureA,
                       RPGrpTexture* pTextureB);

    /**
     * @brief Sets the material colors of the specified Mii model
     *
     * @param pModel Mii model
     * @param body Body color
     * @param skin Skin color
     */
    void SetMatColor(RPGrpModel* pModel, GXColor body, GXColor skin);

    /**
     * @brief Configures the TEV color effect of the specified Mii model
     *
     * @param pModel Mii model
     * @param alpha Effect alpha
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     */
    void SetMatTevColorEffect(RPGrpModel* pModel, u8 alpha, u8 r, u8 g, u8 b);

    /**
     * @brief Gets the additional info about the specified Mii
     *
     * @param rLocation Mii location
     * @param[out] pInfo Additional info
     */
    void GetAdditionalInfo(const RPSysKokeshiLocation& rLocation,
                           RFLAdditionalInfo* pInfo);

    /**
     * @brief Removes the model's scaling from the transformation matrix
     *
     * @param[out] pOut Transformation matrix with scaling removed
     * @param pModel Model whose scale should be used
     * @param pIn Initial transformation matrix
     */
    void GetModelBaseScaleInvalidatedMtx(nw4r::math::MTX34* pOut,
                                         RPGrpModel* pModel,
                                         const nw4r::math::MTX34* pIn);

    /**
     * @brief Gets the archive filename for the specified hand type
     *
     * @param type Hand model type
     */
    const char* GetHandFileName(u32 type);

    /**
     * @brief Gets the Mii location for the specified player slot
     * @details If the specified index is invalid, this function provides a
     * random guest Mii location.
     *
     * @param idx Player index
     * @param[out] pLocation Mii location
     */
    void GetLocationPlayer(u8 idx, RPSysKokeshiLocation* pLocation)
        DECOMP_DONT_INLINE;

    /**
     * @brief Gets the Mii location of a "friend" Mii
     *
     * @param src Mii data source
     * @param pMiddleDB Middle database (for RFLDataSource_Middle)
     * @param[out] pLocation Mii location
     */
    void GetLocationFriend(RFLDataSource src, RPSysMiddleDB* pMiddleDB,
                           RPSysKokeshiLocation* pLocation);

    /**
     * @brief Registers the specified Mii location with the in-memory official
     * database
     *
     * @param rLocation Mii location
     */
    void RegistLocation(const RPSysKokeshiLocation& rLocation);

    /**
     * @brief Sets the active controller manager
     *
     * @param pCtrlMgr Controller manager
     */
    void SetCtrlMgr(RPSysKokeshiCtrlMgr* pCtrlMgr);

    /**
     * @brief Clears the active controller manager
     */
    void ClearCtrlMgr();

    /**
     * @brief Updates the active controller manager's state
     */
    void UpdateCtrlMgr();

    /**
     * @brief Accesses the specified guest Mii's name
     *
     * @param index Default database index
     */
    const wchar_t* GetGuestName(u16 index) const {
        return mpGuestNames[index];
    }

    u8 GetOutputAlpha() const {
        return mOutputAlpha;
    }

    /**
     * @brief Accesses the specified controller data loader
     *
     * @param chan WPAD channel
     */
    RPSysKokeshiCtrlDataLoader* GetCtrlDataLoader(s32 chan) const {
        return mppCtrlDataLoaders[chan];
    }

    /**
     * @brief Gets the body manager used for model assets
     */
    IRPSysKokeshiBodyManager* GetBodyManager() const {
        return mpBodyManager;
    }
    /**
     * @brief Sets the body manager used for model assets
     *
     * @param pBodyManager New body manager
     */
    void SetBodyManager(IRPSysKokeshiBodyManager* pBodyManager) {
        mpBodyManager = pBodyManager;
    }

    /**
     * @brief Gets the name of the specified lightmap texture
     *
     * @param i Lightmap texture index
     */
    static const char* GetLightTextureName(u32 i) {
        return LIGHT_TEXTURE_NAMES[i];
    }

private:
    /**
     * @brief Resource loading error
     */
    enum LoadError {
        LoadError_Success, //!< Load successful
        LoadError_Fail,    //!< Load failed
        LoadError_Busy,    //!< Processor is busy
    };

private:
    /**
     * @brief Gets the index of the controller resource heap that is the current
     * global heap
     *
     * @return Controller channel, or -1 if not applicable
     */
    s32 GetCurrentCtrlHeap() const;

private:
    //! Default value for output alpha
    static const u8 DEFAULT_OUTPUT_ALPHA;

    //! Clothing texture filenames
    static const char* CLOTHING_TEXTURE_NAMES[ClothingTexture_Max];
    //! Lightmap texture names
    static const char* LIGHT_TEXTURE_NAMES[LightMap_Max];
    //! Main material name
    static const char* MAIN_MATERIAL_NAME;
    //! Face library resource filename
    static const char* RFL_RES_NAME;
    //! Common message filename
    static const char* COMMON_MESSAGE_NAME;
    //! Hand model filenames
    static const char* HAND_FILE_NAMES[HandType_Max];

    //! Face library work buffer
    u8* mpNglBuffer; // at 0x4
    //! Names for default database ("Guest") Miis
    const wchar_t* mpGuestNames[RFL_DEFAULT_CHAR_MAX]; // at 0x8
    //! Number of attempts before giving up on picking a random friend Mii
    u16 mFriendRandomNum; // at 0x30
    //! Mii model base scale
    f32 mBaseScale; // at 0x34

    f32 unk28;
    f32 unk2C;
    f32 unk30;

    //! Light effect output alpha?
    u8 mOutputAlpha; // at 0x34
    //! Common message file
    RPSysMessage* mpCommonMessage; // at 0x38
    //! Official database
    RPSysOfficialDB* mpOfficialDB; // at 0x3C

    //! Last resource load error
    LoadError mLoadError; // at 0x40

    //! Mii data loaders per controller
    RPSysKokeshiCtrlDataLoader*
        mppCtrlDataLoaders[WPAD_MAX_CONTROLLERS]; // at 0x44
    //! Controller Mii manager
    RPSysKokeshiCtrlMgr* mpCtrlMgr; // at 0x48

    //! Application body manager
    IRPSysKokeshiBodyManager* mpBodyManager; // at 0x58
};

//! @}

#endif
