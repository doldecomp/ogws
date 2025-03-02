#include <nw4r/lyt.h>
#include <nw4r/ut.h>

#include <cstring>

/******************************************************************************
 *
 * Private structures
 *
 ******************************************************************************/
namespace nw4r {
namespace lyt {
namespace res {

/******************************************************************************
 * AnimationContent
 ******************************************************************************/
struct AnimationContent {
    static const int NAME_LEN =
        MAX(NW4R_LYT_RES_NAME_LEN, NW4R_LYT_MATERIAL_NAME_LEN);

    enum AnimType { ANIMTYPE_PANE, ANIMTYPE_MATERIAL, ANIMTYPE_MAX };

    char name[NAME_LEN];          // at 0x0
    u8 num;                       // at 0x14
    u8 type;                      // at 0x15
    u8 PADDING_0x16[0x18 - 0x16]; // at 0x16
};
/******************************************************************************
 * AnimationTarget
 ******************************************************************************/
struct AnimationTarget {
    enum AnimCurve {
        ANIMCURVE_NONE,
        ANIMCURVE_STEP,
        ANIMCURVE_HERMITE,

        ANIMCURVE_MAX
    };

    u8 id;                     // at 0x0
    u8 target;                 // at 0x1
    u8 curveType;              // at 0x2
    u8 PADDING_0x3;            // at 0x3
    u16 keyNum;                // at 0x4
    u8 PADDING_0x6[0x8 - 0x6]; // at 0x6
    u32 keysOffset;            // at 0x8
};

/******************************************************************************
 * StepKey
 ******************************************************************************/
struct StepKey {
    f32 frame;       // at 0x0
    u16 value;       // at 0x4
    u16 PADDING_0x6; // at 0x6
};
/******************************************************************************
 * HermiteKey
 ******************************************************************************/
struct HermiteKey {
    f32 frame; // at 0x0
    f32 value; // at 0x4
    f32 slope; // at 0x8
};

} // namespace res
} // namespace lyt
} // namespace nw4r

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
namespace {

using namespace nw4r;
using namespace nw4r::lyt;

inline bool RIsSame(f32 a, f32 b, f32 tolerance) {
    f32 c = a - b;
    return -tolerance < c && c < tolerance;
}

u16 GetStepCurveValue(f32 frame, const res::StepKey* pKeys, u32 numKey) {
    if (numKey == 1 || frame <= pKeys[0].frame) {
        return pKeys[0].value;
    }

    if (frame >= pKeys[numKey - 1].frame) {
        return pKeys[numKey - 1].value;
    }

    int left = 0;
    int right = numKey - 1;

    while (left != right - 1 && left != right) {
        int center = (left + right) / 2;
        const res::StepKey& rCenterKey = pKeys[center];

        if (frame < rCenterKey.frame) {
            right = center;
        } else {
            left = center;
        }
    }

    if (RIsSame(frame, pKeys[right].frame, 0.001f)) {
        return pKeys[right].value;
    }

    return pKeys[left].value;
}

f32 GetHermiteCurveValue(f32 frame, const res::HermiteKey* pKeys, u32 numKey) {

    if (numKey == 1 || frame <= pKeys[0].frame) {
        return pKeys[0].value;
    }

    if (frame >= pKeys[numKey - 1].frame) {
        return pKeys[numKey - 1].value;
    }

    int left = 0;
    int right = numKey - 1;

    while (left != right - 1 && left != right) {
        int center = (left + right) / 2;

        if (frame <= pKeys[center].frame) {
            right = center;
        } else {
            left = center;
        }
    }

    const res::HermiteKey& rLeftKey = pKeys[left];
    const res::HermiteKey& rRightKey = pKeys[right];

    if (RIsSame(frame, rRightKey.frame, 0.001f)) {
        if (right < numKey - 1 && rRightKey.frame == pKeys[right + 1].frame) {
            return pKeys[right + 1].value;
        }

        return rRightKey.value;
    }

    f32 t1 = frame - rLeftKey.frame;
    f32 t2 = 1.0f / (rRightKey.frame - rLeftKey.frame);

    f32 v0 = rLeftKey.value;
    f32 v1 = rRightKey.value;

    f32 s0 = rLeftKey.slope;
    f32 s1 = rRightKey.slope;

    f32 t1_t1_t2 = t1 * t1 * t2;
    f32 t1_t1_t2_t2 = t1_t1_t2 * t2;
    f32 t1_t1_t1_t2_t2 = t1 * t1_t1_t2_t2;
    f32 t1_t1_t1_t2_t2_t2 = t1_t1_t1_t2_t2 * t2;

    return v0 * (2.0f * t1_t1_t1_t2_t2_t2 - 3.0f * t1_t1_t2_t2 + 1.0f) +
           v1 * (-2.0f * t1_t1_t1_t2_t2_t2 + 3.0f * t1_t1_t2_t2) +
           s0 * (t1_t1_t1_t2_t2 - 2.0f * t1_t1_t2 + t1) +
           s1 * (t1_t1_t1_t2_t2 - t1_t1_t2);
}

// @typo
void AnimatePainSRT(Pane* pPane, const res::AnimationInfo* pAnimInfo,
                    const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);

        const res::HermiteKey* pKeys =
            detail::ConvertOffsToPtr<res::HermiteKey>(pTarget,
                                                      pTarget->keysOffset);

        pPane->SetSRTElement(
            pTarget->target,
            GetHermiteCurveValue(frame, pKeys, pTarget->keyNum));
    }
}

void AnimateVisibility(Pane* pPane, const res::AnimationInfo* pAnimInfo,
                       const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);

        const res::StepKey* pKeys = detail::ConvertOffsToPtr<res::StepKey>(
            pTarget, pTarget->keysOffset);

        pPane->SetVisible(GetStepCurveValue(frame, pKeys, pTarget->keyNum) !=
                          0);
    }
}

void AnimateVertexColor(Pane* pPane, const res::AnimationInfo* pAnimInfo,
                        const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);
        const res::HermiteKey* pKeys =
            detail::ConvertOffsToPtr<res::HermiteKey>(pTarget,
                                                      pTarget->keysOffset);

        f32 fValue = GetHermiteCurveValue(frame, pKeys, pTarget->keyNum);
        fValue += 0.5f;

        u8 bValue;
        OSf32tou8(&fValue, &bValue);

        pPane->SetColorElement(pTarget->target, bValue);
    }
}

void AnimateMaterialColor(Material* pMaterial,
                          const res::AnimationInfo* pAnimInfo,
                          const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);
        const res::HermiteKey* pKeys =
            detail::ConvertOffsToPtr<res::HermiteKey>(pTarget,
                                                      pTarget->keysOffset);

        f32 fValue = GetHermiteCurveValue(frame, pKeys, pTarget->keyNum);
        fValue += 0.5f;

        s16 sValue;
        OSf32tos16(&fValue, &sValue);

        // [-1024, 1023]
        sValue = ut::Min<s16>(ut::Max<s16>(sValue, -1024), 1023);

        pMaterial->SetColorElement(pTarget->target, sValue);
    }
}

void AnimateTextureSRT(Material* pMaterial, const res::AnimationInfo* pAnimInfo,
                       const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);

        if (pTarget->id < pMaterial->GetTexSRTCap()) {
            const res::HermiteKey* pKeys =
                detail::ConvertOffsToPtr<res::HermiteKey>(pTarget,
                                                          pTarget->keysOffset);

            pMaterial->SetTexSRTElement(
                pTarget->id, pTarget->target,
                GetHermiteCurveValue(frame, pKeys, pTarget->keyNum));
        }
    }
}

void AnimateTexturePattern(Material* pMaterial,
                           const res::AnimationInfo* pAnimInfo,
                           const u32* pTargetOffsetTbl, f32 frame,
                           void** ppTexPalettes) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);

        if (pTarget->id < pMaterial->GetTextureNum() &&
            pTarget->target == ANIMTARGET_TEXPATTURN_IMAGE) {

            const res::StepKey* pKeys = detail::ConvertOffsToPtr<res::StepKey>(
                pTarget, pTarget->keysOffset);

            u16 idx = GetStepCurveValue(frame, pKeys, pTarget->keyNum);

            TexMap texMap(static_cast<TPLPalette*>(ppTexPalettes[idx]), 0);
            pMaterial->SetTextureNoWrap(pTarget->id, texMap);
        }
    }
}

void AnimateIndTexSRT(Material* pMaterial, const res::AnimationInfo* pAnimInfo,
                      const u32* pTargetOffsetTbl, f32 frame) {

    for (int i = 0; i < pAnimInfo->num; i++) {
        const res::AnimationTarget* pTarget =
            detail::ConvertOffsToPtr<res::AnimationTarget>(pAnimInfo,
                                                           pTargetOffsetTbl[i]);

        if (pTarget->id < pMaterial->GetIndTexSRTCap()) {
            const res::HermiteKey* pKeys =
                detail::ConvertOffsToPtr<res::HermiteKey>(pTarget,
                                                          pTarget->keysOffset);

            pMaterial->SetIndTexSRTElement(
                pTarget->id, pTarget->target,
                GetHermiteCurveValue(frame, pKeys, pTarget->keyNum));
        }
    }
}

} // namespace

namespace nw4r {
namespace lyt {

/******************************************************************************
 *
 * AnimTransform
 *
 ******************************************************************************/
AnimTransform::AnimTransform() : mpRes(NULL), mFrame(0.0f) {}

AnimTransform::~AnimTransform() {}

u16 AnimTransform::GetFrameSize() const {
    return mpRes->frameSize;
}

bool AnimTransform::IsLoopData() const {
    return mpRes->loop != 0;
}

/******************************************************************************
 *
 * AnimTransformBasic
 *
 ******************************************************************************/
AnimTransformBasic::AnimTransformBasic()
    : mpFileResAry(NULL), mAnimLinkAry(NULL), mAnimLinkNum(0) {}

AnimTransformBasic::~AnimTransformBasic() {
    if (mAnimLinkAry != NULL) {
        Layout::FreeMemory(mAnimLinkAry);
    }

    if (mpFileResAry != NULL) {
        Layout::FreeMemory(mpFileResAry);
    }
}

void AnimTransformBasic::SetResource(const res::AnimationBlock* pBlock,
                                     ResourceAccessor* pAccessor) {

    mpRes = pBlock;
    mpFileResAry = NULL;

    if (mpRes->fileNum > 0) {
        mpFileResAry = static_cast<void**>(
            Layout::AllocMemory(mpRes->fileNum * sizeof(void*)));

        if (mpFileResAry != NULL) {
            const u32* pStrTable = detail::ConvertOffsToPtr<u32>(
                mpRes, sizeof(res::AnimationBlock));

            for (int i = 0; i < mpRes->fileNum; i++) {
                const char* pName = detail::GetStrTableStr(pStrTable, i);

                mpFileResAry[i] = pAccessor->GetResource(
                    ArcResourceAccessor::RES_TYPE_TEXTURE, pName, NULL);
            }
        }
    }

    mAnimLinkAry = static_cast<AnimationLink*>(
        Layout::AllocMemory(pBlock->animContNum * sizeof(AnimationLink)));

    if (mAnimLinkAry != NULL) {
        mAnimLinkNum = pBlock->animContNum;

        std::memset(mAnimLinkAry, 0,
                    pBlock->animContNum * sizeof(AnimationLink));

        for (u16 i = 0; i < pBlock->animContNum; i++) {
            new (&mAnimLinkAry[i]) AnimationLink();
        }
    }
}

void AnimTransformBasic::Bind(Pane* pPane, bool recursive) {
    const u32* const pContentOffsetTbl =
        detail::ConvertOffsToPtr<u32>(mpRes, mpRes->animContOffsetsOffset);

    for (u16 i = 0; i < mpRes->animContNum; i++) {
        const res::AnimationContent& rContent =
            *detail::ConvertOffsToPtr<res::AnimationContent>(
                mpRes, pContentOffsetTbl[i]);

        if (rContent.type == res::AnimationContent::ANIMTYPE_PANE) {
            Pane* pResult = pPane->FindPaneByName(rContent.name, recursive);

            if (pResult != NULL) {
                mAnimLinkAry[i].SetAnimTransform(this, i);
                pResult->AddAnimationLink(&mAnimLinkAry[i]);
            }
        } else /* res::AnimationContent::ANIMTYPE_MATERIAL */ {
            Material* pResult =
                pPane->FindMaterialByName(rContent.name, recursive);

            if (pResult != NULL) {
                mAnimLinkAry[i].SetAnimTransform(this, i);
                pResult->AddAnimationLink(&mAnimLinkAry[i]);
            }
        }
    }
}

void AnimTransformBasic::Bind(Material* pMaterial) {
    const u32* const pContentOffsetTbl =
        detail::ConvertOffsToPtr<u32>(mpRes, mpRes->animContOffsetsOffset);

    for (u16 i = 0; i < mpRes->animContNum; i++) {
        const res::AnimationContent& rContent =
            *detail::ConvertOffsToPtr<res::AnimationContent>(
                mpRes, pContentOffsetTbl[i]);

        if (rContent.type == res::AnimationContent::ANIMTYPE_MATERIAL &&
            detail::EqualsMaterialName(pMaterial->GetName(), rContent.name)) {

            mAnimLinkAry[i].SetAnimTransform(this, i);
            pMaterial->AddAnimationLink(&mAnimLinkAry[i]);
        }
    }
}

void AnimTransformBasic::Animate(u32 idx, Pane* pPane) {
    u32 contentOffset =
        detail::ConvertOffsToPtr<u32>(mpRes, mpRes->animContOffsetsOffset)[idx];

    const res::AnimationContent* pContent =
        detail::ConvertOffsToPtr<res::AnimationContent>(mpRes, contentOffset);

    const u32* pInfoOffsetTbl =
        detail::ConvertOffsToPtr<u32>(pContent, sizeof(res::AnimationContent));

    for (int i = 0; i < pContent->num; i++) {
        const res::AnimationInfo* pAnimInfo =
            detail::ConvertOffsToPtr<res::AnimationInfo>(pContent,
                                                         pInfoOffsetTbl[i]);

        const u32* pTargetOffsetTbl = detail::ConvertOffsToPtr<u32>(
            pAnimInfo, sizeof(res::AnimationInfo));

        switch (pAnimInfo->kind) {
        case res::AnimationInfo::SIGNATURE_ANMPANESRT: {
            AnimatePainSRT(pPane, pAnimInfo, pTargetOffsetTbl, mFrame);
            break;
        }

        case res::AnimationInfo::SIGNATURE_ANMPANEVIS: {
            AnimateVisibility(pPane, pAnimInfo, pTargetOffsetTbl, mFrame);
            break;
        }

        case res::AnimationInfo::SIGNATURE_ANMVTXCLR: {
            AnimateVertexColor(pPane, pAnimInfo, pTargetOffsetTbl, mFrame);
            break;
        }
        }
    }
}

void AnimTransformBasic::Animate(u32 idx, Material* pMaterial) {
    u32 contentOffset =
        detail::ConvertOffsToPtr<u32>(mpRes, mpRes->animContOffsetsOffset)[idx];

    const res::AnimationContent* pContent =
        detail::ConvertOffsToPtr<res::AnimationContent>(mpRes, contentOffset);

    const u32* pInfoOffsetTbl =
        detail::ConvertOffsToPtr<u32>(pContent, sizeof(res::AnimationContent));

    for (int i = 0; i < pContent->num; i++) {
        const res::AnimationInfo* pAnimInfo =
            detail::ConvertOffsToPtr<res::AnimationInfo>(pContent,
                                                         pInfoOffsetTbl[i]);

        const u32* pTargetOffsetTbl = detail::ConvertOffsToPtr<u32>(
            pAnimInfo, sizeof(res::AnimationInfo));

        switch (pAnimInfo->kind) {
        case res::AnimationInfo::SIGNATURE_ANMMATCLR: {
            AnimateMaterialColor(pMaterial, pAnimInfo, pTargetOffsetTbl,
                                 mFrame);
            break;
        }

        case res::AnimationInfo::SIGNATURE_ANMTEXSRT: {
            AnimateTextureSRT(pMaterial, pAnimInfo, pTargetOffsetTbl, mFrame);
            break;
        }

        case res::AnimationInfo::SIGNATURE_ANMTEXPAT: {
            if (mpFileResAry == NULL) {
                break;
            }

            AnimateTexturePattern(pMaterial, pAnimInfo, pTargetOffsetTbl,
                                  mFrame, mpFileResAry);
            break;
        }

        case res::AnimationInfo::SIGNATURE_ANMINDTEXSRT: {
            AnimateIndTexSRT(pMaterial, pAnimInfo, pTargetOffsetTbl, mFrame);
            break;
        }
        }
    }
}

/******************************************************************************
 *
 * Functions
 *
 ******************************************************************************/
namespace detail {

AnimationLink* FindAnimationLink(AnimationLinkList* pAnimList,
                                 AnimTransform* pAnimTrans) {

    NW4R_UT_LINKLIST_FOREACH(it, *pAnimList, {
        if (pAnimTrans == it->GetAnimTransform()) {
            return &*it;
        }
    });

    return NULL;
}

} // namespace detail
} // namespace lyt
} // namespace nw4r
