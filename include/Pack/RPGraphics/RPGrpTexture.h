#ifndef RP_GRAPHICS_MODEL_TEXTURE_H
#define RP_GRAPHICS_MODEL_TEXTURE_H
#include <Pack/types_pack.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Texture utility
 */
class RPGrpTexture {
public:
    const GXTexObj& GetTexObj() const {
        return mGXTexObj;
    }

private:
    GXTexObj mGXTexObj; // at 0x0
};

//! @}

#endif
