#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                             u32 bufferOption)
    : RPGrpModel(viewNo) {

    const nw4r::g3d::ResMdl mdl =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResMdl>(handle);

    nw4r::g3d::ScnObj* pScnObj;
    u32 size;

    if (bufferOption == 0 && !(typeOption & TypeOption_NoSimple)) {
        pScnObj =
            nw4r::g3d::ScnMdlSimple::Construct(spAllocator, &size, mdl, viewNo);
    } else {
        pScnObj = nw4r::g3d::ScnMdl::Construct(spAllocator, &size, mdl,
                                               bufferOption, viewNo);
    }

    mpModelEx = new EGG::ModelEx(pScnObj);
}

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, int idx, u8 viewNo,
                             u32 typeOption, u32 bufferOption)
    : RPGrpModel(viewNo) {

    const nw4r::g3d::ResFile file =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResFile>(handle);

    const nw4r::g3d::ResMdl mdl = file.GetResMdl(idx);

    nw4r::g3d::ScnObj* pScnObj;
    u32 size;

    if (bufferOption == 0 && !(typeOption & TypeOption_NoSimple)) {
        pScnObj =
            nw4r::g3d::ScnMdlSimple::Construct(spAllocator, &size, mdl, viewNo);
    } else {
        pScnObj = nw4r::g3d::ScnMdl::Construct(spAllocator, &size, mdl,
                                               bufferOption, viewNo);
    }

    mpModelEx = new EGG::ModelEx(pScnObj);
}

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, const char* pName, u8 viewNo,
                             u32 typeOption, u32 bufferOption)
    : RPGrpModel(viewNo) {

    const nw4r::g3d::ResFile file =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResFile>(handle);

    const nw4r::g3d::ResMdl mdl = file.GetResMdl(pName);

    nw4r::g3d::ScnObj* pScnObj;
    u32 size;

    if (bufferOption == 0 && !(typeOption & TypeOption_NoSimple)) {
        pScnObj =
            nw4r::g3d::ScnMdlSimple::Construct(spAllocator, &size, mdl, viewNo);
    } else {
        pScnObj = nw4r::g3d::ScnMdl::Construct(spAllocator, &size, mdl,
                                               bufferOption, viewNo);
    }

    mpModelEx = new EGG::ModelEx(pScnObj);
}

void RPGrpModelG3D::Configure() {
    RPGrpModel::Configure();

    GetScnMdlSimple()->SetScnObjCallback(this);
    GetScnMdlSimple()->SetScnMdlCallback(this);

    GetScnMdlSimple()->EnableScnObjCallbackTiming(
        nw4r::g3d::ScnObj::CALLBACK_TIMING_A);

    GetScnMdlSimple()->EnableScnObjCallbackExecOp(
        nw4r::g3d::ScnObj::EXECOP_CALC_MAT);

    InternalCalc();
}

void RPGrpModelG3D::CreateAnm() {
    mpModelAnm = RPGrpModelAnmG3D::Construct(this);
}

IRPGrpModelCallback*
RPGrpModelG3D::SetCallback(IRPGrpModelCallback* pCallback) {
    IRPGrpModelCallback* pOldCallback = mpCallback;
    mpCallback = pCallback;

    if (pCallback == NULL) {
        GetScnMdlSimple()->DisableScnMdlCallbackTiming(
            nw4r::g3d::ScnObj::CALLBACK_TIMING_ALL);
    } else {
        GetScnMdlSimple()->EnableScnMdlCallbackTiming(
            nw4r::g3d::ScnObj::CALLBACK_TIMING_ALL);
    }

    return pOldCallback;
}

void RPGrpModelG3D::InternalCalc() {
    if (!mReverseCulling) {
        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(mScale);
        }
    } else {
        const nw4r::math::_VEC3& rMag = GEOMETRY_MAGNIFY[mReverseCulling - 1];

        nw4r::math::VEC3 scale(mScale.x * rMag.x, mScale.y * rMag.y,
                               mScale.z * rMag.z);

        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(scale);
        }
    }

    if (mpRecord != NULL) {
        GetScnMdlSimple()->EnableScnMdlCallbackTiming(
            nw4r::g3d::ScnMdl::CALLBACK_TIMING_C);
    }

    if (GetScnObj() != NULL) {
        GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_WORLD, 0, NULL);
    }
}

void RPGrpModelG3D::CalcBeforeDraw() {
    RPGrpModel::CalcBeforeDraw();

    if (mpCallback != NULL) {
        spCalcViewMtxArray = GetScnMdlSimple()->GetViewPosMtxArray();
        spCalcModel = this;

        mpCallback->ReferViewMtx(this);

        spCalcViewMtxArray = NULL;
        spCalcModel = NULL;
    }
}

void RPGrpModelG3D::SetJointVisible(u32 idx, bool enable) {
    if (GetScnMdl() != NULL) {
        nw4r::g3d::ScnMdl::CopiedVisAccess access(GetScnMdl(), idx);
        access.SetVisibilityEx(enable);
    } else {
        GetScnMdlSimple()->GetResMdl().GetResNode(idx).SetVisibility(enable);
    }
}

bool RPGrpModelG3D::IsJointVisible(u32 idx) const {
    if (GetScnMdl() != NULL) {
        nw4r::g3d::ScnMdl::CopiedVisAccess access(GetScnMdl(), idx);
        return access.IsVisible();
    } else {
        return GetScnMdlSimple()->GetResMdl().GetResNode(idx).IsVisible();
    }
}

void RPGrpModelG3D::ExecCallback_CALC_WORLD(
    nw4r::g3d::ScnObj::Timing /* timing */, nw4r::g3d::ScnObj* /* pObj */,
    u32 /* param */, void* /* pInfo */) {}

void RPGrpModelG3D::ExecCallback_CALC_MAT(nw4r::g3d::ScnObj::Timing timing,
                                          nw4r::g3d::ScnObj* /* pObj */,
                                          u32 /* param */, void* /* pInfo */) {

    if (!(unkC & 0x40)) {
        if (timing & nw4r::g3d::ScnObj::CALLBACK_TIMING_A) {
            CalcMaterial();
        }
    } else if (timing & nw4r::g3d::ScnObj::CALLBACK_TIMING_C) {
        CalcMaterial();
    }
}

void RPGrpModelG3D::ExecCallback_DRAW_OPA(
    nw4r::g3d::ScnObj::Timing /* timing */, nw4r::g3d::ScnObj* /* pObj */,
    u32 /* param */, void* /* pInfo */) {

    nw4r::g3d::G3DState::Invalidate(nw4r::g3d::G3DState::INVALIDATE_TEV);
}

void RPGrpModelG3D::ExecCallback_DRAW_XLU(
    nw4r::g3d::ScnObj::Timing /* timing */, nw4r::g3d::ScnObj* /* pObj */,
    u32 /* param */, void* /* pInfo */) {

    nw4r::g3d::G3DState::Invalidate(nw4r::g3d::G3DState::INVALIDATE_TEV);
}

void RPGrpModelG3D::ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) {
    nw4r::math::MTX34 trans;
    nw4r::math::VEC3 scale;

    pResult->GetRotTrans(&trans);
    pResult->GetScale(&scale);

    mpCallback->EditJointLocalMtx(
        this, GetScnMdlSimple()->GetScnMdlCallbackNodeID(), &trans, &scale);

    pResult->SetRotTrans(&trans);
    pResult->SetScale(&scale);

    pFuncObj->SetCallbackNodeID(GetScnMdlSimple()->GetScnMdlCallbackNodeID());
}

void RPGrpModelG3D::ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) {
    if (!sJointWorldMtxInitialized) {
        sJointWorldMtxInitialized = true;
    }

    pManip->GetMtx(&sJointWorldMtx);

    mpCallback->EditJointWorldMtx(
        this, GetScnMdlSimple()->GetScnMdlCallbackNodeID(), &sJointWorldMtx);

    pManip->SetMtx(&sJointWorldMtx);

    pFuncObj->SetCallbackNodeID(GetScnMdlSimple()->GetScnMdlCallbackNodeID());
}

void RPGrpModelG3D::ExecCallbackC(nw4r::math::MTX34* pMtxArray,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* /* pFuncObj */) {
    spCalcWorldMtxArray = pMtxArray;
    spCalcModel = this;

    if (mpCallback != NULL) {
        mpCallback->EditWorldMtx(this);
    }

    if (mpRecord != NULL) {
        mpRecord->Calc(this);
    }

    spCalcWorldMtxArray = NULL;
    spCalcModel = NULL;
}
