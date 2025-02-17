#ifndef NW4R_LYT_ANIMATION_H
#define NW4R_LYT_ANIMATION_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_resources.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class Pane;
class Material;
class ResourceAccessor;

namespace res {

/******************************************************************************
 *
 * AnimationBlock
 *
 ******************************************************************************/
struct AnimationBlock {
    DataBlockHeader blockHeader; // at 0x0
    u16 frameSize;               // at 0x8
    u8 loop;                     // at 0xA
    u8 PADDING_0xB;              // at 0xB
    u16 fileNum;                 // at 0xC
    u16 animContNum;             // at 0xE
    u32 animContOffsetsOffset;   // at 0x10
};

} // namespace res

/******************************************************************************
 *
 * AnimTransform
 *
 ******************************************************************************/
class AnimTransform {
public:
    AnimTransform();
    virtual ~AnimTransform(); // at 0x8

    virtual void SetResource(const res::AnimationBlock* pBlock,
                             ResourceAccessor* pAccessor) = 0; // at 0xC

    virtual void Bind(Pane* pPane, bool recursive) = 0; // at 0x10
    virtual void Bind(Material* pMaterial) = 0;         // at 0x14

    virtual void Animate(u32 idx, Pane* pPane) = 0;         // at 0x18
    virtual void Animate(u32 idx, Material* pMaterial) = 0; // at 0x1C

    u16 GetFrameSize() const {
        return mpRes->frameSize;
    }

    bool IsLoopData() const {
        return mpRes->loop != 0;
    }

    f32 GetFrame() const {
        return mFrame;
    }
    void SetFrame(f32 frame) {
        mFrame = frame;
    }

    f32 GetFrameMax() const {
        return static_cast<f32>(GetFrameSize());
    }

public:
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x4

protected:
    const res::AnimationBlock* mpRes; // at 0xC
    f32 mFrame;                       // at 0x10
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(AnimTransform);

/******************************************************************************
 *
 * AnimTransformBasic
 *
 ******************************************************************************/
class AnimTransformBasic : public AnimTransform {
public:
    AnimTransformBasic();
    virtual ~AnimTransformBasic(); // at 0x8

    virtual void SetResource(const res::AnimationBlock* pBlock,
                             ResourceAccessor* pAccessor); // at 0xC
    virtual void SetResource(const res::AnimationBlock* pBlock,
                             ResourceAccessor* pAccessor,
                             u16 animNum); // at 0x10

    virtual void Bind(Pane* pPane, bool recursive); // at 0x14
    virtual void Bind(Material* pMaterial);         // at 0x18

    virtual void Animate(u32 idx, Pane* pPane);         // at 0x1C
    virtual void Animate(u32 idx, Material* pMaterial); // at 0x20

protected:
    void* mpFileResAry;          // at 0x14
    AnimationLink* mAnimLinkAry; // at 0x18
    u16 mAnimLinkNum;            // at 0x1C
};

/******************************************************************************
 *
 * Functions
 *
 ******************************************************************************/
namespace detail {

AnimationLink* FindAnimationLink(AnimationLinkList* pAnimList,
                                 AnimTransform* pAnimTrans);

} // namespace detail
} // namespace lyt
} // namespace nw4r

#endif
