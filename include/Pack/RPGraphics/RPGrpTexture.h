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
    /**
     * @brief Constructor that uses a texture image resource.
     *
     * @param pRes Texture image resource
     */
    RPGrpTexture(const EGG::ResTIMG* pRes);

    /**
     * @brief Constructor that uses a texture resource from a resource file
     * handle.
     *
     * @param handle Resource file handle
     * @param pName File name.
     */
    RPGrpTexture(RPGrpHandle handle, const char* pName);

    virtual ~RPGrpTexture() {}

    const GXTexObj& GetTexObj() const {
        return mGXTexObj;
    }
};

//! @}

#endif
