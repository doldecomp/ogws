#ifndef NW4R_LYT_LAYOUT_H
#define NW4R_LYT_LAYOUT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_animation.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/ut.h>

#include <revolution/MEM.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class ArcResourceAccessor;
class DrawInfo;
class GroupContainer;
class Pane;

/******************************************************************************
 *
 * OriginType
 *
 ******************************************************************************/
enum OriginType {
    ORIGINTYPE_TOPLEFT,
    ORIGINTYPE_CENTER,

    ORIGINTYPE_MAX
};

namespace res {

/******************************************************************************
 *
 * LYT1 binary layout
 *
 ******************************************************************************/
struct Layout {
    static const u32 SIGNATURE = FOURCC('l', 'y', 't', '1');

    DataBlockHeader blockHeader; // at 0x0
    u8 originType;               // at 0x8
    u8 PADDING_0x9[0xC - 0x9];   // at 0x9
    Size layoutSize;             // at 0xC
};

} // namespace res

/******************************************************************************
 *
 * Layout
 *
 ******************************************************************************/
class Layout {
public:
    static const u32 SIGNATURE = FOURCC('R', 'L', 'Y', 'T');
    static const u32 SIGNATURE_ANIMATION = FOURCC('R', 'L', 'A', 'N');

public:
    Layout();
    virtual ~Layout(); // at 0x8

    virtual bool Build(const void* pLytBinary,
                       ResourceAccessor* pAccessor); // at 0xC

    virtual AnimTransform*
    CreateAnimTransform(const void* pAnmBinary,
                        ResourceAccessor* pAccessor); // at 0x10

    virtual void BindAnimation(AnimTransform* pAnimTrans);   // at 0x14
    virtual void UnbindAnimation(AnimTransform* pAnimTrans); // at 0x18
    virtual void UnbindAllAnimation();                       // at 0x1C
    virtual void SetAnimationEnable(AnimTransform* pAnimTrans,
                                    bool enable); // at 0x20

    virtual void CalculateMtx(const DrawInfo& rInfo); // at 0x24
    virtual void Draw(const DrawInfo& rInfo);         // at 0x28
    virtual void Animate(u32 option = 0);             // at 0x2C

    virtual void SetTagProcessor(ut::WideTagProcessor* pProcessor); // at 0x30

    ut::Rect GetLayoutRect() const;

    Pane* GetRootPane() const {
        return mpRootPane;
    }

    GroupContainer* GetGroupContainer() const {
        return mpGroupContainer;
    }

    static MEMAllocator* GetAllocator() {
        return mspAllocator;
    }
    static void SetAllocator(MEMAllocator* pAllocator) {
        mspAllocator = pAllocator;
    }

    static void* AllocMemory(u32 size) {
        return MEMAllocFromAllocator(mspAllocator, size);
    }
    static void FreeMemory(void* pBlock) {
        MEMFreeToAllocator(mspAllocator, pBlock);
    }

protected:
    static const u32 SIGNATURE_TEXTURELIST = FOURCC('t', 'x', 'l', '1');
    static const u32 SIGNATURE_FONTLIST = FOURCC('f', 'n', 'l', '1');
    static const u32 SIGNATURE_MATERIALLIST = FOURCC('m', 'a', 't', '1');

    static const u32 SIGNATURE_ANIMATIONINFO = FOURCC('p', 'a', 'i', '1');

    static const u32 SIGNATURE_PANESTART = FOURCC('p', 'a', 's', '1');
    static const u32 SIGNATURE_PANEEND = FOURCC('p', 'a', 'e', '1');

    static const u32 SIGNATURE_GROUPSTART = FOURCC('g', 'r', 's', '1');
    static const u32 SIGNATURE_GROUPEND = FOURCC('g', 'r', 'e', '1');

protected:
    static Pane* BuildPaneObj(s32 kind, const void* pBinary,
                              const ResBlockSet& rBlockSet) DECOMP_DONT_INLINE;

protected:
    AnimTransformList mAnimTransList; // at 0x4
    Pane* mpRootPane;                 // at 0x10
    GroupContainer* mpGroupContainer; // at 0x14
    Size mLayoutSize;                 // at 0x18
    u8 mOriginType;                   // at 0x20

    static MEMAllocator* mspAllocator;
};

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
namespace {

template <typename TObj> TObj* CreateObject() {
    void* pBuffer = Layout::AllocMemory(sizeof(TObj));

    if (pBuffer != NULL) {
        return new (pBuffer) TObj();
    }

    return NULL;
}

template <typename TObj, typename TParam> TObj* CreateObject(TParam param) {
    void* pBuffer = Layout::AllocMemory(sizeof(TObj));

    if (pBuffer != NULL) {
        return new (pBuffer) TObj(param);
    }

    return NULL;
}

template <typename TObj, typename TParam1, typename TParam2>
TObj* CreateObject(TParam1 param1, TParam2 param2) {

    void* pBuffer = Layout::AllocMemory(sizeof(TObj));

    if (pBuffer != NULL) {
        return new (pBuffer) TObj(param1, param2);
    }

    return NULL;
}

} // namespace
} // namespace lyt
} // namespace nw4r

#endif
