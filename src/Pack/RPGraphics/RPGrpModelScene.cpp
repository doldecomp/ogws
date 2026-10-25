#include <Pack/RPGraphics.h>

RPGrpModelScene::~RPGrpModelScene() {}

void RPGrpModelScene::CalcView() {
    mpScnRootEx->UpdateFrame();
    mpScnRootEx->CalcWorld();
}

void RPGrpModelScene::g_calc_background() {
    mIdx = 0;
    mpScnRootEx->CalcVtx();
    mpScnRootEx->CalcMaterial();
}

void RPGrpModelScene::setupGX() const {
    mpScnRootEx->getScreen().SetProjectionGX();
    mpLightManager->SetChanAmbColor();
    mpLightManager->LoadObjIndxGX();
    mpFogManager->GetFog(0)->SetGX();
}
