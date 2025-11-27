#ifndef RP_SYSTEM_GAME_CONFIG_H
#define RP_SYSTEM_GAME_CONFIG_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysTagParms.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project Game Config File (`gameConfig.ini`)
 */
class RPSysGameConfig : public RPSysTagParameters {
    RP_SINGLETON_DECL_EX(RPSysGameConfig);

private:
    //! Scene loaded on boot
    RPSysStringTagParm mRootScene; // at 0x10
    //! TV mode (aspect ratio)
    RPSysStringTagParm mTVMode; // at 0x20
    //! Game language
    RPSysStringTagParm mLanguage; // at 0x30

    //! Common print setting
    RPSysPrimTagParm<int> mRPPrint; // at 0x40
    //! System print setting
    RPSysPrimTagParm<int> mRPSysPrint; // at 0x50
    //! Utility print setting
    RPSysPrimTagParm<int> mRPUtlPrint; // at 0x60
    //! Audio print setting
    RPSysPrimTagParm<int> mRPAudPrint; // at 0x70
    //! Sound print setting
    RPSysPrimTagParm<int> mRPSndPrint; // at 0x80
    //! User print setting
    RPSysPrimTagParm<int> mRPUserPrint; // at 0x90

    //! Mr. Sumaki print setting
    RPSysPrimTagParm<int> mRPSmkPrint; // at 0xA0
    //! Mr. Okamura(?) print setting
    RPSysPrimTagParm<int> mRPOkaPrint; // at 0xB0
    //! Unknown
    RPSysPrimTagParm<int> mRPOknPrint; // at 0xC0
    //! Mr. Kasamatsu print setting
    RPSysPrimTagParm<int> mRPKasPrint; // at 0xD0
    //! Mr. Matsutani print setting
    RPSysPrimTagParm<int> mRPMatPrint; // at 0xE0
    //! Mr. Sawaya print setting
    RPSysPrimTagParm<int> mRPSawPrint; // at 0xF0
    //! Mr. Sakakibara print setting
    RPSysPrimTagParm<int> mRPSakPrint; // at 0x100
    //! Mr. Koda print setting
    RPSysPrimTagParm<int> mRPKodPrint; // at 0x110
    //! Mr. Sakaguchi print setting
    RPSysPrimTagParm<int> mRPGutPrint; // at 0x120
    //! Mr. Sakai print setting
    RPSysPrimTagParm<int> mRPSaiPrint; // at 0x130
    //! Mr. Sumiyoshi print setting
    RPSysPrimTagParm<int> mRPSumPrint; // at 0x140
    //! Mr. Umemiya print setting
    RPSysPrimTagParm<int> mRPUmePrint; // at 0x150

    //! Game open setting
    RPSysPrimTagParm<int> mGameOpen; // at 0x160
};

//! @}

#endif
