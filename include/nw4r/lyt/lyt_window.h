#ifndef NW4R_LYT_WINDOW_H
#define NW4R_LYT_WINDOW_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_pane.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class Material;
struct ResBlockSet;

/******************************************************************************
 *
 * InflationLRTB
 *
 ******************************************************************************/
struct InflationLRTB {
    f32 l; // at 0x0
    f32 r; // at 0x4
    f32 t; // at 0x8
    f32 b; // at 0xC
};

namespace res {

/******************************************************************************
 *
 * WindowContent
 *
 ******************************************************************************/
struct WindowContent {
    u32 vtxCols[VERTEXCOLOR_MAX]; // at 0x0
    u16 materialIdx;              // at 0x10
    u8 texCoordNum;               // at 0x12
    u8 PADDING_0x13[0x14 - 0x13]; // at 0x13
};

/******************************************************************************
 *
 * WindowFrame
 *
 ******************************************************************************/
struct WindowFrame {
    u16 materialIdx; // at 0x0
    u8 textureFlip;  // at 0x2
    u8 PADDING_0x3;  // at 0x3
};

/******************************************************************************
 *
 * WND1 binary layout
 *
 ******************************************************************************/
struct Window : public Pane {
    static const u32 SIGNATURE = 'wnd1';

    InflationLRTB inflation;    // at 0x4C
    u8 frameNum;                // at 0x5C
    u8 PADDING_0x5D;            // at 0x5D
    u8 PADDING_0x5E;            // at 0x5E
    u8 PADDING_0x5F;            // at 0x5F
    u32 contentOffset;          // at 0x60
    u32 frameOffsetTableOffset; // at 0x64
};

} // namespace res

/******************************************************************************
 *
 * WindowFrameEnum
 *
 ******************************************************************************/
enum WindowFrameEnum {
    WINDOWFRAME_LT,
    WINDOWFRAME_RT,
    WINDOWFRAME_LB,
    WINDOWFRAME_RB,

    WINDOWFRAME_L,
    WINDOWFRAME_R,
    WINDOWFRAME_T,
    WINDOWFRAME_B,

    WINDOWFRAME_MAX
};

/******************************************************************************
 *
 * WindowFrameSize
 *
 ******************************************************************************/
struct WindowFrameSize {
    f32 l; // at 0x0
    f32 r; // at 0x4
    f32 t; // at 0x8
    f32 b; // at 0xC
};

/******************************************************************************
 *
 * Window
 *
 ******************************************************************************/
class Window : public Pane {
public:
    NW4R_UT_RTTI_DECL(Window);

public:
    Window(const res::Window* pRes, const ResBlockSet& rBlockSet);
    virtual ~Window(); // at 0x8

    virtual void DrawSelf(const DrawInfo& rInfo); // at 0x18
    virtual void AnimateSelf(u32 option);         // at 0x20

    virtual ut::Color GetVtxColor(u32 idx) const;       // at 0x24
    virtual void SetVtxColor(u32 idx, ut::Color color); // at 0x28
    virtual u8 GetVtxColorElement(u32 idx) const;       // at 0x34
    virtual void SetVtxColorElement(u32 idx, u8 value); // at 0x38

    virtual Material* FindMaterialByName(const char* pName,
                                         bool recursive); // at 0x40

    virtual void UnbindAnimationSelf(AnimTransform* pAnimTrans); // at 0x50

    virtual AnimationLink*
    FindAnimationLink(AnimTransform* pAnimTrans); // at 0x54

    virtual void SetAnimationEnable(AnimTransform* pAnimTrans, bool enable,
                                    bool recursive); // at 0x58

    virtual Material* GetContentMaterial() const;      // at 0x64
    virtual Material* GetFrameMaterial(u32 idx) const; // at 0x68

protected:
    struct Frame {
        u8 textureFlip;      // at 0x0
        Material* pMaterial; // at 0x4

        Frame() : textureFlip(0), pMaterial(NULL) {}
    };

    struct Content {
        ut::Color vtxColors[VERTEXCOLOR_MAX]; // at 0x0
        detail::TexCoordAry texCoordAry;      // at 0x10
    };

protected:
    virtual void DrawContent(const math::VEC2& rBase,
                             const WindowFrameSize& rFrameSize,
                             u8 alpha); // at 0x6C

    virtual void DrawFrame(const math::VEC2& rBase, const Frame& rFrame,
                           const WindowFrameSize& rFrameSize,
                           u8 alpha); // at 0x70

    virtual void DrawFrame4(const math::VEC2& rBase, const Frame* pFrames,
                            const WindowFrameSize& rFrameSize,
                            u8 alpha); // at 0x74

    virtual void DrawFrame8(const math::VEC2& rBase, const Frame* pFrames,
                            const WindowFrameSize& rFrameSize,
                            u8 alpha); // at 0x78

    WindowFrameSize GetFrameSize(u8 frameNum, const Frame* pFrames);

protected:
    InflationLRTB mContentInflation; // at 0xD4
    Content mContent;                // at 0xE4
    Frame* mFrames;                  // at 0xFC
    u8 mFrameNum;                    // at 0x100
};

} // namespace lyt
} // namespace nw4r

#endif
