#include <Pack/RPSystem.h>

#include <cstring>

RP_SINGLETON_IMPL_EX(RPSysProjectLocal);

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysProjectLocal::RPSysProjectLocal(EGG::Heap* pHeap)
    : mpParentHeap(pHeap),

#if BUILD_VERSION == RSPE01_01
      mRegion(ERegion_NTSC_U),
      mDialect(EArea_USA),
      mLanguage(EArea_USA),
      mIsPal50(false),
      mSoundStorage(EStorage_Memory),
#endif

#if defined(PACK_SPORTS)
      mPack(RPSysSceneCreator::EPackID_SportsPack)
#elif defined(PACK_PLAY)
      mPack(RPSysSceneCreator::EPackID_PartyPack)
#endif
{
}

/**
 * @brief Destructor
 */
RPSysProjectLocal::~RPSysProjectLocal() {}

/**
 * @brief Appends the locale directory to the specified path
 *
 * @param pPath Path to append to
 * @param pSuffix Optional suffix to append after the locale
 */
void RPSysProjectLocal::appendLocalDirectory(char* pPath, const char* pSuffix) {
    switch (mDialect) {
    case EArea_England: {
        std::strcat(pPath, "EN/");
        break;
    }

    case EArea_France: {
        std::strcat(pPath, "FR/");
        break;
    }

    case EArea_Germany: {
        std::strcat(pPath, "GE/");
        break;
    }

    case EArea_Italy: {
        std::strcat(pPath, "IT/");
        break;
    }

    case EArea_Spain: {
        std::strcat(pPath, "SP/");
        break;
    }

    case EArea_Netherlands: {
        std::strcat(pPath, "EN/");
        break;
    }

    case EArea_Japan: {
        std::strcat(pPath, "JP/");
        break;
    }

    case EArea_USA: {
        std::strcat(pPath, "US/");
        break;
    }

    default: {
        break;
    }
    }

    // @bug The default argument is an empty string, not NULL
    if (pSuffix != NULL) {
        std::strcat(pPath, pSuffix);
    }
}

/**
 * @brief Sets the current dialect
 *
 * @param dialect Dialect area
 */
void RPSysProjectLocal::setDialect(EArea dialect) {
    mDialect = dialect;
}

/**
 * @brief Sets the current language
 *
 * @param lang Language area
 */
void RPSysProjectLocal::setLanguage(EArea lang) {
    mLanguage = lang;
}
