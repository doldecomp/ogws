#include <nw4r/lyt.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>

#include <cstring>

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
namespace {

using namespace nw4r;
using namespace nw4r::lyt;

void ReverseYAxis(math::MTX34* pMtx) {
    pMtx->m[0][1] = -pMtx->m[0][1];
    pMtx->m[1][1] = -pMtx->m[1][1];
    pMtx->m[2][1] = -pMtx->m[2][1];
}

} // namespace

namespace nw4r {
namespace lyt {

NW4R_UT_RTTI_DEF_BASE(Pane);

namespace detail {

/******************************************************************************
 *
 * PaneBase
 *
 ******************************************************************************/
PaneBase::PaneBase() {}

PaneBase::~PaneBase() {}

} // namespace detail

/******************************************************************************
 *
 * Pane
 *
 ******************************************************************************/
Pane::Pane(const res::Pane* pRes) {
    Init();

    mBasePosition = pRes->basePosition;

    SetName(pRes->name);
    SetUserData(pRes->userData);

    mTranslate = pRes->translate;
    mRotate = pRes->rotate;
    mScale = pRes->scale;
    mSize = pRes->size;

    mAlpha = pRes->alpha;
    mGlbAlpha = mAlpha;
    mFlag = pRes->flag;
}

void Pane::Init() {
    mpParent = NULL;
    mpMaterial = NULL;
    mbUserAllocated = false;
}

Pane::~Pane() {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mChildList, {
        mChildList.Erase(it);

        if (!it->IsUserAllocated()) {
            it->~Pane();
            Layout::FreeMemory(&*it);
        }
    })

    UnbindAnimationSelf(NULL);

    if (mpMaterial != NULL && !mpMaterial->IsUserAllocated()) {
        mpMaterial->~Material();
        Layout::FreeMemory(mpMaterial);
    }
}

void Pane::SetName(const char* pName) {
    std::strncpy(mName, pName, NW4R_LYT_RES_NAME_LEN);
    mName[NW4R_LYT_RES_NAME_LEN] = '\0';
}

void Pane::SetUserData(const char* pUserData) {
    std::strncpy(mUserData, pUserData, NW4R_LYT_PANE_USERDATA_LEN);
    mUserData[NW4R_LYT_PANE_USERDATA_LEN] = '\0';
}

void Pane::AppendChild(Pane* pChild) {
    InsertChild(mChildList.GetEndIter(), pChild);
}

void Pane::InsertChild(PaneList::Iterator next, Pane* pChild) {
    mChildList.Insert(next, pChild);
    pChild->mpParent = this;
}

void Pane::RemoveChild(Pane* pChild) {
    mChildList.Erase(pChild);
    pChild->mpParent = NULL;
}

ut::Rect Pane::GetPaneRect(const DrawInfo& rInfo) const {
    ut::Rect rect;
    math::VEC2 base = GetVtxPos();

    rect.left = base.x;
    rect.top = base.y;
    rect.right = base.x + mSize.width;
    rect.bottom = base.y + mSize.height;

    if (rInfo.IsYAxisUp()) {
        rect.top = -rect.top;
        rect.bottom = -rect.bottom;
    }

    return rect;
}

ut::Color Pane::GetVtxColor(u32 idx) const {
#pragma unused(idx)

    return ut::Color::WHITE;
}

void Pane::SetVtxColor(u32 idx, ut::Color color) {
#pragma unused(idx)
#pragma unused(color)
}

u8 Pane::GetColorElement(u32 idx) const {
    switch (idx) {
    case ANIMTARGET_PANE_COLOR_ALPHA: {
        return mAlpha;
    }

    default: {
        return GetVtxColorElement(idx);
    }
    }
}

void Pane::SetColorElement(u32 idx, u8 value) {
    switch (idx) {
    case ANIMTARGET_PANE_COLOR_ALPHA: {
        mAlpha = value;
        break;
    }

    default: {
        SetVtxColorElement(idx, value);
        break;
    }
    }
}

u8 Pane::GetVtxColorElement(u32 idx) const {
#pragma unused(idx)

    return 0xFF;
}

void Pane::SetVtxColorElement(u32 idx, u8 value) {
#pragma unused(idx)
#pragma unused(value)
}

Pane* Pane::FindPaneByName(const char* pName, bool recursive) {
    if (detail::EqualsResName(mName, pName)) {
        return this;
    }

    if (recursive) {
        NW4R_UT_LINKLIST_FOREACH (it, mChildList, {
            Pane* pResult = it->FindPaneByName(pName, true);

            if (pResult != NULL) {
                return pResult;
            }
        })
    }

    return NULL;
}

Material* Pane::FindMaterialByName(const char* pName, bool recursive) {
    if (mpMaterial != NULL &&
        detail::EqualsMaterialName(mpMaterial->GetName(), pName)) {

        return mpMaterial;
    }

    if (recursive) {
        NW4R_UT_LINKLIST_FOREACH (it, mChildList, {
            Material* pResult = it->FindMaterialByName(pName, true);

            if (pResult != NULL) {
                return pResult;
            }
        })
    }

    return NULL;
}

void Pane::CalculateMtx(const DrawInfo& rInfo) {
    if (!IsVisible() && !rInfo.IsInvisiblePaneCalculateMtx()) {
        return;
    }

    math::MTX34 mtx1, mtx2;
    math::MTX34 rotateMtx;

    math::VEC2 scale = mScale;
    if (rInfo.IsLocationAdjust() && IsLocationAdjust()) {
        scale.x *= rInfo.GetLocationAdjustScale().x;
        scale.y *= rInfo.GetLocationAdjustScale().y;
    }

    PSMTXScale(mtx2, scale.x, scale.y, 1.0f);

    PSMTXRotRad(rotateMtx, 'x', NW4R_MATH_DEG_TO_RAD(mRotate.x));
    PSMTXConcat(rotateMtx, mtx2, mtx1);

    PSMTXRotRad(rotateMtx, 'y', NW4R_MATH_DEG_TO_RAD(mRotate.y));
    PSMTXConcat(rotateMtx, mtx1, mtx2);

    PSMTXRotRad(rotateMtx, 'z', NW4R_MATH_DEG_TO_RAD(mRotate.z));
    PSMTXConcat(rotateMtx, mtx2, mtx1);

    PSMTXTransApply(mtx1, mMtx, mTranslate.x, mTranslate.y, mTranslate.z);

    if (mpParent != NULL) {
        math::MTX34Mult(&mGlbMtx, &mpParent->mGlbMtx, &mMtx);
    } else if (rInfo.IsMultipleViewMtxOnDraw()) {
        mGlbMtx = mMtx;
    } else {
        math::MTX34Mult(&mGlbMtx, &rInfo.GetViewMtx(), &mMtx);
    }

    if (rInfo.IsInfluencedAlpha() && mpParent != NULL) {
        mGlbAlpha = static_cast<u8>(mAlpha * rInfo.GetGlobalAlpha());
    } else {
        mGlbAlpha = mAlpha;
    }

    f32 glbAlpha = rInfo.GetGlobalAlpha();
    bool influenced = rInfo.IsInfluencedAlpha();
    bool modifyInfo = IsInfluencedAlpha() && mAlpha != 255;

    if (modifyInfo) {
        DrawInfo& rMtInfo = const_cast<DrawInfo&>(rInfo);
        rMtInfo.SetGlobalAlpha(glbAlpha * mAlpha * (1.0f / 255.0f));
        rMtInfo.SetInfluencedAlpha(true);
    }

    CalculateMtxChild(rInfo);

    if (modifyInfo) {
        DrawInfo& rMtInfo = const_cast<DrawInfo&>(rInfo);
        rMtInfo.SetGlobalAlpha(glbAlpha);
        rMtInfo.SetInfluencedAlpha(influenced);
    }
}

void Pane::CalculateMtxChild(const DrawInfo& rInfo) {
    NW4R_UT_LINKLIST_FOREACH (it, mChildList, { it->CalculateMtx(rInfo); })
}

void Pane::Draw(const DrawInfo& rInfo) {
    if (!IsVisible()) {
        return;
    }

    DrawSelf(rInfo);
    NW4R_UT_LINKLIST_FOREACH (it, mChildList, { it->Draw(rInfo); })
}

void Pane::DrawSelf(const DrawInfo& rInfo) {
#pragma unused(rInfo)
    // Debug draw stripped out
}

void Pane::Animate(u32 option) {
    AnimateSelf(option);

    if (IsVisible() || !(option & ANIMOPTION_SKIP_INVISIBLE)) {
        NW4R_UT_LINKLIST_FOREACH (it, mChildList, { it->Animate(option); })
    }
}

void Pane::AnimateSelf(u32 option) {
    NW4R_UT_LINKLIST_FOREACH (it, mAnimList, {
        if (!it->IsEnable()) {
            continue;
        }

        AnimTransform* pAnimTrans = it->GetAnimTransform();
        pAnimTrans->Animate(it->GetIndex(), this);
    })

    if (IsVisible() || !(option & ANIMOPTION_SKIP_INVISIBLE)) {
        if (mpMaterial != NULL) {
            mpMaterial->Animate();
        }
    }
}

void Pane::BindAnimation(AnimTransform* pAnimTrans, bool recursive) {
    pAnimTrans->Bind(this, recursive);
}

void Pane::UnbindAnimation(AnimTransform* pAnimTrans, bool recursive) {
    UnbindAnimationSelf(pAnimTrans);

    if (recursive) {
        NW4R_UT_LINKLIST_FOREACH (it, mChildList, 
            { it->UnbindAnimation(pAnimTrans, recursive); })
    }
}

void Pane::UnbindAllAnimation(bool recursive) {
    UnbindAnimation(NULL, recursive);
}

void Pane::UnbindAnimationSelf(AnimTransform* pAnimTrans) {
    if (mpMaterial != NULL) {
        mpMaterial->UnbindAnimation(pAnimTrans);
    }

    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mAnimList, {
        if (pAnimTrans == NULL || it->GetAnimTransform() == pAnimTrans) {
            mAnimList.Erase(it);
            it->Reset();
        }
    })
}

void Pane::AddAnimationLink(AnimationLink* pAnimLink) {
    mAnimList.PushBack(pAnimLink);
}

AnimationLink* Pane::FindAnimationLink(AnimTransform* pAnimTrans) {
    AnimationLink* pAnimLink =
        detail::FindAnimationLink(&mAnimList, pAnimTrans);

    if (pAnimLink != NULL) {
        return pAnimLink;
    }

    if (mpMaterial != NULL) {
        pAnimLink = mpMaterial->FindAnimationLink(pAnimTrans);

        if (pAnimLink != NULL) {
            return pAnimLink;
        }
    }

    return NULL;
}

void Pane::SetAnimationEnable(AnimTransform* pAnimTrans, bool enable,
                              bool recursive) {

    AnimationLink* pAnimLink =
        detail::FindAnimationLink(&mAnimList, pAnimTrans);

    if (pAnimLink != NULL) {
        pAnimLink->SetEnable(enable);
    }

    if (mpMaterial != NULL) {
        mpMaterial->SetAnimationEnable(pAnimTrans, enable);
    }

    if (recursive) {
        NW4R_UT_LINKLIST_FOREACH (it, mChildList, 
            { it->SetAnimationEnable(pAnimTrans, enable, recursive); })
    }
}

void Pane::LoadMtx(const DrawInfo& rInfo) {
    math::MTX34 mtx;
    math::MTX34* pMtx = NULL;

    if (rInfo.IsMultipleViewMtxOnDraw()) {
        math::MTX34Mult(&mtx, &rInfo.GetViewMtx(), &mGlbMtx);

        if (rInfo.IsYAxisUp()) {
            ReverseYAxis(&mtx);
        }

        pMtx = &mtx;
    } else if (rInfo.IsYAxisUp()) {
        math::MTX34Copy(&mtx, &mGlbMtx);
        pMtx = &mtx;

        ReverseYAxis(&mtx);
    } else {
        pMtx = &mGlbMtx;
    }

    GXLoadPosMtxImm(*pMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

math::VEC2 Pane::GetVtxPos() const {
    math::VEC2 base(0.0f, 0.0f);

    switch (mBasePosition % HORIZONTALPOSITION_MAX) {
    default:
    case HORIZONTALPOSITION_LEFT: {
        base.x = 0.0f;
        break;
    }

    case HORIZONTALPOSITION_CENTER: {
        base.x = -mSize.width / 2;
        break;
    }

    case HORIZONTALPOSITION_RIGHT: {
        base.x = -mSize.width;
        break;
    }
    }

    switch (mBasePosition / HORIZONTALPOSITION_MAX) {
    default:
    case VERTICALPOSITION_TOP: {
        base.y = 0.0f;
        break;
    }

    case HORIZONTALPOSITION_CENTER: {
        base.y = -mSize.height / 2;
        break;
    }

    case HORIZONTALPOSITION_RIGHT: {
        base.y = -mSize.height;
        break;
    }
    }

    return base;
}

Material* Pane::GetMaterial() const {
    return mpMaterial;
}

} // namespace lyt
} // namespace nw4r
