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

/******************************************************************************
 *
 * AnimationInfo
 *
 ******************************************************************************/
struct AnimationInfo {
    u32 kind;                  // at 0x0
    u8 num;                    // at 0x4
    u8 PADDING_0x5[0x8 - 0x5]; // at 0x5

    static const u32 SIGNATURE_ANMPANESRT = 'RLPA';
    static const u32 SIGNATURE_ANMPANEVIS = 'RLVI';
    static const u32 SIGNATURE_ANMVTXCLR = 'RLVC';

    static const u32 SIGNATURE_ANMMATCLR = 'RLMC';
    static const u32 SIGNATURE_ANMTEXSRT = 'RLTS';
    static const u32 SIGNATURE_ANMTEXPAT = 'RLTP';
    static const u32 SIGNATURE_ANMINDTEXSRT = 'RLIM';
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

    u16 GetFrameSize() const;

    bool IsLoopData() const;

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

    virtual void Bind(Pane* pPane, bool recursive); // at 0x10
    virtual void Bind(Material* pMaterial);         // at 0x14

    virtual void Animate(u32 idx, Pane* pPane);         // at 0x18
    virtual void Animate(u32 idx, Material* pMaterial); // at 0x1C

protected:
    void** mpFileResAry;         // at 0x14
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

/******************************************************************************
 *
 * AnimTargetPane
 *
 ******************************************************************************/
enum AnimTargetPane {
    ANIMTARGET_PANE_TRANSX,
    ANIMTARGET_PANE_TRANSY,
    ANIMTARGET_PANE_TRANSZ,

    ANIMTARGET_PANE_ROTX,
    ANIMTARGET_PANE_ROTY,
    ANIMTARGET_PANE_ROTZ,

    ANIMTARGET_PANE_SCALEX,
    ANIMTARGET_PANE_SCALEY,

    ANIMTARGET_PANE_SIZEX,
    ANIMTARGET_PANE_SIZEY,

    ANIMTARGET_PANE_MAX,

    ANIMTARGET_PANE_COLOR_ALPHA = 16,
    ANIMTARGET_PANE_COLOR_MAX,
};

/******************************************************************************
 *
 * AnimTargetVtxColor
 *
 ******************************************************************************/
enum AnimTargetVtxColor {
    ANIMTARGET_VERTEXCOLOR_LT_RED,
    ANIMTARGET_VERTEXCOLOR_LT_GREEN,
    ANIMTARGET_VERTEXCOLOR_LT_BLUE,
    ANIMTARGET_VERTEXCOLOR_LT_ALPHA,

    ANIMTARGET_VERTEXCOLOR_RT_RED,
    ANIMTARGET_VERTEXCOLOR_RT_GREEN,
    ANIMTARGET_VERTEXCOLOR_RT_BLUE,
    ANIMTARGET_VERTEXCOLOR_RT_ALPHA,

    ANIMTARGET_VERTEXCOLOR_LB_RED,
    ANIMTARGET_VERTEXCOLOR_LB_GREEN,
    ANIMTARGET_VERTEXCOLOR_LB_BLUE,
    ANIMTARGET_VERTEXCOLOR_LB_ALPHA,

    ANIMTARGET_VERTEXCOLOR_RB_RED,
    ANIMTARGET_VERTEXCOLOR_RB_GREEN,
    ANIMTARGET_VERTEXCOLOR_RB_BLUE,
    ANIMTARGET_VERTEXCOLOR_RB_ALPHA,

    ANIMTARGET_VERTEXCOLOR_MAX
};

/******************************************************************************
 *
 * AnimTargetMatColor
 *
 ******************************************************************************/
enum AnimTargetMatColor {
    ANIMTARGET_MATCOLOR_MATR,
    ANIMTARGET_MATCOLOR_MATG,
    ANIMTARGET_MATCOLOR_MATB,
    ANIMTARGET_MATCOLOR_MATA,

    ANIMTARGET_MATCOLOR_TEV0R,
    ANIMTARGET_MATCOLOR_TEV0G,
    ANIMTARGET_MATCOLOR_TEV0B,
    ANIMTARGET_MATCOLOR_TEV0A,

    ANIMTARGET_MATCOLOR_TEV1R,
    ANIMTARGET_MATCOLOR_TEV1G,
    ANIMTARGET_MATCOLOR_TEV1B,
    ANIMTARGET_MATCOLOR_TEV1A,

    ANIMTARGET_MATCOLOR_TEV2R,
    ANIMTARGET_MATCOLOR_TEV2G,
    ANIMTARGET_MATCOLOR_TEV2B,
    ANIMTARGET_MATCOLOR_TEV2A,

    ANIMTARGET_MATCOLOR_TEVK0R,
    ANIMTARGET_MATCOLOR_TEVK0G,
    ANIMTARGET_MATCOLOR_TEVK0B,
    ANIMTARGET_MATCOLOR_TEVK0A,

    ANIMTARGET_MATCOLOR_TEVK1R,
    ANIMTARGET_MATCOLOR_TEVK1G,
    ANIMTARGET_MATCOLOR_TEVK1B,
    ANIMTARGET_MATCOLOR_TEVK1A,

    ANIMTARGET_MATCOLOR_TEVK2R,
    ANIMTARGET_MATCOLOR_TEVK2G,
    ANIMTARGET_MATCOLOR_TEVK2B,
    ANIMTARGET_MATCOLOR_TEVK2A,

    ANIMTARGET_MATCOLOR_TEVK3R,
    ANIMTARGET_MATCOLOR_TEVK3G,
    ANIMTARGET_MATCOLOR_TEVK3B,
    ANIMTARGET_MATCOLOR_TEVK3A,

    ANIMTARGET_MATCOLOR_MAX
};

/******************************************************************************
 *
 * AnimTargetTexSRT
 *
 ******************************************************************************/
enum AnimTargetTexSRT {
    ANIMTARGET_TEXSRT_TRANSX,
    ANIMTARGET_TEXSRT_TRANSY,

    ANIMTARGET_TEXSRT_ROT,

    ANIMTARGET_TEXSRT_SCALEX,
    ANIMTARGET_TEXSRT_SCALEY,

    ANIMTARGET_TEXSRT_MAX
};

/******************************************************************************
 *
 * AnimTargetTexPat
 *
 ******************************************************************************/
enum AnimTargetTexPat {
    ANIMTARGET_TEXPATTURN_IMAGE,

    ANIMTARGET_TEXPATTURN_MAX
};

} // namespace lyt
} // namespace nw4r

#endif
