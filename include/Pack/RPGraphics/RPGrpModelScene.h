#ifndef RP_GRAPHICS_MODEL_SCENE_H
#define RP_GRAPHICS_MODEL_SCENE_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;
class RPGrpScreen;

namespace EGG {
class ScnRenderer;
}

/**
 * @brief Model rendering scene
 */
class RPGrpModelScene {
private:
    char unk00[0x2];
    u8 mCameraIndex; // at 0x2
    char unk03[0x9C - 0x3];
    EGG::ScnRenderer* mpScnRenderer; // at 0x9C
    char unkA0[0xA4 - 0xA0];

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
