#ifndef RP_GRAPHICS_MODEL_MATERIAL_H
#define RP_GRAPHICS_MODEL_MATERIAL_H
#include <Pack/types_pack.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Model material setting
 */
class RPGrpModelMaterial {
public:
    enum ESyncFlag {
        ESyncFlag_ResGenMode = 1 << 0,
    };

private:
    u32 mSyncFlags; // at 0x0
    char unkB[0xB - 0x4];
    u8 mCullMode; // at 0xB
    char _0C[0x20 - 0xC];
    GXColor mTevKColors[GX_MAX_KCOLOR];                // at 0x20
    GXColorS10 mTevColors[GX_MAX_TEVREG - GX_TEVREG0]; // at 0x30
    char unk48[0xD0 - 0x48];

public:
    RPGrpModelMaterial(RPGrpModel* pModel, u16 idx);
    virtual ~RPGrpModelMaterial(); // at 0x8

    void Calc();

    void SetSyncFlags(u32 flags) {
        mSyncFlags |= flags;
    }

    u8 GetCullMode() const {
        return mCullMode;
    }
    void SetCullMode(GXCullMode cullMode) {
        mCullMode = cullMode;
    }

    void SetTevKColor(GXTevKColorID id, GXColor color) {
        mTevKColors[id] = color;
    }
    void SetTevColor(GXTevRegID id, GXColorS10 color) {
        mTevColors[id - GX_TEVREG0] = color;
    }
};

//! @}

#endif
