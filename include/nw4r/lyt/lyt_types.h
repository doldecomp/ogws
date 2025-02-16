#ifndef NW4R_LYT_TYPES_H
#define NW4R_LYT_TYPES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

#define NW4R_LYT_PANE_NAME_LEN 16
#define NW4R_LYT_PANE_USERDATA_LEN 8

#define NW4R_LYT_MATERIAL_NAME_LEN 20

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
    return static_cast<T*>(reinterpret_cast<u8*>(pBase) + offset);
}
template <typename T> const T* ConvertOffsToPtr(const void* pBase, u32 offset) {
    return static_cast<const T*>(reinterpret_cast<const u8*>(pBase) + offset);
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
    AnimationLink() {
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

// TODO: AnimationGroupRef, AnimationShareInfo

// TODO: TexCoordGen, BlendMode, AlphaCompare, TevSwapMode, ChanCtrl, TevStage,
//       TevStageInOp, IndirectStage

} // namespace lyt
} // namespace nw4r

#endif
