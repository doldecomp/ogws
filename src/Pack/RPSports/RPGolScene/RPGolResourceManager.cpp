#include <Pack/RPGraphics.h>
#include <Pack/RPSports/RPGolScene.h>

#include <RPSystem.h>

RP_SINGLETON_IMPL(RPGolResourceManager);

RPGolResourceManager::RPGolResourceManager()
    : mppArchives(NULL), unk8(NULL), unkC(NULL), unk10(NULL), unk14(NULL) {}

RPGolResourceManager::~RPGolResourceManager() {}

void* RPGolResourceManager::getFile(const char* pName, int offset) {
    return RP_GET_INSTANCE(RPSysResourceManager)
        ->GetFileFromArchive(spInstance->mppArchives[offset], pName);
}

bool RPGolResourceManager::checkFile(const char* pName, int offset) {
    return (spInstance->mppArchives[offset])->getFile(pName, NULL) != NULL;
}

void RPGolResourceManager::createModel(const char* pName, int offset) {
    RPGrpModelResManager* resMgr = resMgr->GetCurrent();

    void* file =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive((spInstance->mppArchives[offset]), pName);
    resMgr->CreateData(RPGrpModelResManager::Type_ResFile, file, NULL);
}
