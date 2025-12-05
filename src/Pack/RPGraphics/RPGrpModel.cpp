#include <Pack/RPGraphics.h>

#include <egg/math.h>

#include <revolution/GX.h>

EGG::Allocator* RPGrpModel::spAllocator = NULL;

RPGrpModel* RPGrpModel::spEntryHead = NULL;
RPGrpModel* RPGrpModel::spEntryTail = NULL;
RPGrpModel* RPGrpModel::spGenList = NULL;

RPGrpModel* RPGrpModel::spCalcModel = NULL;
EGG::Matrix34f* RPGrpModel::spCalcModelMtxArray = NULL;
EGG::Matrix34f* RPGrpModel::spCalcViewPosMtxArray = NULL;

RPGrpModel* RPGrpModel::Construct(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                                  u32 bufferOption) {
    RPGrpModel* pModel = NULL;

    switch (RPGrpModelResManager::GetCurrent()->GetType(handle)) {
    case RPGrpModelResManager::Type_ResMdl: {
        pModel = new RPGrpModelG3D(handle, viewNo, typeOption, bufferOption);
        break;
    }

    case RPGrpModelResManager::Type_1:
    default: {
        break;
    }
    }

    pModel->Configure();
    pModel->CreateAnm();
    return pModel;
}

RPGrpModel* RPGrpModel::Construct(RPGrpHandle handle, int idx, u8 viewNo,
                                  u32 typeOption, u32 bufferOption) {
    RPGrpModel* pModel =
        new RPGrpModelG3D(handle, idx, viewNo, typeOption, bufferOption);

    pModel->Configure();
    pModel->CreateAnm();
    return pModel;
}

RPGrpModel* RPGrpModel::Construct(RPGrpHandle handle, const char* pName,
                                  u8 viewNo, u32 typeOption, u32 bufferOption) {
    RPGrpModel* pModel =
        new RPGrpModelG3D(handle, pName, viewNo, typeOption, bufferOption);

    pModel->Configure();
    pModel->CreateAnm();
    return pModel;
}

RPGrpModel::RPGrpModel(u8 viewNo)
    : mViewNo(viewNo),
      mDrawScene(0),
      mDrawGroup(0),
      unk3(8),
      unk4(8),
      mFlags(EFlag_Visible),
      unkA(0),
      unkC(0),
      unk10(0),
      mpEntryNext(NULL),
      mpGenNext(NULL),
      mpCallback(NULL),
      unk20(1.0f),
      unk24(1.0f),
      unk28(1.0f),
      mpModelAnm(NULL),
      mppMaterials(NULL),
      mpBoundingInfo(NULL),
      mpRecord(NULL),
      mReverseCulling(false),
      mpModelEx(NULL) {

    mpGenNext = spGenList;
    spGenList = this;
}

RPGrpModel::~RPGrpModel() {}

void RPGrpModel::Configure() {
    if (GetMaterialNum() <= 0) {
        return;
    }

    mppMaterials = new RPGrpModelMaterial*[GetMaterialNum()];

    for (int i = 0; i < GetMaterialNum(); i++) {
        mppMaterials[i] = NULL;
        CreateMaterial(i);
    }
}

IRPGrpModelCallback* RPGrpModel::SetCallback(IRPGrpModelCallback* pCallback) {
    IRPGrpModelCallback* pOldCallback = mpCallback;
    mpCallback = pCallback;
    return pOldCallback;
}

void RPGrpModel::CreateMaterial(u16 idx) {
    mppMaterials[idx] = new RPGrpModelMaterial(this, idx);
}

void RPGrpModel::CreateBoundingInfo(u32 flags) {
    u32 boundFlags = 0;

    if (flags & BoundOption_Sphere) {
        boundFlags |= RPGrpModelBoundingInfo::BoundFlag_Sphere;
    }

    if (flags & BoundOption_SphereSet) {
        boundFlags |= RPGrpModelBoundingInfo::BoundFlag_Sphere |
                      RPGrpModelBoundingInfo::BoundFlag_SphereSet;
    }

    if (flags & BoundOption_AABB) {
        boundFlags |= RPGrpModelBoundingInfo::BoundFlag_AABB;
    }

    if (flags & BoundOption_AABBSet) {
        boundFlags |= RPGrpModelBoundingInfo::BoundFlag_AABB |
                      RPGrpModelBoundingInfo::BoundFlag_AABBSet;
    }

    IRPGrpModelCallback* pCallback = SetCallback(NULL);
    mpBoundingInfo = new RPGrpModelBoundingInfo(boundFlags, this);
    SetCallback(pCallback);
}

void RPGrpModel::CreateRecord(u16 frames) {
    mpRecord = new RPGrpModelRecord(frames, this);
    mpRecord->Clear();
    mFlags |= EFlag_HasRecord;
}

void RPGrpModel::UpdateFrame() {
    if (mpModelAnm != NULL) {
        mpModelAnm->UpdateFrame();
    }

    nw4r::g3d::ScnObj* pScnObj = mpModelEx->getScnObj();
    if (pScnObj != NULL) {
        pScnObj->G3dProc(nw4r::g3d::G3dObj::G3DPROC_UPDATEFRAME, 0, NULL);
    }
}

void RPGrpModel::Calc() {
    spCalcModel = this;

    if (mpModelAnm != NULL) {
        mpModelAnm->Calc();
    }

    InternalCalc();

    if (mpBoundingInfo != NULL) {
        mpBoundingInfo->Calc();
    }

    spCalcModel = NULL;
}

void RPGrpModel::Entry() {
    if (spEntryTail != NULL) {
        spEntryTail->mpEntryNext = this;
    } else {
        spEntryHead = this;
    }

    spEntryTail = this;
    mFlags |= EFlag_Entered;
}

void RPGrpModel::CalcMaterial() {
    for (int i = 0; i < GetMaterialNum(); i++) {
        mppMaterials[i]->Calc();
    }
}

u16 RPGrpModel::GetMaterialNum() const {
    return mpModelEx->getNumMaterial();
}

void RPGrpModel::SetReverseCulling(bool reverse) {
    if (reverse == mReverseCulling) {
        return;
    }

    if (!mReverseCulling || !reverse) {
        for (u16 i = 0; i < GetMaterialNum(); i++) {
            if (mppMaterials[i]->GetCullMode() == GX_CULL_BACK) {
                mppMaterials[i]->SetCullMode(GX_CULL_FRONT);
            } else if (mppMaterials[i]->GetCullMode() == GX_CULL_FRONT) {
                mppMaterials[i]->SetCullMode(GX_CULL_BACK);
            }

            mppMaterials[i]->SetSyncFlags(
                RPGrpModelMaterial::ESyncFlag_ResGenMode);
        }
    }

    mReverseCulling = reverse;
}

u16 RPGrpModel::ReplaceTexture(const char* pName, const RPGrpTexture& rTexture,
                               bool keepFilterWrap) {

    GXTexObj texObj = rTexture.GetTexObj();
    return mpModelEx->replaceTexture(pName, texObj, keepFilterWrap, NULL, 0,
                                     true);
}

void RPGrpModel::RemoveGenList() {
    RPGrpModel* pIt = spGenList;
    RPGrpModel* pPrev = NULL;

    for (; pIt != NULL; pPrev = pIt, pIt = pIt->mpGenNext) {
        if (pIt != this) {
            continue;
        }

        if (pPrev != NULL) {
            pPrev->mpGenNext = mpGenNext;
            break;
        }

        spGenList = mpGenNext;
    }
}
