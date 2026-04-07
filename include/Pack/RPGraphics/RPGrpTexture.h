#ifndef RP_GRAPHICS_TEXTURE_H
#define RP_GRAPHICS_TEXTURE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/gfxe.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCaptureTexture;

/**
 * @brief GPU texture wrapper
 */
class RPGrpTexture {
private:
    //! GX texture object
    GXTexObj mTexObj; // at 0x0

public:
    /**
     * @brief Constructor
     *
     * @param pCpuTexture CPU texture
     */
    explicit RPGrpTexture(const EGG::CpuTexture* pCpuTexture);

    /**
     * @brief Constructor
     *
     * @param pResTIMG Texture image resource
     */
    explicit RPGrpTexture(const EGG::ResTIMG* pResTIMG);

    /**
     * @brief Constructor
     *
     * @param pCapTexture Capture texture
     */
    explicit RPGrpTexture(const RPGrpCaptureTexture* pCapTexture);

    /**
     * @brief Constructor
     *
     * @param handle Resource file handle
     * @param pName Texture name
     */
    RPGrpTexture(RPGrpHandle handle, const char* pName);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpTexture() {}

    /**
     * @brief Accesses the underlying GX texture object
     */
    const GXTexObj& GetTexObj() const {
        return mTexObj;
    }
};

//! @}

#endif
