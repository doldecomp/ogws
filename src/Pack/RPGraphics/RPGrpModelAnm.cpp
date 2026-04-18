#include <Pack/RPGraphics.h>

RPGrpModelAnm::RPGrpModelAnm()
    : mFlags(0),
      unk54(1),
      mpBlendIndices(NULL),
      unk5C(0),
      unk60(0.0f),
      unk64(0.0f) {}

void RPGrpModelAnm::Configure() {
    for (int i = 0; i < Anm_Max; i++) {
        mAnmNum[i] = 0;
        mPrevPlayIndex[i] = -1;
        mPlayIndex[i] = -1;
        mpAnmFlags[i] = 0;
    }
}

void RPGrpModelAnm::CreateBuffer(Anm anm, u16 num) {
    nw4r::g3d::AnmObj** ppAnmObjs = new nw4r::g3d::AnmObj*[num];
    mpAnmFlags[anm] = new u8[num];

    for (int i = 0; i < num; i++) {
        ppAnmObjs[i] = NULL;
        mpAnmFlags[anm][i] = 0;
    }

    mAnmNum[anm] = num;
    SetAnmObj(anm, ppAnmObjs);

    if (anm == Anm_Chr) {
        mpBlendIndices = new u8[num];

        for (int i = 0; i < num; i++) {
            mpBlendIndices[i] = 0;
        }
    }
}

void RPGrpModelAnm::Calc() {
    InternalCalc();
}

bool RPGrpModelAnm::Start(Anm anm, u16 idx, f32 frame) {
    mPrevPlayIndex[anm] = mPlayIndex[anm];
    mPlayIndex[anm] = idx;

    mpAnmFlags[anm][idx] |= AnmFlag_Playing;

    SetFrame(anm, idx, frame);
    SetUpdateRate(anm, idx, 1.0f);

    unk64 = 0.0f;
    unk60 = 0.0f;

    if (anm == Anm_Chr) {
        u8 blend = mpBlendIndices[idx];

        SetBlendAnm(anm, 0, idx);
        SetBlendWeight(anm, 0, 1.0f, blend);
    } else if (anm == Anm_Shp) {
        SetBlendAnm(anm, 0, idx);
        SetBlendWeight(anm, 0, 1.0f, 0);
    }

    return true;
}

bool RPGrpModelAnm::StartNoBlend(Anm anm, u16 idx, f32 frame) {
    bool success = Start(anm, idx, frame);

    if (anm == Anm_Chr) {
        RemoveBlendAnm(anm, 1, mpBlendIndices[idx]);
    }

    return success;
}

bool RPGrpModelAnm::StartBlend(Anm anm, u16 idx, f32 weight, f32 frame) {
    StartNoBlend(anm, idx, frame);

    s16 sVar1 = mPrevPlayIndex[anm];

    if (idx != sVar1) {
        unk64 = weight;
        unk60 = weight;

        switch (anm) {
        case Anm_Chr: {
            if (weight > 0.0f && sVar1 != -1) {
                SetBlendAnm(anm, 1, sVar1);
                SetBlendWeight(anm, 1, 1.0f, 0);
            }

            break;
        }

        default: {
            break;
        }
        }

        return true;
    }

    return false;
}

bool RPGrpModelAnm::Cancel(Anm anm, u16 idx) {
    bool success = mpAnmFlags[anm][idx] & AnmFlag_Playing;
    mpAnmFlags[anm][idx] &= ~AnmFlag_Playing;
    return success;
}

s16 RPGrpModelAnm::SetBlendAnm(Anm anm, u8 arg1, u16 idx) {
    s16 uVar1 = GetBlendAnm(anm, arg1, 0);

    if (uVar1 != idx) {
        s8 blendIdx = GetBlendIndex(anm, idx, 0);

        if (blendIdx != -1) {
            RemoveBlendAnm(anm, blendIdx, 0);
        }

        if (uVar1 != -1) {
            RemoveBlendAnm(anm, arg1, 0);
        }

        mpAnmFlags[anm][idx] |= 0x1;
    }

    return uVar1;
}

s8 RPGrpModelAnm::GetBlendIndex(Anm anm, AnmIdx idx, u8 blend) {
    for (int i = 0; i < 8; i++) {
        s16 blendAnm = GetBlendAnm(anm, i, blend);

        if (idx == blendAnm) {
            return i;
        }
    }

    return -1;
}

void RPGrpModelAnm::InternalRegist(Anm anm, u16 idx) {
    mpAnmFlags[anm][idx] |= AnmFlag_Regist;
}
