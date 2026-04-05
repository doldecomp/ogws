#include <Pack/RPSingleton.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <cstring>

RP_SINGLETON_IMPL(RPSysFontManager);

/**
 * @brief Font resource filenames
 */
const char* RPSysFontManager::RES_FONT_NAMES[ResFontType_Max] = {
    "pac_nRodDb_32_I4.brfnt",   // ResFontType_nRodDb_32_I4
    "pac_nRodDb_32_IA4.brfnt",  // ResFontType_nRodDb_32_IA4
    "pac_nRodDb_62_IA4.brfnt",  // ResFontType_nRodDb_62_IA4
    "pac_nRodDb_200_IA4.brfnt", // ResFontType_nRodDb_200_IA4
    "pac_nRodEb_32_I4.brfnt",   // ResFontType_nRodEb_32_I4
    "pac_nRodEb_70_IA4.brfnt",  // ResFontType_nRodEb_70_IA4
    "pac_healthTime.brfnt",     // ResFontType_HealthTime
};

/**
 * @brief Whether each font resource is required by this pack
 */
const BOOL RPSysFontManager::sIsNeedResFont[ResFontType_Max] = {
    TRUE,  // ResFontType_nRodDb_32_I4
    TRUE,  // ResFontType_nRodDb_32_IA4
    TRUE,  // ResFontType_nRodDb_62_IA4
    FALSE, // ResFontType_nRodDb_200_IA4
    TRUE,  // ResFontType_nRodEb_32_I4
    TRUE,  // ResFontType_nRodEb_70_IA4
    FALSE, // ResFontType_HealthTime
};

/**
 * @brief Constructor
 */
RPSysFontManager::RPSysFontManager() {
    mpRomFont = new nw4r::ut::RomFont();

    for (int i = 0; i < ResFontType_Max; i++) {
        mpResFonts[i] = new nw4r::ut::ResFont();
        mpResFontData[i] = NULL;
    }
}

/**
 * @brief Destructor
 */
RPSysFontManager::~RPSysFontManager() {}

/**
 * @brief Loads the ROM font provided by the system
 */
void RPSysFontManager::LoadRomFont() {
    EGG::Heap* pResHeap = RP_GET_INSTANCE(RPSysSystem)->getResourceHeap();
    u32 requireSize = nw4r::ut::RomFont::GetRequireBufferSize();

    void* pBuffer = new (pResHeap, 32) u8[requireSize];
    mpRomFont->Load(pBuffer);
}

/**
 * @brief Loads all resource fonts required by this pack
 */
void RPSysFontManager::LoadResFonts() {
    EGG::Archive* pFontArchive =
        RP_GET_INSTANCE(RPSysResourceManager)->GetFontArchive();

    for (u8 i = 0; i < ResFontType_Max; i++) {
        if (!sIsNeedResFont[i]) {
            continue;
        }

        LoadResFont(i, pFontArchive);
    }
}

/**
 * @brief Gets the index of the specified resource font
 *
 * @param pName Font name
 */
u8 RPSysFontManager::GetResFontIndex(const char* pName) const {
    for (u8 i = 0; i < ResFontType_Max; i++) {
        if (std::strcmp(pName, RES_FONT_NAMES[i]) == 0) {
            return i;
        }
    }

    return ResFontType_nRodDb_32_I4;
}

/**
 * @brief Gets the data of the specified resource font
 *
 * @param pName Font name
 */
void* RPSysFontManager::GetResFontData(const char* pName) const {
    u8 idx = GetResFontIndex(pName);
    return mpResFontData[idx];
}

/**
 * @brief Loads the specified resource font from the provided archive
 *
 * @param idx Font index
 * @param pArchive Font archive
 */
void RPSysFontManager::LoadResFont(u8 idx, EGG::Archive* pArchive) {
    // TODO(kiwi) Inline?
    ResFontType type = static_cast<ResFontType>(idx);

    void* pResFontData =
        RPSysResourceManager::GetFileFromArchive(pArchive, RES_FONT_NAMES[idx]);

    mpResFontData[idx] = pResFontData;

    if (!mpResFonts[type]->IsManaging(pResFontData)) {
        mpResFonts[type]->SetResource(pResFontData);
        mpResFonts[type]->SetAlternateChar(L'?');
    }
}
