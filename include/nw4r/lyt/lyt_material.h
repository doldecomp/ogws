#ifndef NW4R_LYT_MATERIAL_H
#define NW4R_LYT_MATERIAL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_pane.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class AnimTransform;

namespace detail {

/******************************************************************************
 *
 * BitGXNums
 *
 ******************************************************************************/
struct BitGXNums {
    u32 texMap : 4;
    u32 texSRT : 4;
    u32 texCoordGen : 4;
    u32 indSRT : 2;
    u32 indStage : 3;
    u32 tevSwap : 1;
    u32 tevStage : 5;
    u32 chanCtrl : 1;
    u32 matCol : 1;
    u32 alpComp : 1;
    u32 blendMode : 1;
};

} // namespace detail

namespace res {

/******************************************************************************
 *
 * MAT1 binary layout
 *
 ******************************************************************************/
struct Material {};

} // namespace res

/******************************************************************************
 *
 * Material
 *
 ******************************************************************************/
class Material {
public:
    Material(const res::Material* pRes, const ResBlockSet& rBlockSet);
    virtual ~Material(); // at 0x8

    virtual bool SetupGX(bool modifyVtxCol, u8 alpha); // at 0xC

    virtual void BindAnimation(AnimTransform* pAnimTrans);   // at 0x10
    virtual void UnbindAnimation(AnimTransform* pAnimTrans); // at 0x14
    virtual void UnbindAllAnimation();                       // at 0x18

    virtual void Animate(); // at 0x1C

    virtual AnimationLink*
    FindAnimationLink(AnimTransform* pAnimTrans); // at 0x20

    virtual void SetAnimationEnable(AnimTransform* pAnimTrans,
                                    bool enable); // at 0x24

    const char* GetName() const {
        return mName;
    }

    bool IsUserAllocated() const {
        return mbUserAllocated;
    }

private:
    AnimationLinkList mAnimList; // at 0x4

    GXColorS10 mTevCols[3]; // at 0x10
    ut::Color mTevKCols[4]; // at 0x28

    detail::BitGXNums mGXMemCap; // at 0x38
    detail::BitGXNums mGXMemNum; // at 0x3C
    void* mpGXMem;               // at 0x40

    char mName[NW4R_LYT_MATERIAL_NAME_LEN + 1]; // at 0x44
    bool mbUserAllocated;                       // at 0x59

    u8 PADDING_0x5A[0x5C - 0x5A]; // at 0x5A
};

} // namespace lyt
} // namespace nw4r

#endif
