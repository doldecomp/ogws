#include <nw4r/lyt.h>

#include <cstring>

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
static const GXColorS10 DefaultBlackColor = {0, 0, 0, 0};
static const GXColorS10 DefaultWhiteColor = {255, 255, 255, 255};

namespace {

using namespace nw4r;
using namespace nw4r::lyt;

/******************************************************************************
 * GXColorS10
 ******************************************************************************/
bool operator==(const GXColorS10& rLhs, const GXColorS10& rRhs) {
    return rLhs.r == rRhs.r && rLhs.g == rRhs.g && rLhs.b == rRhs.b &&
           rLhs.a == rRhs.a;
}
bool operator!=(const GXColorS10& rLhs, const GXColorS10& rRhs) {
    return !(rLhs == rRhs);
}

/******************************************************************************
 * Texture matrices
 ******************************************************************************/
void CalcTextureMtx(math::MTX34* pMtx, const TexSRT& rSrt) {
    math::VEC2 center(0.5f, 0.5f);

    f32 cr = math::CosDeg(rSrt.rotate);
    f32 sr = math::SinDeg(rSrt.rotate);

    f32 a0, a1;

    a0 = cr * rSrt.scale.x;
    a1 = -sr * rSrt.scale.y;

    pMtx->_00 = a0;
    pMtx->_01 = a1;
    pMtx->_02 = 0.0f;
    pMtx->_03 = rSrt.translate.x + center.x + a0 * -center.x + a1 * -center.y;

    a0 = sr * rSrt.scale.x;
    a1 = cr * rSrt.scale.y;

    pMtx->_10 = a0;
    pMtx->_11 = a1;
    pMtx->_12 = 0.0f;
    pMtx->_13 = rSrt.translate.y + center.y + a0 * -center.x + a1 * -center.y;

    pMtx->_20 = 0.0f;
    pMtx->_21 = 0.0f;
    pMtx->_22 = 1.0f;
    pMtx->_23 = 0.0f;
}

void CalcIndTexMtx(f32 mtx[2][3], const TexSRT& rSrt) {
    f32 cr = math::CosDeg(rSrt.rotate);
    f32 sr = math::SinDeg(rSrt.rotate);

    mtx[0][0] = cr * rSrt.scale.x;
    mtx[0][1] = -sr * rSrt.scale.y;
    mtx[0][2] = rSrt.translate.x;

    mtx[1][0] = sr * rSrt.scale.x;
    mtx[1][1] = cr * rSrt.scale.y;
    mtx[1][2] = rSrt.translate.y;
}

inline u32 GetTexMtxIdx(u32 mtx) {
    return (mtx - GX_TEXMTX0) / 3;
}
inline u32 GetTexMtx(u32 idx) {
    return GX_TEXMTX0 + idx * 3;
}

/******************************************************************************
 * Color components
 ******************************************************************************/
void SetColorComponentValue(ut::Color* pColor, u32 idx, s16 value) {
    u8 bvalue = ut::Min<s16>(ut::Max<s16>(value, 0), 255);

    switch (idx % 4) {
    case 0: {
        pColor->r = bvalue;
        break;
    }

    case 1: {
        pColor->g = bvalue;
        break;
    }

    case 2: {
        pColor->b = bvalue;
        break;
    }

    case 3: {
        pColor->a = bvalue;
        break;
    }

    default: {
        break;
    }
    }
}

/******************************************************************************
 * SetIndTexMtx
 ******************************************************************************/
void SetIndTexMtx(GXIndTexMtxID id, const f32 mtx[2][3]) {
    f32 m00, m01, m02, m10, m11, m12;
    f32 a00, a01, a02, a10, a11, a12;

    s8 scaleExp = 0;

    m00 = mtx[0][0];
    m01 = mtx[0][1];
    m02 = mtx[0][2];
    m10 = mtx[1][0];
    m11 = mtx[1][1];
    m12 = mtx[1][2];

    a00 = math::FAbs(m00);
    a01 = math::FAbs(m01);
    a02 = math::FAbs(m02);
    a10 = math::FAbs(m10);
    a11 = math::FAbs(m11);
    a12 = math::FAbs(m12);

    if (a00 >= 1.0f || a01 >= 1.0f || a02 >= 1.0f || a10 >= 1.0f ||
        a11 >= 1.0f || a12 >= 1.0f) {

        do {
            if (scaleExp >= 46) {
                break;
            }

            scaleExp++;

            m00 /= 2.0f;
            m01 /= 2.0f;
            m02 /= 2.0f;
            m10 /= 2.0f;
            m11 /= 2.0f;
            m12 /= 2.0f;

            a00 /= 2.0f;
            a01 /= 2.0f;
            a02 /= 2.0f;
            a10 /= 2.0f;
            a11 /= 2.0f;
            a12 /= 2.0f;
        } while (a00 >= 1.0f || a01 >= 1.0f || a02 >= 1.0f || a10 >= 1.0f ||
                 a11 >= 1.0f || a12 >= 1.0f);

    } else if (a00 < 0.5f && a01 < 0.5f && a02 < 0.5f && a10 < 0.5f &&
               a11 < 0.5f && a12 < 0.5f) {
        do {
            scaleExp--;

            m00 *= 2.0f;
            m01 *= 2.0f;
            m02 *= 2.0f;
            m10 *= 2.0f;
            m11 *= 2.0f;
            m12 *= 2.0f;

            a00 *= 2.0f;
            a01 *= 2.0f;
            a02 *= 2.0f;
            a10 *= 2.0f;
            a11 *= 2.0f;
            a12 *= 2.0f;

        } while (a00 < 0.5f && a01 < 0.5f && a02 < 0.5f && a10 < 0.5f &&
                 a11 < 0.5f && a12 < 0.5f && scaleExp > -17);
    }

    f32 outMtx[2][3] = {m00, m01, m02, m10, m11, m12};
    GXSetIndTexMtx(id, outMtx, scaleExp);
}

/******************************************************************************
 * Texture S/R/T
 ******************************************************************************/
void InitTexSRT(TexSRT* pTexSrt, u32 num) {
    for (u32 i = 0; i < num; i++) {
        pTexSrt[i].translate = math::VEC2(0.0f, 0.0f);
        pTexSrt[i].rotate = 0.0f;
        pTexSrt[i].scale = math::VEC2(1.0f, 1.0f);
    }
}

/******************************************************************************
 * GX memory offsets
 ******************************************************************************/
u32 CalcOffsetTexSRTAry(const detail::BitGXNums& rNums) {
    return rNums.texMap * ROUND_UP(sizeof(TexMap), 4);
}

u32 CalcOffsetTexCoordGenAry(const detail::BitGXNums& rNums) {
    return rNums.texSRT * ROUND_UP(sizeof(TexSRT), 4) +
           CalcOffsetTexSRTAry(rNums);
}

u32 CalcOffsetChanCtrlAry(const detail::BitGXNums& rNums) {
    return rNums.texCoordGen * ROUND_UP(sizeof(TexCoordGen), 4) +
           CalcOffsetTexCoordGenAry(rNums);
}

u32 CalcOffsetMatColAry(const detail::BitGXNums& rNums) {
    return rNums.chanCtrl * ROUND_UP(sizeof(ChanCtrl), 4) +
           CalcOffsetChanCtrlAry(rNums);
}

u32 CalcOffsetTevSwapAry(const detail::BitGXNums& rNums) {
    return rNums.matCol * ROUND_UP(sizeof(ut::Color), 4) +
           CalcOffsetMatColAry(rNums);
}

u32 CalcOffsetGetAlphaCompare(const detail::BitGXNums& rNums) {
    return rNums.tevSwap * ROUND_UP(sizeof(TevSwapMode), 4) +
           CalcOffsetTevSwapAry(rNums);
}

u32 CalcOffsetBlendMode(const detail::BitGXNums& rNums) {
    return rNums.alpComp * ROUND_UP(sizeof(AlphaCompare), 4) +
           CalcOffsetGetAlphaCompare(rNums);
}

u32 CalcOffsetIndirectStageAry(const detail::BitGXNums& rNums) {
    return rNums.blendMode * ROUND_UP(sizeof(BlendMode), 4) +
           CalcOffsetBlendMode(rNums);
}

u32 CalcOffsetIndTexSRTAry(const detail::BitGXNums& rNums) {
    return rNums.indStage * ROUND_UP(sizeof(IndirectStage), 4) +
           CalcOffsetIndirectStageAry(rNums);
}

u32 CalcOffsetTevStageAry(const detail::BitGXNums& rNums) {
    return rNums.indSRT * ROUND_UP(sizeof(TexSRT), 4) +
           CalcOffsetIndTexSRTAry(rNums);
}

} // namespace

namespace nw4r {
namespace lyt {

/******************************************************************************
 *
 * Material
 *
 ******************************************************************************/
Material::Material(const res::Material* pRes, const ResBlockSet& rBlockSet) {
    Init();
    SetName(pRes->name);

    for (int i = 0; i < TEVCOLOR_MAX; i++) {
        mTevCols[i] = pRes->tevCols[i];
    }

    for (int i = 0; i < GX_MAX_KCOLOR; i++) {
        mTevKCols[i] = pRes->tevKCols[i];
    }

    u32 offset = sizeof(res::Material);

    // clang-format off
    const res::TexMap* const pResTexMap = detail::ConvertOffsToPtr<res::TexMap>(pRes, offset);
    offset += pRes->resNum.GetTexMapNum() * sizeof(res::TexMap);

    const TexSRT* const pResTexSrt = detail::ConvertOffsToPtr<TexSRT>(pRes, offset);
    offset += pRes->resNum.GetTexSRTNum() * sizeof(TexSRT);

    const TexCoordGen* const pResTexCoordGen = detail::ConvertOffsToPtr<TexCoordGen>(pRes, offset);
    offset += pRes->resNum.GetTexCoordGenNum() * sizeof(TexCoordGen);

    u8 texMapNum      = ut::Min<u8>(pRes->resNum.GetTexMapNum(), GX_MAX_TEXMAP);
    u8 texSrtNum      = ut::Min<u8>(pRes->resNum.GetTexSRTNum(), MAX_TEX_SRT);
    u8 texCoordGenNum = ut::Min<u8>(pRes->resNum.GetTexCoordGenNum(), GX_MAX_TEXCOORD);

    bool allocChanCtrl  = pRes->resNum.GetChanCtrlNum() != 0;
    bool allocMatCol    = pRes->resNum.GetMatColNum() != 0;
    bool allocTevSwap   = pRes->resNum.HasTevSwapTable();
    bool allocAlphaComp = pRes->resNum.HasAlphaCompare();
    bool allocBlendMode = pRes->resNum.HasBlendMode();

    u8 indTexSrtNum = ut::Min<u8>(pRes->resNum.GetIndTexSRTNum(), MAX_IND_SRT);
    u8 indStageNum  = ut::Min<u8>(pRes->resNum.GetIndTexStageNum(), GX_MAX_INDTEXSTAGE);
    u8 tevStageNum  = ut::Min<u8>(pRes->resNum.GetTevStageNum(), GX_MAX_TEVSTAGE);
    // clang-format on

    ReserveGXMem(texMapNum, texSrtNum, texCoordGenNum, tevStageNum,
                 allocTevSwap, indStageNum, indTexSrtNum, allocChanCtrl,
                 allocMatCol, allocAlphaComp, allocBlendMode);

    if (mpGXMem != NULL) {
        SetTextureNum(texMapNum);

        if (texMapNum > 0) {
            const res::Texture* const pTexture =
                detail::ConvertOffsToPtr<res::Texture>(
                    rBlockSet.pTextureList, sizeof(res::TextureList));

            TexMap* const pTexMap = GetTexMapAry();

            u8 num = 0;
            for (u8 i = 0; i < mGXMemNum.texMap; num++, i++) {
                const char* const pName = detail::ConvertOffsToPtr<char>(
                    pTexture, pTexture[pResTexMap[i].texIdx].nameStrOffset);

                void* const pTexPalette = rBlockSet.pResAccessor->GetResource(
                    ArcResourceAccessor::RES_TYPE_TEXTURE, pName, NULL);

                TexMap texMap(static_cast<TPLPalette*>(pTexPalette), 0);
                SetTextureNoWrap(num, texMap);

                pTexMap[num].SetWrapMode(
                    static_cast<GXTexWrapMode>(pResTexMap[i].wrapS),
                    static_cast<GXTexWrapMode>(pResTexMap[i].wrapT));
            }
        }

        TexSRT* pTexSrt = GetTexSRTAry();
        for (int i = 0; i < texSrtNum; i++) {
            pTexSrt[i].translate = pResTexSrt[i].translate;
            pTexSrt[i].rotate = pResTexSrt[i].rotate;
            pTexSrt[i].scale = pResTexSrt[i].scale;
        }

        TexCoordGen* pTexCoordGen = GetTexCoordGenAry();
        SetTexCoordGenNum(texCoordGenNum);
        for (int i = 0; i < mGXMemNum.texCoordGen; i++) {
            pTexCoordGen[i] = pResTexCoordGen[i];
        }

        if (allocChanCtrl) {
            const ChanCtrl* const pResChanCtrl =
                detail::ConvertOffsToPtr<ChanCtrl>(pRes, offset);

            *GetChanCtrlAry() = *pResChanCtrl;
            offset += sizeof(ChanCtrl);
        }

        if (allocMatCol) {
            const ut::Color* const pResMatCol =
                detail::ConvertOffsToPtr<ut::Color>(pRes, offset);

            *GetMatColAry() = *pResMatCol;
            offset += sizeof(ut::Color);
        }

        if (allocTevSwap) {
            const TevSwapMode* const pResTevSwap =
                detail::ConvertOffsToPtr<TevSwapMode>(pRes, offset);

            TevSwapMode* const pTevSwap = GetTevSwapAry();
            for (int i = 0; i < GX_MAX_TEVSWAP; i++) {
                pTevSwap[i] = pResTevSwap[i];
            }

            offset += GX_MAX_TEVSWAP * sizeof(TevSwapMode);
        }

        if (indTexSrtNum != 0) {
            TexSRT* const pIndTexSrt = GetIndTexSRTAry();

            const TexSRT* const pResIndTexSrt =
                detail::ConvertOffsToPtr<TexSRT>(pRes, offset);

            for (int i = 0; i < indTexSrtNum; i++) {
                pIndTexSrt[i] = pResIndTexSrt[i];
            }
        }
        offset += pRes->resNum.GetIndTexSRTNum() * sizeof(TexSRT);

        if (indStageNum != 0) {
            SetIndStageNum(indStageNum);
            IndirectStage* const pIndStage = GetIndirectStageAry();

            const IndirectStage* const pResIndStage =
                detail::ConvertOffsToPtr<IndirectStage>(pRes, offset);

            for (int i = 0; i < indStageNum; i++) {
                pIndStage[i] = pResIndStage[i];
            }
        }
        offset += pRes->resNum.GetIndTexStageNum() * sizeof(IndirectStage);

        if (tevStageNum != 0) {
            SetTevStageNum(tevStageNum);
            TevStage* const pTevStage = GetTevStageAry();

            const TevStage* const pResTevStage =
                detail::ConvertOffsToPtr<TevStage>(pRes, offset);

            for (int i = 0; i < tevStageNum; i++) {
                pTevStage[i] = pResTevStage[i];
            }
        }
        offset += pRes->resNum.GetTevStageNum() * sizeof(TevStage);

        if (allocAlphaComp) {
            const AlphaCompare* const pResAlphaCompare =
                detail::ConvertOffsToPtr<AlphaCompare>(pRes, offset);

            *GetAlphaComparePtr() = *pResAlphaCompare;
            offset += sizeof(AlphaCompare);
        }

        if (allocBlendMode) {
            const BlendMode* const pResBlendMode =
                detail::ConvertOffsToPtr<BlendMode>(pRes, offset);

            *GetBlendModePtr() = *pResBlendMode;
        }
    }
}

void Material::Init() {
    mTevCols[TEVCOLOR_REG0] = DefaultBlackColor;
    mTevCols[TEVCOLOR_REG1] = DefaultWhiteColor;
    mTevCols[TEVCOLOR_REG2] = DefaultWhiteColor;

    InitBitGXNums(&mGXMemCap);
    InitBitGXNums(&mGXMemNum);

    mbUserAllocated = false;
    mpGXMem = NULL;
}

Material::~Material() {
    UnbindAllAnimation();

    if (mpGXMem != NULL) {
        Layout::FreeMemory(mpGXMem);
        mpGXMem = NULL;
    }
}

void Material::InitBitGXNums(detail::BitGXNums* pNums) {
    pNums->texMap = 0;
    pNums->texSRT = 0;
    pNums->texCoordGen = 0;
    pNums->indSRT = 0;
    pNums->indStage = 0;
    pNums->tevSwap = FALSE;
    pNums->tevStage = 0;
    pNums->chanCtrl = FALSE;
    pNums->matCol = FALSE;
    pNums->alpComp = FALSE;
    pNums->blendMode = 0;
}

void Material::ReserveGXMem(u8 texMapNum, u8 texSrtNum, u8 texCoordGenNum,
                            u8 tevStageNum, bool allocTevSwap, u8 indStageNum,
                            u8 indSrtNum, bool allocChanCtrl, bool allocMatCol,
                            bool allocAlphaComp, bool allocBlendMode) {

    int tevSwapNum = allocTevSwap ? 1 : 0;
    int chanCtrlNum = allocChanCtrl ? 1 : 0;
    int matColNum = allocMatCol ? 1 : 0;
    int alpCompNum = allocAlphaComp ? 1 : 0;
    int blendModeNum = allocBlendMode ? 1 : 0;

    if (mGXMemCap.texMap >= texMapNum && mGXMemCap.texSRT >= texSrtNum &&
        mGXMemCap.texCoordGen >= texCoordGenNum &&
        mGXMemCap.tevStage >= tevStageNum && mGXMemCap.tevSwap >= tevSwapNum &&
        mGXMemCap.indStage >= indStageNum && mGXMemCap.indSRT >= indSrtNum &&
        mGXMemCap.chanCtrl >= chanCtrlNum && mGXMemCap.matCol >= matColNum &&
        mGXMemCap.alpComp >= alpCompNum &&
        mGXMemCap.blendMode >= blendModeNum) {
        return;
    }

    if (mpGXMem != NULL) {
        Layout::FreeMemory(mpGXMem);
        mpGXMem = NULL;

        InitBitGXNums(&mGXMemCap);
        InitBitGXNums(&mGXMemNum);
    }

    // clang-format off
    mpGXMem = Layout::AllocMemory(
        // All of these are <= 4 bytes
        (texCoordGenNum + chanCtrlNum + matColNum + tevSwapNum +
            alpCompNum + blendModeNum + indStageNum) * 4 +

        texMapNum   * sizeof(TexMap)   +
        tevStageNum * sizeof(TevStage) +
        texSrtNum   * sizeof(TexSRT)   +
        indSrtNum   * sizeof(TexSRT));
    // clang-format on

    if (mpGXMem == NULL) {
        return;
    }

    mGXMemCap.texMap = texMapNum;
    mGXMemCap.texSRT = texSrtNum;
    mGXMemCap.texCoordGen = texCoordGenNum;
    mGXMemCap.indSRT = indSrtNum;
    mGXMemCap.indStage = indStageNum;
    mGXMemCap.tevSwap = tevSwapNum;
    mGXMemCap.tevStage = tevStageNum;
    mGXMemCap.chanCtrl = chanCtrlNum;
    mGXMemCap.matCol = matColNum;
    mGXMemCap.alpComp = alpCompNum;
    mGXMemCap.blendMode = blendModeNum;

    mGXMemNum.texSRT = mGXMemCap.texSRT;
    InitTexSRT(GetTexSRTAry(), mGXMemNum.texSRT);

    mGXMemNum.indSRT = mGXMemCap.indSRT;
    InitTexSRT(GetIndTexSRTAry(), mGXMemNum.indSRT);

    mGXMemNum.chanCtrl = mGXMemCap.chanCtrl;
    if (mGXMemNum.chanCtrl != 0) {
        *GetChanCtrlAry() = ChanCtrl();
    }

    mGXMemNum.matCol = mGXMemCap.matCol;
    if (mGXMemNum.matCol != 0) {
        *GetMatColAry() = ut::Color::WHITE;
    }

    mGXMemNum.tevSwap = mGXMemCap.tevSwap;
    if (mGXMemNum.tevSwap != 0) {
        TevSwapMode* const pTevSwap = GetTevSwapAry();

        pTevSwap[GX_TEV_SWAP0].Set(GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                                   GX_CH_ALPHA);

        pTevSwap[GX_TEV_SWAP1].Set(GX_CH_RED, GX_CH_RED, GX_CH_RED,
                                   GX_CH_ALPHA);

        pTevSwap[GX_TEV_SWAP2].Set(GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN,
                                   GX_CH_ALPHA);

        pTevSwap[GX_TEV_SWAP3].Set(GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE,
                                   GX_CH_ALPHA);
    }

    mGXMemNum.alpComp = mGXMemCap.alpComp;
    if (mGXMemNum.alpComp != 0) {
        *GetAlphaComparePtr() = AlphaCompare();
    }

    mGXMemNum.blendMode = mGXMemCap.blendMode;
    if (mGXMemNum.blendMode != 0) {
        *GetBlendModePtr() = BlendMode();
    }
}

const TexMap* Material::GetTexMapAry() const {
    return detail::ConvertOffsToPtr<TexMap>(mpGXMem, 0);
}
TexMap* Material::GetTexMapAry() {
    return detail::ConvertOffsToPtr<TexMap>(mpGXMem, 0);
}

const TexSRT* Material::GetTexSRTAry() const {
    return detail::ConvertOffsToPtr<TexSRT>(mpGXMem,
                                            CalcOffsetTexSRTAry(mGXMemCap));
}
TexSRT* Material::GetTexSRTAry() {
    return detail::ConvertOffsToPtr<TexSRT>(mpGXMem,
                                            CalcOffsetTexSRTAry(mGXMemCap));
}

const TexCoordGen* Material::GetTexCoordGenAry() const {
    return detail::ConvertOffsToPtr<TexCoordGen>(
        mpGXMem, CalcOffsetTexCoordGenAry(mGXMemCap));
}
TexCoordGen* Material::GetTexCoordGenAry() {
    return detail::ConvertOffsToPtr<TexCoordGen>(
        mpGXMem, CalcOffsetTexCoordGenAry(mGXMemCap));
}

const ChanCtrl* Material::GetChanCtrlAry() const {
    return detail::ConvertOffsToPtr<ChanCtrl>(mpGXMem,
                                              CalcOffsetChanCtrlAry(mGXMemCap));
}
ChanCtrl* Material::GetChanCtrlAry() {
    return detail::ConvertOffsToPtr<ChanCtrl>(mpGXMem,
                                              CalcOffsetChanCtrlAry(mGXMemCap));
}

const ut::Color* Material::GetMatColAry() const {
    return detail::ConvertOffsToPtr<ut::Color>(mpGXMem,
                                               CalcOffsetMatColAry(mGXMemCap));
}
ut::Color* Material::GetMatColAry() {
    return detail::ConvertOffsToPtr<ut::Color>(mpGXMem,
                                               CalcOffsetMatColAry(mGXMemCap));
}

const TevSwapMode* Material::GetTevSwapAry() const {
    return detail::ConvertOffsToPtr<TevSwapMode>(
        mpGXMem, CalcOffsetTevSwapAry(mGXMemCap));
}
TevSwapMode* Material::GetTevSwapAry() {
    return detail::ConvertOffsToPtr<TevSwapMode>(
        mpGXMem, CalcOffsetTevSwapAry(mGXMemCap));
}

const AlphaCompare* Material::GetAlphaComparePtr() const {
    return detail::ConvertOffsToPtr<AlphaCompare>(
        mpGXMem, CalcOffsetGetAlphaCompare(mGXMemCap));
}
AlphaCompare* Material::GetAlphaComparePtr() {
    return detail::ConvertOffsToPtr<AlphaCompare>(
        mpGXMem, CalcOffsetGetAlphaCompare(mGXMemCap));
}

const BlendMode* Material::GetBlendModePtr() const {
    return detail::ConvertOffsToPtr<BlendMode>(mpGXMem,
                                               CalcOffsetBlendMode(mGXMemCap));
}
BlendMode* Material::GetBlendModePtr() {
    return detail::ConvertOffsToPtr<BlendMode>(mpGXMem,
                                               CalcOffsetBlendMode(mGXMemCap));
}

const IndirectStage* Material::GetIndirectStageAry() const {
    return detail::ConvertOffsToPtr<IndirectStage>(
        mpGXMem, CalcOffsetIndirectStageAry(mGXMemCap));
}
IndirectStage* Material::GetIndirectStageAry() {
    return detail::ConvertOffsToPtr<IndirectStage>(
        mpGXMem, CalcOffsetIndirectStageAry(mGXMemCap));
}

const TexSRT* Material::GetIndTexSRTAry() const {
    return detail::ConvertOffsToPtr<TexSRT>(mpGXMem,
                                            CalcOffsetIndTexSRTAry(mGXMemCap));
}
TexSRT* Material::GetIndTexSRTAry() {
    return detail::ConvertOffsToPtr<TexSRT>(mpGXMem,
                                            CalcOffsetIndTexSRTAry(mGXMemCap));
}

const TevStage* Material::GetTevStageAry() const {
    return detail::ConvertOffsToPtr<TevStage>(mpGXMem,
                                              CalcOffsetTevStageAry(mGXMemCap));
}
TevStage* Material::GetTevStageAry() {
    return detail::ConvertOffsToPtr<TevStage>(mpGXMem,
                                              CalcOffsetTevStageAry(mGXMemCap));
}

void Material::SetName(const char* pName) {
    std::strncpy(mName, pName, NW4R_LYT_MATERIAL_NAME_LEN);
    mName[NW4R_LYT_MATERIAL_NAME_LEN] = '\0';
}

void Material::SetTextureNum(u8 num) {
    if (num > 0) {
        TexMap* const pTexMap = GetTexMapAry();

        for (u32 i = mGXMemNum.texMap; i < num; i++) {
            new (&pTexMap[i]) TexMap();
        }

        mGXMemNum.texMap = num;
    }
}

void Material::SetTexCoordGenNum(u8 num) {
    if (num > 0) {
        TexCoordGen* const pTexCoordGen = GetTexCoordGenAry();

        for (u32 i = mGXMemNum.texCoordGen; i < num; i++) {
            new (&pTexCoordGen[i]) TexCoordGen();
        }

        mGXMemNum.texCoordGen = num;
    }
}

void Material::SetTevStageNum(u8 num) {
    if (num > 0) {
        TevStage* const pTevStage = GetTevStageAry();

        for (u32 i = mGXMemNum.tevStage; i < num; i++) {
            new (&pTevStage[i]) TevStage();
        }

        mGXMemNum.tevStage = num;
    }
}

void Material::SetIndStageNum(u8 num) {
    if (num > 0) {
        IndirectStage* const pIndStage = GetIndirectStageAry();

        for (u32 i = mGXMemNum.indStage; i < num; i++) {
            new (&pIndStage[i]) IndirectStage();
        }

        mGXMemNum.indStage = num;
    }
}

void Material::SetColorElement(u32 idx, s16 value) {
    switch (idx) {
    case ANIMTARGET_MATCOLOR_MATR:
    case ANIMTARGET_MATCOLOR_MATG:
    case ANIMTARGET_MATCOLOR_MATB:
    case ANIMTARGET_MATCOLOR_MATA: {
        if (mGXMemNum.matCol < 1) {
            break;
        }

        ut::Color* pMatColor = GetMatColAry();
        SetColorComponentValue(pMatColor, idx % 4, value);
        break;
    }

    case ANIMTARGET_MATCOLOR_TEV0R:
    case ANIMTARGET_MATCOLOR_TEV0G:
    case ANIMTARGET_MATCOLOR_TEV0B:
    case ANIMTARGET_MATCOLOR_TEV0A:
    case ANIMTARGET_MATCOLOR_TEV1R:
    case ANIMTARGET_MATCOLOR_TEV1G:
    case ANIMTARGET_MATCOLOR_TEV1B:
    case ANIMTARGET_MATCOLOR_TEV1A:
    case ANIMTARGET_MATCOLOR_TEV2R:
    case ANIMTARGET_MATCOLOR_TEV2G:
    case ANIMTARGET_MATCOLOR_TEV2B:
    case ANIMTARGET_MATCOLOR_TEV2A: {
        u32 regIdx = (idx - 4) / 4;

        switch ((idx - 4) % 4) {
        case 0: {
            mTevCols[regIdx].r = value;
            break;
        }

        case 1: {
            mTevCols[regIdx].g = value;
            break;
        }

        case 2: {
            mTevCols[regIdx].b = value;
            break;
        }

        case 3: {
            mTevCols[regIdx].a = value;
            break;
        }
        }
        break;
    }

    case ANIMTARGET_MATCOLOR_TEVK0R:
    case ANIMTARGET_MATCOLOR_TEVK0G:
    case ANIMTARGET_MATCOLOR_TEVK0B:
    case ANIMTARGET_MATCOLOR_TEVK0A:
    case ANIMTARGET_MATCOLOR_TEVK1R:
    case ANIMTARGET_MATCOLOR_TEVK1G:
    case ANIMTARGET_MATCOLOR_TEVK1B:
    case ANIMTARGET_MATCOLOR_TEVK1A:
    case ANIMTARGET_MATCOLOR_TEVK2R:
    case ANIMTARGET_MATCOLOR_TEVK2G:
    case ANIMTARGET_MATCOLOR_TEVK2B:
    case ANIMTARGET_MATCOLOR_TEVK2A:
    case ANIMTARGET_MATCOLOR_TEVK3R:
    case ANIMTARGET_MATCOLOR_TEVK3G:
    case ANIMTARGET_MATCOLOR_TEVK3B:
    case ANIMTARGET_MATCOLOR_TEVK3A: {
        u32 regIdx = (idx - 16) / 4;
        SetColorComponentValue(&mTevKCols[regIdx], idx - 16, value);
        break;
    }
    }
}

bool Material::SetupGX(bool modulate, u8 alpha) {
    static GXTevKColorSel kColSels[GX_MAX_TEXMAP] = {
        GX_TEV_KCSEL_K3_A, GX_TEV_KCSEL_K3_B, GX_TEV_KCSEL_K3_G,
        GX_TEV_KCSEL_K3_R, GX_TEV_KCSEL_K2_A, GX_TEV_KCSEL_K2_B,
        GX_TEV_KCSEL_K2_G, GX_TEV_KCSEL_K2_R};

    static GXTevKAlphaSel kAlpSels[GX_MAX_TEXMAP] = {
        GX_TEV_KASEL_K3_A, GX_TEV_KASEL_K3_B, GX_TEV_KASEL_K3_G,
        GX_TEV_KASEL_K3_R, GX_TEV_KASEL_K2_A, GX_TEV_KASEL_K2_B,
        GX_TEV_KASEL_K2_G, GX_TEV_KASEL_K2_R};

    bool useVtxColor = true;
    bool useMatColor = false;

    GXSetNumChans(1);

    if (IsChanCtrlCap()) {
        const ChanCtrl* const pChanCtrl = GetChanCtrlAry();

        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, pChanCtrl->GetColorSrc(),
                      GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, pChanCtrl->GetAlphaSrc(),
                      GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        useVtxColor = pChanCtrl->GetColorSrc() == GX_SRC_VTX ||
                      pChanCtrl->GetAlphaSrc() == GX_SRC_VTX;

        useMatColor = pChanCtrl->GetColorSrc() == GX_SRC_REG ||
                      pChanCtrl->GetAlphaSrc() == GX_SRC_REG;
    } else {
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX,
                      GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    }

    bool useRasStage = false;

    if (useVtxColor) {
        useRasStage = useRasStage || modulate;
    }

    if (useMatColor) {
        ut::Color matColor = ut::Color::WHITE;

        if (IsMatColorCap()) {
            matColor = *GetMatColAry();
        }

        matColor = detail::MultipleAlpha(matColor, alpha);
        GXSetChanMatColor(GX_COLOR0A0, matColor);

        useRasStage = useRasStage || matColor != ut::Color::WHITE;
    }

    bool setTexMtx = false;
    bool useTexMtx[MAX_TEX_SRT];

    for (int i = 0; i < MAX_TEX_SRT; i++) {
        useTexMtx[i] = false;
    }

    GXSetNumTexGens(mGXMemNum.texCoordGen);
    if (mGXMemNum.texCoordGen > 0) {
        const TexCoordGen* const pTexCoordGen = GetTexCoordGenAry();

        for (int i = 0; i < mGXMemNum.texCoordGen; i++) {
            u32 texMtx = pTexCoordGen[i].GetTexMtx();

            if (pTexCoordGen[i].GetTexGenType() == GX_TG_MTX2x4 &&
                texMtx != GX_IDENTITY) {

                useTexMtx[GetTexMtxIdx(texMtx)] = true;
                setTexMtx = true;
            }

            GXSetTexCoordGen(static_cast<GXTexCoordID>(i),
                             pTexCoordGen[i].GetTexGenType(),
                             pTexCoordGen[i].GetTexGenSrc(), texMtx);
        }
    }

    if (setTexMtx) {
        const TexSRT* const pTexSrt = GetTexSRTAry();

        for (u8 i = 0; i < mGXMemNum.texSRT; i++) {
            if (!useTexMtx[i]) {
                continue;
            }

            math::MTX34 mtx;
            CalcTextureMtx(&mtx, pTexSrt[i]);
            GXLoadTexMtxImm(mtx, GetTexMtx(i), GX_MTX_2x4);
        }
    }

    if (mGXMemNum.texMap > 0) {
        u32 tlutID = GX_TLUT0;
        u32 bigTlutID = GX_BIGTLUT0;

        const TexMap* const pTexMap = GetTexMapAry();

        for (int i = 0; i < mGXMemNum.texMap; i++) {
            const TexMap& rTexMap = pTexMap[i];

            GXTexObj texObj;
            rTexMap.Get(&texObj);

            if (detail::IsCITexelFormat(rTexMap.GetTexelFormat())) {
                u32 tlutName;
                if (static_cast<int>(rTexMap.GetTexelFormat()) == GX_TF_C14X2) {
                    tlutName = bigTlutID++;
                } else {
                    tlutName = tlutID++;
                }

                GXInitTexObjTlut(&texObj, tlutName);

                GXTlutObj tlutObj;
                rTexMap.Get(&tlutObj);

                GXLoadTlut(&tlutObj, tlutName);
            }

            GXLoadTexObj(&texObj, static_cast<GXTexMapID>(i));
        }
    }

    GXSetTevColorS10(GX_TEVREG0, mTevCols[TEVCOLOR_REG0]);
    GXSetTevColorS10(GX_TEVREG1, mTevCols[TEVCOLOR_REG1]);
    GXSetTevColorS10(GX_TEVREG2, mTevCols[TEVCOLOR_REG2]);

    GXSetTevKColor(GX_KCOLOR0, mTevKCols[GX_KCOLOR0]);
    GXSetTevKColor(GX_KCOLOR1, mTevKCols[GX_KCOLOR1]);
    GXSetTevKColor(GX_KCOLOR2, mTevKCols[GX_KCOLOR2]);
    GXSetTevKColor(GX_KCOLOR3, mTevKCols[GX_KCOLOR3]);

    if (IsTevSwapCap()) {
        const TevSwapMode* const pTevSwap = GetTevSwapAry();

        for (int i = 0; i < GX_MAX_TEVSWAP; i++) {
            GXSetTevSwapModeTable(static_cast<GXTevSwapSel>(i),
                                  pTevSwap[i].GetR(), pTevSwap[i].GetG(),
                                  pTevSwap[i].GetB(), pTevSwap[i].GetA());
        }
    } else {
        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                              GX_CH_ALPHA);

        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED,
                              GX_CH_ALPHA);

        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN,
                              GX_CH_GREEN, GX_CH_ALPHA);

        GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE,
                              GX_CH_ALPHA);
    }

    bool setIndTexMtx = false;
    bool useIndTexMtx[MAX_IND_SRT];

    for (int i = 0; i < MAX_IND_SRT; i++) {
        useIndTexMtx[i] = false;
    }

    if (mGXMemNum.tevStage > 0) {
        GXSetNumTevStages(mGXMemNum.tevStage);

        const TevStage* const pTevStage = GetTevStageAry();

        for (int i = 0; i < mGXMemNum.tevStage; i++) {
            GXTevStageID tevStage = static_cast<GXTevStageID>(i);

            // clang-format off
            GXSetTevOrder(tevStage,
                pTevStage[i].GetTexCoordGen(),
                pTevStage[i].GetTexMap(),
                pTevStage[i].GetColorChan());

            GXSetTevSwapMode(tevStage,
                pTevStage[i].GetRasSwapSel(),
                pTevStage[i].GetTexSwapSel());

            GXSetTevColorIn(tevStage,
                pTevStage[i].GetColorInA(),
                pTevStage[i].GetColorInB(),
                pTevStage[i].GetColorInC(),
                pTevStage[i].GetColorInD());

            GXSetTevColorOp(tevStage,
                pTevStage[i].GetColorOp(),
                pTevStage[i].GetColorBias(),
                pTevStage[i].GetColorScale(),
                pTevStage[i].IsColorClamp(),
                pTevStage[i].GetColorOutReg());

            GXSetTevKColorSel(tevStage,
                pTevStage[i].GetKColorSel());

            GXSetTevAlphaIn(tevStage, 
                pTevStage[i].GetAlphaInA(),
                pTevStage[i].GetAlphaInB(),
                pTevStage[i].GetAlphaInC(),
                pTevStage[i].GetAlphaInD());

            GXSetTevAlphaOp(tevStage, 
                pTevStage[i].GetAlphaOp(),
                pTevStage[i].GetAlphaBias(),
                pTevStage[i].GetAlphaScale(),
                pTevStage[i].IsAlphaClamp(),
                pTevStage[i].GetAlphaOutReg());

            GXSetTevKAlphaSel(tevStage,
                pTevStage[i].GetKAlphaSel());
            // clang-format on

            GXIndTexMtxID indMtx = pTevStage[i].GetIndMtxSel();

            // clang-format off
            GXSetTevIndirect(tevStage,
                pTevStage[i].GetIndStage(),
                pTevStage[i].GetIndFormat(),
                pTevStage[i].GetIndBiasSel(),
                indMtx,
                pTevStage[i].GetIndWrapS(),
                pTevStage[i].GetIndWrapT(),
                pTevStage[i].IsIndAddPrev(),
                pTevStage[i].IsIndUtcLod(),
                pTevStage[i].GetIndAlphaSel());
            // clang-format on

            if (GX_ITM_0 <= indMtx && indMtx <= GX_ITM_2) {
                useIndTexMtx[indMtx - 1] = true;
                setIndTexMtx = true;
            }
        }

        useRasStage = true;
    } else {
        u8 tevStageID = GX_TEVSTAGE0;

        if (mGXMemNum.texMap == 0) {
            GXTevStageID tevStage = GX_TEVSTAGE0;

            GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                          GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC,
                            GX_CC_ZERO);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_A1, GX_CA_RASA,
                            GX_CA_ZERO);

            useRasStage = true;
            tevStageID = GX_TEVSTAGE1;
        } else {
            if (mGXMemNum.texMap == 1) {
                GXTevStageID tevStage = GX_TEVSTAGE0;

                GXSetTevOrder(tevStage, GX_TEXCOORD0, GX_TEXMAP0,
                              GX_COLOR_NULL);
                GXSetTevColorIn(tevStage, GX_CC_C0, GX_CC_C1, GX_CC_TEXC,
                                GX_CC_ZERO);
                GXSetTevAlphaIn(tevStage, GX_CA_A0, GX_CA_A1, GX_CA_TEXA,
                                GX_CA_ZERO);

                tevStageID = GX_TEVSTAGE1;
            } else {
                if (mGXMemNum.texMap == 2) {
                    GXTevStageID tevStage = GX_TEVSTAGE0;

                    GXSetTevOrder(tevStage, GX_TEXCOORD0, GX_TEXMAP0,
                                  GX_COLOR_NULL);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO,
                                    GX_CC_ZERO, GX_CC_TEXC);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO,
                                    GX_CA_ZERO, GX_CA_TEXA);

                    tevStage = GX_TEVSTAGE1;

                    GXSetTevOrder(tevStage, GX_TEXCOORD1, GX_TEXMAP1,
                                  GX_COLOR_NULL);
                    GXSetTevColorIn(tevStage, GX_CC_TEXC, GX_CC_CPREV,
                                    GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevAlphaIn(tevStage, GX_CA_TEXA, GX_CA_APREV,
                                    GX_CA_KONST, GX_CA_ZERO);

                    GXSetTevKColorSel(tevStage, kColSels[GX_TEXMAP0]);
                    GXSetTevKAlphaSel(tevStage, kAlpSels[GX_TEXMAP0]);

                    tevStageID = GX_TEVSTAGE2;
                } else {
                    for (int i = 0; i < mGXMemNum.texMap; i++) {
                        GXTevStageID tevStage =
                            static_cast<GXTevStageID>(tevStageID);

                        GXSetTevOrder(tevStage, static_cast<GXTexCoordID>(i),
                                      static_cast<GXTexMapID>(i),
                                      GX_COLOR_NULL);

                        GXTevColorArg colorD =
                            i == GX_TEXMAP0 ? GX_CC_ZERO : GX_CC_CPREV;
                        GXTevAlphaArg alphaD =
                            i == GX_TEXMAP0 ? GX_CA_ZERO : GX_CA_APREV;

                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC,
                                        GX_CC_KONST, colorD);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA,
                                        GX_CA_KONST, alphaD);

                        GXSetTevKColorSel(tevStage, kColSels[i]);
                        GXSetTevKAlphaSel(tevStage, kAlpSels[i]);

                        tevStageID++;
                    }
                }

                if (mTevCols[TEVCOLOR_REG0] != DefaultBlackColor ||
                    mTevCols[TEVCOLOR_REG1] != DefaultWhiteColor) {

                    GXTevStageID tevStage =
                        static_cast<GXTevStageID>(tevStageID);

                    GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                                  GX_COLOR_NULL);
                    GXSetTevColorIn(tevStage, GX_CC_C0, GX_CC_C1, GX_CC_CPREV,
                                    GX_CC_ZERO);
                    GXSetTevAlphaIn(tevStage, GX_CA_A0, GX_CA_A1, GX_CA_APREV,
                                    GX_CA_ZERO);

                    tevStageID++;
                }
            }

            if (useRasStage) {
                GXTevStageID tevStage = static_cast<GXTevStageID>(tevStageID);

                GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC,
                                GX_CC_ZERO);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA,
                                GX_CA_ZERO);

                tevStageID++;
            }
        }

        const u8 tevStageNum = tevStageID;
        for (u8 id = 0; id < tevStageNum; id++) {
            GXTevStageID tevStage = static_cast<GXTevStageID>(id);

            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            TRUE, GX_TEVPREV);

            GXSetTevDirect(tevStage);
            GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        }

        GXSetNumTevStages(tevStageNum);
    }

    if (setIndTexMtx) {
        const TexSRT* const pIndTexSrt = GetIndTexSRTAry();

        for (int i = 0; i < mGXMemNum.indSRT; i++) {
            if (!useIndTexMtx[i]) {
                continue;
            }

            f32 mtx[2][3];
            CalcIndTexMtx(mtx, pIndTexSrt[i]);
            SetIndTexMtx(static_cast<GXIndTexMtxID>(GX_ITM_0 + i), mtx);
        }
    }

    GXSetNumIndStages(mGXMemNum.indStage);
    if (mGXMemNum.indStage > 0) {
        const IndirectStage* const pIndStage = GetIndirectStageAry();

        for (int i = 0; i < mGXMemNum.indStage; i++) {
            GXIndTexStageID indStage = static_cast<GXIndTexStageID>(i);

            GXSetIndTexOrder(indStage, pIndStage[i].GetTexCoordGen(),
                             pIndStage[i].GetTexMap());

            GXSetIndTexCoordScale(indStage, pIndStage[i].GetScaleS(),
                                  pIndStage[i].GetScaleT());
        }
    }

    if (IsAlphaCompareCap()) {
        const AlphaCompare* const pAlphaComp = GetAlphaComparePtr();

        GXSetAlphaCompare(pAlphaComp->GetComp0(), pAlphaComp->GetRef0(),
                          pAlphaComp->GetOp(), pAlphaComp->GetComp1(),
                          pAlphaComp->GetRef1());
    } else {
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    }

    if (IsBlendModeCap()) {
        const BlendMode* const pBlendMode = GetBlendModePtr();

        GXSetBlendMode(pBlendMode->GetType(), pBlendMode->GetSrcFactor(),
                       pBlendMode->GetDstFactor(), pBlendMode->GetOp());

    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                       GX_LO_SET);
    }

    return useRasStage && useVtxColor;
}

void Material::BindAnimation(AnimTransform* pAnimTrans) {
    pAnimTrans->Bind(this);
}

void Material::UnbindAnimation(AnimTransform* pAnimTrans) {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mAnimList, {
        if (pAnimTrans != NULL && it->GetAnimTransform() != pAnimTrans) {
            continue;
        }

        mAnimList.Erase(it);
        it->Reset();
    })
}

void Material::UnbindAllAnimation() {
    UnbindAnimation(NULL);
}

void Material::Animate() {
    NW4R_UT_LINKLIST_FOREACH (it, mAnimList, {
        if (!it->IsEnable()) {
            continue;
        }

        AnimTransform* pAnimTrans = it->GetAnimTransform();
        pAnimTrans->Animate(it->GetIndex(), this); 
    })
}

void Material::AddAnimationLink(AnimationLink* pAnimLink) {
    mAnimList.PushBack(pAnimLink);
}

AnimationLink* Material::FindAnimationLink(AnimTransform* pAnimTrans) {
    return detail::FindAnimationLink(&mAnimList, pAnimTrans);
}

void Material::SetAnimationEnable(AnimTransform* pAnimTrans, bool enable) {
    AnimationLink* pAnimLink = FindAnimationLink(pAnimTrans);

    if (pAnimLink != NULL) {
        pAnimLink->SetEnable(enable);
    }
}

/******************************************************************************
 *
 * Functions
 *
 ******************************************************************************/
namespace detail {

Size GetTextureSize(Material* pMaterial, u8 idx) {
    if (idx >= pMaterial->GetTextureNum()) {
        return Size(0.0f, 0.0f);
    }

    const TexMap& rTexMap = pMaterial->GetTexture(idx);
    return rTexMap.GetSize();
}

} // namespace detail
} // namespace lyt
} // namespace nw4r
