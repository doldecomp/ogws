#ifndef NW4R_LYT_MATERIAL_H
#define NW4R_LYT_MATERIAL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_texMap.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class AnimTransform;
struct ResBlockSet;

namespace detail {

/******************************************************************************
 *
 * BitGXNums
 *
 ******************************************************************************/
struct BitGXNums {
    u32 texMap : 4;
    u32 texSRT : 4;
    u32 texCoordGen : 4;
    u32 indSRT : 2;
    u32 indStage : 3;
    u32 tevSwap : 1;
    u32 tevStage : 5;
    u32 chanCtrl : 1;
    u32 matCol : 1;
    u32 alpComp : 1;
    u32 blendMode : 1;
};

} // namespace detail

namespace res {

/******************************************************************************
 *
 * MAT1 binary layout
 *
 ******************************************************************************/
struct Material {
    char name[NW4R_LYT_MATERIAL_NAME_LEN]; // at 0x0
    GXColorS10 tevCols[TEVCOLOR_MAX];      // at 0x14
    GXColor tevKCols[GX_MAX_KCOLOR];       // at 0x2C
    MaterialResourceNum resNum;            // at 0x3C
};

} // namespace res

/******************************************************************************
 *
 * Material
 *
 ******************************************************************************/
class Material {
public:
    Material(const res::Material* pRes, const ResBlockSet& rBlockSet);
    virtual ~Material(); // at 0x8

    virtual bool SetupGX(bool modulate, u8 alpha); // at 0xC

    virtual void BindAnimation(AnimTransform* pAnimTrans);   // at 0x10
    virtual void UnbindAnimation(AnimTransform* pAnimTrans); // at 0x14
    virtual void UnbindAllAnimation();                       // at 0x18

    virtual void Animate(); // at 0x1C

    virtual AnimationLink*
    FindAnimationLink(AnimTransform* pAnimTrans); // at 0x20

    virtual void SetAnimationEnable(AnimTransform* pAnimTrans,
                                    bool enable); // at 0x24

    void AddAnimationLink(AnimationLink* pAnimLink);

    GXColorS10 GetTevColor(u32 idx) {
        return mTevCols[idx];
    }
    void SetTevColor(u32 idx, const GXColorS10& rColor) {
        mTevCols[idx] = rColor;
    }

    ut::Color GetTevKColor(u32 idx) {
        return mTevKCols[idx];
    }
    void SetTevKColor(u32 idx, ut::Color color) {
        mTevKCols[idx] = color;
    }

    u8 GetTextureNum() const {
        return mGXMemNum.texMap;
    }
    u8 GetTextureCap() const {
        return mGXMemCap.texMap;
    }
    void SetTextureNum(u8 num);

    u8 GetTexSRTCap() const {
        return mGXMemCap.texSRT;
    }

    u8 GetTexCoordGenCap() const {
        return mGXMemCap.texCoordGen;
    }
    void SetTexCoordGenNum(u8 num);

    u8 GetIndTexSRTCap() const {
        return mGXMemCap.indSRT;
    }

    u8 GetTevStageNum() const {
        return mGXMemNum.tevStage;
    }
    void SetTevStageNum(u8 num);

    void SetIndStageNum(u8 num);

    void SetColorElement(u32 idx, s16 value);

    bool IsTevSwapCap() const {
        return mGXMemCap.tevSwap;
    }
    bool IsChanCtrlCap() const {
        return mGXMemCap.chanCtrl;
    }
    bool IsMatColorCap() const {
        return mGXMemCap.matCol;
    }
    bool IsAlphaCompareCap() const {
        return mGXMemCap.alpComp;
    }
    bool IsBlendModeCap() const {
        return mGXMemCap.blendMode;
    }

    const TexMap* GetTexMapAry() const;
    TexMap* GetTexMapAry();

    const TexSRT* GetTexSRTAry() const;
    TexSRT* GetTexSRTAry();

    const TexCoordGen* GetTexCoordGenAry() const;
    TexCoordGen* GetTexCoordGenAry();

    const ChanCtrl* GetChanCtrlAry() const;
    ChanCtrl* GetChanCtrlAry();

    const ut::Color* GetMatColAry() const;
    ut::Color* GetMatColAry();

    const TevSwapMode* GetTevSwapAry() const;
    TevSwapMode* GetTevSwapAry();

    const AlphaCompare* GetAlphaComparePtr() const;
    AlphaCompare* GetAlphaComparePtr();

    const BlendMode* GetBlendModePtr() const;
    BlendMode* GetBlendModePtr();

    const IndirectStage* GetIndirectStageAry() const;
    IndirectStage* GetIndirectStageAry();

    const TexSRT* GetIndTexSRTAry() const;
    TexSRT* GetIndTexSRTAry();

    const TevStage* GetTevStageAry() const;
    TevStage* GetTevStageAry();

    const TexMap& GetTexture(u8 idx) const {
        return GetTexMapAry()[idx];
    }
    void GetTexture(GXTexObj* pTexObj, u8 idx) const {
        GetTexMapAry()[idx].Get(pTexObj);
    }
    void SetTexture(u8 idx, const TexMap& rTexMap) {
        GetTexMapAry()[idx].Set(rTexMap);
    }
    void SetTextureNoWrap(u8 idx, const TexMap& rTexMap) {
        GetTexMapAry()[idx].SetNoWrap(rTexMap);
    }

    const TexSRT& GetTexSRT(u32 idx) const {
        return GetTexSRTAry()[idx];
    }
    void SetTexSRT(const TexSRT& rTexSRT, u32 idx) {
        GetTexSRTAry()[idx] = rTexSRT;
    }

    void SetTexSRTElement(u32 srt, u32 idx, f32 value) {
        f32* const pArray = reinterpret_cast<f32*>(&GetTexSRTAry()[srt]);
        pArray[idx] = value;
    }

    void SetTexCoordGen(u32 idx, TexCoordGen gen) {
        GetTexCoordGenAry()[idx] = gen;
    }

    ut::Color GetMatColor() const {
        return GetMatColAry()[0];
    }

    void SetIndTexSRTElement(u32 srt, u32 idx, f32 value) {
        f32* const pArray = reinterpret_cast<f32*>(&GetIndTexSRTAry()[srt]);
        pArray[idx] = value;
    }

    void SetName(const char* pName);
    const char* GetName() const {
        return mName;
    }

    bool IsUserAllocated() const {
        return mbUserAllocated;
    }

protected:
    static const int MAX_TEX_SRT = (GX_TEXMTX9 - GX_TEXMTX0) / 3 + 1;
    static const int MAX_IND_SRT = (GX_ITM_2 - GX_ITM_0) + 1;

protected:
    AnimationLinkList mAnimList; // at 0x4

    GXColorS10 mTevCols[TEVCOLOR_MAX];  // at 0x10
    ut::Color mTevKCols[GX_MAX_KCOLOR]; // at 0x28

    detail::BitGXNums mGXMemCap; // at 0x38
    detail::BitGXNums mGXMemNum; // at 0x3C
    void* mpGXMem;               // at 0x40

    char mName[NW4R_LYT_MATERIAL_NAME_LEN + 1]; // at 0x44
    bool mbUserAllocated;                       // at 0x59

    u8 PADDING_0x5A[0x5C - 0x5A]; // at 0x5A

private:
    void Init();
    void InitBitGXNums(detail::BitGXNums* pNums);

    void ReserveGXMem(u8 texMapNum, u8 texSrtNum, u8 texCoordGenNum,
                      u8 tevStageNum, bool allocTevSwap, u8 indStageNum,
                      u8 indSrtNum, bool allocChanCtrl, bool allocMatCol,
                      bool allocAlpComp, bool allocBlendMode);
};

/******************************************************************************
 *
 * Functions
 *
 ******************************************************************************/
namespace detail {

Size GetTextureSize(Material* pMaterial, u8 idx);

} // namespace detail
} // namespace lyt
} // namespace nw4r

#endif
