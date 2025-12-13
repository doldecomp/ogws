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
        ESyncFlag_ResMatTev = 1 << 4,
    };

    enum ETevColor {
        ETevColor_Reg0,
        ETevColor_Reg1,
        ETevColor_Reg2,

        ETevColor_Max
    };

    enum ETevKColor {
        ETevKColor_Reg0,
        ETevKColor_Reg1,
        ETevKColor_Reg2,
        ETevKColor_Reg3,

        ETevKColor_Max
    };

    struct ChanCtrl {
        u8 enable;    // at 0x0
        u8 lightMask; // at 0x1
        u8 ambSrc;    // at 0x2
        u8 matSrc;    // at 0x3
        u8 diffuseFn; // at 0x4
        u8 attnFn;    // at 0x5
    };

private:
    u32 mSyncFlags; // at 0x0
    u16 unk4;
    u8 unk6;
    u8 mNumChans;     // at 0x7
    u8 mNumTexGens;   // at 0x8
    u8 mNumTevStages; // at 0x9
    u8 mNumIndStages; // at 0xA
    u8 mCullMode;     // at 0xB
    char unkC[4];
    ChanCtrl* mpChanCtrls[GX_ALPHA1 - GX_COLOR0 + 1]; // at 0x10
    GXColor mTevKColors[ETevKColor_Max];              // at 0x20
    GXColorS10 mTevColors[ETevColor_Max];             // at 0x30
    char unk48[0x9C - 0x48];
    nw4r::g3d::ScnMdl::CopiedMatAccess mCopiedMatAccess; // at 0x9C

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

    void SetTevKColor(ETevKColor idx, GXColor color) {
        mTevKColors[idx] = color;
    }
    void SetTevKColor(ETevKColor idx, u8 r, u8 g, u8 b) {
        mTevKColors[idx].r = r;
        mTevKColors[idx].g = g;
        mTevKColors[idx].b = b;
    }

    void SetTevColor(ETevColor idx, GXColorS10 color) {
        mTevColors[idx] = color;
    }
    void SetTevColor(ETevColor idx, const GXColor& color) {
        mTevColors[idx].r = color.r;
        mTevColors[idx].g = color.g;
        mTevColors[idx].b = color.b;
        mTevColors[idx].a = color.a;
    }
    void SetTevColor(ETevColor idx, u8 r, u8 g, u8 b, u8 a) {
        mTevColors[idx].r = r;
        mTevColors[idx].g = g;
        mTevColors[idx].b = b;
        mTevColors[idx].a = a;
    }
    void SetTevColorAlpha(ETevColor idx, u8 alpha) {
        mTevColors[idx].a = alpha;
    }
};

//! @}

#endif
