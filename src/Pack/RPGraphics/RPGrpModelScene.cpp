#include <Pack/RPGraphics.h>

#include <egg/gfxe/eggScnRenderer.h>

void RPGrpModelScene::DrawPrepare(const RPGrpCamera* pCamera,
                                  const RPGrpScreen* pScreen) {
    mpScnRenderer->SetCurrentCamera(mCameraIndex++,
                                    pCamera->GetSavedCameraMatrix(), *pScreen);
    mpScnRenderer->CalcView();
}
