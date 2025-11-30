#ifndef HOME_BUTTON_MINI_LIB_API_H
#define HOME_BUTTON_MINI_LIB_API_H
#ifdef __cplusplus
extern "C" {
#endif

#include <homeButtonMiniLib/HBMTypes.h>

void HBMCreate(const HBMDataInfo* pHBInfo);
void HBMInit();

HBMSelectBtnNum HBMCalc(const HBMControllerData* pController);
void HBMDraw();

void HBMSetAdjustFlag(BOOL flag);
void HBMStartBlackOut();
void HBMSetBlackOutColor(u8 r, u8 g, u8 b);

#ifdef __cplusplus
}
#endif
#endif
