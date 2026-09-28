#ifndef RP_GRAPHICS_MODEL_SCENE_H
#define RP_GRAPHICS_MODEL_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <egg/gfxe.h>

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
    char unk00[0x2];
    char mIdx; // at 0x2
    char unk03;
    u8 unk04;
    char unk05[0x3];
    u8 unk08;
    char unk09[0x3];
    EGG::LightManager* mpLightManager; // at 0xC
    EGG::FogManager* mpFogManager;     // at 0x10
    char unk14[0x88];
    EGG::ScnRootEx* mpScnRootEx; // at 0x9C
    char unkA0[0x4];

public:
    virtual ~RPGrpModelScene();                      // at 0x8
    virtual void CalcView();                         // at 0xC
    virtual void CalcDrawList();                     // at 0x10
    virtual void Draw();                             // at 0x14
    virtual void DrawFinish();                       // at 0x18
    virtual void PreConditionForRenderingGX() const; // at 0x1C

    void g_calc_background();

    void DrawPrepare(const RPGrpCamera* pCamera, const RPGrpScreen* pScreen);

    void setDrawPriority(RPGrpModel* pModel) const;

    /**
     * @brief Initializes a scene's projection matrix,
     * ambient lights, and fog GX
     */
    void setupGX() const;
};

//! @}

#endif
