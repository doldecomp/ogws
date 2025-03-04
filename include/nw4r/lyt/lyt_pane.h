#ifndef NW4R_LYT_PANE_H
#define NW4R_LYT_PANE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_animation.h>
#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_resources.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class DrawInfo;
class Material;

/******************************************************************************
 *
 * AnimOption
 *
 ******************************************************************************/
enum AnimOption {
    ANIMOPTION_SKIP_INVISIBLE = (1 << 0),
};

namespace detail {

/******************************************************************************
 *
 * PaneBase
 *
 ******************************************************************************/
class PaneBase {
public:
    PaneBase();
    virtual ~PaneBase(); // at 0x8

public:
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x4
};

} // namespace detail

namespace res {

/******************************************************************************
 *
 * PAN1 binary layout
 *
 ******************************************************************************/
struct Pane {
    static const u32 SIGNATURE = 'pan1';

    DataBlockHeader blockHeader;               // at 0x0
    u8 flag;                                   // at 0x8
    u8 basePosition;                           // at 0x9
    u8 alpha;                                  // at 0xA
    u8 padding;                                // at 0xB
    char name[NW4R_LYT_RES_NAME_LEN];          // at 0xC
    char userData[NW4R_LYT_PANE_USERDATA_LEN]; // at 0x1C
    math::VEC3 translate;                      // at 0x24
    math::VEC3 rotate;                         // at 0x30
    math::VEC2 scale;                          // at 0x3C
    Size size;                                 // at 0x44
};

} // namespace res

/******************************************************************************
 *
 * Pane
 *
 ******************************************************************************/
class Pane : public detail::PaneBase {
public:
    NW4R_UT_RTTI_DECL(Pane);

private:
    enum FlagBit { BIT_VISIBLE, BIT_INFLUENCED_ALPHA, BIT_LOCATION_ADJUST };

    // Need the typedef before the class definition is complete
    typedef ut::LinkList<Pane, offsetof(PaneBase, node)> PaneList;

public:
    explicit Pane(const res::Pane* pRes);
    virtual ~Pane(); // at 0x8

    virtual void CalculateMtx(const DrawInfo& rInfo); // at 0x10
    void CalculateMtxChild(const DrawInfo& rInfo);

    virtual void Draw(const DrawInfo& rInfo);     // at 0x14
    virtual void DrawSelf(const DrawInfo& rInfo); // at 0x18

    virtual void Animate(u32 option);     // at 0x1C
    virtual void AnimateSelf(u32 option); // at 0x20

    virtual ut::Color GetVtxColor(u32 idx) const;       // at 0x24
    virtual void SetVtxColor(u32 idx, ut::Color color); // at 0x28
    virtual u8 GetColorElement(u32 idx) const;          // at 0x2C
    virtual void SetColorElement(u32 idx, u8 value);    // at 0x30
    virtual u8 GetVtxColorElement(u32 idx) const;       // at 0x34
    virtual void SetVtxColorElement(u32 idx, u8 value); // at 0x38

    virtual Pane* FindPaneByName(const char* pName, bool recursive); // at 0x3C
    virtual Material* FindMaterialByName(const char* pName,
                                         bool recursive); // at 0x40

    virtual void BindAnimation(AnimTransform* pAnimTrans,
                               bool recursive); // at 0x44
    virtual void UnbindAnimation(AnimTransform* pAnimTrans,
                                 bool recursive); // at 0x48

    virtual void UnbindAllAnimation(bool recursive);             // at 0x4C
    virtual void UnbindAnimationSelf(AnimTransform* pAnimTrans); // at 0x50

    virtual AnimationLink*
    FindAnimationLink(AnimTransform* pAnimTrans); // at 0x54

    virtual void SetAnimationEnable(AnimTransform* pAnimTrans, bool enable,
                                    bool recursive); // at 0x58

    virtual Material* GetMaterial() const;       // at 0x5C
    virtual void LoadMtx(const DrawInfo& rInfo); // at 0x60

    void AppendChild(Pane* pChild);
    void RemoveChild(Pane* pChild);

    ut::Rect GetPaneRect(const DrawInfo& rInfo) const;

    void AddAnimationLink(AnimationLink* pAnimLink);

    math::VEC2 GetVtxPos() const;

    Pane* GetParent() const {
        return mpParent;
    }

    PaneList& GetChildList() {
        return mChildList;
    }

    void SetSRTElement(u32 idx, f32 value) {
        reinterpret_cast<f32*>(&mTranslate)[idx] = value;
    }

    const math::VEC3& GetTranslate() const {
        return mTranslate;
    }
    void SetTranslate(const math::VEC2& rTransXY) {
        mTranslate.x = rTransXY.x;
        mTranslate.y = rTransXY.y;
    }
    void SetTranslate(const math::VEC3& rTrans) {
        mTranslate = rTrans;
    }

    const math::VEC3& GetRotate() const {
        return mRotate;
    }
    void SetRotate(const math::VEC3& rRotate) {
        mRotate = rRotate;
    }

    const math::VEC2& GetScale() const {
        return mScale;
    }
    void SetScale(const math::VEC2& rScale) {
        mScale = rScale;
    }

    const Size& GetSize() const {
        return mSize;
    }
    void SetSize(const Size& rSize) {
        mSize = rSize;
    }

    const math::MTX34& GetMtx() const {
        return mMtx;
    }
    void SetMtx(const math::MTX34& rMtx) {
        mMtx = rMtx;
    }

    const math::MTX34& GetGlobalMtx() const {
        return mGlbMtx;
    }
    void SetGlobalMtx(const math::MTX34& rGlbMtx) {
        mGlbMtx = rGlbMtx;
    }

    u8 GetAlpha() const {
        return mAlpha;
    }
    void SetAlpha(u8 alpha) {
        mAlpha = alpha;
    }

    u8 GetGlbAlpha() const {
        return mGlbAlpha;
    }
    void SetGlbAlpha(u8 alpha) {
        mGlbAlpha = alpha;
    }

    u8 GetBasePositionH() const {
        return detail::GetHorizontalPosition(mBasePosition);
    }
    void SetBasePositionH(u8 position) {
        detail::SetHorizontalPosition(&mBasePosition, position);
    }

    u8 GetBasePositionV() const {
        return detail::GetVerticalPosition(mBasePosition);
    }
    void SetBasePositionV(u8 position) {
        detail::SetVerticalPosition(&mBasePosition, position);
    }

    bool IsVisible() const {
        return detail::TestBit(mFlag, BIT_VISIBLE);
    }
    void SetVisible(bool visible) {
        detail::SetBit(&mFlag, BIT_VISIBLE, visible);
    }

    bool IsInfluencedAlpha() const {
        return detail::TestBit(mFlag, BIT_INFLUENCED_ALPHA);
    }
    void SetInfluencedAlpha(bool influenced) {
        detail::SetBit(&mFlag, BIT_INFLUENCED_ALPHA, influenced);
    }

    bool IsLocationAdjust() const {
        return detail::TestBit(mFlag, BIT_LOCATION_ADJUST);
    }
    void SetLocationAdjust(bool adjust) {
        detail::SetBit(&mFlag, BIT_LOCATION_ADJUST, adjust);
    }

    const char* GetName() const {
        return mName;
    }
    void SetName(const char* pName);

    const char* GetUserData() const {
        return mUserData;
    }
    void SetUserData(const char* pUserData);

    bool IsUserAllocated() const {
        return mbUserAllocated;
    }

protected:
    Pane* mpParent;              // at 0xC
    PaneList mChildList;         // at 0x10
    AnimationLinkList mAnimList; // at 0x1C
    Material* mpMaterial;        // at 0x28

    math::VEC3 mTranslate; // at 0x2C
    math::VEC3 mRotate;    // at 0x38
    math::VEC2 mScale;     // at 0x44
    Size mSize;            // at 0x4C

    math::MTX34 mMtx;    // at 0x54
    math::MTX34 mGlbMtx; // at 0x84

    u8 mAlpha;        // at 0xB4
    u8 mGlbAlpha;     // at 0xB5
    u8 mBasePosition; // at 0xB6
    u8 mFlag;         // at 0xB7

    char mName[NW4R_LYT_RES_NAME_LEN + 1];          // at 0xB8
    char mUserData[NW4R_LYT_PANE_USERDATA_LEN + 1]; // at 0xC9

    bool mbUserAllocated; // at 0xD2
    u8 PADDING_0xD3;      // at 0xD3

protected:
    void InsertChild(PaneList::Iterator next, Pane* pChild);

private:
    void Init();
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(Pane);

} // namespace lyt
} // namespace nw4r

#endif
