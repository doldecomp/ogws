#ifndef RP_GRAPHICS_MODEL_ANM_H
#define RP_GRAPHICS_MODEL_ANM_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Base class for model animation implementations
 */
class RPGrpModelAnm {
public:
    enum Anm {
        Anm_Chr,
        Anm_Clr,
        Anm_TexPat,
        Anm_TexSrt,
        Anm_Vis,
        Anm_Shp,
        Anm_6,
        Anm_7,

        Anm_Max,
    };

    //! Animation index
    typedef u16 AnmIdx;

    enum AnmPlayPolicy {
        AnmPlayPolicy_OneTime,
        AnmPlayPolicy_Loop,

        AnmPlayPolicy_2,
        AnmPlayPolicy_3,
        AnmPlayPolicy_4,

        AnmPlayPolicy_Max
    };

    enum BindType {
        BindType_One,
        BindType_Partial,

        BindType_Max
    };

protected:
    //! State flags
    u8 mFlags; // at 0x0

    //! Number of binds per animation type
    u16 mAnmNum[Anm_Max]; // at 0x2

    //! Index of the currently playing animation
    s16 mPlayIndex[Anm_Max]; // at 0x12
    //! Index of the previous animation
    s16 mPrevPlayIndex[Anm_Max]; // at 0x22

    //! Flag set per animation type
    u8* mpAnmFlags[Anm_Max]; // at 0x34

    u8 unk54;
    u8* mpBlendIndices; // at 0x58
    u32 unk5C;
    f32 unk60;
    f32 unk64;

public:
    virtual void Configure(); // at 0x8

    virtual void Regist(Anm anm, u16 idx, RPGrpHandle handle) = 0; // at 0xC

    virtual void RegistFromResFile(Anm anm, u16 idx, RPGrpHandle handle,
                                   const char* pName) = 0; // at 0x10

    virtual void RegistFromResFile(Anm anm, u16 idx, RPGrpHandle handle,
                                   u32 id) = 0; // at 0x14

    virtual s16 SetBlendAnm(Anm anm, u8, u16 idx); // at 0x18

    virtual s16 RemoveBlendAnm(Anm anm, u8, u8) = 0; // at 0x1C

    virtual void SetBlendWeight(Anm anm, u8, f32, u8) = 0; // at 0x20

    virtual s16 GetBlendAnm(Anm, u8, u8) = 0; // at 0x24

    virtual f32 GetBlendWeight(Anm, u8, u8) = 0; // at 0x28

    virtual void ReBindChrAnmNode(u16, u16, BindType) = 0; // at 0x2C

    virtual void ReleaseChrAnmNode(u16, u16, BindType) = 0; // at 0x30

    virtual bool StartNoBlend(Anm anm, u16 idx, f32 frame = 0.0f); // at 0x34

    virtual bool StartBlend(Anm anm, u16 idx, f32 weight = 0.0f,
                            f32 frame = 0.0f); // at 0x38

    virtual bool Cancel(Anm anm, u16 idx); // at 0x3C

    virtual bool Start(Anm anm, u16 idx, f32 frame = 0.0f); // at 0x40

    virtual f32 VF_0x44(UNKTYPE) = 0;

    virtual f32 VF_0x48(UNKTYPE) = 0;

    virtual int GetNumFrame(Anm anm, u16 idx) const = 0; // at 0x4C

    virtual AnmPlayPolicy GetAnmPlayPolicy(Anm anm,
                                           u16 idx) const = 0; // at 0x50

    virtual void SetFrame(Anm anm, u16 idx, f32 frame) = 0; // at 0x54

    virtual f32 GetFrame(Anm anm, u16 idx) const = 0; // at 0x58

    virtual void SetUpdateRate(Anm anm, u16 idx, f32 rate) = 0; // at 0x5C

    virtual f32 GetUpdateRate(Anm anm, u16 idx) const = 0; // at 0x60

    virtual void SetEnableQuaternionBlend(bool enable) { // at 0x64
        if (enable) {
            mFlags |= Flag_EnableQuaternionBlend;
        } else {
            mFlags &= ~Flag_EnableQuaternionBlend;
        }
    }

    virtual void SetEnableChrAnm(bool enable) { // at 0x68
        if (!enable) {
            mFlags |= Flag_DisableChrAnm;
        } else {
            mFlags &= ~Flag_DisableChrAnm;
        }
    }

    virtual void UpdateFrame() = 0; // at 0x6C

    virtual void VF_0x70(UNKTYPE) = 0; // at 0x70

    virtual void VF_0x74(UNKTYPE) = 0; // at 0x74

    virtual nw4r::g3d::AnmObj* GetAnmObj(Anm anm, u16 idx) const = 0; // at 0x78

    void CreateBuffer(Anm anm, u16 num);

    void Calc();

    s8 GetBlendIndex(Anm anm, AnmIdx idx, u8);

    void InternalRegist(Anm anm, u16 idx);

    bool StartNoSame(Anm anm, AnmIdx idx, f32 frame = 0.0f) {
        if (mPlayIndex[anm] != idx) {
            return StartNoBlend(anm, idx, frame);
        }

        return false;
    }

    bool StartBlendNoSame(Anm anm, AnmIdx idx, f32 frame = 0.0f) {
        if (mPlayIndex[anm] != idx) {
            return StartBlend(anm, idx, frame);
        }

        return false;
    }

    bool IsEnableQuaternionBlend() const {
        return mFlags & Flag_EnableQuaternionBlend;
    }

    bool IsEnableChrAnm() const {
        return !(mFlags & Flag_DisableChrAnm);
    }

    bool IsBlending(Anm anm) const {
        if (anm == Anm_Chr) {
            return unk60 > 0.0f;
        }

        return false;
    }

protected:
    /**
     * @brief Bitflags
     */
    enum {
        Flag_EnableQuaternionBlend = 1 << 0,
        Flag_DisableChrAnm = 1 << 1,
    };

    enum {
        AnmFlag_PlayingG3D = 1 << 0,
        AnmFlag_Playing = 1 << 1,
        AnmFlag_Regist = 1 << 2,
    };

protected:
    RPGrpModelAnm();
    virtual ~RPGrpModelAnm() {} // at 0x7C

    virtual void SetAnmObj(Anm anm,
                           nw4r::g3d::AnmObj** ppAnmObjs) = 0; // at 0x80
    virtual void InternalCalc() = 0;                           // at 0x84

    u16 GetAnmNum(Anm anm) const {
        return mAnmNum[anm];
    }
};

//! @}

#endif
