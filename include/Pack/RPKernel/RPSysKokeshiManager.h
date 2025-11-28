#ifndef RP_KERNEL_KOKESHI_MANAGER_H
#define RP_KERNEL_KOKESHI_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
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
class RPSysMiddleDB;

/**
 * @brief Mii manager
 */
class RPSysKokeshiManager {
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
        OfficialDBState_Unused,   //!< Database index is unused
        OfficialDBState_Valid,    //!< Database index holds a valid Mii
        OfficialDBState_Favorite, //!< Database index holds a favorite Mii
    };

public:
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

    void GetAdditionalInfo(const RPSysKokeshiLocation& rLocation,
                           RFLAdditionalInfo* pInfo);

    void RegistLocation(const RPSysKokeshiLocation& rLocation);

    void GetLocationPlayer(u8 playerNo, RPSysKokeshiLocation* pLocation);

    void GetLocationFriend(RFLDataSource src, RPSysMiddleDB* pMiddleDB,
                           RPSysKokeshiLocation* pLocation);

    RPGrpModel* CreateNigaoeModel(const RPSysKokeshiLocation& rLocation,
                                  RFLResolution res, RFLExpression expr,
                                  u8 viewNo);

    RPGrpModel* CreateModel(void* pFile, u16 index, const char* pName,
                            u8 viewNo, u32 flags, u32 bufferOption);

    RPGrpModel* CreateModel(void* pFile, u16 index, u8 viewNo, u32 flags,
                            u32 bufferOption);

    const char* GetHandFileName(u32 handType) const;

    void ChangeTexture(RPGrpModel*, const char*, const char*);

    void SetMatColor(RPGrpModel* pModel, GXColor, GXColor);

    /**
     * @brief Accesses the specified guest Mii's name
     *
     * @param index Default database index
     */
    const wchar_t* GetGuestName(u16 index) {
        return mpGuestNames[index];
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
     * @brief Gets the body manager used for kokeshi models
     */
    IRPSysKokeshiBodyManager* GetBodyManager() {
        return mpBodyManager;
    }
    /**
     * @brief Sets the body manager used for kokeshi models
     *
     * @param pBodyManager New body manager
     */
    void SetBodyManager(IRPSysKokeshiBodyManager* pBodyManager) {
        mpBodyManager = pBodyManager;
    }

private:
    //! Face library work buffer
    void* mpNglBuffer; // at 0x4

    //! Names for default database ("Guest") Miis
    const wchar_t* mpGuestNames[RFL_DEFAULT_CHAR_MAX]; // at 0x8

    char unk20[0x44 - 0x20];

    //! Data loaders for every controller
    RPSysKokeshiCtrlDataLoader*
        mppCtrlDataLoaders[WPAD_MAX_CONTROLLERS]; // at 0x44

    char unk54[4];

    //! App body manager
    IRPSysKokeshiBodyManager* mpBodyManager; // at 0x58
};

//! @}

#endif
