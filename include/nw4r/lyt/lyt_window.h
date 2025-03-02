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

    // TODO

protected:
    struct Content {
        ut::Color vtxColors[VERTEXCOLOR_MAX]; // at 0x0
        detail::TexCoordAry texCoordAry;      // at 0x10
    };

    struct Frame {
        u8 textureFlip;      // at 0x0
        Material* pMaterial; // at 0x4
    };

protected:
    InflationLRTB mContentInflation; // at 0xD8
    Content mContent;                // at 0xE8
    Frame* mFrames;                  // at 0x100
    u8 mFrameNum;                    // at 0x104
};

} // namespace lyt
} // namespace nw4r

#endif
