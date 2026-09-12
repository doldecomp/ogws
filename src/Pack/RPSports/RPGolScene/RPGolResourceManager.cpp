#include <Pack/RPSports/RPGolScene.h>
#include <Pack/RPSystem.h>

RP_SINGLETON_IMPL(RPGolResourceManager);

RPGolResourceManager::RPGolResourceManager()
    : mppArchives(NULL), unk8(NULL), unkC(NULL), unk10(NULL), unk14(NULL) {}

RPGolResourceManager::~RPGolResourceManager() {}

void* RPGolResourceManager::hasFile(const char* pName, EArchive archive) {
    return RPSysResourceManager::GetFileFromArchive(
        instance()->mppArchives[archive], pName);
}

bool RPGolResourceManager::checkFile(const char* pName, EArchive archive) {
    return (instance()->mppArchives[archive])->getFile(pName, NULL) != NULL;
}

RPGrpHandle RPGolResourceManager::createModel(const char* pName,
                                              EArchive archive) {
    RPGrpModelResManager* pResMgr = pResMgr->GetCurrent();

    void* pFileData = RPSysResourceManager::GetFileFromArchive(
        (instance()->mppArchives[archive]), pName);
    return pResMgr->CreateData(RPGrpModelResManager::Type_ResFile, pFileData);
}
