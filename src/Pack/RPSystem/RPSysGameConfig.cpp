#include <Pack/RPSystem.h>

RP_SINGLETON_IMPL_EX(RPSysGameConfig);

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysGameConfig::RPSysGameConfig(EGG::Heap* pHeap)
    : RPSysTagParameters("GameConfig"),
      mpParentHeap(pHeap),
      mRootScene(this, "RootScene"),
      mTVMode(this, "TVMode"),

#if defined(VERSION_RSPE01_01)
      mLanguage(this, "Language"),
#endif

      mRPPrint(this, "RPPrint"),
      mRPSysPrint(this, "RPSysPrint"),

#if defined(VERSION_RSPE01_01)
      mRPUtlPrint(this, "RPUtlPrint"),
      mRPAudPrint(this, "RPAudPrint"),
#endif

      mRPSndPrint(this, "RPSndPrint"),
      mRPUserPrint(this, "RPUserPrint"),

#if defined(VERSION_RSPE01_01)
      mRPSmkPrint(this, "RPSmkPrint"),
      mRPOkaPrint(this, "RPOkaPrint"),
      mRPOknPrint(this, "RPOknPrint"),
      mRPKasPrint(this, "RPKasPrint"),
      mRPMatPrint(this, "RPMatPrint"),
      mRPSawPrint(this, "RPSawPrint"),
      mRPSakPrint(this, "RPSakPrint"),
      mRPKodPrint(this, "RPKodPrint"),
      mRPGutPrint(this, "RPGutPrint"),
      mRPSaiPrint(this, "RPSaiPrint"),
      mRPSumPrint(this, "RPSumPrint"),
      mRPUmePrint(this, "RPUmePrint"),
#endif

      mGameOpen(this, "GameOpen") {

    mRootScene.set(NULL);
    mTVMode.set(NULL);
#if defined(VERSION_RSPE01_01)
    mLanguage.set(NULL);
#endif

    mRPPrint.set(false);
    mRPSysPrint.set(false);
#if defined(VERSION_RSPE01_01)
    mRPUtlPrint.set(false);
    mRPAudPrint.set(false);
#endif
    mRPSndPrint.set(false);
    mRPUserPrint.set(false);

#if defined(VERSION_RSPE01_01)
    mRPSmkPrint.set(false);
    mRPOkaPrint.set(false);
    mRPOknPrint.set(false);
    mRPKasPrint.set(false);
    mRPMatPrint.set(false);
    mRPSawPrint.set(false);
    mRPSakPrint.set(false);
    mRPKodPrint.set(false);
    mRPGutPrint.set(false);
    mRPSaiPrint.set(false);
    mRPSumPrint.set(false);
    mRPUmePrint.set(false);
#endif

    mGameOpen.set(false);
}

/**
 * @brief Destructor
 */
RPSysGameConfig::~RPSysGameConfig() {}
