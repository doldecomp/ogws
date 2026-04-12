#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

/******************************************************************************
 *
 * RPGrpModelAnmG3D
 *
 ******************************************************************************/

//! Animation object type conversion table
// clang-format off
const nw4r::g3d::ScnMdlSimple::AnmObjType RPGrpModelAnmG3D::TO_G3D_TYPE[Anm_Max] = {
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_CHR,    // Anm_Chr
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_MATCLR, // Anm_Clr
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_TEXPAT, // Anm_TexPat
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_TEXSRT, // Anm_TexSrt
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_VIS,    // Anm_Vis
    nw4r::g3d::ScnMdlSimple::ANMOBJTYPE_SHP,    // Anm_Shp
};
// clang-format on

//! Animation play policy conversion table
const RPGrpModelAnm::AnmPlayPolicy RPGrpModelAnmG3D::FROM_G3D_POLICY[] = {
    AnmPlayPolicy_OneTime, // nw4r::g3d::ANM_POLICY_ONETIME
    AnmPlayPolicy_Loop,    // nw4r::g3d::ANM_POLICY_LOOP
    AnmPlayPolicy_2,       // ???
    AnmPlayPolicy_3,       // ???
    AnmPlayPolicy_4,       // ???
};

void RPGrpModelAnmG3D::RegistFromResFile(Anm anm, AnmIdx idx,
                                         RPGrpHandle handle,
                                         const char* pName) {
    InternalRegist(anm, idx);

    switch (anm) {
    case Anm_Chr: {
        const nw4r::g3d::ResAnmChr chr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmChr>(handle, pName);

        RegistAnmChr(idx, chr);
        break;
    }

    case Anm_Clr: {
        const nw4r::g3d::ResAnmClr clr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmClr>(handle, pName);

        RegistAnmClr(idx, clr);
        break;
    }

    case Anm_TexPat: {
        const nw4r::g3d::ResAnmTexPat pat =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexPat>(handle,
                                                                   pName);

        RegistAnmTexPat(idx, pat);
        break;
    }

    case Anm_TexSrt: {
        const nw4r::g3d::ResAnmTexSrt srt =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexSrt>(handle,
                                                                   pName);

        RegistAnmTexSrt(idx, srt);
        break;
    }

    case Anm_Vis: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, pName);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_Shp: {
        const nw4r::g3d::ResAnmShp shp =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmShp>(handle, pName);

        RegistAnmShp(idx, shp);
        break;
    }

    case Anm_6: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, pName);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_7: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, pName);

        RegistAnmVis(idx, vis);
        break;
    }

    default: {
        break;
    }
    }
}

void RPGrpModelAnmG3D::RegistFromResFile(Anm anm, AnmIdx idx,
                                         RPGrpHandle handle, u32 id) {
    InternalRegist(anm, idx);

    switch (anm) {
    case Anm_Chr: {
        const nw4r::g3d::ResAnmChr chr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmChr>(handle, id);

        RegistAnmChr(idx, chr);
        break;
    }

    case Anm_Clr: {
        const nw4r::g3d::ResAnmClr clr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmClr>(handle, id);

        RegistAnmClr(idx, clr);
        break;
    }

    case Anm_TexPat: {
        const nw4r::g3d::ResAnmTexPat pat =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexPat>(handle, id);

        RegistAnmTexPat(idx, pat);
        break;
    }

    case Anm_TexSrt: {
        const nw4r::g3d::ResAnmTexSrt srt =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexSrt>(handle, id);

        RegistAnmTexSrt(idx, srt);
        break;
    }

    case Anm_Vis: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, id);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_Shp: {
        const nw4r::g3d::ResAnmShp shp =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmShp>(handle, id);

        RegistAnmShp(idx, shp);
        break;
    }

    case Anm_6: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, id);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_7: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle, id);

        RegistAnmVis(idx, vis);
        break;
    }

    default: {
        break;
    }
    }
}

void RPGrpModelAnmG3D::Init() {
    mppAnmObjChrRes = NULL;
    mppAnmObjMatClrRes = NULL;
    mppAnmObjTexPatRes = NULL;
    mppAnmObjTexSrtRes = NULL;
    mppAnmObjVisRes = NULL;
    mppAnmObjShpRes = NULL;
    unk88 = NULL;
    unk8C = NULL;

    for (int i = 0; i < Anm_Max; i++) {
        unk90[i] = 0;
    }

    mpChrBlendInfo = NULL;
    mpShpBlendInfo = NULL;
}

void RPGrpModelAnmG3D::SetAnmObj(Anm anm, nw4r::g3d::AnmObj** ppAnmObjs) {
    switch (anm) {
    case Anm_Chr: {
        mppAnmObjChrRes =
            reinterpret_cast<nw4r::g3d::AnmObjChrRes**>(ppAnmObjs);
        break;
    }

    case Anm_Clr: {
        mppAnmObjMatClrRes =
            reinterpret_cast<nw4r::g3d::AnmObjMatClrRes**>(ppAnmObjs);
        break;
    }

    case Anm_TexPat: {
        mppAnmObjTexPatRes =
            reinterpret_cast<nw4r::g3d::AnmObjTexPatRes**>(ppAnmObjs);
        break;
    }

    case Anm_TexSrt: {
        mppAnmObjTexSrtRes =
            reinterpret_cast<nw4r::g3d::AnmObjTexSrtRes**>(ppAnmObjs);
        break;
    }

    case Anm_Vis: {
        mppAnmObjVisRes =
            reinterpret_cast<nw4r::g3d::AnmObjVisRes**>(ppAnmObjs);
        break;
    }

    case Anm_Shp: {
        mppAnmObjShpRes =
            reinterpret_cast<nw4r::g3d::AnmObjShpRes**>(ppAnmObjs);
        break;
    }

    case Anm_6: {
        unk88 = reinterpret_cast<nw4r::g3d::AnmObjVisRes**>(ppAnmObjs);
        break;
    }

    case Anm_7: {
        unk8C = reinterpret_cast<nw4r::g3d::AnmObjVisRes**>(ppAnmObjs);
        break;
    }

    default: {
        break;
    }
    }

    InternalSetAnmObj(anm);
}

nw4r::g3d::AnmObj* RPGrpModelAnmG3D::InternalGetAnmObj(Anm anm,
                                                       AnmIdx idx) const {
    switch (anm) {
    case Anm_Chr: {
        return mppAnmObjChrRes[idx];
    }

    case Anm_Clr: {
        return mppAnmObjMatClrRes[idx];
    }

    case Anm_TexPat: {
        return mppAnmObjTexPatRes[idx];
        break;
    }

    case Anm_TexSrt: {
        return mppAnmObjTexSrtRes[idx];
        break;
    }

    case Anm_Vis: {
        return mppAnmObjVisRes[idx];
        break;
    }

    case Anm_Shp: {
        return mppAnmObjShpRes[idx];
        break;
    }

    case Anm_6: {
        return unk88[idx];
        break;
    }

    case Anm_7: {
        return unk8C[idx];
        break;
    }

    default: {
        return NULL;
    }
    }
}

void RPGrpModelAnmG3D::VF_0x74(UNKTYPE) {}

void RPGrpModelAnmG3D::Configure() {
    RPGrpModelAnm::Configure();

    for (int i = 0; i < Anm_Max; i++) {
        unk90[i] = 0;
    }

    mppAnmObjChrRes = NULL;
    mppAnmObjMatClrRes = NULL;
    mppAnmObjTexPatRes = NULL;
    mppAnmObjTexSrtRes = NULL;
    mppAnmObjVisRes = NULL;
    mppAnmObjShpRes = NULL;
    unk88 = NULL;
    unk8C = NULL;

    mpChrBlendInfo = NULL;
#if defined(BUG_FIX)
    mpShpBlendInfo = NULL;
#endif
}

RPGrpModelAnmG3D::RPGrpModelAnmImplement(RPGrpModel* pModel) {
    mpScnMdlSimple = pModel->GetScnMdlSimple();
    Init();

    for (int i = 0; i < Anm_Max; i++) {
        mpToIndexG3D[i] = NULL;
    }
}

void RPGrpModelAnmG3D::InternalSetAnmObj(Anm anm) {
    mpToIndexG3D[anm] = new s8[GetAnmNum(anm)];

    for (int i = 0; i < GetAnmNum(anm); i++) {
        mpToIndexG3D[anm][i] = -1;
    }

    switch (anm) {
    case Anm_Chr: {
        // TODO(kiwi) Why only one? SetBlendWeight could write way out of bounds
        mpChrBlendInfo = new ChrBlendInfo[1];

        mpChrBlendInfo[0].pAnmObj = nw4r::g3d::AnmObjChrBlend::Construct(
            RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl(), 8);

        for (int i = 0; i < 8; i++) {
            mpChrBlendInfo[0].toAnmIdx[i] = -1;
        }
        break;
    }

    case Anm_Clr: {
        if (GetAnmNum(Anm_Clr) >= 2) {

            mpAnmObjMatClrOverride = nw4r::g3d::AnmObjMatClrOverride::Construct(
                RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl(),
                GetAnmNum(Anm_Clr));

            mpAnmObjMatClrOverride->Bind(mpScnMdlSimple->GetResMdl());
            mpScnMdlSimple->SetAnmObj(mpAnmObjMatClrOverride);
        } else {
            mpAnmObjMatClrOverride = NULL;
        }
        break;
    }

    case Anm_TexPat: {
        if (GetAnmNum(Anm_TexPat) >= 2) {

            mpAnmObjTexPatOverride = nw4r::g3d::AnmObjTexPatOverride::Construct(
                RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl(),
                GetAnmNum(Anm_TexPat));

            mpAnmObjTexPatOverride->Bind(mpScnMdlSimple->GetResMdl());
            mpScnMdlSimple->SetAnmObj(mpAnmObjTexPatOverride);
        } else {
            mpAnmObjTexPatOverride = NULL;
        }
        break;
    }

    case Anm_TexSrt: {
        if (GetAnmNum(Anm_TexSrt) >= 2) {

            mpAnmObjTexSrtOverride = nw4r::g3d::AnmObjTexSrtOverride::Construct(
                RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl(),
                GetAnmNum(Anm_TexSrt));

            mpAnmObjTexSrtOverride->Bind(mpScnMdlSimple->GetResMdl());
            mpScnMdlSimple->SetAnmObj(mpAnmObjTexSrtOverride);
        } else {
            mpAnmObjTexSrtOverride = NULL;
        }
        break;
    }

    case Anm_Vis: {
        if (GetAnmNum(Anm_Vis) >= 2) {

            mpAnmObjVisOR = nw4r::g3d::AnmObjVisOR::Construct(
                RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl());

            mpAnmObjVisOR->Bind(mpScnMdlSimple->GetResMdl());
            mpScnMdlSimple->SetAnmObj(mpAnmObjVisOR);
        } else {
            mpAnmObjVisOR = NULL;
        }
        break;
    }

    case Anm_Shp: {
        // TODO(kiwi) Why only one? SetBlendWeight could write way out of bounds
        mpShpBlendInfo = new ShpBlendInfo[1];

        mpShpBlendInfo[0].pAnmObj = nw4r::g3d::AnmObjShpBlend::Construct(
            RPGrpModel::GetAllocator(), NULL, mpScnMdlSimple->GetResMdl(), 8);

        mpShpBlendInfo[0].pAnmObj->Bind(mpScnMdlSimple->GetResMdl());
        mpScnMdlSimple->SetAnmObj(mpShpBlendInfo[0].pAnmObj);

        for (int i = 0; i < 8; i++) {
            mpShpBlendInfo[0].toAnmIdx[i] = -1;
        }
        break;
    }

    default: {
        break;
    }
    }
}

void RPGrpModelAnmG3D::Regist(Anm anm, AnmIdx idx, RPGrpHandle handle) {
    InternalRegist(anm, idx);

    switch (anm) {
    case Anm_Chr: {
        const nw4r::g3d::ResAnmChr chr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmChr>(handle);

        RegistAnmChr(idx, chr);
        break;
    }

    case Anm_Clr: {
        const nw4r::g3d::ResAnmClr clr =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmClr>(handle);

        RegistAnmClr(idx, clr);
        break;
    }

    case Anm_TexPat: {
        const nw4r::g3d::ResAnmTexPat pat =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexPat>(handle);

        RegistAnmTexPat(idx, pat);
        break;
    }

    case Anm_TexSrt: {
        const nw4r::g3d::ResAnmTexSrt srt =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmTexSrt>(handle);

        RegistAnmTexSrt(idx, srt);
        break;
    }

    case Anm_Vis: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_Shp: {
        const nw4r::g3d::ResAnmShp shp =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmShp>(handle);

        RegistAnmShp(idx, shp);
        break;
    }

    case Anm_6: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle);

        RegistAnmVis(idx, vis);
        break;
    }

    case Anm_7: {
        const nw4r::g3d::ResAnmVis vis =
            RPGrpModelResManager::GetCurrent()
                ->GetData<RPGrpModelResManager::Type_ResAnmVis>(handle);

        RegistAnmVis(idx, vis);
        break;
    }

    default: {
        break;
    }
    }
}

bool RPGrpModelAnmG3D::Start(Anm anm, AnmIdx idx, f32 frame) {
    if (anm != Anm_Chr && anm != Anm_Shp) {
        mpAnmFlags[anm][idx] |= AnmFlag_PlayingG3D;

        if (GetAnmNum(anm) >= 2) {
            switch (anm) {
            case Anm_Clr: {
                u8 g3dIdx = 0;
                mpAnmObjMatClrOverride->DetachAll();

                for (int i = 0; i < GetAnmNum(Anm_Clr); i++) {
                    if (!IsPlayingG3D(Anm_Clr, i)) {
                        continue;
                    }

                    mpAnmObjMatClrOverride->Attach(g3dIdx,
                                                   mppAnmObjMatClrRes[i]);
                    mpToIndexG3D[Anm_Clr][idx] = g3dIdx++;
                }
                break;
            }

            case Anm_TexPat: {
                u8 g3dIdx = 0;
                mpAnmObjTexPatOverride->DetachAll();

                for (int i = 0; i < GetAnmNum(Anm_TexPat); i++) {
                    if (!IsPlayingG3D(Anm_TexPat, i)) {
                        continue;
                    }

                    mpAnmObjTexPatOverride->Attach(g3dIdx,
                                                   mppAnmObjTexPatRes[i]);
                    mpToIndexG3D[Anm_TexPat][idx] = g3dIdx++;
                }
                break;
            }

            case Anm_TexSrt: {
                u8 g3dIdx = 0;
                mpAnmObjTexSrtOverride->DetachAll();

                for (int i = 0; i < GetAnmNum(Anm_TexSrt); i++) {
                    if (!IsPlayingG3D(Anm_TexSrt, i)) {
                        continue;
                    }

                    mpAnmObjTexSrtOverride->Attach(g3dIdx,
                                                   mppAnmObjTexSrtRes[i]);
                    mpToIndexG3D[Anm_TexSrt][idx] = g3dIdx++;
                }
                break;
            }

            case Anm_Vis: {
                u8 g3dIdx = 0;
                mpAnmObjVisOR->DetachAll();

                for (int i = 0; i < GetAnmNum(Anm_Vis); i++) {
                    if (!IsPlayingG3D(Anm_Vis, i)) {
                        continue;
                    }

                    mpAnmObjVisOR->Attach(g3dIdx, mppAnmObjVisRes[i]);
                    mpToIndexG3D[Anm_Vis][idx] = g3dIdx++;
                }
                break;
            }

            default: {
                break;
            }
            }

        } else if (anm != Anm_Chr && anm != Anm_Shp) {
            nw4r::g3d::AnmObj* pAnmObj = InternalGetAnmObj(anm, idx);

            if (pAnmObj != mpScnMdlSimple->GetAnmObj(TO_G3D_TYPE[anm])) {
                mpScnMdlSimple->RemoveAnmObj(TO_G3D_TYPE[anm]);
                mpScnMdlSimple->SetAnmObj(pAnmObj);
            }
        }
    }

    return RPGrpModelAnm::Start(anm, idx, frame);
}

bool RPGrpModelAnmG3D::Cancel(Anm anm, AnmIdx idx) {
    bool success = RPGrpModelAnm::Cancel(anm, idx);

    if (!success) {
        return false;
    }

    if (anm == Anm_Chr || anm == Anm_Shp) {
        s8 blendIdx = GetBlendIndex(anm, idx, 0);

        if (blendIdx != -1) {
            RemoveBlendAnm(anm, blendIdx, 0);
        }

    } else if (IsPlayingG3D(anm, idx)) {
        mpAnmFlags[anm][idx] &= ~AnmFlag_PlayingG3D;

        if (GetAnmNum(anm) >= 2) {
            switch (anm) {
            case Anm_Clr: {
                mpAnmObjMatClrOverride->Detach(mpToIndexG3D[Anm_Clr][idx]);
                break;
            }

            case Anm_TexPat: {
                mpAnmObjTexPatOverride->Detach(mpToIndexG3D[Anm_TexPat][idx]);
                break;
            }

            case Anm_TexSrt: {
                mpAnmObjTexSrtOverride->Detach(mpToIndexG3D[Anm_TexSrt][idx]);
                break;
            }

            case Anm_Vis: {
                mpAnmObjVisOR->Detach(mpToIndexG3D[Anm_Vis][idx]);
                break;
            }

            default: {
                break;
            }
            }

            mpToIndexG3D[anm][idx] = -1;

        } else {
            // @bug Messed up the expression somehow?
#if defined(BUG_FIX)
            success = mpScnMdlSimple->RemoveAnmObj(TO_G3D_TYPE[anm]) != NULL;
#else
            mpScnMdlSimple->RemoveAnmObj(TO_G3D_TYPE[anm]);
            success = success != 0;
#endif
        }

    } else {
        success = false;
    }

    return success;
}

s16 RPGrpModelAnmG3D::SetBlendAnm(Anm anm, u8 arg1, AnmIdx idx) {
    s16 uVar1 = RPGrpModelAnm::SetBlendAnm(anm, arg1, idx);

    if (uVar1 != idx) {
        switch (anm) {
        case Anm_Chr: {
            mpChrBlendInfo[0].pAnmObj->Attach(arg1, mppAnmObjChrRes[idx]);
            mpChrBlendInfo[0].toAnmIdx[arg1] = idx;

            if (IsEnableChrAnm() &&
                mpChrBlendInfo[0].pAnmObj->GetParent() == NULL) {

                mpScnMdlSimple->SetAnmObj(mpChrBlendInfo[0].pAnmObj);
            }
            break;
        }

        case Anm_Shp: {
            mpShpBlendInfo[0].pAnmObj->Attach(arg1, mppAnmObjShpRes[idx]);
            mpShpBlendInfo[0].toAnmIdx[arg1] = idx;
            break;
        }

        default: {
            break;
        }
        }
    }

    return uVar1;
}

void RPGrpModelAnmG3D::SetBlendWeight(Anm anm, u8 g3dIndex, f32 weight,
                                      u8 blendIdx) {
    switch (anm) {
    case Anm_Chr: {
        mpChrBlendInfo[blendIdx].pAnmObj->SetWeight(g3dIndex, weight);
        break;
    }

    case Anm_Shp: {
        mpShpBlendInfo[blendIdx].pAnmObj->SetWeight(g3dIndex, weight);
        break;
    }

    default: {
        break;
    }
    }
}

s16 RPGrpModelAnmG3D::RemoveBlendAnm(Anm anm, u8 arg1, u8 arg2) {
    s16 idx = GetBlendAnm(anm, arg1, arg2);

    if (idx != -1) {
        mpAnmFlags[anm][static_cast<AnmIdx>(idx)] &= ~AnmFlag_PlayingG3D;

        switch (anm) {
        case Anm_Chr: {
            mpChrBlendInfo[arg2].pAnmObj->Detach(arg1);
            mpChrBlendInfo[arg2].toAnmIdx[arg1] = -1;
            break;
        }

        case Anm_Shp: {
            mpShpBlendInfo[arg2].pAnmObj->Detach(arg1);
            mpShpBlendInfo[arg2].toAnmIdx[arg1] = -1;
            break;
        }

        default: {
            break;
        }
        }
    }

    return idx;
}

s16 RPGrpModelAnmG3D::GetBlendAnm(Anm anm, u8 arg1, u8 arg2) {
    switch (anm) {
    case Anm_Chr: {
        return mpChrBlendInfo[arg2].toAnmIdx[arg1];
    }

    case Anm_Shp: {
        return mpShpBlendInfo[arg2].toAnmIdx[arg1];
    }

    default: {
        return -1;
    }
    }
}

f32 RPGrpModelAnmG3D::GetBlendWeight(Anm anm, u8 arg1, u8 arg2) {
    switch (anm) {
    case Anm_Chr: {
        return mpChrBlendInfo[arg2].pAnmObj->GetWeight(arg1);
    }

    case Anm_Shp: {
        return mpShpBlendInfo[arg2].pAnmObj->GetWeight(arg1);
    }

    default: {
        return 0.0f;
    }
    }
}

// clang-format off
static nw4r::g3d::AnmObjChr::BindOption TO_BIND_OPTION[RPGrpModelAnm::BindType_Max] = {
    nw4r::g3d::AnmObjChr::BIND_ONE,     // BindType_One
    nw4r::g3d::AnmObjChr::BIND_PARTIAL, // BindType_Partial
};
// clang-format on

void RPGrpModelAnmG3D::ReBindChrAnmNode(u16 arg0, u16 arg1, BindType type) {
    mppAnmObjChrRes[arg0]->Release();
    mppAnmObjChrRes[arg0]->Bind(mpScnMdlSimple->GetResMdl(), arg1,
                                TO_BIND_OPTION[type]);
}

void RPGrpModelAnmG3D::ReleaseChrAnmNode(u16 arg0, u16 arg1, BindType type) {
    mppAnmObjChrRes[arg0]->Release(mpScnMdlSimple->GetResMdl(), arg1,
                                   TO_BIND_OPTION[type]);
}

void RPGrpModelAnmG3D::UpdateFrame() {
    for (int i = 0; i < Anm_Max; i++) {
        if (i == Anm_Chr && IsBlending(Anm_Chr) && IsEnableChrAnm()) {
            s16 idx = GetBlendAnm(Anm_Chr, 0, 0);
            f32 rate = GetUpdateRate(Anm_Chr, idx);

            rate = unk60 - nw4r::math::FAbs(rate);
            unk60 = rate;

            if (rate <= 0.0f) {
                unk64 = 0.0f;
                unk60 = 0.0f;

                SetBlendWeight(Anm_Chr, 0, 1.0f, 0);
                RemoveBlendAnm(Anm_Chr, 1, 0);
            } else {
                f32 weight = rate / unk64;
                SetBlendWeight(Anm_Chr, 0, 1.0f - weight, 0);
                SetBlendWeight(Anm_Chr, 1, weight, 0);
            }
        }
    }
}

void RPGrpModelAnmG3D::InternalCalc() {}

void RPGrpModelAnmG3D::SetEnableQuaternionBlend(bool enable) {
    RPGrpModelAnm::SetEnableQuaternionBlend(enable);

    mpChrBlendInfo[0].pAnmObj->SetAnmFlag(
        nw4r::g3d::AnmObj::FLAG_USE_QUATERNION_ROTATION_BLEND,
        IsEnableQuaternionBlend());
}

void RPGrpModelAnmG3D::SetEnableChrAnm(bool enable) {
    RPGrpModelAnm::SetEnableChrAnm(enable);

    if (IsEnableChrAnm()) {
        if (mpChrBlendInfo[0].pAnmObj->GetParent() == NULL &&
            mpChrBlendInfo[0].pAnmObj->TestAnmFlag(
                nw4r::g3d::AnmObj::FLAG_ANM_BOUND)) {

            mpScnMdlSimple->SetAnmObj(mpChrBlendInfo[0].pAnmObj);
        }
    } else if (mpChrBlendInfo[0].pAnmObj->GetParent() != NULL) {
        mpScnMdlSimple->RemoveAnmObj(mpChrBlendInfo[0].pAnmObj);
    }
}

void RPGrpModelAnmG3D::VF_0x70(UNKTYPE) {}

void RPGrpModelAnmG3D::RegistAnmChr(AnmIdx idx,
                                    const nw4r::g3d::ResAnmChr chr) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjChrRes[idx] = nw4r::g3d::AnmObjChrRes::Construct(
        RPGrpModel::GetAllocator(), &size, chr, mdl, false);

    mppAnmObjChrRes[idx]->Bind(mdl);
}

void RPGrpModelAnmG3D::RegistAnmClr(AnmIdx idx,
                                    const nw4r::g3d::ResAnmClr clr) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjMatClrRes[idx] = nw4r::g3d::AnmObjMatClrRes::Construct(
        RPGrpModel::GetAllocator(), &size, clr, mdl, false);

    mppAnmObjMatClrRes[idx]->Bind(mdl);
}

void RPGrpModelAnmG3D::RegistAnmTexPat(AnmIdx idx,
                                       const nw4r::g3d::ResAnmTexPat pat) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjTexPatRes[idx] = nw4r::g3d::AnmObjTexPatRes::Construct(
        RPGrpModel::GetAllocator(), &size, pat, mdl, false);

    mppAnmObjTexPatRes[idx]->Bind(mdl);
}

void RPGrpModelAnmG3D::RegistAnmTexSrt(AnmIdx idx,
                                       const nw4r::g3d::ResAnmTexSrt srt) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjTexSrtRes[idx] = nw4r::g3d::AnmObjTexSrtRes::Construct(
        RPGrpModel::GetAllocator(), &size, srt, mdl, false);

    mppAnmObjTexSrtRes[idx]->Bind(mdl);
}

void RPGrpModelAnmG3D::RegistAnmVis(AnmIdx idx,
                                    const nw4r::g3d::ResAnmVis vis) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjVisRes[idx] = nw4r::g3d::AnmObjVisRes::Construct(
        RPGrpModel::GetAllocator(), &size, vis, mdl);

    mppAnmObjVisRes[idx]->Bind(mdl);
}

void RPGrpModelAnmG3D::RegistAnmShp(AnmIdx idx,
                                    const nw4r::g3d::ResAnmShp chr) {
    const nw4r::g3d::ResMdl mdl = mpScnMdlSimple->GetResMdl();

    u32 size;
    mppAnmObjShpRes[idx] = nw4r::g3d::AnmObjShpRes::Construct(
        RPGrpModel::GetAllocator(), &size, chr, mdl, false);

    mppAnmObjShpRes[idx]->Bind(mdl);
}

f32 RPGrpModelAnmG3D::VF_0x44(UNKTYPE) {
    return 0.0f;
}

f32 RPGrpModelAnmG3D::VF_0x48(UNKTYPE) {
    return 0.0f;
}

int RPGrpModelAnmG3D::GetNumFrame(Anm anm, AnmIdx idx) const {
    switch (anm) {
    case Anm_Chr: {
        return mppAnmObjChrRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_Clr: {
        return mppAnmObjMatClrRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_TexPat: {
        return mppAnmObjTexPatRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_TexSrt: {
        return mppAnmObjTexSrtRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_Vis: {
        return mppAnmObjVisRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_Shp: {
        return mppAnmObjShpRes[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_6: {
        return unk88[idx]->GetResAnm().GetNumFrame();
    }

    case Anm_7: {
        return unk8C[idx]->GetResAnm().GetNumFrame();
    }

    default: {
        return 0;
    }
    }
}

RPGrpModelAnmG3D::AnmPlayPolicy
RPGrpModelAnmG3D::GetAnmPlayPolicy(Anm anm, AnmIdx idx) const {
    nw4r::g3d::AnmPolicy policy;

    switch (anm) {
    case Anm_Chr: {
        policy = mppAnmObjChrRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_Clr: {
        policy = mppAnmObjMatClrRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_TexPat: {
        policy = mppAnmObjTexPatRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_TexSrt: {
        policy = mppAnmObjTexSrtRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_Vis: {
        policy = mppAnmObjVisRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_Shp: {
        policy = mppAnmObjShpRes[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_6: {
        policy = unk88[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    case Anm_7: {
        policy = unk8C[idx]->GetResAnm().GetAnmPolicy();
        break;
    }

    // @bug Policy variable is possibly uninitialized
#if defined(BUG_FIX)
    default: {
        policy = nw4r::g3d::ANM_POLICY_ONETIME;
        break;
    }
#endif
    }

    return FROM_G3D_POLICY[policy];
}

void RPGrpModelAnmG3D::SetFrame(Anm anm, AnmIdx idx, f32 frame) {
    GetAnmObj(anm, idx)->SetFrame(frame);
}

f32 RPGrpModelAnmG3D::GetFrame(Anm anm, AnmIdx idx) const {
    return GetAnmObj(anm, idx)->GetFrame();
}

void RPGrpModelAnmG3D::SetUpdateRate(Anm anm, AnmIdx idx, f32 rate) {
    GetAnmObj(anm, idx)->SetUpdateRate(rate);
}

nw4r::g3d::AnmObj* RPGrpModelAnmG3D::GetAnmObj(Anm anm, AnmIdx idx) const {
    return InternalGetAnmObj(anm, idx);
}

f32 RPGrpModelAnmG3D::GetUpdateRate(Anm anm, AnmIdx idx) const {
    return GetAnmObj(anm, idx)->GetUpdateRate();
}
