#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModelAnm;
class RPGrpModelMaterial;

/**
 * @brief Base class for model implementations
 */
class RPGrpModel {
public:
    /**
     * @brief Model class type
     */
    enum Kind {
        Kind_None, //!< Dummy value
        Kind_G3D,  //!< RPGrpModelG3D
        Kind_Rfl,  //!< RPGrpModelRfl
    };

protected:
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    u8 mDrawGroup; // at 0x2
    char unk3;
    u16 mFlags; // at 0x4
    char unk6[0x2C - 0x6];
    RPGrpModelAnm* mpModelAnm;         // at 0x2C
    RPGrpModelMaterial** mppMaterials; // at 0x30
    char unk34[0x40 - 0x34];
    EGG::ModelEx* mpModelEx; // at 0x40

public:
    // TODO(kiwi) Probably in ghidra already
    virtual UNKTYPE VF_0x8(UNKTYPE) = 0; // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0; // at 0xC

    virtual UNKTYPE VF_0x10(UNKTYPE) = 0; // at 0x10
    virtual Kind GetKind() = 0;           // at 0x14
    virtual UNKTYPE VF_0x18(UNKTYPE) = 0; // at 0x18
    virtual UNKTYPE VF_0x1C(UNKTYPE) = 0; // at 0x1C

    virtual UNKTYPE VF_0x20(UNKTYPE) = 0;          // at 0x20
    virtual UNKTYPE VF_0x24(UNKTYPE) = 0;          // at 0x24
    virtual UNKTYPE VF_0x28(UNKTYPE) = 0;          // at 0x28
    virtual void SetJointVisible(bool enable) = 0; // at 0x2C

    virtual UNKTYPE VF_0x30(UNKTYPE) = 0;          // at 0x30
    virtual void SetShapeVisible(bool enable) = 0; // at 0x34

    /**
     * @brief Gets the allocator used for model-related allocations
     */
    static EGG::Allocator* GetAllocator() {
        return spAllocator;
    }
    /**
     * @brief Sets the allocator used for model-related allocations
     *
     * @param pAllocator New allocator
     */
    static void SetAllocator(EGG::Allocator* pAllocator) {
        spAllocator = pAllocator;
    }

    /**
     * @brief Removes this model from the global list
     */
    void RemoveGenList();

private:
    //! Allocator used for model-related allocations
    static EGG::Allocator* spAllocator;
};

//! @}

#endif
