#ifndef NW4R_LYT_TYPES_H
#define NW4R_LYT_TYPES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

#define NW4R_LYT_LIBRARY_VERSION 8

#define NW4R_LYT_RES_NAME_LEN 16
#define NW4R_LYT_PANE_USERDATA_LEN 8
#define NW4R_LYT_MATERIAL_NAME_LEN 20

#define NW4R_LYT_MAX_TEXCOORD 8

namespace nw4r {
namespace lyt {

// Forward declarations
class AnimTransform;

namespace detail {

/******************************************************************************
 *
 * Pointer operations
 *
 ******************************************************************************/
template <typename T> T* ConvertOffsToPtr(void* pBase, u32 offset) {
    return reinterpret_cast<T*>(reinterpret_cast<u8*>(pBase) + offset);
}
template <typename T> const T* ConvertOffsToPtr(const void* pBase, u32 offset) {
    return reinterpret_cast<const T*>(reinterpret_cast<const u8*>(pBase) +
                                      offset);
}

/******************************************************************************
 *
 * Bit operations
 *
 ******************************************************************************/
template <typename T> inline void SetBit(T* pBits, int pos, bool value) {
    T mask = ~(1 << pos);
    *pBits &= mask;
    *pBits |= (value ? 1 : 0) << pos;
}
template <typename T> inline bool TestBit(T bits, int pos) {
    T mask = 1 << pos;
    return (bits & mask) != 0;
}
template <typename T> inline T GetBits(T bits, int pos, int len) {
    T mask = ~(static_cast<T>(-1) << len);
    return bits >> pos & mask;
}

} // namespace detail

/******************************************************************************
 *
 * Size
 *
 ******************************************************************************/
struct Size {
    f32 width;  // at 0x0
    f32 height; // at 0x4

    Size() : width(0.0f), height(0.0f) {}
    Size(const Size& rOther) : width(rOther.width), height(rOther.height) {}
    Size(f32 w, f32 h) : width(w), height(h) {}

    friend bool operator==(const Size& rLhs, const Size& rRhs) {
        return rLhs.width == rRhs.width && rLhs.height == rRhs.height;
    }
};

/******************************************************************************
 *
 * AnimationLink
 *
 ******************************************************************************/
class AnimationLink {
public:
    AnimationLink() : mbDisable(false) {
        Reset();
    }

    void Reset() {
        SetAnimTransform(NULL, 0);
    }

    AnimTransform* GetAnimTransform() const {
        return mAnimTrans;
    }
    void SetAnimTransform(AnimTransform* pAnimTrans, u16 idx) {
        mAnimTrans = pAnimTrans;
        mIdx = idx;
    }

    u16 GetIndex() const {
        return mIdx;
    }

    bool IsEnable() const {
        return !mbDisable;
    }
    void SetEnable(bool enable) {
        mbDisable = !enable;
    }

public:
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x0

private:
    AnimTransform* mAnimTrans; // at 0x8
    u16 mIdx;                  // at 0xC
    bool mbDisable;            // at 0xE
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(AnimationLink);

/******************************************************************************
 *
 * AlphaCompare
 *
 ******************************************************************************/
struct AlphaCompare {
    // TODO: Functions

    u8 comp; // at 0x0
    u8 op;   // at 0x1
    u8 ref0; // at 0x2
    u8 ref1; // at 0x3
};

/******************************************************************************
 *
 * BlendMode
 *
 ******************************************************************************/
struct BlendMode {
    // TODO: Functions

    u8 type;      // at 0x0
    u8 srcFactor; // at 0x1
    u8 dstFactor; // at 0x2
    u8 op;        // at 0x3
};

/******************************************************************************
 *
 * ChanCtrl
 *
 ******************************************************************************/
struct ChanCtrl {
    // TODO: Functions

    u8 matSrcCol; // at 0x0
    u8 matSrcAlp; // at 0x1
    u8 reserve1;  // at 0x2
    u8 reserve2;  // at 0x3
};

/******************************************************************************
 *
 * IndirectStage
 *
 ******************************************************************************/
struct IndirectStage {
    // TODO: Functions

    u8 texCoordGen; // at 0x0
    u8 texMap;      // at 0x1
    u8 scaleS;      // at 0x2
    u8 scaleT;      // at 0x3
};

/******************************************************************************
 *
 * TevStageInOp
 *
 ******************************************************************************/
struct TevStageInOp {
    u8 ab; // at 0x0
    u8 cd; // at 0x1
    u8 op; // at 0x2
    u8 cl; // at 0x3
};

/******************************************************************************
 *
 * TevStage
 *
 ******************************************************************************/
struct TevStage {
    // TODO: Functions

    u8 texCoordGen;     // at 0x0
    u8 colChan;         // at 0x1
    u8 texMap;          // at 0x2
    u8 swapSel;         // at 0x3
    TevStageInOp colIn; // at 0x4
    TevStageInOp alpIn; // at 0x8
    u8 indStage;        // at 0xC
    u8 indBiMt;         // at 0xD
    u8 indWrap;         // at 0xE
    u8 indFoAdUtAl;     // at 0xF
};

/******************************************************************************
 *
 * TevSwapMode
 *
 ******************************************************************************/
struct TevSwapMode {
    // TODO: Functions

    u8 swap; // at 0x0
};

/******************************************************************************
 *
 * TexCoordGen
 *
 ******************************************************************************/
struct TexCoordGen {
    TexCoordGen() : reserve(0) {
        Set(GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    }

    void Set(GXTexGenType type, GXTexGenSrc src, u32 mtxID) {
        texGenType = type;
        texGenSrc = src;
        texMtx = mtxID;
    }

    u8 texGenType; // at 0x0
    u8 texGenSrc;  // at 0x1
    u8 texMtx;     // at 0x2
    u8 reserve;    // at 0x3
};

/******************************************************************************
 *
 * TexSRT
 *
 ******************************************************************************/
struct TexSRT {
    math::VEC2 translate; // at 0x0
    f32 rotate;           // at 0x8
    math::VEC2 scale;     // at 0xC
};

} // namespace lyt
} // namespace nw4r

#endif
