#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/g3d.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>

#include <cmath>

namespace nw4r {
namespace g3d {

NW4R_G3D_RTTI_DEF(AnmObjChr);
NW4R_G3D_RTTI_DEF(AnmObjChrNode);
NW4R_G3D_RTTI_DEF(AnmObjChrBlend);
NW4R_G3D_RTTI_DEF(AnmObjChrRes);

namespace {

u32 GetPartialNodeEndId(const ResMdl mdl, u32 target) {
    ResNode targetNode = mdl.GetResNode(target);
    ResNode node = targetNode;

    ResNode endNode = node.GetNextSibling();
    while (!endNode.IsValid()) {
        node = node.GetParentNode();
        if (!node.IsValid()) {
            break;
        }

        endNode = node.GetNextSibling();
    }

    if (endNode.IsValid()) {
        return endNode.GetID();
    }

    return mdl.GetResNodeNumEntries();
}

} // namespace

/******************************************************************************
 *
 * AnmObjChr
 *
 ******************************************************************************/
AnmObjChr::AnmObjChr(MEMAllocator* pAllocator, u16* pBindingBuf, int numBinding)
    : AnmObj(pAllocator, NULL),
      mNumBinding(numBinding),
      mpBinding(pBindingBuf) {

    Release();
}

bool AnmObjChr::TestExistence(u32 i) const {
    return !(mpBinding[i] & (BINDING_UNDEFINED | BINDING_INVALID));
}

bool AnmObjChr::TestDefined(u32 i) const {
    return !(mpBinding[i] & BINDING_UNDEFINED);
}

void AnmObjChr::Release() {
    for (int i = 0; i < mNumBinding; i++) {
        mpBinding[i] = BINDING_UNDEFINED;
    }

    SetAnmFlag(FLAG_ANM_BOUND, false);
}

AnmObjChrRes* AnmObjChr::Attach(int i, AnmObjChrRes* pRes) {
#pragma unused(i)
#pragma unused(pRes)

    return NULL;
}

AnmObjChrRes* AnmObjChr::Detach(int i) {
#pragma unused(i)

    return NULL;
}

void AnmObjChr::SetWeight(int i, f32 weight) {
#pragma unused(i)
#pragma unused(weight)
}

f32 AnmObjChr::GetWeight(int i) const {
#pragma unused(i)

    return 0.0f;
}

void AnmObjChr::DetachAll() {}

/******************************************************************************
 *
 * AnmObjChrNode
 *
 ******************************************************************************/
AnmObjChrNode::AnmObjChrNode(MEMAllocator* pAllocator, u16* pBindingBuf,
                             int numBinding, AnmObjChrRes** ppChildrenBuf,
                             int numChildren)
    : AnmObjChr(pAllocator, pBindingBuf, numBinding),
      mChildrenArraySize(numChildren),
      mpChildrenArray(ppChildrenBuf) {

    for (int i = 0; i < mChildrenArraySize; i++) {
        mpChildrenArray[i] = NULL;
    }
}

AnmObjChrNode::~AnmObjChrNode() {
    DetachAll();
}

AnmObjChrRes* AnmObjChrNode::Attach(int i, AnmObjChrRes* pRes) {
    AnmObjChrRes* pOld = Detach(i);
    bool hasAnm = false;

    for (u32 i = 0; i < mNumBinding; i++) {
        if (!pRes->TestDefined(i)) {
            continue;
        }

        hasAnm = true;
        mpBinding[i] = 0;
    }

    if (hasAnm) {
        SetAnmFlag(FLAG_ANM_BOUND, true);
    }

    mpChildrenArray[i] = pRes;
    pRes->G3dProc(G3DPROC_ATTACH_PARENT, 0, this);
    return pOld;
}

AnmObjChrRes* AnmObjChrNode::Detach(int i) {
    AnmObjChrRes* pOld = mpChildrenArray[i];

    if (pOld != NULL) {
        pOld->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
        mpChildrenArray[i] = NULL;

        bool hasAnm = false;
        for (u32 i = 0; i < mNumBinding; i++) {
            u16 binding = BINDING_UNDEFINED;

            for (int j = 0; j < mChildrenArraySize; j++) {
                AnmObjChrRes* pChild = mpChildrenArray[j];

                if (pChild == NULL || !pChild->TestDefined(i)) {
                    continue;
                }

                hasAnm = true;
                binding = 0;
                break;
            }

            mpBinding[i] = binding;
        }

        if (!hasAnm) {
            SetAnmFlag(FLAG_ANM_BOUND, false);
        }
    }

    return pOld;
}

void AnmObjChrNode::DetachAll() {
    for (int i = 0; i < mChildrenArraySize; i++) {
        Detach(i);
    }
}

void AnmObjChrNode::UpdateFrame() {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            mpChildrenArray[i]->UpdateFrame();
        }
    }
}

void AnmObjChrNode::SetFrame(f32 frame) {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            mpChildrenArray[i]->SetFrame(frame);
        }
    }
}

f32 AnmObjChrNode::GetFrame() const {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            return mpChildrenArray[i]->GetFrame();
        }
    }

    return 0.0f;
}

void AnmObjChrNode::SetUpdateRate(f32 rate) {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            mpChildrenArray[i]->SetUpdateRate(rate);
        }
    }
}

f32 AnmObjChrNode::GetUpdateRate() const {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            return mpChildrenArray[i]->GetUpdateRate();
        }
    }

    return 1.0f;
}

bool AnmObjChrNode::Bind(ResMdl mdl) {
    bool success = false;

    for (int i = 0; i < mChildrenArraySize; i++) {
        AnmObjChrRes* pChild = mpChildrenArray[i];
        if (pChild == NULL) {
            continue;
        }

        bool childSuccess = pChild->Bind(mdl);
        success = success || childSuccess;

        for (u32 j = 0; j < mNumBinding; j++) {
            if (pChild->TestDefined(j)) {
                mpBinding[j] = 0;
            }
        }
    }

    SetAnmFlag(FLAG_ANM_BOUND, true);
    return success;
}

bool AnmObjChrNode::Bind(ResMdl mdl, u32 target, BindOption option) {
#pragma unused(target)
#pragma unused(option)

    bool success = false;

    for (int i = 0; i < mChildrenArraySize; i++) {
        AnmObjChrRes* pChild = mpChildrenArray[i];
        if (pChild == NULL) {
            continue;
        }

        bool childSuccess = pChild->Bind(mdl, target, option);
        success = success || childSuccess;

        for (u32 j = 0; j < mNumBinding; j++) {
            if (pChild->TestDefined(j)) {
                mpBinding[j] = 0;
            }
        }
    }

    SetAnmFlag(FLAG_ANM_BOUND, true);
    return success;
}

void AnmObjChrNode::Release() {
    for (int i = 0; i < mChildrenArraySize; i++) {
        if (mpChildrenArray[i] != NULL) {
            mpChildrenArray[i]->Release();
        }
    }

    AnmObjChr::Release();
}

void AnmObjChrNode::Release(const ResMdl mdl, u32 target, BindOption option) {
    for (int i = 0; i < mChildrenArraySize; i++) {
        AnmObjChrRes* pChild = mpChildrenArray[i];

        if (pChild != NULL) {
            pChild->Release(mdl, target, option);
        }
    }

    AnmObjChr::Release();

    for (int i = 0; i < mChildrenArraySize; i++) {
        AnmObjChrRes* pChild = mpChildrenArray[i];
        if (pChild == NULL) {
            continue;
        }

        for (u32 j = 0; j < mNumBinding; j++) {
            if (pChild->TestDefined(j)) {
                mpBinding[j] = 0;
            }
        }
    }
}

void AnmObjChrNode::G3dProc(u32 task, u32 param, void* pInfo) {
#pragma unused(param)

    switch (task) {
    case G3DPROC_CHILD_DETACHED: {
        for (int i = 0; i < mChildrenArraySize; i++) {
            if (mpChildrenArray[i] == pInfo) {
                Detach(i);
                return;
            }
        }

        break;
    }

    case G3DPROC_DETACH_PARENT: {
        SetParent(NULL);
        break;
    }

    case G3DPROC_ATTACH_PARENT: {
        SetParent(static_cast<G3dObj*>(pInfo));
        break;
    }
    }
}

/******************************************************************************
 *
 * AnmObjChrBlend
 *
 ******************************************************************************/
AnmObjChrBlend* AnmObjChrBlend::Construct(MEMAllocator* pAllocator, u32* pSize,
                                          ResMdl mdl, int numChildren) {
    if (!mdl.IsValid()) {
        return NULL;
    }

    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    int bindNum = mdl.GetResNodeNumEntries();

    u32 bindSize = bindNum * sizeof(u16);
    u32 childrenSize = numChildren * sizeof(AnmObjChrRes*);
    u32 weightSize = numChildren * sizeof(f32);

    u32 bindOfs = ut::RoundUp(sizeof(AnmObjChrBlend), 4);
    u32 childrenOfs = ut::RoundUp(bindOfs + bindSize, 4);
    u32 weightOfs = ut::RoundUp(childrenOfs + childrenSize, 4);

    u32 size = ut::RoundUp(weightOfs + weightSize, 4);
    if (pSize != NULL) {
        *pSize = size;
    }

    if (pAllocator == NULL) {
        return NULL;
    }

    u8* pBuffer = reinterpret_cast<u8*>(Alloc(pAllocator, size));
    if (pBuffer == NULL) {
        return NULL;
    }

    // clang-format off
    return new (pBuffer) AnmObjChrBlend(
        pAllocator,
        reinterpret_cast<u16*>(pBuffer + bindOfs),
        bindNum,
        reinterpret_cast<AnmObjChrRes**>(pBuffer + childrenOfs),
        numChildren,
        reinterpret_cast<f32*>(pBuffer + weightOfs));
    // clang-format on
}

AnmObjChrBlend::AnmObjChrBlend(MEMAllocator* pAllocator, u16* pBindingBuf,
                               int numBinding, AnmObjChrRes** ppChildrenBuf,
                               int numChildren, f32* pWeightBuf)
    : AnmObjChrNode(pAllocator, pBindingBuf, numBinding, ppChildrenBuf,
                    numChildren),
      mpWeightArray(pWeightBuf) {

    for (int i = 0; i < mChildrenArraySize; i++) {
        mpWeightArray[i] = 1.0f;
    }
}

const ChrAnmResult* AnmObjChrBlend::GetResult(ChrAnmResult* pResult, u32 i) {
    AnmObjChrRes* pFirstChild = NULL;
    int blendNum = 0;
    f32 weightSum = 0.0f;

    for (u32 j = 0; static_cast<int>(j) < mChildrenArraySize; j++) {
        f32 weight = mpWeightArray[j];
        AnmObjChrRes* pChild = mpChildrenArray[j];

        if (pChild == NULL) {
            continue;
        }

        if (weight == 0.0f || !pChild->TestExistence(i)) {
            continue;
        }

        blendNum++;
        weightSum += weight;

        if (pFirstChild == NULL) {
            pFirstChild = pChild;
        }
    }

    if (blendNum == 0) {
        pResult->flags = 0;
        return pResult;
    }

    if (blendNum == 1) {
        return pFirstChild->GetResult(pResult, i);
    }

    bool useQuat = TestAnmFlag(FLAG_USE_QUATERNION_ROTATION_BLEND);
    bool useAccScale = TestAnmFlag(FLAG_USE_ACCURATE_SCALE_BLEND);

    f32 esx = 0.0f;
    f32 esy = 0.0f;
    f32 esz = 0.0f;
    math::QUAT rot(0.0f, 0.0f, 0.0f, 1.0f);

    f32 addedWeight = 0.0f;
    math::MTX33 firstRot;
    f32 invWeightSum = math::FInv(weightSum);

    pResult->flags = 0xFFFFFFFF;
    pResult->s.x = 0.0f;
    pResult->s.y = 0.0f;
    pResult->s.z = 0.0f;
    math::MTX34Zero(&pResult->rt);

    for (int j = 0; j < mChildrenArraySize; j++) {
        ChrAnmResult resultBuf;

        AnmObjChrRes* pChild = mpChildrenArray[j];
        f32 weight = mpWeightArray[j];

        if (pChild == NULL || weight == 0.0f || !pChild->TestExistence(i)) {
            continue;
        }

        const ChrAnmResult* pMyResult = pChild->GetResult(&resultBuf, i);

        f32 ratio = weight * invWeightSum;
        u32 flags = pMyResult->flags;

        if (useAccScale) {
            if (!(flags & ChrAnmResult::FLAG_S_ONE)) {
                esx += ratio * math::FLog(pMyResult->s.x);
                esy += ratio * math::FLog(pMyResult->s.y);
                esz += ratio * math::FLog(pMyResult->s.z);
            }
        } else if (!(flags & ChrAnmResult::FLAG_S_ONE)) {
            pResult->s.x += pMyResult->s.x * ratio;
            pResult->s.y += pMyResult->s.y * ratio;
            pResult->s.z += pMyResult->s.z * ratio;
        } else {
            pResult->s.x += ratio;
            pResult->s.y += ratio;
            pResult->s.z += ratio;
        }

        if (useQuat) {
            math::QUAT q;

            if (!(flags & ChrAnmResult::FLAG_R_ZERO)) {
                math::MTX34ToQUAT(&q, &pMyResult->rt);
            } else {
                q.x = 0.0f;
                q.y = 0.0f;
                q.z = 0.0f;
                q.w = 1.0f;
            }

            addedWeight += weight;
            f32 invAddedWeight = math::FInv(addedWeight);

            f32 t = weight * invAddedWeight;
            math::C_QUATSlerp(&rot, &rot, &q, t);
        } else if (!(flags & ChrAnmResult::FLAG_R_ZERO)) {
            pResult->rt.m[0][0] += pMyResult->rt.m[0][0] * ratio;
            pResult->rt.m[0][1] += pMyResult->rt.m[0][1] * ratio;
            pResult->rt.m[0][2] += pMyResult->rt.m[0][2] * ratio;

            pResult->rt.m[1][0] += pMyResult->rt.m[1][0] * ratio;
            pResult->rt.m[1][1] += pMyResult->rt.m[1][1] * ratio;
            pResult->rt.m[1][2] += pMyResult->rt.m[1][2] * ratio;
        } else {
            pResult->rt.m[0][0] += ratio;
            pResult->rt.m[1][1] += ratio;
        }

        if (!(flags & ChrAnmResult::FLAG_T_ZERO)) {
            pResult->rt.m[0][3] += pMyResult->rt.m[0][3] * ratio;
            pResult->rt.m[1][3] += pMyResult->rt.m[1][3] * ratio;
            pResult->rt.m[2][3] += pMyResult->rt.m[2][3] * ratio;
        }

        pResult->flags &= flags;
    }

    if (useAccScale) {
        pResult->s.x = math::FExp(esx);
        pResult->s.y = math::FExp(esy);
        pResult->s.z = math::FExp(esz);
    }

    if (useQuat) {
        Vec t;
        t.x = pResult->rt.m[0][3];
        t.y = pResult->rt.m[1][3];
        t.z = pResult->rt.m[2][3];

        math::QUATToMTX34(&pResult->rt, &rot);

        pResult->rt.m[0][3] = t.x;
        pResult->rt.m[1][3] = t.y;
        pResult->rt.m[2][3] = t.z;
    } else {
        math::VEC3* pV0 = reinterpret_cast<math::VEC3*>(&pResult->rt.m[0][0]);
        math::VEC3* pV1 = reinterpret_cast<math::VEC3*>(&pResult->rt.m[1][0]);
        math::VEC3* pV2 = reinterpret_cast<math::VEC3*>(&pResult->rt.m[2][0]);
        math::VEC3Cross(pV2, pV0, pV1);

        math::VEC3Normalize(pV0, pV0);
        math::VEC3Normalize(pV2, pV2);
        math::VEC3Cross(pV1, pV2, pV0);
    }

    pResult->flags &= ~ChrAnmResult::FLAG_R_RAW_FMT;
    return pResult;
}

void AnmObjChrBlend::SetWeight(int i, f32 weight) {
    mpWeightArray[i] = weight;
}

f32 AnmObjChrBlend::GetWeight(int i) const {
    return mpWeightArray[i];
}

/******************************************************************************
 *
 * AnmObjChrRes
 *
 ******************************************************************************/
AnmObjChrRes* AnmObjChrRes::Construct(MEMAllocator* pAllocator, u32* pSize,
                                      ResAnmChr chr, ResMdl mdl, bool cache) {
    if (!chr.IsValid() || !mdl.IsValid()) {
        return NULL;
    }

    int numAnim = chr.GetNumNode();
    int numMat = mdl.GetResNodeNumEntries();

    int bindNum = numMat;
    int cacheNum = cache ? numAnim : 0;

    u32 bindSize = bindNum * sizeof(u16);
    u32 cacheSize = cacheNum * sizeof(ChrAnmResult);

    u32 size = bindSize + cacheSize + sizeof(AnmObjChrRes);
    if (pSize != NULL) {
        *pSize = size;
    }

    if (pAllocator == NULL) {
        return NULL;
    }

    u8* pBuffer = reinterpret_cast<u8*>(Alloc(pAllocator, size));
    if (pBuffer == NULL) {
        return NULL;
    }

    ChrAnmResult* pCacheBuf =
        cache ? reinterpret_cast<ChrAnmResult*>(pBuffer + sizeof(AnmObjChrRes))
              : NULL;

    u16* pBindingBuf =
        reinterpret_cast<u16*>(cacheSize + (pBuffer + sizeof(AnmObjChrRes)));

    return new (pBuffer)
        AnmObjChrRes(pAllocator, chr, pBindingBuf, bindNum, pCacheBuf);
}

AnmObjChrRes::AnmObjChrRes(MEMAllocator* pAllocator, ResAnmChr chr,
                           u16* pBindingBuf, int numBinding,
                           ChrAnmResult* pCacheBuf)
    : AnmObjChr(pAllocator, pBindingBuf, numBinding),
      FrameCtrl(0.0f, chr.GetNumFrame(), GetAnmPlayPolicy(chr.GetAnmPolicy())),
      mRes(chr),
      mpResultCache(pCacheBuf) {

    if (mpResultCache != NULL) {
        UpdateCache();
    }
}

void AnmObjChrRes::SetFrame(f32 frame) {
    SetFrm(frame);

    if (mpResultCache != NULL) {
        UpdateCache();
    }
}

f32 AnmObjChrRes::GetFrame() const {
    return GetFrm();
}

void AnmObjChrRes::SetUpdateRate(f32 rate) {
    SetRate(rate);
}

f32 AnmObjChrRes::GetUpdateRate() const {
    return GetRate();
}

void AnmObjChrRes::UpdateFrame() {
    UpdateFrm();

    if (mpResultCache != NULL) {
        UpdateCache();
    }
}

bool AnmObjChrRes::Bind(ResMdl mdl) {
    int numAnim = mRes.GetNumNode();
    bool success = false;

    for (u16 i = 0; i < numAnim; i++) {
        const ResAnmChrNodeData* pData = mRes.GetNodeAnm(i);

        // Seek back from name string to start of ResName
        ResName name(ut::AddOffsetToPtr(pData, pData->name - 4));

        ResNode node = mdl.GetResNode(name);
        if (!node.IsValid()) {
            continue;
        }

        mpBinding[node.GetID()] = i;
        success = true;
    }

    SetAnmFlag(FLAG_ANM_BOUND, true);
    return success;
}

bool AnmObjChrRes::Bind(ResMdl mdl, u32 target, BindOption option) {
    bool success = false;

    switch (option) {
    case BIND_PARTIAL: {
        u32 bindBegin = target;
        u32 bindEnd = GetPartialNodeEndId(mdl, bindBegin);

        for (u32 i = bindBegin; i < bindEnd; i++) {
            ResNode node = mdl.GetResNode(i);
            ResName name = node.GetResName();

            int id = mRes.GetNodeAnmIndex(name);
            if (id != ResDic::NOT_FOUND) {
                mpBinding[i] = static_cast<u16>(id);
                success = true;
            }
        }

        break;
    }

    case BIND_ONE: {
        ResNode node = mdl.GetResNode(target);
        ResName name = node.GetResName();

        int id = mRes.GetNodeAnmIndex(name);
        if (id != ResDic::NOT_FOUND) {
            mpBinding[target] = static_cast<u16>(id);
            success = true;
        }
        break;
    }

    default: {
        break;
    }
    }

    SetAnmFlag(FLAG_ANM_BOUND, true);
    return success;
}

void AnmObjChrRes::Release(const ResMdl mdl, u32 target, BindOption option) {
    switch (option) {
    case BIND_PARTIAL: {
        u32 bindBegin = target;
        u32 bindEnd = GetPartialNodeEndId(mdl, bindBegin);

        for (u32 i = bindBegin; i < bindEnd; i++) {
            mpBinding[i] = BINDING_UNDEFINED;
        }

        break;
    }

    case BIND_ONE: {
        mpBinding[target] = BINDING_UNDEFINED;
        break;
    }

    default: {
        break;
    }
    }
}

const ChrAnmResult* AnmObjChrRes::GetResult(ChrAnmResult* pResult, u32 i) {
    u32 id = mpBinding[i];

    if (id & (BINDING_UNDEFINED | BINDING_INVALID)) {
        pResult->flags = 0;
        return pResult;
    }

    if (mpResultCache != NULL) {
        return &mpResultCache[id];
    }

    mRes.GetAnmResult(pResult, id, GetFrm());
    return pResult;
}

void AnmObjChrRes::UpdateCache() {
    f32 frame = GetFrm();

    for (u32 i = 0; i < mNumBinding; i++) {
        u16 bind = mpBinding[i];

        if (!(bind & BINDING_UNDEFINED)) {
            u32 id = bind & BINDING_ID_MASK;
            mRes.GetAnmResult(&mpResultCache[id], id, frame);
        }
    }
}

void AnmObjChrRes::G3dProc(u32 task, u32 param, void* pInfo) {
#pragma unused(param)

    switch (task) {
    case G3DPROC_UPDATEFRAME: {
        UpdateFrame();
        break;
    }

    case G3DPROC_DETACH_PARENT: {
        SetParent(NULL);
        break;
    }

    case G3DPROC_ATTACH_PARENT: {
        SetParent(static_cast<G3dObj*>(pInfo));
        break;
    }
    }
}

} // namespace g3d
} // namespace nw4r
