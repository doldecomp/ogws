#ifndef RP_GRAPHICS_MODEL_ANM_IMPLEMENT_H
#define RP_GRAPHICS_MODEL_ANM_IMPLEMENT_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>
#include <Pack/RPGraphics/RPGrpModelAnm.h>

#include <nw4r/g3d.h>

//! @addtogroup rp_graphics
//! @{

/******************************************************************************
 *
 * RPGrpModelAnmImplement
 *
 ******************************************************************************/

/**
 * @brief Model animation implementation
 */
template <RPGrpModel::Kind K> class RPGrpModelAnmImplement {};

/******************************************************************************
 *
 * RPGrpModelAnmG3D
 *
 ******************************************************************************/

// Shorthand name for specialization
typedef RPGrpModelAnmImplement<RPGrpModel::Kind_G3D> RPGrpModelAnmG3D;

/**
 * @brief Model animation implementation for nw4r::g3d
 */
template <>
class RPGrpModelAnmImplement<RPGrpModel::Kind_G3D> : public RPGrpModelAnm {
public:
    static RPGrpModelAnm* Construct(RPGrpModel* pModel) DECOMP_DONT_INLINE {
        RPGrpModelAnm* pAnm = new RPGrpModelAnmImplement(pModel);
        pAnm->Configure();
        return pAnm;
    }

    virtual void Configure();                                     // at 0x8
    virtual void Regist(Anm anm, AnmIdx idx, RPGrpHandle handle); // at 0xC
    virtual void RegistFromResFile(Anm anm, AnmIdx idx, RPGrpHandle handle,
                                   const char* pName); // at 0x10
    virtual void RegistFromResFile(Anm anm, AnmIdx idx, RPGrpHandle handle,
                                   u32 id);           // at 0x14
    virtual s16 SetBlendAnm(Anm anm, u8, AnmIdx idx); // at 0x18
    virtual s16 RemoveBlendAnm(Anm anm, u8, u8);      // at 0x1C

    virtual void SetBlendWeight(Anm anm, u8, f32, u8);      // at 0x20
    virtual s16 GetBlendAnm(Anm, u8, u8);                   // at 0x24
    virtual f32 GetBlendWeight(Anm, u8, u8);                // at 0x28
    virtual void ReBindChrAnmNode(u16, u16, BindType type); // at 0x2C

    virtual void ReleaseChrAnmNode(u16, u16, BindType type);       // at 0x30
    virtual bool StartNoBlend(Anm anm, u16 idx, f32 frame = 0.0f); // at 0x34
    virtual bool StartBlend(Anm anm, u16 idx, f32 weight = 0.0f,
                            f32 frame = 0.0f); // at 0x38

    virtual bool Cancel(Anm anm, AnmIdx idx);                  // at 0x3C
    virtual bool Start(Anm anm, AnmIdx idx, f32 frame = 0.0f); // at 0x40

    virtual f32 VF_0x44(UNKTYPE);
    virtual f32 VF_0x48(UNKTYPE);

    virtual int GetNumFrame(Anm anm, AnmIdx idx) const; // at 0x4C
    virtual AnmPlayPolicy GetAnmPlayPolicy(Anm anm,
                                           AnmIdx idx) const; // at 0x50

    virtual void SetFrame(Anm anm, AnmIdx idx, f32 frame); // at 0x54
    virtual f32 GetFrame(Anm anm, AnmIdx idx) const;       // at 0x58

    virtual void SetUpdateRate(Anm anm, AnmIdx idx, f32 rate); // at 0x5C
    virtual f32 GetUpdateRate(Anm anm, AnmIdx idx) const;      // at 0x60

    virtual void SetEnableQuaternionBlend(bool enable); // at 0x64

    virtual void SetEnableChrAnm(bool enable); // at 0x68
    virtual void UpdateFrame();                // at 0x6C

    virtual void VF_0x70(UNKTYPE); // at 0x70
    virtual void VF_0x74(UNKTYPE); // at 0x74

    virtual nw4r::g3d::AnmObj* GetAnmObj(Anm anm, AnmIdx idx) const; // at 0x78

    void Init();

    nw4r::g3d::AnmObj* InternalGetAnmObj(Anm anm, AnmIdx idx) const;
    void InternalSetAnmObj(Anm anm);

    bool IsPlayingG3D(Anm anm, u16 idx) const {
        return mpAnmFlags[anm][idx] & AnmFlag_PlayingG3D;
    }

private:
    struct ChrBlendInfo {
        nw4r::g3d::AnmObjChrBlend* pAnmObj; // at 0x0
        s16 toAnmIdx[8];                    // at 0x4
    };

    struct ShpBlendInfo {
        nw4r::g3d::AnmObjShpBlend* pAnmObj; // at 0x0
        s16 toAnmIdx[8];                    // at 0x4
    };

private:
    explicit RPGrpModelAnmImplement(RPGrpModel* pModel);
    virtual ~RPGrpModelAnmImplement() {} // at 0x7C

    virtual void SetAnmObj(Anm anm, nw4r::g3d::AnmObj** ppAnmObjs); // at 0x80
    virtual void InternalCalc();                                    // at 0x84

    void RegistAnmChr(AnmIdx idx, const nw4r::g3d::ResAnmChr chr);

    void RegistAnmClr(AnmIdx idx, const nw4r::g3d::ResAnmClr clr);

    void RegistAnmTexPat(AnmIdx idx, const nw4r::g3d::ResAnmTexPat pat);

    void RegistAnmTexSrt(AnmIdx idx, const nw4r::g3d::ResAnmTexSrt srt);

    void RegistAnmVis(AnmIdx idx, const nw4r::g3d::ResAnmVis vis);

    void RegistAnmShp(AnmIdx idx, const nw4r::g3d::ResAnmShp shp);

private:
    //! Animation object type conversion table
    static const nw4r::g3d::ScnMdlSimple::AnmObjType TO_G3D_TYPE[Anm_Max];
    //! Animation play policy conversion table
    static const AnmPlayPolicy FROM_G3D_POLICY[];

    //! Scene model that this animation controls
    nw4r::g3d::ScnMdlSimple* mpScnMdlSimple; // at 0x6C

    nw4r::g3d::AnmObjChrRes** mppAnmObjChrRes;       // at 0x70
    nw4r::g3d::AnmObjMatClrRes** mppAnmObjMatClrRes; // at 0x74
    nw4r::g3d::AnmObjTexPatRes** mppAnmObjTexPatRes; // at 0x78
    nw4r::g3d::AnmObjTexSrtRes** mppAnmObjTexSrtRes; // at 0x7C
    nw4r::g3d::AnmObjVisRes** mppAnmObjVisRes;       // at 0x80
    nw4r::g3d::AnmObjShpRes** mppAnmObjShpRes;       // at 0x84

    nw4r::g3d::AnmObjVisRes** unk88;
    nw4r::g3d::AnmObjVisRes** unk8C;
    u32 unk90[Anm_Max];

    //! Map from RP animation index to G3D index
    s8* mpToIndexG3D[Anm_Max]; // at 0xB0

    nw4r::g3d::AnmObjMatClrOverride* mpAnmObjMatClrOverride; // at 0xD0
    nw4r::g3d::AnmObjTexPatOverride* mpAnmObjTexPatOverride; // at 0xD4
    nw4r::g3d::AnmObjTexSrtOverride* mpAnmObjTexSrtOverride; // at 0xD8
    nw4r::g3d::AnmObjVisOR* mpAnmObjVisOR;                   // at 0xDC

    ChrBlendInfo* mpChrBlendInfo; // at 0xE0
    ShpBlendInfo* mpShpBlendInfo; // at 0xE4
};

//! @}

#endif
