#ifndef RP_GRAPHICS_VIEW_H
#define RP_GRAPHICS_VIEW_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;
class RPGrpScreen;

class RPGrpView {
public:
    enum EProjType {
        EProjType_Persp,
        EProjType_Ortho,
        EProjType_Max,
    };

protected:
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    char unk2[0x8 - 0x2];
    EProjType mProjType; // at 0x8
    char unkC[0x10 - 0xC];
    RPGrpScreen* mpScreen; // at 0x10
    char unk14[0x1C - 0x14];

public:
    virtual ~RPGrpView();                                // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0;                 // at 0xC
    virtual void AttachCamera(RPGrpCamera* pCamera) = 0; // at 0x10

    void SetDrawScene(u8 scene) {
        mDrawScene = scene;
    }

    EProjType GetProjType() const {
        return mProjType;
    }

    RPGrpScreen* GetScreen() const {
        return mpScreen;
    }

private:
    ;
};

//! @}

#endif
