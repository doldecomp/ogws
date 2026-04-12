#ifndef RP_GRAPHICS_PROJECTION_OBJECT_H
#define RP_GRAPHICS_PROJECTION_OBJECT_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpCamera.h>
#include <Pack/RPGraphics/RPGrpModelResManager.h>
#include <Pack/RPGraphics/RPGrpScreen.h>

#include <nw4r/g3d.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpProjectionObject {
private:
    u8 mViewNo;          // at 0x0
    RPGrpCamera mCamera; // at 0x4
    RPGrpScreen mScreen; // at 0x17C

public:
    RPGrpProjectionObject(u8 viewNo);

    virtual ~RPGrpProjectionObject() {} // at 0x8

    void Calc(nw4r::g3d::Camera cam);

    void LoadScnCamera(RPGrpHandle handle, const char* pName, f32 frame = 0.0f);
};

//! @}

#endif
