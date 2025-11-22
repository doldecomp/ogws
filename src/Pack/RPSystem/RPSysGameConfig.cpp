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
      mLanguage(this, "Language"),
      mRPPrint(this, "RPPrint"),
      mRPSysPrint(this, "RPSysPrint"),
      mRPUtlPrint(this, "RPUtlPrint"),
      mRPAudPrint(this, "RPAudPrint"),
      mRPSndPrint(this, "RPSndPrint"),
      mRPUserPrint(this, "RPUserPrint"),
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
      mGameOpen(this, "GameOpen") {

    mRootScene.set(NULL);
    mTVMode.set(NULL);
    mLanguage.set(NULL);

    mRPPrint.set(false);
    mRPSysPrint.set(false);
    mRPUtlPrint.set(false);
    mRPAudPrint.set(false);
    mRPSndPrint.set(false);
    mRPUserPrint.set(false);

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

    mGameOpen.set(false);
}

/**
 * @brief Destructor
 */
RPSysGameConfig::~RPSysGameConfig() {}
