#ifndef RP_GRAPHICS_CAPTURE_TEXTURE_H
#define RP_GRAPHICS_CAPTURE_TEXTURE_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpScreen;

/**
 * @brief Screen capture texture wrapper
 */
class RPGrpCaptureTexture {
public:
    enum {
        EFlag_MipMap = 1 << 0,
    };

private:
    //! State flags
    u16 mFlags; // at 0x0
    //! Capture setting flags
    u16 mCapFlags; // at 0x2

    //! Capture texture implementation
    EGG::CapTexture* mpCapTexture; // at 0x4

public:
    /**
     * @brief Constructor
     *
     * @param pScreen Capture source
     * @param format Texture format
     * @param flags Creation flags
     */
    RPGrpCaptureTexture(RPGrpScreen* pScreen, int format, u32 flags);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpCaptureTexture() {}

    /**
     * @brief Accesses the underlying capture texture
     */
    EGG::CapTexture* GetCapTexture() const {
        return mpCapTexture;
    }
};

//! @}

#endif
