#ifndef RP_GRAPHICS_MODEL_TEXTURE_H
#define RP_GRAPHICS_MODEL_TEXTURE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Texture utility
 */
class RPGrpTexture {
private:
    GXTexObj mGXTexObj; // at 0x0

public:
    RPGrpTexture();
    RPGrpTexture(RPGrpHandle handle, const char* pName);
    virtual ~RPGrpTexture();

    const GXTexObj& GetTexObj() const {
        return mGXTexObj;
    }
};

//! @}

#endif
