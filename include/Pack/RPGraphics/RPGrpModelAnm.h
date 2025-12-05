#ifndef RP_GRAPHICS_MODEL_ANM_H
#define RP_GRAPHICS_MODEL_ANM_H
#include <Pack/types_pack.h>

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
        Anm_ResAnmChr,
        Anm_ResAnmClr,
        Anm_ResAnmTexPat,
        Anm_ResAnmTexSrt,
        Anm_4,
        Anm_ResAnmShp,
        Anm_6,
        Anm_7,
    };

    enum AnmPlayPolicy {
        AnmPlayPolicy_OneTime,
        AnmPlayPolicy_Loop,
    };

protected:
    char _00[0x68];

public:
    virtual void Configure() = 0; // at 0x8
    virtual void Construct(Anm anm, u16 idx, u16 rd) = 0;

    virtual void Regist(Anm anm, u16 idx, u16 rd, char const* pName,
                        u32 arg4 = 0) = 0; // at 0x10
    virtual void VF_0x14(UNKTYPE) = 0;
    virtual void VF_0x18(UNKTYPE) = 0;
    virtual void VF_0x1C(UNKTYPE) = 0;

    virtual void VF_0x20(UNKTYPE) = 0;
    virtual void VF_0x24(UNKTYPE) = 0;
    virtual void VF_0x28(UNKTYPE) = 0;
    virtual void VF_0x2C(UNKTYPE) = 0;

    virtual void VF_0x30(UNKTYPE) = 0;
    virtual void VF_0x34(UNKTYPE) = 0;
    virtual void VF_0x38(UNKTYPE) = 0;

    virtual void Cancel(Anm anm, u16 idx) = 0;
    virtual void Start(Anm anm, u16 idx, f32 frame = 1.0f) = 0; // at 0x40

    virtual f32 VF_0x44(UNKTYPE) = 0;
    virtual f32 VF_0x48(UNKTYPE) = 0;

    virtual u16 GetNumFrame(Anm anm, u16 idx) const = 0; // at 0x4C
    virtual AnmPlayPolicy GetAnmPlayPolicy(Anm anm,
                                           u16 idx) const = 0; // at 0x50

    virtual void SetFrame(Anm anm, u16 idx, f32 frame) = 0; // at 0x54
    virtual f32 GetFrame(Anm anm, u16 idx) const = 0;       // at 0x58

    virtual void SetUpdateRate(Anm anm, u16 idx, f32 rate) = 0; // at 0x5C
    virtual f32 GetUpdateRate(Anm anm, u16 idx) const = 0;      // at 0x60

    virtual void SetEnableQuaternionBlend(bool enable) = 0; // at 0x64

    virtual void VF_0x68(UNKTYPE) = 0; // at 0x68
    virtual void UpdateFrame() = 0;    // at 0x6C
    virtual void VF_0x70(UNKTYPE) = 0; // at 0x70
    virtual void VF_0x74(UNKTYPE) = 0; // at 0x74

    virtual nw4r::g3d::AnmObj* GetAnmObj(Anm anm, u16 idx) const = 0; // at 0x78

    void CreateBuffer(Anm anm, u16 num);

    void Calc();

protected:
    RPGrpModelAnm(RPGrpModel* pModel);
    virtual ~RPGrpModelAnm(); // at 0x7C

    virtual void SetAnmObj(Anm anm, nw4r::g3d::AnmObj* pAnmObj) = 0; // at 0x80
    virtual void InternalCalc() = 0;                                 // at 0x84
};

//! @}

#endif
