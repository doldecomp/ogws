#ifndef RP_GRAPHICS_MODEL_SCENE_H
#define RP_GRAPHICS_MODEL_SCENE_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;
class RPGrpScreen;

/**
 * @brief Model rendering scene
 */
class RPGrpModelScene {
private:
    char unk00[0xA4];

public:
    virtual ~RPGrpModelScene();                      // at 0x8
    virtual void CalcView();                         // at 0xC
    virtual void CalcDrawList();                     // at 0x10
    virtual void Draw();                             // at 0x14
    virtual void DrawFinish();                       // at 0x18
    virtual void PreConditionForRenderingGX() const; // at 0x1C

    void DrawPrepare(const RPGrpCamera* pCamera, const RPGrpScreen* pScreen);
};

//! @}

#endif
