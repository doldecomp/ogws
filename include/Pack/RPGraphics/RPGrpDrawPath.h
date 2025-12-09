#ifndef RP_GRAPHICS_DRAW_PATH_H
#define RP_GRAPHICS_DRAW_PATH_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Base class for draw paths
 */
class RPGrpDrawPath {
protected:
    EGG::ScnRenderer* mpRenderer;  // at 0x0
    EGG::DrawPathBase* mpPathImpl; // at 0x4

public:
    template <typename T> T* Construct(EGG::ScnRenderer* pRenderer);

    virtual ~RPGrpDrawPath() {} // at 0x8

    virtual void On() { // at 0xC
        mpPathImpl->setEnable(true);
    }

    virtual void Off() { // at 0x10
        mpPathImpl->setEnable(false);
    }

    virtual bool IsEnable() const { // at 0x10
        return mpPathImpl->isEnable();
    }
};

//! @}

#endif
